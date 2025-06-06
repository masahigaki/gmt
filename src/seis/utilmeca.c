/*--------------------------------------------------------------------
 *
 *	Copyright (c) 2013-2025 by the GMT Team (https://www.generic-mapping-tools.org/team.html)
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
/*
 *	Copyright (c) 1996-2012 by G. Patau
 *	Donated to the GMT project by G. Patau upon her retirement from IGPG
 *--------------------------------------------------------------------*/

#include "gmt_dev.h"	/* to have gmt dev environment */
#include "meca.h"
#include "utilmeca.h"

#define squared(x) ((x) * (x))

/************************************************************************/
void meca_get_trans (struct GMT_CTRL *GMT, double slon, double slat, double *t11, double *t12, double *t21, double *t22) {
	/* determine local transformation between (lon,lat) and (x,y) */
	/* return this in the 2 x 2 matrix t */
	/* this is useful for drawing velocity vectors in X,Y coordinates */
	/* even on a map which is not a Cartesian projection */

 	/* Kurt Feigl, from code by T. Herring */

	/* INPUT */
	/*   slat        - latitude, in degrees  */
	/*   slon        - longitude in degrees  */

	/* OUTPUT (returned) */
	/*   t11,t12,t21,t22 transformation matrix */
	/* COMMENT BY PW: Fails as provided if slat > 89.0 and for projection that
	 * gives the same x-coordinates for two different longitudes, as might happen
	 * at the N or S pole.  Some minor protections were added below to handle this.
	 */

	/* LOCAL VARIABLES */
	double su, sv, udlat, vdlat, udlon, vdlon, dudlat, dvdlat, dudlon, dvdlon, dl;
	int flip = 0;

	/* how much does x,y change for a 1 degree change in lon,lon ? */
	gmt_geo_to_xy (GMT, slon,     slat,     &su,    &sv );
	if ((slat+1.0) >= 90.0) {	/* PW: Must do something different at/near NP */
	        gmt_geo_to_xy (GMT, slon,     slat-1.0, &udlat, &vdlat);
		flip = 1;
	}
	else
		gmt_geo_to_xy (GMT, slon,     slat+1.0, &udlat, &vdlat);
	gmt_geo_to_xy (GMT, slon+1.0, slat    , &udlon, &vdlon);

	/* Compute dudlat, dudlon, dvdlat, dvdlon */
	dudlat = udlat - su;
	dvdlat = vdlat - sv;
	dudlon = udlon - su;
	dvdlon = vdlon - sv;
	if (flip) {	/* Fix what we did above */
		dudlat = -dudlat;
		dvdlat = -dvdlat;
	}

	/* Make unit vectors for the long (e/x) and lat (n/y) */
	/* to construct local transformation matrix */

	dl = sqrt (dudlon*dudlon + dvdlon*dvdlon);
	*t11 = (dl == 0.0) ? 0.0 : dudlon/dl;
	*t21 = (dl == 0.0) ? 0.0 : dvdlon/dl;

	dl = sqrt (dudlat*dudlat + dvdlat*dvdlat);
	*t12 = (dl == 0.0) ? 0.0 : dudlat/dl;
	*t22 = (dl == 0.0) ? 0.0 : dvdlat/dl;
}

static double utilmeca_null_axis_dip (double str1, double dip1, double str2, double dip2) {
	/*
	   compute null axis dip when strike and dip are given
	   for each nodal plane.  Angles are in degrees.

	   Genevieve Patau
	*/

	double den;

	den = asind (sind (dip1) * sind (dip2) * sind (str1 - str2));
	if (den < 0.) den = -den;
	return (den);
}

static double utilmeca_null_axis_strike (double str1, double dip1, double str2, double dip2) {
	/*
	   Compute null axis strike when strike and dip are given
	   for each nodal plane.   Angles are in degrees.

	   Genevieve Patau
	*/

	double phn, cosphn, sinphn, sd1, cd1, sd2, cd2, ss1, cs1, ss2, cs2;

	sincosd (dip1, &sd1, &cd1);
	sincosd (dip2, &sd2, &cd2);
	sincosd (str1, &ss1, &cs1);
	sincosd (str2, &ss2, &cs2);

	cosphn = sd1 * cs1 * cd2 - sd2 * cs2 * cd1;
	sinphn = sd1 * ss1 * cd2 - sd2 * ss2 * cd1;
	if (sind(str1 - str2) < 0.0) {
		cosphn = -cosphn;
		sinphn = -sinphn;
	}
	phn = d_atan2d(sinphn, cosphn);
	if (phn < 0.0) phn += 360.0;
	return (phn);
}

static double utilmeca_proj_radius(double str1, double dip1, double str) {
	/*
	   Compute the vector radius for a given strike,
	   equal area projection, inferior sphere.
	   Strike and dip of the plane are given.

	   Genevieve Patau
	*/
	double dip, r;

	dip = atan (tand (dip1) * sind (str - str1));
	r = sqrt (2.) * sin (M_PI_4 - dip / 2.);
	return (r);
}

