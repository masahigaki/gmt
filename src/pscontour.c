/*--------------------------------------------------------------------
 *
 *	Copyright (c) 1991-2025 by the GMT Team (https://www.generic-mapping-tools.org/team.html)
 *	See LICENSE.TXT file for copying and redistribution conditions.
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation; version 3 or any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU Lesser General Public License for more details.
 *
 *	Contact info: www.generic-mapping-tools.org
 *--------------------------------------------------------------------*/
/* Brief synopsis: pscontour will read a file of points in the plane, performs the
 * Delaunay triangulation, and contours these triangles.  As an option
 * the user may provide a file with indices of which vertices constitute
 * the triangles.
 *
 * Author:	Paul Wessel
 * Date:	1-JAN-2010
 * Version:	6 API
 *
 * Note on KEYS: AD)=t means -A takes an optional output Dataset as argument via the +t modifier.
 *               G?(=1 means if -Gf|x is given then we may read an input Dataset, else we set type to ! to skip it
 *               The "1" means we must skip the single char (f or x) before finding the file name
 */

#include "gmt_dev.h"
#include "longopt/pscontour_inc.h"

#define THIS_MODULE_CLASSIC_NAME	"pscontour"
#define THIS_MODULE_MODERN_NAME	"contour"
#define THIS_MODULE_LIB		"core"
#define THIS_MODULE_PURPOSE	"Contour table data by direct triangulation"
#define THIS_MODULE_KEYS	"<D{,AD)=t,CC(,ED(,DDD,G?(=1,>X}"
#define THIS_MODULE_NEEDS	"Jd"
#define THIS_MODULE_OPTIONS "-:>BJKOPRUVXYbdefhilpqstxy" GMT_OPT("Mmc")

struct PSCONTOUR_CTRL {
	struct GMT_CONTOUR contour;
	struct PSCONTOUR_A {	/* -A[n|<int>][labelinfo] */
		bool active;
		struct CONTOUR_ARGS info;
	} A;
	struct PSCONTOUR_C {	/* -C<cpt> */
		bool active;
		struct CONTOUR_ARGS info;
	} C;
	struct PSCONTOUR_D {	/* -D<dumpfile> */
		bool active;
		char *file;
	} D;
	struct PSCONTOUR_E {	/* -E<indexfile>[+b] */
		bool active;
		bool binary;
		char *file;
	} E;
	struct PSCONTOUR_G {	/* -G[d|f|n|l|L|x|X]<params> */
		bool active;
	} G;
	struct PSCONTOUR_I {	/* -I */
		bool active;
	} I;
	struct PSCONTOUR_L {	/* -L<pen> */
		bool active;
		struct GMT_PEN pen;
	} L;
	struct PSCONTOUR_N {	/* -N */
		bool active;
	} N;
	struct PSCONTOUR_S {	/* -S[p|t] */
		bool active;
		unsigned int mode;	/* 0 skip points; 1 skip triangles */
	} S;
	struct PSCONTOUR_T {	/* -T[h|l][+a][+d<gap>[c|i|p][/<length>[c|i|p]]][+lLH|"low,high"] */
		bool active;
		struct CONTOUR_CLOSED info;
	} T;
	struct PSCONTOUR_Q {	/* -Q[<cut>][+z] */
		bool active;
		bool zero;	/* True if we should skip zero-contour */
		bool project;	/* True if we need distances in plot units */
		double length;
		int mode;	/* Could be negative */
		unsigned int min;
		char unit;
	} Q;
	struct PSCONTOUR_W {	/* -W[a|c]<pen>[+c[l|f]] */
		bool active;
		bool cpt_effect;
		unsigned int cptmode;	/* Apply to both a&c */
		struct GMT_PEN pen[2];
	} W;
};

#define PSCONTOUR_MIN_LENGTH 0.01	/* Contours shorter than this are skipped */
#define PEN_CONT	0
#define PEN_ANNOT	1

struct PSCONTOUR_SAVE {
	double *x, *y;
	double cval;
	unsigned int n;
	struct GMT_PEN pen;
	struct GMT_FONT font;
	bool do_it, high;
};

/* Returns the id of the node common to the two edges */
#define get_node_index(edge_1, edge_2) (((pscontour_sum = (edge_1) + (edge_2)) == 1) ? 1 : ((pscontour_sum == 2) ? 0 : 2))
#define get_other_node(node1, node2) (((pscontour_sum = (node1 + node2)) == 3) ? 0 : ((pscontour_sum == 2) ? 1 : 2))	/* The other node needed */

struct PSCONTOUR_LINE {	/* Beginning and end of straight contour segment */
	double x0, y0;
	double x1, y1;
};

struct PSCONTOUR {
	size_t n_alloc;
	unsigned int nl;
	struct PSCONTOUR_LINE *L;
};

struct PSCONTOUR_PT {
	double x, y;
	struct PSCONTOUR_PT *next;
};

struct PSCONTOUR_CHAIN {
	struct PSCONTOUR_PT *begin;
	struct PSCONTOUR_PT *end;
	struct PSCONTOUR_CHAIN *next;
};

static void *New_Ctrl (struct GMT_CTRL *GMT) {	/* Allocate and initialize a new control structure */
	struct PSCONTOUR_CTRL *C;

	C = gmt_M_memory (GMT, NULL, 1, struct PSCONTOUR_CTRL);

	/* Initialize values whose defaults are not 0/false/NULL */
	gmt_contlabel_init (GMT, &C->contour, 1);
	C->A.info.single_cont = GMT->session.d_NaN;
	C->C.info.single_cont = GMT->session.d_NaN;
	C->L.pen = GMT->current.setting.map_default_pen;
	C->T.info.dim[GMT_X] = GMT_TICKED_SPACING * GMT->session.u2u[GMT_PT][GMT_INCH];	/* 14p */
	C->T.info.dim[GMT_Y] = GMT_TICKED_LENGTH  * GMT->session.u2u[GMT_PT][GMT_INCH];	/* 3p */
	C->W.pen[PEN_CONT] = C->W.pen[PEN_ANNOT] = GMT->current.setting.map_default_pen;
	C->W.pen[PEN_ANNOT].width *= 3.0;

	return (C);
}

static void Free_Ctrl (struct GMT_CTRL *GMT, struct PSCONTOUR_CTRL *C) {	/* Deallocate control structure */
	if (!C) return;
	gmt_M_str_free (C->C.info.file);
	gmt_M_str_free (C->D.file);
	gmt_M_str_free (C->E.file);
	gmt_M_str_free (C->T.info.txt[0]);
	gmt_M_str_free (C->T.info.txt[1]);
	gmt_M_free (GMT, C);
}

GMT_LOCAL int pscontour_get_triangle_crossings (struct GMT_CTRL *GMT, struct GMT_CONTOUR_INFO *P, unsigned int n_conts, double *x, double *y, double *z, int *ind, double small, double **xc, double **yc, double **zc, unsigned int **v, unsigned int **cindex) {
	/* This routine finds all the contour crossings for this triangle.  Each contour consists of
	 * linesegments made up of two points, with coordinates xc, yc, and contour level zc.
	 */

	unsigned int i, j, k, k2, i1, nx, n_ok, *vout = NULL, *cind = NULL, *ctmp = NULL;
	bool ok;
	double xx[3], yy[3], zz[3], zmin, zmax, dz, frac, *xout = NULL, *yout = NULL, *zout = NULL, *ztmp = NULL;
	size_t n_alloc;

	xx[0] = x[ind[0]];	yy[0] = y[ind[0]];	zz[0] = z[ind[0]];
	xx[1] = x[ind[1]];	yy[1] = y[ind[1]];	zz[1] = z[ind[1]];
	xx[2] = x[ind[2]];	yy[2] = y[ind[2]];	zz[2] = z[ind[2]];

	if (gmt_M_is_dnan (zz[0]) || gmt_M_is_dnan (zz[1]) || gmt_M_is_dnan (zz[2])) return (0);	/* Cannot have crossings if NaNs are present */
	if (zz[0] == zz[1] && zz[1] == zz[2]) return (0);	/* Cannot have crossings if all nodes are equal */

	zmin = MIN (zz[0], MIN (zz[1], zz[2]));	/* Min z vertex */
	zmax = MAX (zz[0], MAX (zz[1], zz[2]));	/* Max z vertex */

	i = 0;	j = n_conts - 1;
	while (P[i].val < zmin && i < n_conts) i++;
	while (P[j].val > zmax && j > 0) j--;

	nx = j - i + 1;	/* Total number of contours */

	if (nx <= 0) return (0);

	n_alloc = 2 * nx;
	xout = gmt_M_memory (GMT, NULL, n_alloc, double);
	yout = gmt_M_memory (GMT, NULL, n_alloc, double);
	ztmp = gmt_M_memory (GMT, NULL, n_alloc, double);
	zout = gmt_M_memory (GMT, NULL, n_alloc, double);
	vout = gmt_M_memory (GMT, NULL, n_alloc, unsigned int);
	ctmp = gmt_M_memory (GMT, NULL, nx, unsigned int);
	cind = gmt_M_memory (GMT, NULL, nx, unsigned int);

	/* Fill out array zout which holds the nx contour levels */

	k = k2 = 0;
	while (i <= j) {
		ztmp[k2] = ztmp[k2+1] = P[i].val;
		ctmp[k++] = i;
		k2 += 2;
		i++;
	}

	/* Loop over the contour levels and determine the line segments */

	for (k = k2 = j = n_ok = 0; k < nx; k++, k2 += 2) {
		ok = false;
		for (i = 0; i < 3; i++) if (zz[i] == ztmp[k2]) zz[i] += small;	/* Refuse to go through nodes */
		for (i = 0; i < 3; i++) {	/* Try each side in turn 0-1, 1-2, 2-0 */
			i1 = (i == 2) ? 0 : i + 1;
			if ((ztmp[k2] >= zz[i] && ztmp[k2] < zz[i1]) || (ztmp[k2] <= zz[i] && ztmp[k2] > zz[i1])) {
				dz = zz[i1] - zz[i];
				if (dz == 0.0) {	/* Contour goes along edge */
					xout[j] = xx[i];	yout[j] = yy[i];
				}
				else {
					frac = (ztmp[k2] - zz[i]) / dz;
					xout[j] = xx[i] + frac * (xx[i1] - xx[i]);
					yout[j] = yy[i] + frac * (yy[i1] - yy[i]);
				}
				zout[j] = ztmp[k2];
				vout[j++] = i;	/* Keep track of the side number */
				ok = true;	/* Wish to add this segment */
			}
		}
		if (j%2)
			j--;	/* Contour went through a single vertex only, skip this */
		else if (ok)
			cind[n_ok++] = ctmp[k];
	}

	nx = j / 2;	/* Since j might have changed */
	if (nx) {
		*xc = xout;
		*yc = yout;
		*zc = zout;
		*v = vout;
		*cindex = cind;
	} else {
		gmt_M_free (GMT, xout);
		gmt_M_free (GMT, yout);
		gmt_M_free (GMT, zout);
		gmt_M_free (GMT, vout);
		gmt_M_free (GMT, cind);
	}
	gmt_M_free (GMT, ztmp);
	gmt_M_free (GMT, ctmp);
	return (nx);
}

GMT_LOCAL void pscontour_paint_it (struct GMT_CTRL *GMT, struct PSL_CTRL *PSL, struct GMT_PALETTE *P, double x[], double y[], int n, double z) {
	int index;
	double rgb[4];
	struct GMT_FILL *f = NULL;
	struct GMT_PALETTE_HIDDEN *PH = gmt_get_C_hidden (P);

	if (n < 3) return;	/* Need at least 3 points to make a polygon */

	index = gmt_get_rgb_from_z (GMT, P, z, rgb);
	if (PH->skip) return;	/* Skip this z-slice */

	/* Now we must paint, with colors or patterns */

	if ((index >= 0 && (f = P->data[index].fill) != NULL) || (index < 0 && (f = P->bfn[index+3].fill) != NULL))
		gmt_setfill (GMT, f, 0);
	else
		PSL_setfill (PSL, rgb, -2);
	/* Contours drawn separately later if desired */
	PSL_plotpolygon (PSL, x, y, n);
}

GMT_LOCAL void pscontour_sort_and_plot_ticks (struct GMT_CTRL *GMT, struct PSL_CTRL *PSL, struct PSCONTOUR_SAVE *save, size_t n, double *x, double *y, double *z, unsigned int nn, struct CONTOUR_CLOSED *I, unsigned int mode, struct GMT_DATASET *T) {
	/* Labeling and ticking of inner-most contours cannot happen until all contours are found and we can determine
	which are the innermost ones.

	   Note: mode = 1 (plot only), 2 (save labels only), 3 (both).
	*/
	unsigned int np, pol, pol2, j, kk, inside, n_ticks, form;
	int way, k;
	char *lbl[2], *def[2] = {"-", "+"};
	double add, dx, dy, x_back, y_back, x_end, y_end, sa, ca, s;
	double x_mean, y_mean, a, xmin, xmax, ymin, ymax, length;

	double tick_gap = I->dim[GMT_X];
	double tick_length = I->dim[GMT_Y];

	lbl[0] = (I->txt[0]) ? I->txt[0] : def[0];
	lbl[1] = (I->txt[1]) ? I->txt[1] : def[1];

	/* The x/y coordinates in SAVE are now all projected to map inches */

	for (pol = 0; pol < n; pol++) {	/* Mark polygons that have other polygons inside them */
		np = save[pol].n;
		for (pol2 = 0; save[pol].do_it && pol2 < n; pol2++) {
			inside = gmt_non_zero_winding (GMT, save[pol2].x[0], save[pol2].y[0], save[pol].x, save[pol].y, np);
			if (inside == GMT_INSIDE && !I->all) save[pol].do_it = false;
		}
	}

	(void)gmt_setfont (GMT, &GMT->current.setting.font_annot[GMT_PRIMARY]);

	/* Here, only the polygons that are innermost (containing the local max/min, will have do_it = true */

	PSL_settextmode (PSL, PSL_TXTMODE_MINUS);	/* Replace hyphens with minus signs */

	for (pol = 0; pol < n; pol++) {
		if (!save[pol].do_it) continue;
		np = save[pol].n;

		/* Here we need to figure out if this is a local high or low. */

		/* First determine the bounding box for this contour */
		xmin = xmax = save[pol].x[0];	ymin = ymax = save[pol].y[0];
		for (j = 1; j < np; j++) {
			xmin = MIN (xmin, save[pol].x[j]);
			xmax = MAX (xmax, save[pol].x[j]);
			ymin = MIN (ymin, save[pol].y[j]);
			ymax = MAX (ymax, save[pol].y[j]);
		}

		/* Now try to find a data point inside this contour */

		for (j = 0, k = GMT_NOTSET; k == GMT_NOTSET && j < nn; j++) {
			if (gmt_M_y_is_outside (GMT, y[j], ymin, ymax)) continue;	/* Outside y-range */
			if (gmt_M_y_is_outside (GMT, x[j], xmin, xmax)) continue;	/* Outside x-range (YES, use gmt_M_y_is_outside since projected x-coordinates)*/

			inside = gmt_non_zero_winding (GMT, x[j], y[j], save[pol].x, save[pol].y, np);
			if (inside == GMT_INSIDE) k = j;	/* OK, this point is inside */
		}
		if (k == GMT_NOTSET) continue;	/* Unable to determine */
		save[pol].high = (z[k] > save[pol].cval);

		if (save[pol].high && !I->high) continue;	/* Do not tick highs */
		if (!save[pol].high && !I->low) continue;	/* Do not tick lows */

		for (j = 1, s = 0.0; j < np; j++) {	/* Compute distance along the contour */
			s += hypot (save[pol].x[j]-save[pol].x[j-1], save[pol].y[j]-save[pol].y[j-1]);
		}
		if (s < PSCONTOUR_MIN_LENGTH) continue;	/* Contour is too short to be ticked or labeled */

		n_ticks = urint (floor (s / tick_gap));
		if (n_ticks == 0) continue;	/* Too short to be ticked or labeled */

		gmt_setpen (GMT, &save[pol].pen);
		way = gmt_polygon_centroid (GMT, save[pol].x, save[pol].y, np, &x_mean, &y_mean);	/* -1 is CCW, +1 is CW */
		if (I->label) {	/* Compute mean location of closed contour ~hopefully a good point inside to place label. */
			if (mode & 1) {
				form = gmt_setfont (GMT, &save[pol].font);
				PSL_plottext (PSL, x_mean, y_mean, GMT->current.setting.font_annot[GMT_PRIMARY].size, lbl[save[pol].high], 0.0, PSL_MC, form);
			}
			if (mode & 2) gmt_add_label_record (GMT, T, x_mean, y_mean, 0.0, lbl[save[pol].high]);
		}
		if (mode & 1) {	/* Tick the innermost contour */
			add = M_PI_2 * ((save[pol].high) ? -way : +way);	/* So that tick points in the right direction */
			gmt_setpen (GMT, &save[pol].pen);
			for (j = 1; j < np; j++) {	/* Consider each segment from point j-1 to j */
				dx = save[pol].x[j] - save[pol].x[j-1];
				dy = save[pol].y[j] - save[pol].y[j-1];
				length = hypot (dx, dy);
				n_ticks = urint (ceil (length / tick_gap));	/* At least one per side */
				a = atan2 (dy, dx) + add;
				sincos (a, &sa, &ca);
				for (kk = 0; kk <= n_ticks; kk++) {
					x_back = save[pol].x[j-1] + kk * dx / (n_ticks + 1);
					y_back = save[pol].y[j-1] + kk * dy / (n_ticks + 1);
					x_end = x_back + tick_length * ca;
					y_end = y_back + tick_length * sa;
					PSL_plotsegment (PSL, x_back, y_back, x_end, y_end);
				}
			}
		}
	}

	PSL_settextmode (PSL, PSL_TXTMODE_HYPHEN);	/* Back to leave as is */
}

static int usage (struct GMTAPI_CTRL *API, int level) {
	struct GMT_PEN P;

	const char *name = gmt_show_name_and_purpose (API, THIS_MODULE_LIB, THIS_MODULE_CLASSIC_NAME, THIS_MODULE_PURPOSE);
	if (level == GMT_MODULE_PURPOSE) return (GMT_NOERROR);
	GMT_Usage (API, 0, "usage: %s <table> %s %s [-A[n|<contours>][<labelinfo>]] [%s] [-C<contours>] [-D<template>] "
		"[-E<indextable>[+b]] [%s] [-I] %s[-L<pen>] [-N] %s%s[-Q[<n>|<length>[unit]][+z]] [-S[p|t]] [%s] [%s] [-W[a|c]<pen>[+c[l|f]]] "
		"[%s] [%s] [%s] [%s] %s[%s] [%s] [%s] [%s] [%s] [%s] [%s] [%s] [%s] [%s] [%s] [%s]\n",
	     name, GMT_J_OPT, GMT_Rgeoz_OPT, GMT_B_OPT, GMT_CONTG, API->K_OPT, API->O_OPT, API->P_OPT, GMT_CONTT, GMT_U_OPT,
	     GMT_V_OPT, GMT_X_OPT, GMT_Y_OPT, GMT_b_OPT, API->c_OPT, GMT_d_OPT, GMT_e_OPT, GMT_f_OPT, GMT_h_OPT, GMT_i_OPT,
	     GMT_l_OPT, GMT_p_OPT, GMT_qi_OPT, GMT_t_OPT, GMT_s_OPT, GMT_colon_OPT, GMT_PAR_OPT);

	if (level == GMT_SYNOPSIS) return (GMT_MODULE_SYNOPSIS);

	GMT_Message (API, GMT_TIME_NONE, "  REQUIRED ARGUMENTS:\n");
	GMT_Option (API, "<");
	GMT_Option (API, "J-Z,R");
	GMT_Message (API, GMT_TIME_NONE, "\n  OPTIONAL ARGUMENTS:\n");
	GMT_Usage (API, 1, "\n-A[n|<contours>][<labelinfo>]");
	GMT_Usage (API, -2, "Annotation label information. [Default is no annotated contours]. "
		"Give annotation interval or comma-separated list of contours "
		"(for single contour append comma to be seen as list). "
		"Alternatively, give -An to disable all contour annotations "
		"implied by the information provided in -C.");
	GMT_Usage (API, -2, "<labelinfo> controls the specifics of the labels.  Choose from:");
	gmt_label_syntax (API->GMT, 2, 1);
	GMT_Option (API, "B-");
	GMT_Usage (API, 1, "\n-C<contours>");
	GMT_Usage (API, -2, "Contours to be drawn can be specified in one of four ways:");
	GMT_Usage (API, 3, "%s Fixed contour interval.", GMT_LINE_BULLET);
	GMT_Usage (API, 3, "%s Comma-separated contours (for single contour append comma to be seen as list).", GMT_LINE_BULLET);
	GMT_Usage (API, 3, "%s File with contour levels, types, and optional fixed annotation angle and/or pen: "
		"<contlevel> [[<angle>] C|c|A|a [<pen>]]. Use A|a for annotated contours and C|c for plain contours. If -T is used, "
		"only inner-most contours with upper case C or A will be ticked. "
		"If file only contains <contlevel> then we default to type C for plain contours only.", GMT_LINE_BULLET);
	GMT_Usage (API, 3, "%s Name of a CPT. [CPT contours are set to C unless the CPT flags are set; "
		"Use -A to force all to become A].", GMT_LINE_BULLET);
	GMT_Usage (API, -2, "Note: If neither -A nor -C are set then we auto-select the intervals.");
	GMT_Usage (API, 1, "\n-D<template>");
	GMT_Usage (API, -2, "Dump contours as data line segments; no plotting takes place. "
		"Append filename template which may contain C-format specifiers. "
		"If no filename template is given we write all lines to standard output. "
		"If filename has no specifiers then we write all lines to a single file. "
		"If a float format (e.g., %%6.2f) is found we substitute the contour z-value. "
		"If an integer format (e.g., %%06d) is found we substitute a running segment count. "
		"If an char format (%%c) is found we substitute C or O for closed and open contours. "
		"The 1-3 specifiers may be combined and appear in any order to produce the "
		"the desired number of output files (e.g., just %%c gives two files, just %%f would. "
		"separate segments into one file per contour level, and %%d would write all segments. "
		"to individual files; see module documentation for more examples.");
	GMT_Usage (API, 1, "\n-E<indextable>[+b]");
	GMT_Usage (API, -2, "File with triplets of point indices for each triangle "
		"[Default performs the Delaunay triangulation on <table>].  Append +b to read this file using "
		"the same binary settings as for the primary input file [Read as ASCII].");
	GMT_Usage (API, 1, "\n%s", GMT_CONTG);
	GMT_Usage (API, -2, "Control placement of labels along contours.  Choose among five algorithms:");
	gmt_cont_syntax (API->GMT, 2, 0);
	GMT_Usage (API, 1, "\n-I Color triangles using the CPT.");
	GMT_Option (API, "K");
	gmt_pen_syntax (API->GMT, 'L', NULL, "Draws the triangular mesh with the specified pen.", NULL, 0);
	GMT_Usage (API, 1, "\n-N Do NOT clip contours/image at the border [Default clips].");
	GMT_Option (API, "O,P");
	GMT_Usage (API, 1, "\n-Q[<n>|<length>[unit]][+z]");
	GMT_Usage (API, -2, "Do not draw closed contours with less than <n> points [Draw all contours]. "
		"Alternatively, give a minimum contour length and append a unit (%s, or c for Cartesian). "
		"Unit C means Cartesian distances after first projecting the input coordinates. "
		"Optionally, append +z to skip tracing the zero-contour.", GMT_LEN_UNITS_DISPLAY);
	GMT_Usage (API, 1, "\n-S[p|t]");
	GMT_Usage (API, -2, "Control skipping of points or triangles [Default keeps all]:");
	GMT_Usage (API, 3, "p: Skip points outside the region [Default].");
	GMT_Usage (API, 3, "t: Skip triangles whose three vertices are outside the region.");
	GMT_Usage (API, 1, "\n%s", GMT_CONTT);
	gmt_innercont_syntax (API->GMT);
	GMT_Option (API, "U,V");
	gmt_pen_syntax (API->GMT, 'W', NULL, "Set pen attributes. Append a<pen> for annotated or c<pen> for regular contours [Default].", NULL, 0);
	GMT_Usage (API, -2, "The default settings are:n");
	P = API->GMT->current.setting.map_default_pen;
	GMT_Usage (API, 3, "%s Contour pen:  %s.", GMT_LINE_BULLET, gmt_putpen (API->GMT, &P));
	P.width *= 3.0;
	GMT_Usage (API, 3, "%s Annotate pen: %s.", GMT_LINE_BULLET, gmt_putpen (API->GMT, &P));
 	GMT_Usage (API, 3, "+c Controls how pens and fills are affected if a CPT is specified via -C: "
 		"Append l to let pen colors follow the CPT setting (requires -C). "
 		"Append f to let fill/font colors follow the CPT setting. "
 		"Default [+c] sets both effects.");
	GMT_Option (API, "X,bi3,bo,c,d,e,f,h,i,l");
	GMT_Usage (API, -2, "Normally, the annotated contour is selected; change this by specifying the label as "
		"[<annotcontlabel>][/<contlabel>] (use separator | if / is part of the label).");
	GMT_Option (API, "p,qi,s,t,:,.");

	return (GMT_MODULE_USAGE);
}