/***********************************************************************************************************/
double meca_ps_mechanism (struct GMT_CTRL *GMT, struct PSL_CTRL *PSL, double x0, double y0, st_me meca, double size, struct GMT_FILL *F, struct GMT_FILL *E, int outline) {
	/* Draw beachball for double couples
	   By Genevieve Patau
	*/

	double x[1000], y[1000];
	double pos_NP1_NP2 = sind (meca.NP1.str - meca.NP2.str);
	int fault = (meca.NP1.rake > 0 ? 1 : -1);
	double radius_size, str, radius, increment, si, co, ssize[1];

	int i;

	struct SEIS_AXIS N_axis;

	/* compute null axis strike and dip */
	N_axis.dip = utilmeca_null_axis_dip (meca.NP1.str, meca.NP1.dip, meca.NP2.str, meca.NP2.dip);
	N_axis.str = utilmeca_null_axis_strike (meca.NP1.str, meca.NP1.dip, meca.NP2.str, meca.NP2.dip);

	/* compute radius size of the bubble */
	radius_size = size * 0.5;

	/* fill at then beginning (here), outline at the end */
	/*  argument is DIAMETER!! */
	ssize[0] = size;
	gmt_setfill (GMT, E, 0);
	PSL_plotsymbol (PSL, x0, y0, ssize, PSL_CIRCLE);

	gmt_setfill (GMT, F, outline);
	if (fabs (pos_NP1_NP2) < SEIS_EPSILON) {
		/* pure normal or inverse fault (null axis strike is determined
		   with + or - 180 degrees. */
 		/* first nodal plane part */
		i = 0;
		increment = 1.0;
		str = meca.NP1.str;
		while (str <= meca.NP1.str + 180. + SEIS_EPSILON) {
			radius = utilmeca_proj_radius (meca.NP1.str, meca.NP1.dip, str) * radius_size;
			sincosd (str, &si, &co);
			x[i] = x0 + radius * si;
			y[i] = y0 + radius * co;
			str += increment;
			i++;
		}
		if (fault == -1) {
			/* normal fault, close first compressing part */
			str = meca.NP1.str + 180.;
			while (str >= meca.NP1.str - SEIS_EPSILON) {
				sincosd (str, &si, &co);
				x[i] = x0 + si * radius_size;
				y[i] = y0 + co * radius_size;
				str -= increment;
				i++;
			}
			PSL_plotpolygon (PSL, x, y, i);
			i = 0;
		}
		/* second nodal plane part */
		str = meca.NP2.str;
		while (str <= meca.NP2.str + 180. + SEIS_EPSILON) {
			radius = utilmeca_proj_radius (meca.NP2.str, meca.NP2.dip, str) * radius_size;
			sincosd (str, &si, &co);
			x[i] = x0 + radius * si;
			y[i] = y0 + radius * co;
			str += increment;
			i++;
		}
		if (fault == -1) {
			/* normal fault, close second compressing part */
			str = meca.NP2.str + 180.;
			while (str >= meca.NP2.str - SEIS_EPSILON) {
				sincosd (str, &si, &co);
				x[i] = x0 + si * radius_size;
				y[i] = y0 + co * radius_size;
				str -= increment;
				i++;
			}
		}
		PSL_plotpolygon (PSL, x, y, i);
	}
	/* pure strike-slip */
	else if (fabs (90. - N_axis.dip) < SEIS_EPSILON) {

		increment = (fabs(meca.NP1.rake) < SEIS_EPSILON) ? -1.0 : 1.0;
		/* first compressing part */
		for (i = 0; i <= 90; i++) {
			str = meca.NP1.str - 90.0 + i * increment;
			sincosd (str, &si, &co);
			x[i] = x0 + si * radius_size;
			y[i] = y0 + co * radius_size;
		}
		x[i] = x0;
		y[i] = y0;
		i++;
		PSL_plotpolygon (PSL, x, y, i);
		/* second compressing part */
		for (i = 0; i <= 90; i++) {
			str = meca.NP1.str + 90.0 + i * increment;
			sincosd (str, &si, &co);
			x[i] = x0 + si * radius_size;
			y[i] = y0 + co * radius_size;
		}
		x[i] = x0;
		y[i] = y0;
		i++;
		PSL_plotpolygon (PSL, x, y, i);
	}
	else {
		/* other cases */
		/* first nodal plane till null axis */
		i = 0;
		increment = 1.;
		if (meca.NP1.str > N_axis.str) meca.NP1.str -= 360.;
		str = meca.NP1.str;
		while (fabs (90. - meca.NP1.dip) < SEIS_EPSILON ? str <= meca.NP1.str + SEIS_EPSILON : str <= N_axis.str + SEIS_EPSILON) {
			radius = utilmeca_proj_radius (meca.NP1.str, meca.NP1.dip, str) * radius_size;
			sincosd (str, &si, &co);
			x[i] = x0 + radius * si;
			y[i] = y0 + radius * co;
			str += increment;
			i++;
		}

		/* second nodal plane from null axis */
		meca.NP2.str += (1 + fault) * 90.;
		if (meca.NP2.str >= 360.) meca.NP2.str -= 360.;
		increment = fault;
		if (fault * (meca.NP2.str - N_axis.str) < -SEIS_EPSILON) meca.NP2.str += fault * 360.;
		str = fabs (90. - meca.NP2.dip) < SEIS_EPSILON ? meca.NP2.str : N_axis.str;
		while (increment > 0. ? str <= meca.NP2.str + SEIS_EPSILON : str >= meca.NP2.str - SEIS_EPSILON) {
			radius = utilmeca_proj_radius (meca.NP2.str - (1 + fault) * 90., meca.NP2.dip, str) * radius_size;
			sincosd (str, &si, &co);
			x[i] = x0 + radius * si;
			y[i] = y0 + radius * co;
			str += increment;
			i++;
		}

		/* close the first compressing part */
		meca.NP1.str = meca_zero_360(meca.NP1.str);
		meca.NP2.str = meca_zero_360(meca.NP2.str);
		increment = pos_NP1_NP2 >= 0. ? -fault : fault;
		if (increment * (meca.NP1.str - meca.NP2.str) < - SEIS_EPSILON) meca.NP1.str += increment * 360.;
		str = meca.NP2.str;
		while (increment > 0. ? str <= meca.NP1.str + SEIS_EPSILON : str >= meca.NP1.str - SEIS_EPSILON) {
			sincosd (str, &si, &co);
			x[i] = x0 + si * radius_size;
			y[i] = y0 + co * radius_size;
			str += increment;
			i++;
		}

		PSL_plotpolygon (PSL, x, y, i);

		/* first nodal plane till null axis */
		i = 0;
		meca.NP1.str = meca_zero_360 (meca.NP1.str + 180.);
		if (meca.NP1.str - N_axis.str < - SEIS_EPSILON) meca.NP1.str += 360.;
		increment = -1.;
		str = meca.NP1.str;
		while (fabs (90. - meca.NP1.dip) < SEIS_EPSILON ? str >= meca.NP1.str -SEIS_EPSILON : str >= N_axis.str - SEIS_EPSILON) {
			radius = utilmeca_proj_radius (meca.NP1.str - 180., meca.NP1.dip, str) * radius_size;
			sincosd (str, &si, &co);
			x[i] = x0 + radius * si;
			y[i] = y0 + radius * co;
			str += increment;
			i++;
		}

		/* second nodal plane from null axis */
		meca.NP2.str = meca_zero_360(meca.NP2.str + 180.);
		increment = -fault;
		if (fault * (N_axis.str - meca.NP2.str) < - SEIS_EPSILON) meca.NP2.str -= fault * 360.;
		str = fabs (90. - meca.NP2.dip) < SEIS_EPSILON ? meca.NP2.str : N_axis.str;
		while (increment > 0. ? str <= meca.NP2.str + SEIS_EPSILON : str >= meca.NP2.str - SEIS_EPSILON) {
			radius = utilmeca_proj_radius (meca.NP2.str - (1 - fault) * 90., meca.NP2.dip, str) * radius_size;
			sincosd (str, &si, &co);
			x[i] = x0 + radius * si;
			y[i] = y0 + radius * co;
			str += increment;
			i++;
		}

		/* close the second compressing part */
		meca.NP1.str = meca_zero_360(meca.NP1.str);
		meca.NP2.str = meca_zero_360(meca.NP2.str);
		increment = pos_NP1_NP2 >= 0. ? -fault : fault;
		if (increment * (meca.NP1.str - meca.NP2.str) < - SEIS_EPSILON) meca.NP1.str += increment * 360.;
		str = meca.NP2.str;
		while (increment > 0. ? str <= meca.NP1.str + SEIS_EPSILON : str >= meca.NP1.str - SEIS_EPSILON) {
			sincosd (str, &si, &co);
			x[i] = x0 + si * radius_size;
			y[i] = y0 + co * radius_size;
			str += increment;
			i++;
		}

		PSL_plotpolygon (PSL, x, y, i);
	}

	/* fill at then beginning, outline at the end (here) */
	gmt_setfill (GMT, NULL, 1);
	PSL_plotsymbol (PSL, x0, y0, ssize, PSL_CIRCLE);
	return (size);
}

/*********************************************************************/
double meca_ps_plan (struct GMT_CTRL *GMT, struct PSL_CTRL *PSL, double x0, double y0, st_me meca, double size, int num_of_plane) {
	/* By Genevieve Patau */

	int i;

	double x[1000], y[1000], ssize[1];
	double radius_size, str, radius, si, co;

	/* compute radius size of the bubble */
	radius_size = size * 0.5;

	/*  argument is DIAMETER!!*/
	ssize[0] = size;
	PSL_setfill (PSL, GMT->session.no_rgb, 1);
	PSL_plotsymbol (PSL, x0, y0, ssize, PSL_CIRCLE);

	if (num_of_plane != 2) {
		for (i = 0; i <= 180; i++) {
			str = meca.NP1.str + i;
			radius = utilmeca_proj_radius (meca.NP1.str, meca.NP1.dip, str) * radius_size;
			sincosd (str, &si, &co);
			x[i] = x0 + radius * si;
			y[i] = y0 + radius * co;
		}
		PSL_plotline (PSL, x, y, i, PSL_MOVE|PSL_STROKE);
	}
	if (num_of_plane != 1) {
		for (i = 0; i <= 180; i++) {
			str = meca.NP2.str + i;
			radius = utilmeca_proj_radius(meca.NP2.str, meca.NP2.dip, str) * radius_size;
			sincosd (str, &si, &co);
			x[i] = x0 + radius * si;
			y[i] = y0 + radius * co;
		}
		PSL_plotline (PSL, x, y, i, PSL_MOVE|PSL_STROKE);
	}
	return (size);
}

/*********************************************************************/
double meca_zero_360 (double str) {
	/* By Genevieve Patau: put an angle between 0 and 360 degrees */
	if (str >= 360.0)
		str -= 360.0;
	else if (str < 0.0)
		str += 360.0;
	return (str);
}

/**********************************************************************/
double meca_computed_mw (struct SEIS_MOMENT moment, double ms) {
	/* Compute mw-magnitude from seismic moment or MS magnitude. */

	/* Genevieve Patau from
	   Thorne Lay, Terry C. Wallace
	   Modern Global Seismology
	   Academic Press, p. 384
	 */

	double mw;

	if (moment.exponent == 0)
		mw = ms;
	else
		mw = (log10 (moment.mant) + (double)moment.exponent - 16.1) * 2. / 3.;

	return (mw);
}

/*********************************************************************/
static double utilmeca_computed_strike1 (struct SEIS_NODAL_PLANE NP1) {
	/*
	   Compute the strike of the second nodal plane when are given
	   strike, dip and rake for the first nodal plane with AKI & RICHARD's
	   convention.  Angles are in degrees.
	   Genevieve Patau
	*/

	double str2, temp, cp2, sp2, ss, cs, sr, cr;
	double cd1 = cosd (NP1.dip);
	double am = (gmt_M_is_zero (NP1.rake) ? 1. : NP1.rake /fabs (NP1.rake));

	sincosd (NP1.rake, &sr, &cr);
	sincosd (NP1.str, &ss, &cs);
	if (cd1 < SEIS_EPSILON && fabs (cr) < SEIS_EPSILON) {
#if 0
		GMT_Report (API, GMT_MSG_DEBUG, "\nThe second plane is horizontal;");
		GMT_Report (API, GMT_MSG_DEBUG, "\nStrike is undetermined.");
		GMT_Report (API, GMT_MSG_DEBUG, "\nstr2 = NP1.str + 180. is taken to define");
		GMT_Report (API, GMT_MSG_DEBUG, "\nrake in the second plane.\n");
#endif
		str2 = NP1.str + 180.0;
	}
	else {
		temp = cr * cs;
		temp += sr * ss * cd1;
		sp2 = -am * temp;
		temp = ss * cr;
		temp -= sr *  cs * cd1;
		cp2 = am * temp;
		str2 = d_atan2d(sp2, cp2);
		str2 = meca_zero_360(str2);
	}
	return (str2);
}