static int parse (struct GMT_CTRL *GMT, struct PSCONTOUR_CTRL *Ctrl, struct GMT_OPTION *options) {
	/* This parses the options provided to pscontour and sets parameters in Ctrl.
	 * Note Ctrl has already been initialized and non-zero default values set.
	 * Any GMT common options will override values set previously by other commands.
	 * It also replaces any file names specified as input or output with the data ID
	 * returned when registering these sources/destinations with the API.
	 */

	unsigned int n_errors = 0, id, reset = 0;
	int k, j, n;
	char txt_a[GMT_LEN256] = {""}, *c = NULL;
	struct GMT_OPTION *opt = NULL;
	struct GMTAPI_CTRL *API = GMT->parent;

	for (opt = options; opt; opt = opt->next) {	/* Process all the options given */

		switch (opt->option) {

			case '<':	/* Skip input files */
				if (GMT_Get_FilePath (API, GMT_IS_DATASET, GMT_IN, GMT_FILE_REMOTE, &(opt->arg))) n_errors++;
				break;

			/* Processes program-specific parameters */

			case 'A':	/* Annotation control */
				n_errors += gmt_M_repeated_module_option (API, Ctrl->A.active);
				k = gmt_contour_first_pos (GMT, opt->arg);	/* Do deal with backwards compatibility */
				if ((c = gmt_first_modifier (GMT, &opt->arg[k], GMT_CONTSPEC_MODS))) {	/* Process any modifiers */
					if (gmt_contlabel_specs (GMT, c, &Ctrl->contour)) {
						GMT_Report (API, GMT_MSG_ERROR, "Option -A: Expected\n\t-A[n|<contours>][+a<angle>|n|p[u|d]][+c<dx>[/<dy>]][+d][+e][+f<font>][+g<fill>][+i][+j<just>][+l<label>][+n|N<dx>[/<dy>]][+o][+p<pen>][+r<min_rc>][+t[<file>]][+u<unit>][+v][+w<width>][+=<prefix>]\n");
						n_errors ++;
					}
					c[0] = '\0';	/* Chop off modifiers since parsed by gmt_contlabel_specs */
				}
				n_errors += gmt_contour_A_arg_parsing (GMT, opt->arg, &Ctrl->A.info);
				if (Ctrl->A.info.mode == 0) Ctrl->contour.annot = true;
				if (c) c[0] = '+';	/* Restore modifiers */
				break;
			case 'C':	/* Contour arguments */
				n_errors += gmt_M_repeated_module_option (API, Ctrl->C.active);
				n_errors += gmt_contour_C_arg_parsing (GMT, opt->arg, &Ctrl->C.info);
				break;
			case 'D':	/* Dump contours */
				n_errors += gmt_M_repeated_module_option (API, Ctrl->D.active);
				if (opt->arg[0]) Ctrl->D.file = strdup (opt->arg);
				break;
			case 'E':	/* Triplet file */
				n_errors += gmt_M_repeated_module_option (API, Ctrl->E.active);
				if ((c = strstr (opt->arg, "+b"))) {
					Ctrl->E.binary = true;
					c[0] = '\0';
				}
				n_errors += gmt_get_required_file (GMT, opt->arg, opt->option, 0, GMT_IS_DATASET, GMT_IN, GMT_FILE_REMOTE, &(Ctrl->E.file));
				if (c) c[0] = '+';	/* Restore chopped off modifier */
				break;
			case 'G':	/* contour annotation settings */
				n_errors += gmt_M_repeated_module_option (API, Ctrl->G.active);
				n_errors += gmt_contlabel_info (GMT, 'G', opt->arg, &Ctrl->contour);
				break;
			case 'I':	/* Image triangles */
				n_errors += gmt_M_repeated_module_option (API, Ctrl->I.active);
				n_errors += gmt_get_no_argument (GMT, opt->arg, opt->option, 0);
				break;
			case 'L':	/* Draw triangular mesh lines */
				n_errors += gmt_M_repeated_module_option (API, Ctrl->L.active);
				if (gmt_getpen (GMT, opt->arg, &Ctrl->L.pen)) {
					gmt_pen_syntax (GMT, 'L', NULL, " ", NULL, 0);
					n_errors++;
				}
				break;
			case 'N':	/* Do not clip at boundary */
				n_errors += gmt_M_repeated_module_option (API, Ctrl->N.active);
				n_errors += gmt_get_no_argument (GMT, opt->arg, opt->option, 0);
				break;
			case 'Q':	/* Skip small closed contours */
				n_errors += gmt_M_repeated_module_option (API, Ctrl->Q.active);
				if (!gmt_access (GMT, opt->arg, F_OK) && gmt_M_compat_check (GMT, 4)) {	/* Must be the now old -Q<indexfile> option, set to -E */
					GMT_Report (API, GMT_MSG_COMPAT, "Option -Q<indexfile> is deprecated; use -E instead.\n");
					n_errors += gmt_get_required_file (GMT, opt->arg, opt->option, 0, GMT_IS_DATASET, GMT_IN, GMT_FILE_REMOTE, &(Ctrl->E.file));
					Ctrl->E.active = true;
					break;
				}
				if ((c = strstr (opt->arg, "+z"))) {
					Ctrl->Q.zero = true;
					c[0] = '\0';	/* Temporarily chop off modifier */
				}
				if (opt->arg[0]) {
					size_t last = strlen (opt->arg) - 1;
					Ctrl->Q.active = true;
					if (strchr (GMT_LEN_UNITS, opt->arg[last]))	/* Gave a minimum length in data units */
						Ctrl->Q.mode = gmt_get_distance (GMT, opt->arg, &(Ctrl->Q.length), &(Ctrl->Q.unit));
					else if (opt->arg[last] == 'C') {	/* Projected units */
						Ctrl->Q.length = atof (opt->arg);
						Ctrl->Q.project = true;
						Ctrl->Q.unit = 'C';
					}
					else if (opt->arg[last] == 'c') {	/* Cartesian units */
						Ctrl->Q.length = atof (opt->arg);
						Ctrl->Q.unit = 'X';
					}
					else {	/* Just a point count cutoff */
						n = atoi (opt->arg);
						n_errors += gmt_M_check_condition (GMT, n < 0, "Option -Q: Point count must be >= 0\n");
						Ctrl->Q.min = n;
					}
				}
				if (c) c[0] = '+';	/* Restore */
				break;
			case 'S':	/* Skip points outside border */
				n_errors += gmt_M_repeated_module_option (API, Ctrl->S.active);
				if (opt->arg[0] == 'p') Ctrl->S.mode = 0;
				else if (opt->arg[0] == 't') Ctrl->S.mode = 1;
				break;
			case 'T':	/* Embellish innermost closed contours */
				if (!gmt_access (GMT, opt->arg, F_OK) && gmt_M_compat_check (GMT, 4)) {	/* Must be the old -T<indexfile> option, set to -E */
					GMT_Report (API, GMT_MSG_COMPAT, "Option -T<indexfile> is deprecated; use -E instead.\n");
					n_errors += gmt_get_required_file (GMT, opt->arg, opt->option, 0, GMT_IS_DATASET, GMT_IN, GMT_FILE_REMOTE, &(Ctrl->E.file));
					Ctrl->E.active = true;
					break;
				}
				n_errors += gmt_M_repeated_module_option (API, Ctrl->T.active);
				n_errors += gmt_contour_T_arg_parsing (GMT, opt->arg, &Ctrl->T.info);
				break;
			case 'W':	/* Sets pen attributes */
				Ctrl->W.active = true;
				k = reset = 0;
				if ((opt->arg[0] == '-' && opt->arg[1]) || (opt->arg[0] == '+' && opt->arg[1] != 'c')) {	/* Definitively old-style args */
					if (opt->arg[k] == '+') Ctrl->W.cptmode = 1, k++;
					if (opt->arg[k] == '-') Ctrl->W.cptmode = 3, k++;
					j = (opt->arg[k] == 'a' || opt->arg[k] == 'c') ? k+1 : k;
				}
				else {
					if ((c = strstr (opt->arg, "+c"))) {	/* Gave +c modifier - apply to both pens */
						switch (c[2]) {
							case 'l': Ctrl->W.cptmode = 1; break;
							case 'f': Ctrl->W.cptmode = 2; break;
							default:  Ctrl->W.cptmode = 3; break;
						}
						if (!strncmp (&c[2], "lf", 2U) || !strncmp (&c[2], "fl", 2U))	/* Catch any odd +clf or +cfl modifiers */
							Ctrl->W.cptmode = 3;
						c[0] = 0;	/* Temporarily chop of */
						reset = 1;
					}
					j = (opt->arg[0] == 'a' || opt->arg[0] == 'c') ? k+1 : k;
				}
				if (j == k && opt->arg[j]) {	/* Set both */
					if (gmt_getpen (GMT, &opt->arg[j], &Ctrl->W.pen[PEN_CONT])) {
						gmt_pen_syntax (GMT, 'W', NULL, " ", NULL, 0);
						n_errors++;
					}
					else
						Ctrl->W.pen[PEN_ANNOT] = Ctrl->W.pen[PEN_CONT];
				}
				else if (opt->arg[j]) {	/* Gave a or c.  Because the user may say -Wcyan we must prevent this from being seen as -Wc and color yan! */
					/* Get the argument following a or c and up to first comma, slash (or to the end) */
					n = k+1;
					while (!(opt->arg[n] == ',' || opt->arg[n] == '/' || opt->arg[n] == '\0')) n++;
					strncpy (txt_a, &opt->arg[k], (size_t)(n-k));	txt_a[n-k] = '\0';
					if (gmt_colorname2index (GMT, txt_a) >= 0) j = k;	/* Found a colorname; wind j back by 1 */
					id = (opt->arg[k] == 'a') ? PEN_ANNOT : PEN_CONT;
					if (gmt_getpen (GMT, &opt->arg[j], &Ctrl->W.pen[id])) {
						gmt_pen_syntax (GMT, 'W', NULL, " ", NULL, 0);
						n_errors++;
					}
					if (j == k) Ctrl->W.pen[PEN_ANNOT] = Ctrl->W.pen[PEN_CONT];	/* Must copy since it was not -Wc nor -Wa after all */
				}
				if (reset) c[0] = '+';
				if (Ctrl->W.cptmode) Ctrl->W.cpt_effect = true;
				break;

			default:	/* Report bad options */
				n_errors += gmt_default_option_error (GMT, opt);
				break;
		}
	}

	if (Ctrl->C.info.check && gmt_consider_current_cpt (API, &Ctrl->C.active, &(Ctrl->C.info.file)))
		Ctrl->C.info.cpt = true;

	if (Ctrl->A.info.interval > 0.0 && (!Ctrl->C.info.file && Ctrl->C.info.interval == 0.0)) Ctrl->C.info.interval = Ctrl->A.info.interval;

	/* Check that the options selected are mutually consistent */

	n_errors += gmt_M_check_condition (GMT, !GMT->common.J.active && !Ctrl->D.active,
	                                 "Must specify a map projection with the -J option\n");
	n_errors += gmt_M_check_condition (GMT, !GMT->common.R.active[RSET] && !Ctrl->D.active, "Must specify a region with the -R option\n");
#if 0
	n_errors += gmt_M_check_condition (GMT, !Ctrl->C.info.file && Ctrl->C.info.interval <= 0.0 && gmt_M_is_dnan (Ctrl->C.info.single_cont) && gmt_M_is_dnan (Ctrl->A.info.single_cont),
	                                 "Option -C: Must specify contour interval, file name with levels, or CPT\n");
#endif
	n_errors += gmt_M_check_condition (GMT, !Ctrl->D.active && !Ctrl->E.active && !(Ctrl->W.active || Ctrl->I.active),
	                                 "Must specify one of -W or -I\n");
	n_errors += gmt_M_check_condition (GMT, Ctrl->D.active && (Ctrl->I.active || Ctrl->L.active || Ctrl->N.active || Ctrl->G.active || Ctrl->W.active),
	                                 "Cannot use -G, -I, -L, -N, -W with -D\n");
	n_errors += gmt_M_check_condition (GMT, Ctrl->I.active && !Ctrl->C.info.file, "Option -I: Must specify a color palette table via -C\n");
	n_errors += gmt_M_check_condition (GMT, Ctrl->W.cptmode && !Ctrl->C.info.cpt, "Option -W: Modifier +c only valid if -C sets a CPT\n");
	n_errors += gmt_check_binary_io (GMT, 3);
	n_errors += gmt_M_check_condition (GMT, Ctrl->E.binary && !GMT->common.b.active[GMT_IN], "Option -E: Cannot imply binary node input if main input is not also binary (see -bi)\n");

	return (n_errors ? GMT_PARSE_ERROR : GMT_NOERROR);
}