/*********************************************************************/
static double utilmeca_computed_dip1 (struct SEIS_NODAL_PLANE NP1) {
	/*
	   Compute second nodal plane dip when are given strike,
	   dip and rake for the first nodal plane with AKI & RICHARD's
	   convention.  Angles are in degrees.
	   Genevieve Patau
	*/

	double am = (gmt_M_is_zero (NP1.rake) ? 1.0 : NP1.rake / fabs (NP1.rake));
	double dip2;

	dip2 = acosd (am * sind (NP1.rake) * sind (NP1.dip));

	return (dip2);
}

/*********************************************************************/
static double utilmeca_computed_rake1 (struct SEIS_NODAL_PLANE NP1) {
	/*
	   Compute rake in the second nodal plane when strike ,dip
	   and rake are given for the first nodal plane with AKI &
	   RICHARD's convention.  Angles are in degrees.

	   Genevieve Patau
	*/

	double rake2, sinrake2;
	double str2 = utilmeca_computed_strike1(NP1);
	double dip2 = utilmeca_computed_dip1(NP1);
	double am = (gmt_M_is_zero (NP1.rake) ? 1.0 : NP1.rake / fabs (NP1.rake));
	double sd, cd, ss, cs;
	sincosd (NP1.dip, &sd, &cd);
	sincosd (NP1.str - str2, &ss, &cs);

	if (fabs (dip2 - 90.0) < SEIS_EPSILON)
		sinrake2 = am * cd;
	else
		sinrake2 = -am * sd * cs / cd;

	rake2 = d_atan2d (sinrake2, -am * sd * ss);

	return (rake2);
}

/*********************************************************************/
double meca_computed_dip2 (double str1, double dip1, double str2) {
	/*
	   Compute second nodal plane dip when are given
	   strike and dip for the first plane and strike for
	   the second plane.  Angles are in degrees.
	   Warning : if dip1 == 90 and cos(str1 - str2) == 0
				 the second plane dip is undetermined
				 and the only first plane will be plotted.

	   Genevieve Patau */

	double dip2, cosdp12 = cosd(str1 - str2);

	if (fabs (dip1 - 90.) < SEIS_EPSILON && fabs (cosdp12) < SEIS_EPSILON)
		dip2 = 1000.0; /* (only first plane will be plotted) */
	else
		dip2 = d_atan2d (cosd (dip1), -sind (dip1) * cosdp12);

	return (dip2);
}

/*********************************************************************/
double meca_computed_rake2 (double str1, double dip1, double str2, double dip2, double fault) {
	/*
	   Compute rake in the second nodal plane when strike and dip
	   for first and second nodal plane are given with a double
	   characterizing the fault :
						  +1. inverse fault
						  -1. normal fault.
	   Angles are in degrees.

	   Genevieve Patau */

	double rake2, sinrake2, sd, cd, ss, cs;

	sincosd (str1 - str2, &ss, &cs);

	sd = sind(dip1);        cd = cosd(dip2);
	if (fabs (dip2 - 90.0) < SEIS_EPSILON)
		sinrake2 = fault * cd;
	else
		sinrake2 = -fault * sd * cs / cd;

	rake2 = d_atan2d (sinrake2, - fault * sd * ss);

	return (rake2);
}

/*********************************************************************/
void meca_define_second_plane (struct SEIS_NODAL_PLANE NP1, struct SEIS_NODAL_PLANE *NP2) {
	/*
	    Compute strike, dip, slip for the second nodal plane
	    when are given strike, dip and rake for the first one.
	    Genevieve Patau
	*/

	NP2->str = utilmeca_computed_strike1 (NP1);
	NP2->dip = utilmeca_computed_dip1 (NP1);
	NP2->rake  = utilmeca_computed_rake1 (NP1);
}

/***************************************************************************************/
void meca_moment2axe (struct GMT_CTRL *GMT, struct SEIS_M_TENSOR mt, struct SEIS_AXIS *T, struct SEIS_AXIS *N, struct SEIS_AXIS *P) {
	/* This version uses gmt_jacobi and does not suffer from the convert_matrix bug */
	unsigned int j, nrots, np = 3;
	double *a, *d, *b, *z, *v;
	double az[3], pl[3];

	a = gmt_M_memory (GMT, NULL, np*np, double);
	d = gmt_M_memory (GMT, NULL, np, double);
	b = gmt_M_memory (GMT, NULL, np, double);
	z = gmt_M_memory (GMT, NULL, np, double);
	v = gmt_M_memory (GMT, NULL, np*np, double);

	a[0]=mt.f[0];	a[1]=mt.f[3];	a[2]=mt.f[4];
	a[3]=mt.f[3];	a[4]=mt.f[1];	a[5]=mt.f[5];
	a[6]=mt.f[4];	a[7]=mt.f[5];	a[8]=mt.f[2];

	if (gmt_jacobi (GMT, a, np, np, d, v, b, z, &nrots))
		fprintf(GMT->session.std[GMT_ERR],"%s: Eigenvalue routine failed to converge in 50 sweeps.\n", GMT->init.module_name);

	for (j = 0; j < np; j++) {
		pl[j] = asin(-v[j*np]);
		az[j] = atan2(v[j*np+2], -v[j*np+1]);
		if (pl[j] <= 0.) {
			pl[j] = -pl[j];
			az[j] += M_PI;
		}
		if (az[j] < 0)
			az[j] += TWO_PI;
		else if (az[j] > TWO_PI)
			az[j] -= TWO_PI;
		pl[j] *= R2D;
		az[j] *= R2D;
	}
	T->val = d[0];	T->e = mt.expo;	T->str = az[0]; T->dip = pl[0];
	N->val = d[1];	N->e = mt.expo; N->str = az[1]; N->dip = pl[1];
	P->val = d[2];	P->e = mt.expo; P->str = az[2]; P->dip = pl[2];

	gmt_M_free (GMT, a);	gmt_M_free (GMT, d);
	gmt_M_free (GMT, b);	gmt_M_free (GMT, z);
	gmt_M_free (GMT, v);
}

/***************************************************************************************/
double meca_ps_tensor (struct GMT_CTRL *GMT, struct PSL_CTRL *PSL, double x0, double y0, double size, struct SEIS_AXIS T, struct SEIS_AXIS N, struct SEIS_AXIS P, struct GMT_FILL *C, struct GMT_FILL *E, int outline, int plot_zerotrace, int recno) {
	/* Plot beachball for full moment tensors */
	int d, b = 1, m, i, ii, n = 0, j1 = 1, j2 = 0, j3 = 0;
	int bigisotestv0, bigisotestv2;

	double a[3], p[3], v[3], azi[3][2];
	double vi, iso, f, fir, s2alphan, alphan;
	double cfi, sfi, can, san, xz, xn, xe;
	double cpd, spd, cpb, spb, cpm, spm;
	double cad, sad, cab, sab, cam, sam;
	double az = 0., azp = 0., takeoff, r, xc, yc;
	double x1[400], y1[400], x2[400], y2[400], x3[400], y3[400];
	double xp1[800], yp1[800], xp2[400], yp2[400];
	double radius_size, si, co, ssize[1];

	struct GMT_FILL *F1 = NULL, *F2 = NULL;

	a[0] = T.str; a[1] = N.str; a[2] = P.str;
	p[0] = T.dip; p[1] = N.dip; p[2] = P.dip;
	v[0] = T.val; v[1] = N.val; v[2] = P.val;

	vi = (v[0] + v[1] + v[2]) / 3.;
	for (i=0; i<=2; i++) v[i] = v[i] - vi;

	ssize[0] = size;
	radius_size = size * 0.5;

	/* pure implosion or explosion */
	if (fabs (squared(v[0]) + squared(v[1]) + squared(v[2])) < SEIS_EPSILON) {
		if (vi > 0.) {
			gmt_setfill (GMT, C, 1);
			PSL_plotsymbol (PSL, x0, y0, ssize, PSL_CIRCLE);
		}
		if (vi < 0.) {
			gmt_setfill (GMT, E, 1);
			PSL_plotsymbol (PSL, x0, y0, ssize, PSL_CIRCLE);
		}
		return (radius_size*2.);
	}

	if (plot_zerotrace) vi = 0.;

	/* Test to choose the dominant eigenvalue after Frohlich for plotting purposes
	   by DS Dreger
	*/
	bigisotestv0 = 0;
	bigisotestv2 = 0;
	for (i = 0; i < 360; i++) {
		fir = (double)i * D2R;

		f = -v[1] / v[0];
		iso = vi / v[0];
		s2alphan = (2. + 2. * iso) / (3. + (1. - 2. * f) * cos(2. * fir));
		if (s2alphan > 1.0) bigisotestv0 += 1;

		f = -v[1] / v[2];
		iso = vi / v[2];
		s2alphan = (2. + 2. * iso) / (3. + (1. - 2. * f) * cos(2. * fir));
		if (s2alphan > 1.0) bigisotestv2 += 1;
	}

	if (bigisotestv0 == 0) {
		d = 0;
		m = 2;
		F1 = C;
		F2 = E;
	} else if (bigisotestv2 == 0) {
		d = 2;
		m = 0;
		F1 = E;
		F2 = C;
	} else {
		fprintf (stderr, "Warning: bigisotest failed for record %d, please report the issue to us! \n", recno);
		return -1;
	}

	f = - v[1] / v[d];
	iso = vi / v[d];

	sincosd (p[d], &spd, &cpd);
	sincosd (p[b], &spb, &cpb);
	sincosd (p[m], &spm, &cpm);
	sincosd (a[d], &sad, &cad);
	sincosd (a[b], &sab, &cab);
	sincosd (a[m], &sam, &cam);

	for (i = 0; i < 360; i++) {
		fir = (double) i * D2R;
		s2alphan = (2 + 2 * iso) / (3 + (1 - 2 * f) * cos(2 * fir));
		alphan = asin(sqrt(s2alphan));
		sincos (fir, &sfi, &cfi);
		sincos (alphan, &san, &can);

		xz = can * spd + san * sfi * spb + san * cfi * spm;
		xn = can * cpd * cad + san * sfi * cpb * cab + san * cfi * cpm * cam;
		xe = can * cpd * sad + san * sfi * cpb * sab + san * cfi * cpm * sam;

		if (fabs (xn) < SEIS_EPSILON && fabs (xe) < SEIS_EPSILON) {
			takeoff = 0.;
			az = 0.;
		}
		else {
			az = atan2(xe, xn);
			if (az < 0.) az += M_PI * 2.;
			takeoff = acos(xz / sqrt(xz * xz + xn * xn + xe * xe));
		}
		if (takeoff > M_PI_2) {
			takeoff = M_PI - takeoff;
			az += M_PI;
			if (az > M_PI * 2.) az -= M_PI * 2.;
		}
		r = M_SQRT2 * sin(takeoff / 2.);
		sincos (az, &si, &co);
		xc = x0 + radius_size * r * si;
		yc = y0 + radius_size * r * co;

		if (i == 0) {
			azi[i][0] = az;
			x1[i] = xc; y1[i] = yc;
		}
		else {
			if (fabs (fabs (az - azp) - M_PI) < D2R * 10.0 && takeoff > 80.0 * D2R) {
				/* Find a gap, so start a new segment. A gap must meet the following two criteria:
				 * 1. Current azimuth diffs from previous azimuth by ~180 degree
				 * 2. Takeoff angle is ~90 degree so that the data fall at the beachball boundary
				 *
				 * Note: the choices of 10.0 and 80.0 are arbitrary and may NOT work for extreme cases.
				 */
				azi[n][1] = azp;
				assert (n < 2);
				azi[++n][0] = az;
			}
			if (fabs (fabs (az - azp) - M_PI * 2.) < D2R * 2.) {
				if (azp < az)
					azi[n][0] += M_PI * 2.;
				else
					azi[n][0] -= M_PI * 2.;
			}
			switch (n) {
				case 0 :
					x1[j1] = xc; y1[j1++] = yc;
					break;
				case 1 :
					x2[j2] = xc; y2[j2++] = yc;
					break;
				case 2 :
					x3[j3] = xc; y3[j3++] = yc;
					break;
			}
		}
		azp = az;
	}
	azi[n][1] = az;

	/* fill at then beginning (here), outline at the end */
	gmt_setfill (GMT, F2, 0);
	PSL_plotsymbol (PSL, x0, y0, ssize, PSL_CIRCLE);

	gmt_setfill (GMT, F1, outline);
	switch (n) {
		case 0 :
			for (i = 0; i < 360; i++) {
				xp1[i] = x1[i]; yp1[i] = y1[i];
			}
			PSL_plotpolygon (PSL, xp1, yp1, i);
			break;
		case 1 :
			for (i = 0; i < j1; i++) {
				xp1[i] = x1[i]; yp1[i] = y1[i];
			}
			if (azi[0][0] - azi[0][1] > M_PI)
				azi[0][0] -= M_PI * 2.;
			else if (azi[0][1] - azi[0][0] > M_PI)
				azi[0][0] += M_PI * 2.;
			if (azi[0][0] < azi[0][1]) {
				for (az = azi[0][1] - D2R; az > azi[0][0]; az -= D2R) {
					sincos (az, &si, &co);
					xp1[i] = x0 + radius_size * si;
					yp1[i++] = y0 + radius_size * co;
				}
			}
			else {
				for (az = azi[0][1] + D2R; az < azi[0][0]; az += D2R) {
					sincos (az, &si, &co);
					xp1[i] = x0 + radius_size * si;
					yp1[i++] = y0 + radius_size * co;
				}
			}
			PSL_plotpolygon (PSL, xp1, yp1, i);
			for (i = 0; i < j2; i++) {
				xp2[i] = x2[i]; yp2[i] = y2[i];
			}
			if (azi[1][0] - azi[1][1] > M_PI)
				azi[1][0] -= M_PI * 2.;
			else if (azi[1][1] - azi[1][0] > M_PI)
				azi[1][0] += M_PI * 2.;
			if (azi[1][0] < azi[1][1]) {
				for (az = azi[1][1] - D2R; az > azi[1][0]; az -= D2R) {
					sincos (az, &si, &co);
					xp2[i] = x0 + radius_size * si;
					yp2[i++] = y0 + radius_size * co;
				}
			}
			else {
				for (az = azi[1][1] + D2R; az < azi[1][0]; az += D2R) {
					sincos (az, &si, &co);
					xp2[i] = x0 + radius_size * si;
					yp2[i++] = y0 + radius_size * co;
				}
			}
			PSL_plotpolygon (PSL, xp2, yp2, i);
			break;
		case 2 :
			for (i = 0; i < j3; i++) {
				xp1[i] = x3[i]; yp1[i] = y3[i];
			}
			for (ii = 0; ii < j1; ii++) {
				xp1[i] = x1[ii]; yp1[i++] = y1[ii];
			}

			if (azi[2][0] - azi[0][1] > M_PI)
				azi[2][0] -= M_PI * 2.;
			else if (azi[0][1] - azi[2][0] > M_PI)
				azi[2][0] += M_PI * 2.;
			if (azi[2][0] < azi[0][1]) {
				for (az = azi[0][1] - D2R; az > azi[2][0]; az -= D2R) {
					sincos (az, &si, &co);
					xp1[i] = x0 + radius_size * si;
					yp1[i++] = y0 + radius_size * co;
				}
			}
			else {
				for (az = azi[0][1] + D2R; az < azi[2][0]; az += D2R) {
					sincos (az, &si, &co);
					xp1[i] = x0 + radius_size * si;
					yp1[i++] = y0 + radius_size * co;
				}
			}
			PSL_plotpolygon (PSL, xp1, yp1, i);
			for (i = 0; i < j2; i++) {
				xp2[i] = x2[i]; yp2[i] = y2[i];
			}
			if (azi[1][0] - azi[1][1] > M_PI)
				azi[1][0] -= M_PI * 2.;
			else if (azi[1][1] - azi[1][0] > M_PI)
				azi[1][0] += M_PI * 2.;
			if (azi[1][0] < azi[1][1]) {
				for (az = azi[1][1] - D2R; az > azi[1][0]; az -= D2R) {
					sincos (az, &si, &co);
					xp2[i] = x0 + radius_size * si;
					yp2[i++] = y0 + radius_size * co;
				}
			}
			else {
				for (az = azi[1][1] + D2R; az < azi[1][0]; az += D2R) {
					sincos (az, &si, &co);
					xp2[i] = x0 + radius_size * si;
					yp2[i++] = y0 + radius_size * co;
				}
			}
			PSL_plotpolygon (PSL, xp2, yp2, i);
			break;
	}

	/* fill at then beginning, outline at the end (here) */
	gmt_setfill (GMT, NULL, 1);
	PSL_plotsymbol (PSL, x0, y0, ssize, PSL_CIRCLE);

	return (size);
}