#define bailout(code) {gmt_M_free_options (mode); return (code);}
#define Return(code) {Free_Ctrl (GMT, Ctrl); gmt_end_module (GMT, GMT_cpy); bailout (code);}

EXTERN_MSC int GMT_pscontour (void *V_API, int mode, void *args) {
	int add, error = 0;
	bool two_only = false, make_plot, skip = false, convert, get_contours, is_closed;
	bool use_contour = true, skip_points, skip_triangles;

	unsigned int pscontour_sum, m, n, nx, k2, k3, node1, node2, c, cont_counts[2] = {0, 0};
	unsigned int label_mode = 0, last_entry, last_exit, fmt[3] = {0, 0, 0}, n_skipped, n_out, n_cont_attempts = 0;
	unsigned int i, low, high, n_contours = 0, n_tables = 0, tbl_scl = 0, io_mode = 0, tbl, id, *vert = NULL, *cind = NULL;

	size_t n_alloc, n_save = 0, n_save_alloc = 0, *n_seg_alloc = NULL, c_alloc = 0;

	uint64_t k, np, ij, *n_seg = NULL;

	int *ind = NULL;	/* Must remain int due to triangle */

	double xx[3], yy[3], zz[3], xout[5], yout[5], xyz[2][3], rgb[4], z_range, small;
	double *xc = NULL, *yc = NULL, *zc = NULL, *x = NULL, *y = NULL, *z = NULL;
	double current_contour = -DBL_MAX, c_length, *in = NULL, *xp = NULL, *yp = NULL;

	char cont_label[GMT_LEN256] = {""}, format[GMT_LEN256] = {""};
	char *tri_algorithm[2] = {"Watson", "Shewchuk"};

	struct GMT_CONTOUR_INFO *cont = NULL;
	struct PSCONTOUR *line = NULL;
	struct GMT_DATASET *D = NULL;
	struct GMT_DATASEGMENT *S = NULL;
	struct GMT_DATATABLE_HIDDEN *TH = NULL;
	struct GMT_DATASEGMENT_HIDDEN *SH = NULL;
	struct GMT_PALETTE *P = NULL;
	struct GMT_RECORD *In = NULL;
	struct PSCONTOUR_SAVE *save = NULL;
	struct PSCONTOUR_CTRL *Ctrl = NULL;
	struct GMT_CTRL *GMT = NULL, *GMT_cpy = NULL;		/* General GMT internal parameters */
	struct GMT_OPTION *options = NULL, *opt = NULL;
	struct PSL_CTRL *PSL = NULL;		/* General PSL internal parameters */
	struct GMTAPI_CTRL *API = gmt_get_api_ptr (V_API);	/* Cast from void to GMTAPI_CTRL pointer */

	/*----------------------- Standard module initialization and parsing ----------------------*/

	if (API == NULL) return (GMT_NOT_A_SESSION);
	if (mode == GMT_MODULE_PURPOSE) return (usage (API, GMT_MODULE_PURPOSE));	/* Return the purpose of program */
	options = GMT_Create_Options (API, mode, args);	if (API->error) return (API->error);	/* Set or get option list */

	if ((error = gmt_report_usage (API, options, 0, usage)) != GMT_NOERROR) bailout (error);	/* Give usage if requested */

	/* Parse the command-line arguments; return if errors are encountered */

	if ((GMT = gmt_init_module (API, THIS_MODULE_LIB, THIS_MODULE_CLASSIC_NAME, THIS_MODULE_KEYS, THIS_MODULE_NEEDS, module_kw, &options, &GMT_cpy)) == NULL) bailout (API->error); /* Save current state */
	/* Must intercept any old-style -Eaz/el here and change it to -p */
	if ((opt = GMT_Find_Option (API, 'E', options)) && gmt_M_compat_check (GMT, 4)) {	/* Got -E, check if given a file */
		if (gmt_access (GMT, opt->arg, F_OK)) {	/* Argument not a file we can open, so under compat mode we assume we got -Eaz/el */
			GMT_Report (API, GMT_MSG_COMPAT, "Option -E<az/el> is deprecated; use -p instead.\n");
			opt->option = 'p';
		}
	}
	if (GMT_Parse_Common (API, THIS_MODULE_OPTIONS, options)) Return (API->error);
	Ctrl = New_Ctrl (GMT);	/* Allocate and initialize a new control structure */
	if ((error = parse (GMT, Ctrl, options)) != 0) Return (error);

	/*---------------------------- This is the pscontour main code ----------------------------*/

	GMT_Report (API, GMT_MSG_INFORMATION, "Processing input table data\n");
	if (Ctrl->D.active) {
		GMT_Report (API, GMT_MSG_INFORMATION, "With -D, no plotting will take place\n");
		if (!Ctrl->D.file) GMT_Report (API, GMT_MSG_INFORMATION, "Contours will be written to standard output\n");
	}
	if ((error = GMT_Set_Columns (API, GMT_IN, 3, GMT_COL_FIX_NO_TEXT)) != GMT_NOERROR) {
		Return (error);
	}
	if (GMT_Init_IO (API, GMT_IS_DATASET, GMT_IS_POINT, GMT_IN, GMT_ADD_DEFAULT, 0, options) != GMT_NOERROR) {	/* Register data input */
		Return (API->error);
	}
	if (GMT_Begin_IO (API, GMT_IS_DATASET, GMT_IN, GMT_HEADER_ON) != GMT_NOERROR) {	/* Enables data input and sets access mode */
		Return (API->error);
	}

	if (Ctrl->C.info.cpt) {	/* Presumably got a CPT; read it here so we can crash if no-such-file before we process input data */
		if ((P = GMT_Read_Data (API, GMT_IS_PALETTE, GMT_IS_FILE, GMT_IS_NONE, GMT_READ_NORMAL, NULL, Ctrl->C.info.file, NULL)) == NULL) {
			Return (API->error);
		}
		if (Ctrl->I.active && P->is_continuous) {
			GMT_Report (API, GMT_MSG_ERROR, "-I option requires constant color between contours!\n");
			Return (GMT_NOERROR);
		}
		if (P->categorical) {
			GMT_Report (API, GMT_MSG_ERROR, "Categorical data (as implied by CPT) do not have contours.  Check plot.\n");
		}
	}
	make_plot = !Ctrl->D.active;	/* Turn off plotting if -D was used */
	convert = (make_plot || (GMT->common.R.active[RSET] && GMT->common.J.active));
	get_contours = (Ctrl->D.active || Ctrl->W.active);

	if (GMT->common.J.active && gmt_map_setup (GMT, GMT->common.R.wesn)) Return (GMT_PROJECTION_ERROR);

	n_alloc = GMT_INITIAL_MEM_ROW_ALLOC;
	x = gmt_M_memory (GMT, NULL, n_alloc, double);
	y = gmt_M_memory (GMT, NULL, n_alloc, double);
	z = gmt_M_memory (GMT, NULL, n_alloc, double);

	xyz[0][GMT_Z] = DBL_MAX;	xyz[1][GMT_Z] = -DBL_MAX;
	n = 0;
	skip_points = (Ctrl->S.active && Ctrl->S.mode == 0);
	skip_triangles = (Ctrl->S.active && Ctrl->S.mode == 1);

	do {	/* Keep returning records until we reach EOF */
		if ((In = GMT_Get_Record (API, GMT_READ_DATA, NULL)) == NULL) {	/* Read next record, get NULL if special case */
			if (gmt_M_rec_is_error (GMT)) { 	/* Bail if there are any read errors */
				gmt_M_free (GMT, x);	gmt_M_free (GMT, y);	gmt_M_free (GMT, z);
				Return (GMT_RUNTIME_ERROR);
			}
			else if (gmt_M_rec_is_eof (GMT)) 		/* Reached end of file */
				break;
			continue;	/* Go back and read the next record */
		}
		if (In->data == NULL) {
			gmt_quit_bad_record (API, In);
			gmt_M_free (GMT, x);	gmt_M_free (GMT, y);	gmt_M_free (GMT, z);
			Return (API->error);
		}

		/* Data record to process */
		in = In->data;	/* Only need to process numerical part here */

		if (skip_points) {	/* Must check if points are inside plot region */
			gmt_map_outside (GMT, in[GMT_X], in[GMT_Y]);
			skip = (abs (GMT->current.map.this_x_status) > 1 || abs (GMT->current.map.this_y_status) > 1);
		}

		if (!(skip || gmt_M_is_dnan (in[GMT_Z]))) {	/* Unless outside or z = NaN */

			x[n] = in[GMT_X];
			y[n] = in[GMT_Y];
			z[n] = in[GMT_Z];
			if (z[n] < xyz[0][GMT_Z]) {	/* New minimum */
				xyz[0][GMT_X] = x[n];
				xyz[0][GMT_Y] = y[n];
				xyz[0][GMT_Z] = z[n];
			}
			if (z[n] > xyz[1][GMT_Z]) {	/* New maximum */
				xyz[1][GMT_X] = x[n];
				xyz[1][GMT_Y] = y[n];
				xyz[1][GMT_Z] = z[n];
			}
			n++;

			if (n == n_alloc) {
				n_alloc <<= 1;
				x = gmt_M_memory (GMT, x, n_alloc, double);
				y = gmt_M_memory (GMT, y, n_alloc, double);
				z = gmt_M_memory (GMT, z, n_alloc, double);
			}
			if (n == INT_MAX) {
				GMT_Report (API, GMT_MSG_ERROR, "Cannot triangulate more than %d points\n", INT_MAX);
				gmt_M_free (GMT, x);
				gmt_M_free (GMT, y);
				gmt_M_free (GMT, z);
				Return (GMT_RUNTIME_ERROR);
			}
		}
	} while (true);

	x = gmt_M_memory (GMT, x, n, double);
	y = gmt_M_memory (GMT, y, n, double);
	z = gmt_M_memory (GMT, z, n, double);

	if (n == 0) {
		GMT_Report (API, GMT_MSG_ERROR, "No data points given - so no triangulation can take effect\n");
		Return (GMT_RUNTIME_ERROR);
	}

	if (make_plot && gmt_contlabel_prep (GMT, &Ctrl->contour, xyz)) Return (GMT_RUNTIME_ERROR);	/* Prep for crossing lines, if any */

	/* Map transform */

	if (convert) for (i = 0; i < n; i++) gmt_geo_to_xy (GMT, x[i], y[i], &x[i], &y[i]);

	if (Ctrl->E.active) {	/* Read precalculated triangulation indices */
		int64_t s_np;	/* Need a signed 64-bit integer here */
		if ((s_np = gmt_read_triangulation (GMT, 'E', Ctrl->E.file, Ctrl->E.binary, n, &ind)) == GMT_NOTSET) {
			GMT_Report (API, GMT_MSG_ERROR, "Error reading triangulation indices from file %s\n", Ctrl->E.file);
			Return (GMT_RUNTIME_ERROR);
		}
		np = (uint64_t) s_np;	/* Set number of points as unsigned 64-bit int */	
	}
	else {	/* Do our own Delaunay triangulation */
		np = gmt_delaunay (GMT, x, y, n, &ind);
		GMT_Report (API, GMT_MSG_INFORMATION, "Obtained %d indices triplets via Delauney triangulation [%s].\n",
		            np, tri_algorithm[GMT->current.setting.triangulate]);
	}

	if (GMT_End_IO (API, GMT_IN, 0) != GMT_NOERROR) {	/* Disables further data input */
		if (Ctrl->E.active) gmt_M_free (GMT, ind);
		else gmt_delaunay_free (GMT, &ind);
		Return (API->error);
	}

	/* Determine if some triangles are outside the region and should be removed entirely */

	if (skip_triangles) {	/* Must check if triangles are outside plot region */
		for (k = i = n_skipped = 0; i < np; i++) {	/* For all triangles */
			k2 = (unsigned int)k;
			for (k3 = n_out = 0; k3 < 3; k3++, k++) {
				if (gmt_cart_outside (GMT, x[ind[k]], y[ind[k]])) {
					n_out++;	/* Count how many vertices are outside */
				}
			}
			if (n_out == 3) {
				ind[k2] = -1;	/* Flag so no longer to be used */
				n_skipped++;
			}
		}
		if (n_skipped) GMT_Report (API, GMT_MSG_WARNING, "Skipped %u triangles whose vertices are all outside the domain.\n", n_skipped);
	}

	if (Ctrl->C.info.cpt) {	/* We already read the CPT */
		/* Set up which contours to draw based on the CPT slices and their attributes */
		cont = gmt_M_memory (GMT, NULL, P->n_colors + 1, struct GMT_CONTOUR_INFO);
		for (i = c = 0; i < P->n_colors; i++) {
			if (P->data[i].skip) continue;
			if (Ctrl->Q.zero && gmt_M_is_zero (P->data[i].z_low)) continue;	/* Skip zero-contour */
			cont[c].val = P->data[i].z_low;
			if (Ctrl->A.info.mode)
				cont[c].type = 'C';
			else if (P->data[i].annot)
				cont[c].type = 'A';
			else
				cont[c].type = (Ctrl->contour.annot) ? 'A' : 'C';
			cont[c].type = (P->data[i].annot && !Ctrl->A.info.mode) ? 'A' : 'C';
			cont[c].angle = (Ctrl->contour.angle_type == GMT_ANGLE_LINE_FIXED) ? Ctrl->contour.label_angle : GMT->session.d_NaN;
			cont[c].do_tick = Ctrl->T.active;
			GMT_Report (API, GMT_MSG_DEBUG, "Contour slice %d: Value = %g type = %c angle = %g\n", c, cont[c].val, cont[c].type, cont[c].angle);
			c++;
		}
		if (Ctrl->Q.zero && !gmt_M_is_zero (P->data[P->n_colors-1].z_high)) {
			cont[c].val = P->data[P->n_colors-1].z_high;
			if (Ctrl->A.info.mode)
				cont[c].type = 'C';
			else if (P->data[P->n_colors-1].annot & 2)
				cont[c].type = 'A';
			else
				cont[c].type = (Ctrl->contour.annot) ? 'A' : 'C';
			cont[c].angle = (Ctrl->contour.angle_type == GMT_ANGLE_LINE_FIXED) ? Ctrl->contour.label_angle : GMT->session.d_NaN;
			cont[c].do_tick = Ctrl->T.active;
			c++;
		}
		GMT_Report (API, GMT_MSG_DEBUG, "Contour slice %d: Value = %g type = %c angle = %g\n", c, cont[c].val, cont[c].type, cont[c].angle);
		n_contours = c;
	}
	else if ((Ctrl->A.info.file && strchr (Ctrl->A.info.file, ',')) || (Ctrl->C.info.file && strchr (Ctrl->C.info.file, ','))) {	/* Got a comma-separated list of contours */
		uint64_t na = 0, nc = 0;
		double *za = NULL, *zc = NULL;
		if (Ctrl->A.info.file && strchr (Ctrl->A.info.file, ',') && (za = gmt_list_to_array (GMT, Ctrl->A.info.file, gmt_M_type (GMT, GMT_IN, GMT_Z), true, &na)) == NULL) {
			GMT_Report (API, GMT_MSG_ERROR, "Failure while parsing annotated contours from list %s\n", Ctrl->A.info.file);
			Return (GMT_RUNTIME_ERROR);
		}
		if (Ctrl->C.info.file && strchr (Ctrl->C.info.file, ',') && (zc = gmt_list_to_array (GMT, Ctrl->C.info.file, gmt_M_type (GMT, GMT_IN, GMT_Z), true, &nc)) == NULL) {
			GMT_Report (API, GMT_MSG_ERROR, "Failure while parsing regular contours from list %s\n", Ctrl->C.info.file);
			if (za) gmt_M_free (GMT, za);
			Return (GMT_RUNTIME_ERROR);
		}
		n_contours = na + nc;
		cont = gmt_M_memory (GMT, NULL, n_contours, struct GMT_CONTOUR_INFO);
		for (c = 0; c < nc; c++) {
			cont[c].type = 'C';
			cont[c].val = zc[c];
			cont[c].do_tick = Ctrl->T.active ? 1 : 0;
			cont[c].angle = (Ctrl->contour.angle_type == GMT_ANGLE_LINE_FIXED) ? Ctrl->contour.label_angle : GMT->session.d_NaN;
		}
		for (c = 0; c < na; c++) {
			cont[c+nc].type = 'A';
			cont[c+nc].val = za[c];
			cont[c+nc].do_tick = Ctrl->T.active ? 1 : 0;
			cont[c+nc].angle = (Ctrl->contour.angle_type == GMT_ANGLE_LINE_FIXED) ? Ctrl->contour.label_angle : GMT->session.d_NaN;
		}
		if (za) gmt_M_free (GMT, za);
		if (zc) gmt_M_free (GMT, zc);
	}
	else if (Ctrl->C.info.file) {	/* Read contour info from file with cval C|A [angle [pen]] records */
		if ((cont = gmt_get_contours_from_table (GMT, Ctrl->C.info.file, Ctrl->T.active, &Ctrl->contour.angle_type, &n_contours)) == NULL) Return (GMT_RUNTIME_ERROR);
	}
	else if (!gmt_M_is_dnan (Ctrl->C.info.single_cont) || !gmt_M_is_dnan (Ctrl->A.info.single_cont)) {	/* Plot one or two contours only */
		n_contours = 0;
		cont = gmt_M_malloc (GMT, cont, 2, &c_alloc, struct GMT_CONTOUR_INFO);
		if (!gmt_M_is_dnan (Ctrl->C.info.single_cont)) {
			cont[n_contours].type = 'C';
			cont[n_contours++].val = Ctrl->C.info.single_cont;
		}
		if (!gmt_M_is_dnan (Ctrl->A.info.single_cont)) {
			cont[n_contours].type = 'A';
			cont[n_contours].val = Ctrl->A.info.single_cont;
			cont[n_contours].do_tick = Ctrl->T.active;
			cont[n_contours].angle = (Ctrl->contour.angle_type == GMT_ANGLE_LINE_FIXED) ? Ctrl->contour.label_angle : GMT->session.d_NaN;
			n_contours++;
		}
	}
	else {	/* Set up contour intervals automatically from Ctrl->C.info.interval and Ctrl->A.info.interval */
		int ic;
		double min, max, aval, noise;
		if (!Ctrl->C.active && (!Ctrl->A.active || Ctrl->A.info.interval == 0.0)) {	/* Want automatic annotations */
			double x, range = xyz[1][GMT_Z] - xyz[0][GMT_Z];
			int nx;
			x = pow (10, floor (log10 (range)) - 1.0);
			nx = irint (range / x);
			if (nx > 40)
				x *= 5;
			else if (nx > 20)
				x *= 2;
			Ctrl->C.info.interval = x;
			Ctrl->A.info.interval = 2.0 * x;
			Ctrl->C.active  = Ctrl->A.active = Ctrl->contour.annot = true;
			GMT_Report (API, GMT_MSG_INFORMATION, "Auto-determined contour interval = %g and annotation interval = %g\n", Ctrl->C.info.interval, Ctrl->A.info.interval);
		}
		noise = GMT_CONV4_LIMIT * Ctrl->C.info.interval;
		min = floor (xyz[0][GMT_Z] / Ctrl->C.info.interval) * Ctrl->C.info.interval; if (min < xyz[0][GMT_Z]) min += Ctrl->C.info.interval;
		max = ceil  (xyz[1][GMT_Z] / Ctrl->C.info.interval) * Ctrl->C.info.interval; if (max > xyz[1][GMT_Z]) max -= Ctrl->C.info.interval;

		if (Ctrl->contour.annot) {	/* Want annotated contours */
			/* Determine the first annotated contour level */
			aval = floor (xyz[0][GMT_Z] / Ctrl->A.info.interval) * Ctrl->A.info.interval;
			if (aval < xyz[0][GMT_Z]) aval += Ctrl->A.info.interval;
		}
		else	/* No annotations, set aval outside range */
			aval = xyz[1][GMT_Z] + 1.0;
		for (ic = irint (min/Ctrl->C.info.interval), c = 0; ic <= irint (max/Ctrl->C.info.interval); ic++, c++) {
			if (c == c_alloc) cont = gmt_M_malloc (GMT, cont, c, &c_alloc, struct GMT_CONTOUR_INFO);
			gmt_M_memset (&cont[c], 1, struct GMT_CONTOUR_INFO);
			cont[c].val = ic * Ctrl->C.info.interval;
			if (Ctrl->Q.zero && gmt_M_is_zero (cont[c].val)) {	/* Skip zero-contour */
				c--;	/* Since gets incremented each time */
				continue;
			}
			if (Ctrl->contour.annot && (cont[c].val - aval) > noise) aval += Ctrl->A.info.interval;
			cont[c].type = (fabs (cont[c].val - aval) < noise) ? 'A' : 'C';
			cont[c].angle = (Ctrl->contour.angle_type == GMT_ANGLE_LINE_FIXED) ? Ctrl->contour.label_angle : GMT->session.d_NaN;
			cont[c].do_tick = Ctrl->T.active;
		}
		n_contours = c;
	}
	if (n_contours == 0) {
		GMT_Report (API, GMT_MSG_WARNING, "No contours found\n");
	}
	c_alloc = n_contours;
	cont = gmt_M_malloc (GMT, cont, 0, &c_alloc, struct GMT_CONTOUR_INFO);

	if (Ctrl->D.active) {
		uint64_t dim[GMT_DIM_SIZE] = {0, 0, 0, 3};
		if (!Ctrl->D.file || !strchr (Ctrl->D.file, '%')) {	/* No file given or filename without C-format specifiers means a single output file */
			io_mode = GMT_WRITE_SET;
			n_tables = 1;
		}
		else {	/* Must determine the kind of output organization */
			i = 0;
			while (Ctrl->D.file[i]) {
				if (Ctrl->D.file[i++] == '%') {	/* Start of format */
					while (Ctrl->D.file[i] && !strchr ("cdf", Ctrl->D.file[i])) i++;	/* Scan past any format modifiers, like in %7.4f */
					if (Ctrl->D.file[i] == 'c') fmt[0] = i;
					if (Ctrl->D.file[i] == 'd') fmt[1] = i;
					if (Ctrl->D.file[i] == 'f') fmt[2] = i;
					i++;
				}
			}
			n_tables = 1;
			if (fmt[2]) {	/* Want files with the contour level in the name */
				if (fmt[1])	/* f+d[+c]: Write segment files named after contour level and running numbers, with or without C|O modifier */
					io_mode = GMT_WRITE_SEGMENT;
				else {	/* f[+c]: Write one table with all segments for each contour level, possibly one each for C|O */
					io_mode = GMT_WRITE_TABLE;
					tbl_scl = (fmt[0]) ? 2 : 1;
					n_tables = n_contours * tbl_scl;
				}
			}
			else if (fmt[1])	/* d[+c]: Want individual files with running numbers only, with or without C|O modifier  */
				io_mode = GMT_WRITE_SEGMENT;
			else if (fmt[0]) {	/* c: Want two files: one for open and one for closed contours */
				io_mode = GMT_WRITE_TABLE;
				n_tables = 2;
				two_only = true;
			}
		}
		gmt_set_segmentheader (GMT, GMT_OUT, true);	/* Turn on segment headers on output */
		dim[GMT_TBL] = n_tables;
		if ((D = GMT_Create_Data (API, GMT_IS_DATASET, GMT_IS_LINE, 0, dim, NULL, NULL, 0, 0, NULL)) == NULL) {
			gmt_M_free (GMT, cont);
			Return (API->error);	/* An empty dataset */
		}
		n_seg_alloc = gmt_M_memory (GMT, NULL, n_tables, size_t);
		n_seg = gmt_M_memory (GMT, NULL, n_tables, uint64_t);
		if ((error = GMT_Set_Columns (API, GMT_OUT, 3, GMT_COL_FIX_NO_TEXT)) != GMT_NOERROR)
			Return (error);
	}

	if (make_plot) {
		if (Ctrl->contour.delay)	/* Signal that this program initiates clipping that will outlive this process */
			GMT->current.ps.nclip = (Ctrl->N.active) ? +1 : +2;
		if ((PSL = gmt_plotinit (GMT, options)) == NULL) {
			gmt_M_free (GMT, cont);
			Return (GMT_RUNTIME_ERROR);
		}
		gmt_plane_perspective (GMT, GMT->current.proj.z_project.view_plane, GMT->current.proj.z_level);
		gmt_set_basemap_orders (GMT, Ctrl->N.active ? GMT_BASEMAP_FRAME_BEFORE : GMT_BASEMAP_FRAME_AFTER, Ctrl->I.active ? GMT_BASEMAP_GRID_AFTER : GMT_BASEMAP_GRID_BEFORE, GMT_BASEMAP_ANNOT_BEFORE);
		gmt_plotcanvas (GMT);	/* Fill canvas if requested */
		gmt_map_basemap (GMT);	/* If delayed clipping the basemap must be done before clipping */
		if (!Ctrl->N.active) gmt_map_clip_on (GMT, GMT->session.no_rgb, 3);
		Ctrl->contour.line_pen = Ctrl->W.pen[PEN_CONT];
		if (GMT->common.l.active) {	/* Add one or two contour entries to the auto-legend entry under modern mode; examine which pen & label we place */
			char *p = NULL;
			struct GMT_LEGEND_ITEM copy;
			if (strchr ("|/", GMT->common.l.item.label[0])) {	/* Gave single label for contour pen since starting with | or / */
				gmt_M_memcpy (&copy, &(GMT->common.l.item), 1, struct GMT_LEGEND_ITEM);	/* Make an identical copy */
				gmt_strlshift (copy.label, 1U);	/* Remove the leading divider */
				gmt_add_legend_item (API, NULL, false, NULL, true, &(Ctrl->W.pen[PEN_CONT]), &copy, NULL);
			}
			else if ((p = strchr (GMT->common.l.item.label, '|')) || (p = strchr (GMT->common.l.item.label, '/'))) {	/* Got two titles */
				char q = p[0];	/* Get the divider character */
				gmt_M_memcpy (&copy, &(GMT->common.l.item), 1, struct GMT_LEGEND_ITEM);	/* Make an identical copy */
				p[0] = '\0';	/* Truncate the second contour label */
				gmt_add_legend_item (API, NULL, false, NULL, true, &(Ctrl->W.pen[PEN_ANNOT]), &(GMT->common.l.item), NULL);	/* Place the first annotated contour entry */
				p[0] = q;	/* Restore the label in the original -l setting */
				if (copy.draw & GMT_LEGEND_DRAW_D) copy.draw -= GMT_LEGEND_DRAW_D;	/* Only want to draw one horizontal line (if set), so remove for the 2nd entry */
				gmt_strlshift (copy.label, (size_t)(p - GMT->common.l.item.label)+1);	/* Remove the leading annotated contour label first */
				gmt_add_legend_item (API, NULL, false, NULL, true, &(Ctrl->W.pen[PEN_CONT]), &copy, NULL);	/* Place the second regular contour entry */
			}
			else if (Ctrl->A.active)	/* Got a single entry for annotated contours */
				gmt_add_legend_item (API, NULL, false, NULL, true, &(Ctrl->W.pen[PEN_ANNOT]), &(GMT->common.l.item), NULL);
			else	/* Got a single entry for plain contours */
				gmt_add_legend_item (API, NULL, false, NULL, true, &(Ctrl->W.pen[PEN_CONT]), &(GMT->common.l.item), NULL);
		}
	}

	if (Ctrl->L.active) {	/* Draw triangular mesh */

		PSL_command (GMT->PSL, "V\n");
		gmt_setpen (GMT, &Ctrl->L.pen);

		for (k = i = 0; i < np; i++) {	/* For all triangles */
			if (ind[k] < 0) { k += 3; continue; }	/* Skip triangles that are fully outside */
			xx[0] = x[ind[k]];	yy[0] = y[ind[k++]];
			xx[1] = x[ind[k]];	yy[1] = y[ind[k++]];
			xx[2] = x[ind[k]];	yy[2] = y[ind[k++]];

			PSL_plotline (PSL, xx, yy, 3, PSL_MOVE|PSL_STROKE|PSL_CLOSE);
		}
		PSL_command (GMT->PSL, "U\n");
	}

	/* Get PSCONTOUR structs */

	if (get_contours) {
		line = gmt_M_memory (GMT, NULL, n_contours, struct PSCONTOUR);
		for (i = 0; i < n_contours; i++) {
			line[i].n_alloc = GMT_SMALL_CHUNK;
			line[i].L = gmt_M_memory (GMT, NULL, GMT_SMALL_CHUNK, struct PSCONTOUR_LINE);
		}
	}

	z_range = xyz[1][GMT_Z] - xyz[0][GMT_Z];
	small = MIN (Ctrl->C.info.interval, z_range) * 1.0e-6;	/* Our float noise threshold */

	for (ij = i = 0; n_contours && i < np; i++, ij += 3) {	/* For all triangles */

		if (ind[ij] < 0) continue;	/* Skip triangles that are fully outside */

		k = ij;
		xx[0] = x[ind[k]];	yy[0] = y[ind[k]];	zz[0] = z[ind[k++]];
		xx[1] = x[ind[k]];	yy[1] = y[ind[k]];	zz[1] = z[ind[k++]];
		xx[2] = x[ind[k]];	yy[2] = y[ind[k]];	zz[2] = z[ind[k]];

		nx = pscontour_get_triangle_crossings (GMT, cont, n_contours, x, y, z, &ind[ij], small, &xc, &yc, &zc, &vert, &cind);

		if (Ctrl->I.active) {	/* Must color the triangle slices according to CPT */

			if (nx == 0) {	/* No contours go through - easy, but must check for NaNs */
				int kzz;
				double zzz;
				for (k = kzz = 0, zzz = 0.0; k < 3; k++) {
					if (gmt_M_is_dnan (zz[k])) continue;
					zzz += zz[k];
					kzz++;
				}
				if (kzz) pscontour_paint_it (GMT, PSL, P, xx, yy, 3, zzz / kzz);
			}
			else {	/* Must paint all those slices separately */

				/* Find vertices with the lowest and highest values */

				for (k = 1, low = high = 0; k < 3; k++) {
					if (zz[k] < zz[low])   low = (unsigned int)k;
					if (zz[k] > zz[high]) high = (unsigned int)k;
				}

				/* Paint the piece delimited by the low node and the first contour */

				xout[0] = xx[low];	yout[0] = yy[low];
				node1 = get_node_index (vert[0], vert[1]);	/* Find single vertex opposing this contour segment */
				if (node1 == low) {	/* Contour and low node make up a triangle */
					xout[1] = xc[0];	yout[1] = yc[0];
					xout[2] = xc[1];	yout[2] = yc[1];
					m = 3;
				}
				else {	/* Need the other two vertices to form a 4-sided polygon */
					node2 = get_other_node (node1, low);	/* The other node needed */
					xout[1] = xx[node2];	yout[1] = yy[node2];
					if (low == vert[0] || node2 == vert[1]) {	/* Add segment in opposite order */
						xout[2] = xc[1];	yout[2] = yc[1];
						xout[3] = xc[0];	yout[3] = yc[0];
					}
					else  {	/* Add in regular order */
						xout[2] = xc[0];	yout[2] = yc[0];
						xout[3] = xc[1];	yout[3] = yc[1];
					}
					m = 4;
				}
				pscontour_paint_it (GMT, PSL, P, xout, yout, m, 0.5 * (zz[low] + zc[1]));	/* z is contour value */

				/* Then loop over contours and paint the part between contours */

				for (k = 1, k2 = 2, k3 = 3; k < nx; k++, k2 += 2, k3 += 2) {
					xout[0] = xc[k2-2];	yout[0] = yc[k2-2];
					xout[1] = xc[k3-2];	yout[1] = yc[k3-2];
					m = 2;
					last_entry = vert[k2-2];
					last_exit  = vert[k3-2];
					if (last_exit == vert[k2]) {
						xout[m] = xc[k2];	yout[m] = yc[k2];	m++;
						xout[m] = xc[k3];	yout[m] = yc[k3];	m++;
						if (vert[k3] != last_entry) {	/* Need to add an intervening corner */
							node1 = get_node_index (last_entry, vert[k3]);	/* Find corner id */
							xout[m] = xx[node1];	yout[m] = yy[node1];	m++;
						}
					}
					else if (last_exit == vert[k3]) {
						xout[m] = xc[k3];	yout[m] = yc[k3];	m++;
						xout[m] = xc[k2];	yout[m] = yc[k2];	m++;
						if (vert[k2] != last_entry) {	/* Need to add an intervening corner */
							node1 = get_node_index (last_entry, vert[k2]);	/* Find corner id */
							xout[m] = xx[node1];	yout[m] = yy[node1];	m++;
						}
					}
					else if (last_entry == vert[k2]) {
						node1 = get_node_index (last_exit, vert[k3]);	/* Find corner id */
						xout[m] = xx[node1];	yout[m] = yy[node1];	m++;
						xout[m] = xc[k3];	yout[m] = yc[k3];	m++;
						xout[m] = xc[k2];	yout[m] = yc[k2];	m++;
					}
					else {
						node1 = get_node_index (last_exit, vert[k2]);	/* Find corner id */
						xout[m] = xx[node1];	yout[m] = yy[node1];	m++;
						xout[m] = xc[k2];	yout[m] = yc[k2];	m++;
						xout[m] = xc[k3];	yout[m] = yc[k3];	m++;
					}
					pscontour_paint_it (GMT, PSL, P, xout, yout, m, 0.5 * (zc[k2]+zc[k2-2]));
				}

				/* Add the last piece between last contour and high node */

				k2 -= 2;	k3 -= 2;
				xout[0] = xx[high];	yout[0] = yy[high];
				node1 = get_node_index (vert[k2], vert[k3]);	/* Find corner id */
				if (node1 == high) {	/* Cut off a triangular piece */
					xout[1] = xc[k2];	yout[1] = yc[k2];
					xout[2] = xc[k3];	yout[2] = yc[k3];
					m = 3;
				}
				else {	/* Need a 4-sided polygon */
					node2 = get_other_node (node1, high);	/* The other node needed */
					xout[1] = xx[node2];	yout[1] = yy[node2];
					if (high == vert[0] || node2 == vert[1]) {	/* On same side, start here */
						xout[2] = xc[k3];	yout[2] = yc[k3];
						xout[3] = xc[k2];	yout[3] = yc[k2];
					}
					else  {	/* On same side, start here */
						xout[2] = xc[k2];	yout[2] = yc[k2];
						xout[3] = xc[k3];	yout[3] = yc[k3];
					}
					m = 4;
				}
				pscontour_paint_it (GMT, PSL, P, xout, yout, m, 0.5 * (zz[high] + zc[k2]));	/* z is contour value */
			}
		}

		if (get_contours && nx > 0) {	/* Save contour line segments L for later */
			for (k = k2 = 0; k < nx; k++) {
				c = cind[k];
				m = line[c].nl;
				line[c].L[m].x0 = xc[k2];
				line[c].L[m].y0 = yc[k2++];
				line[c].L[m].x1 = xc[k2];
				line[c].L[m].y1 = yc[k2++];
				m++;
				if (m >= line[c].n_alloc) {
					line[c].n_alloc <<= 1;
					line[c].L = gmt_M_memory (GMT, line[c].L, line[c].n_alloc, struct PSCONTOUR_LINE);
				}
				line[c].nl = m;
			}
		}

		if (nx > 0) {
			gmt_M_free (GMT, xc);
			gmt_M_free (GMT, yc);
			gmt_M_free (GMT, zc);
			gmt_M_free (GMT, vert);
			gmt_M_free (GMT, cind);
		}
	}

	/* Draw or dump contours */

	if (Ctrl->Q.active && Ctrl->Q.unit && (strchr (GMT_LEN_UNITS, Ctrl->Q.unit) || Ctrl->Q.unit == 'X')) {	/* Need to compute distances in map units */
		if (gmt_init_distaz (GMT, Ctrl->Q.unit, Ctrl->Q.mode, GMT_MAP_DIST) == GMT_NOT_A_VALID_TYPE)
			Return (GMT_NOT_A_VALID_TYPE);
	}

	if (get_contours) {
		bool use_it;
		struct PSCONTOUR_CHAIN *head_c = NULL, *last_c = NULL, *this_c = NULL;
		struct PSCONTOUR_PT *p = NULL, *q = NULL;

		if (Ctrl->contour.half_width == 5) Ctrl->contour.half_width = 0;	/* Since contours are straight line segments we override the default */

		for (c = 0; c < n_contours; c++) {	/* For all selected contour levels */

			if (line[c].nl == 0) {	/* No contours at this level */
				gmt_M_free (GMT, line[c].L);
				continue;
			}

			GMT_Report (API, GMT_MSG_INFORMATION, "Tracing the %g contour\n", cont[c].val);

			id = (cont[c].type == 'A' || cont[c].type == 'a') ? PEN_ANNOT : PEN_CONT;

			if (cont[c].penset)
				Ctrl->contour.line_pen = cont[c].pen;		/* Load contour-specific pen into contour structure */
			else
				Ctrl->contour.line_pen = Ctrl->W.pen[id];	/* Load current pen into contour structure */

			if (Ctrl->W.cpt_effect) {
				gmt_get_rgb_from_z (GMT, P, cont[c].val, rgb);
				if (Ctrl->W.cptmode & 1)	/* Override pen color according to CPT */
					gmt_M_rgb_copy (&Ctrl->contour.line_pen.rgb, rgb);
				if (Ctrl->W.cptmode & 2)	/* Override label color according to CPT */
					gmt_M_rgb_copy (&Ctrl->contour.font_label.fill.rgb, rgb);
			}
			else if ((Ctrl->contour.font_label.set & 1) == 0) /* Did not specify a font color; fault to pen color */
				gmt_M_rgb_copy (&Ctrl->contour.font_label.fill.rgb, Ctrl->contour.line_pen.rgb);

			head_c = last_c = gmt_M_memory (GMT, NULL, 1, struct PSCONTOUR_CHAIN);

			while (line[c].nl) {	/* Still more line segments at this contour level */
				/* Must hook all the segments into continuous contours. Start with first segment L */
				this_c = last_c->next = gmt_M_memory (GMT, NULL, 1, struct PSCONTOUR_CHAIN);
				k = 0;
				this_c->begin = gmt_M_memory (GMT, NULL, 1, struct PSCONTOUR_PT);
				this_c->end = gmt_M_memory (GMT, NULL, 1, struct PSCONTOUR_PT);
				this_c->begin->x = line[c].L[k].x0;
				this_c->begin->y = line[c].L[k].y0;
				this_c->end->x = line[c].L[k].x1;
				this_c->end->y = line[c].L[k].y1;
				this_c->begin->next = this_c->end;
				line[c].nl--;	/* Used one segment now */
				line[c].L[k] = line[c].L[line[c].nl];
				while (k < line[c].nl) {	/* As long as there are more */
					add = 0;
					if (fabs(line[c].L[k].x0 - this_c->begin->x) < GMT_CONV4_LIMIT && fabs(line[c].L[k].y0 - this_c->begin->y) < GMT_CONV4_LIMIT) {	/* L matches previous */
						p = gmt_M_memory (GMT, NULL, 1, struct PSCONTOUR_PT);
						p->x = line[c].L[k].x1;
						p->y = line[c].L[k].y1;
						p->next = this_c->begin;
						add = -1;
					}
					else if (fabs(line[c].L[k].x1 - this_c->begin->x) < GMT_CONV4_LIMIT && fabs(line[c].L[k].y1 - this_c->begin->y) < GMT_CONV4_LIMIT) {	/* L matches previous */
						p = gmt_M_memory (GMT, NULL, 1, struct PSCONTOUR_PT);
						p->x = line[c].L[k].x0;
						p->y = line[c].L[k].y0;
						p->next = this_c->begin;
						add = -1;
					}
					else if (fabs(line[c].L[k].x0 - this_c->end->x) < GMT_CONV4_LIMIT && fabs(line[c].L[k].y0 - this_c->end->y) < GMT_CONV4_LIMIT) {	/* L matches previous */
						p = gmt_M_memory (GMT, NULL, 1, struct PSCONTOUR_PT);
						p->x = line[c].L[k].x1;
						p->y = line[c].L[k].y1;
						this_c->end->next = p;
						add = 1;
					}
					else if (fabs(line[c].L[k].x1 - this_c->end->x) < GMT_CONV4_LIMIT && fabs(line[c].L[k].y1 - this_c->end->y) < GMT_CONV4_LIMIT) {	/* L matches previous */
						p = gmt_M_memory (GMT, NULL, 1, struct PSCONTOUR_PT);
						p->x = line[c].L[k].x0;
						p->y = line[c].L[k].y0;
						this_c->end->next = p;
						add = 1;
					}
					if (add) {	/* Got one, check if we must reverse it */
						if (add == -1)
							this_c->begin = p;
						else if (add == 1)
							this_c->end = p;
						line[c].nl--;
						line[c].L[k] = line[c].L[line[c].nl];
						k = 0;
					}
					else	/* No match, go to next */
						k++;
				}
				last_c = this_c;
			}
			gmt_M_free (GMT, line[c].L);	/* Done with temporary contour segment array for this level */

			/* Now, turn this linked list of segment pointers into x,y arrays */

			this_c = head_c->next;
			while (this_c) {
				p = this_c->begin;
				m = 1;
				while ((p = p->next) != NULL) m++;	/* Find total number of points in this linked list */
				use_it = (m >= Ctrl->Q.min);	/* True if we will use this line */

				if (use_it) {	/* Need arrays to hold the coordinates */
					xp = gmt_M_memory (GMT, NULL, m, double);
					yp = gmt_M_memory (GMT, NULL, m, double);
					m = 0;
				}
				p = this_c->begin;	/* Start over and maybe get the points this time */
				while ((q = p) != NULL) {	/* More points to add */
					if (use_it) {xp[m] = p->x; yp[m++] = p->y;}
					p = p->next;
					gmt_M_free (GMT, q);	/* Free linked list as we go along */
				}
				last_c = this_c;
				this_c = this_c->next;
				gmt_M_free (GMT, last_c);	/* Free last item */
				if (!use_it) continue;	/* No, go to next */

				is_closed = (m > 2 && !gmt_polygon_is_open (GMT, xp, yp, m));

				if (Ctrl->Q.active) {	/* Avoid plotting short contours based on map length or point count */
					if (Ctrl->Q.unit) {	/* Need length of contour */
						c_length = gmt_line_length (GMT, xp, yp, m, Ctrl->Q.project);
						use_contour = (c_length >= Ctrl->Q.length);
					}
					else
						use_contour = (n >= Ctrl->Q.min);
				}
				if (!use_contour) continue;	/* No, go to next */

				if (current_contour != cont[c].val) {
					if (make_plot) {
						if (Ctrl->W.cptmode & 1) {	/* Override pen color according to CPT */
							gmt_get_rgb_from_z (GMT, P, cont[c].val, rgb);
							PSL_setcolor (PSL, rgb, PSL_IS_STROKE);
							gmt_M_rgb_copy (&Ctrl->contour.line_pen.rgb, rgb);
						}
						if ((Ctrl->W.cptmode & 2) && Ctrl->contour.curved_text) {	/* Override label color according to CPT */
							gmt_M_rgb_copy (&Ctrl->contour.font_label.fill.rgb, rgb);
						}
					}
					current_contour = cont[c].val;
				}

				if (make_plot && (cont[c].type == 'A' || cont[c].type == 'a')) {	/* Annotated contours */
					gmt_get_format (GMT, cont[c].val, Ctrl->contour.unit, NULL, format);
					sprintf (cont_label, format, cont[c].val);
				}
				if (Ctrl->D.active) {
					size_t count;
					unsigned int closed;
					if (convert) {	/* Must first apply inverse map transform */
						double *xtmp = NULL, *ytmp = NULL;
						xtmp = gmt_M_memory (GMT, NULL, m, double);
						ytmp = gmt_M_memory (GMT, NULL, m, double);
						for (count = 0; count < m; count++) gmt_xy_to_geo (GMT, &xtmp[count], &ytmp[count], xp[count], yp[count]);
						S = gmt_prepare_contour (GMT, xtmp, ytmp, m, cont[c].val);
						gmt_M_free (GMT, xtmp);
						gmt_M_free (GMT, ytmp);
					}
					else
						S = gmt_prepare_contour (GMT, xp, yp, m, cont[c].val);
					/* Select which table this segment should be added to */
					closed = (is_closed) ? 1 : 0;
					tbl = (io_mode == GMT_WRITE_TABLE) ? ((two_only) ? closed : tbl_scl * c) : 0;
					if (n_seg[tbl] == n_seg_alloc[tbl]) {
						size_t n_old_alloc = n_seg_alloc[tbl];
						D->table[tbl]->segment = gmt_M_memory (GMT, D->table[tbl]->segment, (n_seg_alloc[tbl] += GMT_SMALL_CHUNK), struct GMT_DATASEGMENT *);
						gmt_M_memset (&(D->table[tbl]->segment[n_old_alloc]), n_seg_alloc[tbl] - n_old_alloc, struct GMT_DATASEGMENT *);	/* Set to NULL */
					}
					D->table[tbl]->segment[n_seg[tbl]++] = S;
					D->table[tbl]->n_segments++;	D->n_segments++;
					D->table[tbl]->n_records += m;	D->n_records += m;
					/* Generate a file name and increment cont_counts, if relevant */
					TH = gmt_get_DT_hidden (D->table[tbl]);
					if (io_mode == GMT_WRITE_TABLE && !TH->file[GMT_OUT])
						TH->file[GMT_OUT] = gmt_make_filename (GMT, Ctrl->D.file, fmt, cont[c].val, is_closed, cont_counts);
					else if (io_mode == GMT_WRITE_SEGMENT) {
						SH = gmt_get_DS_hidden (S);
						SH->file[GMT_OUT] = gmt_make_filename (GMT, Ctrl->D.file, fmt, cont[c].val, is_closed, cont_counts);
					}
				}

				if (make_plot) {
					if (cont[c].do_tick && is_closed) {	/* Must store the entire contour for later processing */
						if (n_save == n_save_alloc) save = gmt_M_malloc (GMT, save, n_save, &n_save_alloc, struct PSCONTOUR_SAVE);
						n_alloc = 0;
						gmt_M_memset (&save[n_save], 1, struct PSCONTOUR_SAVE);
						gmt_M_malloc2 (GMT, save[n_save].x, save[n_save].y, m, &n_alloc, double);
						gmt_M_memcpy (save[n_save].x, xp, m, double);
						gmt_M_memcpy (save[n_save].y, yp, m, double);
						save[n_save].n = m;
						gmt_M_memcpy (&save[n_save].pen,  &Ctrl->contour.line_pen,   1, struct GMT_PEN);
						gmt_M_memcpy (&save[n_save].font, &Ctrl->contour.font_label, 1, struct GMT_FONT);
						save[n_save].do_it = true;
						save[n_save].cval = cont[c].val;
						n_save++;
					}
					gmt_hold_contour (GMT, &xp, &yp, m, cont[c].val, cont_label, cont[c].type, cont[c].angle, is_closed, true, &Ctrl->contour);
					n_cont_attempts++;

				}

				gmt_M_free (GMT, xp);
				gmt_M_free (GMT, yp);
			}
			gmt_M_free (GMT, head_c);
		}
		if (make_plot) label_mode |= 1;		/* Would want to plot ticks and labels if -T is set */
		if (Ctrl->contour.save_labels) {	/* Want to save the contour label locations (lon, lat, angle, label) */
			label_mode |= 2;
			if ((error = gmt_contlabel_save_begin (GMT, &Ctrl->contour)) != 0) {
				gmt_M_free (GMT, cont);
				Return (error);
			}
		}
		if (Ctrl->T.active && n_save) {	/* Finally sort and plot ticked innermost contours and plot/save L|H labels */
			size_t kk;
			save = gmt_M_malloc (GMT, save, 0, &n_save, struct PSCONTOUR_SAVE);

			pscontour_sort_and_plot_ticks (GMT, PSL, save, n_save, x, y, z, n, &Ctrl->T.info, label_mode, Ctrl->contour.Out);
			for (kk = 0; kk < n_save; kk++) {
				gmt_M_free (GMT, save[kk].x);
				gmt_M_free (GMT, save[kk].y);
			}
			gmt_M_free (GMT, save);
		}
		if (make_plot) {
			if (get_contours && n_cont_attempts == 0) GMT_Report (API, GMT_MSG_INFORMATION, "No contours drawn, check your -A and -C settings?\n");
			gmt_contlabel_plot (GMT, &Ctrl->contour);
			gmt_contlabel_free (GMT, &Ctrl->contour);
		}
		if (Ctrl->contour.save_labels) {	/* Close file with the contour label locations (lon, lat, angle, label) */
			if ((error = gmt_contlabel_save_end (GMT, &Ctrl->contour)) != 0) Return (error);
		}
	}

	if (Ctrl->D.active) {	/* Write the contour line output file(s) */
		for (tbl = 0; tbl < D->n_tables; tbl++) D->table[tbl]->segment = gmt_M_memory (GMT, D->table[tbl]->segment, n_seg[tbl], struct GMT_DATASEGMENT *);
		if (GMT_Write_Data (API, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_LINE, io_mode, NULL, Ctrl->D.file, D) != GMT_NOERROR) {
			Return (API->error);
		}
		gmt_M_free (GMT, n_seg_alloc);
		gmt_M_free (GMT, n_seg);
	}

	if (make_plot) {
		if (!(Ctrl->N.active || Ctrl->contour.delay)) gmt_map_clip_off (GMT);
		gmt_map_basemap (GMT);	/* If delayed clipping the basemap is done before plotting, else here */
		gmt_plane_perspective (GMT, -1, 0.0);
		gmt_plotend (GMT);
	}

	gmt_M_free (GMT, x);
	gmt_M_free (GMT, y);
	gmt_M_free (GMT, z);
	gmt_M_free (GMT, cont);
	gmt_M_free (GMT, line);
	if (Ctrl->E.active)
		gmt_M_free (GMT, ind);	/* Allocated above by gmt_M_memory */
	else
		gmt_delaunay_free (GMT, &ind);

	Return (GMT_NOERROR);
}

EXTERN_MSC int GMT_contour (void *V_API, int mode, void *args) {
	/* This is the GMT6 modern mode name */
	struct GMTAPI_CTRL *API = gmt_get_api_ptr (V_API);	/* Cast from void to GMTAPI_CTRL pointer */
	if (API->GMT->current.setting.run_mode == GMT_CLASSIC && !API->usage) {
		GMT_Report (API, GMT_MSG_ERROR, "Shared GMT module not found: contour\n");
		return (GMT_NOT_A_VALID_MODULE);
	}
	return GMT_pscontour (V_API, mode, args);
}