void meca_axe2dc (struct SEIS_AXIS T, struct SEIS_AXIS P, struct SEIS_NODAL_PLANE *NP1, struct SEIS_NODAL_PLANE *NP2) {
	/*
	  Calculate double couple from principal axes.
	  Angles are in degrees.

	  Genevieve Patau, 16 juin 1997
	*/

	double p1, d1, p2, d2;
	double cdp, sdp, cdt, sdt, cpt, spt, cpp, spp;
	double amz, amy, amx, im;

	sincosd (P.dip, &sdp, &cdp);
	sincosd (P.str, &spp, &cpp);
	sincosd (T.dip, &sdt, &cdt);
	sincosd (T.str, &spt, &cpt);

	cpt *= cdt; spt *= cdt;
	cpp *= cdp; spp *= cdp;

	amz = sdt + sdp; amx = spt + spp; amy = cpt + cpp;
	d1 = atan2d (hypot(amx, amy), amz);
	p1 = atan2d (amy, -amx);
	if (d1 > 90.0) {
		d1 = 180.0 - d1;
		p1 -= 180.0;
	}
	if (p1 < 0.0) p1 += 360.0;

	amz = sdt - sdp; amx = spt - spp; amy = cpt - cpp;
	d2 = atan2d (hypot(amx, amy), amz);
	p2 = atan2d (amy, -amx);
	if (d2 > 90.0) {
		d2 = 180.0 - d2;
		p2 -= 180.0;
	}
	if (p2 < 0.0) p2 += 360.0;

	NP1->dip = d1; NP1->str = p1;
	NP2->dip = d2; NP2->str = p2;

	im = 1;
	if (P.dip > T.dip) im = -1;
	NP1->rake = meca_computed_rake2 (NP2->str, NP2->dip, NP1->str, NP1->dip, im);
	NP2->rake = meca_computed_rake2 (NP1->str, NP1->dip, NP2->str, NP2->dip, im);
}

void meca_dc2axe (st_me meca, struct SEIS_AXIS *T, struct SEIS_AXIS *N, struct SEIS_AXIS *P) {
	/*
	From FORTRAN routines of Anne Deschamps :
	compute azimuth and plungement of P-T axis
	from nodal plane strikes, dips and rakes.
	*/

	double cd1, sd1, cd2, sd2, cp1, sp1, cp2, sp2;
	double amz, amx, amy, dx, px, dy, py;

	cd1 = cosd (meca.NP1.dip) * M_SQRT2;
	sd1 = sind (meca.NP1.dip) * M_SQRT2;
	cd2 = cosd (meca.NP2.dip) * M_SQRT2;
	sd2 = sind (meca.NP2.dip) * M_SQRT2;
	cp1 = - cosd (meca.NP1.str) * sd1;
	sp1 = sind (meca.NP1.str) * sd1;
	cp2 = - cosd (meca.NP2.str) * sd2;
	sp2 = sind (meca.NP2.str) * sd2;

	amz = - (cd1 + cd2);
	amx = - (sp1 + sp2);
	amy = cp1 + cp2;
	dx = atan2d (hypot(amx, amy), amz) - 90.0;
	px = atan2d (amy, -amx);
	if (px < 0.0) px += 360.0;
	if (dx < SEIS_EPSILON) {
		if (px > 90.0 && px < 180.0) px += 180.0;
		if (px >= 180.0 && px < 270.0) px -= 180.0;
	}

	amz = cd1 - cd2;
	amx = sp1 - sp2;
	amy = - cp1 + cp2;
	dy = atan2d (hypot(amx, amy), -fabs(amz)) - 90.0;
	py = atan2d (amy, -amx);
	if (amz > 0.0) py -= 180.0;
	if (py < 0.0) py += 360.0;
	if (dy < SEIS_EPSILON) {
		if (py > 90.0 && py < 180.0) py += 180.0;
		if (py >= 180.0 && py < 270.0) py -= 180.0;
	}

	if (meca.NP1.rake > 0.0) {
		P->dip = dy; P->str = py;
		T->dip = dx; T->str = px;
	}
	else {
		P->dip = dx; P->str = px;
		T->dip = dy; T->str = py;
	}

	N->str = utilmeca_null_axis_strike (T->str, T->dip, P->str, P->dip);
	N->dip = utilmeca_null_axis_dip (T->str, T->dip, P->str, P->dip);
}

void meca_axis2xy (double x0, double y0, double size, double pp, double dp, double pt, double dt, double *xp,double *yp, double *xt, double *yt) {
	/* angles are in degrees */
	double radius, spp, cpp, spt, cpt;

	sincosd (pp, &spp, &cpp);
	sincosd (pt, &spt, &cpt);

	size *= 0.5;
	radius = sqrt(1. - sind(dp));
	if (radius >= 0.97) radius = 0.97;
	*xp = radius * spp * size + x0;
	*yp = radius * cpp * size + y0;
	radius = sqrt(1. - sind(dt));
	if (radius >= 0.97) radius = 0.97;
	*xt = radius * spt * size + x0;
	*yt = radius * cpt * size + y0;
}

#if 0	/* Currently not used but saved in case of debug operations */
#ifdef DEBUG
GMT_LOCAL int utilmeca_dump_meca (st_me meca) {
	fprintf (stderr, "\nNodal plane NP1: str = %g dip = %g rake = %g\n", meca.NP1.str, meca.NP1.dip, meca.NP1.rake);
	fprintf (stderr, "Nodal plane NP2: str = %g dip = %g rake = %g\n", meca.NP2.str, meca.NP2.dip, meca.NP2.rake);
	fprintf (stderr, "Magnitude = %g exponent = %d\n", meca.moment.mant, meca.moment.exponent);
	fprintf (stderr, "magms = %g\n", meca.magms);
	return (0);
}
#endif
#endif

/* Parsing of meca -A and coupe -D options for offsetting symbols */

unsigned int meca_line_parse (struct GMT_CTRL *GMT, struct SEIS_OFFSET_LINE *L, char option, char *arg) {
	unsigned int n_errors = 0, k;
	int n;
	char txt[GMT_LEN256] = {""}, *c = NULL, *q = NULL;
	char *modifiers = (option == 'D') ? "cgops" : "gops";	/* Coupe also as +c */
	strncpy (txt, arg, GMT_LEN256-1);

	/* Deal with these possible variations of old -C and new -A options in meca:
	 * 1. -A[+p<pen>][+s<size>]	which is the current syntax
	 * 2. -C[<pen>][+s<size>]	which was the GMT5-6.1.1 syntax
	 * 3. -C[<pen>][P<size>]	which was the GMT4 syntax */

	if ((c = gmt_first_modifier (GMT, txt, modifiers))) {	/* Found at least one valid modifier */
		unsigned int pos = 0;
		char p[GMT_LEN256] = {""};
		while (gmt_getmodopt (GMT, option, c, modifiers, &pos, p, &n_errors) && n_errors == 0) {
			switch (p[0]) {
				case 'c':	/* Geo->cart conversion in coupe: +c */
					if (p[1] == '\0') 
						L->convert_geo = true;	/* ALternate location given geographically, must convert to dist/depth */
					else {
						GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: +c takes no argument %s\n", option, &p[1]);
						n_errors++;
					}
					break;
				case 'g':	/* Symbol fill +g<fill> or no fill +g */
					if (p[1] == '\0') 
						L->fill_mode = SEIS_NO_FILL;	/* No fill */
					else if (gmt_getfill (GMT, &p[1], &L->fill)) {
						GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Bad +g<fill> argument %s\n", option, &p[1]);
						n_errors++;
					}
					else
						L->fill_mode = SEIS_FIXED_FILL;	/* Default is to fill, with -G unless overwritten */
					break;
				case 'o':	/* Variable or fixed plot offsets */
					if (p[1] == '\0')	/* No args means we read dx and dy as the "alternate coordinates". Implies +c */
						L->mode |= SEIS_CART_OFFSET;
					else if ((n = gmt_get_pair (GMT, &p[1], GMT_PAIR_DIM_DUP, L->off)) < 0) {
						GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Failed to parse offset arguments for +o modifier\n", option);
						n_errors++;
					}
					else
						L->mode |= SEIS_CART_OFFSET_FIX;
					break;
				case 'p':	/* Line and symbol pen */
					if (p[1] == '\0' || gmt_getpen (GMT, &p[1], &L->pen)) {
						gmt_pen_syntax (GMT, option, NULL, " ", NULL, 0);
						n_errors++;
					}
					break;
				case 's':	/* Symbol diameter */
					k = 2;	/* Start of size if symbol type was explicitly given */
					switch (p[1]) {	/* Check all standard geometric symbols */
						case 'a': L->symbol = PSL_STAR;	break;
						case 'c': L->symbol = PSL_CIRCLE;	break;
						case 'd': L->symbol = PSL_DIAMOND;	break;
						case 'g': L->symbol = PSL_OCTAGON;	break;
						case 'h': L->symbol = PSL_HEXAGON;	break;
						case 'i': L->symbol = PSL_INVTRIANGLE;	break;
						case 'n': L->symbol = PSL_PENTAGON;	break;
						case 'r': L->symbol = PSL_RECT;	break;
						case 's': L->symbol = PSL_SQUARE;	break;
						case 't': L->symbol = PSL_TRIANGLE;	break;
						case 'x': L->symbol = PSL_CROSS;	break;
						default:	/* Presumably just size and default to circle, but check for errors */
							if (isalpha (p[1])) {	/* Bad symbol code */
								GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Symbol code %s not supported\n", option, &p[1]);
								n_errors++;
							}
							else {	/* No symbol type given, default to circle */
								L->symbol = PSL_CIRCLE;
								k = 1;
							}
							break;
					}
					if (p[1] == '\0' || (L->size = gmt_M_to_inch (GMT, &p[k])) < 0.0) {
						GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Circle diameter cannot be negative or not given!\n", option);
						n_errors++;
					}
					break;
				default: break;	/* These are caught in gmt_getmodopt so break is just for Coverity */
			}
		}
		c[0] = '\0';	/* Chop off the modifiers */
	}
	/* If the user used modern modifiers only as case 1 above then we might be done here */
	if (txt[0] == '\0') return n_errors;

	/* Here we got older syntax: -C<pen>[+s<size>] or -C[<pen>][P<size>] (but the +s<size> would have been stripped off
	 * so here we must either have -C<pen> or -C[<pen>][P<size>] */

	L->symbol = PSL_CIRCLE;	/* Only option with this syntax */
	if ((q = strchr (txt, 'P')) != NULL) {	/* Case 3 way of changing the diameter */
		if (q[1] == '\0' || (L->size = gmt_M_to_inch (GMT, &q[1])) < 0.0) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Circle diameter cannot be negative or not given!\n", option);
			n_errors++;
		}
		q[0] = '\0';	/* Chop off the Psize setting; if txt is not empty we also have an optional pen */
		if (txt[0] && gmt_getpen (GMT, txt, &L->pen)) {
			gmt_pen_syntax (GMT, option, NULL, " ", NULL, 0);
			n_errors++;
		}
	}
	else if (gmt_getpen (GMT, txt, &L->pen)) {	/* Here we just have -C<pen> to deal with */
		gmt_pen_syntax (GMT, option, NULL, " ", NULL, 0);
		n_errors++;
	}
	return n_errors;
}

void meca_line_usage (struct GMTAPI_CTRL *API, char option) {
	/* Print the usage message for coupe -D and meca -A */
	char *insert = (option == 'D') ? "[+c]" : "";	/* Coupe also as +c */
	GMT_Usage (API, 1, "\n-%c%s%s", option, insert, SEIS_LINE_SYNTAX);
	GMT_Usage (API, -2, "Offset focal mechanisms to alternate positions given in the last two columns of the input file (before the optional label). "
		"A line is drawn between both positions:");
	if (option == 'D')
		GMT_Usage (API, 3, "+c Alternate coupe locations given as lon, lat; convert to (distance, depth() in crossectional plane [Read Cartesian locations].");
	GMT_Usage (API, 3, "+g Append fill for optional symbol, or chose no fill with +g [Default uses the beachball fill].");
	GMT_Usage (API, 3, "+o Offset the plot positions by <dx>/<dy>.  If none given then we expect the alternative position columns to hold the offsets.");
	GMT_Usage (API, 3, "+p Specify the pen used to draw the line between original and adjusted position [0.25p].");
	GMT_Usage (API, 3, "+s Draw a small symbol of indicated size at the original location. Default symbol is a circle "
		"but optionally any standard symbol code from a|c|d|g|h|i|n|p|s|t|x is accepted [no symbol].");
}
