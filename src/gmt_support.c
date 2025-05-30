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
/*
 *
 *			G M T _ S U P P O R T . C
 *
 *- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * GMT_support.c contains code used by most GMT programs
 *
 * Author:  Paul Wessel
 * Date:    1-JAN-2010
 * Version: 5
 *
 * A) List of exported gmt_* functions available to modules and libraries via gmt_dev.h:
 *
 *	gmt_BC_init
 *	gmt_RI_prepare
 *	gmt_add_options
 *	gmt_adjust_refpoint
 *	gmt_arabic2roman
 *	gmt_argv2str
 *	gmt_assign_text
 *	gmt_best_dim_choice
 *	gmt_cat_cpt_strings
 *	gmt_centroid_area
 *	gmt_char_count
 *	gmt_run_process_get_first_line
 *  gmt_check_executable
 *	gmt_check_language
 *	gmt_colorname2index
 *	gmt_consider_current_cpt
 *	gmt_contlabel_free
 *	gmt_contlabel_info
 *	gmt_contlabel_init
 *	gmt_contlabel_prep
 *	gmt_contlabel_specs
 *	gmt_contour_A_arg_parsing
 *	gmt_contour_C_arg_parsing
 *	gmt_contour_T_arg_parsing
 *	gmt_contour_edge_init
 *	gmt_contour_first_pos
 *	gmt_contours
 *  gmt_explain_cpt_input
 *  gmt_explain_cpt_output
 *	gmt_cpt_default
 *	gmt_cpt_interval_modifier
 *	gmt_cpt_transparency
 *	gmt_create_array
 *	gmt_create_tempdir
 *	gmt_create_tempfile
 *	gmt_crossing_dateline
 *	gmt_crossover
 *	gmt_crosstracks
 *	gmt_cube_BC_set
 *	gmt_decorate_prep
 *	gmt_decorated_line
 *	gmt_delaunay
 *	gmt_delaunay_free
 *	gmt_dry_run_only
 *	gmt_duplicate_array
 *	gmt_enable_threads
 *	gmt_err_func
 *	gmt_extend_region
 *	gmt_filename_get
 *	gmt_filename_set
 *	gmt_find_macro
 *	gmt_first_modifier
 *	gmt_flip_angle_d
 *	gmt_flip_azim_d
 *	gmt_flip_justify
 *	gmt_format_region
 *	gmt_found_modifier
 *	gmt_free_array
 *	gmt_free_int_selection
 *	gmt_free_list
 *	gmt_free_macros
 *	gmt_free_refpoint
 *	gmt_free_text_selection
 *	gmt_freepen
 *	gmt_gcd_euclid
 *	gmt_get_columbar_bands
 *	gmt_get_contours_from_table
 *	gmt_get_current_item
 *	gmt_get_dist_units
 *	gmt_get_distance
 *	gmt_get_fill_from_key
 *	gmt_get_fill_from_z
 *	gmt_get_format
 *	gmt_get_index
 *	gmt_get_int_selection
 *	gmt_get_limits
 *	gmt_get_no_argument
 *	gmt_get_pair
 *	gmt_get_palette
 *	gmt_get_plot_array
 *	gmt_get_prime_factors
 *	gmt_get_refpoint
 *	gmt_get_required_char
 *	gmt_get_required_double
 *	gmt_get_required_file
 *	gmt_get_required_float
 *	gmt_get_required_int
 *	gmt_get_required_string
 *	gmt_get_required_uint
 *	gmt_get_required_uint64
 *	gmt_get_rgb_from_z
 *	gmt_get_rgb_lookup
 *	gmt_get_rgbtxt_from_z
 *	gmt_get_segtext_selection
 *	gmt_get_strwithtab
 *	gmt_get_tempname
 *	gmt_get_vector_shrinking
 *	gmt_getfill
 *	gmt_getfont
 *	gmt_getfonttype
 *	gmt_getinc
 *	gmt_getincn
 *	gmt_getinset
 *	gmt_getmodopt
 *	gmt_getpanel
 *	gmt_getpen
 *	gmt_getrgb
 *	gmt_getrose
 *	gmt_getscale
 *	gmt_grd_BC_set
 *	gmt_hold_contour
 *	gmt_hsv_to_rgb
 *	gmt_illuminate
 *	gmt_increment_adjust
 *	gmt_init_fill
 *	gmt_init_next_color
 *	gmt_init_pen
 *	gmt_init_track
 *	gmt_inonout
 *	gmt_intpol
 *	gmt_invert_cpt
 *	gmt_is_barcolumn
 *	gmt_is_cpt_master
 *	gmt_is_fill
 *	gmt_is_gmt_end_show
 *	gmt_is_gmtmodule
 *	gmt_just_decode
 *	gmt_just_to_code
 *	gmt_just_to_lonlat
 *	gmt_just_to_xy
 *	gmt_just_validate
 *	gmt_lab_to_rgb
 *	gmt_lab_to_xyz
 *	gmt_list_cpt
 *	gmt_list_custom_symbols
 *	gmt_list_to_array
 *	gmt_load_macros
 *	gmt_locate_custom_symbol
 *	gmt_make_equidistant_array
 *	gmt_make_filename
 *	gmt_make_profiles
 *	gmt_matrix_vect_mult
 *	gmt_mean_point
 *	gmt_memory_use
 *	gmt_minmaxinc_verify
 *	gmt_new_record
 *	gmt_no_pstext_input
 *	gmt_non_zero_winding
 *	gmt_optimal_dim_for_surface
 *	gmt_parse_array
 *	gmt_parse_inv_cpt
 *	gmt_place_var
 *	gmt_pol_area
 *	gmt_polygon_centroid
 *	gmt_polygon_is_open
 *	gmt_polygon_orientation
 *	gmt_prepare_contour
 *	gmt_putfont
 *	gmt_putpen
 *	gmt_putusername
 *	gmt_read_list
 *	gmt_read_triangulation
 *	gmt_resample_data
 *	gmt_reset_array_time
 *	gmt_rgb_to_hsv
 *	gmt_rgb_to_lab
 *	gmt_rgb_to_xyz
 *	gmt_row_col_out_of_bounds
 *	gmt_same_fill
 *	gmt_sample_cpt
 *	gmt_save_current_cpt
 *	gmt_scale_cpt
 *	gmt_scale_pen
 *	gmt_script_is_classic
 *	gmt_segmentize_data
 *	gmt_set_comment
 *	gmt_set_dvalue
 *	gmt_set_inside_mode
 *	gmt_set_int_selection
 *	gmt_set_interpolate_mode
 *	gmt_set_ivalue
 *	gmt_set_next_color
 *	gmt_set_refpoint
 *	gmt_set_script
 *	gmt_set_text_selection
 *	gmt_set_tvalue
 *	gmt_set_value
 *	gmt_set_xy_domain
 *	gmt_signum
 *	gmt_sleep
 *	gmt_smart_justify
 *	gmt_sort_array
 *	gmt_sort_order
 *	gmt_sprintf_float
 *	gmt_str_setcase
 *	gmt_str_tolower
 *	gmt_str_toupper
 *	gmt_stretch_cpt
 *	gmt_substitute_macros
 *	gmt_symbol_free
 *	gmt_testing
 *	gmt_token_check
 *	gmt_trim_line
 *	gmt_trim_requested
 *	gmt_truncate_cpt
 *	gmt_undo_log10
 *	gmt_unpack_rgbcolors
 *	gmt_validate_cpt_parameters
 *	gmt_validate_modifiers
 *	gmt_verify_expectations
 *	gmt_voronoi
 *	gmt_write_glue_function
 *	gmt_x_free
 *	gmt_x_is_outside
 *	gmt_x_out_of_bounds
 *	gmt_xyz_to_lab
 *	gmt_xyz_to_rgb
 *	gmt_y_out_of_bounds
 *
 * B) List of exported gmtlib_* functions available to libraries via gmt_internals.h:
 *
 *	gmtlib_akima
 *	gmtlib_annot_pos
 *	gmtlib_coordinate_array
 *	gmtlib_copy_palette
 *	gmtlib_cptfile_unitscale
 *	gmtlib_create_palette
 *	gmtlib_cspline
 *	gmtlib_decorate_info
 *	gmtlib_decorate_init
 *	gmtlib_decorate_specs
 *	gmtlib_detrend
 *	gmtlib_duplicate_palette
 *	gmtlib_enforce_rgb_triplets
 *	gmtlib_free_cpt_ptr
 *	gmtlib_free_custom_symbols
 *	gmtlib_free_palette
 *	gmtlib_get_annot_label
 *	gmtlib_get_arc
 *	gmtlib_get_coordinate_label
 *	gmtlib_get_custom_symbol
 *	gmtlib_get_map_interval
 *	gmtlib_getpenstyle
 *	gmtlib_getrgb_index
 *	gmtlib_glob_list
 *	gmtlib_image_BC_set
 *	gmtlib_init_cpt
 *	gmtlib_init_rot_matrix
 *	gmtlib_inplace_transpose
 *	gmtlib_invalid_symbolname
 *	gmtlib_is_color
 *	gmtlib_last_valid_file_modifier
 *	gmtlib_linear_array
 *	gmtlib_load_custom_annot
 *	gmtlib_load_rot_matrix
 *	gmtlib_log2_array
 *	gmtlib_log_array
 *	gmtlib_polar_prepare_label
 *	gmtlib_pow_array
 *	gmtlib_prepare_label
 *	gmtlib_read_cpt
 *	gmtlib_refpoint_to_panel_xy
 *	gmtlib_rotate2D
 *	gmtlib_set_current_item_file
 *	gmtlib_smooth_spline
 *	gmtlib_split_line_at_dateline
 *	gmtlib_time_array
 *	gmtlib_var_inc
 *	gmtlib_write_cpt
 */

/*!
 * \file gmt_support.c
 * \brief GMT_support.c contains code used by most GMT programs.
 */

#include "gmt_dev.h"
#include "gmt_internals.h"
#include <locale.h>
#ifndef WIN32
#include <glob.h>
#else
#include <windows.h>
#include <io.h>
#include <tchar.h>
#endif

/*! . */
enum GMT_profmode {
	GMT_GOT_AZIM	= 1,
	GMT_GOT_ORIENT	= 2,
	GMT_GOT_LENGTH	= 4,
	GMT_GOT_NP	= 8,
	GMT_GOT_INC	= 16,
	GMT_GOT_RADIUS	= 32,
};

/*! . */
enum gmt_ends {
	BEG = 0,
	END = 1
};

/*! Internal struct used in the processing of CPT z-scaling and truncation */
struct CPT_Z_SCALE {
	unsigned int z_adjust;	/* 1 if +u<unit> was parsed and scale set, 3 if z has been adjusted, 0 otherwise */
	unsigned int z_mode;	/* 1 if +U<unit> was parsed, 0 otherwise */
	unsigned int z_unit;	/* Unit enum specified via +u<unit> */
	double z_unit_to_meter;	/* Scale, given z_unit, to convert z from <unit> to meters */
};

static char *GMT_just_code[12] = {"--", "LB", "CB", "RB", "--", "LM", "CM", "RM", "--", "LT", "CT", "RT"};

#define gmt_M_uneven_interval(unit) ((unit == 'o' || unit == 'O' || unit == 'k' || unit == 'K' || unit == 'R' || unit == 'r' || unit == 'D' || unit == 'd') ? true : false)	/* true for uneven units */

/** @brief XYZ color of the D65 white point */
#define WHITEPOINT_X	0.950456
#define WHITEPOINT_Y	1.0
#define WHITEPOINT_Z	1.088754

/**
 * @brief sRGB gamma correction, transforms R to R'
 * http://en.wikipedia.org/wiki/SRGB
 */
#define GAMMACORRECTION(t) (((t) <= 0.0031306684425005883) ? (12.92*(t)) : (1.055*pow((t), 0.416666666666666667) - 0.055))

/**
 * @brief Inverse sRGB gamma correction, transforms R' to R
 */
#define INVGAMMACORRECTION(t) (((t) <= 0.0404482362771076) ? ((t)/12.92) : pow(((t) + 0.055)/1.055, 2.4))

/**
 * @brief CIE L*a*b* f function (used to convert XYZ to L*a*b*)
 * http://en.wikipedia.org/wiki/Lab_color_space
 */
#define LABF(t)	 ((t >= 8.85645167903563082e-3) ? pow(t,0.333333333333333) : (841.0/108.0)*(t) + (4.0/29.0))
#define LABINVF(t) ((t >= 0.206896551724137931) ? ((t)*(t)*(t)) : (108.0/841.0)*((t) - (4.0/29.0)))

static unsigned char gmt_M_color_rgb[GMT_N_COLOR_NAMES][3] = {	/* r/g/b of X11 colors */
#include "gmt_color_rgb.h"
};

/*! Names of pens and their thicknesses */
struct GMT_PEN_NAME {
	char name[16];
	double width;
};

/*! . */
static struct GMT_PEN_NAME GMT_penname[GMT_N_PEN_NAMES] = {		/* Names and widths of pens */
#include "gmt_pennames.h"
};

/*! List of GMT color tables available in makecpt and grd2cpt
 *  Some are based on MATLAB and Matplotlib color schemes.
 *  To add more tables, place the master CPT file in share/cpt and
 *  add a one-line entry with name and explanation in gmt_cpt_masters.h. */

static char *GMT_CPT_master[GMT_N_CPT_MASTERS] = {
#include "gmt_cpt_masters.h"
};

/* Local functions needed for public functions below */

GMT_LOCAL void sincosdegree (double angle, double *sa, double *ca) {
	/* A careful sincosd on an angle that checks if we are at a
	 * multiple of 90 and hen makes sure we get ±1 or 0 there */
	int i_angle = rint (angle);
	double delta = fabs (angle - (double)i_angle);
	sincosd (angle, sa, ca);	/* Trig on the direction */
	if (delta > GMT_CONV4_LIMIT) return;	/* Too far from quarter circles */
	/* Now check which quarters */
	if (i_angle == 0 || i_angle == 360) *sa = 0.0, *ca = 1.0;
	else if (i_angle == 90 || i_angle == -270) *sa = 1.0, *ca = 0.0;
	else if (i_angle == 180 || i_angle == -180) *sa = 0.0, *ca = -1.0;
	else if (i_angle == 270 || i_angle == -90) *sa = -1.0, *ca = 0.0;
}

GMT_LOCAL int gmtsupport_parse_pattern_new (struct GMT_CTRL *GMT, char *line, struct GMT_FILL *fill) {
	/* Parse the fill pattern syntax: p|P<pattern>[+r<dpi>][+b<color>|-][+f<color>|-] */
	char *c = NULL;
	unsigned int first = 1;
	double fb_rgb[4];

	fill->dpi = irint (PSL_DOTS_PER_INCH_PATTERN);
	if ((c = strchr (line, '+'))) {	/* Got pattern modifiers */
		unsigned int pos = 0, uerr = 0;
		char p[GMT_BUFSIZ] = {""};
		while (gmt_getmodopt (GMT, 0, c, "bfr", &pos, p, &uerr) && uerr == 0) {	/* Looking for +b, +f, and +r */
			switch (p[0]) {
				case 'b':	/* Background color. Giving no argument means transparent [also checking for obsolete -] */
					if (p[1] == '\0' || p[1] == '-') {	/* Transparent background */
						fill->b_rgb[0] = fill->b_rgb[1] = fill->b_rgb[2] = -1,	fill->b_rgb[3] = 0;
						GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Background pixels set to transparent!\n");
					}
					else {
						if (gmt_getrgb (GMT, &p[1], fill->b_rgb)) {
							GMT_Report (GMT->parent, GMT_MSG_ERROR, "Background colorizing value %s not recognized!\n", &p[1]);
							return 2;
						}
						GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Background pixels set to colors %s\n", gmt_putrgb (GMT, fill->b_rgb));
					}
					fill->set_b_rgb = true;
					break;
				case 'f':	/* Foreground color. Giving no argument means transparent [also checking for obsolete -] */
					if (p[1] == '\0' || p[1] == '-') {	/* Transparent foreground */
						fill->f_rgb[0] = fill->f_rgb[1] = fill->f_rgb[2] = -1,	fill->f_rgb[3] = 0;
						GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Foreground pixels set to transparent!\n");
					}
					else {
						if (gmt_getrgb (GMT, &p[1], fill->f_rgb)) {
							GMT_Report (GMT->parent, GMT_MSG_ERROR, "Foreground colorizing value %s not recognized!\n", &p[1]);
							return 2;
						}
						GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Foreground pixels set to colors %s\n", gmt_putrgb (GMT, fill->f_rgb));
					}
					fill->set_f_rgb = true;
					break;
				case 'r':	/* Dots-per-inch resolution */
					if (p[1] == '-') {
						GMT_Report (GMT->parent, GMT_MSG_ERROR, "Pattern dpi %s is negative!\n", &p[1]);
						return 4;
					}
					fill->dpi = atoi (&p[1]);
					GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Pattern dpi set to %d\n", fill->dpi);
					break;
				default: break;
			}
		}
		if (fill->set_b_rgb && fill->set_f_rgb && fill->b_rgb[0] < 0.0 && fill->f_rgb[0] < 0.0) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Pattern fore- and back-ground pixels cannot both be transparent!\n");
			return (GMT_PARSE_ERROR);
		}
		if (uerr) return (GMT_PARSE_ERROR);
	}

	/* Copy name (or number) of pattern */
	if (c) c[0] = '\0';	/* Chop off the modifiers */
	if (!gmt_M_file_is_memory (&line[1]) && line[1] == '@') {	/* Must be a cache file */
		first = gmt_download_file_if_not_found (GMT, &line[1], 0) + 1;	/* Add one since we started at 1 */
	}
	strncpy (fill->pattern, &line[first], PATH_MAX-1);
	/* Attempt to convert to integer - will be 0 if not an integer and then we set it to -1 for a filename */
	fill->pattern_no = atoi (fill->pattern);
	if (fill->pattern_no == 0) {
		bool R_save = GMT->common.R.active[RSET];
		fill->pattern_no = -1;
		gmt_set_pad (GMT, 0); /* No padding */
		GMT->common.R.active[RSET] = false;

		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Pattern image is in file %s\n", fill->pattern);
		if ((fill->I = GMT_Read_Data (GMT->parent, GMT_IS_IMAGE, GMT_IS_FILE, GMT_IS_SURFACE, GMT_CONTAINER_AND_DATA, NULL, fill->pattern, NULL)) == NULL) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Unable to read image %s, no pattern set\n", fill->pattern);
			return (GMT_RUNTIME_ERROR);
		}
		GMT->common.R.active[RSET] = R_save;
		gmt_set_pad (GMT, GMT->parent->pad); /* Restore to GMT Defaults */
		fill->dim[0] = fill->I->header->n_columns;
		fill->dim[1] = fill->I->header->n_rows;
		if (fill->I->colormap) {	/* Got indexed color image, must build rgb stream instead */
			/* Convert colormap from integer to unsigned char and count colors */
			unsigned char *colormap = gmt_M_memory (GMT, NULL, 4*256, unsigned char);
			int64_t n, j, k;
			if (colormap == NULL) return (GMT_MEMORY_ERROR);
			n = gmt_unpack_rgbcolors (GMT, fill->I, colormap);	/* colormap will be RGBARGBA... */
			/* Expand 8-bit indexed image to 24-bit image */
			if ((fill->I->data = gmt_M_memory (GMT, fill->I->data, 3 * fill->I->header->nm, unsigned char)) == NULL)
				return (GMT_MEMORY_ERROR);
			n = 3 * fill->I->header->nm - 1;
			for (j = (int64_t)fill->I->header->nm - 1; j >= 0; j--) {
				k = 4 * fill->I->data[j] + 3;
				fill->I->data[n--] = colormap[--k], fill->I->data[n--] = colormap[--k], fill->I->data[n--] = colormap[--k];
			}
			gmt_M_free (GMT, colormap);
			fill->I->header->n_bands = 3;
			fill->I->header->size *= 3;
		}
		else if (fill->I->header->n_bands == 4) { /* RGBA image, with a color map */
			uint64_t n4, j4;
			for (j4 = n4 = 0; j4 < 4 * fill->I->header->nm; j4++) /* Reduce image from 32- to 24-bit */
				fill->I->data[n4++] = fill->I->data[j4++], fill->I->data[n4++] = fill->I->data[j4++], fill->I->data[n4++] = fill->I->data[j4++];
			fill->I->header->n_bands = 3;
		}
		fill->image = fill->I->data;
		fill->dim[2] = (fill->I->header->n_bands == 3) ? 24 : 8;
	}
	else
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Pattern number %d selected\n", fill->pattern_no);

	/* If inverse, simply flip the colors around */
	if (line[0] == 'p') {
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Pattern will be inverted\n");
		gmt_M_rgb_copy (fb_rgb, fill->f_rgb);
		gmt_M_rgb_copy (fill->f_rgb, fill->b_rgb);
		gmt_M_rgb_copy (fill->b_rgb, fb_rgb);
		gmt_M_bool_swap (fill->set_b_rgb, fill->set_f_rgb);
	}
	if (c) c[0] = '+';	/* Undo previous damage */
	return (0);
}

GMT_LOCAL int gmtsupport_parse_pattern_old (struct GMT_CTRL *GMT, char *line, struct GMT_FILL *fill) {
	/* Parse the old-style pattern syntax */
	int n, i, len, pos, end;
	unsigned int first = 1;
	char f, word[GMT_LEN256] = {""};
	double fb_rgb[4];

	/* We only get here if there are no +r,+f,+b strings or : in line, and we know line[1] is integer.
	 * However, if user gave -Gp1image.jpg then we will fail trying to parse as old.  So we do a check
	 * here if the argument can be accessed as a file and if so we call the new parser and return */

	if (!gmt_M_file_is_memory (&line[1]) && line[1] == '@') {	/* Must be a cache file */
		first = gmt_download_file_if_not_found (GMT, &line[1], 0) + 1;	/* Add one since we started at 1 */
	}
	if (!gmt_access (GMT, &line[first], F_OK))
		return (gmtsupport_parse_pattern_new (GMT, line, fill));

	n = sscanf (&line[1], "%d/%s", &fill->dpi, fill->pattern);
	if (n != 2) return (1);
	if (!gmt_M_file_is_memory (fill->pattern) && fill->pattern[0] == '@') {	/* Must be a cache file */
		first = gmt_download_file_if_not_found (GMT, fill->pattern, 0);
		/* Shuffle pattern name to skip the leading @ */
		for (i = 1; fill->pattern[i]; i++) fill->pattern[i-1] = fill->pattern[i];
		fill->pattern[i-1] = '\0';
	}
	/* Determine if there are colorizing options applied, i.e. [:F<rgb>B<rgb>] */
	len = (int)MIN(strlen (fill->pattern),PATH_MAX) - 1;
	for (i = 0, pos = GMT_NOTSET; i < len && fill->pattern[i] && pos == GMT_NOTSET; i++)
		if (i < len && fill->pattern[i] == ':' && (fill->pattern[i+1] == 'B' || fill->pattern[i+1] == 'F')) pos = i;	/* THe extra i < len is needed to defeat cppcheck confusion */
	if (pos != GMT_NOTSET) fill->pattern[pos] = '\0';
	fill->pattern_no = atoi (fill->pattern);
	if (fill->pattern_no == 0) fill->pattern_no = GMT_NOTSET;

	/* See if fore- and background colors are given */

	len = (int)strlen (line);
	for (i = 0, pos = GMT_NOTSET; line[i] && pos == GMT_NOTSET; i++) if (line[i] == ':' && i < len && (line[i+1] == 'B' || line[i+1] == 'F')) pos = i;
	pos++;

	if (pos > 0 && line[pos]) {	/* Gave colors */
		while (line[pos]) {
			f = line[pos++];
			if (line[pos] == '-')	/* Signal for transparency masking */
				fb_rgb[0] = fb_rgb[1] = fb_rgb[2] = -1,	fb_rgb[3] = 0;
			else {
				end = pos;
				while (line[end] && !(line[end] == 'F' || line[end] == 'B')) end++;
				strncpy (word, &line[pos], (size_t)(end - pos));
				word[end - pos] = '\0';
				if (gmt_getrgb (GMT, word, fb_rgb)) {
					GMT_Report (GMT->parent, GMT_MSG_ERROR, "Colorizing value %s not recognized!\n", word);
					return 2;
				}
			}
			if (f == 'f' || f == 'F')
				gmt_M_rgb_copy (fill->f_rgb, fb_rgb);
			else if (f == 'b' || f == 'B')
				gmt_M_rgb_copy (fill->b_rgb, fb_rgb);
			else {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Colorizing argument %c not recognized!\n", f);
				return 2;
			}
			while (line[pos] && !(line[pos] == 'F' || line[pos] == 'B')) pos++;
		}
	}

	/* If inverse, simply flip the colors around */
	if (line[0] == 'p') {
		gmt_M_rgb_copy (fb_rgb, fill->f_rgb);
		gmt_M_rgb_copy (fill->f_rgb, fill->b_rgb);
		gmt_M_rgb_copy (fill->b_rgb, fb_rgb);
	}
	return 0;
}

/*! . */
GMT_LOCAL int gmtsupport_parse_pattern (struct GMT_CTRL *GMT, char *line, struct GMT_FILL *fill) {
	int err;
	/* New syntax may have a modifier */
	if (gmt_found_modifier (GMT, line, "bfr") || !strchr(line, '/'))	/* Clearly new syntax */
		err = gmtsupport_parse_pattern_new (GMT, line, fill);
	else
		err = gmtsupport_parse_pattern_old (GMT, line, fill);
	fill->use_pattern = true;
	return (err);
}

/*! . */
GMT_LOCAL char *gmtsupport_get_userimagename (struct GMT_CTRL *GMT, char *line, char *cpt_path) {
	/* When a cpt is not in the current directory but given by relative or absolute path
	 * AND that cpt refers to a user pattern file (which may be a relative or absolute path)
	 * then unless that pattern file can be found we will try to prepend the path to the cpt
	 * file and see if the pattern can be found that way.
	 */

	int j, err;
	char *name = NULL, path[PATH_MAX+GMT_LEN256] = {""};
	struct GMT_FILL fill;
	if (!gmt_M_is_pattern (line)) return NULL;	/* Not an image specification */
	err = gmtsupport_parse_pattern (GMT, line, &fill);	/* See if this returns an error or not */
	if (err) return NULL;	/* Not a valid image specification */
	if (fill.pattern_no > 0) return NULL;	/* Not a user image */

	/* Here we do have a pattern specification */
	/* Try the user's default directories */
	if (gmtlib_getuserpath (GMT, fill.pattern, path))
		return NULL;	/* Yes, found so no problems */

	/* Now must put our faith in the cpt path and hope it has a path that can help us */
	if (cpt_path == NULL || cpt_path[0] == '<') {	/* Without an actual file path we must warn and bail */
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Not enough information to determine location of user pattern %s\n", fill.pattern);
		return NULL;
	}
	j = (int)strlen (cpt_path);
	while (j > 0 && cpt_path[j] != '/') j--;	/* Find last slash */
	if (j > 0) {	/* OK, got the cpt directory */
		cpt_path[j] = '\0';	/* Temporarily chop off the slash */
		sprintf (path, "%s/%s", cpt_path, fill.pattern);
		cpt_path[j] = '/';	/* Restore the slash */
		if (access (path, R_OK)) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Not enough information to determine location of user pattern %s\n", fill.pattern);
			return NULL;
		}
		name = strdup (path);	/* Must use this image name instead as it contains the full working path */
	}
	return (name);
}

/*! . */
void gmt_rgb_to_hsv (double rgb[], double hsv[]) {
	double diff;
	unsigned int i, imax = 0, imin = 0;

	/* This had checks using rgb value in doubles (e.g. (max_v == xr)), which failed always on some compilers.
	   Changed to integer logic: 2009-02-05 by RS.
	*/
	hsv[3] = rgb[3];	/* Pass transparency unchanged */
	for (i = 1; i < 3; i++) {
		if (rgb[i] > rgb[imax]) imax = i;
		if (rgb[i] < rgb[imin]) imin = i;
	}
	diff = rgb[imax] - rgb[imin];
	hsv[0] = 0.0;
	hsv[1] = (rgb[imax] == 0.0) ? 0.0 : diff / rgb[imax];
	hsv[2] = rgb[imax];
	if (hsv[1] == 0.0) return;	/* Hue is undefined */
	hsv[0] = 120.0 * imax + 60.0 * (rgb[(imax + 1) % 3] - rgb[(imax + 2) % 3]) / diff;
	if (hsv[0] < 0.0) hsv[0] += 360.0;
	if (hsv[0] > 360.0) hsv[0] -= 360.0;
}

/*! . */
void gmt_hsv_to_rgb (double rgb[], double hsv[]) {
	int i;
	double h, f, p, q, t, rr, gg, bb;

	rgb[3] = hsv[3];	/* Pass transparency unchanged */
	if (hsv[1] == 0.0)
		rgb[0] = rgb[1] = rgb[2] = hsv[2];
	else {
		h = hsv[0];
		while (h >= 360.0) h -= 360.0;
		while (h < 0.0) h += 360.0;
		h /= 60.0;
		i = irint (floor (h));
		f = h - i;
		p = hsv[2] * (1.0 - hsv[1]);
		q = hsv[2] * (1.0 - (hsv[1] * f));
		t = hsv[2] * (1.0 - (hsv[1] * (1.0 - f)));
		switch (i) {
			case 0:
				rr = hsv[2]; gg = t; bb = p;
				break;
			case 1:
				rr = q; gg = hsv[2]; bb = p;
				break;
			case 2:
				rr = p; gg = hsv[2]; bb = t;
				break;
			case 3:
				rr = p; gg = q; bb = hsv[2];
				break;
			case 4:
				rr = t; gg = p; bb = hsv[2];
				break;
			default:
				rr = hsv[2]; gg = p; bb = q;
				break;
		}

		rgb[0] = (rr < 0.0) ? 0.0 : rr;
		rgb[1] = (gg < 0.0) ? 0.0 : gg;
		rgb[2] = (bb < 0.0) ? 0.0 : bb;
	}
}

/*! . */
GMT_LOCAL void gmtsupport_rgb_to_cmyk (double rgb[], double cmyk[]) {
	/* Plain conversion; with default undercolor removal or blackgeneration */
	/* RGB is in 0-1, CMYK will be in 0-1 range */

	int i;

	cmyk[4] = rgb[3];	/* Pass transparency unchanged */
	cmyk[3] = 1.0 - MAX (rgb[0], MAX (rgb[1], rgb[2]));	/* Black K */
	if (doubleAlmostEqual (cmyk[3], 1.0))	/* All black */
		cmyk[0] = cmyk[1] = cmyk[2] = 0.0;
	else	/* Safe to divide by 1-k */
		for (i = 0; i < 3; i++) cmyk[i] = (1.0 - rgb[i] - cmyk[3]) / (1.0 - cmyk[3]);
	if (cmyk[3] < GMT_CONV8_LIMIT) cmyk[3] = 0.0;	/* Fix minor black round-off */

	/* To implement device-specific blackgeneration, supply lookup table K = BG[cmyk[3]] */

	/* To implement device-specific undercolor removal, supply lookup table u = UR[cmyk[3]] */
}

/*! . */
GMT_LOCAL void gmtsupport_cmyk_to_rgb (double rgb[], double cmyk[]) {
	/* Plain conversion; no undercolor removal or blackgeneration */
	/* CMYK is in 0-1, RGB will be in 0-1 range */

	int i;

	rgb[3] = cmyk[4];	/* Pass transparency unchanged */
	if (doubleAlmostEqual (cmyk[3], 1.0))	/* All black */
		rgb[0] = rgb[1] = rgb[2] = 0.0;
	else	/* Safe to divide by 1-k */
		for (i = 0; i < 3; i++) rgb[i] = (1.0 - cmyk[i]) * (1.0 - cmyk[3]);
}

/*! . */
GMT_LOCAL void gmtsupport_cmyk_to_hsv (double hsv[], double cmyk[]) {
	/* Plain conversion; no undercolor removal or blackgeneration */
	/* CMYK is in 0-1, RGB will be in 0-1 range */

	double rgb[4];

	gmtsupport_cmyk_to_rgb (rgb, cmyk);
	gmt_rgb_to_hsv (rgb, hsv);
}

/*!
 * Transform sRGB to CIE XYZ with the D65 white point
 *
 * Poynton, "Frequently Asked Questions About Color," page 10
 * Wikipedia: http://en.wikipedia.org/wiki/SRGB
 * Wikipedia: http://en.wikipedia.org/wiki/CIE_1931_color_space
 */
void gmt_rgb_to_xyz (double rgb[], double xyz[]) {
	double R, G, B;
	R = INVGAMMACORRECTION(rgb[0]);
	G = INVGAMMACORRECTION(rgb[1]);
	B = INVGAMMACORRECTION(rgb[2]);
	xyz[0] = 0.4123955889674142161*R  + 0.3575834307637148171*G + 0.1804926473817015735*B;
	xyz[1] = 0.2125862307855955516*R  + 0.7151703037034108499*G + 0.07220049864333622685*B;
	xyz[2] = 0.01929721549174694484*R + 0.1191838645808485318*G + 0.9504971251315797660*B;
}

/*! . */
void gmt_xyz_to_rgb (double rgb[], double xyz[]) {
	double R, G, B, min;
	R = ( 3.2406 * xyz[0] - 1.5372 * xyz[1] - 0.4986 * xyz[2]);
	G = (-0.9689 * xyz[0] + 1.8758 * xyz[1] + 0.0415 * xyz[2]);
	B = ( 0.0557 * xyz[0] - 0.2040 * xyz[1] + 1.0570 * xyz[2]);

	min = MIN(MIN(R, G), B);

	/* Force nonnegative values so that gamma correction is well-defined. */
	if (min < 0) {
		R -= min;
		G -= min;
		B -= min;
	}

	/* Transform from RGB to R'G'B' */
	rgb[0] = GAMMACORRECTION(R);
	rgb[1] = GAMMACORRECTION(G);
	rgb[2] = GAMMACORRECTION(B);
}

/*!
 * Convert CIE XYZ to CIE L*a*b* (CIELAB) with the D65 white point
 *
 * Wikipedia: http://en.wikipedia.org/wiki/Lab_color_space
 */

void gmt_xyz_to_lab (double xyz[], double lab[]) {
	double X, Y, Z;
	X = LABF( xyz[0] / WHITEPOINT_X );
	Y = LABF( xyz[1] / WHITEPOINT_Y );
	Z = LABF( xyz[2] / WHITEPOINT_Z );
	lab[0] = 116 * Y - 16;
	lab[1] = 500 * (X - Y);
	lab[2] = 200 * (Y - Z);
}

/*! . */
void gmt_lab_to_xyz (double xyz[], double lab[]) {
	xyz[0] = WHITEPOINT_X * LABINVF( (lab[0] + 16)/116 + lab[1]/500 );
	xyz[1] = WHITEPOINT_Y * LABINVF( (lab[0] + 16)/116 );
	xyz[2] = WHITEPOINT_Z * LABINVF( (lab[0] + 16)/116 - lab[2]/200 );
}

/*! . */
void gmt_rgb_to_lab (double rgb[], double lab[]) {
	/* RGB is in 0-1, LAB will be in ??? range */

	double xyz[3];

	gmt_rgb_to_xyz (rgb, xyz);
	gmt_xyz_to_lab (xyz, lab);
}

/*! . */
void gmt_lab_to_rgb (double rgb[], double lab[]) {
	double xyz[3];
	gmt_lab_to_xyz (xyz, lab);
	gmt_xyz_to_rgb (rgb, xyz);
}

/*! . */
GMT_LOCAL int gmtsupport_comp_double_asc (const void *p_1, const void *p_2) {
	/* Returns -1 if point_1 is < that point_2,
	   +1 if point_2 > point_1, and 0 if they are equal
	*/
	bool bad_1, bad_2;
	const double *point_1 = p_1, *point_2 = p_2;

	bad_1 = gmt_M_is_dnan ((*point_1));
	bad_2 = gmt_M_is_dnan ((*point_2));

	if (bad_1 && bad_2) return (0);
	if (bad_1) return (+1);
	if (bad_2) return (-1);

	if ((*point_1) < (*point_2)) return (-1);
	if ((*point_1) > (*point_2)) return (+1);
	return (0);
}

/*! . */
GMT_LOCAL int gmtsupport_comp_float_asc (const void *p_1, const void *p_2) {
	/* Returns -1 if point_1 is < that point_2,
	   +1 if point_2 > point_1, and 0 if they are equal
	*/
	bool bad_1, bad_2;
	const float *point_1 = p_1, *point_2 = p_2;

	bad_1 = gmt_M_is_fnan ((*point_1));
	bad_2 = gmt_M_is_fnan ((*point_2));

	if (bad_1 && bad_2) return (0);
	if (bad_1) return (+1);
	if (bad_2) return (-1);

	if ((*point_1) < (*point_2)) return (-1);
	if ((*point_1) > (*point_2)) return (+1);
	return (0);
}

/*! . */
GMT_LOCAL int gmtsupport_comp_ulong_asc (const void *p_1, const void *p_2) {
	/* Returns -1 if point_1 is < that point_2,
	   +1 if point_2 > point_1, and 0 if they are equal
	*/
	const uint64_t *point_1 = p_1, *point_2 = p_2;

	if ((*point_1) < (*point_2)) return (-1);
	if ((*point_1) > (*point_2)) return (+1);
	return (0);
}

/*! . */
GMT_LOCAL int gmtsupport_comp_long_asc (const void *p_1, const void *p_2) {
	/* Returns -1 if point_1 is < that point_2,
	   +1 if point_2 > point_1, and 0 if they are equal
	*/
	const int64_t *point_1 = p_1, *point_2 = p_2;

	if ((*point_1) < (*point_2)) return (-1);
	if ((*point_1) > (*point_2)) return (+1);
	return (0);
}

/*! . */
GMT_LOCAL int gmtsupport_comp_uint_asc (const void *p_1, const void *p_2) {
	/* Returns -1 if point_1 is < that point_2,
	   +1 if point_2 > point_1, and 0 if they are equal
	*/
	const unsigned int *point_1 = p_1, *point_2 = p_2;

	if ((*point_1) < (*point_2)) return (-1);
	if ((*point_1) > (*point_2)) return (+1);
	return (0);
}

/*! . */
GMT_LOCAL int gmtsupport_comp_int_asc (const void *p_1, const void *p_2) {
	/* Returns -1 if point_1 is < that point_2,
	   +1 if point_2 > point_1, and 0 if they are equal
	*/
	const int *point_1 = p_1, *point_2 = p_2;

	if ((*point_1) < (*point_2)) return (-1);
	if ((*point_1) > (*point_2)) return (+1);
	return (0);
}

/*! . */
GMT_LOCAL int gmtsupport_comp_ushort_asc (const void *p_1, const void *p_2) {
	/* Returns -1 if point_1 is < that point_2,
	   +1 if point_2 > point_1, and 0 if they are equal
	*/
	const unsigned short int *point_1 = p_1, *point_2 = p_2;

	if ((*point_1) < (*point_2)) return (-1);
	if ((*point_1) > (*point_2)) return (+1);
	return (0);
}

/*! . */
GMT_LOCAL int gmtsupport_comp_short_asc (const void *p_1, const void *p_2) {
	/* Returns -1 if point_1 is < that point_2,
	   +1 if point_2 > point_1, and 0 if they are equal
	*/
	const short int *point_1 = p_1, *point_2 = p_2;

	if ((*point_1) < (*point_2)) return (-1);
	if ((*point_1) > (*point_2)) return (+1);
	return (0);
}

/*! . */
GMT_LOCAL int gmtsupport_comp_uchar_asc (const void *p_1, const void *p_2) {
	/* Returns -1 if point_1 is < that point_2,
	   +1 if point_2 > point_1, and 0 if they are equal
	*/
	const unsigned char *point_1 = p_1, *point_2 = p_2;

	if ((*point_1) < (*point_2)) return (-1);
	if ((*point_1) > (*point_2)) return (+1);
	return (0);
}

/*! . */
GMT_LOCAL int gmtsupport_comp_char_asc (const void *p_1, const void *p_2) {
	/* Returns -1 if point_1 is < that point_2,
	   +1 if point_2 > point_1, and 0 if they are equal
	*/
	const char *point_1 = p_1, *point_2 = p_2;

	if ((*point_1) < (*point_2)) return (-1);
	if ((*point_1) > (*point_2)) return (+1);
	return (0);
}

/*! . */
GMT_LOCAL bool gmtsupport_check_irgb (int irgb[], double rgb[]) {
	if ((irgb[0] < 0 || irgb[0] > 255) || (irgb[1] < 0 || irgb[1] > 255) || (irgb[2] < 0 || irgb[2] > 255)) return (true);
	rgb[0] = gmt_M_is255 (irgb[0]);
	rgb[1] = gmt_M_is255 (irgb[1]);
	rgb[2] = gmt_M_is255 (irgb[2]);
	return (false);
}

/*! . */
GMT_LOCAL bool gmtsupport_check_rgb (double rgb[]) {
	return ((rgb[0] < 0.0 || rgb[0] > 1.0) || (rgb[1] < 0.0 || rgb[1] > 1.0) || (rgb[2] < 0.0 || rgb[2] > 1.0));
}

/*! . */
GMT_LOCAL bool gmtsupport_check_hsv (double hsv[]) {
	return ((hsv[0] < 0.0 || hsv[0] > 360.0) || (hsv[1] < 0.0 || hsv[1] > 1.0) || (hsv[2] < 0.0 || hsv[2] > 1.0));
}

/*! . */
GMT_LOCAL bool gmtsupport_check_cmyk (double cmyk[]) {
	unsigned int i;
	for (i = 0; i < 4; i++) cmyk[i] *= 0.01;
	for (i = 0; i < 4; i++) if (cmyk[i] < 0.0 || cmyk[i] > 1.0) return (true);
	return (false);
}

/*! . */
unsigned int gmt_char_count (char *txt, char c) {
	unsigned int i = 0, n = 0;
	while (txt[i]) if (txt[i++] == c) n++;
	return (n);
}

/*! . */
GMT_LOCAL bool gmtsupport_gethsv (struct GMT_CTRL *GMT, char *line, double hsv[]) {
	int n, i, count, irgb[3], c = 0;
	double rgb[4], cmyk[5];
	char buffer[GMT_LEN64] = {""}, *t = NULL;

	if (!line) { GMT_Report (GMT->parent, GMT_MSG_ERROR, "No argument given to gmtsupport_gethsv\n"); GMT->parent->error = GMT_PARSE_ERROR; return false; }
	if (!line[0]) return (false);	/* Nothing to do - accept default action */

	rgb[3] = hsv[3] = cmyk[4] = 0.0;	/* Default is no transparency */
	if (line[0] == '-') {
		hsv[0] = -1.0; hsv[1] = -1.0; hsv[2] = -1.0;
		return (false);
	}

	strncpy (buffer, line, GMT_LEN64-1);	/* Make local copy */
	if ((t = strstr (buffer, "@")) && strlen (t) > 1) {	/* User requested transparency via @<transparency> */
		double transparency = atof (&t[1]);
		if (transparency < 0.0 || transparency > 100.0)
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "Representation of transparency (%s) not recognized. Using default [0 or opaque].\n", t);
		else
			rgb[3] = hsv[3] = cmyk[4] = transparency / 100.0;	/* Transparency is in 0-1 range */
		t[0] = '\0';	/* Chop off transparency for the rest of this function */
	}

	if (buffer[0] == '#') {	/* #rrggbb */
		n = sscanf (buffer, "#%2x%2x%2x", (unsigned int *)&irgb[0], (unsigned int *)&irgb[1], (unsigned int *)&irgb[2]);
		if (n != 3 || gmtsupport_check_irgb (irgb, rgb)) return (true);
		gmt_rgb_to_hsv (rgb, hsv);
		return (false);
	}

	/* If it starts with a letter, then it could be a name */

	if (isalpha ((unsigned char) buffer[0])) {
		if ((n = (int)gmt_colorname2index (GMT, buffer)) < 0) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Colorname %s not recognized!\n", buffer);
			return (true);
		}
		for (i = 0; i < 3; i++) rgb[i] = gmt_M_is255 (gmt_M_color_rgb[n][i]);
		gmt_rgb_to_hsv (rgb, hsv);
		return (false);
	}

	/* Definitely wrong, at this point, is something that does not end in a number */

	if (strlen(buffer) < 1) return (true);	/* Nothing, which is bad */
	c = buffer[strlen(buffer)-1];
	if (!(isdigit (c) || c == '.')) return (true);

	count = (int)gmt_char_count (buffer, '/');

	if (count == 3) {	/* c/m/y/k */
		n = sscanf (buffer, "%lf/%lf/%lf/%lf", &cmyk[0], &cmyk[1], &cmyk[2], &cmyk[3]);
		if (n != 4 || gmtsupport_check_cmyk (cmyk)) return (true);
		gmtsupport_cmyk_to_hsv (hsv, cmyk);
		return (false);
	}

	if (count == 2) {	/* r/g/b */
		n = sscanf (buffer, "%d/%d/%d", &irgb[0], &irgb[1], &irgb[2]);
		if (n != 3 || gmtsupport_check_irgb (irgb, rgb)) return (true);
		gmt_rgb_to_hsv (rgb, hsv);
		return (false);
	}

	if (gmt_char_count (buffer, '-')  == 2) {		/* h-s-v */
		n = sscanf (buffer, "%lf-%lf-%lf", &hsv[0], &hsv[1], &hsv[2]);
		return (n != 3 || gmtsupport_check_hsv (hsv));
	}

	if (count == 0) {	/* gray */
		n = sscanf (buffer, "%d", &irgb[0]);
		irgb[1] = irgb[2] = irgb[0];
		if (n != 1 || gmtsupport_check_irgb (irgb, rgb)) return (true);
		gmt_rgb_to_hsv (rgb, hsv);
		return (false);
	}

	/* Get here if there is a problem */

	return (true);
}

/*! . */
GMT_LOCAL bool gmtsupport_is_pattern_old (char *word) {
	/* Returns true if the word is a pattern specification
	 * Old style:   P|p<dpi>/<pattern>[:B<color>[F<color>]]
	 */

	if (strchr (word, ':')) return (true);			/* Only patterns may have a colon */
	if (!(word[0] == 'P' || word[0] == 'p')) return false;	/* Patterns must start with P or p */
	if (!strchr (word, '/')) return (false);		/* Patterns separate dpi and pattern with a slash */
	/* Here we know we start with P|p and there is a slash - this can only be a pattern specification */
	return (true);
}

/*! . */
GMT_LOCAL bool gmtsupport_is_pattern_new (struct GMT_CTRL *GMT, char *word) {
	/* Returns true if the word is a pattern specification
	 * New style:   P|p<pattern>[+b<color>][+f<color>][+r<dpi>]
	 */
	char *c = NULL;
	int n;
	if ((c = strchr (word, '+')) && strchr ("bfr", c[1])) return (true);		/* Found +b, +f or +r */
	/* Here we have no modifiers at all */
	if (!(word[0] == 'P' || word[0] == 'p')) return false;	/* Patterns must start with P or p */
	/* Pattern without modifier must be an integer OR a valid file */
	if ((n = atoi (&word[1])) > 0 && n < PSL_N_PATTERNS) return (true);	/* Got a valid integer */
	/* Se if we can access the file */
	if (!gmt_access (GMT, &word[1], F_OK)) return (true);	/* Got a file that exists */
	return (false);	/* Not a pattern */
}

/*! . */
GMT_LOCAL bool gmtsupport_is_pattern (struct GMT_CTRL *GMT, char *word) {
	/* Returns true if the word is a pattern specification
	 * Old style:   P|p<dpi>/<pattern>[:B<color>[F<color>]]
	 * New style:   P|p<pattern>[+b<color>][+f<color>][+r<dpi>]
	 */

	bool val;
	/* New syntax may have a modifier or no slash AND no colon */
	if ((gmt_found_modifier (GMT, word, "bfr") || !strchr(word, '/')) && !strchr (word,':'))
		val = gmtsupport_is_pattern_new (GMT, word);
	else
		val = gmtsupport_is_pattern_old (word);
	return (val);
}

/*! . */
bool gmtlib_is_color (struct GMT_CTRL *GMT, char *word) {
	int i, k, n, n_hyphen = 0, n_slashes = 0;

	/* Returns true if we are sure the word is a color string - else false.
	 * color syntax is <r/g/b>|<h-s-v>|<c/m/y/k>|<colorname>[@transparency].
	 * NOTES: 1) <gray> is excluded since this function is called in places where
	 *  a single integer may be used for font size or pen width...
	 *        2) We are not checking if the values are kosher; just that they follow the pattern  */

	n = (int)strlen (word);
	if (n == 0) return (false);
	if (strchr (word, '@')) return (true);	/* Transparency means we have a color */

	if (word[0] == '#') return (true);		/* Probably #rrggbb */
	if (gmt_colorname2index (GMT, word) >= 0) return (true);	/* Valid color name */
	/* Skip dimension specifications with units c|i|m|p or a colon */
	if (strchr(word,'t')) return (false);		/* Got a t somewhere */
	if (strchr(word,':')) return (false);		/* Got a : somewhere */
	if (strchr(word,'c')) return (false);		/* Got a c somewhere */
	if (strchr(word,'i')) return (false);		/* Got an i somewhere */
	if (strchr(word,'m')) return (false);		/* Got a m somewhere */
	if (strchr(word,'p')) return (false);		/* Got a p somewhere */
	for (i = k = 0; word[i]; i++) if (word[i] == '/') n_slashes++;	/* Count slashes */
	if (n_slashes == 1 || n_slashes > 3) return (false);	/* No color spec takes only 1 slash or more than 3 */
	n--;
	/* Check for h-s-v as well.  Must find 2 hyphens */
	while (n >= 0 && (strchr ("/-.", word[n]) || isdigit ((int)word[n]))) {
		if (word[n] == '-') n_hyphen++;
		n--;	/* Wind down as long as we find -,.,/ or digits */
	}
	return ((n == -1 && (n_slashes || n_hyphen == 2)));	/* Hence <gray> will fail the slash test */
}

/*! . */
int gmt_getfonttype (struct GMT_CTRL *GMT, char *name) {
	unsigned int i;

	if (!name[0]) return (-1);
	if (!isdigit ((unsigned char) name[0])) {	/* Does not start with number. Try font name */
		int ret = GMT_NOTSET;
		for (i = 0; i < GMT->session.n_fonts && strcmp (name, GMT->session.font[i].name); i++);
		if (i < GMT->session.n_fonts) ret = i;
		return (ret);
	}
	if (!isdigit ((unsigned char) name[strlen(name)-1])) return (GMT_NOTSET);	/* Starts with digit, ends with something else: cannot be */
	return (atoi (name));
}

/*! . */
GMT_LOCAL bool gmtsupport_is_fontname (struct GMT_CTRL *GMT, char *word) {
	/* Returns true if the word is one of the named fonts */
	unsigned int i;

	if (!word[0]) return (false);
	for (i = 0; i < GMT->session.n_fonts && strcmp (word, GMT->session.font[i].name); i++);
	if (i == GMT->session.n_fonts) return (false);
	return (true);
}

/*! . */
GMT_LOCAL int gmtsupport_name2pen (char *name) {
	/* Return index into structure with pennames and width, for given name */

	int i, k;
	char Lname[GMT_LEN64] = {""};

	strncpy (Lname, name, GMT_LEN64-1);
	gmt_str_tolower (Lname);
	for (i = 0, k = GMT_NOTSET; k < 0 && i < GMT_N_PEN_NAMES; i++) if (!strcmp (Lname, GMT_penname[i].name)) k = i;
	/* Backwards compatibility for old, inappropriate input pen name "obese" */
	if (k == GMT_NOTSET && !strcmp (Lname, "obese")) k = GMT_N_PEN_NAMES - 1;

	return (k);
}

/*! . */
GMT_LOCAL int gmtsupport_pen2name (double width) {
	/* Return index into structure with pennames and width, for given width */

	int i, k;

	if (gmt_M_is_dnan (width)) return -2;	/* Pen width undefined */
	
	for (i = 0, k = GMT_NOTSET; k < 0 && i < GMT_N_PEN_NAMES; i++) if (gmt_M_eq (width, GMT_penname[i].width)) k = i;

	return (k);
}

/*! . */
GMT_LOCAL int gmtsupport_getpenwidth (struct GMT_CTRL *GMT, char *line, struct GMT_PEN *P) {
	int n;

	/* SYNTAX for pen width:  <floatingpoint>[p|i|c|m] or <name> [fat, thin, etc] */

	if (!line || !line[0]) return (GMT_NOERROR);	/* Nothing given, return */
	if ((line[0] == '.' && (line[1] >= '0' && line[1] <= '9')) || (line[0] >= '0' && line[0] <= '9')) {
		/* Pen thickness with optional unit at end */
		P->width = gmt_convert_units (GMT, line, GMT_PT, GMT_PT);
	}
	else if (!strcmp (line, "auto"))
		P->width = GMT->session.d_NaN;
	else {	/* Pen name was given - these refer to fixed widths in points */
		if ((n = gmtsupport_name2pen (line)) < 0) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Pen name %s not recognized!\n", line);
			return GMT_PARSE_ERROR;
		}
		P->width = GMT_penname[n].width;
	}
	return (GMT_NOERROR);
}

/*! . */
int gmtlib_getpenstyle (struct GMT_CTRL *GMT, char *line, struct GMT_PEN *P) {
	unsigned int i, n, pos, unit = GMT_PT, n_dash = 0;
	double width;
	char tmp[GMT_PEN_LEN] = {""}, string[GMT_BUFSIZ] = {""}, ptr[GMT_BUFSIZ] = {""};

	if (!line || !line[0]) return (GMT_NOERROR);	/* Nothing to do as no style given.  Note we do not reset any existing style here; use solid to do so */
	if (!strcmp (line, "solid")) {	/* Used to override any other default style */
		P->offset = 0.0;
		P->style[0] = '\0';
		 return (GMT_NOERROR);
	}
	if (gmt_M_is_dnan (P->width))  {	/* Must save style as given since we do not know the width yet */
		strncpy (P->style, line, GMT_PEN_LEN);	/* We will update style in gmt_set_undefined_defaults. */
		return (GMT_NOERROR);
	}
	if (!strncmp (line, "dashdot", 7U)) strcpy (line, "-.");	/* Accept "dashdot*" to mean -. */
	if (!strncmp (line, "dotdash", 7U)) strcpy (line, ".-");	/* Accept "dotdash*" to mean .- */
	if (!strncmp (line, "dash", 4U)) strcpy (line, "-");		/* Accept "dash*" to mean - */
	if (!strncmp (line, "dot", 3U)) strcpy (line, ".");		/* Accept "dot*" to mean . */
	if (!strcmp (line, "a")) {	/* Old GMT4 "a" style */
		if (gmt_M_compat_check (GMT, 4))
			GMT_Report (GMT->parent, GMT_MSG_COMPAT, "Pen-style \"a\" is deprecated, use \"dashed\" or \"-\" instead\n");
		else {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Bad pen-style %s\n", line);
			return GMT_PARSE_ERROR;
		}
		strcpy (line, "-");	/* Accepted GMT4 style "a" to mean - */
	}
	else if (!strcmp (line, "o")) {	/* Old GMT4 "o" style */
		if (gmt_M_compat_check (GMT, 4))
			GMT_Report (GMT->parent, GMT_MSG_COMPAT, "Pen-style \"o\" is deprecated, use \"dotted\" or \".\" instead\n");
		else {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Bad pen-style %s\n", line);
			return GMT_PARSE_ERROR;
		}
		strcpy (line, ".");	/* Accepted GMT4 style "a" to mean - */
	}
	n = (int)strlen (line) - 1;
	if (strchr (GMT_DIM_UNITS, line[n]))	/* Separate unit given to style string */
		unit = gmtlib_unit_lookup (GMT, line[n], GMT->current.setting.proj_length_unit);

	width = (P->width < GMT_CONV4_LIMIT) ? GMT_PENWIDTH : P->width;

	if (isdigit ((int)line[0])) {	/* Specified numeric pattern will start with an integer */
		unsigned int c_pos;

		for (i = 1, c_pos = 0; line[i] && c_pos == 0; i++) if (line[i] == ':') c_pos = i;
		if (c_pos == 0) {
			GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Pen style %s does not contain :<phase>. <phase> set to 0\n", line);
			P->offset = 0.0;
			sscanf (line, "%s", P->style);
		}
		else {
			line[c_pos] = ' ';
			sscanf (line, "%s %lf", P->style, &P->offset);
			line[c_pos] = ':';
		}
		for (i = 0; P->style[i]; i++) if (P->style[i] == '_') P->style[i] = ' ';

		/* Must convert given units to points */

		pos = 0;
		while ((gmt_strtok (P->style, " ", &pos, ptr))) {
			snprintf (tmp, GMT_PEN_LEN, "%g ", (atof (ptr) * GMT->session.u2u[unit][GMT_PT]));
			strcat (string, tmp);
			n_dash++;
		}
		string[strlen (string) - 1] = 0;
		if (strlen (string) >= GMT_PEN_LEN) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Pen attributes too long!\n");
			return GMT_PARSE_ERROR;
		}
		strncpy (P->style, string, GMT_PEN_LEN-1);
		P->offset *= GMT->session.u2u[unit][GMT_PT];
	}
	else  {	/* New way of building it up with - and . */
		P->style[0] = '\0';
		P->offset = 0.0;
		for (i = 0; line[i]; i++) {
			if (line[i] == '-') { /* Dash */
				snprintf (tmp, GMT_PEN_LEN, "%g %g ", 8.0 * width, 4.0 * width);
				strcat (P->style, tmp);
				n_dash += 2;
			}
			else if (line[i] == '.') { /* Dot */
				snprintf (tmp, GMT_PEN_LEN, "%g %g ", width, 4.0 * width);
				strcat (P->style, tmp);
				n_dash += 2;
			}
			else if (line[i] == ':') { 	/* :<phase> setting given at the end */
				i++;	/* Advance past the colon */
				P->offset = atof (line) * GMT->session.u2u[unit][GMT_PT];
				i = (unsigned int)(strlen (line) - 1);	/* So that when i++ happens at the end of the for loop we will exit */
			}
			else {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Pen attributes not using just - and . for dashes and dots. Offending character --> %c\n", line[i]);
				return GMT_PARSE_ERROR;
			}
		}
		P->style[strlen(P->style)-1] = '\0';	/* Chop off trailing space */
	}
	if (n_dash >= 11) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Pen attributes contain more than 11 items (limit for PostScript setdash operator)!\n");
		return GMT_PARSE_ERROR;
	}
	return (GMT_NOERROR);
}

/*! . */
GMT_LOCAL bool gmtsupport_is_penstyle (char *word) {
	int n;

	/* Returns true if we are sure the word is a style string - else false.
	 * style syntax is a|o|<pattern>[:<phase>]|<string made up of -|. only>
	 * Also recognized "dashed" for -, "dotted" for . as well as "solid" */

	n = (int)strlen (word);
	if (n == 0) return (false);

	if (!strncmp (word, "dotdash", 7U) || !strncmp (word, "dashdot", 7U) \
	    || !strncmp (word, "dash", 4U) || !strncmp (word, "dot", 3U) \
	    || !strncmp (word, "solid", 5U)) return (true);

	n--;
	if (strchr (GMT_DIM_UNITS, word[n])) n--;	/* Reduce length by 1; the unit character */
	if (n < 0) return (false);		/* word only contained a unit character? */
	if (n == 0) {
		if (word[0] == '-' || word[0] == 'a' || word[0] == '.' || word[0] == 'o') return (true);
		return (false);	/* No other 1-char style patterns possible */
	}
	if (strchr(word,'t')) return (false);	/* Got a t somewhere */
	if (strchr(word,':')) return (true);	/* Got <pattern>:<phase> */
	if (strchr(word,'_')) {	/* Got <pattern> without optional :<phase>, add :0 */
		strcat (word, ":0");
		return (true);
	}
	while (n >= 0 && (word[n] == '-' || word[n] == '.')) n--;	/* Wind down as long as we find - or . */
	return ((n == -1));	/* true if we only found -/., false otherwise */
}

/*! . */
GMT_LOCAL void gmtsupport_free_range  (struct GMT_CTRL *GMT, struct GMT_PALETTE_HIDDEN *H, struct GMT_LUT *S) {
	if (H->alloc_mode_text[GMT_CPT_INDEX_LBL]) gmt_M_str_free (S->label);
	if (H->alloc_mode_text[GMT_CPT_INDEX_KEY]) gmt_M_str_free (S->key);
	gmt_M_free (GMT, S->fill);
}

/*! . */
GMT_LOCAL void gmtsupport_copy_palette_hdrs (struct GMT_CTRL *GMT, struct GMT_PALETTE *P_to, struct GMT_PALETTE *P_from) {
	unsigned int hdr;
	P_to->header = NULL;
	if (P_from->n_headers == 0) return;	/* Nothing to do */
	/* Must duplicate the header records */
	P_to->n_headers = P_from->n_headers;
	if (P_to->n_headers && (P_to->header = gmt_M_memory (GMT, NULL, P_from->n_headers, char *)) == NULL)
		return;
	for (hdr = 0; hdr < P_from->n_headers; hdr++) P_to->header[hdr] = strdup (P_from->header[hdr]);
}

/*! Decode the optional +u|U<unit> and determine scales and +h[<z>] for hinge control */
GMT_LOCAL struct CPT_Z_SCALE *gmtsupport_cpt_parse (struct GMT_CTRL *GMT, char *file, unsigned int direction, unsigned int *hinge_mode, double *z_hinge) {
	/* CPT file arg is <file>[+h[<hinge>]][+u|U<unit>]
	 * The +h modifier is used to turn a soft hinge in a CPT to a hard hinge at the user-selected z-value [0]
	 * or to adjust the location of the hinge for an hard hinge CPT.
	 * Note: The +i<inc> modifier is dealt with and removed in those modules that support it, hence not checked here. */
	enum gmt_enum_units u_number;
	unsigned int mode = 0;
	char *c = NULL, *f = NULL, *m = NULL;
	struct CPT_Z_SCALE *Z = NULL;
	gmt_M_unused(direction);

	if ((f = gmt_strrstr (file, GMT_CPT_EXTENSION)))	/* Got a file with CPT extension, look from there on out */
		m = gmtlib_last_valid_file_modifier (GMT->parent, f, GMT_CPTFILE_MODIFIERS);
	else	/* Must use the full file name */ 
		m = gmtlib_last_valid_file_modifier (GMT->parent, file, GMT_CPTFILE_MODIFIERS);
	*hinge_mode = 0;	/* Default is no hinge modifier */
	if (m && (c = strstr (m, "+h"))) {	/* Gave hinge modifier, examine and set parameters */
		if (c[2]) {	/* Gave hinge value for soft hinge */
			if (gmt_verify_expectations (GMT, gmt_M_type (GMT, GMT_IN, GMT_Z), gmt_scanf (GMT, &c[2], gmt_M_type (GMT, GMT_IN, GMT_Z), z_hinge), &c[2])) {
				GMT_Report (GMT->parent, GMT_MSG_WARNING, "gmtsupport_cpt_parse: CPT hinge modifier %s was not successfully parsed and is ignored.\n", c);
			}
			else {	/* Parsed successfully, this turns a soft CPT hinge to a hard user hinge */
				c[0] = '\0';	/* Chop off the hinge specification from the file name */
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmtsupport_cpt_parse: CPT hard hinge was added at z = %s for file %s\n", &c[2], file);
				*hinge_mode = 1;
			}
		}
		else {	/* Accept zero as hard hinge value */
			*z_hinge = 0.0;
			*hinge_mode = 1;
			c[0] = '\0';	/* Chop off the hinge specification from the file name */
			GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmtsupport_cpt_parse: CPT CPT hard hinge was added at z = 0 for file %s\n", file);
		}
	}

	if (m == NULL || (c = gmtlib_cptfile_unitscale (GMT->parent, m)) == NULL) return NULL;	/* Did not find any +u|U modifiers */
	/* Here, c is assigned */
	mode = (c[1] == 'u') ? 0 : 1;
	u_number = gmtlib_get_unit_number (GMT, c[2]);		/* Convert char unit to enumeration constant for this unit */
	if (u_number == GMT_IS_NOUNIT) {
		GMT_Report (GMT->parent, GMT_MSG_WARNING, "CPT z unit specification %s was unrecognized (part of file name?) and is ignored.\n", c);
		return NULL;
	}
	/* Got a valid unit */
	if ((Z = gmt_M_memory (GMT, NULL, 1, struct CPT_Z_SCALE)) == NULL) return (NULL);
	Z->z_unit_to_meter = GMT->current.proj.m_per_unit[u_number];	/* Converts unit to meters */
	if (mode) Z->z_unit_to_meter = 1.0 / Z->z_unit_to_meter;	/* Wanted the inverse */
	Z->z_unit = u_number;	/* Unit ID */
	Z->z_adjust |= 1;		/* Says we have successfully parsed and readied the x/y scaling */
	Z->z_mode = mode;
	c[0] = '\0';	/* Chop off the unit specification from the file name */
	return (Z);
}

/*! . */
GMT_LOCAL int gmtsupport_find_cpt_hinge (struct GMT_CTRL *GMT, struct GMT_PALETTE *P) {
	/* Return the slice number where z_low' = 0 for a CPT with hinge and normalized z' = -1 to +1 */
	unsigned int k;
	if (!P->has_hinge) return GMT_NOTSET;	/* Does not have any hinge */
	for (k = 0; k < P->n_colors; k++) if (doubleAlmostEqualZero (0.0, P->data[k].z_low)) {
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Found CPT hinge at z' = 0 for slice k = %u!\n", k);
		return (int)k;
	}
	GMT_Report (GMT->parent, GMT_MSG_ERROR, "Hinge requested but no hinge at z' = 0 was found in this CPT\n");
	return GMT_PARSE_ERROR;
}

/*! . */
GMT_LOCAL void gmtsupport_cpt_z_scale (struct GMT_CTRL *GMT, struct GMT_PALETTE *P, struct CPT_Z_SCALE *Z, unsigned int direction) {
	unsigned int k;
	double scale = 1.0;
	struct GMT_PALETTE_HIDDEN *PH = gmt_get_C_hidden (P);
	/* Apply the scaling of z as given by the header's z_* settings.
	 * After reading a cpt it will have z in meters.
	 * Before writing a cpt, it may have units changed back to original units
	 * or scaled to another set of units */

	if (direction == GMT_IN) {
		if (Z) {
			PH->z_adjust[GMT_IN] = Z->z_adjust; PH->z_unit[GMT_IN] = Z->z_unit;
			PH->z_mode[GMT_IN] = Z->z_mode; PH->z_unit_to_meter[GMT_IN] = Z->z_unit_to_meter;
		}
		if (PH->z_adjust[GMT_IN] == 0) return;	/* Nothing to do */
		if (PH->z_adjust[GMT_IN] & 2)  return;	/* Already scaled them */
		scale = PH->z_unit_to_meter[GMT_IN];	/* To multiply all z-related entries in the CPT */
		PH->z_adjust[GMT_IN] = 2;	/* Now the cpt is ready for use and in meters */
		if (PH->z_mode[GMT_IN])
			GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Input CPT z unit was converted from meters to %s after reading.\n", GMT->current.proj.unit_name[PH->z_unit[GMT_IN]]);
		else
			GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Input CPT z unit was converted from %s to meters after reading.\n", GMT->current.proj.unit_name[PH->z_unit[GMT_IN]]);
	}
	else if (direction == GMT_OUT) {	/* grid x/y are assumed to be in meters */
		if (Z) {PH->z_adjust[GMT_OUT] = Z->z_adjust; PH->z_unit[GMT_OUT] = Z->z_unit; PH->z_mode[GMT_OUT] = Z->z_mode; PH->z_unit_to_meter[GMT_OUT] = Z->z_unit_to_meter; }
		if (PH->z_adjust[GMT_OUT] & 1) {	/* Was given a new unit for output */
			scale = 1.0 / PH->z_unit_to_meter[GMT_OUT];
			PH->z_adjust[GMT_OUT] = 2;	/* Now we are ready for writing */
			if (PH->z_mode[GMT_OUT])
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Output CPT z unit was converted from %s to meters before writing.\n", GMT->current.proj.unit_name[PH->z_unit[GMT_OUT]]);
			else
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Output CPT z unit was converted from meters to %s before writing.\n", GMT->current.proj.unit_name[PH->z_unit[GMT_OUT]]);
		}
		else if (PH->z_adjust[GMT_IN] & 2) {	/* Just undo old scaling */
			scale = 1.0 / PH->z_unit_to_meter[GMT_IN];
			PH->z_adjust[GMT_IN] -= 2;	/* Now it is back to where we started */
			if (PH->z_mode[GMT_OUT])
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Output CPT z unit was reverted back to %s from meters before writing.\n", GMT->current.proj.unit_name[PH->z_unit[GMT_IN]]);
			else
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Output CPT z unit was reverted back from meters to %s before writing.\n", GMT->current.proj.unit_name[PH->z_unit[GMT_IN]]);
		}
	}
	/* If we got here we must scale the CPT's z-values */
	for (k = 0; k < P->n_colors; k++) {
		P->data[k].z_high *= scale;
		P->data[k].z_low  *= scale;
		P->data[k].i_dz   /= scale;
	}
}

/*! . */
GMT_LOCAL void gmtsupport_truncate_cpt_slice (struct GMT_LUT *S, bool do_hsv, double z_cut, int side) {
	/* Interpolate this slice to the new low or high value, depending on side */
	double f = (z_cut - S->z_low) * S->i_dz, hsv[4], rgb[4];
	unsigned int k;
	if (do_hsv) {	/* Interpolation in HSV space */
		for (k = 0; k < 4; k++) hsv[k] = S->hsv_low[k] + S->hsv_diff[k] * f;
		gmt_hsv_to_rgb (rgb, hsv);
	}
	else {	/* Interpolation in RGB space */
		for (k = 0; k < 4; k++) rgb[k] = S->rgb_low[k] + S->rgb_diff[k] * f;
		gmt_rgb_to_hsv (rgb, hsv);
	}
	if (side == -1) {
		gmt_M_memcpy (S->hsv_low, hsv, 4, double);
		gmt_M_memcpy (S->rgb_low, rgb, 4, double);
		S->z_low = z_cut;
	}
	else {	/* Last slice */
		gmt_M_memcpy (S->hsv_high, hsv, 4, double);
		gmt_M_memcpy (S->rgb_high, rgb, 4, double);
		S->z_high = z_cut;
	}
	/* Recompute differences used in gmt_get_rgb_from_z */
	for (k = 0; k < 4; k++) S->rgb_diff[k] = S->rgb_high[k] - S->rgb_low[k];
	for (k = 0; k < 4; k++) S->hsv_diff[k] = S->hsv_high[k] - S->hsv_low[k];
	/* Recompute inverse stepsize */
	S->i_dz = 1.0 / (S->z_high - S->z_low);
}

void gmt_explain_cpt_output (struct GMTAPI_CTRL *API, char option) {
	/* Display usage synopsis for -F cpt output/categorical option in makecpt/grd2cpt */

	GMT_Usage (API, 1, "\n-%c%s", option, GMT_COLORMODES_OPT);
	GMT_Usage (API, -2, "Select the color model for output [Default uses the input model]:");
	GMT_Usage (API, 3, "R: Output r/g/b or colornames.");
	GMT_Usage (API, 3, "c: Output c/m/y/k.");
	GMT_Usage (API, 3, "g: Output gray value (Will apply the YIQ if not a gray value).");
	GMT_Usage (API, 3, "h: Output h-s-v.");
	GMT_Usage (API, 3, "r: Output r/g/b only.");
	GMT_Usage (API, 3, "x: Output hex #rrggbb only.");
	GMT_Usage (API, -2, "Two modifiers control generation of categorical labels:");
	GMT_Usage (API, 3, "+c Output a discrete CPT in categorical CPT format. "
		"The <label>, if appended, sets the labels for each category. It may be a "
		"comma-separated list of category names, or <start>[-] where we automatically build "
		"labels from <start> (a letter or an integer). Append - to build range labels <start>-<start+1>.");
	GMT_Usage (API, 3, "+k Set categorical keys rather than numerical values. "
		"<keys> may be a file with one key per line or a comma-separated list of keys. "
		"If <keys> is a single letter then we build sequential alphabetical keys from that letter. "
		"If number of categories is 12 and label is M then we auto-create month name labels, and "
		"if it is 7 and label is D then we auto-create weekday name labels.");
}

void gmt_explain_cpt_input (struct GMTAPI_CTRL *API, char option) {
	/* Display CPT usage for grd* plotters */

	GMT_Usage (API, 1, "\n-%c%s", option, CPT_OPT_ARGS);
	GMT_Usage (API, -2, "Color palette file to convert grid values to colors, provided by one of three ways:");
	GMT_Usage (API, 3, "%s Name one of the master CPTs (no extension) [%s].", GMT_LINE_BULLET, API->GMT->current.setting.cpt);
	GMT_Usage (API, 3, "%s Name a local regular CPTs (with extension).", GMT_LINE_BULLET);
	GMT_Usage (API, 3, "%s Specify <color1>,<color2>[,<color3>,...] to build a linear continuous "
		"CPT to automatically assign continuous colors over the grid data range.", GMT_LINE_BULLET);
	GMT_Usage (API, -2, "A few modifiers control generation of the active CPT:");
	GMT_Usage (API, 3, "+h Enable a soft hinge in your master CPT. Append <hinge> to change its value.");
	GMT_Usage (API, 3, "+i Append <dz> to quantize the grid range [Default uses the exact grid range].");
	GMT_Usage (API, 3, "+u Scale CPT z-values from another <unit> to meters.");
	GMT_Usage (API, 3, "+U Scale CPT z-values from meters to another <unit>.");
	GMT_Usage (API, 3, "+s Append <fname> to save the generated CPT to file.");
	GMT_Usage (API, -2, "Note: For converting units with +u|U, see units %s.", GMT_LEN_UNITS2_DISPLAY);
}

int gmt_prepare_categorical_cpt (struct GMT_CTRL *GMT, char *label, char *key, struct GMT_PALETTE *Pout) {
		bool got_key_file = (key && !gmt_access (GMT, key, R_OK));	/* Want categorical labels read from file */
		unsigned int ns = 0;
		Pout->categorical = GMT_CPT_CATEGORICAL_VAL;
		if (label || (key && !got_key_file)) {	/* Want auto-categorical labels appended to each CPT record */
			char **Plabel = gmt_cat_cpt_strings (GMT, (label) ? label : key, Pout->n_colors, &ns);
			for (unsigned int k = 0; k < MIN (Pout->n_colors, ns); k++) {
				if (Pout->data[k].label) gmt_M_str_free (Pout->data[k].label);
				if (Plabel[k]) Pout->data[k].label = Plabel[k];	/* Now the job of the CPT to free these strings */
			}
			gmt_M_free (GMT, Plabel);	/* But the master array can go */
		}
		if (key) {	/* Want categorical labels */
			char **keys = NULL;
			if (got_key_file) {	/* Got a file with category keys */
				ns = gmt_read_list (GMT, key, &keys);
				if (ns < Pout->n_colors) {
					GMT_Report (GMT->parent, GMT_MSG_ERROR, "The categorical keys file %s had %d entries but CPT has %d categories\n", key, ns, Pout->n_colors);
					return (GMT_RUNTIME_ERROR);
				}
				else if (ns > Pout->n_colors)
					GMT_Report (GMT->parent, GMT_MSG_WARNING, "The categorical keys file %s had %d entries but only %d are needed - skipping the extra keys\n", key, ns, Pout->n_colors);
			}
			else	/* Got comma-separated keys */
				keys = gmt_cat_cpt_strings (GMT, key, Pout->n_colors, &ns);
			for (unsigned int k = 0; k < MIN (Pout->n_colors, ns); k++) {
				if (Pout->data[k].key) gmt_M_str_free (Pout->data[k].key);
				if (k < ns && keys[k]) {
					Pout->data[k].key = keys[k];	/* Now the job of the CPT to free these strings */
					if (Pout->data[k].label) gmt_M_str_free (Pout->data[k].label);
					Pout->data[k].label = strdup (keys[k]);
				}
			}
			gmt_M_free (GMT, keys);	/* But the master array can go */
			Pout->categorical = GMT_CPT_CATEGORICAL_KEY;
		}
		return (GMT_NOERROR);
}

bool gmt_consider_current_cpt (struct GMTAPI_CTRL *API, bool *active, char **arg) {
	/* Modern mode only: Detect if no CPT is given but -C was set.
	 * If -C[+u|U<arg>] is given (i.e., no cpt) then we take that to mean
	 * we want to use the current CPT.  If no current CPT exist then we do nothing
	 * and the module with fail or create a CPT as needed. */
	char *cpt = NULL;
	bool ret = true;

	if (API->GMT->current.setting.run_mode == GMT_CLASSIC) return false;	/* No such thing in classic mode */
	if (!(*active)) return false;		/* Did not give that option so nothing to do */
	if (arg == NULL) return false;	/* No text pointer to work with */

	if (gmt_M_cpt_mod (*arg)) {	/* Gave modifiers for a unit change) */
		char string[PATH_MAX] = {""};
		if ((cpt = gmt_get_current_item (API->GMT, "cpt", false)) == NULL) return false;	/* No current CPT */
		snprintf (string, PATH_MAX, "%s%s", cpt, *arg);	/* Append the modifiers to the current CPT name */
		gmt_M_str_free (cpt);
		gmt_M_str_free (*arg);
		*arg = strdup (string);		/* Pass back the name of the current CPT with modifiers */
	}
	else if (*arg == NULL) {	/* Noting given */
		if ((cpt = gmt_get_current_item (API->GMT, "cpt", false)) == NULL) return false;	/* No current CPT */
		*arg = cpt;		/* Pass back the name of the current CPT */
	}
	else /* Got something already */
		ret = false;
	return ret;
}

unsigned gmt_parse_interpolant (struct GMTAPI_CTRL *API, char *arg, unsigned int *mode, unsigned int *type, double *fit) {
	/* Do the parsing of the -F interpolant option using in sample1d and grdinterpolate */
	unsigned int n_errors = 0;

	*type = *mode = 0;	*fit = 0.0;
	switch (arg[0]) {
		case 'l':
			*mode = GMT_SPLINE_LINEAR;
			break;
		case 'a':
			*mode = GMT_SPLINE_AKIMA;
			break;
		case 'c':
			*mode = GMT_SPLINE_CUBIC;
			break;
		case 'n':
			*mode = GMT_SPLINE_NN;
			break;
		case 'e':
			*mode = GMT_SPLINE_STEP;
			break;
		case 's':
			*mode = GMT_SPLINE_SMOOTH;
			if (arg[1])
				*fit = atof (&arg[1]);
			else {
				GMT_Report (API, GMT_MSG_ERROR, "Option -Fs: No fit parameter given\n");
				n_errors++;
			}
			break;
		default:
			GMT_Report (API, GMT_MSG_ERROR, "Option -F: Bad interpolant selector %c\n", arg[0]);
			n_errors++;
			break;
	}
	if (strstr (&arg[1], "+d1")) *type = 1;	/* Want first derivative */
	else if (strstr (&arg[1], "+d2")) *type = 2;	/* Want second derivative */
	else if (strstr (&arg[1], "+1")) *type = 1;	/* Want first derivative (backwards compatibility) */
	else if (strstr (&arg[1], "+2")) *type = 2;	/* Want second derivative (backwards compatibility) */
	return (n_errors);
}

void gmt_explain_interpolate_mode (struct GMTAPI_CTRL *API) {
	/* Display usage synopsis for -F interpolant option */
	char type[3] = {'l', 'a', 'c'};

	GMT_Usage (API, 1, "\n-F%s", GMT_INTERPOLANT_OPT);
	GMT_Usage (API, -2, "Set the 1-D interpolation mode.  Choose from:");
	GMT_Usage (API, 3, "a: Akima spline interpolation.");
	GMT_Usage (API, 3, "c: Cubic spline interpolation.");
	GMT_Usage (API, 3, "e: Step-up interpolation (to next value).");
	GMT_Usage (API, 3, "l: Linear interpolation.");
	GMT_Usage (API, 3, "n: No interpolation (nearest point).");
	GMT_Usage (API, 3, "s: Smooth spline interpolation (append fit parameter <p>).");
	GMT_Usage (API, -2, "Optionally, request a spline derivative via a modifier:");
	GMT_Usage (API, 3, "+d Append 1 for 1st derivative or 2 for 2nd derivative.");
	GMT_Usage (API, -2, "[Default is -F%c].", type[API->GMT->current.setting.interpolant]);
}

unsigned int gmt_set_interpolate_mode (struct GMT_CTRL *GMT, unsigned int mode, unsigned int type) {
	/* Convenience function that hides away the embedding of mode and type via the GMT_SPLINE_SLOPE factor */
	gmt_M_unused (GMT);
	return (mode + GMT_SPLINE_SLOPE * type);
}

/*! . */
GMT_LOCAL double gmtsupport_csplint (struct GMT_CTRL *GMT, double *x, double *y, double *c, double xp, uint64_t klo) {
	uint64_t khi;
	double h, ih, b, a, yp;
	gmt_M_unused(GMT);

	khi = klo + 1;
	h = x[khi] - x[klo];
	ih = 1.0 / h;
	a = (x[khi] - xp) * ih;
	b = (xp - x[klo]) * ih;
	yp = a * y[klo] + b * y[khi] + ((a*a*a - a) * c[klo] + (b*b*b - b) * c[khi]) * (h*h) / 6.0;

	return (yp);
}

/*! . */
GMT_LOCAL double gmtsupport_csplintslp (struct GMT_CTRL *GMT, double *x, double *y, double *c, double xp, uint64_t klo) {
	/* As gmtsupport_csplint but returns the first derivative instead */
	uint64_t khi;
	double h, ih, b, a, dypdx;
	gmt_M_unused(GMT);

	khi = klo + 1;
	h = x[khi] - x[klo];
	ih = 1.0 / h;
	a = (x[khi] - xp) * ih;
	b = (xp - x[klo]) * ih;
	dypdx = ih * (y[khi] - y[klo]) + ((3.0*b*b - 1.0) * c[khi] - (3.0*a*a - 1.0) * c[klo]) * h / 6.0;

	return (dypdx);
}

/*! . */
GMT_LOCAL double gmtsupport_csplintcurv (struct GMT_CTRL *GMT, double *x, double *c, double xp, uint64_t klo) {
	/* As gmtsupport_csplint but returns the 2nd derivative instead */
	uint64_t khi;
	double h, ih, b, a, d2ypdx2;
	gmt_M_unused(GMT);

	khi = klo + 1;
	h = x[khi] - x[klo];
	ih = 1.0 / h;
	a = (x[khi] - xp) * ih;
	b = (xp - x[klo]) * ih;
	d2ypdx2 = -(b * c[khi] + a * c[klo]);

	return (d2ypdx2);
}

/*! . */
int gmtlib_smooth_spline (struct GMT_CTRL *GMT, double *x, double *y, double *w, double p, uint64_t n, int deriv, double *a) {
	/* Implements a smoothing splines as per Lancaster & Salkauskas [1980].
	 * w is optional weights or NULL, p is fit parameter. The x values are monotonic */
	int error;
	uint64_t n3 = n - 3, n2 = n - 2, n1 = n - 1, k, kk, kkt;
	double ip = 1.0 / p, sum_w = 0;
	double *D = NULL, *Dt = NULL, *B = NULL, *K = NULL, *Q = NULL;
	double *lambda = NULL, *dtau = NULL, *inv_dtau = NULL, *c = NULL, *s = NULL;

	/* Create the inverse lambda diagonal vector (assume w[k] = sigma_k) */
	if ((lambda = gmt_M_memory (GMT, NULL, n, double)) == NULL) return (GMT_RUNTIME_ERROR);
	for (k = 0; k < n; k++) {
		lambda[k] = (w == NULL) ? 1.0 : w[k] * w[k];
		sum_w += lambda[k];
	}
	for (k = 0; k < n; k++) {
		lambda[k] /= sum_w;	/* Normalize weights to sum to 1 */
		lambda[k] *= ip;
	}
	/* Create dtau and inv_dtau vectors */
	if ((dtau = gmt_M_memory (GMT, NULL, n1, double)) == NULL) return (GMT_RUNTIME_ERROR);
	if ((inv_dtau = gmt_M_memory (GMT, NULL, n1, double)) == NULL) return (GMT_RUNTIME_ERROR);
	for (k = 0; k < n1; k++) {
		dtau[k] = x[k+1] - x[k];
		inv_dtau[k] = 1.0 / dtau[k];
	}
	/* Create B matrix */
	if ((B = gmt_M_memory (GMT, NULL, n2*n2, double)) == NULL) return (GMT_RUNTIME_ERROR);
	for (k = 0; k < n2; k++) {	/* For rows 0 to n-3, a total of n-2 rows in B */
		kk = k * n2 + k;	/* Diagonal index */
		B[kk] = (dtau[k] + dtau[k+1]) / 3.0;
		if (k > 0) B[kk-1] = dtau[k] / 6.0;	/* All but first row has entry to left of diagonal */
		if (k < n3) B[kk+1] = dtau[k+1] / 6.0;	/* All but last row has entry to right of diagonal */
	}

	/* Create D and Dt matrix and temp matrix K = inv_lambd * Dt */
	if ((D = gmt_M_memory (GMT, NULL, n2*n, double)) == NULL) return (GMT_RUNTIME_ERROR);
	if ((Dt = gmt_M_memory (GMT, NULL, n*n2, double)) == NULL) return (GMT_RUNTIME_ERROR);
	if ((K = gmt_M_memory (GMT, NULL, n2*n, double)) == NULL) return (GMT_RUNTIME_ERROR);
	for (k = 0; k < n2; k++) {	/* For rows 0 to n-3, a total of n-2 rows in D */
		kk = k * n + k;	/* Diagonal index in D */
		kkt = k * n2 + k;	/* Diagonal index in transpose */
		D[kk] = Dt[kkt] = inv_dtau[k];
		D[kk+1] = Dt[kkt+n2] = -(inv_dtau[k] + inv_dtau[k+1]);
		D[kk+2] = Dt[kkt+2*n2] = inv_dtau[k+1];
		K[kkt] = Dt[kkt] * lambda[k];
		K[kkt+n2] = Dt[kkt+n2] * lambda[k+1];
		K[kkt+2*n2] = Dt[kkt+2*n2] * lambda[k+2];
	}
	/* Need to compute Q = D * K */
	if ((Q = gmt_M_memory (GMT, NULL, n2*n2, double)) == NULL) return (GMT_RUNTIME_ERROR);
	gmt_matrix_matrix_mult (GMT, D, K, n2, n, n2, Q);
	/* Now add B to Q */
	gmt_matrix_matrix_add (GMT, Q, B, n2, n2, Q);
	/* Set c = D * y */
	if ((c = gmt_M_memory (GMT, NULL, n, double)) == NULL) return (GMT_RUNTIME_ERROR);
	gmt_matrix_matrix_mult (GMT, D, y, n2, n, 1U, c);
	/* Solve Q*x = c, with x returned in c; these are the curvatures (s" in the notes) */
	error = gmt_gauss (GMT, Q, c, n2, n2, true);
	if (error) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Gauss returns error code %d\n", error);
		error = GMT_RUNTIME_ERROR;
		goto END_IT;
	}
	/* Set Q = K * c  which is a vector of length n */
	gmt_matrix_matrix_mult (GMT, K, c, n, n2, 1, Q);
	/* Solution for s = y - Q as in the notes */
	if ((s = gmt_M_memory (GMT, NULL, n, double)) == NULL) return (GMT_RUNTIME_ERROR);
	for (k = 0; k < n; k++) s[k] = y[k] - Q[k];
	/* Adjust c (n-2 items) by adding the first and last c = conditions */
	for (k = n2; k > 1; k--) c[k] = c[k-1];
	c[0] = c[n-1] = 0.0;	/* THe natural BCs */
	/* Now build the coefficient matrix a (5.33) with y = s and c = s" */
	for (k = kk = 0; k < n1; k++) {	/* The internal segments */
		a[kk++] = c[k] * inv_dtau[k] / 6.0;
		a[kk++] = c[k+1] * inv_dtau[k] / 6.0;
		a[kk++] = s[k] * inv_dtau[k] - c[k] * dtau[k] / 6.0;
		a[kk++] = s[k+1] * inv_dtau[k] - c[k+1] * dtau[k] / 6.0;
	}
	if (deriv == 1) {	/* Take first derivative and update coefficients */
		for (k = kk = 0; k < n1; k++) {	/* The internal segments */
			a[kk++] *= -3;
			a[kk++] *= +3;
			a[kk] = a[kk+1] - a[kk];
			kk++;
			a[kk++] = 0.0;
		}
	}
	else if (deriv == 2) {	/* Take second derivative and update coefficients */
		for (k = kk = 0; k < n1; k++) {	/* The internal segments */
			a[kk++] *= 6;
			a[kk++] *= 6;
			a[kk++] = 0.0;
			a[kk++] = 0.0;
		}
	}
END_IT:
	gmt_M_free (GMT, c);
	gmt_M_free (GMT, s);
	gmt_M_free (GMT, lambda);
	gmt_M_free (GMT, dtau);
	gmt_M_free (GMT, inv_dtau);
	gmt_M_free (GMT, Q);
	gmt_M_free (GMT, K);
	gmt_M_free (GMT, D);
	gmt_M_free (GMT, Dt);
	gmt_M_free (GMT, B);

	return (error);
}

/*! . */
GMT_LOCAL int gmtsupport_intpol_sub (struct GMT_CTRL *GMT, double *x, double *y, double *w, uint64_t n, uint64_t m, double *u, double *v, double p, int mode) {
	/* Does the main work of interpolating a section that has no NaNs */
	uint64_t i, j;
	int err_flag = 0, spline_mode = mode % GMT_SPLINE_SLOPE, deriv = mode / GMT_SPLINE_SLOPE;
	double dx, dx1, dx2, x_min, x_max, *c = NULL;

	/* Set minimum and maximum */

	if (spline_mode >= GMT_SPLINE_NN) {
		x_min = (3*x[0] - x[1]) / 2;
		x_max = (3*x[n-1] - x[n-2]) / 2;
	}
	else {
		x_min = x[0]; x_max = x[n-1];
	}

	/* Allocate memory for spline factors */

	if (spline_mode == GMT_SPLINE_AKIMA) {	/* Akima's spline */
		if ((c = gmt_M_memory (GMT, NULL, 3*n, double)) == NULL) return (GMT_RUNTIME_ERROR);
		err_flag = gmtlib_akima (GMT, x, y, n, c);
	}
	else if (spline_mode == GMT_SPLINE_CUBIC) {	/* Natural cubic spline */
		if ((c = gmt_M_memory (GMT, NULL, 3*n, double)) == NULL) return (GMT_RUNTIME_ERROR);
		err_flag = gmtlib_cspline (GMT, x, y, n, c);
	}
	else if (spline_mode == GMT_SPLINE_SMOOTH) {	/* Smoothing spline */
		if ((c = gmt_M_memory (GMT, NULL, 4*n, double)) == NULL) return (GMT_RUNTIME_ERROR);
		err_flag = gmtlib_smooth_spline (GMT, x, y, w, p, n, deriv, c);
	}
	if (err_flag != 0) {
		gmt_M_free (GMT, c);
		return (err_flag);
	}

	/* Compute the interpolated values from the coefficients */

	j = 0;
	for (i = 0; i < m; i++) {
		if (u[i] < x_min || u[i] > x_max) {	/* Desired point outside data range */
			if (GMT->current.setting.extrapolate_val[0] == GMT_EXTRAPOLATE_NONE) {
				v[i] = GMT->session.d_NaN;
				continue;
			}
			else if (GMT->current.setting.extrapolate_val[0] == GMT_EXTRAPOLATE_CONSTANT) {
				v[i] = GMT->current.setting.extrapolate_val[1];
				continue;
			}
		}
		while (j > 0 && x[j] >  u[i]) j--;	/* In case u is not sorted */
		while (j < n && x[j] <= u[i]) j++;
		if (j == n) j--;
		if (j > 0) j--;

		switch (mode) {
			case GMT_SPLINE_LINEAR:	/* Linear spline v(u) */
				dx = u[i] - x[j];
				v[i] = (y[j+1]-y[j])*dx/(x[j+1]-x[j]) + y[j];
				break;
			case GMT_SPLINE_AKIMA:	/* Akime's spline u(v) */
				dx = u[i] - x[j];
				v[i] = ((c[3*j+2]*dx + c[3*j+1])*dx + c[3*j])*dx + y[j];
				break;
			case GMT_SPLINE_CUBIC:	/* Natural cubic spline u(v) */
				v[i] = gmtsupport_csplint (GMT, x, y, c, u[i], j);
				break;
			case GMT_SPLINE_NN: /* Nearest neighbor value */
				v[i] = ((u[i] - x[j]) < (x[j+1] - u[i])) ? y[j] : y[j+1];
				break;
			case GMT_SPLINE_STEP: /* Step up to next value when passing it */
                if (i == (m-1))    /* End at the end */
                    v[i] = y[n-1];
				else if (j == 0)	/* Start at the beginning */
					v[i] = y[0];
				else	/* Pick the smallest before the step happens */
					v[i] = (y[j+1] >= y[j]) ? MIN (y[j], y[j+1]) : MAX (y[j], y[j+1]);
				break;
			case GMT_SPLINE_LINEAR+GMT_SPLINE_SLOPE:	/* Linear spline v'(u) */
				v[i] = (y[j+1]-y[j])/(x[j+1]-x[j]);
				break;
			case GMT_SPLINE_AKIMA+GMT_SPLINE_SLOPE:	/* Akime's spline u'(v) */
				dx = u[i] - x[j];
				v[i] = (3.0*c[3*j+2]*dx + 2.0*c[3*j+1])*dx + c[3*j];
				break;
			case GMT_SPLINE_CUBIC+GMT_SPLINE_SLOPE:	/* Natural cubic spline u'(v) */
				v[i] = gmtsupport_csplintslp (GMT, x, y, c, u[i], j);
				break;
			case GMT_SPLINE_NN+GMT_SPLINE_SLOPE:	/* Nearest neighbor slopes are zero */
				v[i] = 0.0;
				break;
			case GMT_SPLINE_STEP+GMT_SPLINE_SLOPE:	/* Step slopes are zero */
				v[i] = 0.0;
				break;
			case GMT_SPLINE_LINEAR+GMT_SPLINE_CURVATURE:	/* Linear spline v"(u) */
				v[i] = 0.0;
				break;
			case GMT_SPLINE_AKIMA+GMT_SPLINE_CURVATURE:	/* Akime's spline u"(v) */
				dx = u[i] - x[j];
				v[i] = 6.0*c[3*j+2]*dx + 2.0*c[3*j+1];
				break;
			case GMT_SPLINE_CUBIC+GMT_SPLINE_CURVATURE:	/* Natural cubic spline u"(v) */
				v[i] = gmtsupport_csplintcurv (GMT, x, c, u[i], j);
				break;
			case GMT_SPLINE_NN+GMT_SPLINE_CURVATURE:	/* Nearest neighbor curvatures are zero  */
				v[i] = 0.0;
				break;
			case GMT_SPLINE_STEP+GMT_SPLINE_CURVATURE:	/* Step curvatures are zero  */
				v[i] = 0.0;
				break;
			case GMT_SPLINE_SMOOTH:	/* Smoothing spline */
				dx1 = x[j+1] - u[i];
				dx2 = u[i] - x[j];
				v[i] = c[4*j] * pow (dx1, 3.0) + c[4*j+1] * pow (dx2, 3.0) + c[4*j+2] * dx1 + c[4*j+3] * dx2;
				break;
			case GMT_SPLINE_SMOOTH+GMT_SPLINE_SLOPE:	/* Derivative of smoothing spline */
				dx1 = x[j+1] - u[i];
				dx2 = u[i] - x[j];
				v[i] = c[4*j] * pow (dx1, 2.0) + c[4*j+1] * pow (dx2, 2.0) + c[4*j+2];
				break;
			case GMT_SPLINE_SMOOTH+GMT_SPLINE_CURVATURE:	/* Curvature of smoothing spline */
				dx1 = x[j+1] - u[i];
				dx2 = u[i] - x[j];
				v[i] = c[4*j] * dx1 + c[4*j+1] * dx2;
				break;
		}
	}
	gmt_M_free (GMT, c);

	return (GMT_NOERROR);
}

/*! . */
GMT_LOCAL void gmtsupport_intpol_reverse (double *x, double *u, uint64_t n, uint64_t m) {
	/* Changes sign on x and u */
	uint64_t i;
	for (i = 0; i < n; i++) x[i] = -x[i];
	for (i = 0; i < m; i++) u[i] = -u[i];
}

/*! Non-square matrix transpose of matrix of size r x c and base address A */
GMT_LOCAL unsigned int gmtsupport_is_set (unsigned int *mark, uint64_t k, unsigned int *bits) {
	/* Return nonzero if this bit is set */
	uint64_t w = k / 32ULL;
	unsigned int b = (unsigned int)(k % 32ULL);
	return (mark[w] & bits[b]);
}

/*! . */
GMT_LOCAL void gmtsupport_set_bit (unsigned int *mark, uint64_t k, unsigned int *bits) {
	/* Set this bit */
	uint64_t w = k / 32ULL;
	unsigned int b = (unsigned int)(k % 32ULL);
	mark[w] |= bits[b];
}

/*! . */
GMT_LOCAL void gmtsupport_decorate_free (struct GMT_CTRL *GMT, struct GMT_DECORATE *G) {
	/* Free memory used by decorate */

	GMT_Destroy_Data (GMT->parent, &(G->X));
	if (G->f_n) {	/* Array for fixed points */
		gmt_M_free (GMT, G->f_xy[GMT_X]);
		gmt_M_free (GMT, G->f_xy[GMT_Y]);
	}
}

/*! . */
GMT_LOCAL int gmtsupport_code_to_lonlat (struct GMT_CTRL *GMT, char *code, double *lon, double *lat) {
	int i, n, error = 0;
	bool z_OK = false;

	n = (int)strlen (code);
	if (n != 2) return (1);

	for (i = 0; i < 2; i++) {
		switch (code[i]) {
			case 'l':
			case 'L':	/* Left */
				*lon = GMT->common.R.wesn[XLO];
				break;
			case 'c':
			case 'C':	/* center */
				*lon = 0.5 * (GMT->common.R.wesn[XLO] + GMT->common.R.wesn[XHI]);
				break;
			case 'r':
			case 'R':	/* right */
				*lon = GMT->common.R.wesn[XHI];
				break;
			case 'b':
			case 'B':	/* bottom */
				*lat = GMT->common.R.wesn[YLO];
				break;
			case 'm':
			case 'M':	/* center */
				*lat = 0.5 * (GMT->common.R.wesn[YLO] + GMT->common.R.wesn[YHI]);
				break;
			case 't':
			case 'T':	/* top */
				*lat = GMT->common.R.wesn[YHI];
				break;
			case 'z':
			case 'Z':	/* z-value */
				z_OK = true;
				break;
			case '+':	/* zmax-location */
				if (z_OK)
					*lon = *lat = DBL_MAX;
				else
					error++;
				break;
			case '-':	/* zmin-location */
				if (z_OK)
					*lon = *lat = -DBL_MAX;
				else
					error++;
				break;
			default:
				error++;
				break;
		}
	}
	if (error) GMT_Report (GMT->parent, GMT_MSG_ERROR, "Unrecognized location code %s\n", code);

	return (error);
}

/*! . */
GMT_LOCAL double gmtsupport_determine_endpoint (struct GMT_CTRL *GMT, double x0, double y0, double length, double az, double *x1, double *y1) {
	/* compute point a distance length from origin along azimuth, return point separation */
	double s_az, c_az;
	sincosdegree (az, &s_az, &c_az);
	if (gmt_M_is_geographic (GMT, GMT_IN)) {	/* Spherical solution */
		double s0, c0, s_d, c_d;
		double d = (length / GMT->current.map.dist[GMT_MAP_DIST].scale);	/* Convert from chosen unit to meter or degree */
		if (!GMT->current.map.dist[GMT_MAP_DIST].arc) d /= GMT->current.proj.DIST_M_PR_DEG;	/* Convert meter to spherical degrees */
		sincosdegree (y0, &s0, &c0);
		sincosdegree (d, &s_d, &c_d);
		*x1 = x0 + atand (s_d * s_az / (c0 * c_d - s0 * s_d * c_az));
		*y1 = d_asind (s0 * c_d + c0 * s_d * c_az);
	}
	else {	/* Cartesian solution */
		*x1 = x0 + length * s_az;
		*y1 = y0 + length * c_az;
	}
	return (gmt_distance (GMT, x0, y0, *x1, *y1));
}

/*! . */
GMT_LOCAL double gmtsupport_determine_endpoints (struct GMT_CTRL *GMT, double x[], double y[], double length, double az) {
	double s_az, c_az;
	sincosdegree (az, &s_az, &c_az);
	length /= 2.0;	/* Going half-way in each direction */
	if (gmt_M_is_geographic (GMT, GMT_IN)) {	/* Spherical solution */
		double s0, c0, s_d, c_d;
		double d = (length / GMT->current.map.dist[GMT_MAP_DIST].scale);	/* Convert from chosen unit to meter or degree */
		if (!GMT->current.map.dist[GMT_MAP_DIST].arc) d /= GMT->current.proj.DIST_M_PR_DEG;	/* Convert meter to spherical degrees */
		sincosdegree (y[0], &s0, &c0);
		sincosdegree (d, &s_d, &c_d);
		x[1] = x[0] + atand (s_d * s_az / (c0 * c_d - s0 * s_d * c_az));
		y[1] = d_asind (s0 * c_d + c0 * s_d * c_az);
		/* Then redo start point by going in the opposite direction */
		sincosdegree (az+180.0, &s_az, &c_az);
		x[0] = x[0] + atand (s_d * s_az / (c0 * c_d - s0 * s_d * c_az));
		y[0] = d_asind (s0 * c_d + c0 * s_d * c_az);
	}
	else {	/* Cartesian solution */
		x[1] = x[0] + length * s_az;
		y[1] = y[0] + length * c_az;
		x[0] = x[0] - length * s_az;
		y[0] = y[0] - length * c_az;
	}
	return (gmt_distance (GMT, x[0], y[0], x[1], y[1]));
}

/*! . */
GMT_LOCAL uint64_t gmtsupport_determine_circle (struct GMT_CTRL *GMT, double x0, double y0, double r, double x[], double y[], unsigned int n) {
	/* Given an origin, radius, and n points, compute a circular path and return it */
	unsigned int k;
	uint64_t np = n;
	double d_angle = 360.0 / n;

	if (gmt_M_is_geographic (GMT, GMT_IN)) {	/* Spherical solution */
		double R[3][3], v[3], v_prime[3], lat;
		double colat = (r / GMT->current.map.dist[GMT_MAP_DIST].scale);	/* Convert from chosen unit to meter or degree */
		if (!GMT->current.map.dist[GMT_MAP_DIST].arc) colat /= GMT->current.proj.DIST_M_PR_DEG;	/* Convert meter to spherical degrees */
		lat = 90.0 - colat;	/* Get small circle latitude about NP */
		/* Set up small circle in local coordinates, convert to Cartesian, rotate, and covert to geo */
		/* Rotation pole is 90 away from x0, at equator, and rotates by 90-y0 degrees */
		gmt_make_rot_matrix (GMT, x0 + 90.0, 0.0, 90.0 - y0, R);
		for (k = 0; k < n; k++) {
			gmt_geo_to_cart (GMT, lat, d_angle * k, v, true);
			gmt_matrix_vect_mult (GMT, 3U, R, v, v_prime);
			gmt_cart_to_geo (GMT, &y[k], &x[k], v_prime, true);
		}
	}
	else {	/* Cartesian solution */
		double s_az, c_az;
		for (k = 0; k < n; k++) {
			sincosdegree (d_angle * k, &s_az, &c_az);
			x[k] = x0 + r * s_az;
			y[k] = y0 + r * c_az;
		}
	}
	return (np);
}

/*! . */
GMT_LOCAL void gmtsupport_line_angle_ave (struct GMT_CTRL *GMT, double x[], double y[], uint64_t start, uint64_t stop, double cangle, uint64_t n, int half, int angle_type, bool directed, struct GMT_LABEL *L) {
	int64_t j, sstart, sstop;
	double sum_x = 0.0, sum_x2 = 0.0, sum_xy = 0.0, sum_y = 0.0, sum_y2 = 0.0, dx, dy;
	/* If directed is true then we want the direction of the line, else orientation is fine */

	if (start == stop) {	/* Can happen if we want no smoothing but landed exactly on a knot point */
		if (start > 0)
			start--;
		else if (stop < (n-1))
			stop++;
	}
	sstart = MAX (0, ((int64_t)start) - half);	/* Must cast since start is unsigned */
	sstop  = MIN (n-1, stop + half);
	for (j = sstart; j <= sstop; j++) {	/* L2 fit for slope over this range of points */
		if (j > sstart) sum_x += (x[j] - x[j-1]), sum_y += (y[j] - y[j-1]);
		dx = x[j] - L->x;
		dy = y[j] - L->y;
		sum_x2 += dx * dx;
		sum_y2 += dy * dy;
		sum_xy += dx * dy;
	}
	if (sum_y2 < GMT_CONV8_LIMIT)	/* Line is horizontal */
		L->line_angle = (directed && sum_x < 0.0) ? 180.0 : 0.0;
	else if (sum_x2 < GMT_CONV8_LIMIT)	/* Line is vertical */
		L->line_angle = (directed && sum_y < 0.0) ? -90.0 : 90.0;
	else {	/* Least-squares fit of slope */
		L->line_angle = d_atan2d (sum_xy, sum_x2);
		if (directed && !(gmt_M_is_zero (sum_x) && gmt_M_is_zero (sum_y))) {
			/* If the line_angle points more or less in the opposite direction as indicated by
			 * sum_x and sum_y we add 180 to it */
			double angle = d_atan2d (sum_y, sum_x);
			if (fabs (L->line_angle - angle) > 145.0) L->line_angle += 180.0;
		}
	}
	if (angle_type == GMT_ANGLE_LINE_DELTA) {	/* Add delta angle to line angle */
		if (gmt_M_is_dnan (cangle)) /* Cannot use this angle - default to along-line angle */
			angle_type = GMT_ANGLE_LINE_PARALLEL;
		else
			L->angle = L->line_angle + cangle;
	}
	if (angle_type == GMT_ANGLE_LINE_FIXED) {	/* Just return the fixed angle given (unless NaN) */
		if (gmt_M_is_dnan (cangle)) /* Cannot use this angle - default to along-line angle */
			angle_type = GMT_ANGLE_LINE_PARALLEL;
		else
			L->angle = L->line_angle = cangle;
	}
	if (angle_type != GMT_ANGLE_LINE_FIXED) {	/* Must base label angle on the contour angle */
		L->angle = L->line_angle + angle_type * 90.0;	/* May add 90 to get normal */
		if (L->angle < 0.0) L->angle += 360.0;
		if (L->angle > 90.0 && L->angle < 270) L->angle -= 180.0;
	}
	GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Ave: Label Line angle = %g start/stop = %d/%d atan2d (%g, %g) Label angle = %g\n", L->line_angle, (int)start, (int)stop, sum_xy, sum_x2, L->angle);
}

/*! . */
GMT_LOCAL void gmtsupport_line_angle_line (struct GMT_CTRL *GMT, double x[], double y[], uint64_t start, uint64_t stop, double cangle, uint64_t n, int angle_type, bool directed, struct GMT_LABEL *L) {
	double dx, dy;
	gmt_M_unused (directed);

	if (start == stop) {	/* Can happen if we want no smoothing but landed exactly on a knot point */
		if (start > 0)
			start--;
		else if (stop < (n-1))
			stop++;
	}
	if (stop >= n) stop = n-1;
	dx = x[stop] - x[start];
	dy = y[stop] - y[start];
	L->line_angle =  d_atan2d (dy, dx);
	if (angle_type == GMT_ANGLE_LINE_FIXED) {	/* Just return the fixed angle given (unless NaN) */
		if (gmt_M_is_dnan (cangle)) /* Cannot use this angle - default to along-line angle */
			angle_type = GMT_ANGLE_LINE_PARALLEL;
		else
			L->angle = cangle;
	}
	if (angle_type != GMT_ANGLE_LINE_FIXED) {	/* Must base label angle on the contour angle */
		L->angle = L->line_angle + angle_type * 90.0;	/* May add 90 to get normal */
		if (L->angle < 0.0) L->angle += 360.0;
		if (L->angle > 90.0 && L->angle < 270) L->angle -= 180.0;
	}
	GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Vec: Label Line angle = %g start/stop = %d/%d atan2d (%g, %g) Label angle = %g\n", L->line_angle, (int)start, (int)stop, dy, dx, L->angle);
}

/*! . */
GMT_LOCAL void gmtsupport_contlabel_angle_ave (struct GMT_CTRL *GMT, double x[], double y[], uint64_t start, uint64_t stop, double cangle, uint64_t n, struct GMT_LABEL *L, struct GMT_CONTOUR *G) {
	gmtsupport_line_angle_ave (GMT, x, y, start, stop, cangle, n, G->half_width, G->angle_type, false, L);
}

/*! . */
GMT_LOCAL void gmtsupport_contlabel_angle_line (struct GMT_CTRL *GMT, double x[], double y[], uint64_t start, uint64_t stop, double cangle, uint64_t n, struct GMT_LABEL *L, struct GMT_CONTOUR *G) {
	gmtsupport_line_angle_line (GMT, x, y, start, stop, cangle, n, G->angle_type, false, L);
}

/*! . */
GMT_LOCAL void gmtsupport_contlabel_angle (struct GMT_CTRL *GMT, double x[], double y[], uint64_t start, uint64_t stop, double cangle, uint64_t n, bool contour, struct GMT_LABEL *L, struct GMT_CONTOUR *G) {
	/* Sets L->line_angle and L->angle */
	if ((G->nudge_flag == 2 && G->half_width == UINT_MAX ) || G->half_width == 0) {	/* Want line-angle to follow line */
		gmtsupport_contlabel_angle_line (GMT, x, y, start, stop, cangle, n, L, G);
	}
	else if (G->half_width == UINT_MAX) {	/* Automatic width specification */
		/* Try to come up with a number that is small for short lines and grow slowly for larger lines */
		G->half_width = MAX (1, lrint (ceil (log10 (0.3333333333*n))));
		G->half_width *= G->half_width;	/* New guess at half-width */
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Automatic label-averaging half_width = %d [n = %d]\n", G->half_width, (int)n);
		if (G->half_width == 1)
			gmtsupport_contlabel_angle_line (GMT, x, y, start, stop, cangle, n, L, G);
		else
			gmtsupport_contlabel_angle_ave (GMT, x, y, start, stop, cangle, n, L, G);
		G->half_width = UINT_MAX;	/* Reset back to auto */
	}
	else {	/* Go width the selected half-width */
		gmtsupport_contlabel_angle_ave (GMT, x, y, start, stop, cangle, n, L, G);
	}
	if (contour) {	/* Limit line_angle to -90/+90 */
		if (L->line_angle > +90.0) L->line_angle -= 180.0;
		if (L->line_angle < -90.0) L->line_angle += 180.0;
	}
}

/*! . */
GMT_LOCAL void gmtsupport_decorated_angle_ave (struct GMT_CTRL *GMT, double x[], double y[], uint64_t start, uint64_t stop, double cangle, uint64_t n, struct GMT_LABEL *L, struct GMT_DECORATE *G) {
	gmtsupport_line_angle_ave (GMT, x, y, start, stop, cangle, n, G->half_width, G->angle_type, true, L);
}

/*! . */
GMT_LOCAL void gmtsupport_decorated_angle_line (struct GMT_CTRL *GMT, double x[], double y[], uint64_t start, uint64_t stop, double cangle, uint64_t n, struct GMT_LABEL *L, struct GMT_DECORATE *G) {
	gmtsupport_line_angle_line (GMT, x, y, start, stop, cangle, n, G->angle_type, true, L);
}

/*! . */
GMT_LOCAL void gmtsupport_decorated_angle (struct GMT_CTRL *GMT, double x[], double y[], uint64_t start, uint64_t stop, double cangle, uint64_t n, bool contour, struct GMT_LABEL *L, struct GMT_DECORATE *G) {
	/* Sets L->line_angle and L->angle */
	if ((G->nudge_flag == 2 && G->half_width == UINT_MAX ) || G->half_width == 0) {	/* Want line-angle to follow line */
		gmtsupport_decorated_angle_line (GMT, x, y, start, stop, cangle, n, L, G);
	}
	else if (G->half_width == UINT_MAX) {	/* Automatic width specification */
		/* Try to come up with a number that is small for short lines and grow slowly for larger lines */
		G->half_width = MAX (1, lrint (ceil (log10 (0.3333333333*n))));
		G->half_width *= G->half_width;	/* New guess at half-width */
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Automatic label-averaging half_width = %d [n = %d]\n", G->half_width, (int)n);
		if (G->half_width == 1)
			gmtsupport_decorated_angle_line (GMT, x, y, start, stop, cangle, n, L, G);
		else
			gmtsupport_decorated_angle_ave (GMT, x, y, start, stop, cangle, n, L, G);
		G->half_width = UINT_MAX;	/* Reset back to auto */
	}
	else {	/* Go width the selected half-width */
		gmtsupport_decorated_angle_ave (GMT, x, y, start, stop, cangle, n, L, G);
	}
	if (contour) {	/* Limit line_angle to -90/+90 */
		if (L->line_angle > +90.0) L->line_angle -= 180.0;
		if (L->line_angle < -90.0) L->line_angle += 180.0;
	}
}

/*! . */
GMT_LOCAL int gmtsupport_sort_label_struct (const void *p_1, const void *p_2) {
	const struct GMT_LABEL **point_1 = (const struct GMT_LABEL **)p_1, **point_2 = (const struct GMT_LABEL **)p_2;

	if ((*point_1)->dist < (*point_2)->dist) return -1;
	if ((*point_1)->dist > (*point_2)->dist) return +1;
	return 0;
}

/*! . */
GMT_LOCAL void gmtsupport_contlabel_fixpath (struct GMT_CTRL *GMT, double **xin, double **yin, double d[], uint64_t *n, struct GMT_CONTOUR *G) {
	/* Sorts labels based on distance and inserts the label (x,y) point into the x,y path */
	uint64_t i, j, k, np;
	double *xp = NULL, *yp = NULL, *x = NULL, *y = NULL;

	if (G->n_label == 0) return;	/* No labels, no need to insert points */

	/* Sort labels based on distance along contour if more than 1 */
	if (G->n_label > 1) qsort (G->L, G->n_label, sizeof (struct GMT_LABEL *), gmtsupport_sort_label_struct);

	np = *n + G->n_label;	/* Length of extended path that includes inserted label coordinates */
	if ((xp = gmt_M_memory (GMT, NULL, np, double)) == NULL) return;
	if ((yp = gmt_M_memory (GMT, NULL, np, double)) == NULL) return;
	x = *xin;	y = *yin;	/* Input coordinate arrays */

	/* Make sure the xp, yp array contains the exact points at which labels should be placed */

	for (k = 0, i = j = 0; i < *n && j < np && k < G->n_label; k++) {
		while (i < *n && d[i] < G->L[k]->dist) {	/* Not at the label point yet - just copy points */
			xp[j] = x[i];
			yp[j] = y[i];
			j++;
			i++;
		}
		/* Add the label point */
		G->L[k]->node = j;		/* Update node since we have been adding new points */
		xp[j] = G->L[k]->x;
		yp[j] = G->L[k]->y;
		j++;
	}
	while (i < *n) {	/* Append the rest of the path */
		xp[j] = x[i];
		yp[j] = y[i];
		j++;
		i++;
	}

	gmt_M_free (GMT, x);	/* Get rid of old path... */
	gmt_M_free (GMT, y);

	*xin = xp;		/* .. and pass out new path */
	*yin = yp;

	*n = np;		/* and the new length */
}

/*! . */
GMT_LOCAL void gmtsupport_contlabel_addpath (struct GMT_CTRL *GMT, double x[], double y[], uint64_t n, double zval, char *label, bool annot, struct GMT_CONTOUR *G) {
	uint64_t i;
	double s = 0.0, c = 1.0, sign = 1.0;
	struct GMT_CONTOUR_LINE *L = NULL;
	/* Adds this segment to the list of contour lines */

	if (G->n_alloc == 0 || G->n_segments == G->n_alloc) {
		G->n_alloc = (G->n_alloc == 0) ? GMT_CHUNK : (G->n_alloc << 1);
		if ((G->segment = gmt_M_memory (GMT, G->segment, G->n_alloc, struct GMT_CONTOUR_LINE *)) == NULL) return;
	}
	if ((G->segment[G->n_segments] = gmt_M_memory (GMT, NULL, 1, struct GMT_CONTOUR_LINE)) == NULL) return;
	L = G->segment[G->n_segments];	/* Pointer to current segment */
	L->n = n;
	if ((L->x = gmt_M_memory (GMT, NULL, L->n, double)) == NULL) return;
	if ((L->y = gmt_M_memory (GMT, NULL, L->n, double)) == NULL) return;
	gmt_M_memcpy (L->x, x, L->n, double);
	gmt_M_memcpy (L->y, y, L->n, double);
	gmt_M_memcpy (&L->pen, &G->line_pen, 1, struct GMT_PEN);
	/* gmt_M_memcpy (L->rgb,&G->rgb, 4, double); */
	gmt_M_memcpy (L->rgb, &G->font_label.fill.rgb, 4, double);
	if ((L->name = gmt_M_memory (GMT, NULL, strlen (label)+1, char)) == NULL) return;
	strcpy (L->name, label);
	L->annot = annot;
	L->z = zval;
	if (G->n_label) {	/* There are labels */
		L->n_labels = G->n_label;
		if ((L->L = gmt_M_memory (GMT, NULL, L->n_labels, struct GMT_LABEL)) == NULL) return;
		for (i = 0; i < L->n_labels; i++) {
			L->L[i].x = G->L[i]->x;
			L->L[i].y = G->L[i]->y;
			L->L[i].line_angle = G->L[i]->line_angle;
			if (G->nudge_flag) {	/* Must adjust point a bit */
				if (G->nudge_flag == 2) sincosdegree (L->L[i].line_angle, &s, &c);
				/* If N+1 or N-1 is used we want positive x nudge to extend away from end point */
				sign = (G->number_placement) ? (double)L->L[i].end : 1.0;
				L->L[i].x += sign * (G->nudge[GMT_X] * c - G->nudge[GMT_Y] * s);
				L->L[i].y += sign * (G->nudge[GMT_X] * s + G->nudge[GMT_Y] * c);
			}
			L->L[i].angle = G->L[i]->angle;
			L->L[i].dist = G->L[i]->dist;
			L->L[i].node = G->L[i]->node;
			L->L[i].label = gmt_M_memory (GMT, NULL, strlen (G->L[i]->label)+1, char);
			gmt_M_memcpy (L->L[i].rgb, G->L[i]->rgb, 4, double);
			strcpy (L->L[i].label, G->L[i]->label);
		}
	}
	G->n_segments++;
}

/*! . */
GMT_LOCAL void gmtsupport_get_radii_of_curvature (double x[], double y[], uint64_t n, double r[]) {
	/* Calculates radius of curvature along the spatial curve x(t), y(t) */

	uint64_t i, im, ip;
	double a, b, c, d, e, f, x0, y0, denom;

	for (im = 0, i = 1, ip = 2; ip < n; i++, im++, ip++) {
		a = (x[im] - x[i]);	b = (y[im] - y[i]);	e = 0.5 * (x[im] * x[im] + y[im] * y[im] - x[i] * x[i] - y[i] * y[i]);
		c = (x[i] - x[ip]);	d = (y[i] - y[ip]);	f = 0.5 * (x[i] * x[i] + y[i] * y[i] - x[ip] * x[ip] - y[ip] * y[ip]);
		denom = b * c - a * d;
		if (denom == 0.0)
			r[i] = DBL_MAX;
		else {
			x0 = (-d * e + b * f) / denom;
			y0 = (c * e - a * f) / denom;
			r[i] = hypot (x[i] - x0, y[i] - y0);
		}
	}
	r[0] = r[n-1] = DBL_MAX;	/* Boundary conditions has zero curvature at end points so r = inf */
}

/*! . */
GMT_LOCAL void gmtsupport_edge_contour (struct GMT_CTRL *GMT, struct GMT_GRID *G, unsigned int col, unsigned int row, unsigned int side, double d, double *x, double *y) {
	gmt_M_unused(GMT);
	if (side == 0) {
		*x = gmt_M_grd_col_to_x (GMT, col+d, G->header);
		*y = gmt_M_grd_row_to_y (GMT, row, G->header);
	}
	else if (side == 1) {
		*x = gmt_M_grd_col_to_x (GMT, col+1, G->header);
		*y = gmt_M_grd_row_to_y (GMT, row-d, G->header);
	}
	else if (side == 2) {
		*x = gmt_M_grd_col_to_x (GMT, col+1-d, G->header);
		*y = gmt_M_grd_row_to_y (GMT, row-1, G->header);
	}
	else {
		*x = gmt_M_grd_col_to_x (GMT, col, G->header);
		*y = gmt_M_grd_row_to_y (GMT, row-1+d, G->header);
	}
}

/*! . */
GMT_LOCAL void gmtsupport_setcontjump (gmt_grdfloat *z, uint64_t nz) {
/* This routine will check if there is a 360 jump problem
 * among these coordinates and adjust them accordingly so
 * that subsequent testing can determine if a zero contour
 * goes through these edges.  E.g., values like 359, 1
 * should become -1, 1 after this function */

	uint64_t i;
	bool jump = false;
	gmt_grdfloat dz;

#ifdef DOUBLE_PRECISION_GRID
	for (i = 1; !jump && i < nz; i++) {
		dz = z[i] - z[0];
		if (fabs (dz) > 180.0) jump = true;
	}

	if (!jump) return;

	z[0] = fmod (z[0], 360.0);
	if (z[0] > 180.0) z[0] -= 360.0;
	else if (z[0] < -180.0) z[0] += 360.0;
	for (i = 1; i < nz; i++) {
		if (z[i] > 180.0) z[i] -= 360.0;
		else if (z[i] < -180.0) z[i] += 360.0;
		dz = z[i] - z[0];
		if (fabs (dz) > 180.0) z[i] -= copysign (360.0, dz);
		z[i] = fmod (z[i], 360.0);
	}
#else
	for (i = 1; !jump && i < nz; i++) {
		dz = z[i] - z[0];
		if (fabsf (dz) > 180.0f) jump = true;
	}

	if (!jump) return;

	z[0] = fmodf (z[0], 360.0f);
	if (z[0] > 180.0f) z[0] -= 360.0f;
	else if (z[0] < -180.0f) z[0] += 360.0f;
	for (i = 1; i < nz; i++) {
		if (z[i] > 180.0f) z[i] -= 360.0f;
		else if (z[i] < -180.0f) z[i] += 360.0f;
		dz = z[i] - z[0];
		if (fabsf (dz) > 180.0f) z[i] -= copysignf (360.0f, dz);
		z[i] = fmodf (z[i], 360.0f);
	}
#endif
}

/*! . */
GMT_LOCAL uint64_t gmtsupport_trace_contour (struct GMT_CTRL *GMT, struct GMT_GRID *G, bool test, unsigned int *edge, double **x, double **y, unsigned int col, unsigned int row, unsigned int side, uint64_t offset, unsigned int *bit, unsigned int *nan_flag) {
	/* Note: side must be signed due to calculations like (side-2)%2 which will not work with unsigned */
	unsigned int side_in, this_side, old_side, n_exits, opposite_side, n_nan, edge_word, edge_bit, periodic = 0;
	int p[5] = {0, 0, 0, 0, 0}, mx;
	bool more, crossed = false;
	size_t n_alloc;
	uint64_t n = 1, m, ij0, ij_in, ij;
	gmt_grdfloat z[5] = {0.0, 0.0, 0.0, 0.0, 0.0}, dz;
	double xk[5] = {0.0, 0.0, 0.0, 0.0, 0.0}, dist1, dist2, *xx = NULL, *yy = NULL;
	static int d_col[5] = {0, 1, 0, 0, 0}, d_row[5] = {0, 0, -1, 0, 0}, d_side[5] = {0, 1, 0, 1, 0};
#if 0
	struct GMT_GRID_HEADER_HIDDEN *HH = gmt_get_H_hidden (G->header);

	/* WORK IN PROGRESS.  Currently has trouble with some contours streaking across a W/E map */
	/* For periodic grids we must also be sensitive to exiting in west and reenter in east, and vice versa */
	if (HH->grdtype == GMT_GRID_GEOGRAPHIC_EXACT360_REPEAT)
		periodic = 1;
	else if (HH->grdtype == GMT_GRID_GEOGRAPHIC_EXACT360_NOREPEAT)
		periodic = 2;
#endif
	/* Note: We need gmt_M_ijp to get us the index into the padded G->data whereas we use gmt_M_ij0 to get the corresponding index for non-padded edge array */
	mx = G->header->mx;	/* Need signed mx below */
	p[0] = p[4] = 0;	p[1] = 1;	p[2] = 1 - mx;	p[3] = -mx;	/* Padded offsets for G->data array */
	*nan_flag = 0;

	/* Check if this edge was already used */

	ij0 = gmt_M_ij0 (G->header, row + d_row[side], col + d_col[side]);	/* Index to use with the edge array */
	edge_word = (unsigned int)(ij0 / 32 + d_side[side] * offset);
	edge_bit = (unsigned int)(ij0 % 32);
	if (test && (edge[edge_word] & bit[edge_bit])) return (0);	/* Been here */

	ij_in = gmt_M_ijp (G->header, row, col);	/* Index to use with the padded G->data array */
	side_in = side;

	/* First check if contour cuts the starting edge */

	z[0] = G->data[ij_in+p[side]];
	z[1] = G->data[ij_in+p[side+1]];
	if (GMT->current.map.z_periodic) gmtsupport_setcontjump (z, 2);

	if (!(z[0] * z[1] < 0.0f)) return (0);	/* This formulation will also return if one of the z's is NaN */

	n_alloc = GMT_CHUNK;
	m = n_alloc - 2;

	if ((xx = gmt_M_memory (GMT, NULL, n_alloc, double)) == NULL) return (0);
	if ((yy = gmt_M_memory (GMT, NULL, n_alloc, double)) == NULL) return (0);

	gmtsupport_edge_contour (GMT, G, col, row, side, z[0] / (z[0] - z[1]), &(xx[0]), &(yy[0]));
	edge[edge_word] |= bit[edge_bit];

	more = true;
	do {
		ij = gmt_M_ijp (G->header, row, col);	/* Index to use with the padded G->data array */

		/* If this is the box and edge we started from, explicitly close the polygon and exit */

		if (n > 1 && ij == ij_in && side == side_in) {	/* Yes, we close and exit */
			xx[n-1] = xx[0]; yy[n-1] = yy[0];	/* Ensure no roundoff */
			more = false;
			continue;
		}

		n_exits = 0;
		old_side = side;
		for (this_side = 0; this_side < 5; this_side++) z[this_side] = G->data[ij+p[this_side]];	/* Copy the 4 corners to the z array and duplicate the 1st as a '5th' corner */
		if (GMT->current.map.z_periodic) gmtsupport_setcontjump (z, 5);

		for (this_side = n_nan = 0; this_side < 4; this_side++) {	/* Loop over the 4 box sides and count possible exits */

			/* Skip if NaN encountered */

			if (gmt_M_is_fnan (z[this_side+1]) || gmt_M_is_fnan (z[this_side])) {	/* Check each side, defined by two nodes, for NaNs */
				n_nan++;
				continue;
			}
			/* Skip if no zero-crossing on this edge */

			if (z[this_side+1] * z[this_side] > 0.0f) continue;
			if (fabs((dz = z[this_side] - z[this_side+1])) < 1e-10) continue;

			/* Save normalized distance along edge from corner this_side to crossing of edge this_side */

			xk[this_side] = z[this_side] / dz;

			/* Skip if this is the entry edge of the current box (this_side == old_side) */

			if (this_side == old_side) continue;

			/* Here we have a new crossing */

			side = this_side;
			n_exits++;
		}
		xk[4] = xk[0];	/* Repeat the first value */

		if (n > m) {	/* Must try to allocate more memory */
			n_alloc <<= 1;
			m = n_alloc - 2;
			if ((xx = gmt_M_memory (GMT, xx, n_alloc, double)) == NULL) return (0);
			if ((yy = gmt_M_memory (GMT, yy, n_alloc, double)) == NULL) return (0);
		}

		/* These are the possible outcomes of n_exits:
		   0: No exits. We must have struck a wall of NaNs
		   1: One exit. Take it!
		   2: Two exits is not possible!
		   3: Three exits means we have entered on a saddle point
		*/

		if (n_exits == 0) {	/* We have hit a field of NaNs, finish contour */
			more = false;
			*nan_flag = n_nan;
			continue;
		}
		else if (n_exits == 3) {	/* Saddle point: Turn to the correct side */
			opposite_side = (old_side + 2) % 4;	/* Opposite side */
			dist1 = xk[old_side] + xk[opposite_side];
			dist2 = xk[old_side+1] + xk[opposite_side+1];
			if (dist1 == dist2) {	/* Perfect saddle, must use fixed saddle decision to avoid a later crossing */
				/* Connect S with W and E with N in this case */
				if (old_side == 0)
					side = 3;
				else if (old_side == 1)
					side = 2;
				else if (old_side == 2)
					side = 1;
				else
					side = 0;
			}
			else if (dist1 > dist2)
				side = (old_side + 1) % 4;
			else
				side = (old_side + 3) % 4;
		}
		gmtsupport_edge_contour (GMT, G, col, row, side, xk[side], &(xx[n]), &(yy[n]));
		n++;

		/* Mark the new edge as used */

		ij0 = gmt_M_ij0 (G->header, row + d_row[side], col + d_col[side]);	/* Non-padded index used for edge array */
		edge_word = (unsigned int)(ij0 / 32 + d_side[side] * offset);
		edge_bit  = (unsigned int)(ij0 % 32);
		edge[edge_word] |= bit[edge_bit];

		if ((side == 0 && row == G->header->n_rows - 1) || (side == 2 && row == 1)) {	/* Going out of grid at N or S */
			more = false;
			continue;
		}
		else if ((side == 1 && col == G->header->n_columns - 2) || (side == 3 && col == 0)) {	/* Going out of grid E-W */
			if (periodic == 0) {	/* And that is it. */
				more = false;
				continue;
			}
			if (side == 1) {	/* Exiting on east to reappear on west */
				side = 3;	/* So entering first col bin from left (3) */
				col = 0;	/* First column bin */
				xx[n] = xx[n-1] - 360.0;
			}
			else {			/* Exiting on west to reappear on east */
				side = 1;	/* So entering last col bin from right (1) */
				col = G->header->n_columns - 2;	/* Last column bin since next col is the boundary of the grid */
				xx[n] = xx[n-1] + 360.0;
			}
			yy[n] = yy[n-1];
			crossed = true;	/* Flag that we crossed periodic boundary and add the duplicate coordinate point to array */
			n++;
			ij0 = gmt_M_ij0 (G->header, row + d_row[side], col + d_col[side]);	/* Flag this edge as used as well */
			edge_word = (unsigned int)(ij0 / 32 + d_side[side] * offset);
			edge_bit  = (unsigned int)(ij0 % 32);
			if (test && (edge[edge_word] & bit[edge_bit])) more = false;	/* Been here before */
			edge[edge_word] |= bit[edge_bit];
			continue;
		}

		switch (side) {	/* Move on to next box (col,row,side) */
			case 0: row++; side = 2; break;	/* Go to row below */
			case 1: col++; side = 3; break;	/* Go to col on right */
			case 2: row--; side = 0; break;	/* Go to row above */
			case 3: col--; side = 1; break;	/* Go to col on left */
		}

	} while (more);

	/* Reduce memory to what is needed */
	xx = gmt_M_memory (GMT, xx, n, double);
	yy = gmt_M_memory (GMT, yy, n, double);

	if (crossed) {
		if ((gmtlib_determine_pole (GMT, xx, yy, n) == 0))
			gmt_eliminate_lon_jumps (GMT, xx, n);	/* Ensure longitudes are in the same quadrants */
	}

	*x = xx;	*y = yy;
	return (n);
}

/*! . */
GMT_LOCAL int64_t gmtsupport_smooth_contour (struct GMT_CTRL *GMT, double **x_in, double **y_in, uint64_t n, int sfactor, int stype) {
	/* Input n (x_in, y_in) points */
	/* n_out = sfactor * n -1 */
	/* Interpolation scheme used (0 = linear, 1 = Akima, 2 = Cubic spline, 3 = None */
	uint64_t i, j, k, n_out;
	double ds, t_next, *x = NULL, *y = NULL;
	double *t_in = NULL, *t_out = NULL, *x_tmp = NULL, *y_tmp = NULL, x0, x1, y0, y1;
	bool *flag = NULL;

	if (sfactor == 0 || n < 4) return (n);	/* Need at least 4 points to call Akima */

	x = *x_in;	y = *y_in;

	n_out = sfactor * n - 1;	/* Number of new points */

	if ((t_in = gmt_M_memory (GMT, NULL, n, double)) == NULL) return (-GMT_MEMORY_ERROR);

	/* Create dummy distance values for input points, and throw out duplicate points while at it */

	t_in[0] = 0.0;
	for (i = j = 1; i < n; i++)	{
		if (gmt_M_x_is_lon (GMT, GMT_IN) && gmt_M_360_range (x[i-1], x[i])) {
			ds = 0.0;	/* 360 degree jumps are excluded */
		}
		else
			ds = hypot ((x[i]-x[i-1]), (y[i]-y[i-1]));
		if (ds > 0.0) {
			t_in[j] = t_in[j-1] + ds;
			x[j] = x[i];
			y[j] = y[i];
			j++;
		}
	}

	n = j;	/* May have lost some duplicates */
	if (sfactor == 0 || n < 4) {	/* Need at least 4 points to call Akima */
		gmt_M_free (GMT, t_in);
		return (n);
	}

	if ((t_out = gmt_M_memory (GMT, NULL, n_out + n, double)) == NULL) return (-GMT_MEMORY_ERROR);
	if ((x_tmp = gmt_M_memory (GMT, NULL, n_out + n, double)) == NULL) return (-GMT_MEMORY_ERROR);
	if ((y_tmp = gmt_M_memory (GMT, NULL, n_out + n, double)) == NULL) return (-GMT_MEMORY_ERROR);
	if ((flag  = gmt_M_memory (GMT, NULL, n_out + n, bool))   == NULL) return (-GMT_MEMORY_ERROR);

	/* Create equidistant output points */

	ds = t_in[n-1] / (n_out-1);
	t_next = ds;
	t_out[0] = 0.0;
	flag[0] = true;
	for (i = j = 1; i < n_out; i++) {
		if (j < n && t_in[j] < t_next) {
			t_out[i] = t_in[j];
			flag[i] = true;
			j++;
			n_out++;
		}
		else {
			t_out[i] = t_next;
			t_next += ds;
		}
	}
	t_out[n_out-1] = t_in[n-1];
	if (t_out[n_out-1] == t_out[n_out-2]) n_out--;
	flag[n_out-1] = true;

	if (gmt_intpol (GMT, t_in, x, NULL, n, n_out, t_out, x_tmp, 0.0, stype)) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "GMT internal error\n");
		gmt_M_free (GMT, t_in);
		gmt_M_free (GMT, t_out);
		gmt_M_free (GMT, flag);
		gmt_M_free (GMT, x_tmp);
		gmt_M_free (GMT, y_tmp);
		return -GMT_RUNTIME_ERROR;
	}
	if (gmt_intpol (GMT, t_in, y, NULL, n, n_out, t_out, y_tmp, 0.0, stype)) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "GMT internal error\n");
		gmt_M_free (GMT, t_in);
		gmt_M_free (GMT, t_out);
		gmt_M_free (GMT, flag);
		gmt_M_free (GMT, x_tmp);
		gmt_M_free (GMT, y_tmp);
		return -GMT_RUNTIME_ERROR;
	}

	/* Make sure interpolated function is bounded on each segment interval */

	i = 0;
	while (i < (n_out - 1)) {
		j = i + 1;
		while (j < n_out && !flag[j]) j++;
		x0 = x_tmp[i];	x1 = x_tmp[j];
		if (x0 > x1) gmt_M_double_swap (x0, x1);
		y0 = y_tmp[i];	y1 = y_tmp[j];
		if (y0 > y1) gmt_M_double_swap (y0, y1);
		for (k = i + 1; k < j; k++) {
			if (x_tmp[k] < x0)
				x_tmp[k] = x0 + 1.0e-10;
			else if (x_tmp[k] > x1)
				x_tmp[k] = x1 - 1.0e-10;
			if (y_tmp[k] < y0)
				y_tmp[k] = y0 + 1.0e-10;
			else if (y_tmp[k] > y1)
				y_tmp[k] = y1 - 1.0e-10;
		}
		i = j;
	}

	/* Replace original coordinates */

	gmt_M_free (GMT, x);
	gmt_M_free (GMT, y);

	*x_in = x_tmp;
	*y_in = y_tmp;

	gmt_M_free (GMT, t_in);
	gmt_M_free (GMT, t_out);
	gmt_M_free (GMT, flag);

	return (n_out);
}

/*! . */
GMT_LOCAL uint64_t gmtsupport_splice_contour (struct GMT_CTRL *GMT, double **x, double **y, uint64_t n, double *x2, double *y2, uint64_t n2) {
	/* Basically does a "tail -r" on the array x,y and append arrays x2/y2 */

	uint64_t i, j, m;
	double *x1, *y1;

	if (n2 < 2) return (n);		/* Nothing to be done when second piece < 2 points */

	m = n + n2 - 1;	/* Total length since one point is shared */

	/* Make more space */

	x1 = *x;	y1 = *y;
	if ((x1 = gmt_M_memory (GMT, x1, m, double)) == NULL) return (0);
	if ((y1 = gmt_M_memory (GMT, y1, m, double)) == NULL) return (0);

	/* Move first piece to the back */

	for (i = m-1, j = n; j > 0; j--, i--) {
		x1[i] = x1[j-1];	y1[i] = y1[j-1];
	}

	/* Put second piece, in reverse, in the front */

	for (i = n2-2, j = 1; j < n2; j++, i--) {
		x1[i] = x2[j];	y1[i] = y2[j];
	}

	*x = x1;
	*y = y1;

	return (m);
}

/*! . */
GMT_LOCAL void gmtsupport_orient_contour (struct GMT_GRID *G, double *x, double *y, uint64_t n, int orient) {
	/* Determine handedness of the contour and if opposite of orient reverse the contour */
	int side[2], z_dir, k, k2;
	bool reverse;
	uint64_t i, j, ij_ul, ij_ur, ij_ll, ij_lr;
	double fx[2], fy[2], dx, dy;
	struct GMT_GRID_HEADER_HIDDEN *HH = gmt_get_H_hidden (G->header);

	if (orient == 0) return;	/* Nothing to be done when no orientation specified */
	if (n < 2) return;		/* Cannot work on a single point */

	for (k = 0; k < 2; k++) {	/* Calculate fractional node numbers from left/top */
		fx[k] = (x[k] - G->header->wesn[XLO]) * HH->r_inc[GMT_X] - G->header->xy_off;
		fy[k] = (G->header->wesn[YHI] - y[k]) * HH->r_inc[GMT_Y] - G->header->xy_off;
	}

	/* Get(i,j) of the lower left node in the rectangle containing this contour segment.
	   We use the average x and y coordinate for this to avoid any round-off involved in
	   working on a single coordinate. The average coordinate should always be inside the
	   rectangle and hence the floor/ceil operators will yield the LL node. */

	i = lrint (floor (0.5 * (fx[0] + fx[1])));
	j = lrint (ceil  (0.5 * (fy[0] + fy[1])));
	ij_ll = gmt_M_ijp (G->header, j, i);     /* lower left corner  */
	ij_lr = gmt_M_ijp (G->header, j, i+1);   /* lower right corner */
	ij_ul = gmt_M_ijp (G->header, j-1, i);   /* upper left corner  */
	ij_ur = gmt_M_ijp (G->header, j-1, i+1); /* upper right corner */

	for (k = 0; k < 2; k++) {	/* Determine which edge the contour points lie on (0-3) */
		/* We KNOW that for each k, either x[k] or y[k] lies EXACTLY on a gridline.  This is used
		 * to deal with the inevitable round-off that places points slightly off the gridline.  We
		 * pick the coordinate closest to the gridline as the one that should be exactly on the gridline */

		k2 = 1 - k;	/* The other point */
		dx = fmod (fx[k], 1.0);
		if (dx > 0.5) dx = 1.0 - dx;	/* Fraction to closest vertical gridline */
		dy = fmod (fy[k], 1.0);
		if (dy > 0.5) dy = 1.0 - dy;	/* Fraction to closest horizontal gridline */
		if (dx < dy)		/* Point is on a vertical grid line (left [3] or right [1]) */
			side[k] = (fx[k] < fx[k2]) ? 3 : 1;	/* Simply check order of fx to determine which it is */
		else						/* Point must be on horizontal grid line (top [2] or bottom [0]) */
			side[k] = (fy[k] > fy[k2]) ? 0 : 2;	/* Same for fy */
	}

	switch (side[0]) {	/* Entry side: check heights of corner points.*/
		                /* if point to the right of the line is higher z_dir = +1 else -1 */
		case 0:	/* Bottom: check heights of lower left and lower right nodes */
			z_dir = (G->data[ij_lr] > G->data[ij_ll]) ? +1 : -1;
			break;
		case 1:	/* Right */
			z_dir = (G->data[ij_ur] > G->data[ij_lr]) ? +1 : -1;
			break;
		case 2:	/* Top */
			z_dir = (G->data[ij_ul] > G->data[ij_ur]) ? +1 : -1;
			break;
		default:/* Left */
			z_dir = (G->data[ij_ll] > G->data[ij_ul]) ? +1 : -1;
			break;
	}
	reverse = (z_dir != orient);

	if (reverse) {	/* Must reverse order of contour */
		for (i = 0, j = n-1; i < n/2; i++, j--) {
			gmt_M_double_swap (x[i], x[j]);
			gmt_M_double_swap (y[i], y[j]);
		}
	}
}

/*! . */
GMT_LOCAL bool gmtsupport_label_is_OK (struct GMT_CTRL *GMT, struct GMT_LABEL *L, char *this_label, char *label, double this_dist, double this_value_dist, uint64_t xl, uint64_t fj, struct GMT_CONTOUR *G) {
	/* Determines if the proposed label passes various tests.  Return true if we should go ahead and add this label to the list */
	bool label_OK = true;
	uint64_t seg, k;
	char format[GMT_LEN256] = {""};
	struct GMT_CONTOUR_LINE *S = NULL;

	if (G->isolate) {	/* Must determine if the proposed label is within radius distance of any other label already accepted */
		for (seg = 0; seg < G->n_segments; seg++) {	/* Previously processed labels */
			S = G->segment[seg];	/* Pointer to current segment */
			for (k = 0; k < S->n_labels; k++) if (hypot (L->x - S->L[k].x, L->y - S->L[k].y) < G->label_isolation) return (false);
		}
		/* Also check labels for current segment */
		for (k = 0; k < G->n_label; k++) if (hypot (L->x - G->L[k]->x, L->y - G->L[k]->y) < G->label_isolation) return (false);
	}

	switch (G->label_type) {
		case GMT_LABEL_IS_NONE:
			if (label && label[0])
				strcpy (this_label, label);
			else
				label_OK = false;
			break;

		case GMT_LABEL_IS_CONSTANT:
		case GMT_LABEL_IS_HEADER:
			if (G->label[0])
				strcpy (this_label, G->label);
			else
				label_OK = false;
			break;

		case GMT_LABEL_IS_PDIST:
			if (G->spacing) {	/* Distances are even so use special contour format */
				gmt_get_format (GMT, this_dist * GMT->session.u2u[GMT_INCH][G->dist_unit], G->unit, NULL, format);
				gmt_sprintf_float (GMT, this_label, format, this_dist * GMT->session.u2u[GMT_INCH][G->dist_unit]);
			}
			else {
				gmt_sprintf_float (GMT, this_label, GMT->current.setting.format_float_map, this_dist * GMT->session.u2u[GMT_INCH][G->dist_unit]);
			}
			break;

		case GMT_LABEL_IS_MDIST:
			gmt_sprintf_float (GMT, this_label, GMT->current.setting.format_float_map, this_value_dist);
			break;

		case GMT_LABEL_IS_FFILE:
			if (G->f_label[fj] && G->f_label[fj][0])
				strcpy (this_label, G->f_label[fj]);
			else
				label_OK = false;
			break;

		case GMT_LABEL_IS_XFILE:
			if (G->X->table[0]->segment[xl]->label && G->X->table[0]->segment[xl]->label[0])
				strcpy (this_label, G->X->table[0]->segment[xl]->label);
			else
				label_OK = false;
			break;

		case GMT_LABEL_IS_SEG:
			sprintf (this_label, "%" PRIu64, (GMT->current.io.status & GMT_IO_SEGMENT_HEADER) ? GMT->current.io.seg_no - 1 : GMT->current.io.seg_no);
			break;

		case GMT_LABEL_IS_FSEG:
			sprintf (this_label, "%d/%" PRIu64, GMT->current.io.tbl_no, (GMT->current.io.status & GMT_IO_SEGMENT_HEADER) ? GMT->current.io.seg_no - 1 : GMT->current.io.seg_no);
			break;

		default:	/* Should not happen... */
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "GMT internal error - no label set\n");
			this_label[0] = '\0';
			return false;
			break;
	}

	return (label_OK);
}

/*! . */
GMT_LOCAL void gmtsupport_place_label (struct GMT_CTRL *GMT, struct GMT_LABEL *L, char *txt, struct GMT_CONTOUR *G, bool use_unit, size_t extra) {
	/* Allocates needed space and copies in the label */
	size_t n, m = 0;

	if (use_unit && G->unit[0])
		m = strlen (G->unit);
	n = strlen (txt) + 1 + m + extra;
	if (G->prefix[0]) {	/* Must prepend the prefix string */
		n += strlen (G->prefix) + 1;
		L->label = gmt_M_memory (GMT, NULL, n, char);
		sprintf (L->label, "%s%s", G->prefix, txt);
	}
	else {
		L->label = gmt_M_memory (GMT, NULL, n, char);
		strcpy (L->label, txt);
	}
	if (use_unit && G->unit[0]) {	/* Append a unit string */
		strcat (L->label, G->unit);
	}
	gmt_M_memcpy (L->rgb, G->font_label.fill.rgb, 4, double);	/* Remember color in case it varies */
}

/*! . */
GMT_LOCAL void gmtsupport_hold_contour_sub (struct GMT_CTRL *GMT, double **xxx, double **yyy, uint64_t nn, double zval, char *label, char ctype, double cangle, bool closed, bool contour, struct GMT_CONTOUR *G) {
	/* The xxx, yyy are expected to be projected x/y inches */
	uint64_t i, j, start = 0;
	size_t n_alloc = GMT_SMALL_CHUNK;
	double *track_dist = NULL, *map_dist = NULL, *value_dist = NULL, *radii = NULL, *xx = NULL, *yy = NULL;
	double dx, dy, width, f, this_dist, step, stept, this_value_dist, lon[2], lat[2];
	struct GMT_LABEL *new_label = NULL;
	char this_label[GMT_BUFSIZ] = {""};

	if (nn < 2) return;

	xx = *xxx;	yy = *yyy;
	G->n_label = 0;

	/* OK, line is long enough to be added to array of lines */

	if (ctype == 'A' || ctype == 'a') {	/* Annotated contours, must find label placement */

		/* Calculate distance along contour and store in track_dist array */

		if (G->dist_kind == 1) gmt_xy_to_geo (GMT, &lon[1], &lat[1], xx[0], yy[0]);
		if ((map_dist = gmt_M_memory (GMT, NULL, nn, double)) == NULL) return;	/* Distances on map in inches */
		if ((track_dist = gmt_M_memory (GMT, NULL, nn, double)) == NULL) return;	/* May be km ,degrees or whatever */
		if ((value_dist = gmt_M_memory (GMT, NULL, nn, double)) == NULL) return;	/* May be km ,degrees or whatever */
		if ((radii = gmt_M_memory (GMT, NULL, nn, double)) == NULL) return;	/* Radius of curvature, in inches */

		/* We will calculate the radii of curvature at all points.  By default we don't care and
		 * will place labels at whatever distance we end up with.  However, if the user has asked
		 * for a minimum limit on the radius of curvature [Default 0] we do not want to place labels
		 * at those sections where the curvature is large.  Since labels are placed according to
		 * distance along track, the way we deal with this is to set distance increments to zero
		 * where curvature is large:  that way, there is no increase in distance over those patches
		 * and the machinery for determining when we exceed the next label distance will not kick
		 * in until after curvature drops and increments are again nonzero.  This procedure only
		 * applies to the algorithms based on distance along track.
		 */

		gmtsupport_get_radii_of_curvature (xx, yy, nn, radii);

		map_dist[0] = track_dist[0] = value_dist[0] = 0.0;	/* Unnecessary, just so we understand the logic */
		for (i = 1; i < nn; i++) {
			/* Distance from xy */
			dx = xx[i] - xx[i-1];
			if (gmt_M_x_is_lon (GMT, GMT_IN) && GMT->current.map.is_world && fabs (dx) > (width = gmt_half_map_width (GMT, yy[i-1]))) {
				width *= 2.0;
				dx = copysign (width - fabs (dx), -dx);
				if (xx[i] < width)
					xx[i-1] -= width;
				else
					xx[i-1] += width;
			}
			dy = yy[i] - yy[i-1];
			step = stept = hypot (dx, dy);
			map_dist[i] = map_dist[i-1] + step;
			if (G->dist_kind == 1 || G->label_type == GMT_LABEL_IS_MDIST) {
				lon[0] = lon[1];	lat[0] = lat[1];
				gmt_xy_to_geo (GMT, &lon[1], &lat[1], xx[i], yy[i]);
				if (G->dist_kind == 1) step = gmtlib_distance_type (GMT, lon[0], lat[0], lon[1], lat[1], GMT_CONT_DIST);
				if (G->label_type == GMT_LABEL_IS_MDIST) stept = gmtlib_distance_type (GMT, lon[0], lat[0], lon[1], lat[1], GMT_LABEL_DIST);
			}
			if (radii[i] < G->min_radius) step = stept = 0.0;	/* If curvature is too great we simply don't add up distances */
			track_dist[i] = track_dist[i-1] + step;
			value_dist[i] = value_dist[i-1] + stept;
		}
		gmt_M_free (GMT, radii);

		/* G->L array is only used so we can later sort labels based on distance along track.  Once
		 * GMT_contlabel_draw has been called we will free up the memory as the labels are kept in
		 * the linked list starting at G->anchor. */

		if ((G->L = gmt_M_memory (GMT, NULL, n_alloc, struct GMT_LABEL *)) == NULL) return;

		if (G->spacing) {	/* Place labels based on distance along contours */
			double last_label_dist, dist_offset, dist;

			dist_offset = (closed && G->dist_kind == 0) ? (1.0 - G->label_dist_frac) * G->label_dist_spacing : 0.0;	/* Label closed contours longer than frac of dist_spacing */
			last_label_dist = 0.0;
			i = 1;
			while (i < nn) {

				dist = track_dist[i] + dist_offset - last_label_dist;
				if (dist > G->label_dist_spacing) {	/* Time for label */
					new_label = gmt_M_memory (GMT, NULL, 1, struct GMT_LABEL);
					f = (dist - G->label_dist_spacing) / (track_dist[i] - track_dist[i-1]);
					if (f < 0.5) {
						new_label->x = xx[i] - f * (xx[i] - xx[i-1]);
						new_label->y = yy[i] - f * (yy[i] - yy[i-1]);
						new_label->dist = map_dist[i] - f * (map_dist[i] - map_dist[i-1]);
						this_value_dist = value_dist[i] - f * (value_dist[i] - value_dist[i-1]);
					}
					else {
						f = 1.0 - f;
						new_label->x = xx[i-1] + f * (xx[i] - xx[i-1]);
						new_label->y = yy[i-1] + f * (yy[i] - yy[i-1]);
						new_label->dist = map_dist[i-1] + f * (map_dist[i] - map_dist[i-1]);
						this_value_dist = value_dist[i-1] + f * (value_dist[i] - value_dist[i-1]);
					}
					this_dist = G->label_dist_spacing - dist_offset + last_label_dist;
					if (gmtsupport_label_is_OK (GMT, new_label, this_label, label, this_dist, this_value_dist, 0, 0, G)) {
						gmtsupport_place_label (GMT, new_label, this_label, G, !(G->label_type == GMT_LABEL_IS_NONE || G->label_type == GMT_LABEL_IS_PDIST), 0);
						new_label->node = i - 1;
						gmtsupport_contlabel_angle (GMT, xx, yy, i - 1, i, cangle, nn, contour, new_label, G);
						G->L[G->n_label++] = new_label;
						if (G->n_label == n_alloc) {
							size_t old_n_alloc = n_alloc;
							n_alloc <<= 1;
							if ((G->L = gmt_M_memory (GMT, G->L, n_alloc, struct GMT_LABEL *)) == NULL) return;
							gmt_M_memset (&(G->L[old_n_alloc]), n_alloc - old_n_alloc, struct GMT_LABEL *);	/* Set to NULL */
						}
					}
					else	/* All in vain... */
						gmt_M_free (GMT, new_label);
					dist_offset = 0.0;
					last_label_dist = this_dist;
				}
				else	/* Go to next point in line */
					i++;
			}
			if (G->n_label == 0) GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Your -Gd|D option produced no contour labels for z = %g\n", zval);

		}
		if (G->number) {	/* Place prescribed number of labels evenly along contours */
			uint64_t nc;
			int e_val = 0;
			double dist, last_dist;

			last_dist = (G->n_cont > 1) ? -map_dist[nn-1] / (G->n_cont - 1) : -0.5 * map_dist[nn-1];
			nc = (map_dist[nn-1] > G->min_dist) ? G->n_cont : 0;
			for (i = j = 0; i < nc; i++) {
				new_label = gmt_M_memory (GMT, NULL, 1, struct GMT_LABEL);
				if (G->number_placement && !closed) {
					e_val = G->number_placement;
					if (G->number_placement == -1 && G->n_cont == 1) {	/* Label justified with start of segment */
						f = d_atan2d (xx[0] - xx[1], yy[0] - yy[1]) + 180.0;	/* 0-360 */
						G->end_just[0] = (f >= 90.0 && f <= 270) ? 7 : 5;
					}
					else if (G->number_placement == +1 && G->n_cont == 1) {	/* Label justified with end of segment */
						f = d_atan2d (xx[nn-1] - xx[nn-2], yy[nn-1] - yy[nn-2]) + 180.0;	/* 0-360 */
						G->end_just[1] = (f >= 90.0 && f <= 270) ? 7 : 5;
					}
					else if (G->number_placement && G->n_cont > 1)	/* One of the end labels */
						e_val = (i == 0) ? -1 : +1;
					dist = (G->n_cont > 1) ? i * track_dist[nn-1] / (G->n_cont - 1) : 0.5 * (G->number_placement + 1.0) * track_dist[nn-1];
					this_value_dist = (G->n_cont > 1) ? i * value_dist[nn-1] / (G->n_cont - 1) : 0.5 * (G->number_placement + 1.0) * value_dist[nn-1];
				}
				else {
					dist = (i + 1 - 0.5 * closed) * track_dist[nn-1] / (G->n_cont + 1 - closed);
					this_value_dist = (i + 1 - 0.5 * closed) * value_dist[nn-1] / (G->n_cont + 1 - closed);
				}
				while (j < nn && track_dist[j] < dist) j++;
				if (j == nn) j--;	/* Safety precaution */
				f = ((j == 0) ? 1.0 : (dist - track_dist[j-1]) / (track_dist[j] - track_dist[j-1]));
				if (f < 0.5) {	/* Pick the smallest fraction to minimize Taylor shortcomings */
					new_label->x = xx[j-1] + f * (xx[j] - xx[j-1]);
					new_label->y = yy[j-1] + f * (yy[j] - yy[j-1]);
					new_label->dist = map_dist[j-1] + f * (map_dist[j] - map_dist[j-1]);
				}
				else {
					f = 1.0 - f;
					new_label->x = (j == 0) ? xx[0] : xx[j] - f * (xx[j] - xx[j-1]);
					new_label->y = (j == 0) ? yy[0] : yy[j] - f * (yy[j] - yy[j-1]);
					new_label->dist = (j == 0) ? 0.0 : map_dist[j] - f * (map_dist[j] - map_dist[j-1]);
				}
				if ((new_label->dist - last_dist) >= G->min_dist) {	/* OK to accept this label */
					this_dist = dist;
					if (gmtsupport_label_is_OK (GMT, new_label, this_label, label, this_dist, this_value_dist, 0, 0, G)) {
						size_t extra = (G->crossect) ? strlen (G->crossect_tag[i]) + 1 : 0;	/* Need to increase allocated space */
						gmtsupport_place_label (GMT, new_label, this_label, G, !(G->label_type == GMT_LABEL_IS_NONE), extra);
						if (G->crossect) {	/* Special crossection mode */
							if (!strcmp (new_label->label, "N/A"))	/* Override the N/A lack of label identifier */
								strcpy (new_label->label, G->crossect_tag[i]);
							else	/* Append tag to the label */
								strcat (new_label->label, G->crossect_tag[i]);
						}
						new_label->node = (j == 0) ? 0 : j - 1;
						gmtsupport_contlabel_angle (GMT, xx, yy, new_label->node, j, cangle, nn, contour, new_label, G);
						if (G->number_placement) new_label->end = e_val;
						G->L[G->n_label++] = new_label;
						if (G->n_label == n_alloc) {
							size_t old_n_alloc = n_alloc;
							n_alloc <<= 1;
							if ((G->L = gmt_M_memory (GMT, G->L, n_alloc, struct GMT_LABEL *)) == NULL) return;
							gmt_M_memset (&(G->L[old_n_alloc]), n_alloc - old_n_alloc, struct GMT_LABEL *);	/* Set to NULL */
						}
						last_dist = new_label->dist;
					}
					else /* Label had no text */
						gmt_M_free (GMT, new_label);
				}
				else	/* All in vain... */
					gmt_M_free (GMT, new_label);
			}
			if (G->n_label == 0) GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Your -Gn|N option produced no contour labels for z = %g\n", zval);
		}
		if (G->crossing) {	/* Determine label positions based on crossing lines */
			uint64_t left, right, line_no;
			struct GMT_DATASEGMENT *S = NULL;
			gmt_init_track (GMT, yy, nn, &(G->ylist));
			for (line_no = 0; line_no < G->X->n_segments; line_no++) {	/* For each of the crossing lines */
				S = G->X->table[0]->segment[line_no];	/* Current segment */
				gmt_init_track (GMT, S->data[GMT_Y], S->n_rows, &(G->ylist_XP));
				G->nx = (unsigned int)gmt_crossover (GMT, S->data[GMT_X], S->data[GMT_Y], NULL, G->ylist_XP, S->n_rows, xx, yy, NULL, G->ylist, nn, false, gmt_M_x_is_lon (GMT, GMT_IN), &G->XC);
				gmt_M_free (GMT, G->ylist_XP);
				if (G->nx == 0) continue;

				/* OK, we found intersections for labels */

				for (i = 0; i < (uint64_t)G->nx; i++) {
					left  = lrint (floor (G->XC.xnode[1][i]));
					right = lrint (ceil  (G->XC.xnode[1][i]));
					new_label = gmt_M_memory (GMT, NULL, 1, struct GMT_LABEL);
					new_label->x = G->XC.x[i];
					new_label->y = G->XC.y[i];
					new_label->node = left;
					new_label->dist = track_dist[left];
					f = G->XC.xnode[1][i] - left;
					if (f < 0.5) {
						this_dist = track_dist[left] + f * (track_dist[right] - track_dist[left]);
						new_label->dist = map_dist[left] + f * (map_dist[right] - map_dist[left]);
						this_value_dist = value_dist[left] + f * (value_dist[right] - value_dist[left]);
					}
					else {
						f = 1.0 - f;
						this_dist = track_dist[right] - f * (track_dist[right] - track_dist[left]);
						new_label->dist = map_dist[right] - f * (map_dist[right] - map_dist[left]);
						this_value_dist = value_dist[right] - f * (value_dist[right] - value_dist[left]);
					}
					if (gmtsupport_label_is_OK (GMT, new_label, this_label, label, this_dist, this_value_dist, line_no, 0, G)) {
						gmtsupport_place_label (GMT, new_label, this_label, G, !(G->label_type == GMT_LABEL_IS_NONE), 0);
						gmtsupport_contlabel_angle (GMT, xx, yy, left, right, cangle, nn, contour, new_label, G);
						G->L[G->n_label++] = new_label;
						if (G->n_label == n_alloc) {
							size_t old_n_alloc = n_alloc;
							n_alloc <<= 1;
							if ((G->L = gmt_M_memory (GMT, G->L, n_alloc, struct GMT_LABEL *)) == NULL) return;
							gmt_M_memset (&(G->L[old_n_alloc]), n_alloc - old_n_alloc, struct GMT_LABEL *);	/* Set to NULL */
						}
					}
					else	/* All in vain... */
						gmt_M_free (GMT, new_label);
				}
				gmt_x_free (GMT, &G->XC);
			}
			gmt_M_free (GMT, G->ylist);
			if (G->n_label == 0) GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Your -Gx|X|l|L option produced no contour labels for z = %g\n", zval);
		}
		if (G->fixed) {	/* Prescribed point locations for labels that match points in input records */
			double dist, min_dist;
			for (j = 0; j < (uint64_t)G->f_n; j++) {	/* Loop over fixed point list */
				min_dist = DBL_MAX;
				for (i = 0; i < nn; i++) {	/* Loop over input line/contour */
					if ((dist = hypot (xx[i] - G->f_xy[0][j], yy[i] - G->f_xy[1][j])) < min_dist) {	/* Better fit */
						min_dist = dist;
						start = i;
					}
				}
				if (min_dist < G->slop) {	/* Closest point within tolerance */
					new_label = gmt_M_memory (GMT, NULL, 1, struct GMT_LABEL);
					new_label->x = xx[start];
					new_label->y = yy[start];
					new_label->node = start;
					new_label->dist = track_dist[start];
					this_dist = track_dist[start];
					new_label->dist = map_dist[start];
					this_value_dist = value_dist[start];
					if (gmtsupport_label_is_OK (GMT, new_label, this_label, label, this_dist, this_value_dist, 0, j, G)) {
						gmtsupport_place_label (GMT, new_label, this_label, G, !(G->label_type == GMT_LABEL_IS_NONE), 0);
						gmtsupport_contlabel_angle (GMT, xx, yy, start, start, cangle, nn, contour, new_label, G);
						G->L[G->n_label++] = new_label;
						if (G->n_label == n_alloc) {
							size_t old_n_alloc = n_alloc;
							n_alloc <<= 1;
							if ((G->L = gmt_M_memory (GMT, G->L, n_alloc, struct GMT_LABEL *)) == NULL) return;
							gmt_M_memset (&(G->L[old_n_alloc]), n_alloc - old_n_alloc, struct GMT_LABEL *);	/* Set to NULL */
						}
					}
					else	/* All in vain... */
						gmt_M_free (GMT, new_label);
				}
			}

			if (G->n_label == 0) GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Your -Gf option produced no contour labels for z = %g\n", zval);
		}
		gmtsupport_contlabel_fixpath (GMT, &xx, &yy, map_dist, &nn, G);	/* Inserts the label x,y into path */
		gmtsupport_contlabel_addpath (GMT, xx, yy, nn, zval, label, true, G);		/* Appends this path and the labels to list */

		gmt_M_free (GMT, track_dist);
		gmt_M_free (GMT, map_dist);
		gmt_M_free (GMT, value_dist);
		/* Free label structure since info is now copied to segment labels */
		for (i = 0; i < (uint64_t)G->n_label; i++) {
			gmt_M_free (GMT, G->L[i]->label);
			gmt_M_free (GMT, G->L[i]);
		}
		gmt_M_free (GMT, G->L);
	}
	else {   /* just one line, no holes for labels */
		gmtsupport_contlabel_addpath (GMT, xx, yy, nn, zval, label, false, G);		/* Appends this path to list */
	}
	*xxx = xx;
	*yyy = yy;
}

/*! . */
GMT_LOCAL void gmtsupport_add_decoration (struct GMT_CTRL *GMT, struct GMT_DATASEGMENT *S, struct GMT_LABEL *L, struct GMT_DECORATE *G) {
	/* Add a symbol location to the growing segment */
	double angle;
	struct GMT_DATASEGMENT_HIDDEN *SH = gmt_get_DS_hidden (S);
	if (S->n_rows == SH->n_alloc) {	/* Need more memory for the segment */
		uint64_t col;
		SH->n_alloc += GMT_SMALL_CHUNK;
		for (col = 0; col < S->n_columns; col++) {
			if ((S->data[col] = gmt_M_memory (GMT, S->data[col], SH->n_alloc, double)) == NULL) return;
			SH->alloc_mode[col] = GMT_ALLOC_INTERNALLY;
		}
		if ((S->text = gmt_M_memory (GMT, S->text, SH->n_alloc, char *)) == NULL) return;
		SH->alloc_mode_text = GMT_ALLOC_INTERNALLY;
	}
	/* Deal with any justifications or nudging */
	if (G->nudge_flag) {	/* Must adjust point a bit */
		double s = 0.0, c = 1.0, sign = 1.0;
		if (G->nudge_flag == 2) sincosdegree (L->line_angle, &s, &c);
		/* If N+1 or N-1 is used we want positive x nudge to extend away from end point */
		sign = (G->number_placement) ? (double)L->end : 1.0;
		L->x += sign * (G->nudge[GMT_X] * c - G->nudge[GMT_Y] * s);
		L->y += sign * (G->nudge[GMT_X] * s + G->nudge[GMT_Y] * c);
	}
	/* Build record with Cartesian (hence col = GMT_Z) "x y angle symbol" since we are using -Jx1i */
	S->data[GMT_X][S->n_rows] = L->x;
	S->data[GMT_Y][S->n_rows] = L->y;
	S->data[GMT_Z][S->n_rows] = gmt_M_to_inch (GMT, G->size);
	if (G->angle_type == GMT_ANGLE_LINE_DELTA) angle = G->symbol_angle + L->line_angle;
	else if (G->angle_type == GMT_ANGLE_LINE_FIXED) angle = G->symbol_angle;
	else angle = L->line_angle;
	S->data[3][S->n_rows] = angle;
	S->text[S->n_rows++] = strdup (G->symbol_code);
}

/*! . */
GMT_LOCAL void gmtsupport_decorated_line_sub (struct GMT_CTRL *GMT, double *xx, double *yy, uint64_t nn, struct GMT_DECORATE *G, struct GMT_DATASET *D, uint64_t seg) {
	/* The xxx, yyy are expected to be projected x/y inches.
	 * This function is modelled after gmtsupport_hold_contour_sub but tweaked to deal with
	 * the placement of psxy-symbols rather that text labels.  This is in most regards
	 * simpler than placing text so many lines related to text have been yanked.  There
	 * is the assumption that the symbols will be filled so we make no attempt to clip
	 * the lines as we do for contours/quated lines.  It would be very complicated to
	 * determine that clip path if the symbol is a star, for instance.  So if fill is
	 * not given then we will see the line beneath the symbol. */
	uint64_t i, j, start = 0;
	bool closed;
	double *track_dist = NULL, *map_dist = NULL, *value_dist = NULL;
	double dx, dy, width, f, this_dist, step, stept, lon[2], lat[2];
	struct GMT_DATASEGMENT *S = D->table[0]->segment[seg];	/* A single segment */
	struct GMT_LABEL L;	/* Needed to pick up angles */
	if (nn < 2) return;	/* You, sir, are not a line! */

	closed = (nn > 2 && !gmt_polygon_is_open (GMT, xx, yy, nn));	/* true if this is a polygon */

	/* Calculate distance along line and store in track_dist array */

	if (G->dist_kind == 1) gmt_xy_to_geo (GMT, &lon[1], &lat[1], xx[0], yy[0]);
	if ((map_dist = gmt_M_memory (GMT, NULL, nn, double)) == NULL) return;	/* Distances on map in inches */
	if ((track_dist = gmt_M_memory (GMT, NULL, nn, double)) == NULL) return;	/* May be km, degrees or whatever */
	if ((value_dist = gmt_M_memory (GMT, NULL, nn, double)) == NULL) return;	/* May be km, degrees or whatever */

	map_dist[0] = track_dist[0] = value_dist[0] = 0.0;	/* Unnecessary, just so we understand the logic */
	for (i = 1; i < nn; i++) {
		/* Distance from xy in plot distances (inch) */
		dx = xx[i] - xx[i-1];
		if (gmt_M_x_is_lon (GMT, GMT_IN) && GMT->current.map.is_world && fabs (dx) > (width = gmt_half_map_width (GMT, yy[i-1]))) {
			width *= 2.0;
			dx = copysign (width - fabs (dx), -dx);
			if (xx[i] < width)
				xx[i-1] -= width;
			else
				xx[i-1] += width;
		}
		dy = yy[i] - yy[i-1];
		step = stept = hypot (dx, dy);	/* Initially these steps are in inches */
		map_dist[i] = map_dist[i-1] + step;
		if (G->dist_kind == 1) {	/* Wanted spacing in map distance units */
			lon[0] = lon[1];	lat[0] = lat[1];
			gmt_xy_to_geo (GMT, &lon[1], &lat[1], xx[i], yy[i]);
			if (G->dist_kind == 1) step = gmtlib_distance_type (GMT, lon[0], lat[0], lon[1], lat[1], GMT_CONT_DIST);
		}
		track_dist[i] = track_dist[i-1] + step;
		value_dist[i] = value_dist[i-1] + stept;
	}

	if (G->spacing) {	/* Place symbols based on distance along lines */
		double last_label_dist, dist_offset, dist;

		dist_offset = (closed && G->dist_kind == 0) ? (1.0 - G->symbol_dist_frac) * G->symbol_dist_spacing : 0.0;	/* Only place symbols on closed contours longer than frac of dist_spacing */
		last_label_dist = 0.0;
		i = 1;
		while (i < nn) {
			dist = track_dist[i] + dist_offset - last_label_dist;
			if (dist > G->symbol_dist_spacing) {	/* Time for symbol */
				f = (dist - G->symbol_dist_spacing) / (track_dist[i] - track_dist[i-1]);
				if (f < 0.5) {
					L.x = xx[i] - f * (xx[i] - xx[i-1]);
					L.y = yy[i] - f * (yy[i] - yy[i-1]);
				}
				else {
					f = 1.0 - f;
					L.x = xx[i-1] + f * (xx[i] - xx[i-1]);
					L.y = yy[i-1] + f * (yy[i] - yy[i-1]);
				}
				this_dist = G->symbol_dist_spacing - dist_offset + last_label_dist;
				gmtsupport_decorated_angle (GMT, xx, yy, i - 1, i, G->symbol_angle, nn, false, &L, G);
				gmtsupport_add_decoration (GMT, S, &L, G);
				dist_offset = 0.0;
				last_label_dist = this_dist;
			}
			else	/* Go to next point in line */
				i++;
		}
	}
	else if (G->number) {	/* Place prescribed number of symbols evenly along lines */
		uint64_t nc;
		double dist;
		nc = (map_dist[nn-1] > G->min_dist) ? G->n_cont : 0;
		L.end = 0;
		for (i = j = 0; i < nc; i++) {
			if (G->number_placement && !closed) {
				dist = (G->n_cont > 1) ? i * track_dist[nn-1] / (G->n_cont - 1) : 0.5 * (G->number_placement + 1.0) * track_dist[nn-1];
				L.end = (G->number_placement && G->n_cont > 1) ? ((i == 0) ? -1 : +1) : G->number_placement;
			}
			else
				dist = (i + 1 - 0.5 * closed) * track_dist[nn-1] / (G->n_cont + 1 - closed);
			while (j < nn && track_dist[j] < dist) j++;
			if (j == nn) j--;	/* Safety precaution */
			f = ((j == 0) ? 1.0 : (dist - track_dist[j-1]) / (track_dist[j] - track_dist[j-1]));
			if (f < 0.5) {	/* Pick the smallest fraction to minimize Taylor shortcomings */
				L.x = xx[j-1] + f * (xx[j] - xx[j-1]);
				L.y = yy[j-1] + f * (yy[j] - yy[j-1]);
			}
			else {
				f = 1.0 - f;
				L.x = (j == 0) ? xx[0] : xx[j] - f * (xx[j] - xx[j-1]);
				L.y = (j == 0) ? yy[0] : yy[j] - f * (yy[j] - yy[j-1]);
			}
			L.node = (j == 0) ? 0 : j - 1;
			gmtsupport_decorated_angle (GMT, xx, yy, L.node, j, G->symbol_angle, nn, false, &L, G);
			gmtsupport_add_decoration (GMT, S, &L, G);
		}
	}
	else if (G->crossing) {	/* Determine label positions based on crossing lines */
		uint64_t left, right, line_no;
		struct GMT_DATASEGMENT *Sd = NULL;
		gmt_init_track (GMT, yy, nn, &(G->ylist));
		for (line_no = 0; line_no < G->X->n_segments; line_no++) {	/* For each of the crossing lines */
			Sd = G->X->table[0]->segment[line_no];	/* Current segment */
			gmt_init_track (GMT, Sd->data[GMT_Y], Sd->n_rows, &(G->ylist_XP));
			G->nx = (unsigned int)gmt_crossover (GMT, Sd->data[GMT_X], Sd->data[GMT_Y], NULL, G->ylist_XP, Sd->n_rows, xx, yy, NULL, G->ylist, nn, false, gmt_M_x_is_lon (GMT, GMT_IN), &G->XC);
			gmt_M_free (GMT, G->ylist_XP);
			if (G->nx == 0) continue;

			/* OK, we found intersections for labels */

			for (i = 0; i < (uint64_t)G->nx; i++) {
				left  = lrint (floor (G->XC.xnode[1][i]));
				right = lrint (ceil  (G->XC.xnode[1][i]));
				L.x = G->XC.x[i];	L.y = G->XC.y[i];
				gmtsupport_decorated_angle (GMT, xx, yy, left, right, G->symbol_angle, nn, false, &L, G);
				gmtsupport_add_decoration (GMT, S, &L, G);
			}
			gmt_x_free (GMT, &G->XC);
		}
		gmt_M_free (GMT, G->ylist);
	}
	else if (G->fixed) {	/* Prescribed point locations for labels that match points in input records */
		double dist, min_dist;
		for (j = 0; j < (uint64_t)G->f_n; j++) {	/* Loop over fixed point list */
			min_dist = DBL_MAX;
			for (i = 0; i < nn; i++) {	/* Loop over input line/contour */
				if ((dist = hypot (xx[i] - G->f_xy[0][j], yy[i] - G->f_xy[1][j])) < min_dist) {	/* Better fit */
					min_dist = dist;
					start = i;
				}
			}
			if (min_dist < G->slop) {	/* Closest point within tolerance */
				L.x = xx[start];	L.y = yy[start];
				gmtsupport_decorated_angle (GMT, xx, yy, start, start, G->symbol_angle, nn, false, &L, G);
				gmtsupport_add_decoration (GMT, S, &L, G);
			}
		}
	}

	gmt_M_free (GMT, track_dist);
	gmt_M_free (GMT, map_dist);
	gmt_M_free (GMT, value_dist);
}

/*! . */
GMT_LOCAL uint64_t gmtsupport_getprevpoint (double plon, double lon[], uint64_t n, uint64_t this_p) {
	/* Return the previous point that does NOT equal plon */
	uint64_t ip = (this_p == 0) ? n - 2 : this_p - 1;	/* Previous point (-2 because last is a duplicate of first) */
	while (doubleAlmostEqualZero (plon, lon[ip]) || doubleAlmostEqual (fabs(plon - lon[ip]), 360.0)) {	/* Same as plon */
		if (ip == 0)
			ip = n - 2;
		else
			ip--;
	}
	return (ip);
}

/*! . */
static inline bool gmtsupport_same_longitude (double a, double b) {
	/* return true if a and b are the same longitude */
	while (a < 0.0)   a += 360.0;
	while (a > 360.0) a -= 360.0;
	while (b < 0.0)   b += 360.0;
	while (b > 360.0) b -= 360.0;
	return doubleAlmostEqualZero (a, b);
}

#define gmt_M_same_latitude(A,B)  (doubleAlmostEqualZero (A,B))			/* A and B are the same latitude */

/*! . */
GMT_LOCAL int gmtsupport_inonout_sphpol_count (double plon, double plat, const struct GMT_DATASEGMENT *P, unsigned int count[]) {
	/* Case of a polar cap */
	uint64_t i, in, ip, prev;
	int cut;
	double W, E, S, N, lon, lon1, lon2, dlon, x_lat, dx1, dx2;

	/* Draw meridian through P and count all the crossings with the line segments making up the polar cap S */

	gmt_M_memset (count, 2, unsigned int);	/* Initialize counts to zero */
	for (i = 0; i < P->n_rows - 1; i++) {	/* -1, since we know last point repeats the first */
		/* Here lon1 and lon2 are the end points (in longitude) of the current line segment in S.  There are
		 * four cases to worry about:
		 * 1) lon equals lon1 (i.e., the meridian through lon goes right through lon1)
		 * 2) lon equals lon2 (i.e., the meridian through lon goes right through lon2)
		 * 3) lon lies between lon1 and lon2 and crosses the segment
		 * 4) none of the above
		 * Since we want to obtain either ONE or ZERO intersections per segment we will skip to next
		 * point if case (2) occurs: this avoids counting a crossing twice for consecutive segments.
		 */
		if (gmtsupport_same_longitude (plon, P->data[GMT_X][i]) && gmt_M_same_latitude (plat, P->data[GMT_Y][i])) return (GMT_ONEDGE);	/* Point is on the perimeter */
		in = i + 1;			/* Next point index */
		/* Next deal with case when the longitude of P goes ~right through the second of the line nodes */
		if (gmtsupport_same_longitude (plon, P->data[GMT_X][in])) continue;	/* Line goes through the 2nd node - ignore */
		lon1 = P->data[GMT_X][i];	/* Copy the first of two longitudes since we may need to mess with them */
		lon2 = P->data[GMT_X][in];	/* Copy the second of two longitudes since we may need to mess with them */
		if (gmtsupport_same_longitude (plon, lon1)) {	/* Line goes through the 1st node */
			/* Must check that the two neighboring points are on either side; otherwise it is just a tangent line */
			ip = gmtsupport_getprevpoint (plon, P->data[GMT_X], P->n_rows, i);	/* Index of previous point != plon */
			gmt_M_set_delta_lon (lon1, P->data[GMT_X][ip], dx1);	/* Allow for jumps across discontinuous 0 or 180 boundary */
			if (dx1 == 0.0) continue;	/* Points ip and i forms a meridian, we a tangent line */
			gmt_M_set_delta_lon (lon1, lon2, dx2);				/* Allow for jumps across discontinuous 0 or 180 boundary */
			if (dx1*dx2 > 0.0) continue;	/* Both on same side since signs are the same */
			cut = (P->data[GMT_Y][i] > plat) ? 0 : 1;	/* node is north (0) or south (1) of P */
			count[cut]++;
			prev = ip + 1;	/* Always exists because ip is <= n-2 */
			/* If prev < i then we have a vertical segment of 2 or more points; prev points to the other end of the segment.
			 * We must then check if our points plat is within that range, meaning the point lies on the segment */
			if (prev < i && ((plat <= P->data[GMT_Y][prev] && plat >= P->data[GMT_Y][i]) || (plat <= P->data[GMT_Y][i] && plat >= P->data[GMT_Y][prev]))) return (GMT_ONEDGE);	/* P is on segment boundary; we are done */
			continue;
		}
		/* OK, not exactly on a node, deal with crossing a line */
		dlon = lon2 - lon1;
		if (dlon > 180.0)		/* Jumped across Greenwich going westward */
			lon2 -= 360.0;
		else if (dlon < -180.0)		/* Jumped across Greenwich going eastward */
			lon1 -= 360.0;
		if (lon1 <= lon2) {	/* Segment goes W to E (or N-S) */
			W = lon1;
			E = lon2;
		}
		else {			/* Segment goes E to W */
			W = lon2;
			E = lon1;
		}
		lon = plon;			/* Local copy of plon, below adjusted given the segment lon range */
		while (lon > W) lon -= 360.0;	/* Make sure we rewind way west for starters */
		while (lon < W) lon += 360.0;	/* Then make sure we wind to inside the lon range or way east */
		if (lon > E) continue;	/* Not crossing this segment */
		if (dlon == 0.0) {	/* Special case of N-S segment: does P lie on it? */
			if (P->data[GMT_Y][in] < P->data[GMT_Y][i]) {	/* Get N and S limits for segment */
				S = P->data[GMT_Y][in];
				N = P->data[GMT_Y][i];
			}
			else {
				N = P->data[GMT_Y][in];
				S = P->data[GMT_Y][i];
			}
			if (plat < S || plat > N) continue;	/* P is not on this segment */
			return (1);	/* P is on segment boundary; we are done*/
		}
		/* Calculate latitude at intersection */
		if (gmt_M_same_latitude (P->data[GMT_Y][i], P->data[GMT_Y][in])) {	/* Special cases */
			if (gmt_M_same_latitude (plat, P->data[GMT_Y][in])) return (GMT_ONEDGE);	/* P is on S boundary */
			x_lat = P->data[GMT_Y][i];
		}
		else
			x_lat = P->data[GMT_Y][i] + ((P->data[GMT_Y][in] - P->data[GMT_Y][i]) / (lon2 - lon1)) * (lon - lon1);
		if (doubleAlmostEqualZero (x_lat, plat))
			return (1);	/* P is on S boundary */

		cut = (x_lat > plat) ? 0 : 1;	/* Cut is north (0) or south (1) of P */
		count[cut]++;
	}

	return (0);	/* This means no special cases were detected that warranted an immediate return */
}

/*! . */
GMT_LOCAL unsigned int gmtsupport_inonout_sphpol (struct GMT_CTRL *GMT, double plon, double plat, struct GMT_DATASEGMENT *S) {
/* This function is used to see if some point P = (plon, plat) is located inside, outside, or on the boundary of the
 * spherical polygon S read by GMT_import_table.  Note GMT->current.io.skip_duplicates must be true when the polygon
 * was read so there are NO duplicate (repeated) points.
 * Returns the following values:
 *	0:	P is outside of S
 *	1:	P is inside of S
 *	2:	P is on boundary of S
 */

	/* Algorithm:
	 * Case 1: The polygon S contains a geographical pole
	 *	   a) if P is beyond the far latitude then P is outside
	 *	   b) Draw meridian through P and count intersections:
	 *		odd: P is outside; even: P is inside
	 * Case 2: S does not contain a pole
	 *	   a) If P is outside range of latitudes then P is outside
	 *	   c) Draw meridian through P and count intersections:
	 *		odd: P is inside; even: P is outside
	 * In all cases, we check if P is on the outline of S
	 * Limitation: We assume points are closely spaced so that we can do linear
	 * approximation between successive points in the polygon.
	 */

	unsigned int count[2];
	struct GMT_DATASEGMENT_HIDDEN *SH = gmt_get_DS_hidden (S);
	gmt_M_unused(GMT);

	if (SH->pole) {	/* Case 1 of an enclosed polar cap */
		if (SH->pole == +1) {	/* N polar cap */
			if (plat < S->min[GMT_Y]) return (GMT_OUTSIDE);	/* South of a N polar cap */
			if (plat > SH->lat_limit) return (GMT_INSIDE);	/* Clearly inside of a N polar cap */
		}
		else if (SH->pole == -1) {	/* S polar cap */
			if (plat > S->max[GMT_Y]) return (GMT_OUTSIDE);	/* North of a S polar cap */
			if (plat < SH->lat_limit) return (GMT_INSIDE);	/* Clearly inside of a S polar cap */
		}

		/* Tally up number of intersections between polygon and meridian through P */

		if (gmtsupport_inonout_sphpol_count (plon, plat, S, count)) return (GMT_ONEDGE);	/* Found P is on S */

		if (SH->pole == +1 && count[0] % 2 == 0) return (GMT_INSIDE);
		if (SH->pole == -1 && count[1] % 2 == 0) return (GMT_INSIDE);

		return (GMT_OUTSIDE);
	}

	/* Here is Case 2.  First check latitude range */

	if (plat < S->min[GMT_Y] || plat > S->max[GMT_Y]) return (GMT_OUTSIDE);

	/* Longitudes are tricker and are tested with the tallying of intersections */

	if (gmtsupport_inonout_sphpol_count (plon, plat, S, count)) return (GMT_ONEDGE);	/* Found P is on S */

	if (count[0] % 2) return (GMT_INSIDE);

	return (GMT_OUTSIDE);	/* Nothing triggered the tests; we are outside */
}

/*! . */
GMT_LOCAL unsigned int gmtsupport_inonout_sub (struct GMT_CTRL *GMT, double x, double y, struct GMT_DATASEGMENT *S) {
	/* Front end for both spherical and Cartesian in-on-out functions */
	unsigned int side;

	if (GMT->current.proj.sph_inside) {	/* Assumes these are input polygons */
		struct GMT_DATASEGMENT_HIDDEN *SH = gmt_get_DS_hidden (S);
		if (SH->pole)	/* 360-degree polar cap, must check fully */
			side = gmtsupport_inonout_sphpol (GMT, x, y, S);
		else {	/* See if we are outside range of longitudes for polygon */
			while (x > S->min[GMT_X]) x -= 360.0;	/* Wind clear of west */
			while (x < S->min[GMT_X]) x += 360.0;	/* Wind east until inside or beyond east */
			if (x > S->max[GMT_X]) return (GMT_OUTSIDE);	/* Point outside, no need to assign value */
			side = gmtsupport_inonout_sphpol (GMT, x, y, S);
		}
	}
	else {	/* Flat Earth case */
		if (y < S->min[GMT_Y] || y > S->max[GMT_Y])
			return (GMT_OUTSIDE);	/* Point outside, no need to assign value */
		if (gmt_M_x_is_lon (GMT, GMT_IN)) {	/* Deal with longitude periodicity */
			if (x < S->min[GMT_X]) {
				x += 360.0;
				if (x > S->max[GMT_X])
					return (GMT_OUTSIDE);	/* Point outside, no need to assign value */
			}
			else if (x > S->max[GMT_X]) {
				x -= 360.0;
				if (x < S->min[GMT_X])
					return (GMT_OUTSIDE);	/* Point outside, no need to assign value */
			}
		}
		else if (x < S->min[GMT_X] || x > S->max[GMT_X])
			return (GMT_OUTSIDE);	/* Point outside, no need to assign value */
		/* It is essential that the longitudes in S are within the min/max limits since this is a Cartesian algorithm */
		side = gmt_non_zero_winding (GMT, x, y, S->data[GMT_X], S->data[GMT_Y], S->n_rows);
	}
	return (side);
}

int gmt_signum (double x) {
	/* The standard sign function */
	if (x < 0.0) return -1;
	if (x > 0.0) return +1;
	return 0;
}

#ifdef TRIANGLE_D

/*
 * New gmt_delaunay interface routine that calls the triangulate function
 * developed by Jonathan Richard Shewchuk, University of California at Berkeley.
 * Suggested by alert GMT user Alain Coat.  You need to get triangle.c and
 * triangle.h from www.cs.cmu.edu/~quake/triangle.html
 */

#define REAL double
#define ANSI_DECLARATORS
#include "triangle.h"

/* Leave link as int**, not uint64_t** */
/*! . */
GMT_LOCAL uint64_t gmtsupport_delaunay_shewchuk (struct GMT_CTRL *GMT, double *x_in, double *y_in, uint64_t n, int **link) {
	/* GMT interface to the triangle package; see above for references.
	 * All that is done is reformatting of parameters and calling the
	 * main triangulate routine.  Thanx to Alain Coat for the tip.
	 */

	uint64_t i, j;
	struct triangulateio In, Out, vorOut;

	GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Delaunay triangulation calculated by Jonathan Shewchuk's Triangle [http://www.cs.cmu.edu/~quake/triangle.html]\n");

	/* Set everything to 0 and NULL */

	gmt_M_memset (&In,     1, struct triangulateio);
	gmt_M_memset (&Out,    1, struct triangulateio);
	gmt_M_memset (&vorOut, 1, struct triangulateio);

	/* Allocate memory for input points */

	In.numberofpoints = (int)n;
	if ((In.pointlist = gmt_M_memory (GMT, NULL, 2 * n, double)) == NULL) return (0);

	/* Copy x,y points to In structure array */

	for (i = j = 0; i < n; i++) {
		In.pointlist[j++] = x_in[i];
		In.pointlist[j++] = y_in[i];
	}

	/* Call Jonathan Shewchuk's triangulate algorithm.  This is 64-bit safe since
	 * all the structures use 4-byte ints (longs are used internally). The options are
	 *  z : Start numbering at zero instead of 1.
	 *	I : No iteration numbers
	 *  Q : Quiet - suppress all explanations
	 *  B : Suppresses output of boundary information
	 *  D : Conforming Delaunay:  all triangles are truly Delaunay.
	 */

	triangulate ("zIQBD", &In, &Out, &vorOut);

	*link = Out.trianglelist;	/* List of node numbers to return via link [NOT ALLOCATED BY gmt_M_memory] */

	gmt_M_str_free (Out.pointlist);
	gmt_M_free (GMT, In.pointlist);

	return (Out.numberoftriangles);
}

/*! . */
GMT_LOCAL struct GMT_DATASET * gmtsupport_voronoi_shewchuk (struct GMT_CTRL *GMT, double *x_in, double *y_in, uint64_t n64, double *wesn, unsigned int mode) {
	/* GMT interface to the triangle package; see above for references.
	 * All that is done is reformatting of parameters and calling the
	 * main triangulate routine.  Here we return Voronoi information
	 * and package the coordinates of the edges in the output dataset.
	 * The wesn[] array contains the min/max x (or lon) and y (or lat) coordinates.
	 * Since the internal variables in triangle are ints (e.g., edgelist) we use
	 * ints here as well
	 */

	/* Currently we only write the edges of a Voronoi cell but we want polygons later.
	 * Info from triangle re Voronoi polygons: "Triangle does not write a list of
	 * the edges adjoining each Voronoi cell, but you can reconstructed it straightforwardly.
	 * For instance, to find all the edges of Voronoi cell 1, search the output .edge file
	 * for every edge that has input vertex 1 as an endpoint.  The corresponding dual
	 * edges in the output .v.edge file form the boundary of Voronoi cell 1." */

#ifdef DEBUG	/* Developers need to see more here with -V */
	unsigned int verbose = GMT_MSG_INFORMATION;
#else
	unsigned int verbose = GMT_MSG_DEBUG;
#endif

	uint64_t dim[GMT_DIM_SIZE] = {1, 0, 2, 2};
	int i, j, k, n, km1, j2, i2, seg, n_int_edges, n_edges, first_edge = 0, n_extra = 0, np_alloc;
	int n_outside_wesn = 0, n_int_vertex = 0, p = 0, corners = 0, n_vertex, n_edges_2;
	unsigned int geometry, side, corner;
	bool move[4] = {false, false, false, false};
	char header[GMT_LEN64] = {""};
	unsigned char *point_type = NULL;
	struct triangulateio In, Out, vorOut;
	struct GMT_DATASET *P = NULL;
	struct GMT_DATASEGMENT *S = NULL;
	double dx, dy, new_x, xe, ye, xp, yp, v_wesn[4], orig_wesn[4];

	GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Voronoi partitioning calculated by Jonathan Shewchuk's Triangle [http://www.cs.cmu.edu/~quake/triangle.html]\n");

	/* Set everything to 0 and NULL */

	gmt_M_memset (&In,     1, struct triangulateio);
	gmt_M_memset (&Out,    1, struct triangulateio);
	gmt_M_memset (&vorOut, 1, struct triangulateio);

	/* Allocate memory for input points */

	In.numberofpoints = n = (int)n64;
	if ((In.pointlist = gmt_M_memory (GMT, NULL, 2 * n, double)) == NULL) return (0);

	/* Copy x,y points to In structure array */

	for (i = j = 0; i < n; i++) {
		In.pointlist[j++] = x_in[i];
		In.pointlist[j++] = y_in[i];
	}

	/* Call Jonathan Shewchuk's triangulate algorithm.  This is 64-bit safe since
	 * all the structures use 4-byte ints (longs are used internally). The options are
	 *  z : Start numbering at zero instead of 1.
	 *	I : No iteration numbers
	 *  Q : Quiet - suppress all explanations
	 *  B : Suppresses output of boundary information
	 *  v : Get Voronoi vertices.
	 *  D : Conforming Delaunay:  all triangles are truly Delaunay.
	 *  j : jettison unused vertices from list.
	 */

	triangulate ("zIQBvDj", &In, &Out, &vorOut);

	/* Determine output size for all edges */

	n_int_edges = vorOut.numberofedges;		/* Number of edges found; some are from point i to j while others are infinite rays */
	n_int_vertex = vorOut.numberofpoints;	/* Number of voronoi points found */
	/* Count number of infinite rays */
	for (i = 0, k = 0; i < n_int_edges; i++, k += 2)
		if (vorOut.edgelist[k+1] == -1) n_extra++;	/* Infinite rays */
	/* Count Voronoi vertices outside specified w/e/s/n region and update v_wesn region to ensure we enclose them all */
	gmt_M_memcpy (orig_wesn, wesn, 4, double);	gmt_M_memcpy (v_wesn, wesn, 4, double);
	for (i = k = 0; i < n_int_vertex; i++, k += 2) {
		if (vorOut.pointlist[k] < wesn[XLO])   v_wesn[XLO] = vorOut.pointlist[k], move[XLO] = true;
		if (vorOut.pointlist[k] > wesn[XHI])   v_wesn[XHI] = vorOut.pointlist[k], move[XHI] = true;
		if (vorOut.pointlist[k+1] < wesn[YLO]) v_wesn[YLO] = vorOut.pointlist[k+1], move[YLO] = true;
		if (vorOut.pointlist[k+1] > wesn[YHI]) v_wesn[YHI] = vorOut.pointlist[k+1], move[YHI] = true;
		if (vorOut.pointlist[k] < wesn[XLO] || vorOut.pointlist[k] > wesn[XHI] || vorOut.pointlist[k+1] < wesn[YLO] || vorOut.pointlist[k+1] > wesn[YHI])
			n_outside_wesn++;
	}
	if (n_outside_wesn) {	/* Extend v_wesn by a tiny bit to avoid any point exactly on wesn boundary */
		dx = 1e-4 * (v_wesn[XHI] - v_wesn[XLO]);
		if (move[XLO]) v_wesn[XLO] -= dx;	if (move[XHI]) v_wesn[XHI] += dx;
		dy = 1e-4 * (v_wesn[YHI] - v_wesn[YLO]);
		if (move[YLO]) v_wesn[YLO] -= dy;	if (move[YHI]) v_wesn[YHI] += dy;
#ifdef DEBUG
		GMT_Report (GMT->parent, verbose, "Given w/e/s/n:    %lg/%lg/%lg/%lg\n",  wesn[XLO],  wesn[XHI],  wesn[YLO], wesn[YHI]);
		GMT_Report (GMT->parent, verbose, "Adjusted w/e/s/n: %lg/%lg/%lg/%lg\n",  v_wesn[XLO],  v_wesn[XHI],  v_wesn[YLO], v_wesn[YHI]);
#endif
		gmt_M_memcpy (wesn, v_wesn, 4, double);	/* Use these limits instead */
	}
	/* Here, wesn is such that all Voronoi points are inside, hence it is only infinite rays that will intersect wesn box */
#ifdef DEBUG
	GMT_Report (GMT->parent, verbose, "Output from triangulate:\n");
	for (i = k = 0; i < n_int_edges; i++, k += 2) {
		if (vorOut.edgelist[k+1] == -1)
			GMT_Report (GMT->parent, verbose, "Edge %8" PRIu64 " Point %8d to infinity normlist = %8g\t%8g slp = %8g\n", i, vorOut.edgelist[k], vorOut.normlist[k], vorOut.normlist[k+1], (vorOut.normlist[k] / vorOut.normlist[k+1]));
		else
			GMT_Report (GMT->parent, verbose, "Edge %8" PRIu64 " Point %8d to %8d\n", i, vorOut.edgelist[k], vorOut.edgelist[k+1]);
	}
	for (i = k = 0; i < n_int_vertex; i++, k += 2)
		GMT_Report (GMT->parent, verbose, "Point %8" PRIu64 " at %g\t%g\n", i, vorOut.pointlist[k], vorOut.pointlist[k+1]);
#endif
	GMT_Report (GMT->parent, verbose, "n_vertex = %d n_edge = %d n_inf_rays = %d n_outside = %d\n", n_int_vertex, n_int_edges, n_extra, n_outside_wesn);
 
	p = 2 * n_int_vertex;		/* Index into vorOut.pointlist for next point to be added along boundary */
	n_vertex = n_int_vertex;	/* Number of all vertices so far */

	if (mode) {	/* Want closed Voronoi polygons, so must allocate more space to hold boundary rays and corners */
		corners = 4;		/* Need to add this many boundingbox corner coordinates */
		dim[GMT_SEG] = n;	/* When all Voronoi polygons are closed there will be one surrounding each input data point */
		dim[GMT_ROW] = 0;	/* Variable row length so cannot specify it here - allocate later */
		geometry = GMT_IS_POLY;	/* Since we will be making closed polygons */
		/* Allocate array for point type.  This holds which side we exited.  Normally 0-3, here we add 1 to use 1-4
		 * instead since here, 0 means interior point.  1 is south and then we go CCW to 2 (east), 3 (north) and 4 (west) */
		if ((point_type = gmt_M_memory (GMT, NULL, n_int_edges + n_int_vertex + corners, char)) == NULL) return (0);
	}
	else {	/* Want line edges only, all dimensions are already known */
		dim[GMT_SEG] = n_int_edges;	/* All dimensions are known since we issue just 1 line per segment */
		geometry = GMT_IS_LINE;	/* Since we only report edges */
	}
	/* Create dataset with a single table with one segment per edge or polygon */
	if ((P = GMT_Create_Data (GMT->parent, GMT_IS_DATASET, geometry, 0, dim, NULL, NULL, 0, 0, NULL)) == NULL) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Unable to create a data set for gmtsupport_voronoi_shewchuk\n");
		gmt_M_free (GMT, point_type);
		GMT->parent->error = GMT_RUNTIME_ERROR;
		return NULL;
	}

	/* Reallocate the triangle arrays to hold the extra vertices we will need to add */
	vorOut.pointlist = realloc (vorOut.pointlist, 2 * (n_int_vertex + n_extra + corners) * sizeof (double));
	vorOut.edgelist  = realloc (vorOut.edgelist,  2 * (n_int_edges  + n_extra + corners) * sizeof (int));

	/* First replace infinite rays with finite points where they intersect the border (i.e., we clip the rays to w/e/s/n) */

	for (i = k = 0; i < n_int_edges; i++, k++) {
		km1 = k++;	/* Index to this edgelist's first point */
		j2 = 2 * vorOut.edgelist[km1];	/* Index into pointlist with x-coordinate of this edge point */
		/* Get the coordinates of the point P; this could be an interior [keep] or exterior Voronoi vertex [to be skipped] */
		xp = vorOut.pointlist[j2++];
		yp = vorOut.pointlist[j2];
		if (vorOut.edgelist[k] == -1) {	/* Infinite ray; calculate intersection with region boundary */
			/* Each edgelist always has a Voronoi vertex as the first point so j2 is never 2 * (-1) */
			/* Determine (xe, ye), the intersection of the ray and the bounding box */
			if (vorOut.normlist[km1] < 0.0) {	/* Slope pointing to the left; Ray will intersect x = xmin, called side = 4 */
				xe = wesn[XLO];	side = 4;
			}
			else {	/* Slope pointing to the right; Ray will intersect x = xmax, called side = 2 */
				xe = wesn[XHI];	side = 2;
			}
			/* Compute y-value at the intersection of ray with border */
			dy = fabs ((vorOut.normlist[k] / vorOut.normlist[km1]) * (xe - xp));
			ye = yp + dy * copysign (1.0, vorOut.normlist[k]);
			if (ye < wesn[YLO]) {	/* Crossed south before west or east: Recompute the x-crossing along y = ymin instead and set ye to ymin */
				side = 1;	/* South */
				new_x = xp + (wesn[YLO] - yp) * (xe - xp) / (ye - yp);
				GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Voronoi infinite ray truncated from %g %g to %g %g\n", xe, ye, new_x, wesn[YLO]);
				xe = new_x;	ye = wesn[YLO];
			}
			else if (ye > wesn[YHI]) {	/* Crossed north before west or east: Recompute the x-crossing along y = ymax instead  and set ye to ymax */
				side = 3;	/* North */
				new_x = xp + (wesn[YHI] - yp) * (xe - xp) / (ye - yp);
				GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Voronoi infinite ray truncated from %g %g to %g %g\n", xe, ye, new_x, wesn[YHI]);
				xe = new_x;	ye = wesn[YHI];
			}
			/* Update the truncated ray (-1) in the edge list with a new vertex and add the vertex coordinates to pointlist */
			if (mode) point_type[n_vertex] = (unsigned char)side;	/* Mark as a border point 1-4 */
			vorOut.edgelist[k] = n_vertex++;		/* Replace the -1 with the new point on the boundary */
			vorOut.pointlist[p++] = xe;				/* Add the ray intersection coordinates to the pointlist */
			vorOut.pointlist[p++] = ye;
		}
	}

	/* Now edgelist only contains actual point IDs and pointlist has been updated to hold all added border points */

#ifdef DEBUG
		GMT_Report (GMT->parent, verbose, "After infinite ray and exterior vertex crossing replacements:\n");
		for (i = k = 0; i < n_int_edges; i++, k += 2) {
			if (vorOut.edgelist[k+1] == -1)
				GMT_Report (GMT->parent, verbose, "Edge %8" PRIu64 " Point %8d to infinity normlist = %8g\t%8g slp = %8g\n", i, vorOut.edgelist[k], vorOut.normlist[k], vorOut.normlist[k+1], (vorOut.normlist[k]/ vorOut.normlist[k+1]));
			else
				GMT_Report (GMT->parent, verbose, "Edge %8" PRIu64 " Point %8d to %8d\n", i, vorOut.edgelist[k], vorOut.edgelist[k+1]);
		}
		for (i = k = 0; i < n_vertex; i++, k += 2)
			GMT_Report (GMT->parent, verbose, "Point %8" PRIu64 " at %g\t%g\n", i, vorOut.pointlist[k], vorOut.pointlist[k+1]);
#endif

	if (mode) {	/* Need to make closed polygons from edges */
		bool first_turn, go_i, go_j;
		signed char *edge_use = NULL;
		int expected_sign = 0, prev_sign, next_sign, *start_vertex = NULL, *stop_vertex = NULL;
		int64_t edge, pstart, pstop, start_point, next_point, prev_point, np;
		double xstart, xstop, xend, ystart, ystop, yend, cross_product;
		double *xcoord = NULL, *ycoord = NULL, *dx = NULL, *dy = NULL, *x_pos = NULL, *y_pos = NULL;
		/* Add the 4 border corners to the point list as well and mark them as corners with special side = 5-8 (i.e., 4 + side 1-4).
		   We need different sides for corners since xmax,ymax is the end for two separate axes. */
		vorOut.pointlist[p++] = wesn[XHI];	vorOut.pointlist[p++] = wesn[YLO];	point_type[n_vertex++] = 5;
		vorOut.pointlist[p++] = wesn[XHI];	vorOut.pointlist[p++] = wesn[YHI];	point_type[n_vertex++] = 6;
		vorOut.pointlist[p++] = wesn[XLO];	vorOut.pointlist[p++] = wesn[YHI];	point_type[n_vertex++] = 7;
		vorOut.pointlist[p++] = wesn[XLO];	vorOut.pointlist[p++] = wesn[YLO];	point_type[n_vertex++] = 8;

#ifdef DEBUG
		GMT_Report (GMT->parent, verbose, "Before border edges are added:\n");
		for (i = k = 0; i < n_int_edges; i++, k += 2)
			GMT_Report (GMT->parent, verbose, "Edge %8" PRIu64 " Point %8d to %8d normlist = %8g\t%8g\n", i, vorOut.edgelist[k], vorOut.edgelist[k+1], vorOut.normlist[k], vorOut.normlist[k+1]);
		for (i = k = 0; i < n_vertex; i++, k += 2)
			GMT_Report (GMT->parent, verbose, "Point %8" PRIu64 " [%d] at %g\t%g\n", i, point_type[i], vorOut.pointlist[k], vorOut.pointlist[k+1]);
#endif
		/* Finally add the new edges between new points along the border and with the corners */
		/* Do the y = ymin and y = ymax sides first (i.e., side 1 and 3) */
		edge = 2 * n_int_edges;	/* Start index of next added edge in edgelist */
		for (side = 1; side <= 3; side += 2) {	/* Since almost the same logic for the two sides */
			corner = (side == 1) ? 5 : 6;	/* The corner at the end of this x-axis */
			xstart = wesn[XLO];	pstart = (side == 1) ? n_vertex - 1 : n_vertex - 2;	/* Initialize the start of the edge at beginning of x-axis */
			xstop  = xend  = wesn[XHI];	pstop  = (side == 1) ? n_vertex - 4 : n_vertex - 3;	/* End of x-axis is end of edge unless there are intersections */
			while (xstart < wesn[XHI]) {	/* As long as we have incomplete edges */
				for (i = n_int_vertex; i < n_vertex; i++) {	/* Must check all of them for one that could be a candidate along this x-axis */
					if (!(point_type[i] == side || point_type[i] == corner)) continue;	/* Not along the x-axis including the end corner */
					j2 = 2 * i;	/* Index into pointlist for the x-coordinate */
					if (vorOut.pointlist[j2] <= xstop && vorOut.pointlist[j2] > xstart) {	/* An intersection closer to the start of our edge, update xstop */
						xstop = vorOut.pointlist[j2];
						pstop = i;
					}
				}
				/* Here, xstop is the point closest to xstart and pstop is its index. */
				/* Add this edge to edgelist */
				vorOut.edgelist[edge++] = (int)pstart;	vorOut.edgelist[edge++] = (int)pstop;
				pstart = pstop;	xstart = xstop;	xstop = xend;	/* Let the end of this edge become start of the next edge */
			}
		}
		/* Do the xmin and xmax sides next (sides 2 and 4) */
		for (side = 2; side <= 4; side += 2) {
			corner = (side == 2) ? 6 : 7;	/* The corner at the end of this y-axis */
			ystart = wesn[YLO];	pstart = (side == 2) ? n_vertex - 4 : n_vertex - 1;	/* Initialize the start of the edge at beginning of y-axis */
			ystop  = yend = wesn[YHI];	pstop  = (side == 2) ? n_vertex - 3 : n_vertex - 2;	/* End of y-axis is end of edge unless there are intersections */
			while (ystart < wesn[YHI]) {	/* As long as we have incomplete edges */
				for (i = n_int_vertex; i < n_vertex; i++) {	/* Must check all of them for one that could be a candidate along this y-axis */
					if (!(point_type[i] == side || point_type[i] == corner)) continue;	/* Not along the y-axis including the end corner */
					j2 = 2 * i + 1;	/* Index into pointlist for the y-coordinate */
					if (vorOut.pointlist[j2] <= ystop && vorOut.pointlist[j2] > ystart) {	/* An intersection closer to the start of our edge, update ystop */
						ystop = vorOut.pointlist[j2];
						pstop = i;
					}
				}
				/* Here, ystop is the point closest to xstart and pstop is its index. */
				/* Add this edge to edgelist */
				vorOut.edgelist[edge++] = (int)pstart;			vorOut.edgelist[edge++] = (int)pstop;
				pstart = pstop;	ystart = ystop;	ystop = yend;	/* Let the end of this edge become start of the next edge */
			}
		}
		n_edges = (int)edge;	/* Total number of all edges times 2 */
#ifdef DEBUG
		GMT_Report (GMT->parent, verbose, "\nAfter border edges are added:\n");
		for (i = k = 0; k < n_edges; i++, k += 2) {
			if (i < n_int_edges)
				GMT_Report (GMT->parent, verbose, "Edge %8" PRIu64 " Point %8d to %8d normlist = %8g\t%8g\n", i, vorOut.edgelist[k], vorOut.edgelist[k+1], vorOut.normlist[k], vorOut.normlist[k+1]);
			else
				GMT_Report (GMT->parent, verbose, "Edge %8" PRIu64 " Point %8d to %8d\n", i, vorOut.edgelist[k], vorOut.edgelist[k+1]);
		}
		for (i = k = 0; i < n_vertex; i++, k += 2)
			GMT_Report (GMT->parent, verbose, "Point %8" PRIu64 " [%d] at %g\t%g\n", i, point_type[i], vorOut.pointlist[k], vorOut.pointlist[k+1]);
#endif
		gmt_M_free (GMT, point_type);

		vorOut.normlist = realloc (vorOut.normlist, n_edges * sizeof (double));
		/* Remove the unneeded external edges flagged by two -1 signs in the edgelist */
		for (j2 = i2 = 0; j2 < n_edges; j2 += 2) {	/* For all the edges */
			if (i2 < j2) {	/* Shuffle the entries to lower indices */
				vorOut.edgelist[i2] = vorOut.edgelist[j2];
				vorOut.edgelist[i2+1] = vorOut.edgelist[j2+1];
				vorOut.normlist[i2] = vorOut.normlist[j2];
				vorOut.normlist[i2+1] = vorOut.normlist[j2+1];
			}
			if (!(vorOut.edgelist[j2] == -1 && vorOut.edgelist[j2+1] == -1)) i2 += 2;	/* Only increment output index when not a dummy edge */
		}
		/* Update the count of edges.  All the unneeded edges will lie within the original n_int_edges section */
		n_edges -= (j2 - i2);
		n_int_edges -= ((j2 - i2)/2);
#ifdef DEBUG
		GMT_Report (GMT->parent, verbose, "\nAfter removing unused edges:\n");
		for (i = k = 0; k < n_edges; i++, k += 2) {
			if (i < n_int_edges)
				GMT_Report (GMT->parent, verbose, "Edge %8" PRIu64 " Point %8d to %8d normlist = %8g\t%8g\n", i, vorOut.edgelist[k], vorOut.edgelist[k+1], vorOut.normlist[k], vorOut.normlist[k+1]);
			else
				GMT_Report (GMT->parent, verbose, "Edge %8" PRIu64 " Point %8d to %8d\n", i, vorOut.edgelist[k], vorOut.edgelist[k+1]);
		}
#endif

		/* Precalculate dx, dy for each edge and store these in normlist (which we need to reallocate first) */
		n_edges_2 = n_edges / 2;
		if ((edge_use = gmt_M_memory (GMT, NULL, n_edges_2, signed char)) == NULL) return (0);	/* 0 = unused, +/-1 = used once in normal or reverse direction, 2 = used twice and done with */
		dx = vorOut.normlist;	dy = &vorOut.normlist[1];	/* So we can use dx[index] and dy[index] */
		start_vertex = vorOut.edgelist;	stop_vertex = &vorOut.edgelist[1];
		x_pos = vorOut.pointlist;	y_pos = &vorOut.pointlist[1];
		for (i = k = 0; k < n_edges; i++, k += 2) {	/* For all the edges */
			i2 = 2 * start_vertex[k];	/* Location of x and y coordinates for start of edge */
			j2 = 2 * stop_vertex[k];	/* Location of x and y coordinates for end of edge */
			dx[k] = x_pos[j2] - x_pos[i2];	/* dx = end_x - start_x */
			dy[k] = y_pos[j2] - y_pos[i2];	/* dy = end_y - start_y */
			if (i >= n_int_edges) edge_use[i] = 1;	/* These edges will only be used once (sign is not important here) */
		}
		/* Need temp array to hold the coordinates of a single polygon [I hope this is large enough - don't know yet] */
		np_alloc = 2 * n_int_edges;
		if ((xcoord = gmt_M_memory (GMT, NULL, np_alloc, double)) == NULL) return (0);
		if ((ycoord = gmt_M_memory (GMT, NULL, np_alloc, double)) == NULL) return (0);

		/* Now stitch together the closed polygons */
		seg = 0;
		first_turn = true;	/* When we find the first 3 points in a polygon we can compute the cross-product and determine sign for all polygons */
		while (seg < n) {
			/* Find the first interior edge that has not already been used twice */
			for (i = first_edge, go_i = true; go_i && i < n_int_edges; i++) {
				if (edge_use[i] == 2) {	/* Done with this edge */
					first_edge++;	/* Might as well skip this one from now on */
					continue;
				}
				/* Here, i2 = 2*i is the index into the edgelist and normlist arrays for the previous edge */
				i2 = 2 * i;
				if (edge_use[i] == +1) {	/* Must reverse direction the 2nd time we start with this edge */
					start_point = prev_point = stop_vertex[i2];
					next_point = start_vertex[i2];
					prev_sign = -1;		/* Since we are reversing this edge */
					edge_use[i] = 2;	/* Flag we are finished with this edge */
				}
				else if (edge_use[i] == -1) {	/* Go in the forward direction the 2nd time we start with this edge */
					start_point = prev_point = start_vertex[i2];
					next_point = stop_vertex[i2];
					prev_sign = +1;	/* Since we are NOT reversing this edge */
					edge_use[i] = 2;	/* Flag we are finished with this edge */
				}
				else {	/* Go in the forward direction the first time */
					start_point = prev_point = start_vertex[i2];
					next_point = stop_vertex[i2];
					prev_sign = +1;	/* Since we are NOT reversing this edge */
					edge_use[i] = 1;	/* Flag we have used this edge one more time */
				}
				/* Add this edge as the first line in the new polygon */
				xcoord[0] = x_pos[2*start_point];	ycoord[0] = y_pos[2*start_point];
				xcoord[1] = x_pos[2*next_point];	ycoord[1] = y_pos[2*next_point];
				np = 2;	/* Total points in this polygon so far */
				while (next_point != start_point) {	/* When this is false we have automatically closed the polygon */
					/* Find first edge of all edges not equal the current edge that has next_point either as 1st or 2nd vertex and the other vertex is not our prev_point */
					for (j = first_edge, go_j = true; go_j && j < n_edges_2; j++) {
						if (j == i || edge_use[j] == 2) continue;	/* Either the same edge or we are already done with this edge */
						/* Here, j2 = 2*j is the index into the edgelist and normlist arrays for the next edge */
						j2 = 2 * j;
						if (start_vertex[j2] == next_point && stop_vertex[j2] != prev_point)	/* Must go in forward order */
							next_sign = 1;
						else if (stop_vertex[j2] == next_point && start_vertex[j2] != prev_point)	/* Go in reverse order */
							next_sign = -1;
						else	/* Not a desired edge since we could not match the vertex number */
							continue;

						/* Here we found an edge candidate, but we don't know if it leads to a convex angle */
						cross_product = dx[i2] * dy[j2] - dx[j2] * dy[i2];	/* This should be negative for right turns */
						if (first_turn) {	/* First pair of edges defines the desired sign of all the subsequent cross-products */
							expected_sign = prev_sign * next_sign * gmt_signum (cross_product);	/* sign may flip if any edge was reversed */
							first_turn = false;
						}
						else if ((prev_sign * next_sign * gmt_signum (cross_product)) != expected_sign)	/* Not making a convex polygon */
							continue;

						/* Here we are going in a convex direction, so we add this new edge to the polygon */
						prev_point = next_point;
						next_point = (next_sign == 1) ? stop_vertex[j2] : start_vertex[j2];
						prev_sign = next_sign;
						i2 = j2;
						/* Add next_point to our polygon */
						assert (np < np_alloc);	/* Otherwise we want to know */
						xcoord[np] = x_pos[2*next_point];
						ycoord[np] = y_pos[2*next_point];
						if (edge_use[j])	/* Now used twice */
							edge_use[j] = 2;
						else	/* Flag according to which direction we used it */
							edge_use[j] = (char)next_sign;
						np++;	/* Increase polygon length counter */
						go_j = false;	/* Exit this loop and search for next edge */
					}
				}
				/* Finalize the polygon */
				snprintf (header, GMT_LEN64, "Voronoi polygon # %d -L%d", seg, seg);
				S = P->table[0]->segment[seg] = GMT_Alloc_Segment (GMT->parent, GMT_NO_STRINGS, np, 2U, header, P->table[0]->segment[seg]);
				gmt_M_memcpy (S->data[GMT_X], xcoord, np, double);
				gmt_M_memcpy (S->data[GMT_Y], ycoord, np, double);
				P->table[0]->n_records += np;	/* Update counts */
				P->n_records += np;
				seg++;
				go_i = false;	/* Exit loop and move to the next polygon */
			}
		}
		/* Free temporary arrays */
		gmt_M_free (GMT, xcoord);
		gmt_M_free (GMT, ycoord);
		gmt_M_free (GMT, edge_use);
	}
	else {	/* Only want line edges */
		for (seg = k = 0; seg < n_int_edges; seg++) {
			j2 = 2 * vorOut.edgelist[k++];
			S = P->table[0]->segment[seg];	/* Current output edge segment */
			S->data[GMT_X][0] = vorOut.pointlist[j2++];
			S->data[GMT_Y][0] = vorOut.pointlist[j2];
			j2 = 2 * vorOut.edgelist[k++];
			S->data[GMT_X][1] = vorOut.pointlist[j2++];
			S->data[GMT_Y][1] = vorOut.pointlist[j2];
			snprintf (header, GMT_LEN64, "Voronoi edge # %d -L%d", seg, seg);
			S->header = strdup (header);
		}
	}

	if (n_outside_wesn)	/* Reset region */
		gmt_M_memcpy (wesn, orig_wesn, 4, double);

	gmt_set_dataset_minmax (GMT, P);	/* Determine min/max for each column */

	/* Free the triangulate arrays that were all allocated internally */
	gmt_M_str_free (Out.pointlist);
	gmt_M_str_free (Out.trianglelist);
	gmt_M_str_free (vorOut.pointattributelist);
	gmt_M_str_free (vorOut.pointlist);
	gmt_M_str_free (vorOut.edgelist);
	gmt_M_str_free (vorOut.normlist);
	gmt_M_free (GMT, In.pointlist);

	return (P);
}
#else
/*! Dummy functions since not installed */
GMT_LOCAL uint64_t gmtsupport_delaunay_shewchuk (struct GMT_CTRL *GMT, double *x_in, double *y_in, uint64_t n, int **link) {
	gmt_M_unused (x_in);
	gmt_M_unused (y_in);
	gmt_M_unused (n);
	gmt_M_unused (link);
	GMT_Report (GMT->parent, GMT_MSG_ERROR, "unavailable: Shewchuk's triangle option was not selected during GMT installation\n");
	return (0);
}

/*! . */
GMT_LOCAL struct GMT_DATASET * gmtsupport_voronoi_shewchuk (struct GMT_CTRL *GMT, double *x_in, double *y_in, uint64_t n, double *wesn, unsigned int mode) {
	gmt_M_unused (x_in);
	gmt_M_unused (y_in);
	gmt_M_unused (n);
	gmt_M_unused (wesn);
	gmt_M_unused (mode);
	GMT_Report (GMT->parent, GMT_MSG_ERROR, "unavailable: Shewchuk's triangle option was not selected during GMT installation\n");
	return (NULL);
}
#endif

/*
 * gmt_delaunay performs a Delaunay triangulation on the input data
 * and returns a list of indices of the points for each triangle
 * found.  Algorithm translated from
 * Watson, D. F., ACORD: Automatic contouring of raw data,
 *   Computers & Geosciences, 8, 97-101, 1982.
 */

struct GMT_PAIR {
	double x, y;
	uint64_t rec;
};

/*! . */
GMT_LOCAL int gmtsupport_sort_pair (const void *p_1, const void *p_2) {
	const struct GMT_PAIR *point_1 = (const struct GMT_PAIR *)p_1, *point_2 = (const struct GMT_PAIR *)p_2;

	if (point_1->x < point_2->x) return -1;
	if (point_1->x > point_2->x) return +1;
	if (point_1->y < point_2->y) return -1;
	if (point_1->y > point_2->y) return +1;
	return 0;
}

/* Leave link as int**, not int** */
/*! . */
GMT_LOCAL uint64_t gmtsupport_delaunay_watson (struct GMT_CTRL *GMT, double *x_in, double *y_in, uint64_t n, int **link) {
	/* Input point x coordinates */
	/* Input point y coordinates */
	/* Number of input points */
	/* pointer to List of point ids per triangle.  Vertices for triangle no i
	   is in link[i*3], link[i*3+1], link[i*3+2] */

	int *index = NULL;	/* Must be int not uint64_t */
	int ix[3], iy[3];
	bool done;
	uint64_t i, j, nuc, ij, jt, km, id, isp, l1, l2, k, k1, jz, i2, kmt, kt, size;
	int64_t *istack = NULL, *x_tmp = NULL, *y_tmp = NULL;
	double det[2][3], *x_circum = NULL, *y_circum = NULL, *r2_circum = NULL, *x = NULL, *y = NULL;
	double xmin, xmax, ymin, ymax, datax, dx, dy, dsq, dd;

	GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Delaunay triangulation calculated by Dave Watson's ACORD [Computers & Geosciences, 8, 97-101, 1982]\n");

	{
		/* Note 2019/01/07: We were notified via https://github.com/GenericMappingTools/gmt/issues/279
		 * that the Watson algorithm may give junk if there are duplicate entries in the input, and if so we issue
		 * a stern warning to users so they can clean up the file first before calling gmtsupport_delaunay_watson */

		struct GMT_PAIR *P = gmt_M_memory (GMT, NULL, n, struct GMT_PAIR);
		uint64_t n_duplicates = 0;
		if (P == NULL) return (0);
		for (i = 0; i < n; i++) {
			P[i].x = x_in[i];
			P[i].y = y_in[i];
			P[i].rec = i + 1;
		}
		qsort (P, n, sizeof (struct GMT_PAIR), gmtsupport_sort_pair);
		for (i = 1; i < n; i++) {
			if (doubleAlmostEqualZero (P[i].x, P[i-1].x) && doubleAlmostEqualZero (P[i].y, P[i-1].y)) {
				GMT_Report (GMT->parent, GMT_MSG_WARNING, "Records %" PRIu64 " and %" PRIu64 " are duplicates!\n", P[i-1].rec, P[i].rec);
				n_duplicates++;
			}
		}
		if (n_duplicates) {	/* Clearly not monotonically increasing or decreasing in x */
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "Bug Report Advice for Watson ACORD External Code:\n");
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "The Watson algorithm can fail if there are duplicate (x,y) records.\n");
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "We found %" PRIu64 " duplicate records in your data set.\n", n_duplicates);
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "Please remove duplicates and redo your analysis if the results are corrupted.\n");
		}
		gmt_M_free (GMT, P);
	}

	size = 10 * n + 1;
	n += 3;
	index = gmt_M_memory (GMT, NULL, 3 * size, int);
	istack = gmt_M_memory (GMT, NULL, size, int64_t);
	x_tmp = gmt_M_memory (GMT, NULL, size, int64_t);
	y_tmp = gmt_M_memory (GMT, NULL, size, int64_t);
	x_circum = gmt_M_memory (GMT, NULL, size, double);
	y_circum = gmt_M_memory (GMT, NULL, size, double);
	r2_circum = gmt_M_memory (GMT, NULL, size, double);
	x = gmt_M_memory (GMT, NULL, n, double);
	y = gmt_M_memory (GMT, NULL, n, double);
	if (index == NULL || istack == NULL || x_tmp == NULL || y_tmp == NULL || x_circum == NULL || y_circum == NULL \
		|| r2_circum == NULL || x == NULL || y == NULL)
		return (0);
	x[0] = x[1] = -1.0;	x[2] = 5.0;
	y[0] = y[2] = -1.0;	y[1] = 5.0;
	x_circum[0] = y_circum[0] = 2.0;	r2_circum[0] = 18.0;

	ix[0] = ix[1] = 0;	ix[2] = 1;
	iy[0] = 1;	iy[1] = iy[2] = 2;

	for (i = 0; i < 3; i++) index[i] = (int)i;
	for (i = 0; i < size; i++) istack[i] = i;

	xmin = ymin = 1.0e100;	xmax = ymax = -1.0e100;

	for (i = 3, j = 0; i < n; i++, j++) {	/* Copy data and get extremas */
		x[i] = x_in[j];
		y[i] = y_in[j];
		if (x[i] > xmax) xmax = x[i];
		if (x[i] < xmin) xmin = x[i];
		if (y[i] > ymax) ymax = y[i];
		if (y[i] < ymin) ymin = y[i];
	}

	/* Normalize data */

	datax = 1.0 / MAX (xmax - xmin, ymax - ymin);

	for (i = 3; i < n; i++) {
		x[i] = (x[i] - xmin) * datax;
		y[i] = (y[i] - ymin) * datax;
	}

	isp = id = 1;
	for (nuc = 3; nuc < n; nuc++) {

		km = 0;

		for (jt = 0; jt < isp; jt++) {	/* loop through established 3-tuples */

			ij = 3 * jt;

			/* Test if new data is within the jt circumcircle */

			dx = x[nuc] - x_circum[jt];
			if ((dsq = r2_circum[jt] - dx * dx) < 0.0) continue;
			dy = y[nuc] - y_circum[jt];
			if ((dsq -= dy * dy) < 0.0) continue;

			/* Delete this 3-tuple but save its edges */

			id--;
			istack[id] = jt;

			/* Add edges to x/y_tmp but delete if already listed */

			for (i = 0; i < 3; i++) {
				l1 = ix[i];
				l2 = iy[i];
				if (km > 0) {
					kmt = km;
					for (j = 0, done = false; !done && j < kmt; j++) {
						if (index[ij+l1] != x_tmp[j]) continue;
						if (index[ij+l2] != y_tmp[j]) continue;
						km--;
						if (j >= km) {
							done = true;
							continue;
						}
						for (k = j; k < km; k++) {
							k1 = k + 1;
							x_tmp[k] = x_tmp[k1];
							y_tmp[k] = y_tmp[k1];
							done = true;
						}
					}
				}
				else
					done = false;
				if (!done) {
					x_tmp[km] = index[ij+l1];
					y_tmp[km] = index[ij+l2];
					km++;
				}
			}
		}

		/* Form new 3-tuples */

		for (i = 0; i < km; i++) {
			kt = istack[id];
			ij = 3 * kt;
			id++;

			/* Calculate the circumcircle center and radius
			 * squared of points ktetr[i,*] and place in tetr[kt,*] */

			for (jz = 0; jz < 2; jz++) {
				i2 = (jz == 0) ? x_tmp[i] : y_tmp[i];
				det[jz][0] = x[i2] - x[nuc];
				det[jz][1] = y[i2] - y[nuc];
				det[jz][2] = 0.5 * (det[jz][0] * (x[i2] + x[nuc]) + det[jz][1] * (y[i2] + y[nuc]));
			}
			dd = 1.0 / (det[0][0] * det[1][1] - det[0][1] * det[1][0]);
			x_circum[kt] = (det[0][2] * det[1][1] - det[1][2] * det[0][1]) * dd;
			y_circum[kt] = (det[0][0] * det[1][2] - det[1][0] * det[0][2]) * dd;
			dx = x[nuc] - x_circum[kt];
			dy = y[nuc] - y_circum[kt];
			r2_circum[kt] = dx * dx + dy * dy;
			index[ij++] = (int)x_tmp[i];
			index[ij++] = (int)y_tmp[i];
			index[ij] = (int)nuc;
		}
		isp += 2;
	}

	for (jt = i = 0; jt < isp; jt++) {
		ij = 3 * jt;
		if (index[ij] < 3 || r2_circum[jt] > 1.0) continue;
		index[i++] = index[ij++] - 3;
		index[i++] = index[ij++] - 3;
		index[i++] = index[ij++] - 3;
	}

	index = gmt_M_memory (GMT, index, i, int);
	*link = index;

	gmt_M_free (GMT, istack);
	gmt_M_free (GMT, x_tmp);
	gmt_M_free (GMT, y_tmp);
	gmt_M_free (GMT, x_circum);
	gmt_M_free (GMT, y_circum);
	gmt_M_free (GMT, r2_circum);
	gmt_M_free (GMT, x);
	gmt_M_free (GMT, y);

	return (i/3);
}

/*! . */
GMT_LOCAL struct GMT_DATASET * gmtsupport_voronoi_watson (struct GMT_CTRL *GMT, double *x_in, double *y_in, uint64_t n, double *wesn, unsigned int mode) {
	gmt_M_unused(x_in); gmt_M_unused(y_in); gmt_M_unused(n); gmt_M_unused(wesn); gmt_M_unused(mode);
	GMT_Report (GMT->parent, GMT_MSG_ERROR, "No Voronoi unless you select Shewchuk's triangle option during GMT installation\n");
	return (0);
}

/*! . */
int64_t gmt_read_triangulation (struct GMT_CTRL *GMT, char option, char *file, bool binary, uint64_t n, int **link) {
	/* Read precalculated triangulation indices from file. Returns -1 if any trouble, else the number of triangles
	 * with the triangle vertex indices in the array link. Pass binary = true to read binary triplets (as per -bi). */
	int *ind = NULL;	/* Must be an int due to triangle */
	unsigned int k;
	uint64_t seg, row, col, ij, n_skipped, n_bad;
	int64_t np;
	unsigned int save_col_type[3];
	double d_n = (double)n - 0.5;	/* So we can use > in test for range below */
	struct GMT_DATASET *Tin = NULL;
	struct GMT_DATATABLE *T = NULL;
	struct GMTAPI_CTRL *API = GMT->parent;

	/* Must switch to Cartesian input and save whatever original input type we have since we are reading integer triplets */
	for (k = 0; k < 3; k++) {
		save_col_type[k] = gmt_M_type (GMT, GMT_IN, k);	/* Remember what we have */
		gmt_set_column_type (GMT, GMT_IN, k, GMT_IS_FLOAT);	/* And temporarily set to float */
	}
	if (binary)
		GMT_Report (API, GMT_MSG_INFORMATION, "Read triangulation indices from %s as binary triplets\n", file);
	else
		gmt_disable_bghio_opts (GMT);	/* Do not want any -b -g -h -i -o to affect the reading this file */
	if ((Tin = GMT_Read_Data (API, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_NONE, GMT_READ_NORMAL, NULL, file, NULL)) == NULL) {
		return (GMT_NOTSET);
	}
	if (!binary) gmt_reenable_bghio_opts (GMT);	/* Recover settings provided by user (if -b -g -h -i were used at all) */
	for (k = 0; k < 3; k++) gmt_set_column_type (GMT, GMT_IN, k, save_col_type[k]);	/* Undo the damage above */

	if (Tin->n_columns < 3) {	/* Trouble */
		GMT_Report (API, GMT_MSG_ERROR, "Option -%c: %s does not have at least 3 columns with indices\n", option, file);
		if (GMT_Destroy_Data (API, &Tin) != GMT_NOERROR) {	/* Even more trouble */
			return (GMT_NOTSET);
		}
		return (GMT_NOTSET);
	}
	T = Tin->table[0];	/* Since we only have one table here */
	if ((ind = gmt_M_memory (GMT, NULL, 3 * T->n_records, int)) == NULL) return (GMT_MEMORY_ERROR);	/* Allocate the integer index array */
	for (seg = ij = n_skipped = n_bad = 0; seg < T->n_segments; seg++) {
		for (row = 0; row < T->segment[seg]->n_rows; row++) {
			if (T->segment[seg]->data[0][row] > d_n || T->segment[seg]->data[1][row] > d_n || T->segment[seg]->data[2][row] > d_n)
				n_skipped++;	/* Outside valid point range */
			else if (T->segment[seg]->data[0][row] < -GMT_CONV8_LIMIT || T->segment[seg]->data[1][row] < -GMT_CONV8_LIMIT || T->segment[seg]->data[2][row] < -GMT_CONV8_LIMIT)
				n_bad++;
			else {	/* Convert to integer values */
				for (col = 0; col < 3; col++) ind[ij++] = irint (T->segment[seg]->data[col][row]);
			}
		}
	}
	np = ij / 3;	/* The actual number of vertices passing the test */
	if (GMT_Destroy_Data (API, &Tin) != GMT_NOERROR) {	/* That's too bad... */
		gmt_M_free (GMT, ind);
		return (GMT_NOTSET);
	}
	GMT_Report (API, GMT_MSG_INFORMATION, "Read %d triplets of triangulation indices from %s.\n", np, file);
	if (n_skipped) GMT_Report (API, GMT_MSG_WARNING, "Found %d indices triplets exceeding range of known vertices - skipped.\n", n_skipped);
	if (n_bad) GMT_Report (API, GMT_MSG_WARNING, "Found %d triplets with negative indices - skipped.\n", n_bad);

	*link = ind;	/* Pass the array back out */
	return (np);	/* Number of triplets returned */
}

/*! . */
GMT_LOCAL int gmtsupport_ensure_new_mapinset_syntax (struct GMT_CTRL *GMT, char option, char *in_text, char *text, char *panel_txt) {
	/* Recasts any old syntax using new syntax and gives a warning.
	   Assumes text and panel_text are blank and have adequate space */
	if (gmt_found_modifier (GMT, in_text, "cgp")) {	/* Tell-tale sign of old syntax */
		char p[GMT_BUFSIZ] = {""}, txt_a[GMT_LEN256] = {""}, txt_b[GMT_LEN256] = {""};
		unsigned int pos = 0, start = 0, i;
		int n;
		bool center = false;
		for (i = 0; start == 0 && in_text[i]; i++) {	/* Find the first valid modifier */
			if (in_text[i] == '+') {
				if (strchr ("cgp", in_text[i+1])) start = i;	/* Found start of the modifiers */
			}
		}
		while ((gmt_strtok (&in_text[start], "+", &pos, p))) {
			switch (p[0]) {
				case 'c':	/* Got inset center */
					center = true;
					if ((n = sscanf (&p[1], "%[^/]/%s", txt_a, txt_b)) != 2) {
						GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Must specify +c<lon>/<lat> for center [Also note this is obsolete syntax]\n", option);
						return (1);
					}
					break;
				case 'g':	/* Fill specification [Obsolete, now done via panel attributes ] */
					GMT_Report (GMT->parent, GMT_MSG_WARNING, "Option -%c:  Insert fill attributes now given with panel setting (-F)\n", option);
					strcat (panel_txt, "+g");
					strcat (panel_txt, &p[1]);
					break;
				case 'p':	/* Pen specification [Obsolete, now done via panel attributes ] */
					GMT_Report (GMT->parent, GMT_MSG_WARNING, "Option -%c:  Insert pen attributes now given with panel setting (-F)\n", option);
					strcat (panel_txt, "+p");
					strcat (panel_txt, &p[1]);
					break;
				default:
					break;
			}
		}
		in_text[start] = '\0';	/* Chop off modifiers for now */
		if (center) {	/* Must extract dimensions of map inset */
			char unit[2] = {0, 0};
			sprintf (text, "g%s/%s/", txt_a, txt_b);	/* -Dg<lon>/<lat> is the new reference point */
			n = sscanf (in_text, "%[^/]/%s", txt_a, txt_b);	/* Read dimensions */
			if (strchr (GMT_LEN_UNITS2, txt_a[0])) {	/* Dimensions in allowable distance units, with unit in front of distance */
				unit[0] = txt_a[0];		/* Extract the unit */
				strcat (text, "+w");		/* Append width modifier */
				strcat (text, &txt_a[1]);	/* Append width to new option */
				strcat (text, unit);		/* Append unit to new option */
				if (n == 2) {			/* Got separate height */
					strcat (text, "/");		/* Separate width from height */
					strcat (text, txt_b);		/* Append height or duplicate */
					strcat (text, unit);		/* Append unit */
				}
			}
			else
				strcat (text, in_text);		/* Append h/w as is */
			strcat (text, "+jCM");	/* Append justification */
		}
		else	/* Just keep as is, minus the modifiers */
			strcpy (text, in_text);
		in_text[start] = '+';	/* Restore modifiers */
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Converted %s to %s and %s\n", in_text, text, panel_txt);
	}
	else	/* New syntax or no +g,+p given so old syntax is same as new */
		strcpy (text, in_text);
	return (0);
}

/*! . */
GMT_LOCAL int gmtsupport_getscale_old (struct GMT_CTRL *GMT, char option, char *text, struct GMT_MAP_SCALE *ms) {
	/* This function parses the -L map scale syntax:
	 * 	-L[f][x]<lon0>/<lat0>[/<slon>]/<slat>/<length>[e|f|M|n|k|u][+u]
	 * The function is also backwards compatible with the previous map scale syntax:
	 * 	-L [f][x]<lon0>/<lat0>[/<slon>]/<slat>/<length>[e|f|M|n|k|u][+l<label>][+j<just>][+p<pen>][+g<fill>][+u]
	 * The old syntax is recognized by the optional +p and +g modifiers.  If either of these are present then we know
	 * we are looking at the old syntax and we parse those options but give warning of obsolesnce; otherwise
	 * we do the parsing of the newer format where the background panel is handled by another options (e.g. -F in psbasemap). */

	int j = 0, i, n_slash, error = 0, k = 0, options;
	bool gave_xy = false;
	char txt_cpy[GMT_BUFSIZ] = {""}, txt_a[GMT_LEN256] = {""}, txt_b[GMT_LEN256] = {""};
	char txt_sx[GMT_LEN256] = {""}, txt_sy[GMT_LEN256] = {""}, txt_len[GMT_LEN256] = {""}, string[GMT_LEN256] = {""};

	if (!text) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: No argument given\n", option);
		return GMT_PARSE_ERROR;
	}

	gmt_M_memset (ms, 1, struct GMT_MAP_SCALE);
	ms->measure = 'k';	/* Default distance unit is km */
	ms->alignment = 't';
	ms->justify = PSL_TC;

	/* First deal with possible prefixes f and x (i.e., f, x, xf, fx) */
	if (text[j] == 'f') ms->fancy = true, j++;
	if (text[j] == 'x') gave_xy = true, j++;
	if (text[j] == 'f') ms->fancy = true, j++;	/* in case we got xf instead of fx */

	/* Determine if we have the optional longitude component specified by counting slashes.
	 * We stop counting if we reach a + sign since the fill or label might have a slash in them */

	for (n_slash = 0, i = j; text[i] && text[i] != '+'; i++) if (text[i] == '/') n_slash++;
	options = (text[i] == '+') ? i : -1;	/* -1, or starting point of first option */
	if (options > 0) {	/* Have optional args, make a copy and truncate text */
		strncpy (txt_cpy, &text[options], GMT_BUFSIZ-1);
		text[options] = '\0';
		for (i = 0; txt_cpy[i]; i++) {	/* Unless +fgjlpu, change other + to ASCII 1 to bypass strtok trouble later [f is now deprecated] */
			if (txt_cpy[i] == '+' && !strchr ("fgjlpu", (int)txt_cpy[i+1])) txt_cpy[i] = 1;
		}
	}

	if (n_slash == 4) {		/* -L[f][x]<x0>/<y0>/<lon>/<lat>/<length>[m|n|k][+l<label>][+j<just>][+p<pen>][+g<fill>][+u] */
		k = sscanf (&text[j], "%[^/]/%[^/]/%[^/]/%[^/]/%s", txt_a, txt_b, txt_sx, txt_sy, txt_len);
	}
	else if (n_slash == 3) {	/* -L[f][x]<x0>/<y0>/<lat>/<length>[m|n|k][+l<label>][+j<just>][+p<pen>][+g<fill>][+u] */
		k = sscanf (&text[j], "%[^/]/%[^/]/%[^/]/%s", txt_a, txt_b, txt_sy, txt_len);
	}
	else {	/* Wrong number of slashes */
		error++;
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Not enough arguments given, including no width\n", option);
		return (error);
	}
	i = (int)strlen (txt_len) - 1;
	if (isalpha ((int)txt_len[i])) {	/* Letter at end of distance value */
		ms->measure = txt_len[i];
		if (gmt_M_compat_check (GMT, 4) && ms->measure == 'm') {
			GMT_Report (GMT->parent, GMT_MSG_COMPAT, "Distance unit m is deprecated; use M for statute miles\n");
			ms->measure = 'M';
		}
		if (strchr (GMT_LEN_UNITS2, ms->measure))	/* Gave a valid distance unit */
			txt_len[i] = '\0';
		else {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Valid distance units are %s\n", option, GMT_LEN_UNITS2_DISPLAY);
			error++;
		}
	}
	ms->length = atof (txt_len);

	if (gave_xy)	/* Set up anchor in plot units */
		snprintf (string, GMT_LEN256, "x%s/%s", txt_a, txt_b);
	else	/* Set up ancher in geographical coordinates */
		snprintf (string, GMT_LEN256, "g%s/%s", txt_a, txt_b);
	if ((ms->refpoint = gmt_get_refpoint (GMT, string, option)) == NULL) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Scale reference point was not accepted\n", option);
		gmt_refpoint_syntax (GMT, "L", NULL, GMT_ANCHOR_MAPSCALE, 3);
		return (1);	/* Failed basic parsing */
	}

	error += gmt_verify_expectations (GMT, GMT_IS_LAT, gmt_scanf (GMT, txt_sy, GMT_IS_LAT, &ms->origin[GMT_Y]), txt_sy);
	if (fabs (ms->origin[GMT_Y]) > 90.0) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Latitude where scale should apply is out of range\n", option);
		error++;
	}
	if (k == 5)	{/* Must also decode longitude of scale */
		error += gmt_verify_expectations (GMT, GMT_IS_LON, gmt_scanf (GMT, txt_sx, GMT_IS_LON, &ms->origin[GMT_X]), txt_sx);
		if (fabs (ms->origin[GMT_X]) > 360.0) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Scale longitude is out of range\n", option);
			error++;
		}
	}
	else		/* Default to central meridian [this will be the result if we assign NaN here] */
		ms->origin[GMT_X] = GMT->session.d_NaN;
	if (ms->length <= 0.0) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Length must be positive\n", option);
		error++;
	}

	ms->old_style = gmt_found_modifier (GMT, txt_cpy, "fgp");

	if (options > 0) {	/* Gave +?<args> which now must be processed */
		char p[GMT_BUFSIZ], oldshit[GMT_LEN128] = {""};
		unsigned int pos = 0, bad = 0;
		while ((gmt_strtok (txt_cpy, "+", &pos, p))) {
			switch (p[0]) {
				case 'f':	/* Fill specification */
					if (ms->old_style && gmt_M_compat_check (GMT, 4)) {	/*  Warn about old GMT 4 syntax */
						GMT_Report (GMT->parent, GMT_MSG_COMPAT, "+f<fill> in map scale is deprecated, use -F panel settings instead\n");
						strncat (oldshit, "+g", GMT_LEN128-1);
						strncat (oldshit, &p[1], GMT_LEN128-3);
					}
					else
						bad++;
					break;
				case 'g':	/* Fill specification */
					if (ms->old_style && gmt_M_compat_check (GMT, 5)) {	/* Warn about old GMT 5 syntax */
						GMT_Report (GMT->parent, GMT_MSG_COMPAT, "+g<fill> in map scale is deprecated, use -F panel settings instead\n");
						strncat (oldshit, "+", GMT_LEN128-1);
						strncat (oldshit, p, GMT_LEN128-2);
					}
					else
						bad++;
					break;

				case 'j':	/* Label justification */
					ms->alignment = p[1];
					if (!(ms->alignment == 'l' || ms->alignment == 'r' || ms->alignment == 't' || ms->alignment == 'b')) bad++;
					break;

				case 'p':	/* Pen specification */
					if (ms->old_style && gmt_M_compat_check (GMT, 5)) {	/* Warn about old syntax */
						GMT_Report (GMT->parent, GMT_MSG_COMPAT, "+p<pen> in map scale is deprecated, use -F panel settings instead\n");
						strncat (oldshit, "+", GMT_LEN128-1);
						strncat (oldshit, p, GMT_LEN128-2);
					}
					else
						bad++;
					break;

				case 'l':	/* Label specification */
					if (p[1]) strncpy (ms->label, &p[1], GMT_LEN64-1);
					ms->do_label = true;
					for (i = 0; ms->label[i]; i++) if (ms->label[i] == 1) ms->label[i] = '+';	/* Change back ASCII 1 to + */
					break;

				case 'u':	/* Add units to annotations */
					ms->unit = true;
					break;

				default:
					bad++;
					break;
			}
		}
		error += bad;
		text[options] = '+';	/* Restore original string */
		if (ms->old_style && gmt_getpanel (GMT, 'F', oldshit, &(ms->panel))) {
			gmt_mappanel_syntax (GMT, 'F', "Specify a rectangular panel behind the scale", 3);
			error++;
		}
	}
	if (error)
		gmt_mapscale_syntax (GMT, 'L', "Draw a map scale centered on <lon0>/<lat0>.");

	ms->plot = true;
	return (error);
}

/*! . */
GMT_LOCAL int gmtsupport_getrose_old (struct GMT_CTRL *GMT, char option, char *text, struct GMT_MAP_ROSE *ms) {
	int plus;
	unsigned int j = 0, i, error = 0, colon, slash, k, pos, order[4] = {3,1,0,2};
	bool gave_xy = false;
	char txt_a[GMT_LEN256] = {""}, txt_b[GMT_LEN256] = {""}, txt_c[GMT_LEN256] = {""}, txt_d[GMT_LEN256] = {""};
	char tmpstring[GMT_LEN256] = {""}, string[GMT_LEN256] = {""}, p[GMT_LEN256] = {""};

	/* SYNTAX is -?[f|m][x]<lon0>/<lat0>/<size>[/<info>][:label:][+<aint>/<fint>/<gint>[/<aint>/<fint>/<gint>]], where <info> is
	 * 1)  -?f: <info> is <kind> = 1,2,3 which is the level of directions [1].
	 * 2)  -?m: <info> is <dec>/<dlabel>, where <Dec> is magnetic declination and dlabel its label [no mag].
	 * If -?m, optionally set annotation interval with +
	 */

	if (!text[0]) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: No argument given\n", option);
		return GMT_PARSE_ERROR;
	}

	ms->type = GMT_ROSE_DIR_PLAIN;
	ms->size = 0.0;
	ms->a_int[0] = 30.0;	ms->f_int[0] = 5.0;	ms->g_int[0] = 1.0;
	ms->a_int[1] = 30.0;	ms->f_int[1] = 5.0;	ms->g_int[1] = 1.0;
	strcpy (ms->label[0], GMT->current.language.cardinal_name[2][2]);
	strcpy (ms->label[1], GMT->current.language.cardinal_name[2][1]);
	strcpy (ms->label[2], GMT->current.language.cardinal_name[2][3]);
	strcpy (ms->label[3], GMT->current.language.cardinal_name[2][0]);

	/* First deal with possible prefixes f and x (i.e., f|m, x, xf|m, f|mx) */
	if (text[j] == 'f') ms->type = GMT_ROSE_DIR_FANCY, j++;
	if (text[j] == 'm') ms->type = GMT_ROSE_MAG, j++;
	if (text[j] == 'x') gave_xy = true, j++;
	if (text[j] == 'f') ms->type = GMT_ROSE_DIR_FANCY, j++;		/* in case we got xf instead of fx */
	if (text[j] == 'm') ms->type = GMT_ROSE_MAG, j++;		/* in case we got xm instead of mx */

	/* Determine if we have the optional label components specified */

	for (i = j, slash = 0; text[i] && slash < 2; i++) if (text[i] == '/') slash++;	/* Move i until the 2nd slash is reached */
	for (k = (unsigned int)strlen(text) - 1, colon = 0; text[k] && k > i && colon < 2; k--)
		if (text[k] == ':') colon++;	/* Move k to starting colon of :label: */
	if (colon == 2 && k > i)
		colon = k + 2;	/* Beginning of label */
	else
		colon = 0;	/* No labels given */

	for (plus = -1, i = slash; text[i] && plus < 0; i++) if (text[i] == '+') plus = i+1;	/* Find location of + */
	if (plus > 0) {		/* Get annotation interval(s) */
		k = sscanf (&text[plus], "%lf/%lf/%lf/%lf/%lf/%lf", &ms->a_int[1], &ms->f_int[1], &ms->g_int[1], &ms->a_int[0], &ms->f_int[0], &ms->g_int[0]);
		if (k < 1) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Give annotation interval(s)\n", option);
			error++;
		}
		if (k == 3) ms->a_int[0] = ms->a_int[1], ms->f_int[0] = ms->f_int[1], ms->g_int[0] = ms->g_int[1];
		text[plus-1] = '\0';	/* Break string so sscanf won't get confused later */
	}
	if (colon > 0) {	/* Get labels in string :w,e,s,n: */
		for (k = colon; text[k] && text[k] != ':'; k++);	/* Look for terminating colon */
		if (text[k] != ':') { /* Ran out, missing terminating colon */
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Labels must be given in format :w,e,s,n:\n", option);
			error++;
			return (error);
		}
		strncpy (tmpstring, &text[colon], (size_t)(k-colon));
		tmpstring[k-colon] = '\0';
		k = pos = 0;
		while (k < 4 && (gmt_strtok (tmpstring, ",", &pos, p))) {	/* Get the four labels */
			if (strcmp (p, "-")) strncpy (ms->label[order[k]], p, GMT_LEN64-1);
			k++;
		}
		ms->do_label = true;
		if (k == 0) {	/* No labels wanted */
			ms->label[0][0] = ms->label[1][0] = ms->label[2][0] = ms->label[3][0] = '\0';
			ms->do_label = false;
		}
		else if (k != 4) {	/* Ran out of labels */
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Labels must be given in format :w,e,s,n:\n", option);
			error++;
		}
		text[colon-1] = '\0';	/* Break string so sscanf won't get confused later */
	}

	/* -?[f][x]<x0>/<y0>/<size>[/<kind>][:label:] OR -L[m][x]<x0>/<y0>/<size>[/<dec>/<declabel>][:label:][+gint[/mint]] */
	if (ms->type == GMT_ROSE_MAG) {	/* Magnetic rose */
		k = sscanf (&text[j], "%[^/]/%[^/]/%[^/]/%[^/]/%[^/]", txt_a, txt_b, txt_c, txt_d, ms->dlabel);
		if (! (k == 3 || k == 5)) {	/* Wrong number of parameters */
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Correct syntax\n", option);
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "\t-%c[f|m][x]<x0>/<y0>/<size>[/<info>][:wesnlabels:][+<gint>[/<mint>]]\n", option);
			error++;
		}
		if (k == 3) {	/* No magnetic north directions */
			ms->kind = 1;
			ms->declination = 0.0;
			ms->dlabel[0] = '\0';
		}
		else {
			error += gmt_verify_expectations (GMT, GMT_IS_LON, gmt_scanf (GMT, txt_d, GMT_IS_LON, &ms->declination), txt_d);
			ms->kind = 2;
		}
	}
	else {
		k = sscanf (&text[j], "%[^/]/%[^/]/%[^/]/%d", txt_a, txt_b, txt_c, &ms->kind);
		if (k == 3) ms->kind = 1;
		if (k < 3 || k > 4) {	/* Wrong number of parameters */
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Correct syntax\n", option);
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "\t-%c[f|m][x]<x0>/<y0>/<size>[/<info>][:wesnlabels:][+<gint>[/<mint>]]\n", option);
			error++;
		}
	}
	if (colon > 0) text[colon-1] = ':';	/* Put it back */
	if (plus > 0) text[plus-1] = '+';	/* Put it back */
	if (gave_xy)	/* Set up ancher in plot units */
		snprintf (string, GMT_LEN256, "x%s/%s", txt_a, txt_b);
	else	/* Set up ancher in geographical coordinates */
		snprintf (string, GMT_LEN256, "g%s/%s", txt_a, txt_b);
	if ((ms->refpoint = gmt_get_refpoint (GMT, string, option)) == NULL) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Map rose reference point was not accepted\n", option);
		gmt_refpoint_syntax (GMT, "Td|m", NULL, GMT_ANCHOR_MAPROSE, 3);
		return (1);	/* Failed basic parsing */
	}
	ms->justify = PSL_MC;	/* Center it is */
	ms->size = gmt_M_to_inch (GMT, txt_c);
	if (ms->size <= 0.0) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Size must be positive\n", option);
		error++;
	}
	if (ms->kind < 1 || ms->kind > 3) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  <kind> must be 1, 2, or 3\n", option);
		error++;
	}

	ms->plot = true;
	return (error);
}

/* Here lies GMT Crossover core functions that previously was in X2SYS only */
/* gmtsupport_ysort must be an int since it is passed to qsort_r! */
/*! . */

#ifdef QSORT_R_THUNK_FIRST
/* thunk arg is first argument to compare function */
GMT_LOCAL int gmtsupport_ysort (void *arg, const void *p1, const void *p2) {
#else
/* thunk arg is last argument to compare function */
GMT_LOCAL int gmtsupport_ysort (const void *p1, const void *p2, void *arg) {
#endif
	const struct GMT_XSEGMENT *a = p1, *b = p2;
	double *x2sys_y = arg;

	if (x2sys_y[a->start] < x2sys_y[b->start]) return -1;
	if (x2sys_y[a->start] > x2sys_y[b->start]) return  1;

	/* Here they have the same low y-value, now sort on other y value */
	if (x2sys_y[a->stop] < x2sys_y[b->stop]) return -1;
	if (x2sys_y[a->stop] > x2sys_y[b->stop]) return  1;

	/* Identical */
	return (0);
}

/*! . */
GMT_LOCAL void gmtsupport_x_alloc (struct GMT_CTRL *GMT, struct GMT_XOVER *X, size_t nx_alloc, bool first) {
	if (first) {	/* Initial allocation */
		X->x = gmt_M_memory (GMT, NULL, nx_alloc, double);
		X->y = gmt_M_memory (GMT, NULL, nx_alloc, double);
		X->xnode[0] = gmt_M_memory (GMT, NULL, nx_alloc, double);
		X->xnode[1] = gmt_M_memory (GMT, NULL, nx_alloc, double);
	}
	else {	/* Increment */
		X->x = gmt_M_memory (GMT, X->x, nx_alloc, double);
		X->y = gmt_M_memory (GMT, X->y, nx_alloc, double);
		X->xnode[0] = gmt_M_memory (GMT, X->xnode[0], nx_alloc, double);
		X->xnode[1] = gmt_M_memory (GMT, X->xnode[1], nx_alloc, double);
	}
}

GMT_LOCAL bool gmtsupport_x_overlap (double *xa, double *xb, uint64_t *xa_start, uint64_t *xa_stop, uint64_t *xb_start, uint64_t *xb_stop, bool geo, double *dx) {
	/* Return true if the two x-ranges overlap */
	if (geo) {	/* More complicated, and may change both the start/stop indices and the array longitudes */
		int k;
		double del_x = xa[*xa_stop] - xa[*xa_start];	/* Check if line A has a longitude jump */
		if (del_x > 180.0) {xa[*xa_start] += 360.0; gmt_M_uint64_swap(*xa_start, *xa_stop);}	/* Deal with 360 and swap start and stop indices */
		del_x = xb[*xb_stop] - xb[*xb_start];		/* Check if line B has a longitude jump */
		if (del_x > 180.0) {xb[*xb_start] += 360.0; gmt_M_uint64_swap(*xb_start, *xb_stop);}	/* Deal with 360 and swap start and stop indices */
		/* Here we have fixed any 360 jumps in A and B and reassign what is start and stop. We must now look for overlaps
		 * between the segments by considering that A may be off by -360, 0, or +360 degrees in longitude relative to B. */

		for (k = -1; k <= 1; k++) {	/* Try offsets of k * 360. If we find overlap then *dx returns the shift we must add to the xa coordinates later */
			*dx = k * 360.0;
			if (!(((xa[*xa_stop] + (*dx)) < xb[*xb_start]) || ((xa[*xa_start] + (*dx)) > xb[*xb_stop]))) return true;
		}
		return false;	/* No overlap */
	}
	else {	/* Cartesian is simple since xa_start <= xa_stop and xb_start <= xb_stop */
		return (!((xa[*xa_stop] < xb[*xb_start]) || (xa[*xa_start] > xb[*xb_stop])));
	}
}

GMT_LOCAL int gmtsupport_polar_adjust (struct GMT_CTRL *GMT, int side, double angle, double x, double y) {
	int justify, left, right, top, bottom, low;
	double x0, y0, f_angle = 180.0;

	/* gmt_geo_to_xy (GMT->current.proj.central_meridian, GMT->current.proj.pole, &x0, &y0); */

	x0 = GMT->current.proj.c_x0;
	y0 = GMT->current.proj.c_y0;
	if (GMT->current.proj.north_pole) {
		low = 0;
		left = 7;
		right = 5;
	}
	else {
		low = 2;
		left = 5;
		right = 7;
	}
	if ((y - y0 - GMT_CONV4_LIMIT) > 0.0) { /* i.e., y > y0 */
		top = 2;
		bottom = 10;
	}
	else {
		top = 10;
		bottom = 2;
	}
	if (GMT->current.proj.projection_GMT == GMT_POLAR) {	/* Special concerns with r/theta systems */
		if (GMT->current.proj.got_azimuths) gmt_M_int_swap (left, right);	/* Because with azimuths we get confused... */
		if (GMT->current.proj.flip) {
			gmt_M_int_swap (top, bottom);
			gmt_M_int_swap (left, right);
			low = 2 - low;
			//f_angle = 0.0;
		}
	}
	if (side%2) {	/* W and E border */
		if ((y - y0 + GMT_CONV4_LIMIT) > 0.0)
			justify = (side == 1) ? left : right;
		else
			justify = (side == 1) ? right : left;
	}
	else {	/* S and N border */
		if (GMT->current.map.frame.horizontal) {
			if (side == low)
				justify = (doubleAlmostEqualZero (angle, f_angle)) ? bottom : top;
			else
				justify = (gmt_M_is_zero (angle)) ? top : bottom;
			if (GMT->current.proj.flip && !GMT->current.proj.got_elevations) justify = (justify + 8) % 16;
			if (GMT->current.proj.got_elevations && (doubleAlmostEqualZero (angle, f_angle) || gmt_M_is_zero (angle)))
				justify = (justify + 8) % 16;
		}
		else {
			if (x >= x0)
				justify = (side == 2) ? left : right;
			else
				justify = (side == 2) ? right : left;
		}
	}
	return (justify);
}

/*! . */
GMT_LOCAL bool gmtsupport_get_label_parameters (struct GMT_CTRL *GMT, int side, double line_angle, int type, double *text_angle, unsigned int *justify) {
	bool ok;

	*text_angle = line_angle;
#ifdef OPT_WORKS_BADLY
	if (*text_angle < -90.0) *text_angle += 360.0;
	if (GMT->current.map.frame.horizontal && !(side%2)) *text_angle += 90.0;
	if (*text_angle > 270.0 ) *text_angle -= 360.0;
	else if (*text_angle > 90.0) *text_angle -= 180.0;
#else
	if ( (*text_angle + 90.0) < GMT_CONV8_LIMIT) *text_angle += 360.0;
	if (GMT->current.map.frame.horizontal && !(side%2)) *text_angle += 90.0;
	if ( (*text_angle - 270.0) > GMT_CONV8_LIMIT ) *text_angle -= 360.0;
	else if ( (*text_angle - 90.0) > GMT_CONV8_LIMIT) *text_angle -= 180.0;
#endif

	if (type == 0 && GMT->current.setting.map_annot_oblique & GMT_OBL_ANNOT_LON_HORIZONTAL) *text_angle = 0.0;	/* Force horizontal lon annotation */
	if (type == 1 && GMT->current.setting.map_annot_oblique & GMT_OBL_ANNOT_LAT_HORIZONTAL) *text_angle = 0.0;	/* Force horizontal lat annotation */

	switch (side) {
		case 0:		/* S */
			if (GMT->current.map.frame.horizontal)
				*justify = (GMT->current.proj.got_elevations) ? 2 : 10;
			else
				*justify = ((*text_angle) < 0.0) ? 5 : 7;
			break;
		case 1:		/* E */
			if (type == 1 && GMT->current.setting.map_annot_oblique & GMT_OBL_ANNOT_LAT_PARALLEL) {
				*text_angle = 90.0;	/* Force parallel lat annotation */
				*justify = 10;
			}
			else
				*justify = 5;
			break;
		case 2:		/* N */
			if (GMT->current.map.frame.horizontal)
				*justify = (GMT->current.proj.got_elevations) ? 10 : 2;
			else
				*justify = ((*text_angle) < 0.0) ? 7 : 5;
			break;
		default:	/* W */
			if (type == 1 && GMT->current.setting.map_annot_oblique & GMT_OBL_ANNOT_LAT_PARALLEL) {
				*text_angle = 90.0;	/* Force parallel lat annotation */
				*justify = 2;
			}
			else
				*justify = 7;
			break;
	}

	if (GMT->current.map.frame.horizontal) return (true);

	switch (side) {
		case 0:		/* S */
		case 2:		/* N */
			ok = (fabs ((*text_angle)) >= GMT->current.setting.map_annot_min_angle);
			break;
		default:	/* E or W */
			ok = (fabs ((*text_angle)) <= (90.0 - GMT->current.setting.map_annot_min_angle));
			break;
	}
	return (ok);
}

/*! . */
GMT_LOCAL int gmtsupport_gnomonic_adjust (struct GMT_CTRL *GMT, double angle, double x, double y) {
	/* Called when GNOMONIC and global region.  angle has been fixed to the +- 90 range */
	/* This is a kludge until we rewrite the entire justification stuff */
	bool inside;
	double xp, yp, r;

	/* Create a point a small step away from (x,y) along the angle baseline
	 * If it is inside the circle the we want right-justify, else left-justify. */
	sincosdegree (angle, &yp, &xp);
	xp = xp * GMT->current.setting.map_line_step + x;
	yp = yp * GMT->current.setting.map_line_step + y;
	r = hypot (xp - GMT->current.proj.r, yp - GMT->current.proj.r);
	inside = (r < GMT->current.proj.r);
	return ((inside) ? 7 : 5);
}

/*! . */
GMT_LOCAL void gmtsupport_free_one_custom_symbol (struct GMT_CTRL *GMT, struct GMT_CUSTOM_SYMBOL *sym) {
	/* Free one allocated custom symbol */
	struct GMT_CUSTOM_SYMBOL_ITEM *s = NULL, *current = NULL;

	if (sym == NULL) return;
	s = sym->first;
	while (s) {
		current = s;
		s = s->next;
		gmt_M_free (GMT, current->fill);
		gmt_M_free (GMT, current->pen);
		gmt_M_free (GMT, current->string);
		if (current->eps) {
			gmt_M_free (GMT, current->eps->macro);
			gmt_M_str_free (current->eps->name);
			gmt_M_free (GMT, current->eps);
		}
		gmt_M_free (GMT, current);
	}
	gmt_M_free (GMT, sym->type);
	gmt_M_free (GMT, sym);
}

/*! . */
GMT_LOCAL int gmtsupport_decode_arg (char *txt, int column, struct GMT_CUSTOM_SYMBOL_ITEM *s) {
	/* Look for $<var> arguments which means supply input at runtime from data record.
	 * Otherwise it is a value to be used as is.  One exception are values that end with
	 * 'a' which means azimuth.  We return revised actions for the two rotation actions.
	 * Other symbols will ignore the returned action. */
	int new_action = s->action;	/* This output is only used for the ROTATE symbol */
	size_t k = strlen (txt) - 1;	/* Index of last character */
	assert (column < CUSTOM_SYMBOL_MAXVAR);	/* Otherwise we want to know */
	if (txt[0] == '$') {	/* Got a variable as angle */
		s->var[column] = atoi (&txt[1]);
		s->is_var[column] = true;
		s->var_sign[column] = 1.0;
		new_action = GMT_SYMBOL_VARROTATE;	/* Mark as a different rotate action */
	}
	else if (txt[0] == '-' && txt[1] == '$') {	/* Got a variable as negative angle */
		s->var[column] = atoi (&txt[2]);
		s->is_var[column] = true;
		s->var_sign[column] = -1.0;
		new_action = GMT_SYMBOL_VARROTATE;	/* Mark as a different rotate action */
	}
	else if (txt[k] == 'a') {	/* Got a fixed azimuth and must flag via a different action */
		txt[k] = '\0';	/* Temporarily remove the trailing 'a' */
		s->p[column] = atof (txt);	/* Get azimuth */
		new_action = GMT_SYMBOL_AZIMROTATE;	/* Mark as a different rotate action */
		txt[k] = 'a';	/* Restore the trailing 'a' */
		s->angular = GMT_IS_AZIMUTH;
	}
	else	/* Got a fixed Cartesian plot angle */
		s->p[column] = atof (txt);
	return (new_action);
}

int gmt_locate_custom_symbol (struct GMT_CTRL *GMT, const char *in_name, char *name, char *path, unsigned int *pos) {
	/* Return codes are 0 = not found, 1 = def, 2 = eps */
	bool try[3] = {false, true, true};	/* Try to look for either .def or .eps (index [0] is not used) */
	bool try_remote = false;
	size_t k, length;
	char file[PATH_MAX] = {""}, *ext[3] = {"", ".def", ".eps"};
	/* Because we do not necessarily know if the custom symbol requested is an EPS or DEF file, we must check
	 * for both unless an extension is given and then we know.  To minimize checking on the remote server, we
	 * decide to look for one or both files only locally first, and if that fails then we start looking in the\
	 * remote cache. */

	/* Determine if in_name ends in ".def", ".eps" or neither */
	length = strlen (in_name);
	if (length > 4 && !strcmp (&in_name[length-4], ext[GMT_CUSTOM_DEF])) {	/* User gave trailing .def extension */
		strncpy (name, in_name, length-4);	/* Eliminate extension in name */
		try[GMT_CUSTOM_EPS] = false;	/* No need looking for eps files */
	}
	else if (length > 4 && !strcmp (&in_name[length-4], ext[GMT_CUSTOM_EPS])) {	/* User gave trailing .eps extension */
		strncpy (name, in_name, length-4);	/* Eliminate extension in name */
		try[GMT_CUSTOM_DEF] = false;	/* No need looking for def files */
	}
	else	/* Use as is, extension remains unknown */
		strcpy (name, in_name);

	if (gmt_file_is_cache (GMT->parent, name)) {
		try_remote = true;	/* Is a cache file */
		*pos = 1;
	}
	for (k = GMT_CUSTOM_DEF; k <= GMT_CUSTOM_EPS; k++) {
		if (!try[k]) continue;	/* No need to check for this type of custom symbol*/
		snprintf (file, PATH_MAX, "%s%s", name, ext[k]);	/* Full name of potential def|eps file */
		if (gmt_getsharepath (GMT, "custom", &name[*pos], ext[k], path, R_OK) || gmtlib_getuserpath (GMT, &file[*pos], path)) {
			GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Found custom symbol %s in %s\n", name, path);
			return (int)k;	/* Found local *.def or *.eps file */
		}
	}
	if (!try_remote) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Could not find either custom symbol or EPS macro %s\n", name);
		return 0;	/* Not found, and since not a cache file we don't need to look further */
	}

	/* Here we failed to find the cache file locally.  Now try remote cache */
	for (k = GMT_CUSTOM_DEF; k <= GMT_CUSTOM_EPS; k++) {
		if (!try[k]) continue;	/* No need to check this on */
		snprintf (file, PATH_MAX, "%s%s", name, ext[k]);	/* Full name of potential def|eps file */
		/* Look for remote files.  Passing 4 to avoid hearing about missing remote files
		 * which can happen when we look for *.def but the file is actually a *.eps [Example 46] */
		*pos = gmt_download_file_if_not_found (GMT, file, 4);
		/* Here, pos is position of first character in the name after any leading URLs or @ [0] */
		if (gmt_getsharepath (GMT, "custom", &name[*pos], ext[k], path, R_OK) || gmtlib_getuserpath (GMT, &file[*pos], path)) {
			GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Found custom symbol %s in %s\n", name, path);
			return (int)k;	/* Found local *.def or *.eps file */
		}
	}
	GMT_Report (GMT->parent, GMT_MSG_ERROR, "Could not find either custom symbol or EPS macro %s\n", name);
	return (0);
}

GMT_LOCAL struct GMT_CUSTOM_SYMBOL_EPS * gmtsupport_load_eps_symbol (struct GMT_CTRL *GMT, char *name, char *path) {
	unsigned int bb;
	bool got_BB[2] = {false, false};
	static char *BB_string[2] = {"%%HiResBoundingBox:", "%%BoundingBox:"};
	char buffer[GMT_BUFSIZ] = {""};
	struct stat buf;
	struct GMT_CUSTOM_SYMBOL_EPS *E = NULL;
	FILE *fp = NULL;

	if (stat (path, &buf)) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Could not determine size of EPS symbol %s\n", path);
		return NULL;
	}
	if ((fp = fopen (path, "r")) == NULL) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Could not find custom symbol %s\n", path);
		return NULL;
	}
	if ((E = gmt_M_memory (GMT, NULL, 1U, struct GMT_CUSTOM_SYMBOL_EPS)) == NULL) return NULL;
	if ((E->macro = gmt_M_memory (GMT, NULL, (size_t)buf.st_size, char)) == NULL) return NULL;
	E->name = strdup (name);
	while (fgets (buffer, GMT_BUFSIZ, fp)) {
		for (bb = 0; bb < 2; bb++) {	/* Check for both flavors of BoundingBox unless found */
			if (!got_BB[bb] && (strstr (buffer, BB_string[bb]))) {
				char c1[GMT_VF_LEN] = {""}, c2[GMT_VF_LEN] = {""}, c3[GMT_VF_LEN] = {""}, c4[GMT_VF_LEN] = {""};
				sscanf (&buffer[strlen(BB_string[bb])], "%s %s %s %s", c1, c2, c3, c4);
				E->BB[0] = atof (c1);	E->BB[2] = atof (c2);
				E->BB[1] = atof (c3);	E->BB[3] = atof (c4);
				got_BB[bb] = true;
				if (bb == 0) got_BB[1] = true;	/* If we find HighRes BB then we don't need to look for LowRes BB */
				GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Custom EPS symbol %s has width %g and height %g inches [%s]\n",
					path, (E->BB[1] - E->BB[0]) / 72, (E->BB[3] - E->BB[2]) / 72, &BB_string[bb][2]);
			}
		}
		if (buffer[0] == '%' && (buffer[1] == '%' || buffer[1] == '!')) continue;	/* Skip comments */
		strcat (E->macro, buffer);	/* Keep appending to the macro until EOF */
	}
	gmt_fclose (GMT, fp);
	if (strstr (E->macro, "%%Creator: GMT")) {	/* Check if a GMT EPS or not */
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "EPS symbol %s is a GMT-produced macro\n", path);
		E->GMT_made = true;	/* So we know to scale the EPS by 1200/72 or not in gmt_plot.c */
	}
	return (E);
}

GMT_LOCAL void gmtsupport_make_template (struct GMTAPI_CTRL *API, char *stem, char path[]) {
	/* Create a template for making a unique temporary file or directory name on the system.
	 * The 6 XXXXXX will be replaced by mktemp or mkstemp with a unique 6-char token (62^6 unique tokens).
	 * If a temp dir is designated then we use that in the path else we assume current directory.
	 * If stem is NULL we use "gmttemp" as file prefix.  If extension is not NULL we append it as is.
	 * Note: path is expected to have a length of PATH_MAX.
	 */
	if (API->tmp_dir)	/* Use the established temp directory */
		snprintf (path, PATH_MAX, "%s/%s_XXXXXX", API->tmp_dir, stem ? stem : "gmttemp");
	else	/* Must dump it in current directory */
		snprintf (path, PATH_MAX, "%s_XXXXXX", stem ? stem : "gmttemp");
}

int gmt_create_tempdir (struct GMTAPI_CTRL *API, char *name, char path[]) {
	/* Get unique directory name template and create directory in one go */

	gmtsupport_make_template (API, name, path);	/* Readying the directory name template */

#ifdef _WIN32
	if (gmt_get_tempname (API, name, NULL, path))
		return GMT_RUNTIME_ERROR;
	if (gmt_mkdir (path)) {
		GMT_Report (API, GMT_MSG_ERROR, "Unable to create directory %s - exiting.\n", path);
		return GMT_RUNTIME_ERROR;
	}
#else
	/* Create final temp dir name and create it at the same time to avoid race condition */
	if (mkdtemp (path) == NULL) {
		GMT_Report (API, GMT_MSG_ERROR, "Could not create temporary directory %s.\n", path);
		return (GMT_RUNTIME_ERROR);
	}
#endif
	return (GMT_NOERROR);
}

int gmt_get_tempname (struct GMTAPI_CTRL *API, char *stem, char *extension, char path[]) {
	/* Create a unique temporary file or directory name on the system;
	 * If stem is NULL we use "gmttemp" as file prefix.  If extension is not NULL we append it.
	 * Note: path is expected to have a length of PATH_MAX.
	 */

	gmtsupport_make_template (API, stem, path);	/* Readying the name template */

#ifdef _WIN32
	if (_mktemp_s (path, strlen(path) + 1) == EINVAL) {
#else
	if (mkstemp (path) == GMT_NOTSET) {
#endif
		GMT_Report (API, GMT_MSG_ERROR, "Could not create a temporary name from template %s.\n", path);
		return (GMT_RUNTIME_ERROR);
	}
	if (extension) strcat (path, extension);	/* Appending a file extension is unlikely to change uniqueness */
	return (GMT_NOERROR);
}

FILE *gmt_create_tempfile (struct GMTAPI_CTRL *API, char *stem, char *extension, char path[]) {
	/* Returns file pointer to the desired temp file open for writing */
	FILE *fp = NULL;
#ifndef _WIN32
	/* Here we can use the race-safe mkstemp function which returns a file descriptor */
	int fd = 0;
	gmt_M_unused (extension);
	gmtsupport_make_template (API, stem, path);	/* Readying the name template */
	if ((fd = mkstemp (path)) == -1) {	/* Create filename AND open in one go to avoid race condition */
		GMT_Report (API, GMT_MSG_ERROR, "gmt_create_tempfile: Could not create temporary file name and open it %s.\n", path);
		API->error = GMT_RUNTIME_ERROR;
		return NULL;
	}
	if ((fp = fdopen (fd, API->GMT->current.io.w_mode)) == NULL) {	/* Get FILE pointer from file descriptor */
		API->error = GMT_RUNTIME_ERROR;
		GMT_Report (API, GMT_MSG_ERROR, "gmt_create_tempfile: Could not fdopen the temporary file %s.\n", path);
		return NULL;
	}
#else	/* Must create file name first, then open file - susceptible to race condition if another process gets there first */
	if (gmt_get_tempname (API, stem, extension, path)) {
		GMT_Report (API, GMT_MSG_ERROR, "gmt_create_tempfile: Could not create temporary file name %s.\n", path);
		API->error = GMT_RUNTIME_ERROR;
		return NULL;
	}
	if ((fp = fopen (path, API->GMT->current.io.w_mode)) == NULL) {
		GMT_Report (API, GMT_MSG_ERROR, "gmtlib_get_tile_list: Unable to open the temporary file: %s.\n", path);
		API->error = GMT_RUNTIME_ERROR;
		return NULL;
	}
#endif
	return (fp);
}

/*! . */
GMT_LOCAL int gmtsupport_init_custom_symbol (struct GMT_CTRL *GMT, char *in_name, struct GMT_CUSTOM_SYMBOL **S) {
	/* Load in an initialize a new custom symbol.  These files can live in many places:
	 * 1. In the current directory
	 * 2. In the user dir [~/.gmt]
	 * 3. In the user cache dir [~/.gmt/cache]
	 * 4. In the user data dir [~/.gmt/data]
	 * 5. In the system share/custom dir
	 * THus we must use both gmt_getsharepath and gmtlib_getuserpath when looking */
	unsigned int k, nc = 0, nv, error = 0, var_symbol = 0, pos = 0, n_txt = 0, type;
	int last;
	bool do_fill, do_pen, first = true;
	char name[GMT_BUFSIZ] = {""}, path[PATH_MAX] = {""}, buffer[GMT_BUFSIZ] = {""}, col[8][GMT_LEN128], OP[GMT_LEN8] = {""}, right[GMT_LEN64] = {""};
	char arg[3][GMT_LEN64] = {"", "", ""}, *fill_p = NULL, *pen_p = NULL, *c = NULL;
	FILE *fp = NULL;
	struct GMT_CUSTOM_SYMBOL *head = NULL;
	struct GMT_CUSTOM_SYMBOL_ITEM *s = NULL, *previous = NULL;

	if ((type = gmt_locate_custom_symbol (GMT, in_name, name, path, &pos)) == 0) return GMT_RUNTIME_ERROR;

	if (type == GMT_CUSTOM_EPS) {	/* Must replace EPS symbol with a simple 1-action custom symbol EPS command */
		/* Single action with x=y=0, set size=1, and add in EPS loaded */
		if ((head = gmt_M_memory (GMT, NULL, 1, struct GMT_CUSTOM_SYMBOL)) == NULL) return GMT_MEMORY_ERROR;
		strncpy (head->name, basename (&name[pos]), GMT_LEN64-1);
		if ((s = gmt_M_memory (GMT, NULL, 1, struct GMT_CUSTOM_SYMBOL_ITEM)) == NULL) return GMT_MEMORY_ERROR;
		head->first = s;
		s->action = GMT_SYMBOL_EPS;
		s->p[0] = 1.0;
		if ((s->eps = gmtsupport_load_eps_symbol (GMT, name, path)) == NULL) return GMT_RUNTIME_ERROR;
		*S = head;
		return (GMT_NOERROR);
	}

	if ((fp = fopen (path, "r")) == NULL) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Could not find custom symbol %s\n", &name[pos]);
		return GMT_ERROR_ON_FOPEN;
	}

	if ((head = gmt_M_memory (GMT, NULL, 1, struct GMT_CUSTOM_SYMBOL)) == NULL) return GMT_MEMORY_ERROR;
	strncpy (head->name, basename (&name[pos]), GMT_LEN64-1);
	while (fgets (buffer, GMT_BUFSIZ, fp)) {
		if (buffer[0] == '#') continue;	/* Skip comments */
		gmt_chop (buffer);	/* Get rid of \n \r */
		if ((c = strrchr (buffer, '#')))	/* Has trailing comments */
			c[0] = '\0';	/* Chop it off */
		if (gmt_is_a_blank_line (buffer)) continue;	/* Skip blank lines */
		if (buffer[0] == 'N' && buffer[1] == ':') {	/* Got extra parameter specs. This is # of data columns expected beyond the x,y[,z] stuff */
			char flags[GMT_LEN64] = {""};
			nc = sscanf (&buffer[2], "%d %s", &head->n_required, flags);
			if ((head->type = gmt_M_memory (GMT, NULL, head->n_required, unsigned int)) == NULL) return GMT_MEMORY_ERROR;
			if (nc == 2) {	/* Got optional types argument */
				if (strlen (flags) != head->n_required) {
					GMT_Report (GMT->parent, GMT_MSG_ERROR, "Custom symbol %s has inconsistent N: <npar> [<types>] declaration\n", &name[pos]);
					fclose (fp);
					gmtsupport_free_one_custom_symbol (GMT, head);
					return GMT_PARSE_ERROR;
				}
				for (k = 0; k < head->n_required; k++) {	/* Determine the argument types */
					switch (flags[k]) {
						case 'a':	head->type[k] = GMT_IS_AZIMUTH; break;		/* Azimuth that needs to be converted via the map projection */
						case 'r':	head->type[k] = GMT_IS_ANGLE; break;		/* Angles, we enforce 0-360 range */
						case 'l':	head->type[k] = GMT_IS_DIMENSION; break;	/* Length that will be in the current measure unit */
						case 'o':	head->type[k] = GMT_IS_FLOAT; break;		/* Other, i.e, non-dimensional quantity not to be changed */
						case 's':	head->type[k] = GMT_IS_STRING; n_txt++;	break;		/* A text string */
						default:
							GMT_Report (GMT->parent, GMT_MSG_ERROR, "Custom symbol %s has unrecognized <types> declaration in %s\n", &name[pos], flags);
							fclose (fp);
							return GMT_PARSE_ERROR;
							break;
					}
				}
			}
			else {
				for (k = 0; k < head->n_required; k++) head->type[k] = GMT_IS_DIMENSION;	/* Default is lengths */
			}
			continue;
		}
		if ((s = gmt_M_memory (GMT, NULL, 1, struct GMT_CUSTOM_SYMBOL_ITEM)) == NULL) return GMT_MEMORY_ERROR;
		if (first) head->first = s;
		first = false;
		for (k = 0; k < 8; k++) col[k][0] = '\0';	/* Reset col array */
		if (strstr (buffer, "if $")) {	/* Parse a logical if-test or elseif here */
			if (strstr (buffer, "} elseif $")) {	/* Actually, it is an elseif-branch [skip { elseif]; nc -=3 means we count the cols only */
				nc = sscanf (buffer, "%*s %*s %s %s %s %*s %s %s %s %s %s %s %s %s", arg[0], OP, right, col[0], col[1], col[2], col[3], col[4], col[5], col[6], col[7]) - 3;
				s->conditional = GMT_BEGIN_ELSEIF;	/* elseif test */
			}
			else {	/* Starting if-branch [skip if] */
				nc = sscanf (buffer, "%*s %s %s %s %*s %s %s %s %s %s %s %s %s", arg[0], OP, right, col[0], col[1], col[2], col[3], col[4], col[5], col[6], col[7]) - 3;
				s->conditional = (col[nc-1][0] == '{') ? GMT_BEGIN_BLOCK_IF : GMT_BEGIN_SINGLE_IF;		/* If block or single if command */
			}
			for (k = 0; right[k]; k++) if (right[k] == ':') right[k] = ' ';	/* Remove any colon in case right side has two range values */
			nv = sscanf (right, "%s %s", arg[1], arg[2]);	/* Get one [or two] constants or variables on right hand side */
			for (k = 0; k < nv + 1; k++) {
				if (arg[k][0] == '$') {	/* Left or right hand side value is a variable */
					s->is_var[k] = true;
					if (arg[k][1] == 'x')	/* Test on x or longitude */
						s->var[k] = GMT_VAR_IS_X;
					else if (arg[k][1] == 'y')	/* Test on y or latitude */
						s->var[k] = GMT_VAR_IS_Y;
					else if (arg[k][1] == 's')	/* Test on symbol size */
						s->var[k] = GMT_VAR_SIZE;
					else if (arg[k][1] == 't') {	/* Test on trailing text or word */
						if (arg[k][2] == '\0')	/* The whole text */
							s->var[k] = GMT_VAR_STRING;
						else	/* Use a single word */
							s->var[k] = GMT_VAR_WORD + atoi (&arg[k][2]);	/* Get the word number $t<varno> plus GMT_VAR_WORD */
					}
					else
						s->var[k] = atoi (&arg[k][1]);	/* Get the variable number $<varno> */
					s->const_val[k] = 0.0;
				}
				else {	/* A constant */
					size_t len = strlen (arg[k]) - 1;
					s->is_var[k] = false;
					if (gmt_not_numeric (GMT, arg[k])) {	/* Got a text item for string comparison */
						size_t len = strlen (arg[k]);
						s->var[k] = GMT_CONST_STRING;
						s->string = gmt_M_memory (GMT, NULL, len + 1, char);
						if (len > 2 && ((arg[k][0] == '\"' && arg[k][len-1] == '\"') || (arg[k][0] == '\'' && arg[k][len-1] == '\'')))	/* Get rid of quotes */
							strncpy (s->string, &arg[k][1], len-2);
						else
							strcpy (s->string, arg[k]);
					}
					else {	/* Numerical value */
						s->var[k] = GMT_CONST_VAR;
						s->const_val[k] = (strchr (GMT_DIM_UNITS, arg[k][len])) ? gmt_M_to_inch (GMT, arg[k]) : atof (arg[k]);	/* A constant, possibly a length unit */
					}
				}
			}
			k = 0;
			if (OP[0] == '!') s->negate = true, k = 1;	/* Reverse any test that follows */
			s->operator = OP[k];	/* Use a 1-char code for operator (<, =, >, etc.); modify below where ambiguous */
			switch (OP[k]) {
				case '<':	/* Less than [Default] */
					if (OP[k+1] == '=')	/* Let <= be called operator L */
						s->operator = 'L';
					else if (OP[k+1] == '>')	/* Let <> be called operator i (exclusive in-range not including the boundaries) */
						s->operator = 'i';
					else if (OP[k+1] == ']')	/* Let <] be called operator r (in-range but only include right boundary) */
						s->operator = 'r';
					break;
				case '[':	/* Inclusive range */
					if (OP[k+1] == ']')	/* Let [] be called operator I (inclusive range) */
						s->operator = 'I';
					else if (OP[k+1] == '>')	/* Let [> be called operator l (in range but only include left boundary) */
						s->operator = 'l';
					break;
				case '>':	/* Greater than [Default] */
					if (OP[k+1] == '=') s->operator = 'G';	/* Let >= be called operator G */
					break;
				case '=':	/* Equal [Default] */
					if (OP[k+1] != '=') GMT_Report (GMT->parent, GMT_MSG_WARNING, "Please use == to indicate equality operator\n");
					if (gmt_M_is_dnan (s->const_val[0])) s->operator = 'E';	/* Let var == NaN be called operator E (equals NaN) */
					break;
			}
		}
		else if (strstr (buffer, "} else {"))	/* End of if-block and start of else-block */
			s->conditional = GMT_END_IF_ELSE;
		else if (strchr (buffer, '}'))		/* End of if-block */
			s->conditional = GMT_END_IF;
		else					/* Regular command, no conditional test prepended */
			nc = sscanf (buffer, "%s %s %s %s %s %s %s %s", col[0], col[1], col[2], col[3], col[4], col[5], col[6], col[7]);

		last = nc - 1;	/* Index of last col argument */

		/* Check if command has any trailing -Gfill -Wpen specifiers */

		do_fill = do_pen = false;
		if (col[last][0] == '-' && col[last][1] == 'G') fill_p = &col[last][2], do_fill = true, last--;
		if (col[last][0] == '-' && col[last][1] == 'W') pen_p = &col[last][2], do_pen = true, last--;
		if (col[last][0] == '-' && col[last][1] == 'G') fill_p = &col[last][2], do_fill = true, last--;	/* Check again for -G since perhaps -G -W was given */
		if (last < 0) error++;

		s->action = col[last][0];
		if (s->conditional == GMT_END_IF) s->action = '}';	/* The {, }, E, and F are dummy actions */
		if (s->conditional == GMT_END_IF_ELSE) s->action = 'E';
		if (s->conditional == GMT_BEGIN_ELSEIF) s->action = 'F';
		if (last >= 2 && s->conditional < GMT_BEGIN_BLOCK_IF) {	/* OK to parse x,y coordinates */
			s->x = atof (col[GMT_X]);
			s->y = atof (col[GMT_Y]);
		}
		/* Unfortunately, "R" was used for two things: General rotation and Rounded rectangle symbol.  We now use "O" for rotation
		 * but for backwards compatibility we must fix any old-style "R" for rotation here by replacing with "O" */
		if (s->action == 'R' && last == 1)	/* Got the deprecated R for rotate the coordinate system, not R for rounded rectangle */
			s->action = GMT_SYMBOL_ROTATE;

		switch (s->action) {

			/* M, D, S, and A allows for arbitrary lines or polygons to be designed - these may be painted or filled with pattern */

			case GMT_SYMBOL_MOVE:		/* Set a new anchor point */
				if (last != 2) error++;
				break;

			case GMT_SYMBOL_DRAW:		/* Draw to next point */
				if (last != 2) error++;
				break;

			case GMT_SYMBOL_STROKE:		/* Stroke current path as line, not polygon */
				if (last != 0) error++;
				break;

			case GMT_SYMBOL_ARC:		/* Draw arc of a circle */
				if (last != 5) error++;
				s->p[0] = atof (col[2]);
				gmtsupport_decode_arg (col[3], 1, s);	/* angle1 could be a variable or constant degrees */
				gmtsupport_decode_arg (col[4], 2, s);	/* angle2 could be a variable or constant degrees */
				break;

			case GMT_SYMBOL_ROTATE:		/* Rotate coordinate system about (0,0) */
				if (last != 1) error++;
				s->action = gmtsupport_decode_arg (col[0], 0, s);	/* angle could be a variable or constant heading or azimuth in degrees */
				break;

			case GMT_SYMBOL_TEXTURE:		/* Texture changes only (modify pen, fill settings) */
				if (last != 0) error++;
				break;

			case '{':		/* Start of block */
			case '}':		/* End of block */
			case 'E':		/* End of if-block and start of else block */
			case 'F':		/* End of if-block and start of another if block */
				break;	/* Nothing to do but move on */

			/* These are standard psxy-type symbols */

			case '?':		/* Any one of these standard types, obtained from last item in data record */
				var_symbol++;
				if (var_symbol == 1) {	/* First time we augment the type array by one to avoid bad memory access in psxy */
					if ((head->type = gmt_M_memory (GMT, head->type, head->n_required+1, unsigned int)) == NULL) return GMT_MEMORY_ERROR;
					head->type[head->n_required] = GMT_IS_DIMENSION;	/* It is actually a symbol code but this gets us passed the test */
				}
				/* Intentionally fall through */
			case PSL_STAR:			/* Draw star symbol */
			case PSL_CIRCLE:		/* Draw complete circle */
			case PSL_DIAMOND:		/* Draw diamond symbol */
			case PSL_OCTAGON:		/* Draw octagon symbol */
			case PSL_HEXAGON:		/* Draw hexagon symbol */
			case PSL_INVTRIANGLE:	/* Draw inverted triangle symbol */
			case PSL_PENTAGON:		/* Draw pentagon symbol */
			case PSL_DOT:			/* Draw solid dot */
			case PSL_SQUARE:		/* Draw square symbol */
			case PSL_TRIANGLE:		/* Draw triangle symbol */
			case PSL_CROSS:			/* Draw cross symbol */
			case PSL_YDASH:			/* Draw vertical dash symbol */
			case PSL_PLUS:			/* Draw plus symbol */
			case PSL_XDASH:			/* Draw horizontal dash symbol */
				if (last != 3) error++;
				s->p[0] = atof (col[2]);
				break;

			case GMT_SYMBOL_TEXT:		/* Draw letter/text symbol [ expect x, y, size, string l] */
				if (last != 4) error++;	/* Did not get the expected arguments */
				s->p[0] = atof (col[2]);	/* Text size is either (1) fixed point size of (2) fractional size relative to the 1x1 box */
				if (col[2][strlen(col[2])-1] == 'p')	/* Gave font size as a fixed point size that will not scale with symbol size */
					s->p[0] = -s->p[0];	/* Mark fixed size via a negative point size */
				s->string = gmt_M_memory (GMT, NULL, strlen (col[3]) + 1, char);
				strcpy (s->string, col[3]);
				if ((c = strchr (s->string, '$'))) {	/* Got a text string variable */
					s->action = GMT_SYMBOL_VARTEXT;
					if (c[1] == 't' && isdigit (c[2]))	/* Select this word from trailing text */
						s->var[0] = atoi (&c[2]);	/* Word number is 0-(n-1) */
				}
				s->font = GMT->current.setting.font_annot[GMT_PRIMARY];	/* Default font for symbols */
				s->justify = PSL_MC;				/* Default justification of text */
				head->text = 1;	/* We will be typesetting text so fonts are required */
				if (s->action == GMT_SYMBOL_VARTEXT && c[1] == 't') head->text = 2;	/* Flag that trailing text will be used */
				k = 1;
				while (col[last][k] && col[last][k] != '+') k++;
				if (col[last][k]) {	/* Gave modifiers */
					unsigned int pos = 0;
					char p[GMT_BUFSIZ] = {""};
					while ((gmt_strtok (&col[last][k], "+", &pos, p))) {	/* Parse any +<modifier> statements */
						switch (p[0]) {
							case 'f':	/* Change font [Note: font size is ignored as the size argument take precedent] */
								if (gmt_getfont (GMT, &p[1], &s->font))
									GMT_Report (GMT->parent, GMT_MSG_WARNING, "Macro code l contains bad +<font> modifier (set to %s)\n", gmt_putfont (GMT, &s->font));
								break;
							case 'j':	s->justify = gmt_just_decode (GMT, &p[1], PSL_NO_DEF);	break;	/* text justification */
							default:
								GMT_Report (GMT->parent, GMT_MSG_ERROR, "Macro code l contains bad modifier +%c\n", p[0]);
								error++;
								break;
						}
					}
				}
				/* Fit in GMT 4 compatibility mode we must check for obsolete %font suffix in the text */
				if (gmt_M_compat_check (GMT, 4) && (c = strchr (s->string, '%')) && !(c[1] == 'X' || c[1] == 'Y')) {	/* Gave font name or number, too, using GMT 4 style */
					GMT_Report (GMT->parent, GMT_MSG_COMPAT, "Warning in macro l: <string>[%%<font>] is deprecated syntax, use +f<font> instead\n");
					*c = 0;		/* Replace % with the end of string NUL indicator */
					c++;		/* Go to next character */
					if (gmt_getfont (GMT, c, &s->font)) GMT_Report (GMT->parent, GMT_MSG_WARNING, "Custom symbol subcommand l contains bad GMT4-style font information (set to %s)\n", gmt_putfont (GMT, &GMT->current.setting.font_annot[GMT_PRIMARY]));
				}

				break;

			case PSL_RECT:		/* Draw rect symbol */
				if (last != 4) error++;
				s->p[0] = atof (col[2]);
				s->p[1] = atof (col[3]);
				break;

			case PSL_RNDRECT:		/* Draw rounded rect symbol */
				if (last != 5) error++;
				s->p[0] = atof (col[2]);
				s->p[1] = atof (col[3]);
				s->p[2] = atof (col[4]);
				break;

			case PSL_ELLIPSE:		/* Draw ellipse symbol */
			case PSL_ROTRECT:		/* Draw rotated rect symbol */
				if (last != 5) error++;
				gmtsupport_decode_arg (col[2], 0, s);	/* angle could be a variable or constant degrees */
				s->p[1] = atof (col[3]);
				s->p[2] = atof (col[4]);
				break;

			case PSL_MARC:		/* Draw mathangle symbol */
			case PSL_WEDGE:		/* Draw wedge (pie) symbol */
				if (last != 5) error++;
				s->p[0] = atof (col[2]);
				gmtsupport_decode_arg (col[3], 1, s);	/* angle1 could be a variable or constant degrees */
				gmtsupport_decode_arg (col[4], 2, s);	/* angle2 could be a variable or constant degrees */
				break;

			case PSL_VECTOR:		/* Draw a vector symbol. Vector head is hardwired and scales with pen thickness */
				if (last != 4) error++;
				gmtsupport_decode_arg (col[2], 0, s);	/* angle could be a variable or constant degrees */
				s->p[1] = atof (col[3]);	/* Non-dimensional length */
				break;

			case GMT_SYMBOL_EPS:		/* Place EPS file */
				if (last != 4) error++;
				s->p[0] = atof (col[2]);
				if ((type = gmt_locate_custom_symbol (GMT, col[3], name, path, &pos)) == 0) return GMT_RUNTIME_ERROR;
				if ((s->eps = gmtsupport_load_eps_symbol (GMT, name, path)) == NULL) return GMT_RUNTIME_ERROR;
				break;

			default:
				error++;
				break;
		}

		if (error) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Failed to parse symbol commands in file %s\n", path);
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Offending line: %s\n", buffer);
			gmt_M_free (GMT, head);
			fclose (fp);
			return GMT_PARSE_ERROR;
		}

		if (do_fill) {	/* Update current fill */
			s->fill = gmt_M_memory (GMT, NULL, 1, struct GMT_FILL);
			if ((c = strstr (fill_p, "+p")))	/* Want to replace this fills's color with that of the current pen color */
				s->var_pen -= GMT_USE_PEN_RGB;	/* Flag so we can replace fill color at run-time */
			else if (fill_p[0] == '-')	/* Do not want to fill this polygon */
				s->fill->rgb[0] = -1.0;
			else if (gmt_getfill (GMT, fill_p, s->fill)) {
				gmt_fill_syntax (GMT, 'G', NULL, " ");
				fclose (fp);
				gmt_M_free (GMT, head);
				return GMT_PARSE_ERROR;
			}
		}
		else
			s->fill = NULL;
		if (do_pen) {	/* Update current pen */
			s->pen = gmt_M_memory (GMT, NULL, 1, struct GMT_PEN);
			if (pen_p[0] == '-')	/* Do not want to draw outline */
				s->pen->rgb[0] = -1.0;
			else {	/* Pen of some sort */
				bool p_normal = false;
				if ((c = strstr (pen_p, "+g"))) {	/* Want to replace this pen's color with that of the current fill color */
					s->var_pen -= GMT_USE_FILL_RGB;	/* Flag so we can replace pen color at run-time */
					c[0] = '\0';	/* Chop off the "g+" suffix */
				}
				if (pen_p[0] == '$')	{	/* Variable pen thickness obtained at run-time via data column */
					unsigned int k = 0;
					s->var_pen = atoi (&pen_p[1]);	/* Remember variable column number */
					/* Replace ${var} by "01" (number of zeros depends on size of var), scale pen by the indicated variable later */
					while (pen_p[k] && pen_p[k] != ',')
						pen_p[k++] = '0';
					if (k) pen_p[k-1] = '1';	/* Now we have a unit pen thickness for later scaling */
				}
				if (gmt_getpen (GMT, pen_p, s->pen)) {
					gmt_pen_syntax (GMT, 'W', NULL, " ", NULL, 0);
					fclose (fp);
					return GMT_PARSE_ERROR;
				}
				if ((c = strchr (pen_p, ','))) c[0] = '\0';	/* Chop off anything after pen width so we can check for pen units */
				if (strchr (pen_p, 'c') == NULL && strchr (pen_p, 'i') == NULL && strchr (pen_p, 'p') == NULL) {
					/* No unit means normalized pen thickness in 0-1 range to be scaled by symbol size later */
					p_normal = true;
				}
				if (p_normal) s->pen->width = -s->pen->width;	/* Negative pen means normalized 0-1 */
				if (c) c[0] = ',';	/* Restore the pen argument */
			}
		}
		else
			s->pen = NULL;

		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Code %c Conditional = %d OP = %c negate = %d var = %d/%d/%d do_pen = %d do_fill = %d\n", \
			(int)s->action, s->conditional, (int)s->operator, s->negate, s->var[0], s->var[1], s->var[2], do_pen, do_fill);
		if (previous) previous->next = s;
		previous = s;
	}
	fclose (fp);
	head->n_required -= n_txt;	/* Words from trailing text is not part of required arguments (which are all numerical) */
	*S = head;
	return (GMT_NOERROR);
}

/*! . */
GMT_LOCAL double gmtsupport_polygon_area (struct GMT_CTRL *GMT, double x[], double y[], uint64_t n) {
	uint64_t i, last;
	double area, xold, yold;

	/* Sign will be +ve if polygon is CW, negative if CCW */

	last = (n > 2 && gmt_polygon_is_open (GMT, x, y, n)) ? n : n - 1;	/* Skip repeating vertex */

	area = yold = 0.0;
	xold = x[last-1];
	yold = y[last-1];

	for (i = 0; i < last; i++) {
		area += (xold - x[i]) * (yold + y[i]);
		xold = x[i];
		yold = y[i];
	}
	return (0.5 * area);
}

#if 0
GMT_LOCAL void gmtsupport_dataset_detrend (struct GMT_CTRL *GMT, struct GMT_DATASET *D, unsigned int mode, double *coeff) {
	/* Will detrend the x [and y if not NULL] columns separately. */
	unsigned id = 0, tbl, col, n_cols;
	uint64_t row, seg;
	double sumt, sumt2, sumx, sumtx, xmin, xmax, t, t_factor;
	struct GMT_DATASEGMENT *S = NULL;

	/* mode = 0 (GMT_FFT_REMOVE_NOTHING):  Do nothing.
	   mode = 1 (GMT_FFT_REMOVE_MEAN):  Remove the mean value (returned via coeff[0], coeff[2])
	   mode = 2 (GMT_FFT_REMOVE_MID):   Remove the mid value value (returned via coeff[0], coeff[2])
	   mode = 3 (GMT_FFT_REMOVE_TREND): Remove the best-fitting line by least squares (returned via coeff[0-4])
	*/
	if (mode == GMT_FFT_REMOVE_NOTHING) {	/* Do nothing */
		GMT_Report (API, GMT_MSG_WARNING, "No detrending selected\n");
		return;
	}
	t_factor =  2.0 / (n - 1);
	for (tbl = seg_no = 0; tbl < D->n_tables; tbl++) {
		for (seg = 0; seg < D->n_segments; seg++) {	/* For each segment to modify */
			S = D->table[tbl]->segment[seg];
			for (col = 1; col < n_cols; col++) {
				sumt = sumt2 = sumx = sumtx = 0.0;
				xmin = DBL_MAX, xmax = -DBL_MAX;
				for (row = 0; row < S->n_rows; row++) {
					t = row * t_factor - 1.0;
					sumt += t;
					sumt2 += (t * t);
					sumx += S->data[col][row];
					sumtx += (t * S->data[col][row]);
					if (S->data[col][row] < xmin) xmin = S->data[col][row];
					if (S->data[col][row] > xmax) xmax = S->data[col][row];
				}
				id = 2 * (col - 1);
				coeff[id] = (mode == GMT_FFT_REMOVE_MID) ? 0.5 * (xmin + xmax) : sumx / S->n_rows;
				coeff[id+1] = (mode == GMT_FFT_REMOVE_TREND) ? sumtx / sumt2 : 0.0;
				/* Remove the desired trend */
				for (row = 0; row < S->n_rows; row++) {
					t = row * t_factor - 1.0;
					S->data[col][row] -= (coeff[id] + t * coeff[id+1]);
				}
			}
		}
	}
}

GMT_LOCAL void gmtsupport_cols_detrend (struct GMT_CTRL *GMT, double *t, double *x, double *y, uint64_t n, unsigned int mode, double *coeff) {
	/* Will detrend the x [and y if not NULL] columns separately. */
	unsigned id = 0, tbl, col, n_cols;
	uint64_t row, seg;
	double sumt, sumt2, sumx, sumtx, xmin, xmax, t, t_factor, *C[2] = {NULL, NULL};
	struct GMT_DATASEGMENT *S = NULL;

	/* mode = 0 (GMT_FFT_REMOVE_NOTHING):  Do nothing.
	   mode = 1 (GMT_FFT_REMOVE_MEAN):  Remove the mean value (returned via coeff[0], coeff[2])
	   mode = 2 (GMT_FFT_REMOVE_MID):   Remove the mid value value (returned via coeff[0], coeff[2])
	   mode = 3 (GMT_FFT_REMOVE_TREND): Remove the best-fitting line by least squares (returned via coeff[0-4])
	*/
	if (mode == GMT_FFT_REMOVE_NOTHING) {	/* Do nothing */
		GMT_Report (API, GMT_MSG_WARNING, "No detrending selected\n");
		return;
	}
	t_factor =  2.0 / (n - 1);
	n_cols = (y == NULL) ? 1 : 2;
	C[0] = x;	C[1] = y;	/* So we can loop over these columns */
	for (col = 0; col < n_cols; col++) {
		sumt = sumt2 = sumx = sumtx = 0.0;
		xmin = DBL_MAX, xmax = -DBL_MAX;
		for (row = 0; row < S->n_rows; row++) {
			t = row * t_factor - 1.0;
			sumt += t;
			sumt2 += (t * t);
			sumx += C[col][row];
			sumtx += (t * C[col][row]);
			if (C[col][row] < xmin) xmin = C[col][row];
			if (C[col][row] > xmax) xmax = C[col][row];
		}
		id = 2 * (col - 1);
		coeff[id] = (mode == GMT_FFT_REMOVE_MID) ? 0.5 * (xmin + xmax) : sumx / S->n_rows;
		coeff[id+1] = (mode == GMT_FFT_REMOVE_TREND) ? sumtx / sumt2 : 0.0;
		/* Remove the desired trend */
		for (row = 0; row < S->n_rows; row++) {
			t = row * t_factor - 1.0;
			C[col][row] -= (coeff[id] + t * coeff[id+1]);
		}
	}
}
#endif

#define SEG_DIST 2
#define SEG_AZIM 3

/*! . */
GMT_LOCAL struct GMT_DATASET * gmtsupport_resample_data_spherical (struct GMT_CTRL *GMT, struct GMT_DATASET *Din, double along_ds, unsigned int mode, unsigned int ex_cols, enum GMT_enum_track smode) {
	/* Spherical version; see gmt_resample_data for details */
	int ndig;
	bool resample;
	uint64_t tbl, col, n_cols;
	uint64_t row, seg, seg_no;
	char buffer[GMT_BUFSIZ] = {""}, ID[GMT_BUFSIZ] = {""};
	double along_dist, azimuth, dist_inc;
	struct GMT_DATASET *D = NULL;
	struct GMT_DATATABLE *Tin = NULL, *Tout = NULL;
	struct GMT_DATASEGMENT_HIDDEN *SH = NULL;

	resample = (!gmt_M_is_zero(along_ds));
	n_cols = 2 + mode + ex_cols;
	D = gmt_alloc_dataset (GMT, Din, 0, n_cols, GMT_ALLOC_NORMAL);	/* Same table length as Din, but with up to 4 columns (lon, lat, dist, az) */
	ndig = irint (floor (log10 ((double)Din->n_segments))) + 1;	/* Determine how many decimals are needed for largest segment id */

	for (tbl = seg_no = 0; tbl < Din->n_tables; tbl++) {
		Tin  = Din->table[tbl];
		Tout = D->table[tbl];
		for (seg = Tout->n_records = 0; seg < Tin->n_segments; seg++, seg_no++) {	/* For each segment to resample */
			gmt_M_memcpy (Tout->segment[seg]->data[GMT_X], Tin->segment[seg]->data[GMT_X], Tin->segment[seg]->n_rows, double);	/* Duplicate longitudes */
			gmt_M_memcpy (Tout->segment[seg]->data[GMT_Y], Tin->segment[seg]->data[GMT_Y], Tin->segment[seg]->n_rows, double);	/* Duplicate latitudes */
			SH = gmt_get_DS_hidden (Tout->segment[seg]);
			/* Resample lines as per smode */
			if (resample) {	/* Resample lon/lat path and also reallocate more space for all other columns */
				Tout->segment[seg]->n_rows = SH->n_alloc = gmt_resample_path (GMT, &Tout->segment[seg]->data[GMT_X], &Tout->segment[seg]->data[GMT_Y], Tout->segment[seg]->n_rows, along_ds, smode);
				for (col = 2; col < n_cols; col++)	/* Also realloc the other columns */
					Tout->segment[seg]->data[col] = gmt_M_memory (GMT, Tout->segment[seg]->data[col], Tout->segment[seg]->n_rows, double);
			}
			Tout->n_records += Tout->segment[seg]->n_rows;	/* Update record count */
			if (mode == 0) continue;	/* No dist/az needed */
			for (row = 0, along_dist = 0.0; row < Tout->segment[seg]->n_rows; row++) {	/* Process each point along resampled FZ trace */
				dist_inc = (row) ? gmt_distance (GMT, Tout->segment[seg]->data[GMT_X][row], Tout->segment[seg]->data[GMT_Y][row], Tout->segment[seg]->data[GMT_X][row-1], Tout->segment[seg]->data[GMT_Y][row-1]) : 0.0;
				along_dist += dist_inc;
				Tout->segment[seg]->data[SEG_DIST][row] = along_dist;
				if (mode == 1) continue;	/* No az needed */
				if (row)
					azimuth = gmt_az_backaz (GMT, Tout->segment[seg]->data[GMT_X][row-1], Tout->segment[seg]->data[GMT_Y][row-1], Tout->segment[seg]->data[GMT_X][row], Tout->segment[seg]->data[GMT_Y][row], false);
				else	/* Special deal for first point */
					azimuth = gmt_az_backaz (GMT, Tout->segment[seg]->data[GMT_X][0], Tout->segment[seg]->data[GMT_Y][0], Tout->segment[seg]->data[GMT_X][1], Tout->segment[seg]->data[GMT_Y][1], false);
				Tout->segment[seg]->data[SEG_AZIM][row] = azimuth;
			}
			ID[0] = 0;
			if (Tout->segment[seg]->label) strncpy (ID, Tout->segment[seg]->label, GMT_BUFSIZ-1);	/* Look for label in header */
			else if (Tout->segment[seg]->header) gmt_parse_segment_item (GMT, Tout->segment[seg]->header, "-L", ID);	/* Look for label in header */
			if (!ID[0]) snprintf (ID, GMT_BUFSIZ, "%*.*" PRIu64, ndig, ndig, seg_no);	/* Must assign a label from running numbers */
			if (!Tout->segment[seg]->label) Tout->segment[seg]->label = strdup (ID);
			gmt_M_str_free (Tout->segment[seg]->header);
			snprintf (buffer, GMT_BUFSIZ, "Segment label -L%s", ID);
			Tout->segment[seg]->header = strdup (buffer);
		}
	}
	return (D);
}

/*! . */
GMT_LOCAL struct GMT_DATASET * gmtsupport_resample_data_cartesian (struct GMT_CTRL *GMT, struct GMT_DATASET *Din, double along_ds, unsigned int mode, unsigned int ex_cols, enum GMT_enum_track smode) {
	/* Cartesian version; see gmt_resample_data for details */

	int ndig;
	bool resample;
	uint64_t tbl, col, n_cols;
	uint64_t row, seg, seg_no;
	char buffer[GMT_BUFSIZ] = {""}, ID[GMT_BUFSIZ] = {""};
	double along_dist, azimuth, dist_inc;
	struct GMT_DATASET *D = NULL;
	struct GMT_DATATABLE *Tin = NULL, *Tout = NULL;
	struct GMT_DATASEGMENT_HIDDEN *SH = NULL;

	resample = (!gmt_M_is_zero(along_ds));
	n_cols = 2 + mode + ex_cols;
	D = gmt_alloc_dataset (GMT, Din, 0, n_cols, GMT_ALLOC_NORMAL);	/* Same table length as Din, but with up to 4 columns (lon, lat, dist, az) */
	ndig = irint (floor (log10 ((double)Din->n_segments))) + 1;	/* Determine how many decimals are needed for largest segment id */

	for (tbl = seg_no = 0; tbl < Din->n_tables; tbl++) {
		Tin  = Din->table[tbl];
		Tout = D->table[tbl];
		for (seg = Tout->n_records = 0; seg < Tin->n_segments; seg++, seg_no++) {	/* For each segment to resample */
			gmt_M_memcpy (Tout->segment[seg]->data[GMT_X], Tin->segment[seg]->data[GMT_X], Tin->segment[seg]->n_rows, double);	/* Duplicate x */
			gmt_M_memcpy (Tout->segment[seg]->data[GMT_Y], Tin->segment[seg]->data[GMT_Y], Tin->segment[seg]->n_rows, double);	/* Duplicate y */
			SH = gmt_get_DS_hidden (Tout->segment[seg]);
			/* Resample lines as per smode */
			if (resample) {	/* Resample x/y path and also reallocate more space for all other columns */
				Tout->segment[seg]->n_rows = SH->n_alloc = gmt_resample_path (GMT, &Tout->segment[seg]->data[GMT_X], &Tout->segment[seg]->data[GMT_Y], Tout->segment[seg]->n_rows, along_ds, smode);
				for (col = 2; col < n_cols; col++)	/* Also realloc the other columns */
					Tout->segment[seg]->data[col] = gmt_M_memory (GMT, Tout->segment[seg]->data[col], Tout->segment[seg]->n_rows, double);
			}
			Tout->n_records += Tout->segment[seg]->n_rows;	/* Update record count */
			if (mode == 0) continue;	/* No dist/az needed */
			for (row = 0, along_dist = 0.0; row < Tout->segment[seg]->n_rows; row++) {	/* Process each point along resampled FZ trace */
				dist_inc = (row) ? gmt_distance (GMT, Tout->segment[seg]->data[GMT_X][row], Tout->segment[seg]->data[GMT_Y][row], Tout->segment[seg]->data[GMT_X][row-1], Tout->segment[seg]->data[GMT_Y][row-1]) : 0.0;
				along_dist += dist_inc;
				Tout->segment[seg]->data[SEG_DIST][row] = along_dist;
				if (mode == 1) continue;	/* No az needed */
				if (row)
					azimuth = gmt_az_backaz (GMT, Tout->segment[seg]->data[GMT_X][row-1], Tout->segment[seg]->data[GMT_Y][row-1], Tout->segment[seg]->data[GMT_X][row], Tout->segment[seg]->data[GMT_Y][row], false);
				else	/* Special deal for first point */
					azimuth = gmt_az_backaz (GMT, Tout->segment[seg]->data[GMT_X][0], Tout->segment[seg]->data[GMT_Y][0], Tout->segment[seg]->data[GMT_X][1], Tout->segment[seg]->data[GMT_Y][1], false);
				Tout->segment[seg]->data[SEG_AZIM][row] = azimuth;
			}
			ID[0] = 0;
			if (Tout->segment[seg]->label) strncpy (ID, Tout->segment[seg]->label, GMT_BUFSIZ-1);	/* Look for label in header */
			else if (Tout->segment[seg]->header) gmt_parse_segment_item (GMT, Tout->segment[seg]->header, "-L", ID);	/* Look for label in header */
			if (!ID[0]) snprintf (ID, GMT_BUFSIZ, "%*.*" PRIu64, ndig, ndig, seg_no);	/* Must assign a label from running numbers */
			if (!Tout->segment[seg]->label) Tout->segment[seg]->label = strdup (ID);
			gmt_M_str_free (Tout->segment[seg]->header);
			snprintf (buffer, GMT_BUFSIZ, "Segment label -L%s", ID);
			Tout->segment[seg]->header = strdup (buffer);
		}
	}
	return (D);

}

/*! . */
GMT_LOCAL struct GMT_DATASET * gmtsupport_crosstracks_spherical (struct GMT_CTRL *GMT, struct GMT_DATASET *Din, double cross_length, double across_ds, double deviation, uint64_t n_cols, unsigned int mode, char unit) {
	/* Din is a data set with at least two columns (lon/lat);
	 * it can contain any number of tables and segments.
	 * cross_length is the desired length of cross-profiles, in meters.
	 * across_ds is the sampling interval to use along the cross-profiles.
	 * n_cols sets how many data columns beyond x,y,d should be allocated.
	 * Dout is the new data set with all the crossing profiles; it will
	 * have 4 + n_cols columns, where the first 4 are x,y,d,az.
	 */

	int k, ndig, sdig, n_cross, n_half_cross, k_start, k_stop;

	unsigned int ii, np_cross;

	uint64_t dim[GMT_DIM_SIZE] = {0, 0, 0, 0};

	uint64_t tbl, row, left, right, seg, seg_no, n_tot_cols;
	size_t n_x_seg = 0, n_x_seg_alloc = 0;

	bool skip_seg_no, set_fixed_azim = false;

	char buffer[GMT_BUFSIZ] = {""}, seg_name[GMT_BUFSIZ] = {""}, ID[GMT_BUFSIZ] = {""};

	double dist_inc, d_shift, orientation, sign = 1.0, az_cross, x, y, fixed_azim, dist_to_end;
	double dist_across_seg, angle_radians, across_ds_radians, ds_phase = 0.0, n_cross_float;
	double Rot[3][3], Rot0[3][3], E[3], P[3], L[3], R[3], T[3], X[3];

	struct GMT_DATASET *Xout = NULL;
	struct GMT_DATATABLE *Tin = NULL, *Tout = NULL;
	struct GMT_DATASEGMENT *S = NULL;

	if (Din->n_columns < 2) {	/* Trouble */
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Dataset does not have at least 2 columns with coordinates\n");
		return (NULL);
	}

	if (mode & GMT_ALTERNATE) sign = -1.0;	/* Survey layout */
	if (mode & GMT_FIXED_AZIM) {	/* Got fixed azimuth */
		fixed_azim = deviation;
		deviation = 0.0;	/* To prevent any deviation below */
		set_fixed_azim = true;
	}

	/* Get resampling step size and zone width in degrees */

	n_cross_float = cross_length / across_ds;	/* Number of points in a cross profile may be a fraction if badly chosen increments */
	n_cross = irint (n_cross_float);	/* Number of integer points in a cross profile */
	if (fabs (n_cross_float - n_cross) > (0.05 * across_ds))	/* Use a 5% slop */
		GMT_Report (GMT->parent, GMT_MSG_WARNING, "Your crossprofile length (%g) is not an integer multiple of your along-profile-spacing (%g); %g will be rounded to nearest integer %d\n", cross_length, across_ds, n_cross_float, n_cross);
	cross_length = cross_length / GMT->current.map.dist[GMT_MAP_DIST].scale;	/* Now in meters [or degrees] */
	n_cross++;	/* Since one more node than increments */
	n_half_cross = (n_cross % 2) ? (n_cross - 1) / 2 : n_cross / 2;	/* Half-width of points in a cross profile depending on odd/even */
	if (unit && strchr (GMT_ARC_UNITS, unit)) {	/* Gave increments in arc units (already in degrees at this point) */
		across_ds_radians = D2R * cross_length / (n_cross - 1);	/* Angular change from point to point */
		dist_to_end = 0.5 * cross_length;	/* Distance from center to end of profile in degrees */
	}
	else {	/* Must convert distances to degrees */
		dist_to_end = 0.5 * cross_length / GMT->current.proj.DIST_M_PR_DEG;		/* Distance from center to end of profile in degrees */
		across_ds_radians = D2R * (cross_length / GMT->current.proj.DIST_M_PR_DEG) / (n_cross - 1);	/* Angular change from point to point */
	}
	if ((n_cross % 2) == 0) ds_phase = 0.5;
	k_start = -n_half_cross;
	k_stop = k_start + n_cross - 1;
	if (mode & GMT_LEFT_ONLY)	/* Only want left side of profiles */
		k_stop = 0;
	else if (mode & GMT_RIGHT_ONLY)	/* Only want right side of profiles */
		k_start = 0;
	np_cross = k_stop - k_start + 1;/* Total cross-profile length */

	n_tot_cols = 4 + n_cols;	/* Total number of columns in the resulting data set */
	dim[GMT_TBL] = Din->n_tables;	dim[GMT_COL] = n_tot_cols;	dim[GMT_ROW] = np_cross;
	if ((Xout = GMT_Create_Data (GMT->parent, GMT_IS_DATASET, GMT_IS_LINE, 0, dim, NULL, NULL, 0, 0, NULL)) == NULL) return (NULL);	/* An empty dataset of n_tot_cols columns and np_cross rows */
	sdig = irint (floor (log10 ((double)Din->n_segments))) + 1;	/* Determine how many decimals are needed for largest segment id */
	skip_seg_no = (Din->n_tables == 1 && Din->table[0]->n_segments == 1);
	for (tbl = seg_no = 0; tbl < Din->n_tables; tbl++) {	/* Process all tables */
		Tin  = Din->table[tbl];
		Tout = Xout->table[tbl];
		for (seg = 0; seg < Tin->n_segments; seg++, seg_no++) {	/* Process all segments */

			ndig = irint (floor (log10 ((double)Tin->segment[seg]->n_rows))) + 1;	/* Determine how many decimals are needed for largest id */

			GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Process Segment %s [segment %" PRIu64 "] which has %" PRIu64 " crossing profiles\n", Tin->segment[seg]->label, seg, Tin->segment[seg]->n_rows);

			/* Resample control point track along great circle paths using specified sampling interval */

			for (row = 0; row < Tin->segment[seg]->n_rows; row++) {	/* Process each point along segment */
				/* Compute segment line orientation (-90/90) from azimuths */
				orientation = 0.5 * fmod (2.0 * Tin->segment[seg]->data[SEG_AZIM][row], 360.0);
				if (orientation > 90.0) orientation -= 180.0;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Working on cross profile %" PRIu64 " [local line orientation = %06.1f]\n", row, orientation);

				x = Tin->segment[seg]->data[GMT_X][row];	y = Tin->segment[seg]->data[GMT_Y][row];	/* Reset since now we want lon/lat regardless of grid format */
				gmt_geo_to_cart (GMT, y, x, P, true);		/* 3-D vector of current point P */
				if (set_fixed_azim) {	/* Need 2nd point in azim direction to cross with P */
					double b_x, b_y;
					gmtlib_translate_point (GMT, x, y, fixed_azim, dist_to_end, &b_x, &b_y, NULL);
					gmt_geo_to_cart (GMT, b_y, b_x, R, true);		/* 3-D vector of end point R */
					gmt_cross3v (GMT, P, R, E);			/* Get pole E to plane trough P and R */
				}
				else {	/* Erect an orthogonal (- deviation) profile */
					left = (row) ? row - 1 : row;			/* Left point (if there is one) */
					x = Tin->segment[seg]->data[GMT_X][left];	y = Tin->segment[seg]->data[GMT_Y][left];
					gmt_geo_to_cart (GMT, y, x, L, true);		/* 3-D vector of left point L */
					right = (row < (Tin->segment[seg]->n_rows-1)) ? row + 1 : row;	/* Right point (if there is one) */
					x = Tin->segment[seg]->data[GMT_X][right];	y = Tin->segment[seg]->data[GMT_Y][right];
					gmt_geo_to_cart (GMT, y, x, R, true);		/* 3-D vector of right point R */
					gmt_cross3v (GMT, L, R, T);			/* Get pole T of plane trough L and R (and center of Earth) */
					gmt_normalize3v (GMT, T);			/* Make sure T has unit length */
					gmt_cross3v (GMT, T, P, E);			/* Get pole E to plane trough P normal to L,R (hence going trough P) */
				}
				gmt_normalize3v (GMT, E);			/* Make sure E has unit length */
				if (!gmt_M_is_zero (deviation)) {	/* Must now rotate E about P by the deviation first */
					gmtlib_load_rot_matrix (-D2R * deviation, Rot0, P);	/* Negative so that rotation goes clockwise */
					gmt_matrix_vect_mult (GMT, 3U, Rot0, E, X);				/* Rotate E about P by deviation */
					gmt_M_memcpy (E, X, 3u, double);	/* Copy the result to E */
					gmt_normalize3v (GMT, E);			/* Make sure E has unit length */
				}
				gmtlib_init_rot_matrix (Rot0, E);			/* Get partial rotation matrix since no actual angle is applied yet */
				az_cross = fmod (Tin->segment[seg]->data[SEG_AZIM][row] + 270.0, 360.0);	/* Azimuth of cross-profile in 0-360 range */
				if (mode & GMT_ALTERNATE)
					sign = -sign;
				else if (mode & GMT_EW_SN)
					sign = (az_cross >= 315.0 || az_cross < 135.0) ? -1.0 : 1.0;	/* We want profiles to be either ~E-W or ~S-N */
				dist_across_seg = 0.0;
				S = GMT_Alloc_Segment (GMT->parent, GMT_NO_STRINGS, np_cross, n_tot_cols, NULL, NULL);
				for (k = k_start, ii = 0; k <= k_stop; k++, ii++) {	/* For each point along normal to FZ */
					angle_radians = sign * (k + ds_phase) * across_ds_radians;		/* The required rotation for this point relative to FZ origin */
					gmt_M_memcpy (Rot, Rot0, 9, double);			/* Get a copy of the "0-angle" rotation matrix */
					gmtlib_load_rot_matrix (angle_radians, Rot, E);		/* Build the actual rotation matrix for this angle */
					gmt_matrix_vect_mult (GMT, 3U, Rot, P, X);				/* Rotate the current FZ point along the normal */
					gmt_cart_to_geo (GMT, &S->data[GMT_Y][ii], &S->data[GMT_X][ii], X, true);	/* Get lon/lat of this point along crossing profile */
					dist_inc = (ii) ? gmt_distance (GMT, S->data[GMT_X][ii], S->data[GMT_Y][ii], S->data[GMT_X][ii-1], S->data[GMT_Y][ii-1]) : 0.0;
					dist_across_seg += dist_inc;
					S->data[SEG_DIST][ii] = dist_across_seg;	/* Store distances across the profile */
					if (ii) S->data[SEG_AZIM][ii] = gmt_az_backaz (GMT, S->data[GMT_X][ii-1], S->data[GMT_Y][ii-1], S->data[GMT_X][ii], S->data[GMT_Y][ii], false);
				}
				S->data[SEG_AZIM][0] = gmt_az_backaz (GMT, S->data[GMT_X][0], S->data[GMT_Y][0], S->data[GMT_X][1], S->data[GMT_Y][1], false);	/* Special deal for first point */
				S->n_rows = ii;
				/* Reset distance origin for cross profile */

				d_shift = S->data[SEG_DIST][n_half_cross];	/* d_shift is here the distance at the center point (i.e., where crossing the guide FZ) */
				for (ii = 0; ii < np_cross; ii++) S->data[SEG_DIST][ii] -= d_shift;	/* We reset the origin for distances to where this profile crosses the trial FZ */

				orientation = 0.5 * fmod (2.0 * (Tin->segment[seg]->data[SEG_AZIM][row]+90.0), 360.0);	/* Orientation of cross-profile at zero distance */
				if (orientation > 90.0) orientation -= 180.0;
				ID[0] = seg_name[0] = 0;
				if (Tin->segment[seg]->label) {	/* Use old segment label and append crossprofile number */
					snprintf (ID, GMT_BUFSIZ, "%s-%*.*" PRIu64, Tin->segment[seg]->label, ndig, ndig, row);
				}
				else if (Tin->segment[seg]->header) {	/* Look for label in header */
					gmt_parse_segment_item (GMT, Tin->segment[seg]->header, "-L", seg_name);
					if (seg_name[0]) snprintf (ID, GMT_BUFSIZ, "%s-%*.*" PRIu64, seg_name, ndig, ndig, row);
				}
				if (!ID[0]) {	/* Must assign a label from running numbers */
					if (skip_seg_no)	/* Single track, just list cross-profile no */
						snprintf (ID, GMT_BUFSIZ, "%*.*" PRIu64, ndig, ndig, row);
					else	/* Segment number and cross-profile no */
						snprintf (ID, GMT_BUFSIZ, "%*.*" PRIu64 "-%*.*" PRIu64, sdig, sdig, seg_no, ndig, ndig, row);
				}
				S->label = strdup (ID);
				if (strchr (ID, ' ')) {	/* Has spaces */
					char tmp[GMT_BUFSIZ] = {""};
					snprintf (tmp, GMT_BUFSIZ, "\"%s\"", ID);
					strcpy (ID, tmp);
				}
				snprintf (buffer, GMT_BUFSIZ, "Cross profile number -L%s at %8.3f/%07.3f az=%05.1f",
					ID, Tin->segment[seg]->data[GMT_X][row], Tin->segment[seg]->data[GMT_Y][row], orientation);
				S->header = strdup (buffer);

				if (n_x_seg == n_x_seg_alloc) {
					size_t old_n_x_seg_alloc = n_x_seg_alloc;
					Tout->segment = gmt_M_memory (GMT, Tout->segment, (n_x_seg_alloc += GMT_SMALL_CHUNK), struct GMT_DATASEGMENT *);
					gmt_M_memset (&(Tout->segment[old_n_x_seg_alloc]), n_x_seg_alloc - old_n_x_seg_alloc, struct GMT_DATASEGMENT *);	/* Set to NULL */
				}
				Tout->segment[n_x_seg++] = S;
				Tout->n_segments++;	Xout->n_segments++;
				Tout->n_records += np_cross;	Xout->n_records += np_cross;
			}
		}
	}

	return (Xout);
}

/*! . */
GMT_LOCAL struct GMT_DATASET * gmtsupport_crosstracks_cartesian (struct GMT_CTRL *GMT, struct GMT_DATASET *Din, double cross_length, double across_ds, double deviation, uint64_t n_cols, unsigned int mode, char unit) {
	/* Din is a data set with at least two columns (x,y);
	 * it can contain any number of tables and segments.
	 * cross_length is the desired length of cross-profiles, in Cartesian units.
	 * across_ds is the sampling interval to use along the cross-profiles.
	 * n_cols sets how many data columns beyond x,y,d should be allocated.
	 * Dout is the new data set with all the crossing profiles;
	*/

	bool set_fixed_azim = false;

	int k, ndig, sdig, n_half_cross, k_start, k_stop;

	unsigned int ii, np_cross;

	uint64_t tbl, row, seg, seg_no, n_tot_cols;

	uint64_t dim[GMT_DIM_SIZE] = {0, 0, 0, 0};
	size_t n_x_seg = 0, n_x_seg_alloc = 0;

	char buffer[GMT_BUFSIZ] = {""}, seg_name[GMT_BUFSIZ] = {""}, ID[GMT_BUFSIZ] = {""};

	double dist_across_seg, orientation, sign = 1, az_cross, x, y, sa, ca;

	struct GMT_DATASET *Xout = NULL;
	struct GMT_DATATABLE *Tin = NULL, *Tout = NULL;
	struct GMT_DATASEGMENT *S = NULL;
	gmt_M_unused (unit);	/* For now */

	if (Din->n_columns < 2) {	/* Trouble */
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Dataset does not have at least 2 columns with coordinates\n");
		return (NULL);
	}

	if (mode & GMT_ALTERNATE) sign = -1.0;	/* Survey mode */
	if (mode & GMT_FIXED_AZIM) {	/* Got fixed azimuth */
		az_cross = deviation;
		deviation = 0.0;	/* To prevent any deviation below */
		set_fixed_azim = true;
	}

	/* Get resampling step size and zone width in degrees */

	cross_length *= 0.5;					/* Now half-length in user's units */
	n_half_cross = irint (cross_length / across_ds);	/* Half-width of points in a cross profile */
	across_ds = cross_length / n_half_cross;		/* Exact increment (recalculated in case of roundoff) */
	n_tot_cols = 4 + n_cols;				/* Total number of columns in the resulting data set */
	k_start = -n_half_cross;
	k_stop = n_half_cross;
	if (mode & GMT_RIGHT_ONLY)	/* Only want left side of profiles */
		k_stop = 0;
	else if (mode & GMT_LEFT_ONLY)	/* Only want right side of profiles */
		k_start = 0;
	np_cross = k_stop - k_start + 1;			/* Total cross-profile length */
	dim[GMT_TBL] = Din->n_tables;	dim[GMT_COL] = n_tot_cols;	dim[GMT_ROW] = np_cross;
	if ((Xout = GMT_Create_Data (GMT->parent, GMT_IS_DATASET, GMT_IS_LINE, 0, dim, NULL, NULL, 0, 0, NULL)) == NULL) return (NULL);	/* An empty dataset of n_tot_cols columns and np_cross rows */
	sdig = irint (floor (log10 ((double)Din->n_segments))) + 1;	/* Determine how many decimals are needed for largest segment id */

	for (tbl = seg_no = 0; tbl < Din->n_tables; tbl++) {	/* Process all tables */
		Tin  = Din->table[tbl];
		Tout = Xout->table[tbl];
		for (seg = 0; seg < Tin->n_segments; seg++, seg_no++) {	/* Process all segments */

			ndig = irint (floor (log10 ((double)Tin->segment[seg]->n_rows))) + 1;	/* Determine how many decimals are needed for largest id */

			GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Process Segment %s [segment %" PRIu64 "] which has %" PRIu64 " crossing profiles\n", Tin->segment[seg]->label, seg, Tin->segment[seg]->n_rows);

			for (row = 0; row < Tin->segment[seg]->n_rows; row++) {	/* Process each point along segment */
				/* Compute segment line orientation (-90/90) from azimuths */
				orientation = 0.5 * fmod (2.0 * Tin->segment[seg]->data[SEG_AZIM][row], 360.0);
				if (orientation > 90.0) orientation -= 180.0;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Working on cross profile %" PRIu64 " [local line orientation = %06.1f]\n", row, orientation);

				x = Tin->segment[seg]->data[GMT_X][row];	y = Tin->segment[seg]->data[GMT_Y][row];	/* Reset since now we want lon/lat regardless of grid format */
				if (!set_fixed_azim) az_cross = fmod (Tin->segment[seg]->data[SEG_AZIM][row] + 270.0, 360.0);	/* Azimuth of cross-profile in 0-360 range */
				if (mode & GMT_ALTERNATE)
					sign = -sign;
				else if (mode & GMT_EW_SN)
					sign = (az_cross >= 315.0 || az_cross < 135.0) ? -1.0 : 1.0;	/* We want profiles to be either ~E-W or ~S-N */
				S = GMT_Alloc_Segment (GMT->parent, GMT_NO_STRINGS, np_cross, n_tot_cols, NULL, NULL);
				sincosdegree (90.0 - az_cross - deviation, &sa, &ca);	/* Trig on the direction */
				for (k = k_start, ii = 0; k <= k_stop; k++, ii++) {	/* For each point along normal to FZ */
					dist_across_seg = sign * k * across_ds;		/* The current distance along this profile */
					S->data[GMT_X][ii] = x + dist_across_seg * ca;
					S->data[GMT_Y][ii] = y + dist_across_seg * sa;
					S->data[SEG_DIST][ii] = dist_across_seg;	/* Store distances across the profile */
					if (ii) S->data[SEG_AZIM][ii] = gmt_az_backaz (GMT, S->data[GMT_X][ii-1], S->data[GMT_Y][ii-1], S->data[GMT_X][ii], S->data[GMT_Y][ii], false);
				}
				S->data[SEG_AZIM][0] = gmt_az_backaz (GMT, S->data[GMT_X][0], S->data[GMT_Y][0], S->data[GMT_X][1], S->data[GMT_Y][1], false);	/* Special deal for first point */

				orientation = 0.5 * fmod (2.0 * (Tin->segment[seg]->data[SEG_AZIM][row]+90.0), 360.0);	/* Orientation of cross-profile at zero distance */
				if (orientation > 90.0) orientation -= 180.0;
				ID[0] = seg_name[0] = 0;
				if (Tin->segment[seg]->label) {	/* Use old segment label and append crossprofile number */
					snprintf (ID, GMT_BUFSIZ, "%s-%*.*" PRIu64, Tin->segment[seg]->label, ndig, ndig, row);
				}
				else if (Tin->segment[seg]->header) {	/* Look for label in header */
					gmt_parse_segment_item (GMT, Tin->segment[seg]->header, "-L", seg_name);
					if (seg_name[0]) snprintf (ID, GMT_BUFSIZ, "%s-%*.*" PRIu64, seg_name, ndig, ndig, row);
				}
				if (!ID[0]) {	/* Must assign a label from running numbers */
					if (Tin->n_segments == 1 && Din->n_tables == 1)	/* Single track, just list cross-profile no */
						snprintf (ID, GMT_BUFSIZ, "%*.*" PRIu64, ndig, ndig, row);
					else	/* Segment number and cross-profile no */
						snprintf (ID, GMT_BUFSIZ, "%*.*" PRIu64 "%*.*" PRIu64, sdig, sdig, seg_no, ndig, ndig, row);
				}
				S->label = strdup (ID);
				snprintf (buffer, GMT_BUFSIZ, "Cross profile number -L\"%s\" at %g/%g az=%05.1f",
					ID, Tin->segment[seg]->data[GMT_X][row], Tin->segment[seg]->data[GMT_Y][row], orientation);
				S->header = strdup (buffer);

				if (n_x_seg == n_x_seg_alloc) {
					size_t old_n_x_seg_alloc = n_x_seg_alloc;
					Tout->segment = gmt_M_memory (GMT, Tout->segment, (n_x_seg_alloc += GMT_SMALL_CHUNK), struct GMT_DATASEGMENT *);
					gmt_M_memset (&(Tout->segment[old_n_x_seg_alloc]), n_x_seg_alloc - old_n_x_seg_alloc, struct GMT_DATASEGMENT *);	/* Set to NULL */
				}
				Tout->segment[n_x_seg++] = S;
				Tout->n_segments++;	Xout->n_segments++;
				Tout->n_records += np_cross;	Xout->n_records += np_cross;
			}
		}
	}

	return (Xout);
}

/*! . */
GMT_LOCAL bool gmtsupport_straddle_dateline (double x0, double x1) {
	if (fabs (x0 - x1) > 90.0) return (false);	/* Probably Greenwhich crossing with 0/360 discontinuity */
	if ((x0 < 180.0 && x1 > 180.0) || (x0 > 180.0 && x1 < 180.0)) return (true);	/* Crossed Dateline */
	return (false);
}

/*! . */
GMT_LOCAL double gmtsupport_guess_surface_time (struct GMT_CTRL *GMT, unsigned int factors[], unsigned int n_columns, unsigned int n_rows) {
	/* Routine to guess a number proportional to the operations
	 * required by surface working on a user-desired grid of
	 * size n_columns by n_rows, where n_columns = (x_max - x_min)/dx, and same for
	 * n_rows.  (That is, one less than actually used in routine.)
	 *
	 * This is based on the following untested conjecture:
	 * 	The operations are proportional to T = nxg*nyg*L,
	 *	where L is a measure of the distance that data
	 *	constraints must propagate, and nxg, nyg are the
	 * 	current size of the grid.
	 *	For n_columns,n_rows relatively prime, we will go through only
	 * 	one grid cycle, L = max(n_columns,n_rows), and T = n_columns*n_rows*L.
	 *	But for n_columns,n_rows whose greatest common divisor is a highly
	 * 	composite number, we will have L equal to the division
	 * 	step made at each new grid cycle, and nxg,nyg will
	 * 	also be smaller than n_columns,n_rows.  Thus we can hope to find
	 *	some n_columns,n_rows for which the total value of T is C->small.
	 *
	 * The above is pure speculation and has not been derived
	 * empirically.  In actual practice, the distribution of the
	 * data, both spatially and in terms of their values, will
	 * have a strong effect on convergence.
	 *
	 * W. H. F. Smith, 26 Feb 1992.  */

	unsigned int gcd;		/* Current value of the gcd  */
	unsigned int nxg, nyg;	/* Current value of the grid dimensions  */
	unsigned int nfactors = 0;	/* Number of prime factors of current gcd  */
	unsigned int factor;	/* Currently used factor  */
	/* Doubles are used below, even though the values will be integers,
		because the multiplications might reach sizes of O(n**3)  */
	double t_sum;		/* Sum of values of T at each grid cycle  */
	double length;		/* Current propagation distance.  */

	gcd = gmt_gcd_euclid (n_columns, n_rows);
	if (gcd > 1) {
		nfactors = gmt_get_prime_factors (GMT, gcd, factors);
		nxg = n_columns/gcd;
		nyg = n_rows/gcd;
		if (nxg < 3 || nyg < 3) {
			factor = factors[nfactors - 1];
			nfactors--;
			gcd /= factor;
			nxg *= factor;
			nyg *= factor;
		}
	}
	else {
		nxg = n_columns;
		nyg = n_rows;
	}
	length = (double)MAX(nxg, nyg);
	t_sum = nxg * (nyg * length);	/* Make it double at each multiply  */

	/* Are there more grid cycles ?  */
	while (gcd > 1) {
		factor = factors[nfactors - 1];
		nfactors--;
		gcd /= factor;
		nxg *= factor;
		nyg *= factor;
		length = (double)factor;
		t_sum += nxg * (nyg * length);
	}
	return (t_sum);
}

/*! . */
GMT_LOCAL int gmtsupport_compare_sugs (const void *point_1, const void *point_2) {
	/* Sorts sugs into DESCENDING order!  */
	if (((struct GMT_SURFACE_SUGGESTION *)point_1)->factor < ((struct GMT_SURFACE_SUGGESTION *)point_2)->factor) return (1);
	if (((struct GMT_SURFACE_SUGGESTION *)point_1)->factor > ((struct GMT_SURFACE_SUGGESTION *)point_2)->factor) return(-1);
	return (0);
}

/*! . */
uint64_t gmt_read_list (struct GMT_CTRL *GMT, char *file, char ***list) {
	/* Reads a file with one string per line. Returns number of strings an
	 * allocated pointer to the array */
	uint64_t n = 0;
	size_t n_alloc = GMT_CHUNK;
	char **p = NULL, line[GMT_BUFSIZ] = {""};
	FILE *fp = NULL;

	if ((fp = gmt_fopen (GMT, file, "r")) == NULL) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Cannot find/open list file %s\n", file);
		return (0);
	}

	if ((p = gmt_M_memory (GMT, NULL, n_alloc, char *)) == NULL) return (0);

	while (fgets (line, GMT_BUFSIZ, fp)) {
		gmt_chop (line);	/* Remove trailing CR or LF */
		p[n++] = strdup (line);
		if (n == n_alloc) p = gmt_M_memory (GMT, p, n_alloc <<= 1, char *);
	}
	gmt_fclose (GMT, fp);
	if (n > 0)
		*list = gmt_M_memory (GMT, p, n, char *);
	else {
		gmt_M_free (GMT, p);
		*list = NULL;
	}

	return (n);
}

/*! . */
GMT_LOCAL int gmtsupport_sort_order_descend (const void *p_1, const void *p_2) {
	/* Returns -1 if point_1 is < that point_2,
	   +1 if point_2 > point_1, and 0 if they are equal
	*/
	bool bad_1, bad_2;
	const struct GMT_ORDER *point_1 = p_1, *point_2 = p_2;

	bad_1 = gmt_M_is_dnan (point_1->value);
	bad_2 = gmt_M_is_dnan (point_2->value);

	if (bad_1 && bad_2) return (0);
	if (bad_1) return (+1);
	if (bad_2) return (-1);

	if (point_1->value > point_2->value) return (-1);
	if (point_1->value < point_2->value) return (+1);
	return (0);
}

/*! . */
GMT_LOCAL int gmtsupport_sort_order_ascend (const void *p_1, const void *p_2) {
	/* Returns -1 if point_1 is < that point_2,
	   +1 if point_2 > point_1, and 0 if they are equal
	*/
	bool bad_1, bad_2;
	const struct GMT_ORDER *point_1 = p_1, *point_2 = p_2;

	bad_1 = gmt_M_is_dnan (point_1->value);
	bad_2 = gmt_M_is_dnan (point_2->value);

	if (bad_1 && bad_2) return (0);
	if (bad_1) return (+1);
	if (bad_2) return (-1);

	if (point_1->value < point_2->value) return (-1);
	if (point_1->value > point_2->value) return (+1);
	return (0);
}

/*! . */
void gmt_free_list (struct GMT_CTRL *GMT, char **list, uint64_t n) {
	/* Properly free memory allocated by gmt_read_list */
	uint64_t i;
	if (n == 0) return;	/* Nothing to do here */
	for (i = 0; i < n; i++) gmt_M_str_free (list[i]);
	gmt_M_free (GMT, list);
}

#ifndef WIN32
/*! . */
GMT_LOCAL int gmtsupport_globerr (const char *path, int eerrno) {
	fprintf (stderr, "gmtlib_glob_list: %s: %s\n", path, strerror(eerrno));
	return 0;	/* let glob() keep going */
}
#else
/* Build our own glob for Windows, using tips and code from
   http://www.thecodingforums.com/threads/globing-on-windows-in-c-c-language.739310/

  match a character.
  Parmas: target - target string, pat - pattern string.
  Returns: number of pat character matched.
  Notes: means that a * in pat will return zero
*/
static int gmtsupport_chmatch (const char *target, const char *pat) {
	char *end = NULL, *ptr = NULL;
	if (*pat == '[' && (end = strchr (pat, ']')) ) {
		/* treat close bracket following open bracket as character */
		if (end == pat + 1) {
			end = strchr (pat+2, ']');
			/* make "[]" with no close mismatch all */
			if (end == 0) return 0;
		}
		/* allow [A-Z] and like syntax */
		if (end - pat == 4 && pat[2] == '-' && pat[1] <= pat[3]) {
			if(*target >= pat[1] && *target <= pat[3])
				return 5;
			else
				return 0;
		}

		/* search for character list contained within brackets */
		ptr = strchr (pat+1, *target);
		if (ptr != 0 && ptr < end)
			return (int)(end - pat + 1);
		else
			return 0;
	}
	if (*pat == '?' && *target != 0)return 1;
	if (*pat == '*') return 0;
	if (*target == 0 || *pat == 0)return 0;
	if (*target == *pat) return 1;
	return 0;
}
/* wildcard matcher.  Params: str - the target string
   pattern - pattern to match
   Returns: 1 if match, 0 if not.
   Notes: ? - match any character
   * - match zero or more characters
   [?], [*], escapes,
   [abc], match a, b or c.
   [A-Z] [0-9] [*-x], match range.
   [[] - match '['.
   [][abc] match ], [, a, b or c
*/
GMT_LOCAL int gmtsupport_matchwild (const char *str, const char *pattern) {
	const char *target = str;
	const char *pat = pattern;
	int gobble;

	while( (gobble = gmtsupport_chmatch(target, pat)) ) {
		target++;
		pat += gobble;
	}
	if (*target == 0 && *pat == 0)
		return 1;
	else if (*pat == '*') {
		while (pat[1] == '*') pat++;
		if (pat[1] == 0) return 1;
		while (*target)
			if (gmtsupport_matchwild (target++, pat+1)) return 1;
	}
	return 0;
}
#endif

/*! . */
uint64_t gmtlib_glob_list (struct GMT_CTRL *GMT, const char *pattern, char ***list) {
#ifdef WIN32
	uint64_t k = 0, n = 0;
	size_t n_alloc = GMT_SMALL_CHUNK;
	char **p = NULL, **file = NULL;
	if ((p = gmt_get_dir_list (GMT, ".", NULL)) == NULL) return 0;

	if ((file = gmt_M_memory (GMT, NULL, n_alloc, char *)) == NULL) return 0;

	while (p[k]) {	/* A NULL marks the end for us */
		if (gmtsupport_matchwild (p[k], pattern)) {	/* Found a match */
			file[n++] = strdup (p[k]);
			if (n == n_alloc) {
				n_alloc <<= 1;
				file = gmt_M_memory (GMT, file, n_alloc, char *);
			}
		}
		k++;
	}
	gmt_free_dir_list (GMT, &p);
	if (n < n_alloc) file = gmt_M_memory (GMT, file, n, char *);
	*list = file;
	return n;
}
#else	/* Standard UNIX glob use */
	unsigned int pos = 0, k = 0;
	int ret, flags = 0;
	char **p = NULL, item[GMT_LEN256] = {""};
	glob_t results;

	if (!pattern || pattern[0] == '\0') return 0;	/* Nothing passed */

	while ((gmt_strtok (pattern, " \t", &pos, item))) {	/* For all separate arguments */
		flags |= (k > 1 ? GLOB_APPEND : 0);
		ret = glob (item, flags, gmtsupport_globerr, &results);
		if (ret != 0 && ret != GLOB_NOMATCH) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "gmtlib_glob_list: problem with wildcard expansion of (%s), stopping early [%s]\n",
				item,
		/* ugly: */	(ret == GLOB_ABORTED ? "filesystem problem" :
				 ret == GLOB_NOMATCH ? "no match of pattern" :
				 ret == GLOB_NOSPACE ? "no dynamic memory" :
				 "unknown problem"));
			break;
		}
		k++;
	}

	if (results.gl_pathc) p = gmt_M_memory (GMT, NULL, results.gl_pathc, char *);
	for (k = 0; k < results.gl_pathc; k++)
		p[k] = strdup (results.gl_pathv[k]);

	globfree (&results);

	*list = p;
	return (uint64_t)results.gl_pathc;
}
#endif

GMT_LOCAL int gmtsupport_find_mod_syntax_start (char *arg, int k) {
	/* Either arg[n] == '+' or not found so arg[n] == 0 */
	bool look = true;
	int n = k;
	while (look && arg[n]) {
		if (arg[n] == '+' && islower (arg[n+1])) look = false;
		else n++;
	}
	return n;
}

/* There are many tools which requires grid x/y or cpt z to be in meters but the user may have these
 * data in km or miles.  Appending +u<unit> to the file addresses this conversion. */

/*! . */
char *gmtlib_cptfile_unitscale (struct GMTAPI_CTRL *API, char *name) {
	/* Determine if this file ends in +u|U<unit>, with <unit> one of the valid Cartesian distance units */
	char *c = NULL, *f = NULL;
	size_t len = strlen (name);	/* Get length of the file name */
	if (len < 4) return NULL;	/* Not enough space for name and modifier */
	if ((f = gmt_strrstr (name, GMT_CPT_EXTENSION)))
		c = gmtlib_last_valid_file_modifier (API, f, "uU");
	else
		c = gmtlib_last_valid_file_modifier (API, name, "uU");
	if (c == NULL) return NULL;	/* No modifiers */
	if (c && (f = strstr (c, "+u")) == NULL && (f = strstr (c, "+U")) == NULL) return NULL;	/* No +u or +U modifier */
	if (strchr (GMT_LEN_UNITS2, f[2]) == NULL) return NULL;		/* Does no have a valid unit at the end */
	return f;	/* Return valid modifier */
}

/*! . */
/* Used externally, e.g. GSFML */
int gmtlib_detrend (struct GMT_CTRL *GMT, double *x, double *y, uint64_t n, double increment, double *intercept, double *slope, int mode) {
	/* Deals with linear trend in a dataset, depending on mode:
	 * -1: Determine trend, and remove it from x,y. Return slope and intercept
	 * 0 : Just determine trend. Return slope and intercept
	 * +1: Restore trend in x,y based on given slope/intercept.
	 * (x,y) is the data.  If x == NULL then data is equidistant with increment as the spacing.
	 */
	uint64_t i;
	bool equidistant;
	double xx;

	equidistant = (x == NULL);	/* If there are no x-values we assume dx is passed via intercept */
	if (mode < 1) {	/* Must determine trend */
		uint64_t m = 0;
		double sum_x = 0.0, sum_xx = 0.0, sum_y = 0.0, sum_xy = 0.0;
		for (i = 0; i < n; i++) {
			if (gmt_M_is_dnan (y[i])) continue;
			xx = (equidistant) ? increment*i : x[i];
			sum_x  += xx;
			sum_xx += xx*xx;
			sum_y  += y[i];
			sum_xy += xx*y[i];
			m++;
		}
		*intercept = *slope = 0.0;
		if (m == 0) {	/* No points passed the NaN test */
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "called with no valid points, return NaNs\n");
			*intercept = (m) ? sum_y : GMT->session.d_NaN;	/* Value of single y-point or NaN */
			*slope = GMT->session.d_NaN;

		}
		else if (m == 1) {	/* Ain't fitting a line to one point no more */
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "called with 1 point, return NaNs\n");
			*intercept = (m) ? sum_y : GMT->session.d_NaN;	/* Value of single y-point or NaN */
			*slope = GMT->session.d_NaN;
		}
		else {	/* Got enough points to compute the trend */
			double denom = m * sum_xx - sum_x * sum_x;
			*intercept = (sum_y * sum_xx - sum_x * sum_xy) / denom;
			*slope     = (m * sum_xy - sum_x * sum_y)      / denom;
		}
	}

	if (mode) {	/* Either remove or restore trend from/to the data */
		if (gmt_M_is_dnan (*slope)) {
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "called with slope = NaN - skipped\n");
			return (-1);
		}
		if (gmt_M_is_dnan (*intercept)) {
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "called with intercept = NaN - skipped\n");
			return (-1);
		}
		for (i = 0; i < n; i++) {
			xx = (equidistant) ? increment*i : x[i];
			y[i] += (mode * (*intercept + (*slope) * xx));
		}
	}
	return (GMT_NOERROR);
}

/*! . */
bool gmt_is_fill (struct GMT_CTRL *GMT, char *word) {
	/* Return true if argument is an image fill or color or no fill (-) */
	if (!strcmp (word,"-")) return true;	/* Or skip */
	if (gmtsupport_is_pattern (GMT, word)) return true;
	if (gmtlib_is_color (GMT, word)) return true;
	return false;
}

//#define gmt_is_fill(GMT,word) (!strcmp(word,"-") || gmtsupport_is_pattern (GMT,word) || gmtlib_is_color (GMT, word))

/* The two flip_angle functions are needed when vectors given by angle/length is to be plotted
 * using Cartesian projections in which the direction of positive x and/or y-axis might have
 * been reversed.  Thus we flip the vector angle accordingly.
 */

/*! . */
void gmt_flip_azim_d (struct GMT_CTRL *GMT, double *azim) {
	/* Adjust an azimuth for Cartesian axes pointing backwards/downwards */
	if (GMT->current.proj.projection_GMT != GMT_LINEAR) return;	/* This only applies to Cartesian scaling */
	/* Must check if negative scales were used */
	if (!GMT->current.proj.xyz_pos[GMT_X]) {	/* Negative x scale */
		if (!GMT->current.proj.xyz_pos[GMT_Y])	/* Negative y-scale too */
			*azim += 180.0;
		else
			*azim = -*azim;
	}
	else if (!GMT->current.proj.xyz_pos[GMT_Y])	/* Negative y-scale only */
		*azim = 180.0 - (*azim);
}

/*! . */
void gmt_flip_angle_d (struct GMT_CTRL *GMT, double *angle) {
	/* Adjust an angle for Cartesian axes pointing backwards/downwards */
	if (GMT->current.proj.projection_GMT != GMT_LINEAR) return;	/* This only applies to Cartesian scaling */
	/* Must check if negative scales were used */
	if (!GMT->current.proj.xyz_pos[GMT_X]) {	/* Negative x scale */
		if (!GMT->current.proj.xyz_pos[GMT_Y])	/* Negative y-scale too */
			*angle += 180.0;
		else
			*angle = 180.0 - (*angle);
	}
	else if (!GMT->current.proj.xyz_pos[GMT_Y])	/* Negative y-scale only */
		*angle = -*angle;
}

/*! . */
unsigned int gmt_get_prime_factors (struct GMT_CTRL *GMT, uint64_t n, unsigned int *f) {
	/* Fills the integer array f with the prime factors of n.
	 * Returns the number of locations filled in f, which is
	 * one if n is prime.
	 *
	 * f[] should have been malloc'ed to enough space before
	 * calling prime_factors().  We can be certain that f[32]
	 * is enough space, for if n fits in a long, then n < 2**32,
	 * and so it must have fewer than 32 prime factors.  I think
	 * that in general, ceil(log2((double)n)) is enough storage
	 * space for f[].
	 *
	 * Tries 2,3,5 explicitly; then alternately adds 2 or 4
	 * to the previously tried factor to obtain the next trial
	 * factor.  This is done with the variable two_four_toggle.
	 * With this method we try 7,11,13,17,19,23,25,29,31,35,...
	 * up to a maximum of sqrt(n).  This shortened list results
	 * in 1/3 fewer divisions than if we simply tried all integers
	 * between 5 and sqrt(n).  We can reduce the size of the list
	 * of trials by an additional 20% by removing the multiples
	 * of 5, which are equal to 30m +/- 5, where m >= 1.  Starting
	 * from 25, these are found by alternately adding 10 or 20.
	 * To do this, we use the variable ten_twenty_toggle.
	 *
	 * W. H. F. Smith, 26 Feb 1992, after D.E. Knuth, vol. II  */

	unsigned int current_factor = 0;	/* The factor currently being tried  */
	unsigned int max_factor;		/* Don't try any factors bigger than this  */
	unsigned int n_factors = 0;		/* Returned; one if n is prime  */
	unsigned int two_four_toggle = 0;	/* Used to add 2 or 4 to get next trial factor  */
	unsigned int ten_twenty_toggle = 0;	/* Used to add 10 or 20 to skip_five  */
	unsigned int skip_five = 25;	/* Used to skip multiples of 5 in the list  */
	unsigned int base_factor[3] = {2, 3, 5};	/* Standard factors to try */
	uint64_t m = n;			/* Used to keep a working copy of n  */
	unsigned int k;			/* counter */
	gmt_M_unused(GMT);

	/* Initialize max_factor  */

	if (m < 2) return (0);
	max_factor = urint (floor(sqrt((double)m)));

	/* First find the 2s, 3s, and 5s */
	for (k = 0; k < 3; k++) {
		current_factor = base_factor[k];
		while (!(m % current_factor)) {
			m /= current_factor;
			f[n_factors++] = current_factor;
		}
		if (m == 1) return (n_factors);
	}

	/* Unless we have already returned we now try all the rest  */

	while (m > 1 && current_factor <= max_factor) {

		/* Current factor is either 2 or 4 more than previous value  */

		if (two_four_toggle) {
			current_factor += 4;
			two_four_toggle = 0;
		}
		else {
			current_factor += 2;
			two_four_toggle = 1;
		}

		/* If current factor is a multiple of 5, skip it.  But first,
			set next value of skip_five according to 10/20 toggle:  */

		if (current_factor == skip_five) {
			if (ten_twenty_toggle) {
				skip_five += 20;
				ten_twenty_toggle = 0;
			}
			else {
				skip_five += 10;
				ten_twenty_toggle = 1;
			}
			continue;
		}

		/* Get here when current_factor is not a multiple of 2,3 or 5:  */

		while (!(m % current_factor)) {
			m /= current_factor;
			f[n_factors++] = current_factor;
		}
	}

	/* Get here when all factors up to floor(sqrt(n)) have been tried.  */

	if (m > 1) f[n_factors++] = (unsigned int)m;	/* m is an additional prime factor of n  */

	return (n_factors);
}

/*! . */
void gmt_sort_array (struct GMT_CTRL *GMT, void *base, uint64_t n, unsigned int type) {
	/* Front function to call qsort on all <type> array into ascending order */
	size_t width[GMT_N_TYPES] = {
		sizeof(uint8_t),      /* GMT_UCHAR */
		sizeof(int8_t),       /* GMT_CHAR */
		sizeof(uint16_t),     /* GMT_USHORT */
		sizeof(int16_t),      /* GMT_SHORT */
		sizeof(uint32_t),     /* GMT_UINT */
		sizeof(int32_t),      /* GMT_INT */
		sizeof(uint64_t),     /* GMT_ULONG */
		sizeof(int64_t),      /* GMT_LONG */
		sizeof(float),        /* GMT_FLOAT */
		sizeof(double)};      /* GMT_DOUBLE */
	int (*compare[GMT_N_TYPES]) (const void *, const void *) = {
		/* Array of function pointers */
		gmtsupport_comp_uchar_asc,   /* GMT_CHAR */
		gmtsupport_comp_char_asc,    /* GMT_UCHAR */
		gmtsupport_comp_ushort_asc,  /* GMT_USHORT */
		gmtsupport_comp_short_asc,   /* GMT_SHORT */
		gmtsupport_comp_uint_asc,    /* GMT_UINT */
		gmtsupport_comp_int_asc,     /* GMT_INT */
		gmtsupport_comp_ulong_asc,   /* GMT_ULONG */
		gmtsupport_comp_long_asc,    /* GMT_LONG */
		gmtsupport_comp_float_asc,   /* GMT_FLOAT */
		gmtsupport_comp_double_asc}; /* GMT_DOUBLE */
	gmt_M_unused(GMT);

	qsort (base, n, width[type], compare[type]);
}

/*! . */
void gmt_sort_order (struct GMT_CTRL *GMT, struct GMT_ORDER *base, uint64_t n, int dir) {
	/* Sort the order array in ascending or descending direction */
	if (dir == -1)
		qsort (base, n, sizeof (struct GMT_ORDER), gmtsupport_sort_order_descend);
	else if (dir == +1)
		qsort (base, n, sizeof (struct GMT_ORDER), gmtsupport_sort_order_ascend);
	else
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "gmt_sort_order: Given illegal direction %d\n", dir);
}

/*! . */
const char * GMT_strerror (int err) {
	/* Returns the error string for a given error code "err"
	 * Passes "err" on to nc_strerror if the error code is not one we defined */
	if (err < 0) return nc_strerror (err);	/* Negative error codes come from netCDF */
	return (gmt_error_string[err]);		/* Other errors are internal GMT errors */
}

/*! . */
int gmt_err_func (struct GMT_CTRL *GMT, int err, bool fail, char *file, const char *where) {
	if (err == GMT_NOERROR) return (err);

	/* When error code is non-zero: print error message */
	if (file && file[0])
		gmtlib_report_func (GMT, GMT_MSG_ERROR, where, "%s [%s]\n", GMT_strerror(err), file);
	else
		gmtlib_report_func (GMT, GMT_MSG_ERROR, where, "%s\n", GMT_strerror(err));
	/* Pass error code on or exit */
	if (fail)
		return GMT_RUNTIME_ERROR;
	else
		return (err);
}

/*! . */
void gmt_init_fill (struct GMT_CTRL *GMT, struct GMT_FILL *fill, double r, double g, double b) {
	/* Initialize FILL structure */

	/* Set whole structure to null (0, 0.0) */
	gmt_M_unused(GMT);
	gmt_M_memset (fill, 1, struct GMT_FILL);
	/* Non-null values: */
	fill->b_rgb[0] = fill->b_rgb[1] = fill->b_rgb[2] = 1.0;
	fill->rgb[0] = r, fill->rgb[1] = g, fill->rgb[2] = b;
}

/*! . */
bool gmt_getfill (struct GMT_CTRL *GMT, char *line, struct GMT_FILL *fill) {
	bool error = false;

	assert (fill);	/* Ffill needs to not point to NULL */
	if (!line) { GMT_Report (GMT->parent, GMT_MSG_ERROR, "No argument given to gmt_getfill\n"); GMT->parent->error = GMT_PARSE_ERROR; return true; }

	/* Syntax:   -G<gray>, -G<rgb>, -G<cmyk>, -G<hsv> or -Gp|P<image>[+b<rgb>][+f<rgb>][+r<dpi>]   */
	/* Note, <rgb> can be r/g/b, gray, or - for masks.  optionally, append @<transparency> [0] */

	gmt_init_fill (GMT, fill, -1.0, -1.0, -1.0);	/* Initialize fill structure */
	gmt_chop (line);	/* Remove trailing CR, LF and properly NULL-terminate the string */
	if (!line[0]) return (false);	/* No argument given: we are out of here */

	if (gmt_M_is_pattern (line))	/* Image specified */
		error = gmtsupport_parse_pattern (GMT, line, fill);
	else	/* Plain color or shade */
		error = gmt_getrgb (GMT, line, fill->rgb);

	return (error);
}

/*! . */
int gmtlib_getrgb_index (struct GMT_CTRL *GMT, double rgb[]) {
	/* Find the index of preset RGB triplets (those with names)
	   Return -1 if none found */

	int i;
	unsigned char irgb[3];
	gmt_M_unused(GMT);

	/* First convert from 0-1 to 0-255 range */
	for (i = 0; i < 3; i++) irgb[i] = gmt_M_u255(rgb[i]);

	/* Compare all RGB codes */
	for (i = 0; i < GMT_N_COLOR_NAMES; i++) {
		if (gmt_M_color_rgb[i][0] == irgb[0] && gmt_M_color_rgb[i][1] == irgb[1] && gmt_M_color_rgb[i][2] == irgb[2]) return (i);
	}

	/* Nothing found */
	return (-1);
}

/*! . */
int gmt_colorname2index (struct GMT_CTRL *GMT, char *name) {
	/* Return index into structure with colornames and r/g/b */

	int k;
	char Lname[GMT_LEN64] = {""};

	strncpy (Lname, name, GMT_LEN64-1);
	gmt_str_tolower (Lname);
	k = gmt_hash_lookup (GMT, Lname, GMT->session.rgb_hashnode, GMT_N_COLOR_NAMES, GMT_N_COLOR_NAMES);

	return (k);
}

/*! . */
bool gmt_getrgb (struct GMT_CTRL *GMT, char *line, double rgb[]) {
	int n, i, count, irgb[3], c = 0;
	double hsv[4], cmyk[5];
	char buffer[GMT_LEN64] = {""}, *t = NULL;

	if (!line) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "No argument given to gmt_getrgb\n");
		GMT->parent->error = GMT_PARSE_ERROR;
		return true;
	}
	if (!line[0]) return (false);	/* Nothing to do - accept default action */

	rgb[3] = hsv[3] = cmyk[4] = 0.0;	/* Default is no transparency */

	strncpy (buffer, line, GMT_LEN64-1);	/* Make local copy */
	if ((t = strstr (buffer, "@")) && strlen (t) > 1) {	/* User requested transparency via @<transparency> */
		double transparency = atof (&t[1]);
		if (transparency < 0.0 || transparency > 100.0)
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "Representation of transparency (%s) not recognized. Using default [0 or opaque].\n", line);
		else
			rgb[3] = hsv[3] = cmyk[4] = transparency / 100.0;	/* Transparency is in 0-1 range */
		t[0] = '\0';	/* Chop off transparency for the rest of this function */
	}

	if (strstr (buffer, "auto")) {	/* Will select sequential colors from a list - flag via -5 or -6 */
		/* Let auto[-segment] be GMT_COLOR_AUTO_SEGMENT and auto-table be GMT_COLOR_AUTO_TABLE */
		if (strstr (buffer, "table"))
			rgb[0] = rgb[1] = rgb[2] = GMT_COLOR_AUTO_TABLE - 7;
		else
			rgb[0] = rgb[1] = rgb[2] = GMT_COLOR_AUTO_SEGMENT - 7;
		return (false);
	}

	if (buffer[0] == '-') {
		rgb[0] = rgb[1] = rgb[2] = -1.0;
		return (false);
	}

	if (buffer[0] == '#') {	/* #rrggbb */
		n = sscanf (buffer, "#%2x%2x%2x", (unsigned int *)&irgb[0], (unsigned int *)&irgb[1], (unsigned int *)&irgb[2]);
		return (n != 3 || gmtsupport_check_irgb (irgb, rgb));
	}

	/* If it starts with a letter, then it could be a name */

	if (isalpha ((unsigned char) buffer[0])) {
		if ((n = (int)gmt_colorname2index (GMT, buffer)) < 0) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Colorname %s not recognized!\n", buffer);
			return (true);
		}
		for (i = 0; i < 3; i++) rgb[i] = gmt_M_is255 (gmt_M_color_rgb[n][i]);
		return (false);
	}

	/* Definitely wrong, at this point, is something that does not end in a number */

	if (strlen(buffer) < 1) return (true);	/* Nothing, which is bad */
	c = buffer[strlen(buffer)-1];
	if (c <= 0 || !(isdigit (c) || c == '.')) return (true);

	count = (int)gmt_char_count (buffer, '/');

	if (count == 3) {	/* c/m/y/k */
		n = sscanf (buffer, "%lf/%lf/%lf/%lf", &cmyk[0], &cmyk[1], &cmyk[2], &cmyk[3]);
		if (n != 4 || gmtsupport_check_cmyk (cmyk)) return (true);
		gmtsupport_cmyk_to_rgb (rgb, cmyk);
		return (false);
	}

	if (count == 2) {	/* r/g/b */
		n = sscanf (buffer, "%lf/%lf/%lf", &rgb[0], &rgb[1], &rgb[2]);
		rgb[0] /= 255.0 ; rgb[1] /= 255.0 ; rgb[2] /= 255.0;
		return (n != 3 || gmtsupport_check_rgb (rgb));
	}

	if (gmt_char_count (buffer, '-') == 2) {	/* h-s-v despite pretending to be r/g/b */
		n = sscanf (buffer, "%lf-%lf-%lf", &hsv[0], &hsv[1], &hsv[2]);
		if (n != 3 || gmtsupport_check_hsv (hsv)) return (true);
		gmt_hsv_to_rgb (rgb, hsv);
		return (false);
	}

	if (count == 0) {	/* gray */
		n = sscanf (buffer, "%lf", &rgb[0]);
		rgb[0] /= 255.0 ; rgb[1] = rgb[2] = rgb[0];
		return (n != 1 || gmtsupport_check_rgb (rgb));
	}

	/* Get here if there is a problem */

	return (true);
}

/*! . */
void gmtlib_enforce_rgb_triplets (struct GMT_CTRL *GMT, char *text, unsigned int size) {
	/* Purpose is to replace things like @;lightgreen; with @r/g/b; which PSL_plottext understands.
	 * Likewise, if @transparency is appended we change it to =transparency so PSL_plottext can parse it */

	unsigned int i, j, k = 0, n, last = 0, n_slash;
	double rgb[4];
	char buffer[GMT_BUFSIZ] = {""}, color[GMT_LEN256] = {""}, *p = NULL;

	if (!strchr (text, '@')) return;	/* Nothing to do since no escape sequence in string */

	while ((p = strstr (text, "@;"))) {	/* Found a @; sequence */
		i = (unsigned int)(p - text) + 2;	/* Position of first character after @; */
		for (j = last; j < i; j++, k++) buffer[k] = text[j];	/* Copy everything from last stop up to the color specification */
		text[i-1] = 'X';	/* Wipe the ; so that @; won't be found a 2nd time */
		if (text[i] != ';') {	/* Color info now follows */
			n = i;
			n_slash = 0;
			while (text[n] && text[n] != ';') {	/* Find end of the color info and also count slashes */
				if (text[n] == '/') n_slash++;
				n++;
			}
			if (n_slash != 2) {	/* r/g/b not given, must replace whatever it was with a r/g/b triplet */
				text[n] = '\0';	/* Temporarily terminate string so getrgb can work */
				if (gmt_getrgb (GMT, &text[i], rgb))
					GMT_Report (GMT->parent, GMT_MSG_WARNING, "Failed to convert %s to r/g/b\n", &text[i]);
				text[n] = ';';	/* Undo damage */
				if (rgb[3] > 0.0)	/* Asked for transparency as well */
					snprintf (color, GMT_LEN256, "%f/%f/%f=%ld", gmt_M_t255(rgb,0), gmt_M_t255(rgb,1), gmt_M_t255(rgb,2), lrint (100.0 * rgb[3]));	/* Format triplet w/ transparency */
				else
					snprintf (color, GMT_LEN256, "%f/%f/%f", gmt_M_t255(rgb,0), gmt_M_t255(rgb,1), gmt_M_t255(rgb,2));	/* Format triplet only */
				for (j = 0; color[j]; j++, k++) buffer[k] = color[j];	/* Copy over triplet and update buffer pointer k */
			}
			else	/* Already in r/g/b format, just copy */
				for (j = i; j < n; j++, k++) buffer[k] = text[j];
			i = n;	/* Position of terminating ; */
		}
		buffer[k++] = ';';	/* Finish the specification */
		last = i + 1;	/* Start of next part to copy */
	}
	i = last;	/* Finish copying everything left in the text string */
	while (text[i]) buffer[k++] = text[i++];
	buffer[k++] = '\0';	/* Properly terminate buffer */

	if (k > size) GMT_Report (GMT->parent, GMT_MSG_WARNING, "Replacement string too long - truncated\n");
	strncpy (text, buffer, k);	/* Copy back the revised string */
}

/*! . */
int gmt_getfont (struct GMT_CTRL *GMT, char *buffer, struct GMT_FONT *F) {
	unsigned int i, n;
	int k;
	double pointsize;
	char size[GMT_LEN256] = {""}, name[GMT_LEN256] = {""}, fill[GMT_LEN256] = {""}, line[GMT_BUFSIZ] = {""}, *s = NULL;

	if (!buffer || !buffer[0]) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "No argument given to gmt_getfont\n");
		return GMT_PARSE_ERROR;
	}
	assert (F);	/* F needs to not point to NULL */
	strncpy (line, buffer, GMT_BUFSIZ-1);	/* Work on a copy of the arguments */
	gmt_chop (line);	/* Remove trailing CR, LF and properly NULL-terminate the string */

	/* Processes font settings given as [size][,name][,fill][=pen] */

	F->form = 1;	/* Default is to fill the text with a solid color */
	F->set = 0;     /* Start from no settings */
	if ((s = strchr (line, '='))) {	/* Specified an outline pen */
		s[0] = 0, i = 1;	/* Chop of this modifier */
		if (s[1] == '~') F->form |= 8, i = 2;	/* Want to have an outline that does not obscure the text */
		if (gmt_getpen (GMT, &s[i], &F->pen))
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "Representation of font outline pen not recognized - ignored.\n");
		else
			F->form |= 2;	/* Turn on outline font flag */
		F->set = 2;	/* Means we specified font pen */
	}
	for (i = 0; line[i]; i++) if (line[i] == ',') line[i] = ' ';	/* Replace , with space */
	n = sscanf (line, "%s %s %s", size, name, fill);
	for (i = 0; line[i]; i++) if (line[i] == ' ') line[i] = ',';	/* Replace space with , */
	if (n == 2 && i > 0) {	/* Could be size,name or size,fill or name,fill */
		if (line[i-1] == ',') {		/* Must be size,name, so we can continue */
		}
		else if (line[0] == ',') {	/* ,name,fill got stored in size,name */
			strncpy (fill, name, GMT_LEN256-1);
			strncpy (name, size, GMT_LEN256-1);
			size[0] = '\0';
		}
		else if (gmt_is_fill (GMT, name)) {	/* fill got stored in name */
			strncpy (fill, name, GMT_LEN256-1);
			name[0] = '\0';
			if (gmtsupport_is_fontname (GMT, size)) {	/* name got stored in size */
				strncpy (name, size, GMT_LEN256-1);
				size[0] = '\0';
			}
		}
		else if (gmtsupport_is_fontname (GMT, size)) {	/* name got stored in size and size in name */
			strncpy (fill, name, GMT_LEN256-1);	/* Copy size */
			strncpy (name, size, GMT_LEN256-1);	/* Place name where it belongs */
			strncpy (size, fill, GMT_LEN256-1);	/* Place size where it belongs */
			fill[0] = '\0';	/* No fill */
		}
	}
	else if (n == 1) {	/* Could be size or name or fill */
		if (line[0] == ',' && line[1] == ',') {	/* ,,fill got stored in size */
			strncpy (fill, size, GMT_LEN256-1);
			size[0] = '\0';
		}
		else if (line[0] == ',') {		/* ,name got stored in size */
			strncpy (name, size, GMT_LEN256-1);
			size[0] = '\0';
		}
		else if (gmt_is_fill (GMT, size)) {	/* fill got stored in size */
			strncpy (fill, size, GMT_LEN256-1);
			size[0] = '\0';
		}
		else if (gmtsupport_is_fontname (GMT, size)) {	/* name got stored in size */
			strncpy (name, size, GMT_LEN256-1);
			size[0] = '\0';
		}
		/* Unstated else branch means we got size stored correctly */
	}
	/* Unstated else branch means we got all 3: size,name,fill */

	/* Assign font size, type, and fill, if given */
	if (!size[0] || size[0] == '-') { /* Skip */ }
	else if (!strncmp (size, "auto", 4U))
		F->size = GMT->session.d_NaN;
	else if ((pointsize = gmt_convert_units (GMT, size, GMT_PT, GMT_PT)) < GMT_CONV4_LIMIT)
		GMT_Report (GMT->parent, GMT_MSG_WARNING, "Representation of font size not recognized. Using default.\n");
	else
		F->size = pointsize;
	if (!name[0] || name[0] == '-') { /* Skip */ }
	else if ((k = gmt_getfonttype (GMT, name)) >= 0)
		F->id = k;
	else
		GMT_Report (GMT->parent, GMT_MSG_WARNING, "Representation of font type not recognized. Using default.\n");
	if (!fill[0]) { /* Skip */ }
	else if (fill[0] == '-') {	/* Want no fill */
		F->form &= 2;	/* Turn off fill font flag set initially */
		gmt_M_rgb_copy (F->fill.rgb, GMT->session.no_rgb);
	}
	else {	/* Decode fill and set flags */
		if (gmt_getfill (GMT, fill, &F->fill)) GMT_Report (GMT->parent, GMT_MSG_WARNING, "Representation of font fill not recognized. Using default.\n");
		if (F->fill.use_pattern) F->form &= 2, F->form |= 4;	/* Flag that font fill is a pattern and not solid color */
		F->set |= 1;	/* Means we did specify something related to the fill */
	}
	if ((F->form & 7) == 0) {
		GMT_Report (GMT->parent, GMT_MSG_WARNING, "Cannot turn off both font fill and font outline.  Reset to font fill.\n");
		F->form = 1;
	}
	return (false);
}

/*! . */
char *gmt_putfont (struct GMT_CTRL *GMT, struct GMT_FONT *F) {
	/* gmt_putfont creates a GMT textstring equivalent of the specified font */

	static char text[GMT_BUFSIZ];
	char size[GMT_LEN32] = {""};

	if (gmt_M_is_dnan (F->size))
		snprintf (size, GMT_LEN32, "auto,");
	else
		snprintf (size, GMT_LEN32, "%gp,", F->size);

	if (F->form & 2) {
		if (F->form & 8)
			snprintf (text, GMT_BUFSIZ, "%s%s,%s=~%s", size, GMT->session.font[F->id].name, gmtlib_putfill (GMT, &F->fill), gmt_putpen (GMT, &F->pen));
		else
			snprintf (text, GMT_BUFSIZ, "%s%s,%s=%s", size, GMT->session.font[F->id].name, gmtlib_putfill (GMT, &F->fill), gmt_putpen (GMT, &F->pen));
	}
	else
		snprintf (text, GMT_BUFSIZ, "%s%s,%s", size, GMT->session.font[F->id].name, gmtlib_putfill (GMT, &F->fill));
	return (text);
}

/*! . */
void gmt_init_pen (struct GMT_CTRL *GMT, struct GMT_PEN *pen, double width) {
	/* Sets default black solid pen of given width in points */
	gmt_M_unused(GMT);
	gmt_M_memset (pen, 1, struct GMT_PEN);
	pen->width = width;
}

GMT_LOCAL bool gmtsupport_is_pen (struct GMT_CTRL *GMT, char *line) {
	/* Returns true if text is a pen specification. Note: false means it is only a number, which could be a dumb specification for a pen, e.g. 2 */
	char *c = NULL;
	unsigned int i, nc;
	gmt_M_unused (GMT);
	if ((c = strchr (line, '+')) && strchr ("cosv", c[1])) return (true);	/* Found valid pen modifiers */
	for (i = nc = 0; line[i]; i++) if (line[i] == ',') nc++;	/* count commas */
	if (nc > 0) return (true);	/* At least 1 comma means we got color and/or style so clearly a pen */
	if (strchr (GMT_DIM_UNITS, line[strlen(line)-1])) return (true);	/* Clearly ends with a explicit measure unit, so a pen */
	if (isalpha (line[0])) return true;	/* A name probably, like faint */
	return (false);	/* Might still be, but here we just have a dumb number so who can tell */
}

/*! . */
bool gmt_getpen (struct GMT_CTRL *GMT, char *buffer, struct GMT_PEN *P) {
	int i, n;
	bool set_NaN = false;
	char def_width[GMT_LEN256] = {""}, width[GMT_LEN256] = {""}, color[GMT_LEN256] = {""}, style[GMT_LEN256] = {""}, line[GMT_BUFSIZ] = {""}, *c = NULL;

	if (!buffer || !buffer[0]) return (false);		/* Nothing given: return silently, leaving P intact */
	assert (P);	/* P needs to not point to NULL */

	strncpy (line, buffer, GMT_BUFSIZ-1);	/* Work on a copy of the arguments */
	gmt_chop (line);	/* Remove trailing CR, LF and properly NULL-terminate the string */
	if (!line[0]) return (false);		/* Nothing given: return silently, leaving P intact */

	/* First chop off and processes any line modifiers :
	 * +c[l|f] : Determine how a CPT (-C) affects pen and fill colors normally controlled via -W.
	 * +s : Draw line via Bezier spline [Default is linear segments]
	 * +o<offset(s) : Start and end line after an initial offset from actual coordinates [planned for 5.3]
	 * +v[b|e]<size><vecargs>  : Draw vector head at line endings [planned for 5.3].
	 */

	if ((c = strchr (line, '+')) && strchr ("cosv", c[1])) {	/* Found valid modifiers */
		char mods[GMT_LEN256] = {""}, v_args[2][GMT_LEN256] = {"",""}, p[GMT_LEN64] = {""}, T[2][GMT_LEN64] = {"",""}, *t = NULL, *t2 = NULL;
		unsigned int pos = 0;
		int n;
		bool processed_vector = false, use[2] = {false, false}, may_differ = false;
		size_t len;
		if ((t2 = strstr (line, "+v"))) {	/* Keep the +v <args> since strtok will split them otherwise */
			if ((t = strstr (line, "+vb"))) {	/* Keep the +v <args> since strtok will split them otherwise */
				strncpy (v_args[BEG], &t[3], GMT_LEN256-1);
				if ((t = strstr (v_args[BEG], "+ve"))) t[0] = '\0';	/* Chop off the other one */
				use[BEG] = true;
			}
			if ((t = strstr (line, "+ve"))) {	/* Keep the +v <args> since strtok will split them otherwise */
				strncpy (v_args[END], &t[3], GMT_LEN256-1);
				if ((t = strstr (v_args[END], "+vb"))) t[0] = '\0';	/* Chop off the other one */
				use[END] = true;
			}
			if (use[BEG] == false && use[END] == false) {	/* Just gave +v to apply to both ends */
				strncpy (v_args[BEG], &t2[2], GMT_LEN256-1);
				strncpy (v_args[END], &t2[2], GMT_LEN256-1);
				may_differ = use[BEG] = use[END] = true;
			}
		}
		strncpy (mods, &c[1], GMT_LEN256-1);	/* Get our copy of the modifiers */
		c[0] = '\0';		/* Chop off modifiers */
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Pen modifier found: %s\n", mods);
		while ((gmt_strtok (mods, "+", &pos, p))) {
			switch (p[0]) {
				case 'c':	/* Effect of CPT on lines and fills */
					switch (p[1]) {
						case 'l':   P->cptmode = 1; break;
						case 'f':   P->cptmode = 2; break;
						case '\0':  P->cptmode = 3; break;
						default:
							GMT_Report (GMT->parent, GMT_MSG_ERROR, "Failure parsing pen modification +%s\n", p);
							return false;
						break;
					}
					break;
				case 's':
					if (processed_vector) break;	/* This is the +s within +v vector specifications */
					P->mode = PSL_BEZIER;
					break;
				case 'o':
					if (processed_vector) break;	/* This is the +o within +v vector specifications */
					n = sscanf (&p[1], "%[^/]/%s", T[BEG], T[END]);
					if (n == 1) strcpy (T[END], T[BEG]);
					for (n = 0; n < 2; n++) {
						len = strlen (T[n]) - 1;
						if (strchr (GMT_DIM_UNITS, T[n][len])) {	/* Plot distances in cm,inch,points */
							P->end[n].type = 0;
							P->end[n].unit = 'C';
							P->end[n].offset = gmt_M_to_inch (GMT, T[n]);
						}
						else if (strchr (GMT_LEN_UNITS, T[n][len]))	/* Length units */
							P->end[n].type = gmt_get_distance (GMT, T[n], &P->end[n].offset, &P->end[n].unit);
						else {	/* No units, select Cartesian */
							P->end[n].type = 0;
							P->end[n].unit = 'X';
							P->end[n].offset = atof (T[n]);
						}
					}
					break;
				case 'v':	/* Vector specs */
					processed_vector = true;
					for (n = 0; n < 2; n++) {
						if (!use[n]) continue;
						gmt_M_free (GMT, P->end[n].V);	/* Must free previous structure first */
						P->end[n].V = gmt_M_memory (GMT, NULL, 1, struct GMT_SYMBOL);
						sscanf (v_args[n], "%[^+]%s", T[BEG], T[END]);
						P->end[n].V->size_x = gmt_M_to_inch (GMT, T[BEG]);
						if (gmt_parse_vector (GMT, 'v', T[END], P->end[n].V)) {	/* Error decoding new vector syntax */
							GMT_Report (GMT->parent, GMT_MSG_ERROR, "Failure parsing vector specifications %s\n", T[END]);
							return false;
						}
						if (P->end[n].V->v.status & PSL_VEC_BEGIN) P->end[n].V->v.status -= PSL_VEC_BEGIN;	/* Always at end in this context */
						P->end[n].V->v.status |= PSL_VEC_END;	/* Always at end in this context */
						gmt_init_vector_param (GMT, P->end[n].V, false, false, NULL, false, NULL);	/* Update vector head parameters */
						if (may_differ)	/* Must allow different symbols at the two ends */
							P->end[n].V->v.v_kind[END] = P->end[n].V->v.v_kind[n];
						else
							P->end[n].V->v.v_kind[END] = MAX (P->end[n].V->v.v_kind[BEG], P->end[n].V->v.v_kind[END]);
						switch (P->end[n].V->v.v_kind[END]) {
							case PSL_VEC_ARROW:
								P->end[n].length = 0.5 * P->end[n].V->size_x * (2.0 - P->end[n].V->v.v_shape);
								break;
							case PSL_VEC_CIRCLE:
								P->end[n].length = sqrt (P->end[n].V->size_x * 0.5 * P->end[n].V->v.h_width / M_PI);	/* Same circle area as vector head */
								break;
							case PSL_VEC_SQUARE:
								P->end[n].length = sqrt (P->end[n].V->size_x * 0.5 * P->end[n].V->v.h_width)/2;	/* Same square area as vector head */
								break;
							case PSL_VEC_TERMINAL:
								P->end[n].length = 0.0;
								break;

						}
						use[n] = false;	/* Done processing this one */
					}
					break;
				case 'a': case 'b': case 'e': case 'g': case 'h': case 'j': case 'l': case 'm': case 'n': case 'p': case 'q':
					 case 'r': case 't': case 'z':	/* These are possible modifiers within +v vector specifications */
					if (processed_vector) break;
					GMT_Report (GMT->parent, GMT_MSG_WARNING, "Pen modifier (%s) not recognized.\n", p);
					break;
				default:
					GMT_Report (GMT->parent, GMT_MSG_WARNING, "Pen modifier (%s) not recognized.\n", p);
					break;
			}
		}
	}

	/* Processes pen specifications given as [width[,<color>[,<style>[t<unit>]]][@<transparency>] */

	if (gmt_M_is_dnan (P->width)) {	/* Worry in case no width is given */
		strcpy (def_width, "0");	/* To avoid any parsing errors */
		set_NaN = true;	/* Flag this specific case */
	}
	else	/* Default to current pen width if pen width is not given */
		sprintf (def_width, "%.16gp", P->width);
	for (i = 0; line[i]; i++) if (line[i] == ',') line[i] = ' ';	/* Replace , with space */
	n = sscanf (line, "%s %s %s", width, color, style);
	for (i = 0; line[i]; i++) if (line[i] == ' ') line[i] = ',';	/* Replace space with , */
	if (n == 2) {	/* Could be width,color or width,style or color,style */
		if (line[0] == ',') {	/* ,color,style got stored in width,color */
			strncpy (style, color, GMT_LEN256-1);
			strncpy (color, width, GMT_LEN256-1);
			strncpy (width, def_width, GMT_LEN256-1);
		}
		else if (gmtsupport_is_penstyle (color)) {	/* style got stored in color */
			strncpy (style, color, GMT_LEN256-1);
			color[0] = '\0';
			if (gmtlib_is_color (GMT, width)) {	/* color got stored in width */
				strncpy (color, width, GMT_LEN256-1);
				strncpy (width, def_width, GMT_LEN256-1);
			}
		}
		else	/* Means we got width, color */
			set_NaN = false;
	}
	else if (n == 1) {	/* Could be width or color or style */
		if (line[0] == ',' && line[1] == ',') {	/* ,,style got stored in width */
			strncpy (style, width, GMT_LEN256-1);
			strncpy (width, def_width, GMT_LEN256-1);
		}
		else if (line[0] == ',') {		/* ,color got stored in width */
			strncpy (color, width, GMT_LEN256-1);
			strncpy (width, def_width, GMT_LEN256-1);
		}
		else if (gmtsupport_is_penstyle (width)) {	/* style got stored in width */
			strncpy (style, width, GMT_LEN256-1);
			strncpy (width, def_width, GMT_LEN256-1);
		}
		else if (gmtlib_is_color (GMT, width)) {	/* color got stored in width */
			strncpy (color, width, GMT_LEN256-1);
			strncpy (width, def_width, GMT_LEN256-1);
		}
		else	/* Means we got width */
			set_NaN = false;
	}
	/* Assign width, color, style if given */
	if (gmtsupport_getpenwidth (GMT, width, P)) GMT_Report (GMT->parent, GMT_MSG_WARNING, "Representation of pen width (%s) not recognized. Using default.\n", width);
	if (gmt_getrgb (GMT, color, P->rgb)) GMT_Report (GMT->parent, GMT_MSG_WARNING, "Representation of pen color (%s) not recognized. Using default.\n", color);
	if (set_NaN) P->width = GMT->session.d_NaN;	/* This will prevent gmtlib_getpenstyle to set final style since that needs actual width [see gmt_set_undefined_defaults] */
	if (gmtlib_getpenstyle (GMT, style, P)) GMT_Report (GMT->parent, GMT_MSG_WARNING, "Representation of pen style (%s) not recognized. Using default.\n", style);

	return (false);
}

/*! . */
char *gmt_putpen (struct GMT_CTRL *GMT, struct GMT_PEN *P) {
	/* gmt_putpen creates a GMT textstring equivalent of the specified pen */

	static char text[GMT_BUFSIZ];
	int i, k;

	k = gmtsupport_pen2name (P->width);
	if (P->style[0]) {
		if (k == -2)	/* Width is undefined */
			snprintf (text, GMT_BUFSIZ, "%s,%s:%.5gp", gmt_putcolor (GMT, P->rgb), P->style, P->offset);
		else if (k == -1)	/* Width has no name */
			snprintf (text, GMT_BUFSIZ, "%.5gp,%s,%s:%.5gp", P->width, gmt_putcolor (GMT, P->rgb), P->style, P->offset);
		else	/* Named pen width */
			snprintf (text, GMT_BUFSIZ, "%s,%s,%s:%.5gp", GMT_penname[k].name, gmt_putcolor (GMT, P->rgb), P->style, P->offset);
		for (i = 0; text[i]; i++) if (text[i] == ' ') text[i] = '_';
	}
	else {
		if (k == -2)	/* Width is undefined */
			snprintf (text, GMT_BUFSIZ, "%s", gmt_putcolor (GMT, P->rgb));
		else if (k == -1)	/* Width has no name */
			snprintf (text, GMT_BUFSIZ, "%.5gp,%s", P->width, gmt_putcolor (GMT, P->rgb));
		else	/* Named pen width */
			snprintf (text, GMT_BUFSIZ, "%s,%s", GMT_penname[k].name, gmt_putcolor (GMT, P->rgb));
	}
	return (text);
}

void gmt_freepen (struct GMT_CTRL *GMT, struct GMT_PEN *P) {
	for (int k = 0; k < 2; k++) {
		gmt_M_free (GMT, P->end[k].V);
	}
}

void gmt_scale_pen (struct GMT_CTRL *GMT, struct GMT_PEN *P, double scale) {
	/* Scale all pen attributes by given scale. Note: P as assumed to be reset to nominal values before scaling */
	gmt_M_unused (GMT);
	P->width  *= scale;
	P->offset *= scale;
	if (P->style[0]) {	/* Must scale the dashes and gaps and update string */
		unsigned int pos = 0;
		char tmp[GMT_PEN_LEN] = {""}, p[GMT_LEN64] = {""};
		double w;
		while ((gmt_strtok (P->style, "+", &pos, p))) {
			w = atof (p) * scale;	/* New gap or dash length */
			snprintf (p, GMT_LEN64, "%.3g", w);
			if (tmp[0]) strcat (tmp, " ");	/* If not first then we need space between items */
			strcat (tmp, p);
		}
		/* Update the style attribute */
		strncpy (P->style, tmp, GMT_PEN_LEN);
	}
}

#define GMT_INC_IS_FEET		1
#define GMT_INC_IS_SURVEY_FEET	2
#define GMT_INC_IS_M		4
#define GMT_INC_IS_KM		8
#define GMT_INC_IS_MILES	16
#define GMT_INC_IS_NMILES	32
#define GMT_INC_IS_NNODES	64
#define GMT_INC_IS_EXACT	128
#define GMT_INC_UNITS		63

/*! . */
bool gmt_getinc (struct GMT_CTRL *GMT, char *line, double inc[]) {
	/* Special case of getincn use where n is two. */

	int n;

	/* Syntax: -I<xinc>[m|s|e|f|k|M|n|u|+e|n][/<yinc>][m|s|e|f|k|M|n|u|+e|n]
	 * Units: d = arc degrees
	 * 	  m = arc minutes
	 *	  s = arc seconds [was c]
	 *	  e = meter [Convert to degrees]
	 *	  f = feet [Convert to degrees]
	 *	  M = Miles [Convert to degrees]
	 *	  k = km [Convert to degrees]
	 *	  n = nautical miles [Convert to degrees]
	 *	  u = survey feet [Convert to degrees]
	 * Flags: +e = Adjust -R to fit exact -I [Default modifies -I to fit -R]
	 *	  +n = incs are actually n_columns/n_rows - convert to get xinc/yinc
	 */

	if (!line) { GMT_Report (GMT->parent, GMT_MSG_ERROR, "No argument given to gmt_getinc\n"); return (true); }

	if ((n = gmt_getincn (GMT, line, inc, 2)) < 0) return true;
	if (n == 1) {	/* Must copy y info from x */
		inc[GMT_Y] = inc[GMT_X];
		GMT->current.io.inc_code[GMT_Y] = GMT->current.io.inc_code[GMT_X];	/* Use exact inc codes for both x and y */
	}

	if (GMT->current.io.inc_code[GMT_X] & GMT_INC_IS_NNODES && GMT->current.io.inc_code[GMT_X] & GMT_INC_UNITS) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "number of x nodes cannot have units\n");
		return (true);
	}
	if (GMT->current.io.inc_code[GMT_Y] & GMT_INC_IS_NNODES && GMT->current.io.inc_code[GMT_Y] & GMT_INC_UNITS) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "number of y nodes cannot have units\n");
		return (true);
	}
	return (false);
}

GMT_LOCAL unsigned int gmtsupport_set_geo (struct GMT_CTRL *GMT) {
	/* Returns 0 for all Cartesian, or sum of GMT_IS_LON if longitudes and GMT_IS_LAT if latitudes */
	unsigned int x = GMT_IS_LON, y = GMT_IS_LAT;
	if (!GMT->common.R.active[RSET]) return x + y;	/* Just as before to avoid breaking things */
	/* Here we have -Rw/e/s/n.  If it clearly is not geographic then we return 0, else we return one or the sum of GMT_IS_LON and GMT_IS_LAT */
	if ((GMT->common.R.wesn[XHI] - GMT->common.R.wesn[XLO]) > 360.0) x = 0;	/* Cannot exceed 360 degrees longitude */
	if ((GMT->common.R.wesn[YHI] - GMT->common.R.wesn[YLO]) > 180.0) y = 0;	/* Cannot exceed 180 degrees latitude */
	if (GMT->common.R.wesn[XLO] < -720.0 || GMT->common.R.wesn[XLO] > 360.0) x = 0;	/* Clearly outside normal longitude range */
	if (GMT->common.R.wesn[XHI] < -360.0 || GMT->common.R.wesn[XHI] > 720.0) x = 0;	/* Clearly outside normal longitude range */
	if (GMT->common.R.wesn[YLO] < -90.0 || GMT->common.R.wesn[YLO] > 90.0) y = 0;	/* Clearly outside normal latitude range */
	if (GMT->common.R.wesn[YHI] < -90.0 || GMT->common.R.wesn[YHI] > 90.0) y = 0;	/* Clearly outside normal latitude range */
	return x+y;	/* Might still be geographic for the purpose of parsing -I */
}

/*! . */
int gmt_getincn (struct GMT_CTRL *GMT, char *line, double inc[], unsigned int n) {
	bool separate;
	unsigned int last, i, pos, side = GMT_X, geo = gmtsupport_set_geo (GMT);	/* true unless clearly -R is Cartesian */
	unsigned geo_bit[2] = {GMT_IS_LON, GMT_IS_LAT};
	char p[GMT_BUFSIZ];
	double scale = 1.0;

	/* Deciphers dx/dy/dz/dw/du/dv/... increment strings with n items */

	if (!line) { GMT_Report (GMT->parent, GMT_MSG_ERROR, "No argument given to gmt_getincn\n"); GMT->parent->error = GMT_PARSE_ERROR; return -GMT_PARSE_ERROR; }

	gmt_M_memset (inc, n, double);

	i = pos = GMT->current.io.inc_code[GMT_X] = GMT->current.io.inc_code[GMT_Y] = 0;
	separate = (strchr (line, '/') != NULL);
	while (i < n && (gmt_strtok (line, "/", &pos, p))) {
		last = (unsigned int)strlen (p) - 1;
		if (last && p[last] == 'e' && p[last-1] == '+') {	/* +e: Let -I override -R */
			p[last] = p[last-1] = 0;
			if (i < 2) GMT->current.io.inc_code[i] |= GMT_INC_IS_EXACT;
			last -= 2;
		}
		else if (last && p[last] == '=') {	/* Obsolete =: Let -I override -R */
			p[last] = 0;
			if (i < 2) GMT->current.io.inc_code[i] |= GMT_INC_IS_EXACT;
			last--;
		}
		else if (last && p[last] == 'n' && p[last-1] == '+') {	/* +n: Number of nodes given, determine inc from domain (! added since documentation mentioned this once... */
			p[last] = 0;
			if (i < 2) GMT->current.io.inc_code[i] |= GMT_INC_IS_NNODES;
			last -= 2;
		}
		else if (p[last] == '+' || p[last] == '!') {	/* Obsolete + (! added since documentation mentioned this once...) */
			p[last] = 0;
			if (i < 2) GMT->current.io.inc_code[i] |= GMT_INC_IS_NNODES;
			if (last) last--;	/* Coverity rightly points out that if last == 0 it would become 4294967295 */
		}
		if (geo == 0 || (separate && (side <= GMT_Y && (geo & geo_bit[side]) == 0)) ) {	/* Gave a unit to a Cartesian axes that does not take any unit */
			if (p[last] && strchr (GMT_LEN_UNITS "c", p[last])) {
				if (separate) {	/* Report per axis since separate increments where given */
					static char *A = "xyzvuw";
					GMT_Report (GMT->parent, GMT_MSG_WARNING, "Unit %c is ignored as the %c-axis is not geographic\n", p[last], A[i]);
				}
				else	/* Single message since common increment for all axes */
					GMT_Report (GMT->parent, GMT_MSG_WARNING, "Unit %c is ignored as no axis is geographic\n", p[last]);
				p[last] = 0;
			}
		}
		switch (p[last]) {
			case 'd':	/* Gave arc degree */
				p[last] = 0;
				break;
			case 'm':	/* Gave arc minutes */
				p[last] = 0;
				scale = GMT_MIN2DEG;
				break;
			case 'c':
				if (gmt_M_compat_check (GMT, 4)) {
					GMT_Report (GMT->parent, GMT_MSG_COMPAT, "Second interval unit c is deprecated; use s instead\n");
				}
				else {
					scale = 1.0;
					break;
				}
				/* Intentionally fall through - to case 's' */
			case 's':	/* Gave arc seconds */
				p[last] = 0;
				scale = GMT_SEC2DEG;
				break;
			case 'e':	/* Gave meters along mid latitude */
				p[last] = 0;
				if (i < 2) GMT->current.io.inc_code[i] |= GMT_INC_IS_M;
				break;
			case 'f':	/* Gave feet along mid latitude */
				p[last] = 0;
				if (i < 2) GMT->current.io.inc_code[i] |= GMT_INC_IS_FEET;
				break;
			case 'k':	/* Gave km along mid latitude */
				p[last] = 0;
				if (i < 2) GMT->current.io.inc_code[i] |= GMT_INC_IS_KM;
				break;
			case 'M':	/* Gave miles along mid latitude */
				p[last] = 0;
				if (i < 2) GMT->current.io.inc_code[i] |= GMT_INC_IS_MILES;
				break;
			case 'n':	/* Gave nautical miles along mid latitude */
				p[last] = 0;
				if (i < 2) GMT->current.io.inc_code[i] |= GMT_INC_IS_NMILES;
				break;
			case 'u':	/* Gave survey feet along mid latitude */
				p[last] = 0;
				if (i < 2) GMT->current.io.inc_code[i] |= GMT_INC_IS_SURVEY_FEET;
				break;
			default:	/* No special flags or units */
				scale = 1.0;
				geo = false;
				break;
		}
		if ((sscanf (p, "%lf", &inc[i])) != 1) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Unable to decode %s as a floating point number\n", p);
			GMT->parent->error = GMT_PARSE_ERROR;
			return -GMT_PARSE_ERROR;
		}
		inc[i] *= scale;
		i++;	/* Goto next increment */
		side++;
	}
	if (geo) {
		if (geo == (GMT_IS_LON+GMT_IS_LAT))	/* Regular lon/lat region presumably */
			gmt_set_geographic (GMT, GMT_IN);
		else if (geo & GMT_IS_LON)
			gmt_set_column_type (GMT, GMT_IN, GMT_X, GMT_IS_LON);
		else if (geo & GMT_IS_LAT)
			gmt_set_column_type (GMT, GMT_IN, GMT_Y, GMT_IS_LAT);
	}

	return (i);	/* Returns the number of increments found */
}

double gmtlib_conv_distance (struct GMT_CTRL *GMT, double value, char in_unit, char out_unit)
{
	/* Given the length in value and the unit of measure, convert from in_unit to out_unit.
	 * When conversions between arc lengths and linear distances are used we assume a spherical Earth. */
		unsigned int k;
	char units[2];
	double scale[2] = {1.0, 1.0};
	units[GMT_IN] = in_unit;	units[GMT_OUT] = out_unit;
	for (k = GMT_IN; k <= GMT_OUT; k++) {	/* Set in/out scales */
		switch (units[k]) {
			case 'd': scale[k] = GMT->current.proj.DIST_M_PR_DEG; break;			/* arc degree */
			case 'm': scale[k] = GMT->current.proj.DIST_M_PR_DEG * GMT_MIN2DEG; break;	/* arc minutes */
			case 's': scale[k] = GMT->current.proj.DIST_M_PR_DEG * GMT_SEC2DEG; break;	/* arc seconds */
			case 'e': scale[k] = 1.0; break;						/* meters */
			case 'f': scale[k] = METERS_IN_A_FOOT; break;					/* feet */
			case 'k': scale[k] = METERS_IN_A_KM; break;					/* km */
			case 'M': scale[k] = METERS_IN_A_MILE; break;					/* miles */
			case 'n': scale[k] = METERS_IN_A_NAUTICAL_MILE; break;				/* nautical miles */
			case 'u': scale[k] = METERS_IN_A_SURVEY_FOOT; break;				/* survey feet */
			default:  break;								/* No units */
		}
	}
	return (value * scale[GMT_IN] / scale[GMT_OUT]);	/* Do the conversion */
}

/*! . */
int gmt_get_distance (struct GMT_CTRL *GMT, char *line, double *dist, char *unit) {
	/* Accepts a distance length with optional unit character.  The
	 * recognized units are:
	 * e (meter), f (foot), M (mile), n (nautical mile), k (km), u(survey foot)
	 * and d (arc degree), m (arc minute), s (arc second).
	 * If no unit is found it means Cartesian data, unless -fg is set,
	 * in which we default to meters.
	 * Passes back the radius, the unit, and returns distance_flag:
	 * flag = 0: Units are user Cartesian. Use Cartesian distances
	 * flag = 1: Unit is d|e|f|k|m|M|n|s|u. Use Flat-Earth distances.
	 * flag = 2: Unit is d|e|f|k|m|M|n|s|u. Use great-circle distances.
	 * flag = 3: Unit is d|e|f|k|m|M|n|s|u. Use geodesic distances.
	 * One of 2 modifiers may be prepended to the distance to control how
	 * spherical distances are computed:
	 *   - means less accurate; use Flat Earth approximation (fast).
	 *   + means more accurate; use geodesic distances (slow).
	 * Otherwise we use great circle distances (intermediate) [Default].
	 * The calling program must call gmt_init_distaz with the
	 * distance_flag and unit to set up the gmt_distance functions.
	 * Distances computed will be in the unit selected.
	 */
	int last, d_flag = 1, start = 1, way;
	char copy[GMT_LEN64] = {""};

	/* Syntax:  -S<dist>[d|e|f|k|m|M|n|s|u]  */

	if (!line) { GMT_Report (GMT->parent, GMT_MSG_ERROR, "No argument given to gmt_get_distance\n"); return (-1); }

	strncpy (copy, line, GMT_LEN64-1);
	*dist = GMT->session.d_NaN;

	switch (copy[0]) {	/* Look for obsolete modifiers -/+ to set how spherical distances are computed */
		case '-':	/* Want flat Earth calculations */
			way = 0;
			break;
		case '+':	/* Want geodesic distances */
			way = 2;
			break;
		default:	/* Default is great circle distances */
			way = 1;
			start = 0;
			break;
	}
	if (way != 1) {
		if (gmt_M_compat_check (GMT, 6))
			GMT_Report (GMT->parent, GMT_MSG_COMPAT, "Leading +|- to set distance mode is deprecated; use common option -j instead\n");
		else if (way == 0) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Negative distance given\n");
			return (-1);
		}
	}

	/* Extract the distance unit, if any */

	last = (int)strlen (line) - 1;
	if (strchr (GMT_LEN_UNITS GMT_OPT("c"), (int)copy[last])) {	/* Got a valid distance unit */
		*unit = copy[last];
		if (gmt_M_compat_check (GMT, 4) && *unit == 'c') {
			GMT_Report (GMT->parent, GMT_MSG_COMPAT, "Unit c is deprecated; use s instead\n");
			*unit = 's';
		}
		copy[last] = '\0';	/* Chop off the unit */
	}
	else if (!strchr ("0123456789.", (int)copy[last])) {	/* Got an invalid distance unit */
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Invalid distance unit (%c). Choose among %s\n", (int)copy[last], GMT_LEN_UNITS_DISPLAY);
		return (-1);
	}
	else if (start == 1 || gmt_M_is_geographic (GMT, GMT_IN))	/* Indicated a spherical calculation mode (-|+) or -fg but appended no unit; default to meter */
		*unit = GMT_MAP_DIST_UNIT;
	else {	/* Cartesian, presumably */
		*unit = 'X';
		d_flag = way = 0;
	}

	/* Get the specified length */
	if (strlen (&copy[start]) == 0) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "No distance argument given, only unit.\n");
		return (-2);
	}
	else if ((sscanf (&copy[start], "%lf", dist)) != 1) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Unable to decode %s as a floating point number.\n", &copy[start]);
		return (-2);
	}

	if ((*dist) < 0.0) return (-3);	/* Quietly flag a negative distance */

	return (d_flag + way);	/* Range 0-3 */
}

/*! . */
void gmt_RI_prepare (struct GMT_CTRL *GMT, struct GMT_GRID_HEADER *h) {
	/* This routine adjusts the grid header. It computes the correct n_columns, n_rows, x_inc and y_inc,
	   based on user input of the -I option and the current settings of x_min, x_max, y_min, y_max and registration.
	   On output the grid boundaries are always gridline or pixel oriented, depending on registration.
	   The routine is not run when n_columns and n_rows are already set.
	*/
	struct GMT_GRID_HEADER_HIDDEN *HH = gmt_get_H_hidden (h);

	h->xy_off = 0.5 * h->registration;	/* Use to calculate mean location of block */

	gmt_increment_adjust (GMT, h->wesn, h->inc, h->registration);

	/* Determine n_columns */
	h->n_columns = gmt_M_grd_get_nx (GMT, h);
	/* Determine n_rows */
	h->n_rows = gmt_M_grd_get_ny (GMT, h);

	/* Set the inverse increments */
	HH->r_inc[GMT_X] = 1.0 / h->inc[GMT_X];
	HH->r_inc[GMT_Y] = 1.0 / h->inc[GMT_Y];
}

/*! . */
void gmt_increment_adjust (struct GMT_CTRL *GMT, double *wesn, double *inc, enum GMT_enum_reg registration) {
	/* This routine adjusts raw grid increments given with projected units and ensures they are compatible
	 * with the given domain boundaries.  Depending on -I settings we may need to adjust inc as well as
	 * xmax and ymax.
	*/
	unsigned int one_or_zero, n_rows, n_columns;
	double s;

	if (GMT->current.io.inc_code[GMT_X] == 0 && GMT->current.io.inc_code[GMT_Y] == 0) return;	/* Nothing to do */

	one_or_zero = !registration;

	/* XINC AND XMIN/XMAX CHECK FIRST */

	/* Adjust x_inc */

	if (GMT->current.io.inc_code[GMT_X] & GMT_INC_IS_NNODES) {	/* Got n_columns */
		int64_t n = lrint (inc[GMT_X]);
		if (n <= 0 || !doubleAlmostEqual (inc[GMT_X], (double)n)) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Your number of x-nodes %g is not a valid integer\n", inc[GMT_X]);
		}
		inc[GMT_X] = gmt_M_get_inc (GMT, wesn[XLO], wesn[XHI], n, registration);
		GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Given n_columns implies x_inc = %g\n", inc[GMT_X]);
	}
	else if (GMT->current.io.inc_code[GMT_X] & GMT_INC_UNITS) {	/* Got funny units */
		if (gmt_M_is_geographic (GMT, GMT_IN)) {
			switch (GMT->current.io.inc_code[GMT_X] & GMT_INC_UNITS) {
				case GMT_INC_IS_FEET:	/* foot */
					s = METERS_IN_A_FOOT;
					break;
				case GMT_INC_IS_KM:	/* km */
					s = METERS_IN_A_KM;
					break;
				case GMT_INC_IS_MILES:	/* Statute mile */
					s = METERS_IN_A_MILE;
					break;
				case GMT_INC_IS_NMILES:	/* Nautical mile */
					s = METERS_IN_A_NAUTICAL_MILE;
					break;
				case GMT_INC_IS_SURVEY_FEET:	/* US survey foot */
					s = METERS_IN_A_SURVEY_FOOT;
					break;
				case GMT_INC_IS_M:	/* Meter */
				default:
					s = 1.0;
					break;
			}
			inc[GMT_X] *= s / (GMT->current.proj.DIST_M_PR_DEG * cosd (0.5 * (wesn[YLO] + wesn[YHI])));	/* Latitude scaling of E-W distances */
			GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Distance to degree conversion implies x_inc = %g\n", inc[GMT_X]);
		}
		else {
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "Cartesian x-increments are unit-less! - unit ignored\n");
			GMT->current.io.inc_code[GMT_X] -= (GMT->current.io.inc_code[GMT_X] & GMT_INC_UNITS);
		}
	}
	if (!(GMT->current.io.inc_code[GMT_X] & (GMT_INC_IS_NNODES | GMT_INC_IS_EXACT))) {	/* Adjust x_inc to exactly fit west/east */
		s = wesn[XHI] - wesn[XLO];
		n_columns = urint (s / inc[GMT_X]);
		s /= n_columns;
		if (fabs (s - inc[GMT_X]) > 0.0) {
			inc[GMT_X] = s;
			GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Given domain implies x_inc = %g\n", inc[GMT_X]);
		}
	}

	if (GMT->current.io.inc_code[GMT_X] & GMT_INC_IS_EXACT) {	/* Want to keep x_inc exactly as given; adjust x_max accordingly */
		/* Determine n_columns */
		n_columns = gmt_M_get_n (GMT, wesn[XLO], wesn[XHI], inc[GMT_X], registration);
		s = (wesn[XHI] - wesn[XLO]) - inc[GMT_X] * (n_columns - one_or_zero);
		if (fabs (s) > 0.0) {
			wesn[XHI] -= s;
			GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "x_max adjusted to %g\n", wesn[XHI]);
		}
	}

	/* YINC AND YMIN/YMAX CHECK SECOND */

	/* Adjust y_inc */

	if (GMT->current.io.inc_code[GMT_Y] & GMT_INC_IS_NNODES) {	/* Got n_rows */
		int64_t n = lrint (inc[GMT_Y]);
		if (n <= 0 || !doubleAlmostEqual (inc[GMT_Y], (double)n)) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Your number of y-nodes %g is not a valid integer\n", inc[GMT_Y]);
		}
		inc[GMT_Y] = gmt_M_get_inc (GMT, wesn[YLO], wesn[YHI], n, registration);
		GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Given n_rows implies y_inc = %g\n", inc[GMT_Y]);
	}
	else if (GMT->current.io.inc_code[GMT_Y] & GMT_INC_UNITS) {	/* Got funny units */
		if (gmt_M_is_geographic (GMT, GMT_IN)) {
			switch (GMT->current.io.inc_code[GMT_Y] & GMT_INC_UNITS) {
				case GMT_INC_IS_FEET:	/* feet */
					s = METERS_IN_A_FOOT;
					break;
				case GMT_INC_IS_KM:	/* km */
					s = METERS_IN_A_KM;
					break;
				case GMT_INC_IS_MILES:	/* miles */
					s = METERS_IN_A_MILE;
					break;
				case GMT_INC_IS_NMILES:	/* nmiles */
					s = METERS_IN_A_NAUTICAL_MILE;
					break;
				case GMT_INC_IS_SURVEY_FEET:	/* US survey feet */
					s = METERS_IN_A_SURVEY_FOOT;
					break;
				case GMT_INC_IS_M:	/* Meter */
				default:
					s = 1.0;
					break;
			}
			inc[GMT_Y] = (inc[GMT_Y] == 0.0) ? inc[GMT_X] : inc[GMT_Y] * s / GMT->current.proj.DIST_M_PR_DEG;
			GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Distance to degree conversion implies y_inc = %g\n", inc[GMT_Y]);
		}
		else {
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "Cartesian y-increments are unit-less! - unit ignored\n");
			GMT->current.io.inc_code[GMT_Y] -= (GMT->current.io.inc_code[GMT_Y] & GMT_INC_UNITS);
		}
	}
	if (!(GMT->current.io.inc_code[GMT_Y] & (GMT_INC_IS_NNODES | GMT_INC_IS_EXACT))) {	/* Adjust y_inc to exactly fit south/north */
		s = wesn[YHI] - wesn[YLO];
		n_rows = urint (s / inc[GMT_Y]);
		s /= n_rows;
		if (fabs (s - inc[GMT_Y]) > 0.0) {
			inc[GMT_Y] = s;
			GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Given domain implies y_inc = %g\n", inc[GMT_Y]);
		}
	}

	if (GMT->current.io.inc_code[GMT_Y] & GMT_INC_IS_EXACT) {	/* Want to keep y_inc exactly as given; adjust y_max accordingly */
		/* Determine n_rows */
		n_rows = gmt_M_get_n (GMT, wesn[YLO], wesn[YHI], inc[GMT_Y], registration);
		s = (wesn[YHI] - wesn[YLO]) - inc[GMT_Y] * (n_rows - one_or_zero);
		if (fabs (s) > 0.0) {
			wesn[YHI] -= s;
			GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "y_max adjusted to %g\n", wesn[YHI]);
		}
	}

	GMT->current.io.inc_code[GMT_X] = GMT->current.io.inc_code[GMT_Y] = 0;	/* Processed, so resetting these */
}

/*! . */
struct GMT_PALETTE * gmtlib_create_palette (struct GMT_CTRL *GMT, uint64_t n_colors) {
	/* Makes an empty palette table with a blank hidden struct */
	struct GMT_PALETTE *P = gmt_M_memory (GMT, NULL, 1, struct GMT_PALETTE);
	struct GMT_PALETTE_HIDDEN *PH = gmt_M_memory (GMT, NULL, 1, struct GMT_PALETTE_HIDDEN);
	if (P == NULL || PH == NULL) return NULL;
	P->hidden = PH;
	if (n_colors > 0) P->data = gmt_M_memory (GMT, NULL, n_colors, struct GMT_LUT);
	P->n_colors = (unsigned int)n_colors;
	PH->alloc_mode = GMT_ALLOC_INTERNALLY;		/* Memory can be freed by GMT. */
	PH->alloc_level = GMT->hidden.func_level;	/* Must be freed at this level. */
	PH->id = GMT->parent->unique_var_ID++;		/* Give unique identifier */

	return (P);
}

/*! . */
void gmtlib_free_cpt_ptr (struct GMT_CTRL *GMT, struct GMT_PALETTE *P) {
	unsigned int i;
	struct GMT_PALETTE_HIDDEN *PH = NULL;
	if (!P) return;
	/* Frees all memory used by this palette but does not free the palette itself */
	PH = gmt_get_C_hidden (P);
	for (i = 0; i < P->n_colors; i++) {
		gmtsupport_free_range (GMT, PH, &P->data[i]);
	}
	for (i = 0; i < 3; i++)
		if (P->bfn[i].fill)
			gmt_M_free (GMT, P->bfn[i].fill);
	gmt_M_free (GMT, P->data);
	/* Use free() to free the headers since they were allocated with strdup */
	if (P->n_headers) {
		for (i = 0; i < P->n_headers; i++) gmt_M_str_free (P->header[i]);
		gmt_M_free (GMT, P->header);
	}
	P->n_headers = P->n_colors = 0;
	gmt_M_free (GMT, P->hidden);
}

/*! . */
void gmtlib_copy_palette (struct GMT_CTRL *GMT, struct GMT_PALETTE *P_to, struct GMT_PALETTE *P_from) {
	unsigned int i;
	/* Copies the information from P_from to P_to */
	P_to->n_headers = P_from->n_headers;		/* Number of CPT header records (0 if no header) */
	P_to->n_colors = P_from->n_colors;			/* Number of colors in CPT lookup table */
	P_to->mode = P_from->mode;					/* Flags controlling use of BFN colors */
	P_to->model = P_from->model;				/* RGB, HSV, CMYK */
	P_to->is_wrapping = P_from->is_wrapping;	/* If 1 then we must wrap around to find color - can never be F or B */
	P_to->is_gray = P_from->is_gray;			/* 1 if only grayshades are needed */
	P_to->is_bw = P_from->is_bw;				/* 1 if only black and white are needed */
	P_to->is_continuous = P_from->is_continuous;	/* 1 if continuous color tables have been given */
	P_to->has_pattern = P_from->has_pattern;	/* 1 if CPT contains any patterns */
	P_to->has_hinge = P_from->has_hinge;		/* 1 if CPT is hinged at hinge (below) */
	P_to->has_range = P_from->has_range;		/* 1 if CPT has a natural range (minmax below) */
	P_to->categorical = P_from->categorical;	/* 1 (number) or 2 (key) if CPT applies to categorical data */
	P_to->hinge = P_from->hinge;				/* z-value for hinged CPTs */
	P_to->wrap_length = P_from->wrap_length;	/* z-length of active CPT */
	gmt_M_memcpy (P_to->minmax, P_from->minmax, 2, double);	/* Min/max z-value for a default range, if given */

	gmt_M_memcpy (P_to->hidden, P_from->hidden, 1, struct GMT_PALETTE_HIDDEN);
	gmt_M_memcpy (P_to->data, P_from->data, P_to->n_colors, struct GMT_LUT);
	gmt_M_memcpy (P_to->bfn, P_from->bfn, 3, struct GMT_BFN);
	for (i = 0; i < 3; i++) {
		P_to->bfn[i].fill = NULL;	/* Reset junk pointer from the memcopy */
		if (P_from->bfn[i].fill) {
			P_to->bfn[i].fill = gmt_M_memory (GMT, NULL, 1, struct GMT_FILL);
			gmt_M_memcpy (P_to->bfn[i].fill, P_from->bfn[i].fill, 1, struct GMT_FILL);
		}
	}
	for (i = 0; i < P_from->n_colors; i++) {
		P_to->data[i].fill = NULL;	/* Reset junk pointer from the memcopy */
		if (P_from->data[i].fill) {
			P_to->data[i].fill = gmt_M_memory (GMT, NULL, 1, struct GMT_FILL);
			gmt_M_memcpy (P_to->data[i].fill, P_from->data[i].fill, 1, struct GMT_FILL);
		}
		P_to->data[i].key = NULL;
		P_to->data[i].label = NULL;
		if (P_from->data[i].label) P_to->data[i].label = strdup (P_from->data[i].label);
		if (P_from->data[i].key) P_to->data[i].key = strdup (P_from->data[i].key);
	}
	GMT->current.setting.color_model = P_to->model;
	gmtsupport_copy_palette_hdrs (GMT, P_to, P_from);
}

/*! . */
struct GMT_PALETTE * gmtlib_duplicate_palette (struct GMT_CTRL *GMT, struct GMT_PALETTE *P_from, unsigned int mode) {
	/* Mode not used yet */
	struct GMT_PALETTE *P = gmtlib_create_palette (GMT, P_from->n_colors);
	gmt_M_unused(mode);
	gmtlib_copy_palette (GMT, P, P_from);
	return (P);
}

/*! . */
void gmtlib_free_palette (struct GMT_CTRL *GMT, struct GMT_PALETTE **P) {
	gmtlib_free_cpt_ptr (GMT, *P);
	gmt_M_free (GMT, *P);
	*P = NULL;
}

/*! Adds listing of available GMT cpt choices to a program's usage message */
int gmt_list_cpt (struct GMT_CTRL *GMT, char option) {
	char line[GMT_LEN256] = {""};
	char divider[115] = {"----------------------------------------------------------------------------------------------------------------"};
	struct GMTAPI_CTRL *API = GMT->parent;
	/* Note: 108 is the max length of entries in gmt_cpt_masters.h.  Update 115 and 113 if that changes */
	int L = MAX (MIN (API->terminal_width-5, 113), 0);	/* Number of dashes to print in divider line */
	GMT_Usage (API, 1, "\n-%c Specify a colortable [Default is %s]:", option, GMT->current.setting.cpt);
	GMT_Usage (API, 2, "[Legend: R = Default z-range, H = Hard Hinge, S = Soft Hinge, C = Colormodel]");
	divider[L] = '\0';	/* Truncate the line */
	gmt_message (GMT, "     %s\n", divider);
	for (unsigned int k = 0; k < GMT_N_CPT_MASTERS; k++) {
		char *c = NULL;
		strncpy (line, GMT_CPT_master[k], GMT_LEN256);
		c = strchr (line, ':');	/* Find the start of the info */
		c[0] = '\0';
		gmt_message (GMT, "     %s: ", line);
		GMT_Usage (API, -19, "%s", &c[2]);
	}
	gmt_message (GMT, "     %s\n", divider);
	GMT_Usage (API, 2, "[For more, visit www.seaviewsensing.com/pub/cpt-city and www.fabiocrameri.ch/visualisation.php]. "
		"Alternatively, specify -Ccolor1,color2[,color3,...] to build a linear "
		"continuous CPT from those colors automatically.");

	return (GMT_NOERROR);
}

/*! . */
GMT_LOCAL char *gmtsupport_cpt_master_index (struct GMT_CTRL *GMT, char *name) {
	/* Returns the full cpt name after looking it up in the master list. NULL if not master. */
	size_t len;
	gmt_M_unused(GMT);
	len = strlen (name);	/* Length of the master table name so we can limit comparison to just those characters */
	/* Note: There are near-duplicate names like broc and brocO, but since they are ordered alphabetically our
	 * search for broc will first compare with broc before brocO so not an issue. */
	for (unsigned int k = 0; k < GMT_N_CPT_MASTERS; k++) {
		char *c = strchr(GMT_CPT_master[k], ' ');
		if (!strncmp (name, c - len, len))	/* Match the end of the cpt name */
			return strndup (GMT_CPT_master[k], c - GMT_CPT_master[k]);	/* Return the full cpt name */
	}
	return NULL;
}

/*! . */
GMT_LOCAL void gmtsupport_make_continuous_colorlist (struct GMT_CTRL *GMT, struct GMT_PALETTE *P) {
	/* Convert a (by default) discrete CPT made from a color list to a continuous CPT instead */
	unsigned int k, i;
	gmt_M_unused(GMT);
	if (P->is_continuous) return;	/* Nothing to do */
	P->n_colors--;	/* One less slice */
	for (k = 0; k < P->n_colors; k++) {	/* Copy next low color to previous high color */
		gmt_M_rgb_copy (P->data[k].rgb_high, P->data[k+1].rgb_low);
		gmt_M_rgb_copy (P->data[k].hsv_high, P->data[k+1].hsv_low);
		/* Update color differences for interpolation function later (dz remains the same == 1) */
		for (i = 0; i < 4; i++) P->data[k].rgb_diff[i] = P->data[k].rgb_high[i] - P->data[k].rgb_low[i];
		for (i = 0; i < 4; i++) P->data[k].hsv_diff[i] = P->data[k].hsv_high[i] - P->data[k].hsv_low[i];
	}
	P->is_continuous = true;	/* Flag this as a continuous CPT */
}

/*! . */
unsigned int gmt_validate_cpt_parameters (struct GMT_CTRL *GMT, struct GMT_PALETTE *P, char *file, bool *interpolate, bool *force_continuous) {
	if (P->mode & GMT_CPT_COLORLIST && !P->categorical && !(*interpolate) && P->n_colors > 1) {	/* Color list with -T/min/max should be seen as continuous */
		*force_continuous = true, P->mode |= GMT_CPT_CONTINUOUS;
		gmtsupport_make_continuous_colorlist (GMT, P);
	}
	if (*interpolate) {
		if (!P->is_continuous && !(P->mode & GMT_CPT_COLORLIST)) {
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "%s is a discrete CPT. You can stretch it (-T<min>/<max>) but not interpolate it (-T<min>/<max>/<inc>).\n", file);
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "Selecting the given range and ignoring the increment setting.\n");
			*interpolate = false;
		}
	}
	else {	/* Did not request resampling */
		if (P->categorical) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "%s is a special categorical, discrete CPT. You can select a subset only via (-Tmin/max/inc).\n", file);
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "This will yield a subset categorical CPT with [(max-min)/inc] - 1 entries.\n", file);
			return GMT_RUNTIME_ERROR;
		}
	}
	return GMT_NOERROR;
}

char ** gmt_cat_cpt_strings (struct GMT_CTRL *GMT, char *in_label, unsigned int n, unsigned int *n_set) {
	/* Generate categorical labels for n categories from the label magic argument.
	 * Note: If n = 12 and label = M then we create month names.
	 * Note: If n = 7 and label = D then we create day names
	 */
	unsigned int k = 0, kind = 0;
	bool upper = false;
	char all_items[12*GMT_LEN16] = {""};
	char *label = NULL, **Clabel = gmt_M_memory (GMT, NULL, n, char *);

	if (Clabel == NULL) return NULL;
	if (n == 12 && !strcmp (in_label, "M")) {	/* Create a month-list from current defaults */
		gmtlib_set_case_and_kind (GMT, GMT->current.setting.format_time[GMT_PRIMARY], &upper, &kind);
		strcpy (all_items, GMT->current.language.month_name[kind][0]);
		for (k = 1; k < 12; k++) {	/* Append comma-separated list of months in current language, format */
			strcat (all_items, ",");
			strcat (all_items, GMT->current.language.month_name[kind][k]);
		}
		if (upper) gmt_str_toupper (all_items);
		label = all_items;
	}
	else if (n == 7 && !strcmp (in_label, "D")) {	/* Create a weekday-list from current defaults */
		unsigned int day;
		gmtlib_set_case_and_kind (GMT, GMT->current.setting.format_time[GMT_PRIMARY], &upper, &kind);
		day = (GMT->current.setting.time_week_start + GMT_WEEK2DAY_I) % GMT_WEEK2DAY_I;	/* Wrap around */
		strcpy (all_items, GMT->current.language.day_name[kind][day]);
		for (k = 1; k < 7; k++) {	/* Append comma-separated list of weekdays in current language, format */
			day = (k + GMT->current.setting.time_week_start + GMT_WEEK2DAY_I) % GMT_WEEK2DAY_I;	/* Wrap around */
			strcat (all_items, ",");
			strcat (all_items, GMT->current.language.day_name[kind][day]);
		}
		if (upper) gmt_str_toupper (all_items);
		label = all_items;
	}
	else 	/* Pass what we were given as is */
		label = in_label;
	if (strchr (label, ',')) {	/* Got list of category names */
		char *word = NULL, *trail = NULL, *orig = strdup (label);
		trail = orig;	k = 0;
		while ((word = strsep (&trail, ",")) != NULL && k < n) {
			if (*word != '\0')	/* Skip empty strings */
				Clabel[k] = strdup (word);
			k++;
		}
		gmt_M_str_free (orig);
		if (k != n) {
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "The comma-separated string %s had %d entries but %d were expected\n", label, k, n);
		}
	}
	else {	/* Auto-build the labels */
		unsigned int mode;
		int start;
		char string[GMT_LEN64] = {""};
		if (isdigit (label[0])) {	/* Integer categories */
			mode = 1;
			start = atoi (label);
			GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Building %d sequential strings from integers starting at %d\n", n, start);
		}
		else {	/* Letter categories */
			mode = 3;
			start = label[0];
			if (strlen (label) > 1)
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Expected a single letter to initialize auto-labels but found %s.\n", label);
			GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Building %d sequential strings from letters starting at %c\n", n, start);
		}
		if (label[strlen(label)-1] == '-') mode++;	/* Wants a range */
		for (k = 0; k < n; k++) {
			switch (mode) {
				case 1:	/* Single integer label */
					sprintf (string, "%d", start+k);
					break;
				case 2:	/* Integer range label */
					sprintf (string, "%d-%d", start+k, start+k+1);
					break;
				case 3:	/* Single letter label */
					sprintf (string, "%c", start+k);
					break;
				case 4:	/* Character range label */
					sprintf (string, "%c-%c", start+k, start+k+1);
					break;
			}
			Clabel[k] = strdup (string);
		}
	}
	*n_set = k;	/* How many we actually set */
	return Clabel;
}

/*! . */
struct GMT_PALETTE * gmtlib_read_cpt (struct GMT_CTRL *GMT, void *source, unsigned int source_type, unsigned int cpt_flags) {
	/* Opens and reads a color palette file in RGB, HSV, or CMYK of arbitrary length.
	 * Return the result as a palette struct.
	 * source_type can be GMT_IS_[FILE|STREAM|FDESC]
	 * cpt_flags is a combination of:
	 * GMT_CPT_NO_BNF = Suppress reading BFN (i.e. use parameter settings)
	 * GMT_CPT_EXTEND_BNF = Make B and F equal to low and high color
	 */

	unsigned int n = 0, i, nread, annot, id, n_cat_records = 0, color_model, hinge_mode = 0;
	size_t k, L;
	bool gap, overlap, error = false, close_file = false, check_headers = true;
	size_t n_alloc = GMT_SMALL_CHUNK, n_hdr_alloc = 0;
	double dz, z_hinge;
	char T0[GMT_LEN64] = {""}, T1[GMT_LEN64] = {""}, T2[GMT_LEN64] = {""}, T3[GMT_LEN64] = {""}, T4[GMT_LEN64] = {""};
	char T5[GMT_LEN64] = {""}, T6[GMT_LEN64] = {""}, T7[GMT_LEN64] = {""}, T8[GMT_LEN64] = {""}, T9[GMT_LEN64] = {""};
	char line[GMT_BUFSIZ] = {""}, clo[GMT_LEN64] = {""}, chi[GMT_LEN64] = {""}, c, cpt_file[PATH_MAX] = {""};
	char *name = NULL, *h = NULL;
	FILE *fp = NULL;
	struct GMT_PALETTE *X = NULL;
	struct GMT_PALETTE_HIDDEN *XH = NULL;
	struct CPT_Z_SCALE *Z = NULL;	/* For unit manipulations */

	/* Determine input source */

	if (source_type == GMT_IS_FILE) {	/* source is a file name */
		struct stat S;
		strncpy (cpt_file, source, PATH_MAX-1);
		Z = gmtsupport_cpt_parse (GMT, cpt_file, GMT_IN, &hinge_mode, &z_hinge);
		if (strncmp (cpt_file, "/dev/fd/", 8U) && stat (cpt_file, &S) == 0 && S.st_size == 0) {	/* Exclude process substitution files in /dev/fd */
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Color palette table %s is empty\n", cpt_file);
			gmt_M_free (GMT, Z);
			return (NULL);
		}
		if ((fp = fopen (cpt_file, "r")) == NULL) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Cannot open color palette table %s\n", cpt_file);
			gmt_M_free (GMT, Z);
			return (NULL);
		}
		close_file = true;	/* We only close files we have opened here */

	}
	else if (source_type == GMT_IS_STREAM) {	/* Open file pointer given, just copy */
		fp = (FILE *)source;
		if (fp == NULL) fp = GMT->session.std[GMT_IN];	/* Default input */
		if (fp == GMT->session.std[GMT_IN])
			strcpy (cpt_file, "<stdin>");
		else
			strcpy (cpt_file, "<input stream>");
	}
	else if (source_type == GMT_IS_FDESC) {		/* Open file descriptor given, just convert to file pointer */
		int *fd = source;
		if (fd && (fp = fdopen (*fd, "r")) == NULL) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Cannot convert file descriptor %d to stream in gmtlib_read_cpt\n", *fd);
			return (NULL);
		}
		else
			close_file = true;	/* fdopen allocates memory */
		if (fd == NULL) fp = GMT->session.std[GMT_IN];	/* Default input */
		if (fp == GMT->session.std[GMT_IN])
			strcpy (cpt_file, "<stdin>");
		else
			strcpy (cpt_file, "<input file descriptor>");
	}
	else {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Unrecognized source type %d in gmtlib_read_cpt\n", source_type);
		return (NULL);
	}

	GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Reading CPT from %s\n", cpt_file);

	X = gmtlib_create_palette (GMT, 0);
	X->data = gmt_M_memory (GMT, NULL, n_alloc, struct GMT_LUT);
	X->mode = cpt_flags;	/* Maybe limit what to do with BFN selections */
	color_model = GMT->current.setting.color_model;		/* Save the original setting since it may be modified by settings in the CPT */
	/* Also: GMT->current.setting.color_model is used in some rgb_to_xxx functions so it must be set if changed by cpt */
	X->is_gray = X->is_bw = true;	/* May be changed when reading the actual colors */
	XH = gmt_get_C_hidden (X);
	/* Set default BFN colors; these may be overwritten by things in the CPT */
	for (id = 0; id < 3; id++) {
		gmt_M_rgb_copy (X->bfn[id].rgb, GMT->current.setting.color_patch[id]);
		gmt_rgb_to_hsv (X->bfn[id].rgb, X->bfn[id].hsv);
		if (X->bfn[id].rgb[0] == -1.0) X->bfn[id].skip = true;
		if (X->is_gray && !gmt_M_is_gray (X->bfn[id].rgb)) X->is_gray = X->is_bw = false;
		if (X->is_bw && !gmt_M_is_bw(X->bfn[id].rgb)) X->is_bw = false;
	}

	while (!error && fgets (line, GMT_BUFSIZ, fp)) {
		gmt_strstrip (line, true);
		c = line[0];

		if (strstr (line, "COLOR_MODEL")) {	/* CPT overrides default color model */
			if (strstr (line, "+RGB") || strstr (line, "rgb"))
				X->model = GMT_RGB | GMT_COLORINT;
			else if (strstr (line, "RGB"))
				X->model = GMT_RGB;
			else if (strstr (line, "+GRAY") || strstr (line, "gray"))
				X->model = GMT_GRAY | GMT_COLORINT;
			else if (strstr (line, "+HSV") || strstr (line, "hsv"))
				X->model = GMT_HSV | GMT_COLORINT;
			else if (strstr (line, "HSV"))
				X->model = GMT_HSV;
			else if (strstr (line, "+CMYK") || strstr (line, "cmyk"))
				X->model = GMT_CMYK | GMT_COLORINT;
			else if (strstr (line, "CMYK"))
				X->model = GMT_CMYK;
			else {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Unrecognized COLOR_MODEL in color palette table %s\n", cpt_file);
				if (close_file) fclose (fp);
				if (Z) gmt_M_free (GMT, Z);
				gmtlib_free_palette (GMT, &X);
				return (NULL);
			}
			continue;	/* Don't want this instruction to be also kept as a comment */
		}
		else if (strstr (line, "HINGE")) {	/* CPT has either a soft or hard hinge */
			if (strstr (line, "HINGE =")) {	/* Bad mix of old CPTs with new GMT parsing - treat as hard hinge */
				GMT_Report (GMT->parent, GMT_MSG_WARNING, "Mixing old CPT master tables with HINGE = <value> in %s.  Interpreted as HARD_HINGE.\n", cpt_file);
				X->mode |= GMT_CPT_HARD_HINGE;
				X->has_hinge = 1;
			}
			else if (strstr (line, "HARD_HINGE")) {	/* Hard hinge is always active */
				X->mode |= GMT_CPT_HARD_HINGE;
				X->has_hinge = 1;
			}
			else if (strstr (line, "SOFT_HINGE"))	/* Soft hinge the user can activate to a hard hinge via +h[<value>] */
				X->mode |= GMT_CPT_SOFT_HINGE;
			continue;	/* Don't want this instruction to be also kept as a comment */
		}
		else if ((h = strstr (line, "RANGE ="))) {	/* CPT has a default range */
			k = 7;	while (h[k] == ' ' || h[k] == '\t') k++;	/* Skip any leading spaces or tabs */
			if (sscanf (&h[k], "%[^/]/%s", T1, T2) != 2) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Could not parse RANGE [%s] in %s\n", &h[7], cpt_file);
				if (close_file) fclose (fp);
				if (Z) gmt_M_free (GMT, Z);
				gmtlib_free_palette (GMT, &X);
				return (NULL);
			}
			gmt_scanf_arg (GMT, T1, GMT_IS_UNKNOWN, false, &X->minmax[0]);
			gmt_scanf_arg (GMT, T2, GMT_IS_UNKNOWN, false, &X->minmax[1]);
			X->has_range = 1;
			continue;	/* Don't want this instruction to be also kept as a comment */
		}
		else if ((h = strstr (line, "CYCLIC")))	/* CPT should wrap around */
			X->is_wrapping = 1;
		else if ((h = strstr (line, "ENABLE_B_OPTION")))	/* CPT was stretched to exact min/max with no dz rounding */
			XH->auto_scale = 1;
		else if ((h = strstr (line, "COLOR_LIST")))	/* CPT was created from a list of colors */
			X->mode |= GMT_CPT_COLORLIST;

		GMT->current.setting.color_model = X->model;

		if (c == '#') {	/* Possibly a header/comment record */
			if (GMT->common.h.mode == GMT_COMMENT_IS_RESET) continue;	/* Simplest way to replace headers on output is to ignore them on input */
			if (!check_headers) continue;	/* Done with the initial header records */
			if (n_hdr_alloc == 0) X->header = gmt_M_memory (GMT, X->header, (n_hdr_alloc = GMT_TINY_CHUNK), char *);
			X->header[X->n_headers] = strdup (line);
			X->n_headers++;
			if (X->n_headers >= n_hdr_alloc) X->header = gmt_M_memory (GMT, X->header, (n_hdr_alloc += GMT_TINY_CHUNK), char *);
			continue;
		}
		if (c == '\0' || c == '\n') continue;	/* Comment or blank */
		check_headers = false;	/* First non-comment record signals the end of headers */

		gmt_chop (line);	/* Chop '\r\n' */

		T1[0] = T2[0] = T3[0] = T4[0] = T5[0] = T6[0] = T7[0] = T8[0] = T9[0] = 0;
		switch (c) {	/* Must check that B,F,N is a single word */
			case 'B':
				id = (line[1] == ' ' || line[1] == '\t') ? GMT_BGD : 3;
				break;
			case 'F':
				id = (line[1] == ' ' || line[1] == '\t') ? GMT_FGD : 3;
				break;
			case 'N':
				id = (line[1] == ' ' || line[1] == '\t') ? GMT_NAN : 3;
				break;
			default:
				id = 3;
				break;
		}

		if (id <= GMT_NAN) {	/* Foreground, background, or nan color */
			if (X->mode & GMT_CPT_NO_BNF) continue; /* Suppress parsing B, F, N lines when bit 0 of X->mode is set */
			X->bfn[id].skip = false;
			if ((nread = sscanf (&line[2], "%s %s %s %s", T1, T2, T3, T4)) < 1) error = true;
			if (T1[0] == '-')	/* Skip this slice */
				X->bfn[id].skip = true;
			else if (gmtsupport_is_pattern (GMT, T1)) {	/* Gave a pattern */
				X->bfn[id].fill = gmt_M_memory (GMT, NULL, 1, struct GMT_FILL);
				if (gmt_getfill (GMT, T1, X->bfn[id].fill)) {
					GMT_Report (GMT->parent, GMT_MSG_ERROR, "CPT Pattern fill (%s) not understood!\n", T1);
					if (close_file) fclose (fp);
					if (Z) gmt_M_free (GMT, Z);
					gmtlib_free_palette (GMT, &X);
					return (NULL);
				}
				X->has_pattern = true;
				if ((name = gmtsupport_get_userimagename (GMT, T1, cpt_file))) {	/* Must replace fill->pattern with this full path */
					strncpy (X->bfn[id].fill->pattern, name, PATH_MAX-1);
					gmt_M_str_free (name);
				}
			}
			else {	/* Shades, RGB, HSV, or CMYK */
				if (nread == 1)	/* Gray shade */
					snprintf (clo, GMT_LEN64, "%s", T1);
				else if (X->model & GMT_CMYK)
					snprintf (clo, GMT_LEN64, "%s/%s/%s/%s", T1, T2, T3, T4);
				else if (X->model & GMT_HSV)
					snprintf (clo, GMT_LEN64, "%s-%s-%s", T1, T2, T3);
				else
					snprintf (clo, GMT_LEN64, "%s/%s/%s", T1, T2, T3);
				if (X->model & GMT_HSV) {
					if (gmtsupport_gethsv (GMT, clo, X->bfn[id].hsv)) error = true;
					gmt_hsv_to_rgb (X->bfn[id].rgb, X->bfn[id].hsv);
				}
				else {
					if (gmt_getrgb (GMT, clo, X->bfn[id].rgb)) error = true;
					gmt_rgb_to_hsv (X->bfn[id].rgb, X->bfn[id].hsv);
				}
				if (X->is_gray && !gmt_M_is_gray (X->bfn[id].rgb)) X->is_gray = X->is_bw = false;
				if (X->is_bw && !gmt_M_is_bw(X->bfn[id].rgb)) X->is_bw = false;
			}
			continue;
		}

		if (hinge_mode && ((X->mode & GMT_CPT_SOFT_HINGE) || (X->mode & GMT_CPT_HARD_HINGE))) { /* Activate a soft hinge for the CPT and/or adjust the hinge */
			X->has_hinge = 1;
			X->hinge = z_hinge;	/* This is now the user-selected hinge value */
		}

		/* Here we have regular z-slices.  Allowable formats are
		 *
		 * key <fill> [;<label>]	for categorical data
		 * z0 - z1 - [LUB] [;<label>]
		 * z0 pattern z1 - [LUB] [;<label>]
		 * z0 r0 z1 r1 [LUB] [;<label>]
		 * z0 r0 g0 b0 z1 r1 g1 b1 [LUB] [;<label>]
		 * z0 h0 s0 v0 z1 h1 s1 v1 [LUB] [;<label>]
		 * z0 c0 m0 y0 k0 z1 c1 m1 y1 k1 [LUB] [;<label>]
		 *
		 * z can be in any format (float, dd:mm:ss, dateTclock)
		 */

		/* First determine if a label is given */

		if ((k = strcspn(line, ";")) && line[k] != '\0') {
			char string[GMT_LEN64] = {""};
			/* OK, find the label and chop it off */
			strcpy (string, &line[k+1]);
			gmt_chop (string);	/* Strip off trailing return */
			X->data[n].label = strdup (string);
			k--;	/* Position before ; */
			while (k && (line[k] == '\t' || line[k] == ' ')) k--;
			line[k+1] = '\0';	/* Chop label and trailing white space off from line */
			XH->alloc_mode_text[GMT_CPT_INDEX_LBL] = GMT_ALLOC_INTERNALLY;
		}

		/* Determine if psscale need to label these steps by looking for the optional single L|U|B character at the end */

		L = strlen(line) - 1;   /* Position in line of last character. Will be 0 if just L|U|B */
		/* Must check previous char since hex colors like #5CC3EB should not trigger on 'B' */
		if (L > 0 && strchr (" \t", line[L-1])) {   /* Got a single character - check if L|U|B */
			c = line[L];
			if (c == 'L')
				X->data[n].annot = GMT_CPT_L_ANNOT;
			else if (c == 'U')
				X->data[n].annot = GMT_CPT_U_ANNOT;
			else if (c == 'B')
				X->data[n].annot = GMT_CPT_B_ANNOT;
			if (X->data[n].annot) line[strlen(line)-1] = '\0';	/* Chop off this information so it does not affect our column count below */
		}

		nread = sscanf (line, "%s %s %s %s %s %s %s %s %s %s", T0, T1, T2, T3, T4, T5, T6, T7, T8, T9);	/* Hope to read 4, 8, or 10 fields */

		if (nread <= 0) continue;	/* Probably a line with spaces - skip */
		if (X->model & GMT_CMYK && nread != 10) error = true;	/* CMYK should results in 10 fields */
		if (!(X->model & GMT_CMYK) && !(nread == 2 || nread == 4 || nread == 8)) error = true;	/* HSV or RGB should result in 8 fields, gray, patterns, or skips in 4 */
		if (nread == 2 && gmt_not_numeric (GMT, T0)) {	/* Truly categorical CPT with named key */
			X->data[n].z_low = n;	/* Just use counter as z value dummy */
			X->data[n].key = (T0[0] == '\\') ? strdup (&T0[1]) : strdup (T0);	/* Skip escape: For user to have a name like B it must be \B to avoid conflict with BNF settings*/
			X->categorical |= GMT_CPT_CATEGORICAL_KEY;	/* Flag this type of CPT */
			XH->alloc_mode_text[GMT_CPT_INDEX_KEY] = GMT_ALLOC_INTERNALLY;
		}
		else {	/* Floating point lookup values */
			gmt_scanf_arg (GMT, T0, GMT_IS_UNKNOWN, false, &X->data[n].z_low);
			if (strchr (T0, 'T')) X->mode |= GMT_CPT_TIME;
		}
		X->data[n].skip = false;
		if (T1[0] == '-') {				/* Skip this slice */
			if (nread != 4) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "z-slice to skip not in [z0 - z1 -] format!\n");
				if (close_file) fclose (fp);
				if (Z) gmt_M_free (GMT, Z);
				gmtlib_free_palette (GMT, &X);
				return (NULL);
			}
			gmt_scanf_arg (GMT, T2, GMT_IS_UNKNOWN, false, &X->data[n].z_high);
			X->data[n].skip = true;		/* Don't paint this slice if possible*/
			gmt_M_rgb_copy (X->data[n].rgb_low,  GMT->current.setting.ps_page_rgb);	/* If we must paint, use page color */
			gmt_M_rgb_copy (X->data[n].rgb_high, GMT->current.setting.ps_page_rgb);
		}
		else if (gmtsupport_is_pattern (GMT, T1)) {	/* Gave pattern fill */
			X->data[n].fill = gmt_M_memory (GMT, NULL, 1, struct GMT_FILL);
			if (gmt_getfill (GMT, T1, X->data[n].fill)) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "CPT Pattern fill (%s) not understood!\n", T1);
				if (close_file) fclose (fp);
				if (Z) gmt_M_free (GMT, Z);
				gmtlib_free_palette (GMT, &X);
				return (NULL);
			}
			else if (nread == 2) {	/* Categorical cpt records with key fill [;label] */
				X->data[n].z_high = X->data[n].z_low;
				n_cat_records++;
				X->categorical |= GMT_CPT_CATEGORICAL_VAL;
			}
			else if (nread == 4) {
				gmt_scanf_arg (GMT, T2, GMT_IS_UNKNOWN, false, &X->data[n].z_high);
			}
			else {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "z-slice with pattern fill not in [z0 pattern z1 -] format!\n");
				if (close_file) fclose (fp);
				if (Z) gmt_M_free (GMT, Z);
				gmtlib_free_palette (GMT, &X);
				return (NULL);
			}
			X->has_pattern = true;
			if ((name = gmtsupport_get_userimagename (GMT, T1, cpt_file))) {	/* Must replace fill->pattern with this full path */
				strncpy (X->data[n].fill->pattern, name, PATH_MAX-1);
				gmt_M_str_free (name);
			}
		}
		else {						/* Shades, RGB, HSV, or CMYK */
			if (nread == 2) {	/* Categorical cpt records with key fill [;label] */
				X->data[n].z_high = X->data[n].z_low;
				snprintf (clo, GMT_LEN64, "%s", T1);
				sprintf (chi, "-");
				n_cat_records++;
				X->categorical |= GMT_CPT_CATEGORICAL_VAL;
			}
			else if (nread == 4) {	/* gray shades or color names */
				gmt_scanf_arg (GMT, T2, GMT_IS_UNKNOWN, false, &X->data[n].z_high);
				snprintf (clo, GMT_LEN64, "%s", T1);
				snprintf (chi, GMT_LEN64, "%s", T3);
			}
			else if (X->model & GMT_CMYK) {
				gmt_scanf_arg (GMT, T5, GMT_IS_UNKNOWN, false, &X->data[n].z_high);
				snprintf (clo, GMT_LEN64, "%s/%s/%s/%s", T1, T2, T3, T4);
				snprintf (chi, GMT_LEN64, "%s/%s/%s/%s", T6, T7, T8, T9);
			}
			else if (X->model & GMT_HSV) {
				gmt_scanf_arg (GMT, T4, GMT_IS_UNKNOWN, false, &X->data[n].z_high);
				snprintf (clo, GMT_LEN64, "%s-%s-%s", T1, T2, T3);
				snprintf (chi, GMT_LEN64, "%s-%s-%s", T5, T6, T7);
			}
			else {			/* RGB */
				gmt_scanf_arg (GMT, T4, GMT_IS_UNKNOWN, false, &X->data[n].z_high);
				snprintf (clo, GMT_LEN64, "%s/%s/%s", T1, T2, T3);
				snprintf (chi, GMT_LEN64, "%s/%s/%s", T5, T6, T7);
			}
			if (X->model & GMT_HSV) {
				if (gmtsupport_gethsv (GMT, clo, X->data[n].hsv_low)) error = true;
				if (!strcmp (chi, "-"))	/* Duplicate first color */
					gmt_M_memcpy (X->data[n].hsv_high, X->data[n].hsv_low, 4, double);
				else if (gmtsupport_gethsv (GMT, chi, X->data[n].hsv_high)) error = true;
				gmt_hsv_to_rgb (X->data[n].rgb_low,  X->data[n].hsv_low);
				gmt_hsv_to_rgb (X->data[n].rgb_high, X->data[n].hsv_high);
			}
			else {
				if (gmt_getrgb (GMT, clo, X->data[n].rgb_low)) error = true;
				if (!strcmp (chi, "-"))	/* Duplicate first color */
					gmt_M_memcpy (X->data[n].rgb_high, X->data[n].rgb_low, 4, double);
				else if (gmt_getrgb (GMT, chi, X->data[n].rgb_high)) error = true;
				gmt_rgb_to_hsv (X->data[n].rgb_low,  X->data[n].hsv_low);
				gmt_rgb_to_hsv (X->data[n].rgb_high, X->data[n].hsv_high);
			}
			if (!X->categorical) {
				dz = X->data[n].z_high - X->data[n].z_low;
				if (dz <= 0.0) {
					GMT_Report (GMT->parent, GMT_MSG_ERROR, "Z-slice around line %d with dz <= 0\n", n);
					if (Z) gmt_M_free (GMT, Z);
					gmtlib_free_palette (GMT, &X);
					if (close_file) fclose (fp);
					return (NULL);
				}
				X->data[n].i_dz = 1.0 / dz;
			}
			/* Is color map continuous, gray or b/w? */
			if (X->is_gray && !(gmt_M_is_gray (X->data[n].rgb_low) && gmt_M_is_gray (X->data[n].rgb_high))) X->is_gray = X->is_bw = false;
			if (X->is_bw && !(gmt_M_is_bw(X->data[n].rgb_low) && gmt_M_is_bw(X->data[n].rgb_high))) X->is_bw = false;

			/* Differences used in gmt_get_rgb_from_z */
			for (i = 0; i < 4; i++) X->data[n].rgb_diff[i] = X->data[n].rgb_high[i] - X->data[n].rgb_low[i];
			for (i = 0; i < 4; i++) X->data[n].hsv_diff[i] = X->data[n].hsv_high[i] - X->data[n].hsv_low[i];

			if (X->model & GMT_HSV) {
				if (!X->is_continuous && !gmt_M_same_rgb(X->data[n].hsv_low,X->data[n].hsv_high)) X->is_continuous = true;
			}
			else {
				if (!X->is_continuous && !gmt_M_same_rgb(X->data[n].rgb_low,X->data[n].rgb_high)) X->is_continuous = true;
			/* When HSV is converted from RGB: avoid interpolation over hue differences larger than 180 degrees;
			   take the shorter distance instead. This does not apply for HSV color tables, since there we assume
			   that the H values are intentional and one might WANT to interpolate over more than 180 degrees. */
				if (X->data[n].hsv_diff[0] < -180.0) X->data[n].hsv_diff[0] += 360.0;
				if (X->data[n].hsv_diff[0] >  180.0) X->data[n].hsv_diff[0] -= 360.0;
			}
		}

		n++;
		if (n == n_alloc) {
			size_t old_n_alloc = n_alloc;
			n_alloc <<= 1;
			X->data = gmt_M_memory (GMT, X->data, n_alloc, struct GMT_LUT);
			gmt_M_memset (&(X->data[old_n_alloc]), n_alloc - old_n_alloc, struct GMT_LUT);	/* Initialize new structs to zero */
		}
	}

	if (close_file) fclose (fp);

	if (X->mode & GMT_CPT_EXTEND_BNF) {	/* Use low and high colors as back and foreground */
		gmt_M_rgb_copy (X->bfn[GMT_BGD].rgb, X->data[0].rgb_low);
		gmt_M_rgb_copy (X->bfn[GMT_FGD].rgb, X->data[n-1].rgb_high);
		gmt_M_rgb_copy (X->bfn[GMT_BGD].hsv, X->data[0].hsv_low);
		gmt_M_rgb_copy (X->bfn[GMT_FGD].hsv, X->data[n-1].hsv_high);
	}

	if (X->categorical && n_cat_records != n) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Cannot decode %s as categorical CPT\n", cpt_file);
		if (Z) gmt_M_free (GMT, Z);
		gmtlib_free_palette (GMT, &X);
		return (NULL);
	}
	if (error) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Failed to decode %s\n", cpt_file);
		if (Z) gmt_M_free (GMT, Z);
		gmtlib_free_palette (GMT, &X);
		return (NULL);
	}
	if (n == 0) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "CPT %s has no z-slices!\n", cpt_file);
		if (Z) gmt_M_free (GMT, Z);
		gmtlib_free_palette (GMT, &X);
		return (NULL);
	}

	if (n < n_alloc) X->data = gmt_M_memory (GMT, X->data, n, struct GMT_LUT);
	X->n_colors = n;

	/* The master gray.cpt has only one slice and hence it comes out as both gray & bw, but it can only be one of them. */
	if (X->n_colors == 1 && X->is_gray && X->is_bw) X->is_bw = false;	/* Prefer gray over bw (would crash grdimage with externals). */

	if (X->categorical) {	/* Set up fake ranges so CPT is continuous */
		dz = 1.0;	/* This will presumably get reset in the loop */
		for (i = 0; i < X->n_colors; i++) {
			X->data[i].z_high = (i == (X->n_colors-1)) ? X->data[i].z_low + dz : X->data[i+1].z_low;
			dz = X->data[i].z_high - X->data[i].z_low;
			if (dz <= 0.0) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Z-slice around line %d with dz <= 0\n", i);
				return (NULL);
			}
			X->data[i].i_dz = 1.0 / dz;
		}
		/* Add special flag since this CPT is basically a list of colors */
		X->mode |= GMT_CPT_COLORLIST;
	}
	X->wrap_length = X->data[X->n_colors-1].z_high - X->data[0].z_low;

	for (i = annot = 0, gap = overlap = false; i < X->n_colors - 1; i++) {
		dz = X->data[i].z_high - X->data[i+1].z_low;
		if (dz < -GMT_CONV12_LIMIT) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Color palette table %s has a gap of size %g between slices %d and %d!\n", cpt_file, -dz, i, i+1);
			gap = true;
		}
		else if (dz > GMT_CONV12_LIMIT) {
			overlap = true;
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Color palette table %s has an overlap of size %g between slices %d and %d\n", cpt_file, dz, i, i+1);
		}
		else if (fabs (dz) > 0.0) {	/* Split the tiny difference across the two values */
			dz *= 0.5;
			X->data[i].z_high -= dz;
			X->data[i+1].z_low += dz;
		}
		annot += X->data[i].annot;
	}
	annot += X->data[i].annot;
	if (gap || overlap) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Must abort due to above errors in %s\n", cpt_file);
		for (i = 0; i < X->n_colors; i++) {
			gmt_M_free (GMT, X->data[i].fill);
			gmt_M_str_free (X->data[i].label);
		}
		gmtlib_free_palette (GMT, &X);
		gmt_M_free (GMT, Z);
		return (NULL);
	}

	if (!annot) {	/* Must set default annotation flags */
		for (i = 0; i < X->n_colors; i++) X->data[i].annot = GMT_CPT_L_ANNOT;
		X->data[i-1].annot = GMT_CPT_B_ANNOT;
	}

	/* Reset the color model to what it was in the GMT defaults when a + is used there. */
	if (color_model & GMT_COLORINT) GMT->current.setting.color_model = color_model;

	if (X->n_headers < n_hdr_alloc) X->header = gmt_M_memory (GMT, X->header, X->n_headers, char *);

	if (Z) {
		gmtsupport_cpt_z_scale (GMT, X, Z, GMT_IN);
		gmt_M_free (GMT, Z);
	}

	return (X);
}

char * gmt_cpt_default (struct GMTAPI_CTRL *API, char *cpt, char *file, struct GMT_GRID_HEADER *h) {
	/* Return which type of default CPT this data set should use.
	 * If cpt is specified then that is what we will use. If not, then
	 * we determine if file is a remote data set, and if it is and has a
	 * default CPT then we use that, else we return NULL which means use
	 * the GMT default CPT given by GMT->current.setting.cpt */
	int k_data;
	static char *srtm_cpt = "srtm";
	char *curr_cpt = NULL;
	struct GMT_GRID_HEADER_HIDDEN *HH = gmt_get_H_hidden (h);

	if (cpt) {
		GMT_Report (API, GMT_MSG_INFORMATION, "gmt_cpt_default: Use specific CPT: %s\n", cpt);
		return strdup (cpt);	/* CPT was already specified, so use it */
	}
	if (file == NULL) {
		GMT_Report (API, GMT_MSG_INFORMATION, "gmt_cpt_default: No file given so cannot determine\n");
		return NULL;	/* No file given, so nothing to work with */
	}
	if (API->GMT->current.setting.run_mode == GMT_MODERN && (curr_cpt = gmt_get_current_item (API->GMT, "cpt", false))) {
		GMT_Report (API, GMT_MSG_INFORMATION, "gmt_cpt_default: Use current CPT: %s\n", curr_cpt);
		return curr_cpt;	/* Use current CPT */
	}
	if (HH->cpt && HH->cpt[0] != '-') {
		GMT_Report (API, GMT_MSG_INFORMATION, "gmt_cpt_default: Use grid header default CPT: %s\n", HH->cpt);
		return (strdup (HH->cpt));	/* Found default CPT in the grid header */
	}

	/* Check if we are reading a remote dataset with a default CPT */
	if ((k_data = gmt_remote_dataset_id (API, file)) == GMT_NOTSET) {
		size_t LOX;
		if ((k_data = gmt_get_tile_id (API, file)) == GMT_NOTSET)
			return NULL;	/* Go with the default, whatever that is */
		LOX = strlen (file) - 8;	/* Position of the L|O|X flag */
		if (file[LOX] == 'L') {
			GMT_Report (API, GMT_MSG_INFORMATION, "gmt_cpt_default: Use SRTM default CPT: %s\n", srtm_cpt);
			return strdup (srtm_cpt);
		}
	}
	if (API->remote_info[k_data].CPT[0] == '-') {
			GMT_Report (API, GMT_MSG_INFORMATION, "gmt_cpt_default: No CPT default for remote dataset %s\n", file);
		return (NULL);
	}

	GMT_Report (API, GMT_MSG_INFORMATION, "gmt_cpt_default: Use dataset default CPT: %s\n", API->remote_info[k_data].CPT);
	return (strdup (API->remote_info[k_data].CPT));
}

char *gmt_is_cpt_master (struct GMT_CTRL *GMT, char *cpt) {
	/* If cpt is the name of a GMT CPT master table, return that name, otherwise NULL */
	char *c = NULL, *f = NULL, *master = NULL;
	if (!cpt || !cpt[0]) return gmtsupport_cpt_master_index (GMT, GMT->current.setting.cpt);	/* No cpt given means use GMT->current.setting.cpt master */
	if (gmt_M_file_is_memory (cpt)) return NULL;	/* A CPT was given via memory location so cannot be a master reference */
	if ((f = gmt_strrstr (cpt, GMT_CPT_EXTENSION)))	/* Only examine modifiers from there onwards */
		c = gmtlib_last_valid_file_modifier (GMT->parent, f, GMT_CPTFILE_MODIFIERS);
	else	/* Must examine the entire file name for modifiers */
		c = gmtlib_last_valid_file_modifier (GMT->parent, cpt, GMT_CPTFILE_MODIFIERS);
	if (c && (f = gmt_first_modifier (GMT, c, GMT_CPTFILE_MODIFIERS)))
		f[0] = '\0';	/* Must chop off modifiers for further checks to work */
	if (gmt_access (GMT, cpt, R_OK)) master = gmtsupport_cpt_master_index (GMT, cpt);
	if (c && f) f[0] = '+';	/* Restore modifier before we return */
	return master;
}

int gmtlib_set_current_item_file (struct GMT_CTRL *GMT, const char *item, char *file) {
	char panel[GMT_LEN16] = {""};
	int fig, subplot, inset;

	if (GMT->current.setting.run_mode == GMT_CLASSIC) {	/* Must be more careful */
		if (!strncmp (item, "cpt", 3U)) return (GMT_FILE_NOT_FOUND);	/* Current CPT not available in classic mode */
		snprintf (file, PATH_MAX, "%s/%s-gmt.%s", GMT->parent->tmp_dir, GMT->parent->session_name, item);	/* Global file in the tmp dir only */
		return (GMT_NOERROR);
	}

	gmtlib_get_graphics_item (GMT->parent, &fig, &subplot, panel, &inset);	/* Determine the graphics item */

	/* Set the correct output file name given the graphics item */
	if (inset)	/* Only one inset may be active at any given time */
		snprintf (file, PATH_MAX, "%s/gmt.inset.%s", GMT->parent->gwf_dir, item);
	else if (subplot & GMT_SUBPLOT_ACTIVE) {	/* Either subplot master or a panel-specific item */
		if (subplot & GMT_PANEL_NOTSET)	/* Master for all subplot panels */
			snprintf (file, PATH_MAX, "%s/gmt.%d.subplot.%s", GMT->parent->gwf_dir, fig, item);
		else	/* item for just this subplot */
			snprintf (file, PATH_MAX, "%s/gmt.%d.panel.%s.%s", GMT->parent->gwf_dir, fig, panel, item);
	}
	else if (fig)	/* Limited to one figure only */
		snprintf (file, PATH_MAX, "%s/gmt.%d.%s", GMT->parent->gwf_dir, fig, item);
	else
		snprintf (file, PATH_MAX, "%s/gmt.%s", GMT->parent->gwf_dir, item);
	return (GMT_NOERROR);
}

void gmt_save_current_cpt (struct GMT_CTRL *GMT, struct GMT_PALETTE *P, unsigned int cpt_flags) {
	char file[PATH_MAX] = {""};

	if (gmtlib_set_current_item_file (GMT, "cpt", file) == GMT_FILE_NOT_FOUND) return;

	if (GMT_Write_Data (GMT->parent, GMT_IS_PALETTE, GMT_IS_FILE, GMT_IS_NONE, cpt_flags, NULL, file, P) != GMT_NOERROR)
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Unable to save current CPT file to %s !\n", file);
	else
		GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Save current CPT file to %s !\n", file);
}

char *gmt_get_current_item (struct GMT_CTRL *GMT, const char *item, bool strict) {
	/* If modern and a current item file exists, allocate a string with its name and return, else NULL.
	 * Currently, item can be cpt.
	 * if strict is true the file must be available for the current item, otherwise we may look up the hierarchical chain */
	char path[PATH_MAX] = {""}, panel[GMT_LEN16] = {""}, *file = NULL;
	int fig, subplot, inset;

	if (GMT->current.setting.run_mode == GMT_CLASSIC) {	/* A few more checks */
		if (!strncmp (item, "cpt", 3U)) return NULL;	/* Current CPT concept not available in classic mode */
		/* For gridlines we must use a global file in the tmp dir */
		snprintf (path, PATH_MAX, "%s/%s-gmt.%s", GMT->parent->tmp_dir, GMT->parent->session_name, item);
		if (!access (path, R_OK)) file = strdup (path);	/* Yes, found it */
		if (strict && file == NULL) goto FOUND_NOTHING;
	}

	/* Modern mode */

	gmtlib_get_graphics_item (GMT->parent, &fig, &subplot, panel, &inset);	/* Determine the cpt level */
	/* Find the appropriate graphics item for where we are but may have to go up the hierarchy */

	if (inset) {	/* See if an inset item exists */
		snprintf (path, PATH_MAX, "%s/gmt.inset.%s", GMT->parent->gwf_dir, item);
		if (!file && !access (path, R_OK)) file = strdup (path);	/* Yes, found it */
		if (strict && file == NULL) goto FOUND_NOTHING;
	}
	if (!file && (subplot & GMT_SUBPLOT_ACTIVE)) {	/* Nothing yet, see if subplot has one */
		if ((subplot & GMT_PANEL_NOTSET) == 0) {	/* Panel-specific item available? */
			snprintf (path, PATH_MAX, "%s/gmt.%d.panel.%s.%s", GMT->parent->gwf_dir, fig, panel, item);
			if (!access (path, R_OK)) file = strdup (path);	/* Yes, found it */
			if (strict && file == NULL) goto FOUND_NOTHING;
		}
		if (!file) {	/* No, try subplot master item instead? */
			snprintf (path, PATH_MAX, "%s/gmt.%d.subplot.%s", GMT->parent->gwf_dir, fig, item);
			if (!access (path, R_OK)) file = strdup (path);	/* Yes, found it */
			if (strict && file == NULL) goto FOUND_NOTHING;
		}
	}
	if (!file && fig) {	/* Not found an item file yet, so try one for this specific figure */
		snprintf (path, PATH_MAX, "%s/gmt.%d.%s", GMT->parent->gwf_dir, fig, item);
		if (!access (path, R_OK)) file = strdup (path);	/* Yes, found it */
		if (strict && file == NULL) goto FOUND_NOTHING;
	}
	if (!file) {	/* Not found an item file yet, finally try the session master */
		snprintf (path, PATH_MAX, "%s/gmt.%s", GMT->parent->gwf_dir, item);
		if (!access (path, R_OK)) file = strdup (path);	/* Yes, found it */
		if (strict && file == NULL) goto FOUND_NOTHING;
	}
	if (file) {
		GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Selected current %s file %s\n", file, item);
		return (file);
	}

FOUND_NOTHING:
	GMT_Report (GMT->parent, GMT_MSG_DEBUG, "No current %s file found\n", item);
	return (NULL);
}

/*! . */
struct GMT_PALETTE *gmt_get_palette (struct GMT_CTRL *GMT, char *file, enum GMT_enum_cpt mode, double zmin, double zmax, double dz) {
	/* Will read in a CPT.  However, if file does not exist in the current directory we may provide
	   a CPT for quick/dirty work provided mode == GMT_CPT_OPTIONAL and hence zmin/zmax are set to the desired data range */

	struct GMT_PALETTE *P = NULL;
	unsigned int continuous = (file && strchr(file,',')), first = 0;
	char *master = NULL;

	if (mode == GMT_CPT_REQUIRED) {	/* The calling function requires the CPT to be present; GMT_Read_Data will work or fail accordingly */
		P = GMT_Read_Data (GMT->parent, GMT_IS_PALETTE, GMT_IS_FILE, GMT_IS_NONE, GMT_READ_NORMAL|continuous, NULL, file, NULL);
		if (GMT->parent->gwf_dir == NULL || file == NULL || strstr (file, GMT->parent->gwf_dir) == NULL)	/* Avoid writing a sessions CPT to a sessions CPT */
			gmt_save_current_cpt (GMT, P, 0);	/* Save for use by session, if modern mode */
		return (P);
	}

	/* Here, the cpt is optional (mode == GMT_CPT_OPTIONAL).  There are four possibilities:
	   1. A cpt in current directory is given - simply read it and return.
	   2. file is NULL and runmode is classic and hence we default to master CPT name GMT->init.cpt[GMT_DEFAULT_CPT] (or a type-specific CPT).
	   3. file is NULL and runmode is modern and a current cpt exists - use it.
	   4. A specific master CPT name is given. If this does not exist then things will fail in GMT_makecpt.

	   For 2 & 3 we take the master table and linearly stretch the z values to fit the range, or honor default range for dynamic CPTs.
	*/

	if (gmt_file_is_cache (GMT->parent, file))	/* Must be a cache file */
		first = gmt_download_file_if_not_found (GMT, file, 0);
	if (first == 0)	/* Check if given a master or a real file */
		master = gmt_is_cpt_master (GMT, file);
	if (master) {	/* Take master cpt and stretch to fit data range using continuous colors */
		char *current_cpt = NULL;
		double noise;
		struct GMT_PALETTE_HIDDEN *PH = NULL;

		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "CPT argument %s understood to be a master table\n", file);
		if (gmt_M_is_dnan (zmin) || gmt_M_is_dnan (zmax)) {	/* Safety valve 1 */
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "All data points are NaNs so cannot do meaningful automatic CPT generation\n");
			zmin = 0.0;	zmax = 1.0;	/* Does not matter since only NaN color will be used */
		}
		if (zmax <= zmin) {	/* Safety valve 2 [min == max] */
			/* Have a constant grid or a mask grid with NaNs and a constant [1] - adjust min or max so that we can do an automatic CPT */
			if (zmin > 0.0)	/* Both are positive so just increase max */
				zmax = 2.0 * zmin;
			else if (zmin < 0.0)	/* Both are negative so just decrease min */
				zmin = 2.0 * zmax;
			else	/* All zeros, must set max to 1 */
				zmax = 1.0;
			GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Found zmax == zmin, replaced with %lg and %lg to allow automatic CPT generation!\n", zmin, zmax);
		}

		if (file == NULL && (current_cpt = gmt_get_current_item (GMT, "cpt", false))) {	/* There is a current CPT in modern mode */
			P = GMT_Read_Data (GMT->parent, GMT_IS_PALETTE, GMT_IS_FILE, GMT_IS_NONE, GMT_READ_NORMAL, NULL, current_cpt, NULL);
			gmt_M_str_free (current_cpt);
			return (P);
		}

		master = (file && file[0]) ? file : GMT->current.setting.cpt;	/* Set master CPT prefix */
		P = GMT_Read_Data (GMT->parent, GMT_IS_PALETTE, GMT_IS_FILE, GMT_IS_NONE, GMT_READ_NORMAL|GMT_CPT_CONTINUOUS, NULL, master, NULL);
		if (!P) return (P);		/* Error reading file. Return right away to avoid a segv in next line */
		/* Stretch to fit the data range */
		/* Prevent slight round-off from causing the min/max float data values to fall outside the cpt range */
		if (gmt_M_is_zero (dz)) {
			GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Auto-stretching CPT file %s to fit data range %g to %g\n", master, zmin, zmax);
			noise = (zmax - zmin) * GMT_CONV8_LIMIT;
			zmin -= noise;	zmax += noise;
		}
		else {	/* Round to multiple of dz */
			zmin = (floor (zmin / dz) * dz);
			zmax = (ceil (zmax / dz) * dz);
			GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Auto-stretching CPT file %s to fit rounded data range %g to %g\n", master, zmin, zmax);
		}
		PH = gmt_get_C_hidden (P);
		PH->auto_scale = 1;	/* Flag for colorbar to supply -Baf if not given */
		if ((gmt_stretch_cpt (GMT, P, zmin, zmax)) == GMT_PARSE_ERROR) return (NULL);
	}
	else if (file) {	/* Gave a CPT file */
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "CPT argument %s understood to be a regular CPT table\n", file);
		P = GMT_Read_Data (GMT->parent, GMT_IS_PALETTE, GMT_IS_FILE, GMT_IS_NONE, GMT_READ_NORMAL, NULL, &file[first], NULL);
	}
	else
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "No CPT file or master given?\n");

	if (GMT->parent->gwf_dir == NULL || file == NULL || strstr (file, GMT->parent->gwf_dir) == NULL)	/* Avoid writing a sessions CPT to a sessions CPT */
		gmt_save_current_cpt (GMT, P, 0);	/* Save for use by session, if modern */
	return (P);
}

/*! . */
void gmt_cpt_transparency (struct GMT_CTRL *GMT, struct GMT_PALETTE *P, double transparency, unsigned int mode) {
	/* Set transparency for all slices, and possibly BNF */

	unsigned int i;
	gmt_M_unused(GMT);

	for (i = 0; i < P->n_colors; i++) P->data[i].hsv_low[3] = P->data[i].hsv_high[3] = P->data[i].rgb_low[3] = P->data[i].rgb_high[3] = transparency;

	if (mode == 0) return;	/* Do not want to change transparency of BFN*/

	/* Background, foreground, and nan colors */

	for (i = 0; i < 3; i++) P->bfn[i].hsv[3] = P->bfn[i].rgb[3] = transparency;
}

/*! . */
unsigned int gmt_parse_inv_cpt (struct GMT_CTRL *GMT, char *arg) {
	unsigned int mode = 0;
	/* Sets the mode for the -I option in makecpt and grd2cpt */
	if (!arg || arg[0] == 0)	/* Default is -Ic */
		mode |= GMT_CPT_C_REVERSE;
	else {	/* Got argument(s).  Only combinations c, z, cz, or zc allowed */
		size_t k;
		for (k = 0; k < strlen (arg); k++) {
			switch (arg[k]) {
				case 'c':	mode |= GMT_CPT_C_REVERSE;	break;	/* Invert c-range */
				case 'z':	mode |= GMT_CPT_Z_REVERSE;	break;	/* Invert z-range */
				default:
					GMT_Report (GMT->parent, GMT_MSG_ERROR, "gmt_parse_inv_cpt: Unrecognized mode %c passed!\n", arg[k]);
					return UINT_MAX;
					break;
			}
		}
	}
	return (mode);
}

GMT_LOCAL int gmtsupport_validate_cpt (struct GMT_CTRL *GMT, struct GMT_PALETTE *P, double *z_low, double *z_high) {
	int ks;
	if (!P->has_hinge) return GMT_NOTSET;	/* Not our concern here */
	/* Claims to have a hinge */
	ks = gmtsupport_find_cpt_hinge (GMT, P);	/* Get hinge slice (or -1 if no hinge found) */
	if (ks == GMT_PARSE_ERROR) return (GMT_PARSE_ERROR);
	if (ks == GMT_NOTSET) {	/* Must be a rogue CPT - ignore the hinge setting */
		GMT_Report (GMT->parent, GMT_MSG_WARNING, "gmt_stretch_cpt: CPT says it has a hinge but none is actually found? - ignored.\n");
		P->has_hinge = 0;
		return GMT_NOTSET;
	}
	if (*z_low < P->hinge && *z_high > P->hinge) return ks;	/* Output range includes hinge, all is well */

	/* Here we have a CPT with a hinge that is not included in the desired range.  Per policy:
	 * We throw away the unreferenced CPT half and return the other relevant half.
	 */
	if (*z_low >= P->hinge) {	/* Must exclude the below-hinge CPT colors entirely */
		gmt_M_memcpy (P->data, &P->data[ks], P->n_colors-ks, struct GMT_LUT);
		P->n_colors -= ks;
		GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmtsupport_validate_cpt: CPT hard hinge is outside actual data range - range adjusted to start at hinge %g and below-hinge CPT ignored.\n", *z_low);
	}
	else if (*z_high <= P->hinge) {	/* Must exclude the above-hinge CPT colors entirely */
		P->n_colors = ks;
		GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmtsupport_validate_cpt: CPT hard hinge is outside actual data range - range adjusted to end at hinge %g and above-hinge CPT ignored.\n", *z_high);
	}
	/* Behave as a single CPT range with no hinge from now on */
	P->has_hinge = 0;
	return GMT_NOTSET;
}

/*! . */
unsigned int gmt_stretch_cpt (struct GMT_CTRL *GMT, struct GMT_PALETTE *P, double z_low, double z_high) {
	/* Replace CPT z-values with new ones linearly scaled from z_low to z_high.  If these are
	 * zero then we substitute the CPT's default range instead (if available).
	 * Note: If P has a hinge then its value is expected to be in the final user data values.
	 * Default hinge is 0 but *h modifier can set this for CPTs with soft hinges.
	 * Note: Input P has normalized z' values at this time (0-1) so z' hinge is at 0.5.
	 * If a hinge is outside the requested data range then we make adjustments:
	 *   hard hinge: include hinge in the final output range and ignore the other half of the CPT
	 *   soft hinge: Ignore the hinge setting.
	 */
	int is, ks;
	double z_min, z_start, scale;
	if (z_low == z_high) {	/* Range information not given, rely on CPT RANGE setting */
		if (P->has_range == 0) {
			GMT_Report (GMT->parent, GMT_MSG_DEBUG, "gmt_stretch_cpt: Passed z_low == z_high but CPT has no explicit range.  No changes made\n");
			return GMT_NOERROR;
		}
		z_low = P->minmax[0];	z_high = P->minmax[1];
	}
	if ((ks = gmtsupport_validate_cpt (GMT, P, &z_low, &z_high)) == GMT_PARSE_ERROR) return (GMT_PARSE_ERROR);	/* Deal with any issue related to hinges */

	z_min = P->data[0].z_low;
	z_start = z_low;
	if (P->has_hinge)	/* Separate scale on either side of hinge, start with scale for section below the hinge */
		scale = (P->hinge - z_low) / (0.0 - P->data[0].z_low);
	else	/* No hinge, single scale using the entire CPT */
		scale = (z_high - z_low) / (P->data[P->n_colors-1].z_high - P->data[0].z_low);

	for (is = 0; is < (int)P->n_colors; is++) {
		if (is == ks) {	/* Must change scale and z_min for cpt above the hinge */
			z_min = 0.0; z_start = P->hinge;
			scale = (z_high - P->hinge) / (P->data[P->n_colors-1].z_high - 0.0);
		}
		P->data[is].z_low  = z_start + (P->data[is].z_low  - z_min) * scale;
		P->data[is].z_high = z_start + (P->data[is].z_high - z_min) * scale;
		P->data[is].i_dz /= scale;
	}
	return (GMT_NOERROR);
}

/*! . */
GMT_LOCAL int gmtsupport_lutsort (const void *p1, const void *p2) {
	/* Sorts color LUT into ASCENDING order!  */
	if (((struct GMT_LUT *)p1)->z_low < ((struct GMT_LUT *)p2)->z_low) return (-1);
	if (((struct GMT_LUT *)p1)->z_low > ((struct GMT_LUT *)p2)->z_low) return(+1);
	return (0);	/* Should never happen */
}

GMT_LOCAL void gmtsupport_LUT_swap (struct GMT_LUT *slice) {
	/* Exchanges the low and high color values for one slice */
	unsigned int k;
	for (k = 0; k < 4; k++) {
		gmt_M_double_swap (slice->rgb_low[k], slice->rgb_high[k]);
		gmt_M_double_swap (slice->hsv_low[k], slice->hsv_high[k]);
		slice->rgb_diff[k] = -slice->rgb_diff[k];
		slice->hsv_diff[k] = -slice->hsv_diff[k];
	}
}

/*! . */
void gmt_scale_cpt (struct GMT_CTRL *GMT, struct GMT_PALETTE *P, double scale) {
	/* Scale all z-related variables in the CPT by scale */
	unsigned int i;
	bool flip = (scale < 0.0);	/* More work to do if a negative scale is given */
	gmt_M_unused(GMT);
	for (i = 0; i < P->n_colors; i++) {
		P->data[i].z_low  *= scale;
		P->data[i].z_high *= scale;
		P->data[i].i_dz   /= fabs (scale);
		if (flip) {
			gmt_M_double_swap (P->data[i].z_low, P->data[i].z_high);
			gmtsupport_LUT_swap (&(P->data[i]));
		}
	}
	if (P->has_hinge) P->hinge *= scale;
	if (P->has_range) {	/* Update the range min/max */
		P->minmax[0] *= scale;
		P->minmax[1] *= scale;
		if (flip) gmt_M_double_swap (P->minmax[0], P->minmax[1]);
	}
	if (flip)	/* Must also reverse the order of slices */
		qsort (P->data, P->n_colors, sizeof (struct GMT_LUT), gmtsupport_lutsort);
}

#define gmt_M_fill_swap(x, y) {struct GMT_FILL *F_tmp; F_tmp = x, x = y, y = F_tmp;}
/*! . */
void gmt_invert_cpt (struct GMT_CTRL *GMT, struct GMT_PALETTE *P) {
	unsigned int i, j, k;
	gmt_M_unused(GMT);
	/* Reverse the order of the colors, leaving the z arrangement intact */
	for (i = 0, j = P->n_colors-1; i < P->n_colors; i++, j--) {
		for (k = 0; k < 4; k++) {
			gmt_M_double_swap (P->data[i].rgb_low[k], P->data[j].rgb_high[k]);
			gmt_M_double_swap (P->data[i].hsv_low[k], P->data[j].hsv_high[k]);
		}
		if (i < j) gmt_M_fill_swap (P->data[i].fill, P->data[j].fill);

	}
	for (i = 0; i < P->n_colors; i++) {	/* Update the difference arrays */
		for (k = 0; k < 4; k++) {
			P->data[i].rgb_diff[k] = P->data[i].rgb_high[k] - P->data[i].rgb_low[k];
			P->data[i].hsv_diff[k] = P->data[i].hsv_high[k] - P->data[i].hsv_low[k];
		}
	}
	/* Swap the B&F settings */
	for (k = 0; k < 4; k++) {
		gmt_M_double_swap (P->bfn[GMT_BGD].rgb[k], P->bfn[GMT_FGD].rgb[k]);
		gmt_M_double_swap (P->bfn[GMT_BGD].hsv[k], P->bfn[GMT_FGD].hsv[k]);
	}
	gmt_M_fill_swap (P->bfn[GMT_BGD].fill, P->bfn[GMT_FGD].fill);
}

void gmt_undo_log10 (struct GMT_CTRL *GMT, struct GMT_PALETTE *P) {
	unsigned int i;
	gmt_M_unused(GMT);
	/* Turn z into 10^z */
	for (i = 0; i < P->n_colors; i++) {
		P->data[i].z_low  = pow (10.0, P->data[i].z_low);
		P->data[i].z_high = pow (10.0, P->data[i].z_high);
	}
}

/*! . */
struct GMT_PALETTE *gmt_sample_cpt (struct GMT_CTRL *GMT, struct GMT_PALETTE *Pin, double z[], int nz_in, bool continuous, bool reverse, bool log_mode, bool no_inter) {
	/* Resamples the current CPT based on new z-array.
	 * Old cpt is first normalized to z' = 0-1 range and scaled to fit new user z range.
	 * New cpt may be continuous and/or reversed.
	 * We write the new CPT to stdout. */

	unsigned int i = 0, j, k, upper, lower, nz;
	uint64_t dim_nz[GMT_DIM_SIZE] = {0, 0, 0, 0};
	bool even = false;	/* even is true when nz is passed as negative */
	bool set_z_only = false;
	double rgb_low[4], rgb_high[4], rgb_fore[4], rgb_back[4];
	double *x = NULL, *z_out = NULL, a, b, f, x_inc, x_hinge = 0.5;
	double hsv_low[4], hsv_high[4], hsv_fore[4], hsv_back[4];

	struct GMT_LUT *lut = NULL;
	struct GMT_PALETTE *P = NULL;

	if (nz_in < 0) {	/* Called from grd2cpt which wants equal area colors */
		nz = abs (nz_in);
		even = true;
	}
	else
		nz = nz_in;

	if (log_mode) {	/* Our z values are actually log10(z), need array with z for output */
		z_out = gmt_M_memory (GMT, NULL, nz, double);
		for (i = 0; i < nz; i++) z_out[i] = pow (10.0, z[i]);
	}
	else	/* Just point to the incoming z values */
		z_out = z;

	(void) gmtsupport_validate_cpt (GMT, Pin, &z_out[0], &z_out[nz-1]);	/* Deal with any issure related to hinges */

	i += gmt_M_check_condition (GMT, !Pin->is_continuous && continuous, "Making a continuous cpt from a discrete cpt may give unexpected results!\n");


	dim_nz[0] = nz - 1;
	if ((P = GMT_Create_Data (GMT->parent, GMT_IS_PALETTE, GMT_IS_NONE, 0, dim_nz, NULL, NULL, 0, 0, NULL)) == NULL) {
		gmt_M_free (GMT, z_out);
		return NULL;
	}

	lut = gmt_M_memory (GMT, NULL, Pin->n_colors, struct GMT_LUT);

	i += gmt_M_check_condition (GMT, (no_inter || set_z_only) && P->n_colors > Pin->n_colors, "Number of picked colors exceeds colors in input cpt!\n");

	/* First normalize old CPT so z-range is normalized z' = 0-1 */

	b = 1.0 / (Pin->data[Pin->n_colors-1].z_high - Pin->data[0].z_low);
	a = -Pin->data[0].z_low * b;

	for (i = 0; i < Pin->n_colors; i++) {	/* Copy/normalize CPT and reverse if needed */
		if (reverse) {
			j = Pin->n_colors - i - 1;
			lut[i].z_low = 1.0 - a - b * Pin->data[j].z_high;
			lut[i].z_high = 1.0 - a - b * Pin->data[j].z_low;
			gmt_M_rgb_copy (lut[i].rgb_high, Pin->data[j].rgb_low);
			gmt_M_rgb_copy (lut[i].rgb_low,  Pin->data[j].rgb_high);
			gmt_M_rgb_copy (lut[i].hsv_high, Pin->data[j].hsv_low);
			gmt_M_rgb_copy (lut[i].hsv_low,  Pin->data[j].hsv_high);
		}
		else {
			j = i;
			lut[i].z_low = a + b * Pin->data[j].z_low;
			lut[i].z_high = a + b * Pin->data[j].z_high;
			gmt_M_rgb_copy (lut[i].rgb_high, Pin->data[j].rgb_high);
			gmt_M_rgb_copy (lut[i].rgb_low,  Pin->data[j].rgb_low);
			gmt_M_rgb_copy (lut[i].hsv_high, Pin->data[j].hsv_high);
			gmt_M_rgb_copy (lut[i].hsv_low,  Pin->data[j].hsv_low);
		}
	}
	lut[0].z_low = 0.0;			/* Prevent roundoff errors */
	lut[Pin->n_colors-1].z_high = 1.0;

	/* Then set up normalized output locations x */

	x = gmt_M_memory (GMT, NULL, nz, double);

	if (nz < 2)	/* Want a single color point, assume range 0-1 */
		nz = 2;
	else if (even) {
		x_inc = 1.0 / (nz - 1);
		for (i = 0; i < nz; i++) x[i] = i * x_inc;	/* Normalized z values 0-1 */
	}
	else {	/* As with LUT, translate users z-range to 0-1 range */
		double scale_low, scale_high, z_hinge = 0.0, hinge = 0.0;
		if (Pin->has_hinge) {	/* Need separate scales on either side of hinge at 0.0 */
			hinge = Pin->hinge;
			scale_low  = x_hinge / (hinge - z[0]);	/* Convert z_out below the hinge to x = 0 - x_hinge */
			scale_high = (1.0 - x_hinge) * (1.0 / (z[nz-1] - hinge));	/* Convert z)out above hinge to x_hinge - 1 */
		}
		else {	/* No hinge, or output range excludes hinge, same scale for all of CPT */
			scale_high = 1.0 / (z[nz-1] - z[0]);
			z_hinge = -DBL_MAX;	/* So the if-test in the loop below always fail */
			x_hinge = 0.0;		/* Starting x is zero */
			hinge = z[0];	/* There is no hinge so we need z-min */
		}

		for (i = 0; i < nz; i++) {
			if (z[i] <= z_hinge)	/* Below or equal to hinge */
				x[i] = (z[i] - z[0]) * scale_low;
			else /* Above hinge or there is no hinge */
				x[i] = x_hinge + (z[i] - hinge) * scale_high;
		}
	}
	x[0] = 0.0;	/* Prevent bad roundoff */
	x[nz-1] = 1.0;

	/* Determine color at lower and upper limit of each interval */

	for (i = 0; i < P->n_colors; i++) {

		lower = i;
		upper = i + 1;

		if (set_z_only) { /* Just duplicate the RGB colors */
			gmt_M_memcpy (rgb_low, Pin->data[i].rgb_low, 4, double);
			gmt_M_memcpy (rgb_high, Pin->data[i].rgb_high, 4, double);
			gmt_rgb_to_hsv (rgb_low, hsv_low);
			gmt_rgb_to_hsv (rgb_high, hsv_high);
		}
		else if (no_inter) { /* Just pick the first n_colors */
			j = MIN (i, Pin->n_colors);
			if (Pin->model & GMT_HSV) {	/* Pick in HSV space */
				for (k = 0; k < 4; k++) hsv_low[k] = lut[j].hsv_low[k], hsv_high[k] = lut[j].hsv_high[k];
				gmt_hsv_to_rgb (rgb_low, hsv_low);
				gmt_hsv_to_rgb (rgb_high, hsv_high);
			}
			else {	/* Pick in RGB space */
				for (k = 0; k < 4; k++) rgb_low[k] = lut[j].rgb_low[k], rgb_high[k] = lut[j].rgb_low[k];
				gmt_rgb_to_hsv (rgb_low, hsv_low);
				gmt_rgb_to_hsv (rgb_high, hsv_high);
			}
		}
		else if (continuous) { /* Interpolate color at lower and upper value */

			for (j = 0; j < Pin->n_colors && x[lower] >= lut[j].z_high; j++);
			if (j == Pin->n_colors) j--;

			f = 1.0 / (lut[j].z_high - lut[j].z_low);

			if (Pin->model & GMT_HSV) {	/* Interpolation in HSV space */
				for (k = 0; k < 4; k++) hsv_low[k] = lut[j].hsv_low[k] + (lut[j].hsv_high[k] - lut[j].hsv_low[k]) * f * (x[lower] - lut[j].z_low);
				gmt_hsv_to_rgb (rgb_low, hsv_low);
			}
			else {	/* Interpolation in RGB space */
				for (k = 0; k < 4; k++) rgb_low[k] = lut[j].rgb_low[k] + (lut[j].rgb_high[k] - lut[j].rgb_low[k]) * f * (x[lower] - lut[j].z_low);
				gmt_rgb_to_hsv (rgb_low, hsv_low);
			}

			while (j < Pin->n_colors && x[upper] > lut[j].z_high) j++;

			f = 1.0 / (lut[j].z_high - lut[j].z_low);

			if (Pin->model & GMT_HSV) {	/* Interpolation in HSV space */
				for (k = 0; k < 4; k++) hsv_high[k] = lut[j].hsv_low[k] + (lut[j].hsv_high[k] - lut[j].hsv_low[k]) * f * (x[upper] - lut[j].z_low);
				gmt_hsv_to_rgb (rgb_high, hsv_high);
			}
			else {	/* Interpolation in RGB space */
				for (k = 0; k < 4; k++) rgb_high[k] = lut[j].rgb_low[k] + (lut[j].rgb_high[k] - lut[j].rgb_low[k]) * f * (x[upper] - lut[j].z_low);
				gmt_rgb_to_hsv (rgb_high, hsv_high);
			}
#if 0
			/* Avoid aliasing for continuous CPTs */
			if (i > 0 && !gmt_M_same_rgb (P->data[i-1].rgb_high, rgb_low)) {
				/* Discontinuous resampling, must average the colors */
				GMT_Report (GMT->parent, GMT_MSG_WARNING, "CPT resampling caused aliasing - corrected by averaging at boundaries\n");
				if (Pin->model & GMT_HSV) {	/* Interpolation in HSV space */
					for (k = 0; k < 4; k++) P->data[i-1].hsv_high[k] = hsv_low[k] = 0.5 * (P->data[i-1].hsv_high[k] + hsv_low[k]);
					gmt_hsv_to_rgb (P->data[i-1].rgb_high, P->data[i-1].hsv_high);
				}
				else {
					for (k = 0; k < 4; k++) P->data[i-1].rgb_high[k] = rgb_low[k] = 0.5 * (P->data[i-1].rgb_high[k] + rgb_low[k]);
					gmt_rgb_to_hsv (P->data[i-1].rgb_high, P->data[i-1].hsv_high);
				}
			}
#endif
		}
		else {	 /* Interpolate central value and assign color to both lower and upper limit */

			if (Pin->has_hinge && x[lower] <= x_hinge && x[upper] > x_hinge)	/* Detected hinge, so select the hinge normalized x-value */
				a = x_hinge;
			else	/* Get halfway between the limits */
				a = (x[lower] + x[upper]) / 2;
			for (j = 0; j < Pin->n_colors && a >= lut[j].z_high; j++);
			if (j == Pin->n_colors) j--;

			f = 1.0 / (lut[j].z_high - lut[j].z_low);

			if (Pin->model & GMT_HSV) {	/* Interpolation in HSV space */
				for (k = 0; k < 4; k++) hsv_low[k] = hsv_high[k] = lut[j].hsv_low[k] + (lut[j].hsv_high[k] - lut[j].hsv_low[k]) * f * (a - lut[j].z_low);
				gmt_hsv_to_rgb (rgb_low, hsv_low);
				gmt_hsv_to_rgb (rgb_high, hsv_high);
			}
			else {	/* Interpolation in RGB space */
				for (k = 0; k < 4; k++) rgb_low[k] = rgb_high[k] = lut[j].rgb_low[k] + (lut[j].rgb_high[k] - lut[j].rgb_low[k]) * f * (a - lut[j].z_low);
				gmt_rgb_to_hsv (rgb_low, hsv_low);
				gmt_rgb_to_hsv (rgb_high, hsv_high);
			}
		}

		if (lower == 0) {
			gmt_M_rgb_copy (rgb_back, rgb_low);
			gmt_M_rgb_copy (hsv_back, hsv_low);
		}
		if (upper == P->n_colors) {
			gmt_M_rgb_copy (rgb_fore, rgb_high);
			gmt_M_rgb_copy (hsv_fore, hsv_high);
		}

		gmt_M_rgb_copy (P->data[i].rgb_low, rgb_low);
		gmt_M_rgb_copy (P->data[i].rgb_high, rgb_high);
		gmt_M_rgb_copy (P->data[i].hsv_low, hsv_low);
		gmt_M_rgb_copy (P->data[i].hsv_high, hsv_high);
		P->data[i].z_low = z_out[lower];
		P->data[i].z_high = z_out[upper];
		P->is_gray = (gmt_M_is_gray (P->data[i].rgb_low) && gmt_M_is_gray (P->data[i].rgb_high));
		P->is_bw = (gmt_M_is_bw(P->data[i].rgb_low) && gmt_M_is_bw (P->data[i].rgb_high));

		/* Differences used in gmt_get_rgb_from_z */
		for (k = 0; k < 4; k++) P->data[i].rgb_diff[k] = P->data[i].rgb_high[k] - P->data[i].rgb_low[k];
		for (k = 0; k < 4; k++) P->data[i].hsv_diff[k] = P->data[i].hsv_high[k] - P->data[i].hsv_low[k];

		/* When HSV is converted from RGB: avoid interpolation over hue differences larger than 180 degrees;
		   take the shorter distance instead. This does not apply for HSV color tables, since there we assume
		   that the H values are intentional and one might WANT to interpolate over more than 180 degrees. */
		if (!(P->model & GMT_HSV)) {
			if (P->data[i].hsv_diff[0] < -180.0) P->data[i].hsv_diff[0] += 360.0;
			if (P->data[i].hsv_diff[0] >  180.0) P->data[i].hsv_diff[0] -= 360.0;
		}
		f = P->data[i].z_high - P->data[i].z_low;
		if (f <= 0.0) {
			gmt_M_free (GMT, x);
			gmt_M_free (GMT, lut);
			if (log_mode) gmt_M_free (GMT, z_out);
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Z-slice around line %d with dz <= 0\n", i);
			return (NULL);
		}
		P->data[i].i_dz = 1.0 / f;
	}

	gmt_M_free (GMT, x);
	gmt_M_free (GMT, lut);
	if (log_mode) gmt_M_free (GMT, z_out);
	P->model = Pin->model;
	P->categorical = Pin->categorical;
	P->is_wrapping = Pin->is_wrapping;
	P->is_continuous = continuous;
	P->is_bw = Pin->is_bw;
	P->is_gray = Pin->is_gray;
	P->has_range = Pin->has_hinge = 0;	/* No longer normalized or special hinge after resampling */

	/* Background, foreground, and nan colors */

	gmt_M_memcpy (P->bfn, Pin->bfn, 3, struct GMT_BFN);	/* Copy over BNF */

	if (reverse) {	/* Flip foreground and background colors */
		gmt_M_rgb_copy (rgb_low, P->bfn[GMT_BGD].rgb);
		gmt_M_rgb_copy (P->bfn[GMT_BGD].rgb, P->bfn[GMT_FGD].rgb);
		gmt_M_rgb_copy (P->bfn[GMT_FGD].rgb, rgb_low);
		gmt_M_rgb_copy (hsv_low, P->bfn[GMT_BGD].hsv);
		gmt_M_rgb_copy (P->bfn[GMT_BGD].hsv, P->bfn[GMT_FGD].hsv);
		gmt_M_rgb_copy (P->bfn[GMT_FGD].hsv, hsv_low);
	}

	/* Must set default annotation flags */
	for (i = 0; i < P->n_colors; i++) P->data[i].annot = GMT_CPT_L_ANNOT;
	if (i) P->data[i-1].annot = GMT_CPT_B_ANNOT;
	else P->data[i].annot = GMT_CPT_B_ANNOT;

	gmtsupport_copy_palette_hdrs (GMT, P, Pin);
	return (P);
}

/*! . */
int gmtlib_write_cpt (struct GMT_CTRL *GMT, void *dest, unsigned int dest_type, unsigned int cpt_flags, struct GMT_PALETTE *P) {
	/* We write the CPT to fp [or stdout].
	 * dest_type can be GMT_IS_[FILE|STREAM|FDESC]
	 * cpt_flags is a combination of:
	 * GMT_CPT_NO_BNF = Do not write BFN
	 * GMT_CPT_EXTEND_BNF = Make B and F equal to low and high color
	 */

	unsigned int i, append = 0, hinge_mode = 0;
	bool close_file = false, use[3] = {true, true, true};
	double cmyk[5], z_hinge;
	char format[GMT_BUFSIZ] = {""}, cpt_file[PATH_MAX] = {""}, code[3] = {'B', 'F', 'N'};
	char lo[GMT_LEN64] = {""}, hi[GMT_LEN64] = {""}, kind[3] = {'L', 'U', 'B'};
	static char *msg1[2] = {"Writing", "Appending"};
	FILE *fp = NULL;
	struct CPT_Z_SCALE *Z = NULL;	/* For unit manipulations */
	struct GMT_PALETTE_HIDDEN *PH = NULL;

	if (cpt_flags & GMT_CPT_GRAY_SET && !P->is_gray)
		GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Colors in the CPT file %s were converted to gray via the YIQ-translation.\n", &cpt_file[append]);

	/* When writing the CPT to file it is no longer a normalized CPT with a hinge */
	P->has_range = P->has_hinge = 0;

	if (dest_type == GMT_IS_FILE && !dest) dest_type = GMT_IS_STREAM;	/* No filename given, default to stdout */

	if (dest_type == GMT_IS_FILE) {	/* dest is a file name */
		static char *msg2[2] = {"create", "append to"};
		strncpy (cpt_file, dest, PATH_MAX-1);
		append = (cpt_file[0] == '>');	/* Want to append to existing file */
		if ((Z = gmtsupport_cpt_parse (GMT, &cpt_file[append], GMT_OUT, &hinge_mode, &z_hinge))) {
			gmtsupport_cpt_z_scale (GMT, P, Z, GMT_OUT);
			gmt_M_free (GMT, Z);
		}
		if ((fp = fopen (&cpt_file[append], (append) ? "a" : "w")) == NULL) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Cannot %s file %s\n", msg2[append], &cpt_file[append]);
			return (GMT_ERROR_ON_FOPEN);
		}
		close_file = true;	/* We only close files we have opened here */
	}
	else if (dest_type == GMT_IS_STREAM) {	/* Open file pointer given, just copy */
		fp = (FILE *)dest;
		if (fp == NULL) fp = GMT->session.std[GMT_OUT];	/* Default destination */
		if (fp == GMT->session.std[GMT_OUT])
			strcpy (cpt_file, "<stdout>");
		else
			strcpy (cpt_file, "<output stream>");
	}
	else if (dest_type == GMT_IS_FDESC) {		/* Open file descriptor given, just convert to file pointer */
		int *fd = dest;
		if (fd && (fp = fdopen (*fd, "a")) == NULL) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Cannot convert file descriptor %d to stream in gmtlib_write_cpt\n", *fd);
			return (GMT_ERROR_ON_FDOPEN);
		}
		else
			close_file = true;	/* fdopen allocates memory */
		if (fd == NULL) fp = GMT->session.std[GMT_OUT];	/* Default destination */
		if (fp == GMT->session.std[GMT_OUT])
			strcpy (cpt_file, "<stdout>");
		else
			strcpy (cpt_file, "<output file descriptor>");
	}
	else {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Unrecognized source type %d in gmtlib_write_cpt\n", dest_type);
		return (GMT_NOT_A_VALID_METHOD);
	}
	GMT_Report (GMT->parent, GMT_MSG_DEBUG, "%s CPT to %s\n", msg1[append], &cpt_file[append]);

	PH = gmt_get_C_hidden (P);

	if (hinge_mode && P->mode & GMT_CPT_SOFT_HINGE) { /* Add a hard hinge to the CPT */
		P->mode -= GMT_CPT_SOFT_HINGE;
		P->mode |= GMT_CPT_HARD_HINGE;
		P->has_hinge = 1;
		P->hinge = z_hinge;	/* This is the user-unit value to be used during stretching in gmt_stretch_cpt */
	}

	/* Start writing CPT info to fp */

	for (i = 0; i < P->n_headers; i++) {	/* First write the old headers */
		gmtlib_write_tableheader (GMT, fp, P->header[i]);
	}
	gmtlib_write_newheaders (GMT, fp, 0);	/* Write general header block */

	if (!(P->model & GMT_COLORINT)) {}	/* Write nothing when color interpolation is not forced */
	else if (P->model & GMT_GRAY)
		fprintf (fp, "# COLOR_MODEL = gray\n");
	else if (P->model & GMT_HSV)
		fprintf (fp, "# COLOR_MODEL = hsv\n");
	else if (P->model & GMT_CMYK)
		fprintf (fp, "# COLOR_MODEL = cmyk\n");
	else
		fprintf (fp, "# COLOR_MODEL = rgb\n");
	if (P->has_hinge)
		fprintf (fp, "# HARD_HINGE\n");
	if (P->is_wrapping)
		fprintf (fp, "# CYCLIC\n");
	if (PH->auto_scale)
		fprintf (fp, "# ENABLE_B_OPTION\n");

	sprintf (format, "%%s\t%%s%%c");

	/* Determine color at lower and upper limit of each interval */

	for (i = 0; i < P->n_colors; i++) {

		/* Print out one row */
		gmt_ascii_format_col (GMT, lo, P->data[i].z_low,  GMT_OUT, GMT_Z);
		gmt_ascii_format_col (GMT, hi, P->data[i].z_high, GMT_OUT, GMT_Z);

		if (P->categorical) {
			if (P->categorical & GMT_CPT_CATEGORICAL_KEY) strncpy (lo, P->data[i].key, GMT_LEN64-1);
			if (P->model & GMT_GRAY)
				fprintf (fp, format, lo, gmt_putgray (GMT, P->data[i].hsv_low), '\t');
			if (P->model & GMT_HSV)
				fprintf (fp, format, lo, gmtlib_puthsv (GMT, P->data[i].hsv_low), '\t');
			else if (P->model & GMT_CMYK) {
				gmtsupport_rgb_to_cmyk (P->data[i].rgb_low, cmyk);
				fprintf (fp, format, lo, gmtlib_putcmyk (GMT, cmyk), '\t');
			}
			else if (P->model & GMT_NO_COLORNAMES)
				fprintf (fp, format, lo, gmt_putrgb (GMT, P->data[i].rgb_low), '\t');
			else if (P->model & GMT_HEX_COLOR)
				fprintf (fp, format, lo, gmt_puthex (GMT, P->data[i].rgb_low), '\t');
			else
				fprintf (fp, format, lo, gmt_putcolor (GMT, P->data[i].rgb_low), '\t');
		}
		else if (P->model & GMT_GRAY) {
			fprintf (fp, format, lo, gmt_putgray (GMT, P->data[i].rgb_low), '\t');
			fprintf (fp, format, hi, gmt_putgray (GMT, P->data[i].rgb_high), '\t');
		}
		else if (P->model & GMT_HSV) {
			fprintf (fp, format, lo, gmtlib_puthsv (GMT, P->data[i].hsv_low), '\t');
			fprintf (fp, format, hi, gmtlib_puthsv (GMT, P->data[i].hsv_high), '\t');
		}
		else if (P->model & GMT_CMYK) {
			gmtsupport_rgb_to_cmyk (P->data[i].rgb_low, cmyk);
			fprintf (fp, format, lo, gmtlib_putcmyk (GMT, cmyk), '\t');
			gmtsupport_rgb_to_cmyk (P->data[i].rgb_high, cmyk);
			fprintf (fp, format, hi, gmtlib_putcmyk (GMT, cmyk), '\t');
		}
		else if (P->model & GMT_NO_COLORNAMES) {
			fprintf (fp, format, lo, gmt_putrgb (GMT, P->data[i].rgb_low), '\t');
			fprintf (fp, format, hi, gmt_putrgb (GMT, P->data[i].rgb_high), '\t');
		}
		else if (P->model & GMT_HEX_COLOR) {
			fprintf (fp, format, lo, gmt_puthex (GMT, P->data[i].rgb_low), '\t');
			fprintf (fp, format, hi, gmt_puthex (GMT, P->data[i].rgb_high), '\t');
		}
		else {
			fprintf (fp, format, lo, gmt_putcolor (GMT, P->data[i].rgb_low), '\t');
			fprintf (fp, format, hi, gmt_putcolor (GMT, P->data[i].rgb_high), '\t');
		}
		if (P->data[i].annot) fprintf (fp, "%c", kind[P->data[i].annot-1]);
		if (P->data[i].label) fprintf (fp, "\t;%s", P->data[i].label);
		fputc ('\n', fp);
	}

	/* Background, foreground, and nan colors */

	if (cpt_flags & GMT_CPT_NO_BNF) {	/* Do not want to write BFN to the CPT */
		if (close_file) fclose (fp);
		return (GMT_NOERROR);
	}

	if (P->is_wrapping || P->categorical) use[GMT_BGD] = use[GMT_FGD] = false;	/* These types of CPT has no back/foreground colors */

	for (i = 0; i < 3; i++) {
		if (!use[i]) continue;	/* This BNF entry does not apply to this CPT */
		if (P->bfn[i].skip)
			fprintf (fp, "%c\t-\n", code[i]);
		else if (P->model & GMT_GRAY)
			fprintf (fp, "%c\t%s\n", code[i], gmt_putgray (GMT, P->bfn[i].rgb));
		else if (P->model & GMT_HSV)
			fprintf (fp, "%c\t%s\n", code[i], gmtlib_puthsv (GMT, P->bfn[i].hsv));
		else if (P->model & GMT_CMYK) {
			gmtsupport_rgb_to_cmyk (P->bfn[i].rgb, cmyk);
			fprintf (fp, "%c\t%s\n", code[i], gmtlib_putcmyk (GMT, cmyk));
		}
		else if (P->model & GMT_NO_COLORNAMES)
			fprintf (fp, "%c\t%s\n", code[i], gmt_putrgb (GMT, P->bfn[i].rgb));
		else if (P->model & GMT_HEX_COLOR)
			fprintf (fp, "%c\t%s\n", code[i], gmt_puthex (GMT, P->bfn[i].rgb));
		else
			fprintf (fp, "%c\t%s\n", code[i], gmt_putcolor (GMT, P->bfn[i].rgb));
	}
	if (close_file) fclose (fp);

	return (GMT_NOERROR);
}

GMT_LOCAL void gmtsupport_reset_cpt (struct GMT_CTRL *GMT, struct GMT_PALETTE *P) {
	/* Determine if CPT is continuous, B/W, or gray-scale */
	unsigned int k;
	gmt_M_unused (GMT);

	P->is_continuous = false;
	P->is_gray = P->is_bw = true;	/* May be changed when reading the actual colors */
	for (k = 0; k < 3; k++) {
		if (P->bfn[k].rgb[0] == -1.0) P->bfn[k].skip = true;
		if (P->is_gray && !gmt_M_is_gray (P->bfn[k].rgb)) P->is_gray = P->is_bw = false;
		if (P->is_bw && !gmt_M_is_bw(P->bfn[k].rgb)) P->is_bw = false;
	}
	for (k = 0; k < P->n_colors; k++) {
		if (!P->is_continuous && !gmt_M_same_rgb(P->data[k].hsv_low,P->data[k].hsv_high)) P->is_continuous = true;
		if (P->is_gray && !(gmt_M_is_gray (P->data[k].rgb_low) && gmt_M_is_gray (P->data[k].rgb_high))) P->is_gray = P->is_bw = false;
		if (P->is_bw && !(gmt_M_is_bw(P->data[k].rgb_low) && gmt_M_is_bw(P->data[k].rgb_high))) P->is_bw = false;
	}

}

/*! . */
struct GMT_PALETTE * gmt_truncate_cpt (struct GMT_CTRL *GMT, struct GMT_PALETTE *P, double z_low, double z_high) {
	/* Truncate this CPT to start and end at z_low, z_high.  If either is NaN we do nothing at that end. */
	unsigned int k, j, first = 0, last = P->n_colors - 1;
	struct GMT_PALETTE_HIDDEN *PH = NULL;

	if (gmt_M_is_dnan (z_low) && gmt_M_is_dnan (z_high)) return (P);	/* No change */

	/* If this CPT has a natural range then its z-values are either 0 to 1 or -1 to +1.  We must first
	 * expand it to its natural z-range before we can truncate since z_low/z_high are in user units */

	if (P->has_range) {
		if ((gmt_stretch_cpt (GMT, P, 0.0, 0.0)) == GMT_PARSE_ERROR) return NULL;	/* Stretch to its natural range first */
		P->has_range = 0;
	}

	if ((!gmt_M_is_dnan (z_low) && z_low > P->data[last].z_high) || (!gmt_M_is_dnan (z_high) && z_high < P->data[0].z_low)) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "gmt_truncate_cpt error: z_low/z_high [%g/%g] is completely outside range of this CPT [%g/%g]!\n",
			z_low, z_high, P->data[0].z_low, P->data[last].z_high);
			return NULL;
	}
	if (!gmt_M_is_dnan (z_low) && z_low < P->data[0].z_low) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "gmt_truncate_cpt error: z_low = %g less than lowest z (%g)\n",
			z_low, P->data[0].z_low, P->data[0].z_low);
		return NULL;
	}
	if (!gmt_M_is_dnan (z_high) && z_high > P->data[last].z_high) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "gmt_truncate_cpt: z_high = %g larger than highest z (%g)\n",
			z_high, P->data[last].z_high, P->data[last].z_high);
		return NULL;
	}
	/* OK, here we can sanely do things */
	if (!gmt_M_is_dnan (z_low)) {	/* Find first slice fully or partially within range */
		while (first < P->n_colors && P->data[first].z_high <= z_low) first++;
		if (z_low > P->data[first].z_low)	/* Must truncate this slice */
			gmtsupport_truncate_cpt_slice (&P->data[first], P->model & GMT_HSV, z_low, -1);
	}
	if (!gmt_M_is_dnan (z_high)) {	/* Find last slice fully or partially within range */
		while (last > 0 && P->data[last].z_low >= z_high) last--;
		if (P->data[last].z_high > z_high)	/* Must truncate this slice */
			gmtsupport_truncate_cpt_slice (&P->data[last], P->model & GMT_HSV, z_high, +1);
	}

	PH = gmt_get_C_hidden (P);
	for (k = 0; k < first; k++)
		gmtsupport_free_range (GMT, PH, &P->data[k]);	/* Free any char strings */
	for (k = last + 1; k < P->n_colors; k++)
		gmtsupport_free_range (GMT, PH, &P->data[k]);	/* Free any char strings */

	if (first) {	/* Shuffle CPT down */
		for (k = 0, j = first; j <= last; k++, j++) {
			P->data[k] = P->data[j];
		}
	}
	P->n_colors = last - first + 1;
	P->data = gmt_M_memory (GMT, P->data, P->n_colors, struct GMT_LUT);	/* Truncate */
	/* Check if anything has changed regarding continuous, gray scale, or B/W */
	gmtsupport_reset_cpt (GMT, P);
	return (P);
}

/*! . */
void gmtlib_init_cpt (struct GMT_CTRL *GMT, struct GMT_PALETTE *P) {
	/* For CPTs passed to/from external APIs we need to initialize some derived CPT quantities.
	 * The data is received as r/b/g regardless of model so we must set hsv quantities. */
	unsigned int k, n;

	for (n = 0; n < P->n_colors; n++) {
		gmt_rgb_to_hsv (P->data[n].rgb_low,  P->data[n].hsv_low);
		gmt_rgb_to_hsv (P->data[n].rgb_high, P->data[n].hsv_high);
		P->data[n].i_dz = 1.0 / (P->data[n].z_high - P->data[n].z_low);	/* Recompute inverse stepsize */
		/* Differences used in gmt_get_rgb_from_z */
		for (k = 0; k < 4; k++) P->data[n].rgb_diff[k] = P->data[n].rgb_high[k] - P->data[n].rgb_low[k];
		for (k = 0; k < 4; k++) P->data[n].hsv_diff[k] = P->data[n].hsv_high[k] - P->data[n].hsv_low[k];
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "%d: %g to %g. R/G/B %s to %s. idz = %g diff R/G/B = %g/%g/%g\n", n,
			P->data[n].z_low, P->data[n].z_high, gmt_putrgb (GMT, P->data[n].rgb_low), gmt_putrgb (GMT, P->data[n].rgb_high),
			P->data[n].i_dz, P->data[n].rgb_diff[0], P->data[n].rgb_diff[1], P->data[n].rgb_diff[2]);
	}
	P->wrap_length = P->data[P->n_colors-1].z_high - P->data[0].z_low;
	GMT->current.setting.color_model = (P->model | GMT_COLORINT);	/* So color interpolation will happen in the color system */

	/* We leave BNF as we got them from the external API */
}

/*! . */
int gmt_get_index (struct GMT_CTRL *GMT, struct GMT_PALETTE *P, double *value) {
	unsigned int index, lo, hi, mid;
	gmt_M_unused(GMT);

	if (gmt_M_is_dnan (*value)) return (GMT_NAN - 3);	/* Set to NaN color */
	if (P->is_wrapping)	/* Wrap to fit CPT range - we can never return back- or fore-ground colors */
		*value = MOD (*value - P->data[0].z_low, P->wrap_length) + P->data[0].z_low;	/* Now within range */
	else if (*value > P->data[P->n_colors-1].z_high) {
		if (P->categorical) {	/* Set to NaN for categorical */
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "Requested color lookup for z = %.12lg is not a categorical value - returning NaN color\n", *value);
			return GMT_NAN - 3;
		}
		return (GMT_FGD - 3);	/* Set to foreground color */
	}
	else if (*value < P->data[0].z_low) {
		if (P->categorical) {	/* Set to NaN for categorical */
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "Requested color lookup for z = %.12lg is not a categorical value - returning NaN color\n", *value);
			return GMT_NAN - 3;
		}
		return (GMT_BGD - 3);	/* Set to background color */
	}

	/* Must search for correct index */

	/* Speedup by Mika Heiskanen. This works if the colortable
	 * has been is sorted into increasing order. Careful when
	 * modifying the tests in the loop, the test and the mid+1
	 * parts are especially designed to make sure the loop
	 * converges to a single index.
	 */

	lo = 0;
	hi = P->n_colors - 1;
	while (lo != hi)
	{
		mid = (lo + hi) / 2;
		if (*value >= P->data[mid].z_high)
			lo = mid + 1;
		else
			hi = mid;
	}
	index = lo;
	
	if (*value >= P->data[index].z_low && *value < P->data[index].z_high) {
		if (P->categorical && !doubleAlmostEqualZero (P->data[index].z_low, *value)) {
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "Requested color lookup for z = %.12lg is not a categorical value - returning NaN color\n", *value);
			index = GMT_NAN - 3;	/* Since categorical data is not on an interval */
		}
		return (index);
	}

	/* Slow search in case the table was not sorted
	 * No idea whether it is possible, but it most certainly
	 * does not hurt to have the code here as a backup.
	 */

	index = 0;
	while (index < P->n_colors && ! (*value >= P->data[index].z_low && *value < P->data[index].z_high) ) index++;
	if (index == P->n_colors) index--;	/* Because we use <= for last range */
	if (P->categorical && !doubleAlmostEqualZero (P->data[index].z_low, *value)) {
		GMT_Report (GMT->parent, GMT_MSG_WARNING, "Requested color lookup for z = %.12lg is not a categorical value - returning NaN color\n", *value);
		index = GMT_NAN - 3;	/* Since categorical data is not on an interval */
	}
	return (index);
}

/*! . */
void gmt_get_rgb_lookup (struct GMT_CTRL *GMT, struct GMT_PALETTE *P, int index, double value, double *rgb) {
	unsigned int i;
	double rel, hsv[4];
	struct GMT_PALETTE_HIDDEN *PH = gmt_get_C_hidden (P);

	if (index < 0) {	/* NaN, Foreground, Background */
		gmt_M_rgb_copy (rgb, P->bfn[index+3].rgb);
		PH->skip = P->bfn[index+3].skip;
	}
	else if (P->data[index].skip) {		/* Set to page color for now */
		gmt_M_rgb_copy (rgb, GMT->current.setting.ps_page_rgb);
		PH->skip = true;
	}
	else {	/* Do linear interpolation between low and high colors */
		rel = (value - P->data[index].z_low) * P->data[index].i_dz;
		if (GMT->current.setting.color_model == (GMT_HSV | GMT_COLORINT)) {	/* Interpolation in HSV space */
			for (i = 0; i < 4; i++) hsv[i] = P->data[index].hsv_low[i] + rel * P->data[index].hsv_diff[i];
			gmt_hsv_to_rgb (rgb, hsv);
		}
		else {	/* Interpolation in RGB space */
			for (i = 0; i < 4; i++) rgb[i] = P->data[index].rgb_low[i] + rel * P->data[index].rgb_diff[i];
		}
		PH->skip = false;
	}
}

/*! . */
int gmt_get_rgb_from_z (struct GMT_CTRL *GMT, struct GMT_PALETTE *P, double value, double *rgb) {
	int index = gmt_get_index (GMT, P, &value);
	gmt_get_rgb_lookup (GMT, P, index, value, rgb);
	return (index);
}

/*! . */
int gmt_get_rgbtxt_from_z (struct GMT_CTRL *GMT, struct GMT_PALETTE *P, char *text) {
	/* Assumes text is long enough to hold the color specification */
	double z, rgb[4];
	if (!strcmp (text, "-")) return 0;	/* Got just - which means we did not want fill; not an error */
	if (strncmp (text, "z=", 2U)) return 0;	/* Not a z=<value> specification, so no error since presumably we got a color or fill */
	if (P == NULL) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Requested color lookup via z=<value> but no CPT was given via -A<cpt>\n");
		return GMT_NO_CPT;
	}
	z = atof (&text[2]);	/* Extract the z value */
	gmt_get_rgb_from_z (GMT, P, z, rgb);	/* Convert via CPT to r/g/b */
	sprintf (text, "%s", gmt_putcolor (GMT, rgb));
	GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Gave z=%g and returned %s\n", z, text);
	return 0;
}

/*! . */
int gmt_get_fill_from_z (struct GMT_CTRL *GMT, struct GMT_PALETTE *P, double value, struct GMT_FILL *fill) {
	int index;
	struct GMT_FILL *f = NULL;

	index = gmt_get_index (GMT, P, &value);

	/* Check if pattern */

	if (index >= 0 && (f = P->data[index].fill))
		gmt_M_memcpy (fill, f, 1, struct GMT_FILL);
	else if (index < 0 && (f = P->bfn[index+3].fill))
		gmt_M_memcpy (fill, f, 1, struct GMT_FILL);
	else {
		gmt_get_rgb_lookup (GMT, P, index, value, fill->rgb);
		fill->use_pattern = false;
	}
	return (index);
}

bool gmt_same_fill (struct GMT_CTRL *GMT, struct GMT_FILL *F1, struct GMT_FILL *F2) {
	gmt_M_unused(GMT);
	/* Return true if the two fills are identical */
	if (F1->use_pattern != F2->use_pattern) return false;	/* One is a pattern, the other isn't, so cannot be the same */
	if (F1->use_pattern) {	/* Both are patterns */
		if (F1->pattern_no != F2->pattern_no) return false;	/* Different patters used */
		if (F1->pattern_no == -1)	/* Both have custom fill patterns */
			return !strcmp (F1->pattern, F2->pattern);
		return true;	/* They are the same */
	}
	return gmt_M_same_rgb (F1->rgb, F2->rgb);	/* true if the same color, including transparency level */
}

/*! . */
GMT_LOCAL int gmtsupport_get_index_from_key (struct GMT_CTRL *GMT, struct GMT_PALETTE *P, char *key) {
	/* Will match key to a key in the color table.  Because a key is a string and may
	 * some times (via shapefiles) be enclosed in quotes, we must skip using those quotes
	 * in the string comparison.  The CPT key cannot have quotes and must be a single word.
	 * Use the ;labal mechanism in the CPT to annotate colorbars with longer names.
	 * Also note that there is no fore or back-ground color in this case.  We may assign
	 * the NaN color if the key is blank or not matched in the CPT. */
	unsigned int index;
	size_t len, pos = 0;
	gmt_M_unused(GMT);

	if (!key || key[0] == '\0') return (GMT_NAN - 3);	/* Set to NaN color */
	len = strlen (key);
	if ((key[0] == '\"' && key[len-1] == '\"') || (key[0] == '\'' && key[len-1] == '\'')) {	/* Must exclude quotes */
		pos = 1; len -= 2;
	}
	/* Must search for correct index */

	for (index = 0; index < P->n_colors; index++) {
		if (!strncmp (P->data[index].key, &key[pos], len))
			return (int)index;
	}
	return (GMT_NAN - 3);
}

/*! . */
int gmt_get_fill_from_key (struct GMT_CTRL *GMT, struct GMT_PALETTE *P, char *key, struct GMT_FILL *fill) {
	int index;
	struct GMT_FILL *f = NULL;

	index = gmtsupport_get_index_from_key (GMT, P, key);

	/* Check if pattern */

	if (index >= 0 && (f = P->data[index].fill))
		gmt_M_memcpy (fill, f, 1, struct GMT_FILL);
	else if (index < 0 && (f = P->bfn[index+3].fill))
		gmt_M_memcpy (fill, f, 1, struct GMT_FILL);
	else {	/* Not pattern */
		if (index < 0) /* NaN color */
			gmt_M_rgb_copy (fill->rgb, P->bfn[index+3].rgb);
		else
			gmt_M_rgb_copy (fill->rgb, P->data[index].rgb_low);
		fill->use_pattern = false;
	}
	return (index);
}

/*! . */
void gmt_illuminate (struct GMT_CTRL *GMT, double intensity, double rgb[]) {
	double di, hsv[4];

	if (gmt_M_is_dnan (intensity)) return;
	if (intensity == 0.0) return;
	if (fabs (intensity) > 1.0) intensity = copysign (1.0, intensity);

	gmt_rgb_to_hsv (rgb, hsv);
	if (intensity > 0.0) {	/* Lighten the color */
		di = 1.0 - intensity;
		if (hsv[1] != 0.0) hsv[1] = di * hsv[1] + intensity * GMT->current.setting.color_hsv_max_s;
		hsv[2] = di * hsv[2] + intensity * GMT->current.setting.color_hsv_max_v;
	}
	else {			/* Darken the color */
		di = 1.0 + intensity;
		if (hsv[1] != 0.0) hsv[1] = di * hsv[1] - intensity * GMT->current.setting.color_hsv_min_s;
		hsv[2] = di * hsv[2] - intensity * GMT->current.setting.color_hsv_min_v;
	}
	if (hsv[1] < 0.0) hsv[1] = 0.0;
	if (hsv[2] < 0.0) hsv[2] = 0.0;
	if (hsv[1] > 1.0) hsv[1] = 1.0;
	if (hsv[2] > 1.0) hsv[2] = 1.0;
	gmt_hsv_to_rgb (rgb, hsv);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * gmtlib_akima computes the coefficients for a quasi-cubic hermite spline.
 * Same algorithm as in the IMSL library.
 * Programmer:	Paul Wessel
 * Date:	16-JAN-1987
 * Ver:		v.1-pc
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 */

/*! . */
int gmtlib_akima (struct GMT_CTRL *GMT, double *x, double *y, uint64_t nx, double *c) {
	uint64_t i, no;
	double t1, t2, b, rm1, rm2, rm3, rm4;
	gmt_M_unused(GMT);

	/* Assumes that n >= 4 and x is monotonically increasing */

	rm3 = (y[1] - y[0])/(x[1] - x[0]);
	t1 = rm3 - (y[1] - y[2])/(x[1] - x[2]);
	rm2 = rm3 + t1;
	rm1 = rm2 + t1;

	/* get slopes */

	no = nx - 2;
	for (i = 0; i < nx; i++) {
		if (i >= no)
			rm4 = rm3 - rm2 + rm3;
		else
			rm4 = (y[i+2] - y[i+1])/(x[i+2] - x[i+1]);
		t1 = fabs(rm4 - rm3);
		t2 = fabs(rm2 - rm1);
		b = t1 + t2;
		c[3*i] = (b != 0.0) ? (t1*rm2 + t2*rm3) / b : 0.5*(rm2 + rm3);
		rm1 = rm2;
		rm2 = rm3;
		rm3 = rm4;
	}
	no = nx - 1;

	/* compute the coefficients for the nx-1 intervals */

	for (i = 0; i < no; i++) {
		t1 = 1.0 / (x[i+1] - x[i]);
		t2 = (y[i+1] - y[i])*t1;
		b = (c[3*i] + c[3*i+3] - t2 - t2)*t1;
		c[3*i+2] = b*t1;
		c[3*i+1] = -b + (t2 - c[3*i])*t1;
	}
	return (GMT_NOERROR);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * gmtlib_cspline computes the coefficients for a natural cubic spline.
 * To evaluate, call gmtsupport_csplint
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 */

/*! . */
int gmtlib_cspline (struct GMT_CTRL *GMT, double *x, double *y, uint64_t n, double *c) {
	uint64_t i, k;
	double ip, s, dx1, i_dx2, *u = gmt_M_memory (GMT, NULL, n, double);

	if (u == NULL) return GMT_MEMORY_ERROR;

	/* Assumes that n >= 4 and x is monotonically increasing */

	c[0] = c[n-1] = 0.0;	/* The other c[i] are set directly in the loop */
	for (i = 1; i < n-1; i++) {
		i_dx2 = 1.0 / (x[i+1] - x[i-1]);
		dx1 = x[i] - x[i-1];
		s = dx1 * i_dx2;
		ip = 1.0 / (s * c[i-1] + 2.0);
		c[i] = (s - 1.0) * ip;
		u[i] = (y[i+1] - y[i]) / (x[i+1] - x[i]) - (y[i] - y[i-1]) / dx1;
		u[i] = (6.0 * u[i] * i_dx2 - s * u[i-1]) * ip;
	}
	for (k = n-1; k > 0; k--) c[k-1] = c[k-1] * c[k] + u[k-1];
	gmt_M_free (GMT, u);

	return (GMT_NOERROR);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * gmt_intpol will interpolate from the dataset <x,y> onto a new set <u,v>
 * where <x,y> and <u> is supplied by the user. <v> is returned. The
 * parameter mode governs what interpolation scheme that will be used.
 * If u[i] is outside the range of x, then v[i] will contain a value
 * determined by the content of the GMT_EXTRAPOLATE_VAL. Namely, NaN if
 * GMT_EXTRAPOLATE_VAL[0] = 1; pure extrapolation if GMT_EXTRAPOLATE_VAL[0] = 1;
 * or a constant value (GMT_EXTRAPOLATE_VAL[1]) if GMT_EXTRAPOLATE_VAL[0] = 2
 *
 * input:  x = x-values of input data
 *	   y = y-values "    "     "
 *     w = weights or NULL [for smoothing spline only]
 *	   n = number of data pairs
 *	   m = number of desired interpolated values
 *	   u = x-values of these points
 *     p = fit-value for smoothing spline
 *	  mode = type of interpolation, with added 10*derivative_level [0,1,2]
 *	  mode = GMT_SPLINE_LINEAR [0] : Linear interpolation
 *	  mode = GMT_SPLINE_AKIMA [1] : Quasi-cubic hermite spline (gmtlib_akima)
 *	  mode = GMT_SPLINE_CUBIC [2] : Natural cubic spline (cubspl)
 *	  mode = GMT_SPLINE_CUBIC [3] : Smooth cubic spline
 *    mode = GMT_SPLINE_NN [4]    : No interpolation (closest point)
 *    mode = GMT_SPLINE_STEP [5]  : Step interpolation (repeat output until next input node reached)
 *	  derivative_level = 0 :	The spline values
 *	  derivative_level = 1 :	The spline's 1st derivative
 *	  derivative_level = 2 :	The spline 2nd derivative
 * output: v = y-values at interpolated points
 * PS. v must have space allocated before calling gmt_intpol
 *
 * Programmer:	Paul Wessel
 * Date:	16-MAR-2009
 * Ver:		v.3.0
 * Now y can contain NaNs and we will interpolate within segments of clean data
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 */

/*! . */
int gmt_intpol (struct GMT_CTRL *GMT, double *x, double *y, double *w, uint64_t n, uint64_t m, double *u, double *v, double p, int mode) {
	uint64_t i, this_n, this_m, start_i, start_j, stop_i, stop_j;
	int err_flag = 0, smode, deriv;
	bool down = false, check = true, clean = true;
	double dx, *wp = NULL;

	if (mode < 0) {	/* No need to check for sanity */
		check = false;
		mode = -mode;
	}
	smode = mode % GMT_SPLINE_SLOPE;	/* Get spline method first */
	deriv = mode / GMT_SPLINE_SLOPE;	/* Get spline derivative order [0-2] */
	if (smode > GMT_SPLINE_STEP) smode = GMT_SPLINE_LINEAR;	/* Default to linear */
	if (smode != GMT_SPLINE_STEP && n < 4) smode = GMT_SPLINE_LINEAR;	/* Default to linear if 3 or fewer points, unless when nearest neighbor */
	if (n < 2) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Need at least 2 x-values\n");
		return (GMT_DIM_TOO_SMALL);
	}
	mode = smode + GMT_SPLINE_SLOPE * deriv;	/* Reassemble the possibly new mode */
	if (check) {
		/* Check to see if x-values are monotonically increasing/decreasing */

		dx = x[1] - x[0];
		if (gmt_M_is_dnan (y[0])) clean = false;
		if (dx > 0.0) {
			for (i = 2; i < n && err_flag == 0; i++) {
				if ((x[i] - x[i-1]) <= 0.0) err_flag = (int)i;
				if (clean && gmt_M_is_dnan (y[i])) clean = false;
			}
		}
		else {
			down = true;
			for (i = 2; i < n && err_flag == 0; i++) {
				if ((x[i] - x[i-1]) >= 0.0) err_flag = (int)i;
				if (clean && gmt_M_is_dnan (y[i])) clean = false;
			}
		}

		if (err_flag) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "x-values are not monotonically increasing/decreasing (at zero-based record %d)!\n", err_flag);
			return (err_flag);
		}

	}

	if (down) gmtsupport_intpol_reverse (x, u, n, m);	/* Must flip directions temporarily */

	if (clean) {	/* No NaNs to worry about */
		err_flag = gmtsupport_intpol_sub (GMT, x, y, w, n, m, u, v, p, mode);
		if (err_flag != GMT_NOERROR) return (err_flag);
		if (down) gmtsupport_intpol_reverse (x, u, n, m);	/* Must flip directions back */
		return (GMT_NOERROR);
	}

	/* Here input has NaNs so we need to treat it section by section */

	for (i = 0; i < m; i++) v[i] = GMT->session.d_NaN;	/* Initialize all output to NaN */
	start_i = start_j = 0;
	while (start_i < n && gmt_M_is_dnan (y[start_i])) start_i++;	/* First non-NaN data point */
	while (start_i < n && start_j < m) {
		stop_i = start_i + 1;
		while (stop_i < n && !gmt_M_is_dnan (y[stop_i])) stop_i++;	/* Wind to next NaN point (or past end of array) */
		this_n = stop_i - start_i;	/* Number of clean points to interpolate from */
		stop_i--;			/* Now stop_i is the ID of the last usable point */
		if (this_n == 1) {		/* Not enough to interpolate, just skip this single point */
			start_i++;	/* Skip to next point (which is NaN) */
			while (start_i < n && gmt_M_is_dnan (y[start_i])) start_i++;	/* Wind to next non-NaN data point */
			continue;
		}
		/* OK, have enough points to interpolate; find corresponding output section */
		while (start_j < m && u[start_j] < x[start_i]) start_j++;
		if (start_j == m) continue;	/* Ran out of points */
		stop_j = start_j;
		while (stop_j < m && u[stop_j] <= x[stop_i]) stop_j++;
		this_m = stop_j - start_j;	/* Number of output points to interpolate to */
		wp = (w) ? &w[start_j] : NULL;
		err_flag = gmtsupport_intpol_sub (GMT, &x[start_i], &y[start_i], wp, this_n, this_m, &u[start_j], &v[start_j], p, mode);
		if (err_flag != GMT_NOERROR) return (err_flag);
		start_i = stop_i + 1;	/* Move to point after last usable point in current section */
		while (start_i < n && gmt_M_is_dnan (y[start_i])) start_i++;	/* Next section's first non-NaN data point */
	}

	if (down) gmtsupport_intpol_reverse (x, u, n, m);	/* Must flip directions back */

	return (GMT_NOERROR);
}

/*! . */
void gmtlib_inplace_transpose (gmt_grdfloat *A, unsigned int n_rows, unsigned int n_cols) {
	/* In-place transpose of a gmt_grdfloat grid array.  Based on example
	 * code from http://www.geeksforgeeks.org/inplace-m-x-n-size-matrix-transpose
	 * Switched to C-style bit flag.
	 */
	uint64_t size = ((uint64_t)n_rows) * ((uint64_t)n_cols) - 1ULL;
	gmt_grdfloat t;	/* holds element to be replaced, eventually becomes next element to move */
	uint64_t next;	/* location of 't' to be moved */
	uint64_t cycleBegin;	/* holds start of cycle */
	uint64_t i;	/* iterator */
	uint64_t n_words = ((size + 1ULL) / 32ULL) + 1ULL;
	unsigned int *mark = NULL;
	unsigned int bits[32];

	mark = calloc (n_words, sizeof (unsigned int));
	for (i = 1, bits[0] = 1; i < 32; i++) bits[i] = bits[i-1] << 1;
	gmtsupport_set_bit (mark, 0ULL, bits);
	gmtsupport_set_bit (mark, size, bits);
	i = 1;	/* Note that A[0] and A[size-1] won't move */
	while (i < size) {
		cycleBegin = i;
		t = A[i];
		do {
			next = (i * n_rows) % size;
			gmt_M_float_swap (A[next], t);
			gmtsupport_set_bit (mark, i, bits);
			i = next;
		}
		while (i != cycleBegin);

		/* Get Next Move (what about querying random location?) */
		for (i = 1; i < size && gmtsupport_is_set (mark, i, bits); i++);
	}
	gmt_M_str_free (mark);
}

/*! . */
void gmt_contlabel_init (struct GMT_CTRL *GMT, struct GMT_CONTOUR *G, unsigned int mode) {
	/* Assign default values to structure */
	gmt_M_memset (G, 1, struct GMT_CONTOUR);	/* Sets all to 0 */
	if (mode == 1) {
		G->line_type = 1;
		strcpy (G->line_name, "Contour");
	}
	else {
		G->line_type = 0;
		strcpy (G->line_name, "Line");
	}
	snprintf (G->label_file, PATH_MAX, "%s_labels.txt", G->line_name);
	G->must_clip = true;
	G->draw = true;
	G->spacing = true;
	G->half_width = UINT_MAX;	/* Auto */
	G->label_dist_frac = 0.25;	/* Fraction of above head start for closed labels */
	G->box = 2;			/* Rect box shape is Default */
	G->label_dist_spacing = (GMT->current.setting.proj_length_unit == GMT_CM) ? 10.0 / 2.54 : 4.0;	/* Inches */
	G->clearance[GMT_X] = G->clearance[GMT_Y] = 15.0;	/* 15 % */
	G->clearance_flag = 1;	/* Means we gave percentages of label font size */
	G->just = PSL_MC;
	G->font_label = GMT->current.setting.font_annot[GMT_PRIMARY];	/* FONT_ANNOT_PRIMARY */
	G->font_label.size = 9.0;
	G->font_label.set = 0;
	G->dist_unit = GMT->current.setting.proj_length_unit;
	G->pen = GMT->current.setting.map_default_pen;
	G->debug_pen = GMT->current.setting.map_default_pen;
	G->line_pen = GMT->current.setting.map_default_pen;
	gmt_M_rgb_copy (G->rgb, GMT->current.setting.ps_page_rgb);		/* Default box color is page color [nominally white] */
}

GMT_LOCAL int gmtsupport_is_cpt_file (struct GMT_CTRL *GMT, char *file) {
	/* Read a file that may be a CPT file or a contour listing file.  We will return
	 * 0 if it is a contour file, 1 if a CPT and -1 if we get read errors.
	 * Because a non-commented record in a contour listing file is of the format
	 *   cval [[angle] C|A|c|a [pen]]] OR  cval C|A|c|a [angle [pen]] (deprecated format),
	 * we can uniquely determine if it is that sort of file by finding the lone
	 * character A|a|C|c between white space on the left and white space or NULL on right.
	 * If that is not found then it must be a CPT file, unless only one column is found.
	 */
	int n, answer = 1;	/* Default response is that this is a CPT file, flagged as 1 */
	char *txt = NULL, *c = NULL, A[GMT_LEN64] = {""}, B[GMT_LEN64] = {""};
	unsigned int k = 0;
	struct GMT_DATASET *C = NULL;

	if ((C = GMT_Read_Data (GMT->parent, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_TEXT, GMT_IO_ASCII, NULL, file, NULL)) == NULL) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Unable to read potential CPT or contour information file %s\n", file);
		return (-1);
	}
	if (C->n_records == 0) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "No records found in CPT or contour information file %s\n", file);
		return (-1);
	}
	if (C->table[0]->segment[0]->text == NULL || (txt = C->table[0]->segment[0]->text[0]) == NULL) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "No text records found in CPT or contour information file %s\n", file);
		return (-1);
	}
	if ((c = strchr (txt, ';'))) c[0] = '\0';	/* Chop off optional CPT labels since they may have text that can trick us */
	n = sscanf (txt, "%s %s", A, B);	/* See if we can read 2 items */
	while (txt[k] && !(txt[k] == '\t' || txt[k] == ' ')) k++;	/* Scan to first occurrence of white space, thus skipping <cval> */
	while (txt[k] && strchr ("AaCc", txt[k]) == NULL) k++;		/* Scan to first occurrence of one of the key letters */
	if (n == 1 || ((k && (txt[k-1] == '\t' || txt[k-1] == ' ')) && (txt[k] && (txt[k+1] == '\t' || txt[k+1] == ' ' || txt[k+1] == '\0'))))
		answer = 0;	/* Yes, this is a contour file */
	if (c) c[0] = ';';	/* Restore semicolon to be nice */

	if (GMT_Destroy_Data (GMT->parent, &C)) {
		GMT_Report (GMT->parent, GMT_MSG_WARNING, "Unable to free memory for contour information file %s\n", file);
	}

	if (answer)
		GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "File %s assumed to be a CPT file\n", file);
	else
		GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "File %s determined to be a contour information file\n", file);

	return (answer);	/* If we find a recognized contour type then we return true */
}


unsigned int gmt_contour_C_arg_parsing (struct GMT_CTRL *GMT, char *arg, struct CONTOUR_ARGS *A) {
	unsigned int n_errors = 0;
	struct GMTAPI_CTRL *API = GMT->parent;

	/* Parse the -C<arg> options for grdcontour and pscontour */

	if (gmt_M_no_cpt_given (arg)) {
		if (GMT->current.setting.run_mode == GMT_MODERN)
			A->check = true;	/* Must see (after parsing) if there is a current CPT in this modern mode session */
		else {
			GMT_Report (API, GMT_MSG_ERROR, "Option -C: No argument given\n");
			n_errors++;
		}
	}
	else if (gmt_M_file_is_memory (arg)) {	/* Passed a CPT memory reference from a module */
		A->interval = 1.0;	/* This takes us past a check only */
		A->cpt = true;
		gmt_M_str_free (A->file);
		A->file = strdup (arg);
	}
	else if (!gmt_access (GMT, arg, R_OK)) {	/* Gave a readable file (CPT or contour file) */
		int answer;
		A->interval = 1.0;	/* This takes us past a check only */
		if ((answer = gmtsupport_is_cpt_file (GMT, arg)) == -1)
			n_errors++;
		else	
			A->cpt = (answer == 1);
		gmt_M_str_free (A->file);
		A->file = strdup (arg);
	}
	else if (strchr (arg, ',')) {	/* Gave a comma-separated list of one or more contours */
		A->interval = 1.0;	/* This takes us past a check only */
		gmt_M_str_free (A->file);
		A->file = strdup (arg);
	}
	else if (arg[0] == '+' && (isdigit(arg[1]) || strchr ("-+.", arg[1]))) {
		if (!gmt_M_compat_check (GMT, 5))
			GMT_Report (API, GMT_MSG_COMPAT, "Option -C: Specifying single contour with leading + is deprecated.  Please use -C<cont>, instead\n");
		A->single_cont = atof (&arg[1]);
	}
	else if (arg[0] != '-') {	/* Constant contour interval */
		A->interval = atof (arg);
		if (gmt_M_is_zero (A->interval)) {
			GMT_Report (API, GMT_MSG_ERROR, "Option -C: Contour interval cannot be zero\n");
			n_errors++;
		}
	}
	else {
		GMT_Report (API, GMT_MSG_ERROR, "Option -C: Contour interval cannot be negative (%s)\n", arg);
		n_errors++;
	}
	return (n_errors);
}

unsigned int gmt_contour_first_pos (struct GMT_CTRL *GMT, char *arg) {
	/* Because of backwards compatibility, we need to anticipate shits like -A+1 for a
	 * single annotated contour and hence cannot confuse it with a modifier for contour specs.
	 * Thus, here we scan past any leading single contour specification using deprecated syntax. */
	unsigned int k = 1;
	gmt_M_unused(GMT);
	if (arg[0] != '+') return 0;	/* Start checking from start */
	if (isalpha (arg[1]) || arg[1] == '=') return 0;	/* Standard modifier */
	/* Here we must have +<value> which we wish to skip */
	if (arg[k] == '+') k++;	/* Must step over a signed contour since ++2 and +-2 were OK back then */
	while (arg[k] && arg[k] != '+') k++;
	return k;
}

unsigned int gmt_contour_A_arg_parsing (struct GMT_CTRL *GMT, char *arg, struct CONTOUR_ARGS *A) {
	unsigned int n_errors = 0;
	struct GMTAPI_CTRL *API = GMT->parent;

	/* Parse the -A<arg> options for grdcontour and pscontour after contour-specs are stripped off */
	if (arg[0] == '\0') return GMT_NOERROR;	/* Probably the -A was just setting contour parameters via modifiers */

	if (arg[0] == 'n' && arg[1] == '\0')	/* -An turns off all labels */
		A->mode = 1;	/* Turn off all labels */
	else if (arg[0] == '+' && (isdigit(arg[1]) || strchr ("-+.", arg[1]))) {
		if (!gmt_M_compat_check (GMT, 5))
			GMT_Report (API, GMT_MSG_COMPAT, "Option -A: Specifying single contour with leading + is deprecated.  Please use -A<cont>, instead\n");
		A->single_cont = atof (&arg[1]);
	}
	else if (strchr (arg, ',')) {	/* Gave a comma-separated list of one or more annotated contours */
		gmt_M_str_free (A->file);
		A->file = strdup (arg);
	}
	else if (arg[0] == '-' && arg[1] == '\0') {	/* -A- is deprecated version of -An */
		if (!gmt_M_compat_check (GMT, 5))
			GMT_Report (API, GMT_MSG_COMPAT, "Option -A: Turning off annotations with -A- is deprecated.  Please use -An instead\n");
		A->mode = 1;	/* Turn off all labels */
	}
	else if (arg[0] != '-') {	/* Constant annotated contour interval */
		A->interval = atof (arg);
		if (gmt_M_is_zero (A->interval)) {
			GMT_Report (API, GMT_MSG_ERROR, "Option -A: Contour interval cannot be zero\n");
			n_errors++;
		}
	}
	else {
		GMT_Report (API, GMT_MSG_ERROR, "Option -A: Annotated contour interval cannot be negative (%s)\n", arg);
		n_errors++;
	}
	return n_errors;
}

GMT_LOCAL unsigned int gmtsupport_contour_old_T_parser (struct GMT_CTRL *GMT, char *arg, struct CONTOUR_CLOSED *I) {
	/* The backwards compatible parser for old-style -T option: */
	/* -T[+|-][<gap>[c|i|p]/<length>[c|i|p]][:LH] but also accept new -Th|l<...> */
	int n, j;
	unsigned int n_errors = 0;
	char txt_a[GMT_LEN256] = {""}, txt_b[GMT_LEN256] = {""};
	if (strchr (arg, '/')) {	/* Gave gap/length */
		n = sscanf (arg, "%[^/]/%[^:]", txt_a, txt_b);
		if (n == 2) {
			I->dim[GMT_X] = gmt_M_to_inch (GMT, txt_a);
			I->dim[GMT_Y] = gmt_M_to_inch (GMT, txt_b);
		}
	}
	for (j = 0; arg[j] && arg[j] != ':'; j++);
	if (arg[j] == ':') I->label = true, j++;
	if (arg[j]) {	/* Override high/low markers */
		if (strlen (&(arg[j])) == 2) {	/* Standard :LH syntax */
			txt_a[0] = arg[j++];	txt_a[1] = '\0';
			txt_b[0] = arg[j++];	txt_b[1] = '\0';
		}
		else if (strchr (&(arg[j]), ',')) {	/* Found :<labellow>,<labelhigh> */
			sscanf (&(arg[j]), "%[^,],%s", txt_a, txt_b);
		}
		else {
			GMT_Report (GMT->parent, GMT_MSG_ERROR,
			            "Option -T: Give low and high labels either as :LH or :<low>,<high>.\n");
			I->label = false;
			n_errors++;
		}
		if (I->label) {	/* Replace defaults */
			I->txt[0] = strdup (txt_a);
			I->txt[1] = strdup (txt_b);
		}
	}
	return (n_errors);
}

unsigned int gmt_contour_T_arg_parsing (struct GMT_CTRL *GMT, char *arg, struct CONTOUR_CLOSED *I) {
	unsigned int j = 0, n_errors = 0;
	int n;
	char string[GMT_LEN256] = {""};
	char txt_a[GMT_LEN256] = {""}, txt_b[GMT_LEN256] = {""};
	struct GMTAPI_CTRL *API = GMT->parent;

	/* Parse the -T<arg> options for grdcontour and pscontour */

	I->high = I->low = true;	/* Default if just -T is given */
	if (arg[0]) {	/* But here we gave more options */
		if (arg[0] == 'h' || (arg[0] == '+' && !strchr ("adl", arg[1])))			/* Only tick local highs */
			I->low = false, j = 1;
		else if (arg[0] == 'l' || arg[0] == '-')	/* Only tick local lows */
			I->high = false, j = 1;
		else
			j = 0;
		if (gmt_found_modifier (GMT, arg, "adl")) {	/* New parser */
			if (gmt_validate_modifiers (GMT, arg, 'T', "adl", GMT_MSG_ERROR)) n_errors++;
			if (gmt_get_modifier (arg, 'a', string))
				I->all = true;
			if (gmt_get_modifier (arg, 'd', string))
				if ((n = gmt_get_pair (GMT, string, GMT_PAIR_DIM_NODUP, I->dim)) < 1) n_errors++;
			if (gmt_get_modifier (arg, 'l', string)) {	/* Want to label innermost contours */
				I->label = true;
				if (string[0] == 0)
					;	/* Use default labels */
				else if (strlen (string) == 2) {	/* Standard +lLH syntax */
					char A[2] = {0, 0};
					A[0] = string[0];	I->txt[0] = strdup (A);
					A[0] = string[1];	I->txt[1] = strdup (A);
				}
				else if (strchr (string, ',') && (n = sscanf (string, "%[^,],%s", txt_a, txt_b)) == 2) {	/* Found :<labellow>,<labelhigh> */
					I->txt[0] = strdup (txt_a);
					I->txt[1] = strdup (txt_b);
				}
				else {
					GMT_Report (API, GMT_MSG_ERROR,
					            "Option -T: Give low and high labels either as +lLH or +l<low>,<high>.\n");
					n_errors++;
				}
			}
		}
		else {
			if (gmt_M_compat_check (API->GMT, 4))  {
				GMT_Report (API, GMT_MSG_COMPAT, "Your format for -T is deprecated (but accepted); use -T[l|h][+d<tick_gap>[%s][/<tick_length>[%s]]][+lLH] instead\n",
				            GMT_DIM_UNITS_DISPLAY, GMT_DIM_UNITS_DISPLAY);
				n_errors += gmtsupport_contour_old_T_parser (GMT, &arg[j], I);
			}
			else {
				GMT_Report (API, GMT_MSG_COMPAT, "Option -T: Your format for -T is deprecated; use -T[l|h][+d<tick_gap>[%s][/<tick_length>[%s]]][+lLH] instead\n",
				            GMT_DIM_UNITS_DISPLAY, GMT_DIM_UNITS_DISPLAY);
				n_errors++;
			}
		}
		n_errors += gmt_M_check_condition (GMT, I->dim[GMT_X] <= 0.0 || I->dim[GMT_Y] == 0.0,
		                                   "Option -T: Expected\n\t-T[l|h][+d<tick_gap>[%s][/<tick_length>[%s]]][+lLH], <tick_gap> must be > 0\n",
		                                   GMT_DIM_UNITS_DISPLAY, GMT_DIM_UNITS_DISPLAY);
	}

	return (n_errors);
}

/*! . */
int gmt_contlabel_specs (struct GMT_CTRL *GMT, char *txt, struct GMT_CONTOUR *G) {
	unsigned int k = 0, bad = 0, pos = 0;
	size_t L;
	char p[GMT_BUFSIZ] = {""}, txt_a[GMT_LEN256] = {""}, txt_b[GMT_LEN256] = {""}, c;
	char *specs = NULL;

	/* Decode [+a<angle>|n|p[u|d]][+c<dx>[/<dy>]][+d[<pen>]][+e][+f<font>][+g<fill>][+i][+j<just>][+l<label>][+n|N<dx>[/<dy>]][+o][+p[<pen>]][+r<min_rc>][+t[<file>]][+u<unit>][+v][+w<width>][+x|X<suffix>][+=<prefix>] strings */

	/* txt is pointing to the very first modifier */

	G->nudge_flag = 0;
	G->draw = true;

	if (txt == NULL || !txt[k]) return (0);

	/* Decode new-style +separated substrings */

	specs = &txt[k+1];
	while ((gmt_strtok (specs, "+", &pos, p))) {
		switch (p[0]) {
			case 'a':	/* Angle specification */
				if (p[1] == 'p' || p[1] == 'P')	{	/* Line-parallel label */
					G->angle_type = G->hill_label = GMT_ANGLE_LINE_PARALLEL;
					if (p[2] == 'u' || p[2] == 'U')		/* Line-parallel label readable when looking up hill */
						G->hill_label = +1;
					else if (p[2] == 'd' || p[2] == 'D')	/* Line-parallel label readable when looking down hill */
						G->hill_label = -1;
				}
				else if (p[1] == 'n' || p[1] == 'N')	/* Line-normal label */
					G->angle_type = GMT_ANGLE_LINE_NORMAL;
				else {					/* Label at a fixed angle */
					G->label_angle = atof (&p[1]);
					G->angle_type = GMT_ANGLE_LINE_FIXED;
					gmt_lon_range_adjust (GMT_IS_M180_TO_P180_RANGE, &G->label_angle);	/* Now -180/+180 */
					while (fabs (G->label_angle) > 90.0) G->label_angle -= copysign (180.0, G->label_angle);
				}
				break;

			case 'c':	/* Clearance specification */
				k = sscanf (&p[1], "%[^/]/%s", txt_a, txt_b);
				G->clearance_flag = ((strchr (txt_a, '%')) ? 1 : 0);
				if (G->clearance_flag) {	/* Chop off percentage sign(s) and read as unitless values */
					if ((L = strlen (txt_a)) && txt_a[L-1] == '%') txt_a[L-1] = '\0';
					G->clearance[GMT_X] = atof (txt_a);
					if (k == 2 && (L = strlen (txt_b)) && txt_b[L-1] == '%') txt_b[L-1] = '\0';
					G->clearance[GMT_Y] = (k == 2) ? atof (txt_b) : G->clearance[GMT_X];
				}
				else {	/* Deal with units */
					G->clearance[GMT_X] = gmt_M_to_inch (GMT, txt_a);
					G->clearance[GMT_Y] = (k == 2 ) ? gmt_M_to_inch (GMT, txt_b) : G->clearance[GMT_X];
				}
				if (k == 0) bad++;
				break;

			case 'd':	/* Debug option - draw helper points or lines */
				G->debug = true;
				if (p[1] && gmt_getpen (GMT, &p[1], &G->debug_pen)) bad++;
				break;

			case 'e':	/* Just lay down text info; Delay actual label plotting until a psclip -C call */
				G->delay = true;
				break;

			case 'f':	/* Font specification */
				if (gmt_getfont (GMT, &p[1], &G->font_label)) bad++;
				break;

			case 'g':	/* Box Fill specification */
				if (p[1] && gmt_getrgb (GMT, &p[1], G->rgb)) bad++;
				G->fillbox = true;
				G->must_clip = (G->rgb[3] > 0.0);	/* May still be transparent if gave transparency; else opaque */
				break;

			case 'h':	/* Hide the lines used to place labels [Was this ever documented? If not, remove] */
			case 'i':	/* Make line invisible */
				G->draw = false;
				break;

			case 'j':	/* Justification specification */
				txt_a[0] = p[1];	txt_a[1] = p[2];	txt_a[2] = '\0';
				G->just = gmt_just_decode (GMT, txt_a, PSL_MC);
				break;
			case 'k':	/* Font color specification (backwards compatibility only since font color is now part of font specification */
				if (gmt_M_compat_check (GMT, 4)) {
					GMT_Report (GMT->parent, GMT_MSG_COMPAT,
					            "+k<fontcolor> in contour label spec is obsolete, now part of +f<font>\n");
					if (gmt_getfill (GMT, &p[1], &(G->font_label.fill))) bad++;
				}
				else
					bad++;
				break;
			case 'l':	/* Exact Label specification */
				strncpy (G->label, &p[1], GMT_BUFSIZ-1);
				G->label_type = GMT_LABEL_IS_CONSTANT;
				break;

			case 'L':	/* Label code specification */
				switch (p[1]) {
					case 'h':	/* Take the first string in segment headers */
						G->label_type = GMT_LABEL_IS_HEADER;
						break;
					case 'd':	/* Use the current plot distance in chosen units */
						G->label_type = GMT_LABEL_IS_PDIST;
						G->dist_unit = gmtlib_unit_lookup (GMT, p[2], GMT->current.setting.proj_length_unit);
						break;
					case 'D':	/* Use current map distance in chosen units */
						G->label_type = GMT_LABEL_IS_MDIST;
						if (p[2] && strchr ("defkMn", (int)p[2])) {	/* Found a valid unit */
							c = p[2];
							if (gmt_init_distaz (GMT, c, gmt_M_sph_mode (GMT), GMT_LABEL_DIST) == GMT_NOT_A_VALID_TYPE) bad++;
						}
						else 	/* Meaning "not set" */
							c = 0;
						G->dist_unit = (int)c;
						break;
					case 'f':	/* Take the 3rd column in fixed contour location file */
						G->label_type = GMT_LABEL_IS_FFILE;
						break;
					case 'x':	/* Take the first string in segment headers in the crossing file */
						G->label_type = GMT_LABEL_IS_XFILE;
						break;
					case 'n':	/* Use the current segment number */
						G->label_type = GMT_LABEL_IS_SEG;
						break;
					case 'N':	/* Use <current file number>/<segment number> */
						G->label_type = GMT_LABEL_IS_FSEG;
						break;
					default:	/* Probably meant lower case l */
						strncpy (G->label, &p[1], GMT_BUFSIZ-1);
						G->label_type = GMT_LABEL_IS_HEADER;
						break;
				}
				break;

			case 'n':	/* Nudge specification; dx/dy are increments along local line axes */
				G->nudge_flag = 1;
				/* Intentionally fall through - to 'N' */
			case 'N':	/* Nudge specification; dx/dy are increments along plot axes */
				G->nudge_flag++;
				k = sscanf (&p[1], "%[^/]/%s", txt_a, txt_b);
				G->nudge[GMT_X] = gmt_M_to_inch (GMT, txt_a);
				G->nudge[GMT_Y] = (k == 2 ) ? gmt_M_to_inch (GMT, txt_b) : G->nudge[GMT_X];
				if (k == 0) bad++;
				break;
			case 'o':	/* Use rounded rectangle textbox shape */
				G->box = 4 + (G->box & 1);
				break;

			case 'p':	/* Draw text box outline [with optional textbox pen specification] */
				if (p[1] && gmt_getpen (GMT, &p[1], &G->pen)) bad++;
				G->box |= 1;
				break;

			case 'r':	/* Minimum radius of curvature specification */
				G->min_radius = gmt_M_to_inch (GMT, &p[1]);
				break;

			case 's':	/* Font size specification (for backward compatibility only since size is part of font specification) */
				if (gmt_M_compat_check (GMT, 4)) {
					GMT_Report (GMT->parent, GMT_MSG_COMPAT, "+s<fontsize> in contour label spec is obsolete, now part of +f<font>\n");
					G->font_label.size = gmt_convert_units (GMT, &p[1], GMT_PT, GMT_PT);
					if (G->font_label.size <= 0.0) bad++;
				}
				else
					bad++;
				break;

			case 'T':	/* Deprecated, just give a warning that it is the same as +t and deliberately fall through to case 't' */
				if (gmt_M_compat_check (GMT, 6))
					GMT_Report (GMT->parent, GMT_MSG_COMPAT, "+T in contour label spec is deprecated; only +t is supported\n");
				else {
					bad++;
					break;
				}
			case 't':	/* Save contour label locations to given file [x y angle label] */
				G->save_labels = 1;
				if (p[1]) strncpy (G->label_file, &p[1], PATH_MAX-1);
				break;

			case 'u':	/* Label Unit specification */
				if (p[1]) strncpy (G->unit, &p[1], GMT_LEN64-1);
				break;

			case 'v':	/* Curved text [Default is straight] */
				G->curved_text = true;
				break;

			case 'w':	/* Angle filter width [Default is auto] */
				G->half_width = atoi (&p[1]) / 2;
				break;

			case 'x':	/* Crossection labeling for SqN2 only; add given text to start and end label */
				if (!G->number || G->n_cont != 2) {
					GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -Sq: The +x modifier is only valid with -SqN2\n");
					bad++;
				}
				else {
					G->crossect = true;
					if (p[1])
						sscanf (&p[1], "%[^,],%s", G->crossect_tag[0], G->crossect_tag[1]);
					else {	/* Default is to prime the end annotation only */
						G->crossect_tag[0][0] = '\0';
						strcpy (G->crossect_tag[1], "'");
					}
				}
				break;

			case '=':	/* Label Prefix specification */
				if (p[1]) strncpy (G->prefix, &p[1], GMT_LEN64-1);
				break;

			default:
				bad++;
				break;
		}
	}
	if (G->curved_text && G->nudge_flag) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Cannot combine +v and +n\n");
		bad++;
	}
	return (bad);
}

/*! . */
int gmt_contlabel_info (struct GMT_CTRL *GMT, char flag, char *txt, struct GMT_CONTOUR *L) {
	/* Interpret the contour-label information string and set structure items */
	int k, j = 0, error = 0;
	char txt_a[GMT_LEN256] = {""}, c, arg, *p = NULL;

	L->spacing = false;	/* Turn off the default since we gave an option */
	strncpy (L->option, &txt[1], GMT_BUFSIZ-1);	 /* May need to process L->option later after -R,-J have been set */
	if ((p = strstr (txt, "+r"))) {	/* Want to isolate labels by given radius */
		*p = '\0';	/* Temporarily chop off the +r<radius> part */
		L->isolate = true;
		L->label_isolation = gmt_M_to_inch (GMT, &p[2]);
	}
	L->flag = flag;
	/* Special check for quoted lines */
	if (txt[0] == 'S' || txt[0] == 's') {	/* -SqS|n should be treated as -SqN|n once file is segmentized */
		arg = (txt[0] == 'S') ? 'N' : 'n';	/* S -> N and s -> n */
		L->segmentize = true;
	}
	else
		arg = txt[0];

	switch (arg) {
		case 'L':	/* Quick straight lines for intersections */
			L->do_interpolate = true;
			/* Intentionally fall through - to 'l' */
		case 'l':
			L->crossing = GMT_CONTOUR_XLINE;
			break;
		case 'N':	/* Specify number of labels per segment */
			L->number_placement = 1;	/* Distribution of labels */
			if (txt[1] == '-') L->number_placement = -1, j = 1;	/* Left label if n = 1 */
			if (txt[1] == '+') L->number_placement = +1, j = 1;	/* Right label if n = 1 */
			/* Intentionally fall through - to 'n' */
		case 'n':	/* Specify number of labels per segment */
			L->number = true;
			k = sscanf (&txt[1+j], "%d/%s", &L->n_cont, txt_a);
			if (k == 2) L->min_dist = gmt_M_to_inch (GMT, txt_a);
			if (L->n_cont == 0) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Number of labels must exceed zero\n", L->flag);
				error++;
			}
			if (L->min_dist < 0.0) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Minimum label separation cannot be negative\n", L->flag);
				error++;
			}
			break;
		case 'f':	/* Fixed points file */
			L->fixed = true;
			k = sscanf (&txt[1], "%[^/]/%lf", L->file, &L->slop);
			if (k == 1) L->slop = GMT_CONV8_LIMIT;
			if (gmt_access (GMT, L->file, R_OK)) {	/* Cannot read/find file */
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Cannot find/read fixed point file %s\n", L->flag, L->file);
				error++;
			}
			break;
		case 'X':	/* Crossing complicated curve */
			L->do_interpolate = true;
			/* Intentionally fall through - to 'x' */
		case 'x':	/* Crossing line */
			L->crossing = GMT_CONTOUR_XCURVE;
			strncpy (L->file, &txt[1], PATH_MAX-1);
			if (gmt_access (GMT, L->file, R_OK)) {	/* Cannot read/find file */
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Cannot find/read crossing line file %s\n", L->flag, L->file);
				error++;
			}
			break;
		case 'D':	/* Specify distances in geographic units (km, degrees, etc) */
			L->dist_kind = 1;
			/* Intentionally fall through - to 'd' */
		case 'd':	/* Specify distances in plot units [cip] */
			L->spacing = true;
			k = sscanf (&txt[j], "%[^/]/%lf", txt_a, &L->label_dist_frac);
			if (k == 1) L->label_dist_frac = 0.25;
			if (L->dist_kind == 1) {	/* Distance units other than xy specified */
				k = (int)strlen (txt_a) - 1;
				c = (isdigit ((int)txt_a[k]) || txt_a[k] == '.') ? 0 : txt_a[k];
				L->label_dist_spacing = atof (&txt_a[1]);
				if (gmt_init_distaz (GMT, c, gmt_M_sph_mode (GMT), GMT_CONT_DIST) == GMT_NOT_A_VALID_TYPE) error++;
			}
			else
				L->label_dist_spacing = gmt_M_to_inch (GMT, &txt_a[1]);
			if (L->label_dist_spacing <= 0.0) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Spacing between labels must exceed 0.0\n", L->flag);
				error++;
			}
			if (L->label_dist_frac < 0.0 || L->label_dist_frac > 1.0) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Initial label distance fraction must be in 0-1 range\n", L->flag);
				error++;
			}
			break;
		default:
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Unrecognized modifier %c\n", L->flag, txt[0]);
			error++;
			break;
	}
	if (p && L->isolate) *p = '+';	/* Replace the + from earlier */

	return (error);
}

/*! . */
void gmtlib_decorate_init (struct GMT_CTRL *GMT, struct GMT_DECORATE *G, unsigned int mode) {
	/* Assign default values to structure */

	gmtsupport_decorate_free (GMT, G);	/* In case we've been here before we must free stuff first */

	gmt_M_memset (G, 1, struct GMT_DECORATE);	/* Sets all to 0 */
	if (mode == 1) {
		G->line_type = 1;
		strcpy (G->line_name, "Contour");
	}
	else {
		G->line_type = 0;
		strcpy (G->line_name, "Line");
	}
	G->spacing = true;
	G->half_width = UINT_MAX;	/* Auto */
	G->symbol_dist_spacing = 4.0;	/* Inches */
	G->symbol_dist_frac = 0.25;	/* Fraction of above head start for closed lines */
	if (GMT->current.setting.proj_length_unit == GMT_CM) G->symbol_dist_spacing = 10.0 / 2.54;
}

/*! . */
int gmtlib_decorate_specs (struct GMT_CTRL *GMT, char *txt, struct GMT_DECORATE *G) {
	unsigned int k, bad = 0, pos = 0;
	char p[GMT_BUFSIZ] = {""}, txt_a[GMT_LEN256] = {""}, txt_b[GMT_LEN256] = {""};
	char *specs = NULL;

	/* Decode [+a<angle>|n|p[u|d]][+d[<pen>]][+g<fill>][+i][+n|N<dx>[/<dy>]][+p[<pen>]]+s<symbolinfo>[+w<width>] strings */

	for (k = 0; txt[k] && txt[k] != '+'; k++);	/* Look for +<options> strings */

	if (!txt[k]) return (0);

	/* Decode new-style +separated substrings */

	G->nudge_flag = 0;
	G->fill[0] = G->pen[0] = '\0';	/* Reset each time in case we are parsing args from a segment header */
	specs = &txt[k+1];
	while ((gmt_strtok (specs, "+", &pos, p))) {
		switch (p[0]) {
			case 'a':	/* Angle specification */
				if (p[1] == 'p' || p[1] == 'P')	{ /* Line-parallel label */
					if (p[2]) {	/* Gave optional fixed angle deviation from line-parallel */
						G->angle_type = GMT_ANGLE_LINE_DELTA;
						G->symbol_angle = atof (&p[2]);
						gmt_lon_range_adjust (GMT_IS_M180_TO_P180_RANGE, &G->symbol_angle);	/* Now -180/+180 */
						while (fabs (G->symbol_angle) > 90.0) G->symbol_angle -= copysign (180.0, G->symbol_angle);
					}
					else
						G->angle_type = GMT_ANGLE_LINE_PARALLEL;
				}
				else if (p[1] == 'n' || p[1] == 'N')	/* Line-normal label */
					G->angle_type = GMT_ANGLE_LINE_NORMAL;
				else {					/* Label at a fixed angle */
					G->symbol_angle = atof (&p[1]);
					G->angle_type = GMT_ANGLE_LINE_FIXED;
					gmt_lon_range_adjust (GMT_IS_M180_TO_P180_RANGE, &G->symbol_angle);	/* Now -180/+180 */
					while (fabs (G->symbol_angle) > 90.0) G->symbol_angle -= copysign (180.0, G->symbol_angle);
				}
				break;

			case 'd':	/* Debug option - draw helper points or lines */
				G->debug = true;
				if (p[1] && gmt_getpen (GMT, &p[1], &G->debug_pen)) bad++;
				break;

			case 'g':	/* Symbol Fill specification */
				if (p[1]) strncpy (G->fill, &p[1], GMT_LEN64-1);
				break;

			case 'i':	/* Invisible main line (do not draw line) */
				G->invisible = true;
				break;

			case 'n':	/* Nudge specification; dx/dy are increments along local line axes */
				G->nudge_flag = 1;
				/* Intentionally fall through - to 'N' */
			case 'N':	/* Nudge specification; dx/dy are increments along plot axes */
				G->nudge_flag++;
				k = sscanf (&p[1], "%[^/]/%s", txt_a, txt_b);
				G->nudge[GMT_X] = gmt_M_to_inch (GMT, txt_a);
				G->nudge[GMT_Y] = (k == 2 ) ? gmt_M_to_inch (GMT, txt_b) : G->nudge[GMT_X];
				if (k == 0) bad++;
				break;

			case 'p':	/* Set symbol outline specification */
				if (p[1]) strncpy (G->pen, &p[1], GMT_LEN64-1);
				break;

			case 's':	/* Symbol to place */
				if (p[1]) {
					if (strchr (GMT_DECORATE_SYMBOLS, p[1]) == NULL) {
						GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -S~: Symbol +%s not allowed!\n", &p[1]);
						bad++;
					}
					else if (p[1] == 'k') {	/* Custom symbol - separate file from size */
						char *s = strrchr (p, '/');
						if (s == NULL) {	/* No slash, no size */
							GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -S~: Custom symbol %s not given any size\n", &p[2]);
							bad++;
						}
						else {
							strncpy (G->size, &s[1], GMT_LEN64-1);
							if (gmt_not_numeric (GMT, G->size)) {
								GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -S~: Custom symbol %s not given a valid size\n", &p[2]);
								bad++;
							}
							else {	/* Size seems OK */
								s[0] = '\0';	/* Truncate size */
								strncpy (G->symbol_code, &p[1], GMT_LEN256-1);
								s[0] = '/';	/* Restore size */
								if (gmtlib_invalid_symbolname (GMT, G->symbol_code))
									bad++;
							}
						}
					}
					else {	/* Regular geometric symbol */
						strncpy (G->size, &p[2], GMT_LEN64-1);
						G->symbol_code[0] = p[1];
					}
				}
				break;
			case 'w':	/* Angle filter width [Default is auto] */
				G->half_width = atoi (&p[1]) / 2;
				break;

			case '.':	/* Assume it can be a decimal part without leading 0 */
			case '0':	/* A single annotated contour */
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				break;

			default:
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -S~: Modifier +%s not recognized!\n", p);
				bad++;
				break;
		}
	}
	if (G->symbol_code[0] == '\0') {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "No symbol specified!\n");
		bad++;
	}
	if (G->size[0] == '\0') {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "No symbol size specified!\n");
		bad++;
	}
	if (G->fill[0] == '\0' && G->pen[0] == '\0')	/* Neither fill nor pen - select default outline */
		sprintf (G->pen, "%s", gmt_putpen (GMT, &GMT->current.setting.map_default_pen));

	return (bad);
}

/*! . */
int gmtlib_decorate_info (struct GMT_CTRL *GMT, char flag, char *txt, struct GMT_DECORATE *L) {
	/* Interpret the contour-label information string and set structure items */
	int k, j = 0, error = 0;
	char txt_a[GMT_LEN256] = {""}, c, arg;

	L->spacing = false;	/* Turn off the default since we gave an option */
	strncpy (L->option, &txt[1], GMT_BUFSIZ-1);	 /* May need to process L->option later after -R,-J have been set */
	L->flag = flag;
	/* Special check for quoted lines */
	if (txt[0] == 'S' || txt[0] == 's') {	/* -SqS|n should be treated as -SqN|n once file is segmentized */
		arg = (txt[0] == 'S') ? 'N' : 'n';	/* S -> N and s -> n */
		L->segmentize = true;
	}
	else
		arg = txt[0];

	switch (arg) {
		case 'L':	/* Quick straight lines for intersections */
			L->do_interpolate = true;
			/* Intentionally fall through - to 'l' */
		case 'l':
			L->crossing = GMT_DECORATE_XLINE;
			break;
		case 'N':	/* Specify number of labels per segment */
			L->number_placement = 1;	/* Distribution of labels */
			if (txt[1] == '-') L->number_placement = -1, j = 1;	/* Left symbol if n = 1 */
			if (txt[1] == '+') L->number_placement = +1, j = 1;	/* Right symbol if n = 1 */
			/* Intentionally fall through - to 'n' */
		case 'n':	/* Specify number of labels per segment */
			L->number = true;
			k = sscanf (&txt[1+j], "%d/%s", &L->n_cont, txt_a);
			if (k == 2) L->min_dist = gmt_M_to_inch (GMT, txt_a);
			if (L->n_cont == 0) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Number of symbols must exceed zero\n", L->flag);
				error++;
			}
			if (L->min_dist < 0.0) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Minimum symbols separation cannot be negative\n", L->flag);
				error++;
			}
			break;
		case 'f':	/* Fixed points file */
			L->fixed = true;
			k = sscanf (&txt[1], "%[^/]/%lf", L->file, &L->slop);
			if (k == 1) L->slop = GMT_CONV8_LIMIT;
			if (gmt_access (GMT, L->file, R_OK)) {	/* Cannot read/find file */
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Cannot find/read fixed point file %s\n", L->file);
				error++;
			}
			break;
		case 'X':	/* Crossing complicated curve */
			L->do_interpolate = true;
			/* Intentionally fall through - to 'x'*/
		case 'x':	/* Crossing line */
			L->crossing = GMT_DECORATE_XCURVE;
			strncpy (L->file, &txt[1], PATH_MAX-1);
			if (gmt_access (GMT, L->file, R_OK)) {	/* Cannot read/find file */
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Cannot find/read crossing line file %s\n", L->file);
				error++;
			}
			break;
		case 'D':	/* Specify distances in geographic units (km, degrees, etc) */
			L->dist_kind = 1;
			/* Intentionally fall through - to 'd' */
		case 'd':	/* Specify distances in plot units [cip] */
			L->spacing = true;
			k = sscanf (&txt[j], "%[^/]/%lf", txt_a, &L->symbol_dist_frac);
			if (k == 1) L->symbol_dist_frac = 0.25;
			if (L->dist_kind == 1) {	/* Distance units other than xy specified */
				k = (int)strlen (txt_a) - 1;
				c = (isdigit ((int)txt_a[k]) || txt_a[k] == '.') ? 0 : txt_a[k];
				L->symbol_dist_spacing = atof (&txt_a[1]);
				if (gmt_init_distaz (GMT, c, gmt_M_sph_mode (GMT), GMT_CONT_DIST) == GMT_NOT_A_VALID_TYPE) error++;
			}
			else
				L->symbol_dist_spacing = gmt_M_to_inch (GMT, &txt_a[1]);
			if (L->symbol_dist_spacing <= 0.0) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Spacing between symbols must exceed 0.0\n", L->flag);
				error++;
			}
			if (L->symbol_dist_frac < 0.0 || L->symbol_dist_frac > 1.0) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Initial symbols distance fraction must be in 0-1 range\n", L->flag);
				error++;
			}
			break;
		default:
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Unrecognized modifier %c\n", L->flag, txt[0]);
			error++;
			break;
	}

	return (error);
}

unsigned int gmt_get_dist_units (struct GMT_CTRL *GMT, char *args, char *unit, unsigned int *mode) {
	/* Examine the -E<args> option and determine the distance unit and mode. */
	unsigned int id, pos = 0, pos2 = 0, error = 0, l_mode[3], this_mode = 0;
	size_t len, k, kk, s;
	char *c = NULL, p[GMT_BUFSIZ] = {""}, modifiers[GMT_BUFSIZ] = {""}, p2[GMT_BUFSIZ] = {""}, this_unit = 0, l_unit[3];

	/* step is given in either Cartesian units or, for geographic, in the prevailing unit (m, km) */

	*mode = (gmt_M_is_geographic (GMT, GMT_IN)) ? GMT_GREATCIRCLE : 0;	/* Great circle or Cartesian */
	*unit = 0;	/* Initially not set */
	while (!error && (gmt_strtok (args, ",", &pos, p))) {	/* Split on each line since separated by commas */
		k = s = 0;	len = strlen (p);
		while (s == 0 && k < len) {	/* Find first occurrence of recognized modifier+<char> that may take a unit, if any */
			if ((p[k] == '+') && (p[k+1] && strchr ("ilr", p[k+1]))) s = k;
			k++;
		}
		if (s == 0) continue;	/* No modifier with unit specification; go to next line */
		/* Here we are processing +i, +l, or +r, all of which take a distance with optional unit */
		gmt_M_memset (l_unit, 3, char);		/* Clean register */
		gmt_M_memset (l_mode, 3, unsigned int);	/* Clean register */
		strcpy (modifiers, &p[s]);
		pos2 = 0;
		if (modifiers[2] == '+') {	/* Gave leading + for geodesic calculation (deprecated) */
			if (gmt_M_compat_check (GMT, 6))
				GMT_Report (GMT->parent, GMT_MSG_COMPAT, "Leading + with increment to set ellipsoidal mode is deprecated; use -je instead\n");
			modifiers[2] = '@';	/* Flag for + in increment which means geodesic mode [to avoid being screwed by gmt_strtok on +] */
		}
		while ((gmt_strtok (modifiers, "+", &pos2, p2))) {
			switch (p2[0]) {
				case 'i':	id = 0;	break;	/* Increment along line */
				case 'l':	id = 1;	break;	/* Length of line */
				case 'r':	id = 2;	break;	/* Radius of circular ring */
				default:	id = 9; break;	/* Probably +d or some other non-distance setting to skip */
			}
			if (id == 9) continue;	/* Just go to next */
			/* id points to the correct array index for i, l, r (0-2) */
			if (strchr (GMT_LEN_UNITS, p2[strlen(p2)-1])) l_unit[id] = p2[strlen(p2)-1];
			if (p2[1] == '-') {
				if (gmt_M_compat_check (GMT, 6)) {
					GMT_Report (GMT->parent, GMT_MSG_COMPAT, "Leading - to increment to set Flat Earth mode is deprecated; use -jf instead\n");
					l_mode[id] = GMT_FLATEARTH;
				}
				else {
					GMT_Report (GMT->parent, GMT_MSG_ERROR, "Negative increment is not allowed\n");
					error++;
				}
			}
			else if (p2[1] == '@') {	/* Leading + in strict GMT6 mode is just a positive sign */
				if (gmt_M_compat_check (GMT, 6))
					l_mode[id] = GMT_GEODESIC;
			}
		}
		/* Some sanity checking to make sure only one unit and mode are given for all lines */
		for (k = 0; k < 3; k++) {
			if (l_unit[k] == 0) continue;	/* Not set, skip to next */
			for (kk = k + 1; kk < 3; kk++) {
				if (l_unit[kk] == 0) continue;	/* Not set, skip to next */
				if (l_unit[k] != l_unit[kk]) error++;
			}
			this_unit = l_unit[k];
		}
		if (this_unit) {	/* Got a unit */
			if (*unit && this_unit != *unit)	/* Got a different unit that before */
				error++;
			else
				*unit = this_unit;	/* Set default unit if not specified as part of the modifiers */
		}
		/* Now check modes */
		for (k = 0; k < 3; k++) {
			if (l_mode[k] == 0) continue;	/* Not set, skip to next */
			for (kk = k + 1; kk < 3; kk++) {
				if (l_mode[kk] == 0) continue;	/* Not set, skip to next */
				if (l_mode[k] != l_mode[kk]) error++;
			}
			this_mode = l_mode[k];
		}
		if (this_mode)	/* Got a mode other than Cartesian */
			*mode = this_mode;
	}
	if (*unit == 0) {
		if (gmt_M_is_geographic (GMT, GMT_IN))	/* km for geographic unless +g given */
			*unit = (strstr (args, "+g")) ? 'd' : 'k';
		else
			*unit = 'X';	/* Default is Cartesian if nothing is specified */
	}
	if (strchr (GMT_LEN_UNITS, *unit) && gmt_M_is_cartesian (GMT, GMT_IN)) {	/* Want geographic distance unit but -fg or -J not set */
		gmt_parse_common_options (GMT, "f", 'f', "g");
		if (*mode == 0) *mode = GMT_GREATCIRCLE;	/* Default to great circle distances if no other mode was implied */
	}
	if (error) GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -E:  All lines must have the same distance units\n");
	/* Process args so any i|l|r+<dist> becomes i|l|r <dist> as the + will cause trouble otherwise.  This + for geodesics have already been processed */
	while ((c = strstr (args, "+i+"))) c[2] = ' ';
	while ((c = strstr (args, "+l+"))) c[2] = ' ';
	while ((c = strstr (args, "+r+"))) c[2] = ' ';
	return (error);
}

void gmt_explain_lines (struct GMTAPI_CTRL *API, unsigned mode) {
	/* mode is 0 for gratrack and 1for grdinterpolate */
	static char *item[2] = {"grid", "top layer in the cube"};
	GMT_Usage (API, 1, "\n-E<table|<origin>|<line1>[,<line2>,...][+a<az>][+c][+d][+g][+i<step>][+l<length>][+n<np>][+o<az>][+p][+r<radius>][+x]");
	GMT_Usage (API, -2, "Read profiles from <table> or create them on the fly. Choose on of these choices:");
	GMT_Usage (API, 3, "%s Read one or more profiles from <table>", GMT_LINE_BULLET);
	GMT_Usage (API, 3, "%s Create quick paths based on <line1>[,<line2>,...]. Each <line> is given by <start>/<stop>, where <start> or <stop> "
		"are <lon/lat> or a 2-character key that uses the \"pstext\"-style justification format "
		"to specify a point on the map as [LCR][BMT].  In addition, you can use Z-, Z+ to mean "
		"the global minimum and maximum locations in the %s.", GMT_LINE_BULLET, item[mode]);
	GMT_Usage (API, 3, "%s Set an origin, provide azimuth and length and more via modifiers and create a profile.", GMT_LINE_BULLET);
	GMT_Usage (API, -2, "Several modifiers are available to create the profiles:");
	GMT_Usage (API, 3, "+a Define a profile from <origin> in the <az> direction; requires +l.");
	GMT_Usage (API, 3, "+c Create a continuous segment if two end points are identical [separate segments].");
	GMT_Usage (API, 3, "+d Insert an extra output column with distances following the coordinates.");
	GMT_Usage (API, 3, "+g Use gridline coordinates (degree longitude or latitude) if <line> is so aligned [great circle].");
	GMT_Usage (API, 3, "+i Set the sampling increment <step> [Default is 0.5 x min of (x_inc, y_inc)].");
	GMT_Usage (API, 3, "+l Set the length of the profile.");
	GMT_Usage (API, 3, "+o Like +a but centers profile on <origin>; requires +l.");
	GMT_Usage (API, 3, "+p Sample along the parallel if <line> has constant latitude.");
	GMT_Usage (API, 3, "+n Set <np>, the number of output points and compute <inc> from <length>, so +l is required.");
	GMT_Usage (API, 3, "+r Set <radius> of circle about <origin>; requires +i or +n.");
	GMT_Usage (API, 3, "+x Follow a loxodrome (rhumbline) [great circle].");
	GMT_Usage (API, -2, "Note:  A unit is optional.  Only ONE unit type from %s can be used throughout this option, "
		"so mixing of units is not allowed [Default unit is km, if geographic].", GMT_LEN_UNITS2_DISPLAY);
}

/*! . */
struct GMT_DATASET *gmt_make_profiles (struct GMT_CTRL *GMT, char option, char *args, bool resample, bool project, bool get_distances, double step, enum GMT_enum_track mode, double xyz[2][3], unsigned int *dtype) {
	/* Given a list of comma-separated start/stop coordinates, build a data table
	 * of the profiles. xyz holds the grid min/max coordinates (or NULL if used without a grid;
	 * in that case the special Z+, Z- coordinate shorthands are unavailable).
	 * If resample is true then we sample the track between the end points.
	 * If project is true then we convert to plot units.
	 * If get_distances is true then add a column with distances. We also do this if +d is added to args.
	 */
	unsigned int n_cols, dcol, np = 0, k, s, pos = 0, pos2 = 0, xtype = gmt_M_type (GMT, GMT_IN, GMT_X), ytype = gmt_M_type (GMT, GMT_IN, GMT_Y);
	enum GMT_profmode p_mode;
	bool continuous = false, single, may_adjust = false, gridline_units = false, parallel = false;
	uint64_t dim[GMT_DIM_SIZE] = {1, 1, 0, 0};
	int n, error = 0;
	double L, az = 0.0, length = 0.0, r = 0.0, orig_step = step, last_x = 0, last_y = 0, d_adjust_scl = 1.0;
	size_t len;
	char p[GMT_BUFSIZ] = {""}, txt_a[GMT_LEN256] = {""}, txt_b[GMT_LEN256] = {""}, txt_c[GMT_LEN256] = {""}, txt_d[GMT_LEN256] = {""};
	char modifiers[GMT_BUFSIZ] = {""}, p2[GMT_BUFSIZ] = {""};
	struct GMT_DATASET *D = NULL;
	struct GMT_DATATABLE *T = NULL;
	struct GMT_DATATABLE_HIDDEN *TH = NULL;
	struct GMT_DATASEGMENT *S = NULL;
	struct GMT_DATASEGMENT_HIDDEN *SH = NULL;

	/* step is given in either Cartesian units or, for geographic, in the prevailing unit (m, km) */

	if (strstr (args, "+c")) continuous = true;	/* Want to join abutting profiles */
	if (strstr (args, "+d")) get_distances = true;	/* Want to add distances to the output */
	if (strstr (args, "+g")) gridline_units = true;	/* Want degree longitudes or latitudes along a gridline */
	if (strstr (args, "+p")) parallel = true;	/* Want to sample along a parallel */
	if (strstr (args, "+x")) GMT->current.map.loxodrome = true;	/* Want to sample along a rhumbline */
	single = (strchr (args, ',') == NULL);	/* Only a single line */
	if (get_distances) GMT_Report (GMT->parent, GMT_MSG_DEBUG, "gmt_make_profiles: Return distances along track\n");

	if (gmt_M_is_geographic (GMT, GMT_IN)) {
		if (single &&gridline_units)
			may_adjust = true;
		if (parallel) mode = GMT_TRACK_FILL_P;
	}
	n_cols = (get_distances) ? 3 :2;
	dim[GMT_COL] = n_cols;
	dim[GMT_SEG] = GMT_SMALL_CHUNK;
	*dtype = GMT_IS_FLOAT;	/* Normally, distances are floatint point values */
	if ((D = GMT_Create_Data (GMT->parent, GMT_IS_DATASET, GMT_IS_LINE, 0, dim, NULL, NULL, 0, 0, NULL)) == NULL)
		return (NULL);

	T = D->table[0];	/* The only table */
	TH = gmt_get_DT_hidden (T);
	T->n_segments = 0;    /* Start working on first segment */

	while (gmt_strtok (args, ",", &pos, p)) {	/* Split on each line since separated by commas */
		S = GMT_Alloc_Segment (GMT->parent, GMT_NO_STRINGS, 2, n_cols, NULL, NULL);	/* n_cols with 2 rows each */
		SH = gmt_get_DS_hidden (S);
		k = p_mode = s = 0;	len = strlen (p);
		while (s == 0 && k < len) {	/* Find first occurrence of recognized modifier+<char>, if any */
			if ((p[k] == '+') && (p[k+1] && strchr ("acdgilnoprx", p[k+1]))) s = k;
			k++;
		}
		if (s) {
			strncpy (modifiers, &p[s], GMT_BUFSIZ-1);
			pos2 = 0;
			while ((gmt_strtok (modifiers, "+", &pos2, p2))) {
				switch (p2[0]) {	/* fabs is used for lengths since -<length> might have been given to indicate Flat Earth Distances */
					case 'a':	az = atof (&p2[1]);	p_mode |= GMT_GOT_AZIM;		break;
					case 'c':	case 'd':	case 'g':	case 'p':	case 'x':	break;	/* Already processed up front */
					case 'n':	np = atoi (&p2[1]);	p_mode |= GMT_GOT_NP;		break;
					case 'o':	az = atof (&p2[1]);	p_mode |= GMT_GOT_ORIENT;	break;
					case 'i':	step = fabs (atof (&p2[1]));
							if (step > 2.0*orig_step)
								GMT_Report (GMT->parent, GMT_MSG_WARNING, "Output sampling interval in d exceeds grid interval and may lead to aliasing.\n");
							p_mode |= GMT_GOT_INC;					break;
					case 'l':	length = fabs (atof (&p2[1]));	p_mode |= GMT_GOT_LENGTH;	break;
					case 'r':	r = fabs (atof (&p2[1]));	p_mode |= GMT_GOT_RADIUS;	break;
					default:	error++;	break;
				}
			}
			/* Some sanity checking to make correct combos of modifiers are given */
			if (((p_mode & GMT_GOT_AZIM) || (p_mode & GMT_GOT_ORIENT)) && (p_mode & GMT_GOT_LENGTH) == 0) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Modifiers +a and +o requires +l<length>\n", option);
				error++;
			}
			if ((p_mode & GMT_GOT_RADIUS) && !((p_mode & GMT_GOT_NP) || (p_mode & GMT_GOT_INC))) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Modifies +r requires +i<inc> or +n<np>\n", option);
				error++;
			}
			p[s] = '\0';	/* Chop off for now */
			if (error) {
				gmt_M_free (GMT, T->segment);
				gmt_M_free (GMT, T);
				return (NULL);
			}
		}
		n = sscanf (p, "%[^/]/%[^/]/%[^/]/%s", txt_a, txt_b, txt_c, txt_d);
		if (n == 1) { /* Easy, got <code> for a central point */
			error += gmtsupport_code_to_lonlat (GMT, txt_a, &S->data[GMT_X][0], &S->data[GMT_Y][0]);
		}
		else if (n == 4) {	/* Easy, got lon0/lat0/lon1/lat1 */
			error += gmt_verify_expectations (GMT, xtype, gmt_scanf_arg (GMT, txt_a, xtype, false, &S->data[GMT_X][0]), txt_a);
			error += gmt_verify_expectations (GMT, ytype, gmt_scanf_arg (GMT, txt_b, ytype, false, &S->data[GMT_Y][0]), txt_b);
			error += gmt_verify_expectations (GMT, xtype, gmt_scanf_arg (GMT, txt_c, xtype, false, &S->data[GMT_X][1]), txt_c);
			error += gmt_verify_expectations (GMT, ytype, gmt_scanf_arg (GMT, txt_d, ytype, false, &S->data[GMT_Y][1]), txt_d);
			if (may_adjust && gridline_units) {	/* Want to use arc-units along gridlines and not great circle units */
				if (doubleAlmostEqualZero (S->data[GMT_X][0], S->data[GMT_X][1]))
					d_adjust_scl = 1.0, dcol = GMT_Y, mode = GMT_TRACK_FILL_M;	/* Scaling spherical degrees to latitude degrees on a sphere */
				else if (doubleAlmostEqualZero (S->data[GMT_Y][0], S->data[GMT_Y][1]))
					d_adjust_scl = cosd (S->data[GMT_Y][0]), dcol = GMT_X, mode = GMT_TRACK_FILL_P;	/* Scaling spherical degrees to longitude degrees on a sphere at that latitude */
				else
					may_adjust = false;	/* Not our case */
			}
		}
		else if (n == 2) {	/* More complicated: either <code>/<code> or <clon>/<clat> with +a|o|r */
			if ((p_mode & GMT_GOT_AZIM) || (p_mode & GMT_GOT_ORIENT) || (p_mode & GMT_GOT_RADIUS)) {	/* Got a center point via coordinates */
				error += gmt_verify_expectations (GMT, xtype, gmt_scanf_arg (GMT, txt_a, xtype, false, &S->data[GMT_X][0]), txt_a);
				error += gmt_verify_expectations (GMT, ytype, gmt_scanf_arg (GMT, txt_b, ytype, false, &S->data[GMT_Y][0]), txt_b);
			}
			else { /* Easy, got <code>/<code> */
				error += gmtsupport_code_to_lonlat (GMT, txt_a, &S->data[GMT_X][0], &S->data[GMT_Y][0]);
				error += gmtsupport_code_to_lonlat (GMT, txt_b, &S->data[GMT_X][1], &S->data[GMT_Y][1]);
			}
		}
		else if (n == 3) {	/* More complicated: <code>/<lon>/<lat> or <lon>/<lat>/<code> */
			if (gmtsupport_code_to_lonlat (GMT, txt_a, &S->data[GMT_X][0], &S->data[GMT_Y][0])) {	/* Failed, so try the other way */
				error += gmt_verify_expectations (GMT, xtype, gmt_scanf_arg (GMT, txt_a, xtype, false, &S->data[GMT_X][0]), txt_a);
				error += gmt_verify_expectations (GMT, ytype, gmt_scanf_arg (GMT, txt_b, ytype, false, &S->data[GMT_Y][0]), txt_b);
				error += gmtsupport_code_to_lonlat (GMT, txt_c, &S->data[GMT_X][1], &S->data[GMT_Y][1]);
			}
			else {	/* Worked, pick up second point */
				error += gmt_verify_expectations (GMT, xtype, gmt_scanf_arg (GMT, txt_b, xtype, false, &S->data[GMT_X][1]), txt_b);
				error += gmt_verify_expectations (GMT, ytype, gmt_scanf_arg (GMT, txt_c, ytype, false, &S->data[GMT_Y][1]), txt_c);
			}
		}
		S->n_rows = 2;
		for (n = 0; n < 2; n++) {	/* Reset any zmin/max settings if used and applicable */
			if (S->data[GMT_X][n] == DBL_MAX) {	/* Meant zmax location */
				if (xyz) {
					S->data[GMT_X][n] = xyz[1][GMT_X];
					S->data[GMT_Y][n] = xyz[1][GMT_Y];
				}
				else {
					error++;
					GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  z+ option not applicable here\n", option);
				}
			}
			else if (S->data[GMT_X][n] == -DBL_MAX) {	/* Meant zmin location */
				if (xyz) {
					S->data[GMT_X][n] = xyz[0][GMT_X];
					S->data[GMT_Y][n] = xyz[0][GMT_Y];
				}
				else {
					error++;
					GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  z- option not applicable here\n", option);
				}
			}
		}
		if (error) {
			gmt_M_free (GMT, T->segment);
			gmt_M_free (GMT, T);
			gmt_free_segment (GMT, &S);
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Valid coordinate codes are [lcr][bmt] and z[+-]\n", option);
			return (NULL);
		}
		if (p_mode & GMT_GOT_AZIM) {		/* Got center and azimuth of line; determine a suitable end point */
			L = gmtsupport_determine_endpoint (GMT, S->data[GMT_X][0], S->data[GMT_Y][0], length, az, &S->data[GMT_X][1], &S->data[GMT_Y][1]);
			if (p_mode & GMT_GOT_NP) step = L / (np - 1);
		}
		else if (p_mode & GMT_GOT_ORIENT) {	/* Got center and orientation of line; determine suitable end points */
			L = gmtsupport_determine_endpoints (GMT, S->data[GMT_X], S->data[GMT_Y], length, az);
			if (p_mode & GMT_GOT_NP) step = L / (np - 1);
		}
		else if (p_mode & GMT_GOT_RADIUS) {	/* Got center and a radius; determine circular path */
			double x0, y0;
			/* Determine np from the +i<inc> if +n was not set */
			x0 = S->data[GMT_X][0];	y0 = S->data[GMT_Y][0];
			if (p_mode & GMT_GOT_INC) {
				double colat = (r / GMT->current.map.dist[GMT_MAP_DIST].scale);	/* Convert from chosen radius unit to meter or degree */
				if (!GMT->current.map.dist[GMT_MAP_DIST].arc) colat /= GMT->current.proj.DIST_M_PR_DEG;	/* Convert meter to spherical degrees */
				/* colat is the radius in spherical degrees (if geographic) */
				step = (step / GMT->current.map.dist[GMT_MAP_DIST].scale);	/* Convert from chosen unit to meter or degree */
				if (!GMT->current.map.dist[GMT_MAP_DIST].arc) step /= GMT->current.proj.DIST_M_PR_DEG;	/* Convert meter to spherical degrees */
				/* If geographic then the length of the circle is 360 degeres of longitude scaled by the sine of the colatitude */
				L = (gmt_M_is_geographic (GMT, GMT_IN)) ? sind (colat) * 360.0 : 2.0 * M_PI * r;
				np = urint (L / step);
			}
			S->data[GMT_X] = gmt_M_memory (GMT, S->data[GMT_X], np, double);
			S->data[GMT_Y] = gmt_M_memory (GMT, S->data[GMT_Y], np, double);
			S->n_rows = gmtsupport_determine_circle (GMT, x0, y0, r, S->data[GMT_X], S->data[GMT_Y], np);
			resample = false;	/* Since we already got our profile */
		}
		if (resample) S->n_rows = SH->n_alloc = gmt_resample_path (GMT, &S->data[GMT_X], &S->data[GMT_Y], S->n_rows, d_adjust_scl * step, mode);
		if (get_distances) {	/* Compute cumulative distances along line */
			gmt_M_free (GMT, S->data[GMT_Z]);	/* Free so we can alloc a new array */
			S->data[GMT_Z] = gmt_dist_array (GMT, S->data[GMT_X], S->data[GMT_Y], S->n_rows, true);
			if (p_mode & GMT_GOT_ORIENT) {	/* Adjust distances to have 0 at specified origin */
				L = 0.5 * S->data[GMT_Z][S->n_rows-1];	/* Half-way distance to remove */
				for (k = 0; k < S->n_rows; k++) S->data[GMT_Z][k] -= L;
			}
			if (may_adjust) {	/* Adjust distances to equal longitudes or latitudes */
				gmt_M_memcpy (S->data[GMT_Z], S->data[dcol], S->n_rows, double);
				*dtype = (dcol == GMT_X) ? GMT_IS_LON : GMT_IS_LAT;
			}
		}
		if (project) {	/* Project coordinates */
			uint64_t k;
			double x, y;
			for (k = 0; k < S->n_rows; k++) {
				gmt_geo_to_xy (GMT, S->data[GMT_X][k], S->data[GMT_Y][k], &x, &y);
				S->data[GMT_X][k] = x;
				S->data[GMT_Y][k] = y;
			}
		}
		if (continuous && T->n_segments && doubleAlmostEqual (S->data[GMT_Y][0], last_y) && gmtsupport_same_longitude (S->data[GMT_X][0], last_x)) {
			/* Need to append to previous segment after allocating more space */
			struct GMT_DATASEGMENT *prev_S = T->segment[T->n_segments-1];
			uint64_t start = prev_S->n_rows, add = S->n_rows - 1, rec;
			if (gmt_alloc_segment (GMT, prev_S, prev_S->n_rows + S->n_rows - 1, prev_S->n_columns, GMT_NO_STRINGS, false)) {
				GMT_Report (GMT->parent, GMT_MSG_WARNING, "gmt_make_profiles: Cannot reallocate the existing segment");
				T->segment[T->n_segments++] = S;	/* Hook into table */
			}
			else {	/* Copy over but avoid repeating the joint */
				gmt_M_memcpy (&(prev_S->data[GMT_X][start]), &(S->data[GMT_X][1]), add, double);
				gmt_M_memcpy (&(prev_S->data[GMT_Y][start]), &(S->data[GMT_Y][1]), add, double);
				if(get_distances){
					gmt_M_memcpy (&(prev_S->data[GMT_Z][start]), &(S->data[GMT_Z][1]), add, double);
					for (rec = start; rec < prev_S->n_rows; rec++) prev_S->data[GMT_Z][rec] += prev_S->data[GMT_Z][start-1];
				}
				gmt_free_segment (GMT, &S);	/* Done with this guy */
				S = prev_S;
			}
		}
		else {	/* Not continuous, or first segment */
			gmt_free_segment (GMT, &T->segment[T->n_segments]);	/* Done with this guy */
			if (continuous) gmt_eliminate_lon_jumps (GMT, S->data[GMT_X], S->n_rows);	/* Avoid jumps in longitude due to joining */
			T->segment[T->n_segments++] = S;	/* Hook into table */
		}

		last_x = S->data[GMT_X][S->n_rows-1];
		last_y = S->data[GMT_Y][S->n_rows-1];

		if (T->n_segments == TH->n_alloc) {	/* Allocate more space */
			size_t old_n_alloc = TH->n_alloc;
			TH->n_alloc <<= 1;
			T->segment = gmt_M_memory (GMT, T->segment, TH->n_alloc, struct GMT_DATASEGMENT *);
			gmt_M_memset (&(T->segment[old_n_alloc]), TH->n_alloc - old_n_alloc, struct GMT_DATASEGMENT *);	/* Set to NULL */
		}
	}
	gmtlib_finalize_dataset (GMT, D);	/* Reallocate to fit */
	gmt_set_dataset_minmax (GMT, D);	/* Determine min/max for each column */
	return (D);
}

/*! . */
int gmt_decorate_prep (struct GMT_CTRL *GMT, struct GMT_DECORATE *G, double xyz[2][3]) {
	/* G is pointer to the LABELED CONTOUR structure
	 * xyz, if not NULL, have the (x,y,z) min and max values for a grid
	 */

	/* Prepares decorated line symbols machinery as needed */

	unsigned int error = 0, dummy;
	uint64_t k, i, seg, row, rec;
	double x, y;

	if (G->spacing && G->dist_kind == 1) {
		GMT->current.map.dist[GMT_LABEL_DIST].func = GMT->current.map.dist[GMT_CONT_DIST].func;
		GMT->current.map.dist[GMT_LABEL_DIST].scale = GMT->current.map.dist[GMT_CONT_DIST].scale;
	}
	if (G->dist_kind == 1 && gmt_M_is_cartesian (GMT, GMT_IN)) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Map distance options requires a map projection.\n", G->flag);
		error++;
	}

	if (G->crossing == GMT_DECORATE_XLINE) {
		G->X = gmt_make_profiles (GMT, G->flag, G->option, G->do_interpolate, true, false, 0.0, GMT_TRACK_FILL, xyz, &dummy);
	}
	else if (G->crossing == GMT_DECORATE_XCURVE) {
		unsigned int first = 0;
		if (gmt_file_is_cache (GMT->parent, G->file)) {	/* Must be a cache file */
			first = gmt_download_file_if_not_found (GMT, G->file, 0);
		}
		gmt_disable_bghio_opts (GMT);	/* Do not want any -b -g -h -i -o to affect the reading this file */
		if ((G->X = GMT_Read_Data (GMT->parent, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_LINE, GMT_READ_NORMAL, NULL, &G->file[first], NULL)) == NULL) {	/* Failure to read the file */
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Crossing file %s does not exist or had no data records\n", G->flag, G->file);
			error++;
		}
		else if (G->X->n_columns < 2 || G->X->n_records < 2) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Crossing file %s does not have enough columns or records\n", G->flag, G->file);
			GMT_Destroy_Data (GMT, &(G->X));
			error++;
		}
		else {	/* Should be OK to use; note there is only one table here */
			struct GMT_DATASEGMENT *S = NULL;
			for (k = 0; k < G->X->table[0]->n_segments; k++) {
				S = G->X->table[0]->segment[k];
				for (i = 0; i < S->n_rows; i++) {	/* Project */
					gmt_geo_to_xy (GMT, S->data[GMT_X][i], S->data[GMT_Y][i], &x, &y);
					S->data[GMT_X][i] = x;
					S->data[GMT_Y][i] = y;
				}
			}
		}
		gmt_reenable_bghio_opts (GMT);	/* Recover settings provided by user (if -b -g -h -i were used at all) */
	}
	else if (G->fixed) {
		unsigned int first = 0;
		struct GMT_DATASET *T = NULL;
		struct GMT_DATASEGMENT *S = NULL;
		double xy[2];
		/* File is expected to have x,y coordinates and we will ignore anything beyond that */
		if ((error = GMT_Set_Columns (GMT->parent, GMT_IN, 2, GMT_COL_FIX_NO_TEXT))) {
			return (error);
		}
		if (gmt_file_is_cache (GMT->parent, G->file)) {	/* Must be a cache file */
			first = gmt_download_file_if_not_found (GMT, G->file, 0);
		}
		gmt_disable_bghio_opts (GMT);	/* Do not want any -b -g -h -i -o to affect the reading from -F files */
		if ((T = GMT_Read_Data (GMT->parent, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_POINT, GMT_READ_NORMAL, NULL, &G->file[first], NULL)) == NULL) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Could not open file %s\n", G->flag, G->file);
			error++;
			return (error);
		}
		gmt_reenable_bghio_opts (GMT);	/* Recover settings provided by user (if -b -g -h -i were used at all) */
		if (T->n_columns < 2) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Data file %s has only %" PRIu64 " data columns!\n", G->file, T->n_columns);
			return (error);
		}
		G->f_xy[GMT_X] = gmt_M_memory (GMT, NULL, T->n_records, double);
		G->f_xy[GMT_Y] = gmt_M_memory (GMT, NULL, T->n_records, double);
		for (seg = rec = k = 0; seg < T->table[0]->n_segments; seg++) {
			S = T->table[0]->segment[seg];	/* Current segment */
			for (row = 0; row < S->n_rows; row++, rec++) {
				xy[GMT_X] = S->data[GMT_X][row];
				xy[GMT_Y] = S->data[GMT_Y][row];
				gmt_map_outside (GMT, xy[GMT_X], xy[GMT_Y]);
				if (abs (GMT->current.map.this_x_status) > 1 || abs (GMT->current.map.this_y_status) > 1) continue;	/* Outside map region */
				gmt_geo_to_xy (GMT, xy[GMT_X], xy[GMT_Y], &G->f_xy[GMT_X][k], &G->f_xy[GMT_Y][k]);	/* Project -> xy inches */
				k++;
			}
		}
		G->f_n = (unsigned int)k;
		if ((G->f_n = (unsigned int)k) == 0) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Fixed position file %s does not have any data records\n",
				G->flag, G->file);
			error++;
			gmt_M_free (GMT, G->f_xy[GMT_X]);
			gmt_M_free (GMT, G->f_xy[GMT_Y]);
		}
		if (GMT_Destroy_Data (GMT->parent, &T) != GMT_NOERROR)
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "Option -%c:  Failed to free DATASET allocated to parse %s\n",
				G->flag, G->file);
	}

	return (error);
}

/*! . */
int gmt_contlabel_prep (struct GMT_CTRL *GMT, struct GMT_CONTOUR *G, double xyz[2][3]) {
	/* G is pointer to the LABELED CONTOUR structure
	 * xyz, if not NULL, have the (x,y,z) min and max values for a grid
	 */

	/* Prepares contour labeling machinery as needed */

	unsigned int error = 0, dummy;
	uint64_t k, i, seg, row, rec;
	double x, y;

	gmt_contlabel_free (GMT, G);	/* In case we've been here before */

	if (G->clearance_flag) {	/* Gave a percentage of fontsize as clearance */
		G->clearance[GMT_X] = 0.01 * G->clearance[GMT_X] * G->font_label.size * GMT->session.u2u[GMT_PT][GMT_INCH];
		G->clearance[GMT_Y] = 0.01 * G->clearance[GMT_Y] * G->font_label.size * GMT->session.u2u[GMT_PT][GMT_INCH];
	}
	if (G->label_type == GMT_LABEL_IS_FFILE && !G->fixed) {	/* Requires fixed file */
		error++;
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Labeling option +Lf requires the fixed label location setting\n", G->flag);
	}
	if (G->label_type == GMT_LABEL_IS_XFILE && G->crossing != GMT_CONTOUR_XCURVE) {	/* Requires cross file */
		error++;
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Labeling option +Lx requires the crossing lines setting\n", G->flag);
	}
	if (G->spacing && G->dist_kind == 1 && G->label_type == GMT_LABEL_IS_MDIST && G->dist_unit == 0) {	/* Did not specify unit - use same as in -G */
		GMT->current.map.dist[GMT_LABEL_DIST].func = GMT->current.map.dist[GMT_CONT_DIST].func;
		GMT->current.map.dist[GMT_LABEL_DIST].scale = GMT->current.map.dist[GMT_CONT_DIST].scale;
	}
	if ((G->dist_kind == 1 || G->label_type == GMT_LABEL_IS_MDIST) && gmt_M_is_cartesian (GMT, GMT_IN)) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Map distance options requires a map projection.\n", G->flag);
		error++;
	}
	if (G->angle_type == GMT_ANGLE_LINE_PARALLEL)
		G->no_gap = (G->just < 5 || G->just > 7);	/* Don't clip contour if label is not in the way */
	else if (G->angle_type == GMT_ANGLE_LINE_NORMAL)
		G->no_gap = ((G->just + 2)%4 != 0);	/* Don't clip contour if label is not in the way */

	if (G->crossing == GMT_CONTOUR_XLINE) {
		G->X = gmt_make_profiles (GMT, G->flag, G->option, G->do_interpolate, true, false, 0.0, GMT_TRACK_FILL, xyz, &dummy);
	}
	else if (G->crossing == GMT_CONTOUR_XCURVE) {
		unsigned int first = 0;
		if (gmt_file_is_cache (GMT->parent, G->file)) {	/* Must be a cache file */
			first = gmt_download_file_if_not_found (GMT, G->file, 0);
		}
		if ((G->X = GMT_Read_Data (GMT->parent, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_LINE, GMT_READ_NORMAL, NULL, &G->file[first], NULL)) == NULL) {	/* Failure to read the file */
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Crossing file %s does not exist or had no data records\n", G->flag, G->file);
			error++;
		}
		else if (G->X->n_columns < 2 || G->X->n_records < 2) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Crossing file %s does not have enough columns or records\n", G->flag, G->file);
			GMT_Destroy_Data (GMT, &(G->X));
			error++;
		}
		else {	/* Should be OK to use; note there is only one table here */
			struct GMT_DATASEGMENT *S = NULL;
			for (k = 0; k < G->X->table[0]->n_segments; k++) {
				S = G->X->table[0]->segment[k];
				for (i = 0; i < S->n_rows; i++) {	/* Project */
					gmt_geo_to_xy (GMT, S->data[GMT_X][i], S->data[GMT_Y][i], &x, &y);
					S->data[GMT_X][i] = x;
					S->data[GMT_Y][i] = y;
				}
			}
		}
	}
	else if (G->fixed) {
		unsigned int first = 0;
		struct GMT_DATASET *T = NULL;
		struct GMT_DATASEGMENT *S = NULL;
		double xy[2];
		/* Reading this way since file has coordinates and possibly a text label.
		 * If G->label_type == GMT_LABEL_IS_FFILE then we also have text labels.
		 * Since those could be numbers we force reading 2 columns and get anything
		 * beyond that as text. */
		if ((error = GMT_Set_Columns (GMT->parent, GMT_IN, 2, GMT_COL_FIX))) {
			return (error);
		}
		if (gmt_file_is_cache (GMT->parent, G->file)) {	/* Must be a cache file */
			first = gmt_download_file_if_not_found (GMT, G->file, 0);
		}
		if ((T = GMT_Read_Data (GMT->parent, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_POINT, GMT_READ_NORMAL, NULL, &G->file[first], NULL)) == NULL) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Could not open file %s\n", G->flag, G->file);
			error++;
			return (error);
		}
		if (T->n_columns < 2) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Data file %s has only %" PRIu64 " data columns!\n", G->file, T->n_columns);
			return (error);
		}
		/* Repackage this information into the G structure via f_xy and f_label arrays */
		G->f_xy[GMT_X] = gmt_M_memory (GMT, NULL, T->n_records, double);
		G->f_xy[GMT_Y] = gmt_M_memory (GMT, NULL, T->n_records, double);
		if (T->type == GMT_READ_MIXED) G->f_label = gmt_M_memory (GMT, NULL, T->n_records, char *);
		for (seg = rec = k = 0; seg < T->table[0]->n_segments; seg++) {
			S = T->table[0]->segment[seg];	/* Current segment */
			for (row = 0; row < S->n_rows; row++, rec++) {
				xy[GMT_X] = S->data[GMT_X][row];	xy[GMT_Y] = S->data[GMT_Y][row];
				gmt_map_outside (GMT, xy[GMT_X], xy[GMT_Y]);
				if (abs (GMT->current.map.this_x_status) > 1 || abs (GMT->current.map.this_y_status) > 1) continue;	/* Outside map region */
				gmt_geo_to_xy (GMT, xy[GMT_X], xy[GMT_Y], &G->f_xy[GMT_X][k], &G->f_xy[GMT_Y][k]);	/* Project -> xy inches */
				if (S->text)	/* The label part if asked for */
					G->f_label[k] = strdup (S->text[row]);
				k++;
			}
		}
		if ((G->f_n = (unsigned int)k) == 0) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Fixed position file %s does not have any data records\n", G->flag, G->file);
			error++;
			gmt_M_free (GMT, G->f_xy[GMT_X]);
			gmt_M_free (GMT, G->f_xy[GMT_Y]);
			if (G->f_label) gmt_M_free (GMT, G->f_label);
		}
		if (GMT_Destroy_Data (GMT->parent, &T) != GMT_NOERROR)
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "Option -%c:  Failed to free DATASET allocated to parse %s\n",
			            G->flag, G->file);
	}

	return (error);
}

/*! . */
void gmt_contlabel_free (struct GMT_CTRL *GMT, struct GMT_CONTOUR *G) {
	uint64_t seg, j;
	struct GMT_CONTOUR_LINE *L = NULL;

	/* Free memory */

	for (seg = 0; seg < G->n_segments; seg++) {
		L = G->segment[seg];	/* Pointer to current segment */
		for (j = 0; j < L->n_labels; j++) gmt_M_free (GMT, L->L[j].label);
		gmt_M_free (GMT, L->L);
		gmt_M_free (GMT, L->x);
		gmt_M_free (GMT, L->y);
		gmt_M_free (GMT, L->name);
		gmt_M_free (GMT, L);
	}
	gmt_M_free (GMT, G->segment);
	GMT_Destroy_Data (GMT->parent, &(G->X));
	if (G->f_n) {	/* Array for fixed points */
		gmt_M_free (GMT, G->f_xy[GMT_X]);
		gmt_M_free (GMT, G->f_xy[GMT_Y]);
		if (G->f_label) {
			for (j = 0; j < G->f_n; j++) gmt_M_str_free (G->f_label[j]);
			gmt_M_free (GMT, G->f_label);
		}
	}
}

/*! . */
void gmt_symbol_free (struct GMT_CTRL *GMT, struct GMT_SYMBOL *S) {
	/* Free memory used by the symbol structure in psxy[z] */
	if (S->symbol == GMT_SYMBOL_QUOTED_LINE)
		gmt_contlabel_free (GMT, &(S->G));
	if (S->symbol == GMT_SYMBOL_DECORATED_LINE)
		gmtsupport_decorate_free (GMT, &(S->D));
}

unsigned int *gmt_contour_edge_init (struct GMT_CTRL *GMT, struct GMT_GRID_HEADER *header, unsigned int *n_edges) {
	/* Create and return the edge bit flag array used to keep track of contours and return now many edges */
	unsigned int *edge = NULL;
	*n_edges = header->n_rows * (urint (ceil (header->n_columns / 16.0)));
	edge = gmt_M_memory (GMT, NULL, *n_edges, unsigned int);
	if (edge == NULL) *n_edges = 0;	/* Disaster, but at least return consistent values */
	return (edge);
}

/*! . */
int64_t gmt_contours (struct GMT_CTRL *GMT, struct GMT_GRID *G, unsigned int smooth_factor, unsigned int int_scheme, int orient, unsigned int *edge, bool *first, double **x, double **y) {
	/* The routine finds the zero-contour in the grd dataset.  it assumes that
	 * no node has a value exactly == 0.0.  If more than max points are found
	 * gmtsupport_trace_contour will try to allocate more memory in blocks of GMT_CHUNK points.
	 * orient arranges the contour so that the values to the left of the contour is higher (orient = 1)
	 * or lower (orient = -1) than the contour value.
	 * Note: grd has a pad while edge does not!
	 */

	static unsigned int  side;
	static openmp_int col_0, row_0;
	unsigned int nans = 0;
	openmp_int row, col;
	int scol;
	uint64_t n2, n_edges, offset;
	int64_t n = 0;
	double *x2 = NULL, *y2 = NULL;
	static unsigned int bit[32];

	n_edges = G->header->n_rows * (uint64_t) ceil (G->header->n_columns / 16.0);
	offset = n_edges / 2;

	/* Reset edge-flags to zero, if necessary */
	if (*first) {	/* Set col_0,row_0 for southern boundary */
		unsigned int i;
		gmt_M_memset (edge, n_edges, unsigned int);
		col_0 = side = 0;
		row_0 = (openmp_int)G->header->n_rows - 1;
		for (i = 1, bit[0] = 1; i < 32; i++) bit[i] = bit[i-1] << 1;
		*first = false;
	}

	if (side == 0) {	/* Southern boundary */
		for (col = col_0, row = row_0; col < (openmp_int)G->header->n_columns-1; col++) {
			if ((n = gmtsupport_trace_contour (GMT, G, true, edge, x, y, col, row, 0, offset, bit, &nans))) {
				if (orient) gmtsupport_orient_contour (G, *x, *y, n, orient);
				if ((n = gmtsupport_smooth_contour (GMT, x, y, n, smooth_factor, int_scheme)) < 0) return n;
				col_0 = col + 1;	row_0 = row;
				return (n);
			}
		}
		if (n == 0) {	/* No more crossing of southern boundary, go to next side (east) */
			col_0 = (openmp_int)G->header->n_columns - 2;
			row_0 = (openmp_int)G->header->n_rows - 1;
			side++;
		}
	}

	if (side == 1) {	/* Eastern boundary */
		for (col = col_0, row = row_0; row > 0; row--) {
			if ((n = gmtsupport_trace_contour (GMT, G, true, edge, x, y, col, row, 1, offset, bit, &nans))) {
				if (orient) gmtsupport_orient_contour (G, *x, *y, n, orient);
				if ((n = gmtsupport_smooth_contour (GMT, x, y, n, smooth_factor, int_scheme)) < 0) return n;
				col_0 = col;	row_0 = row - 1;
				return (n);
			}
		}
		if (n == 0) {	/* No more crossing of eastern boundary, go to next side (north) */
			col_0 = (openmp_int)G->header->n_columns - 2;
			row_0 = 1;
			side++;
		}
	}

	if (side == 2) {	/* Northern boundary */
		for (col = scol = col_0, row = row_0; scol >= 0; col--, scol--) {
			if ((n = gmtsupport_trace_contour (GMT, G, true, edge, x, y, col, row, 2, offset, bit, &nans))) {
				if (orient) gmtsupport_orient_contour (G, *x, *y, n, orient);
				if ((n = gmtsupport_smooth_contour (GMT, x, y, n, smooth_factor, int_scheme)) < 0) return n;
				col_0 = col - 1;	row_0 = row;
				return (n);
			}
		}
		if (n == 0) {	/* No more crossing of northern boundary, go to next side (west) */
			col_0 = 0;
			row_0 = 1;
			side++;
		}
	}

	if (side == 3) {	/* Western boundary */
		for (col = col_0, row = row_0; row < (openmp_int)G->header->n_rows; row++) {
			if ((n = gmtsupport_trace_contour (GMT, G, true, edge, x, y, col, row, 3, offset, bit, &nans))) {
				if (orient) gmtsupport_orient_contour (G, *x, *y, n, orient);
				if ((n = gmtsupport_smooth_contour (GMT, x, y, n, smooth_factor, int_scheme)) < 0) return n;
				col_0 = col;	row_0 = row + 1;
				return (n);
			}
		}
		if (n == 0) {	/* No more crossing of western boundary, go to next side (vertical internals) */
			col_0 = 1;
			row_0 = 1;
			side++;
		}
	}

	if (side == 4) {	/* Then loop over interior boxes (vertical edges) */
		for (row = row_0; row < (openmp_int)G->header->n_rows; row++) {
			for (col = col_0; col < (openmp_int)G->header->n_columns-1; col++) {
				if (row == 60 && col == 1)
					n = 0;
				if ((n = gmtsupport_trace_contour (GMT, G, true, edge, x, y, col, row, 3, offset, bit, &nans))) {
					if (nans && (n2 = gmtsupport_trace_contour (GMT, G, false, edge, &x2, &y2, col-1, row, 1, offset, bit, &nans))) {
						/* Must trace in other direction, then splice */
						n = gmtsupport_splice_contour (GMT, x, y, n, x2, y2, n2);
						gmt_M_free (GMT, x2);
						gmt_M_free (GMT, y2);
					}
					if (orient) gmtsupport_orient_contour (G, *x, *y, n, orient);
					if ((n = gmtsupport_smooth_contour (GMT, x, y, n, smooth_factor, int_scheme)) < 0) return n;
					col_0 = col + 1;	row_0 = row;
					return (n);
				}
			}
			col_0 = 1;
		}
		if (n == 0) {	/* No more crossing of vertical internal edges, go to next side (horizontal internals) */
			col_0 = 0;
			row_0 = 1;
			side++;
		}
	}

	if (side == 5) {	/* Then loop over interior boxes (horizontal edges) */
		for (row = row_0; row < (openmp_int)G->header->n_rows; row++) {
			for (col = col_0; col < (openmp_int)G->header->n_columns-1; col++) {
				if ((n = gmtsupport_trace_contour (GMT, G, true, edge, x, y, col, row, 2, offset, bit, &nans))) {
					if (nans && (n2 = gmtsupport_trace_contour (GMT, G, false, edge, &x2, &y2, col-1, row, 0, offset, bit, &nans))) {
						/* Must trace in other direction, then splice */
						n = gmtsupport_splice_contour (GMT, x, y, n, x2, y2, n2);
						gmt_M_free (GMT, x2);
						gmt_M_free (GMT, y2);
					}
					if (orient) gmtsupport_orient_contour (G, *x, *y, n, orient);
					if ((n = gmtsupport_smooth_contour (GMT, x, y, n, smooth_factor, int_scheme)) < 0) return n;
					col_0 = col + 1;	row_0 = row;
					return (n);
				}
			}
			col_0 = 1;
		}
	}

	/* Nothing found */
	return (0);
}

/*! . */
struct GMT_DATASEGMENT * gmt_prepare_contour (struct GMT_CTRL *GMT, double *x, double *y, uint64_t n, double z) {
	/* Returns a segment with this contour */
	unsigned int n_cols;
	char header[GMT_BUFSIZ];
	struct GMT_DATASEGMENT *S = NULL;

	if (n < 2) return (NULL);

	n_cols = (gmt_M_is_dnan (z)) ? 2 : 3;	/* psmask only dumps xy */
	S = GMT_Alloc_Segment (GMT->parent, GMT_NO_STRINGS, n, n_cols, NULL, NULL);
	if (n_cols == 3)
		snprintf (header, GMT_BUFSIZ, "%g contour -Z%g", z, z);
	else
		sprintf (header, "clip contour");
	S->header = strdup (header);

	gmt_M_memcpy (S->data[GMT_X], x, n, double);
	gmt_M_memcpy (S->data[GMT_Y], y, n, double);
	if (n_cols == 3) gmt_M_setnval (S->data[GMT_Z], n, z);
	S->n_rows = n;

	return (S);
}

/*! . */
char * gmt_make_filename (struct GMT_CTRL *GMT, char *template, unsigned int fmt[], double z, bool closed, unsigned int count[]) {
	/* Produce a filename given the template and the running values.
	 * Here, c, d, f stands for the O/C character, the running count,
	 * and the contour level z.  When a running count is used it is
	 * incremented.  If c is not used the only count[0] is used, else
	 * we used count[0] for open and count[1] for closed contours. */

	unsigned int i, n_fmt;
	static char kind[2] = {'O', 'C'};
	char file[PATH_MAX];
	gmt_M_unused(GMT);

	for (i = n_fmt = 0; i < 3; i++) if (fmt[i]) n_fmt++;
	if (n_fmt == 0) return (NULL);	/* Will write single file [or to stdout] */

	if (n_fmt == 1) {	/* Just need a single item */
		if (fmt[0])	/* Just two kinds of files, closed and open */
			snprintf (file, PATH_MAX, template, kind[closed]);
		else if (fmt[1])	/* Just files with a single unique running number */
			snprintf (file, PATH_MAX, template, count[0]++);
		else	/* Contour level file */
			snprintf (file, PATH_MAX, template, z);
	}
	else if (n_fmt == 2) {	/* Need two items, and f+c is not allowed */
		if (fmt[0]) {	/* open/close is involved */
			if (fmt[1] < fmt[0])	/* Files with a single unique running number and open/close */
				snprintf (file, PATH_MAX, template, count[closed]++, kind[closed]);
			else	/* Same in reverse order */
				snprintf (file, PATH_MAX, template, kind[closed], count[closed]++);
		}
		else if (fmt[1] < fmt[2])	/* Files with a single unique running number and contour value */
			snprintf (file, PATH_MAX, template, count[0]++, z);
		else 	/* Same in reverse order */
			snprintf (file, PATH_MAX, template, z, count[0]++);
	}
	else {	/* Combinations of three items */
		if (fmt[0] < fmt[1] && fmt[1] < fmt[2])	/* Files with c, d, and f in that order */
			snprintf (file, PATH_MAX, template, kind[closed], count[closed]++, z);
		else if (fmt[0] < fmt[2] && fmt[2] < fmt[1])	/* Files with c, f, and d in that order */
			snprintf (file, PATH_MAX, template, kind[closed], z, count[closed]++);
		else if (fmt[1] < fmt[2] && fmt[2] < fmt[0])	/* Files with d, f, c in that order */
			snprintf (file, PATH_MAX, template, count[closed]++, z, kind[closed]);
		else if (fmt[1] < fmt[0] && fmt[0] < fmt[2])	/* Files with d, c, f in that order */
			snprintf (file, PATH_MAX, template, count[closed]++, kind[closed], z);
		else if (fmt[2] < fmt[0] && fmt[0] < fmt[1])	/* Files with f, c, d in that order */
			snprintf (file, PATH_MAX, template, z, kind[closed], count[closed]++);
		else						/* Files with f, d, c in that order */
			snprintf (file, PATH_MAX, template, z, count[closed]++, kind[closed]);
	}
	return (strdup (file));
}


/* Function to split a floating point into nearest fraction, with maxden the largest allowable denominator.
 * Borrowed from https://www.ics.uci.edu/~eppstein/numth/frap.c */

GMT_LOCAL void gmtsupport_make_fraction (struct GMT_CTRL *GMT, double x0, int maxden, int *n, int *d) {
	uint64_t m[2][2], ai;
	double x = x0, e;
	/* initialize matrix */
	m[0][0] = m[1][1] = 1, m[0][1] = m[1][0] = 0;

	/* loop finding terms until denom gets too big */
	while (m[1][0] *  ( ai = (uint64_t)x ) + m[1][1] <= (uint64_t)maxden) {
		uint64_t t = m[0][0] * ai + m[0][1];
		m[0][1] = m[0][0];
		m[0][0] = t;
		t = m[1][0] * ai + m[1][1];
		m[1][1] = m[1][0];
		m[1][0] = t;
		if (x == (double)ai) break;     // AF: division by zero
		x = 1 / (x - (double) ai);
		if (x > (double)0x7FFFFFFF) break;  // AF: representation failure
	}

	*n = m[0][0];	*d = m[1][0];
	e = x0 - ((double) *n / (double) *d);
	if (e > GMT_CONV4_LIMIT)
		GMT_Report (GMT->parent, GMT_MSG_WARNING, "Bad fraction, error = %g\n", e);
}

/*! . */
void gmt_sprintf_float (struct GMT_CTRL *GMT, char *string, char *format, double x) {
	/* Determines if %-apostrophe is used in the format for a float. If so, must temporarily switch to LC_NUMERIC=en_US */
	char *use_locale = strstr (format, "%'");
#ifdef HAVE_SETLOCALE
	if (use_locale) setlocale (LC_NUMERIC, "en_US");
#endif
	if (GMT->current.plot.substitute_pi) {	/* Want to use pi when close to known multiples of pi. This variable is set per axis in gmt_xy_axis */
		/* Any fraction of pi up to 1/20th allowed.
		 * substitute_pi becomes true when items with "pi" are used in -R, -I etc. */
		int k = 1, m, n;
		char fmt[GMT_LEN16] = {""};
		double f = fabs (x / M_PI);		/* Float multiples of pi */
		if (fabs (f) < GMT_CONV4_LIMIT) {	/* Deal with special case of zero pi */
			sprintf (string, "0");
			return;
		}
		gmtsupport_make_fraction (GMT, f, 20, &n, &m);	/* Max 20th of pi */
		string[0] = (x < 0.0) ? '-' : '+';	/* Place leading sign */
		string[1] = '\0';			/* Chop off old string */
		if (n > 1) {	/* Need an integer in front of pi */
			k += snprintf (fmt, GMT_LEN16, "%d", n);
			strcat (string, fmt);
			//k += irint (floor (log10 ((double)n))) + 1;	/* Add how many decimals needed for n */
		}
		strcat (string, "@~p@~");	/* Place the pi symbol */
		k += 5;	/* Add number of characters just placed to print pi */
		if (m > 1) {	/* Add the fractions part */
			k += snprintf (fmt, GMT_LEN16, "/%d", m);
			strcat (string, fmt);
			//k += irint (floor (log10 ((double)m))) + 2;	/* Add how many decimals needed for /m */
		}
		string[k] = '\0';	/* Truncate any old string */
		//fprintf (stderr, "f = %g n = %d  m = %d.  String = %s\n", f, n, m, string);
	}
	else
#ifndef WIN32
		sprintf (string, format, x);
#else
	{	/* Windows doesn't support %' format */
		if (use_locale) {
			char *new_format = gmt_strrep(format, "%'", "%");
			sprintf (string, new_format, x);
			gmt_M_str_free (new_format);
		} else
			sprintf (string, format, x);
	}
#endif
	if (use_locale) {
#ifdef HAVE_SETLOCALE
		setlocale (LC_NUMERIC, "C");	/* Undo the damage */
#endif
		if (strchr (string, ',') == NULL && fabs (x) > 1000.0 && fabs (x - irint (x)) < GMT_CONV8_LIMIT) {
			/* System not capable of printf groups for integers so we insert those commas manually... */
			char *tmp = strdup (string);
			int n = 0, olen = (int)strlen (tmp), k = (x < 0) ? 1 : 0;
			int nlen = olen + irint (floor (log10(fabs(x))/3.0));	/* Number of commas added */
			string[nlen] = '\0';
			/* We guild the string from back to front */
			while (olen) {	/* While more letters in original string */
				string[--nlen] = tmp[--olen];
				if (++n == 3 && (olen-k) > 0) {
					string[--nlen] = ',';
					n = 0;
				}
			}
			GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Expanded %s to %s\n", tmp, string);
			gmt_M_str_free (tmp);
		}
	}
}

/*! . */
void gmt_hold_contour (struct GMT_CTRL *GMT, double **xxx, double **yyy, uint64_t nn, double zval, char *label, char ctype, double cangle, bool closed, bool contour, struct GMT_CONTOUR *G) {
	/* The xxx, yyy are expected to be projected x/y inches.
	 * This function just makes sure that the xxx/yyy are continuous and do not have map jumps.
	 * If there are jumps we find them and call the main gmtsupport_hold_contour_sub for each segment
	 * contour is true for contours and false for quoted lines.
	 */

	uint64_t seg, first, n, *split = NULL;
	double *xs = NULL, *ys = NULL, *xin = NULL, *yin = NULL;

	if ((split = gmtlib_split_line (GMT, xxx, yyy, &nn, G->line_type)) == NULL) {	/* Just one long line */
		gmtsupport_hold_contour_sub (GMT, xxx, yyy, nn, zval, label, ctype, cangle, closed, contour, G);
		return;
	}

	/* Here we had jumps and need to call the _sub function once for each segment */

	xin = *xxx;	yin = *yyy;
	for (seg = 0, first = 0; seg <= split[0]; seg++) {	/* Number of segments are given by split[0] + 1 */
		n = split[seg+1] - first;
		xs = gmt_M_memory (GMT, NULL, n, double);
		ys = gmt_M_memory (GMT, NULL, n, double);
		gmt_M_memcpy (xs, &xin[first], n, double);
		gmt_M_memcpy (ys, &yin[first], n, double);
		gmtsupport_hold_contour_sub (GMT, &xs, &ys, n, zval, label, ctype, cangle, closed, contour, G);
		gmt_M_free (GMT, xs);
		gmt_M_free (GMT, ys);
		first += n;	/* First point in the next segment */
	}
	gmt_M_free (GMT, split);
}

/*! . */
void gmt_decorated_line (struct GMT_CTRL *GMT, double **xxx, double **yyy, uint64_t nn, struct GMT_DECORATE *G, struct GMT_DATASET *D, uint64_t seg) {
	/* The xxx, yyy are expected to be projected x/y inches.
	 * This function just makes sure that the xxx/yyy are continuous and do not have map jumps.
	 * If there are jumps we find them and call the main gmtsupport_decorated_line_sub for each segment
	 */

	uint64_t *split = NULL;

	if ((split = gmtlib_split_line (GMT, xxx, yyy, &nn, G->line_type)) == NULL)	/* Just one long line */
		gmtsupport_decorated_line_sub (GMT, *xxx, *yyy, nn, G, D, seg);
	else {
		/* Here we had jumps and need to call the _sub function once for each segment */
		uint64_t seg, first, n;
		double *xin = *xxx, *yin = *yyy;
		for (seg = 0, first = 0; seg <= split[0]; seg++) {	/* Number of segments are given by split[0] + 1 */
			n = split[seg+1] - first;
			gmtsupport_decorated_line_sub (GMT, &xin[first], &yin[first], n, G, D, seg);
			first = n;	/* First point in next segment */
		}
		gmt_M_free (GMT, split);
	}
}

/*! . */
void gmt_get_plot_array (struct GMT_CTRL *GMT) {
	/* Allocate more space for plot arrays */
	GMT->current.plot.n_alloc = (GMT->current.plot.n_alloc == 0) ? GMT_CHUNK : (GMT->current.plot.n_alloc << 1);
	GMT->current.plot.x = gmt_M_memory (GMT, GMT->current.plot.x, GMT->current.plot.n_alloc, double);
	GMT->current.plot.y = gmt_M_memory (GMT, GMT->current.plot.y, GMT->current.plot.n_alloc, double);
	GMT->current.plot.pen = gmt_M_memory (GMT, GMT->current.plot.pen, GMT->current.plot.n_alloc, unsigned int);
}

/*! . */
int gmt_get_format (struct GMT_CTRL *GMT, double interval, char *unit, char *prefix, char *format) {
	int i, j, ndec = 0;
	bool general = false;
	char text[GMT_BUFSIZ];
	size_t s_length;

	if (fabs (interval) < GMT_CONV15_LIMIT) interval = 0.0;
	if (!strcmp (GMT->current.setting.format_float_map, "%.12g")) {	/* Default map format given means auto-detect decimals */

		/* Find number of decimals needed in the format statement */

		snprintf (text, GMT_BUFSIZ, GMT->current.setting.format_float_map, interval);
		for (i = 0; text[i] && text[i] != '.'; i++);
		if (text[i]) {	/* Found a decimal point */
			for (j = i + 1; text[j] && text[j] != 'e'; j++);
			ndec = j - i - 1;
			if (text[j] == 'e') {	/* Exponential notation, modify ndec */
				ndec -= atoi (&text[++j]);
				if (ndec < 0) ndec = 0;	/* since a positive exponent could give -ve answer */
			}
		}
		general = true;
		strcpy (format, GMT->current.setting.format_float_map);
	}

	if (unit && unit[0]) {	/* Must append the unit string */
		if (!strchr (unit, '%'))	/* No percent signs */
			strncpy (text, unit, 80U);
		else {
			s_length = strlen(unit);
			for (i = j = 0; i < (int)s_length; i++) {
				text[j++] = unit[i];
				if (unit[i] == '%') text[j++] = unit[i];
			}
			text[j] = 0;
		}
		if (ndec > 0)
			sprintf (format, "%%.%df%s", ndec, text);
		else
			sprintf (format, "%s%s", GMT->current.setting.format_float_map, text);
		if (ndec == 0) ndec = 1;	/* To avoid resetting format later */
	}
	else if (ndec > 0)
		sprintf (format, "%%.%df", ndec);
	else if (!general) {	/* Pull ndec from given format if .<precision> is given */
		int len = (int)MIN(strlen(GMT->current.setting.format_float_map), GMT_LEN64) - 1;
		for (i = 0, j = -1; j == -1 && i < len && GMT->current.setting.format_float_map[i]; i++)
			if (i < len && GMT->current.setting.format_float_map[i] == '.') j = i;	/* The extra i > len needed to defeat cppcheck confusion */
		if (j > -1) ndec = atoi (&GMT->current.setting.format_float_map[j+1]);
		strcpy (format, GMT->current.setting.format_float_map);
	}
	if (prefix && prefix[0]) {	/* Must prepend the prefix string */
		snprintf (text, GMT_BUFSIZ, "%s%s", prefix, format);
		strcpy (format, text);
	}
	return (ndec);
}

void gmt_set_inside_mode (struct GMT_CTRL *GMT, struct GMT_DATASET *D, unsigned int mode) {
	/* Determine if we use spherical or Cartesian function for in--on-out polygon tests */
	static char *method[2] = {"Cartesian", "spherical"};
	if (mode == GMT_IOO_SPHERICAL)	/* Force spherical */
		GMT->current.proj.sph_inside = true;
	else if (mode == GMT_IOO_CARTESIAN)	/* Force Cartesian */
		GMT->current.proj.sph_inside = false;
	else if (gmt_M_is_cartesian (GMT, GMT_IN))	/* If data is Cartesian then we do that */
		GMT->current.proj.sph_inside = false;
	else if (GMT->current.map.is_world)	/* Here we are dealing with geographic data that has 360 degree range */
		GMT->current.proj.sph_inside = true;
	else if (D) {	/* Geographic data less than 360 degree range in longitudes */
		double lat[2];
		lat[0] = D->min[GMT_Y]; lat[1] = D->max[GMT_Y];
		if (doubleAlmostEqual (lat[0], -90.0) || doubleAlmostEqual (lat[1], +90.0))	/* Goes to a pole, must do spherical */
			GMT->current.proj.sph_inside = true;
		else {	/* Limited in lon and lat, can do Cartesian but must ensure polygons do not jump within range */
			uint64_t tbl, seg, row;
			unsigned int range;
			struct GMT_DATASEGMENT *S = NULL;

			GMT->current.proj.sph_inside = false;
			if (D->min[GMT_X] >= 0.0 && D->max[GMT_X] > 0.0)
				range = GMT_IS_0_TO_P360_RANGE;
			else if (D->min[GMT_X] < 0.0 && D->max[GMT_X] <= 0.0)
				range = GMT_IS_M360_TO_0_RANGE;
			else
				range = GMT_IS_M180_TO_P180_RANGE;
			/* Ensure that all longitudes are in the correct range as required by gmt_non_zero_winding */
			for (tbl = 0; tbl < D->n_tables; tbl++) {
				for (seg = 0; seg < D->table[tbl]->n_segments; seg++) {
					S = D->table[tbl]->segment[seg];	/* Shorthand */
					for (row = 0; row < S->n_rows; row++)
						gmt_lon_range_adjust (range, &S->data[GMT_X][row]);
				}
			}
		}
	}
	else
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Not enough information given to gmt_set_inside_mode.\n");
	GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "A point's inside/outside status w.r.t. polygon(s) will be determined using a %s algorithm.\n", method[GMT->current.proj.sph_inside]);
}

/*! . */
unsigned int gmt_non_zero_winding (struct GMT_CTRL *GMT, double xp, double yp, double *x_in, double *y_in, uint64_t n_path) {
	/* Routine returns (2) if (xp,yp) is inside the
	   polygon x[n_path], y[n_path], (0) if outside,
	   and (1) if exactly on the path edge.
	   Uses non-zero winding rule in Adobe PostScript
	   Language reference manual, section 4.6 on Painting.
	   Path should have been closed first, so that
	   x[n_path-1] = x[0], and y[n_path-1] = y[0].

	   This is version 2, trying to kill a bug
	   in above routine:  If point is on X edge,
	   fails to discover that it is on edge.

	   We are imagining a ray extending "up" from the
	   point (xp,yp); the ray has equation x = xp, y >= yp.
	   Starting with crossing_count = 0, we add 1 each time
	   the path crosses the ray in the +x direction, and
	   subtract 1 each time the ray crosses in the -x direction.
	   After traversing the entire polygon, if (crossing_count)
	   then point is inside.  We also watch for edge conditions.

	   If two or more points on the path have x[i] == xp, then
	   we have an ambiguous case, and we have to find the points
	   in the path before and after this section, and check them.
	   */

	uint64_t i, j, k, jend, crossing_count;
	bool above, free = false;
	double y_sect, *x, *y;

	if (n_path < 3) return (GMT_OUTSIDE);	/* Cannot be inside a null set, a point or a straight line so default to outside */

	if (gmt_polygon_is_open (GMT, x_in, y_in, n_path)) {
		GMT_Report (GMT->parent, GMT_MSG_WARNING, "gmt_non_zero_winding given non-closed polygon - must create closed polygon\n");
		x = gmt_M_memory (GMT, NULL, n_path+1, double);
		y = gmt_M_memory (GMT, NULL, n_path+1, double);
		gmt_M_memcpy (x, x_in, n_path, double);	x[n_path] = x[0];	/* CLose the polygon */
		gmt_M_memcpy (y, y_in, n_path, double);	y[n_path] = y[0];	/* CLose the polygon */
		free = true;
	}
	else {	/* Can use input points */
		x = x_in;
		y = y_in;
	}

	above = false;
	crossing_count = 0;

	/* First make sure first point in path is not a special case:  */
	j = jend = n_path - 1;
	if (x[j] == xp) {
		/* Trouble already.  We might get lucky:  */
		if (y[j] == yp) goto on_edge_case;

		/* Go backward down the polygon until x[i] != xp:  */
		if (y[j] > yp) above = true;
		i = j - 1;
		while (x[i] == xp && i > 0) {
			if (y[i] == yp) goto on_edge_case;
			if (!(above) && y[i] > yp) above = true;
			i--;
		}

		/* Now if i == 0 polygon is degenerate line x=xp;
		   since we know xp,yp is inside bounding box,
		   it must be on edge:  */
		if (i == 0) goto on_edge_case;

		/* Now we want to mark this as the end, for later:  */
		jend = i;

		/* Now if (j-i)>1 there are some segments the point could be exactly on:  */
		for (k = i+1; k < j; k++) {
			if ((y[k] <= yp && y[k+1] >= yp) || (y[k] >= yp && y[k+1] <= yp)) goto on_edge_case;
		}


		/* Now we have arrived where i is > 0 and < n_path-1, and x[i] != xp.
			We have been using j = n_path-1.  Now we need to move j forward
			from the origin:  */
		j = 1;
		while (x[j] == xp) {
			if (y[j] == yp) goto on_edge_case;
			if (!(above) && y[j] > yp) above = true;
			j++;
		}

		/* Now at the worst, j == jstop, and we have a polygon with only 1 vertex
			not at x = xp.  But now it doesn't matter, that would end us at
			the main while below.  Again, if j>=2 there are some segments to check:  */
		for (k = 0; k < j-1; k++) {
			if ((y[k] <= yp && y[k+1] >= yp) || (y[k] >= yp && y[k+1] <= yp)) goto on_edge_case;
		}


		/* Finally, we have found an i and j with points != xp.  If (above) we may have crossed the ray:  */
		if (above && x[i] < xp && x[j] > xp)
			crossing_count++;
		else if (above && x[i] > xp && x[j] < xp)
			crossing_count--;

		/* End nightmare scenario for x[0] == xp.  */
	}

	else {
		/* Get here when x[0] != xp:  */
		i = 0;
		j = 1;
		while (x[j] == xp && j < jend) {
			if (y[j] == yp) goto on_edge_case;
			if (!(above) && y[j] > yp) above = true;
			j++;
		}
		/* Again, if j==jend, (i.e., 0) then we have a polygon with only 1 vertex
			not on xp and we will branch out below.  */

		/* if ((j-i)>2) the point could be on intermediate segments:  */
		for (k = i+1; k < j-1; k++) {
			if ((y[k] <= yp && y[k+1] >= yp) || (y[k] >= yp && y[k+1] <= yp)) goto on_edge_case;
		}

		/* Now we have x[i] != xp and x[j] != xp.
			If (above) and x[i] and x[j] on opposite sides, we are certain to have crossed the ray.
			If not (above) and (j-i)>1, then we have not crossed it.
			If not (above) and j-i == 1, then we have to check the intersection point.  */

		if (x[i] < xp && x[j] > xp) {
			if (above)
				crossing_count++;
			else if ((j-i) == 1) {
				y_sect = y[i] + (y[j] - y[i]) * ((xp - x[i]) / (x[j] - x[i]));
				if (y_sect == yp) goto on_edge_case;
				if (y_sect > yp) crossing_count++;
			}
		}
		if (x[i] > xp && x[j] < xp) {
			if (above)
				crossing_count--;
			else if ((j-i) == 1) {
				y_sect = y[i] + (y[j] - y[i]) * ((xp - x[i]) / (x[j] - x[i]));
				if (y_sect == yp) goto on_edge_case;
				if (y_sect > yp) crossing_count--;
			}
		}

		/* End easier case for x[0] != xp  */
	}

	/* Now MAIN WHILE LOOP begins:
		Set i = j, and search for a new j, and do as before.  */

	i = j;
	while (i < jend) {
		above = false;
		j = i+1;
		while (x[j] == xp) {
			if (y[j] == yp) goto on_edge_case;
			if (!(above) && y[j] > yp) above = true;
			j++;
		}
		/* if ((j-i)>2) the point could be on intermediate segments:  */
		for (k = i+1; k < j-1; k++) {
			if ((y[k] <= yp && y[k+1] >= yp) || (y[k] >= yp && y[k+1] <= yp)) goto on_edge_case;
		}

		/* Now we have x[i] != xp and x[j] != xp.
			If (above) and x[i] and x[j] on opposite sides, we are certain to have crossed the ray.
			If not (above) and (j-i)>1, then we have not crossed it.
			If not (above) and j-i == 1, then we have to check the intersection point.  */

		if (x[i] < xp && x[j] > xp) {
			if (above)
				crossing_count++;
			else if ((j-i) == 1) {
				y_sect = y[i] + (y[j] - y[i]) * ((xp - x[i]) / (x[j] - x[i]));
				if (y_sect == yp) goto on_edge_case;
				if (y_sect > yp) crossing_count++;
			}
		}
		if (x[i] > xp && x[j] < xp) {
			if (above)
				crossing_count--;
			else if ((j-i) == 1) {
				y_sect = y[i] + (y[j] - y[i]) * ((xp - x[i]) / (x[j] - x[i]));
				if (y_sect == yp) goto on_edge_case;
				if (y_sect > yp) crossing_count--;
			}
		}

		/* That's it for this piece.  Advance i:  */

		i = j;
	}

	if (free) { gmt_M_free (GMT, x); gmt_M_free (GMT, y); }

	/* End of MAIN WHILE.  Get here when we have gone all around without landing on edge.  */

	return ((crossing_count) ? GMT_INSIDE: GMT_OUTSIDE);

on_edge_case:
	if (free) { gmt_M_free (GMT, x); gmt_M_free (GMT, y); }

	return (GMT_ONEDGE);
}

/*! . */
unsigned int gmt_inonout (struct GMT_CTRL *GMT, double x, double y, struct GMT_DATASEGMENT *S) {
	/* Front end for both spherical and Cartesian in-on-out functions.
	 * Knows to check for polygons with holes as well. */
	unsigned int side, side_h;
	struct GMT_DATASEGMENT *H = NULL;
	struct GMT_DATASEGMENT_HIDDEN *SH = gmt_get_DS_hidden (S);
	struct GMT_DATASEGMENT_HIDDEN *SHnext = NULL;

	if ((side = gmtsupport_inonout_sub (GMT, x, y, S)) <= GMT_ONEDGE) return (side);	/* Outside polygon or on perimeter, we are done */

	/* Here, point is inside the polygon perimeter. See if there are holes */

	if (GMT->current.io.OGR && (H = SH->next)) {	/* Must check for and skip if inside a hole */
		side_h = GMT_OUTSIDE;	/* We are outside a hole until we are found to be inside it */
		SHnext = gmt_get_DS_hidden (H);
		while (side_h == GMT_OUTSIDE && H && SHnext->ogr && SHnext->ogr->pol_mode == GMT_IS_HOLE) {	/* Found a hole */
			/* Must check if point is inside this hole polygon */
			side_h = gmtsupport_inonout_sub (GMT, x, y, H);
			H = SHnext->next;	/* Move to next polygon hole */
			if (H) SHnext = gmt_get_DS_hidden (H);
		}
		if (side_h == GMT_INSIDE) side = GMT_OUTSIDE;	/* Inside one of the holes, hence outside polygon; go to next perimeter polygon */
		if (side_h == GMT_ONEDGE) side = GMT_ONEDGE;	/* On path of one of the holes, hence on polygon path; update side */
	}
	else if ((H = SH->next)) {	/* Must also check non ogr polygones for holes */
		side_h = GMT_OUTSIDE;	/* We are outside a hole until we are found to be inside it */
		SHnext = gmt_get_DS_hidden (H);
		while (side_h == GMT_OUTSIDE && H && SHnext->pol_mode == GMT_IS_HOLE) {	/* Found a hole */
			/* Must check if point is inside this hole polygon */
			side_h = gmtsupport_inonout_sub (GMT, x, y, H);
			H = SHnext->next;	/* Move to next polygon hole */
			if (H) SHnext = gmt_get_DS_hidden (H);
		}
		if (side_h == GMT_INSIDE) side = GMT_OUTSIDE;	/* Inside one of the holes, hence outside polygon; go to next perimeter polygon */
		if (side_h == GMT_ONEDGE) side = GMT_ONEDGE;	/* On path of one of the holes, hence on polygon path; update side */
	}

	/* Here, point is inside or on edge, we return the value */
	return (side);
}

/* GMT always compiles the standard Delaunay triangulation routine
 * based on the work by Dave Watson.  You may also link with the triangle.o
 * module from Jonathan Shewchuk, Berkeley U. by passing the compiler
 * directive -DTRIANGLE_D. The latter is much faster and also has options
 * for Voronoi construction (which Watson's function does not have).
 */

/*! . */
int64_t gmt_delaunay (struct GMT_CTRL *GMT, double *x_in, double *y_in, uint64_t n, int **link) {
	if (GMT->current.setting.triangulate == GMT_TRIANGLE_SHEWCHUK) return (gmtsupport_delaunay_shewchuk (GMT, x_in, y_in, n, link));
	if (GMT->current.setting.triangulate == GMT_TRIANGLE_WATSON)   return (gmtsupport_delaunay_watson    (GMT, x_in, y_in, n, link));
	GMT_Report (GMT->parent, GMT_MSG_ERROR, "GMT_TRIANGULATE outside possible range! %d\n", GMT->current.setting.triangulate);
	return (-1);
}

/*! . */
struct GMT_DATASET * gmt_voronoi (struct GMT_CTRL *GMT, double *x_in, double *y_in, uint64_t n, double *wesn, unsigned int mode) {
	if (GMT->current.setting.triangulate == GMT_TRIANGLE_SHEWCHUK) return (gmtsupport_voronoi_shewchuk (GMT, x_in, y_in, n, wesn, mode));
	if (GMT->current.setting.triangulate == GMT_TRIANGLE_WATSON)   return (gmtsupport_voronoi_watson    (GMT, x_in, y_in, n, wesn, mode));
	GMT_Report (GMT->parent, GMT_MSG_ERROR, "GMT_TRIANGULATE outside possible range! %d\n", GMT->current.setting.triangulate);
	return (NULL);
}

/*! . */
void gmt_delaunay_free (struct GMT_CTRL *GMT, int **link) {
	/* Since one function uses gmt_M_memory and the other does not */
	if (GMT->current.setting.triangulate == GMT_TRIANGLE_SHEWCHUK) gmt_M_str_free (*link);
	if (GMT->current.setting.triangulate == GMT_TRIANGLE_WATSON) gmt_M_free (GMT, *link);
}
/*
 * This section holds functions used for setting boundary  conditions in
 * processing grd file data.
 *
 * This is a new feature of GMT v3.1.   My first draft of this (April 1998)
 * set only one row of padding.  Additional thought showed that the bilinear
 * invocation of bcr routines would not work properly on periodic end conditions
 * in this case.  So second draft (May 5-6, 1998) will set two rows of padding,
 * and I will also have to edit bcr so that it works for this case.  The GMT
 * bcr routines are currently used in grdsample, grdtrack, and grdview.
 *
 * I anticipate that later (GMT v5 ?) this code could (?) be modified to also
 * handle the boundary conditions needed by surface.
 *
 * The default boundary condition is derived from application of Green's
 * theorem to the conditions for minimizing curvature:
 * laplacian (f) = 0 on edges, and d[laplacian(f)]/dn = 0 on edges, where
 * n is normal to an edge.  We also set d2f/dxdy = 0 at corners.
 *
 * The new routines here allow the user to choose other specifications:
 *
 * Either
 *	one or both of
 *	data are periodic in (x_max - x_min)
 *	data are periodic in (y_max - y_min)
 *
 * Or
 *	data are a geographical grid.
 *
 * Periodicities assume that the min,max are compatible with the inc;
 * that is, (x_max - x_min)modulo(x_inc) ~= 0.0 within precision tolerances,
 * and similarly for y.  It is assumed that this is OK and that gmt_grd_RI_verify
 * was called during read grd and found to be OK.
 *
 * In the geographical case, if x_max - x_min < 360 we will use the default
 * boundary conditions, but if x_max - x_min >= 360 the 360 periodicity in x
 * will be used to set the x boundaries, and so we require 360modulo(x_inc)
 * == 0.0 within precision tolerance.  If y_max != 90 the north edge will
 * default, and similarly for y_min != -90.  If a y edge is at a pole and
 * x_max - x_min >= 360 then the geographical y uses a 180 degree phase
 * shift in the values, so we require 180modulo(x_inc) == 0.
 * Note that a grid-registered file will require that the entire row of
 * values representing a pole must all be equal, else d/dx != 0 which
 * is wrong.  So compatibility error-checking is built in.
 *
 * Note that a periodicity or polar boundary eliminates the need for
 * d2/dxdy = 0 at a corner.  There are no "corners" in those cases.
 *
 * Author:	W H F Smith
 * Date:	17 April 1998
 * Revised:	5  May 1998
 * Notes PW, April-2011: BCs are now set after a grid or image is read,
 * thus all programs load grids with all BCs set. Contents of old structs
 * GMT_BCR and GMT_EDGEINFO folded into GRDHEADER. Remaining functions
 * were renamed and are now
 * 	gmt_BC_init		- Determines and sets what BCs to use
 *	gmt_grd_BC_set		- Sets the BCs on a grid
 *	gmtlib_image_BC_set	- Sets the BCs on an image
 */

/*! Initialize grid boundary conditions based on grid header and -n settings */
int gmt_BC_init (struct GMT_CTRL *GMT, struct GMT_GRID_HEADER *h) {
	int i = 0, type;
	bool same;
	char *kind[5] = {"not set", "natural", "periodic", "geographic", "extended data"};
	struct GMT_GRID_HEADER_HIDDEN *HH = gmt_get_H_hidden (h);

	if (HH->no_BC) return (GMT_NOERROR);	/* Told not to deal with BC stuff */

	if (GMT->common.n.bc_set) {	/* Override BCs via -n+<BC> */
		while (GMT->common.n.BC[i]) {
			switch (GMT->common.n.BC[i]) {
				case 'g':	/* Geographic sets everything */
					HH->gn = HH->gs = true;
					HH->BC[XLO] = HH->BC[XHI] = HH->BC[YLO] = HH->BC[YHI] = GMT_BC_IS_GEO;
					break;
				case 'n':	/* Natural BCs */
					if (GMT->common.n.BC[i+1] == 'x') { HH->BC[XLO] = HH->BC[XHI] = GMT_BC_IS_NATURAL; i++; }
					else if (GMT->common.n.BC[i+1] == 'y') { HH->BC[YLO] = HH->BC[YHI] = GMT_BC_IS_NATURAL; i++; }
					else HH->BC[XLO] = HH->BC[XHI] = HH->BC[YLO] = HH->BC[YHI] = GMT_BC_IS_NATURAL;
					break;
				case 'p':	/* Periodic BCs */
					if (GMT->common.n.BC[i+1] == 'x') { HH->BC[XLO] = HH->BC[XHI] = GMT_BC_IS_PERIODIC; HH->nxp = 1; i++; }
					else if (GMT->common.n.BC[i+1] == 'y') { HH->BC[YLO] = HH->BC[YHI] = GMT_BC_IS_PERIODIC; HH->nyp = 1; i++; }
					else { HH->BC[XLO] = HH->BC[XHI] = HH->BC[YLO] = HH->BC[YHI] = GMT_BC_IS_PERIODIC; HH->nxp = HH->nyp = 1; }
					break;
				default:
					GMT_Report (GMT->parent, GMT_MSG_ERROR, "Cannot parse boundary condition %s\n", GMT->common.n.BC);
					return (-1);
					break;
			}
			i++;
		}
		if (HH->gn && !(HH->BC[XLO] == GMT_BC_IS_GEO && HH->BC[XHI] == GMT_BC_IS_GEO && HH->BC[YLO] == GMT_BC_IS_GEO && HH->BC[YHI] == GMT_BC_IS_GEO)) {
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "GMT boundary condition g overrides n[x|y] or p[x|y]\n");
			HH->BC[XLO] = HH->BC[XHI] = HH->BC[YLO] = HH->BC[YHI] = GMT_BC_IS_GEO;
		}
	}
	else {	/* Determine BC based on whether grid is geographic or not */
		type = (gmt_M_x_is_lon (GMT, GMT_IN)) ? GMT_BC_IS_GEO : GMT_BC_IS_NATURAL;
		for (i = 0; i < 4; i++)
			if (HH->BC[i] == GMT_BC_IS_NOTSET) HH->BC[i] = type;
	}

	/* Check if geographic conditions can be used with this grid */
	if (HH->gn && !gmt_grd_is_global (GMT, h)) {
		/* User has requested geographical conditions, but grid is not global */
		GMT_Report(GMT->parent, GMT_MSG_INFORMATION, "Longitude range too small; geographic boundary condition changed to natural.\n");
		HH->nxp = HH->nyp = 0;
		HH->gn  = HH->gs = false;
		for (i = 0; i < 4; i++)
			if (HH->BC[i] == GMT_BC_IS_NOTSET) HH->BC[i] = GMT_BC_IS_NATURAL;
	}
	else if (gmt_grd_is_global (GMT, h)) {	/* Grid is truly global */
		double xtest = fmod (180.0, h->inc[GMT_X]) * HH->r_inc[GMT_X];
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Grid is considered to have a 360-degree longitude range.\n");
		if (GMT->parent->ignore_BC) xtest = 0.0;	/* To bypass the checks below */
		/* xtest should be within GMT_CONV4_LIMIT of zero or of one.  */
		if (xtest > GMT_CONV4_LIMIT && xtest < (1.0 - GMT_CONV4_LIMIT) && GMT->current.proj.projection_GMT == 0) {
			/* Maybe error.  We need it to divide into 180 so we can phase-shift at poles but not if we
			   already projected the grid to Cartesian.  */
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "x_inc does not divide 180; geographic boundary condition changed to natural.\n");
			HH->nxp = HH->nyp = 0;
			HH->gn  = HH->gs = false;
			for (i = 0; i < 4; i++)
				if (HH->BC[i] == GMT_BC_IS_NOTSET) HH->BC[i] = GMT_BC_IS_NATURAL;
		}
		else {
			HH->nxp = urint (360.0 * HH->r_inc[GMT_X]);
			HH->nyp = 0;
			HH->gn = ((fabs(h->wesn[YHI] - 90.0)) < (GMT_CONV4_LIMIT * h->inc[GMT_Y]));
			HH->gs = ((fabs(h->wesn[YLO] + 90.0)) < (GMT_CONV4_LIMIT * h->inc[GMT_Y]));
			if (!HH->gs) HH->BC[YLO] = GMT_BC_IS_NATURAL;
			if (!HH->gn) HH->BC[YHI] = GMT_BC_IS_NATURAL;
		}
	}
	else {	/* Either periodic or natural */
		if (HH->nxp != 0) HH->nxp = (h->registration == GMT_GRID_PIXEL_REG) ? h->n_columns : h->n_columns - 1;
		if (HH->nyp != 0) HH->nyp = (h->registration == GMT_GRID_PIXEL_REG) ? h->n_rows : h->n_rows - 1;
	}

	if (HH->BC[XLO] == GMT_BC_IS_PERIODIC && HH->BC[XHI] == GMT_BC_IS_PERIODIC) {	/* Parameters needed for x-periodic, non-geographic grids */
		GMT->common.n.periodic[GMT_X] = true;
		GMT->common.n.range[GMT_X] = h->wesn[XHI] - h->wesn[XLO];
		GMT->common.n.half_range[GMT_X] = 0.5 * GMT->common.n.range[GMT_X];
	}
	if (HH->BC[YLO] == GMT_BC_IS_PERIODIC && HH->BC[YHI] == GMT_BC_IS_PERIODIC) {	/* Parameters needed for y-periodic, non-geographic grids */
		GMT->common.n.periodic[GMT_Y] = true;
		GMT->common.n.range[GMT_Y] = h->wesn[YHI] - h->wesn[YLO];
		GMT->common.n.half_range[GMT_Y] = 0.5 * GMT->common.n.range[GMT_Y];
	}
	for (i = 1, same = true; same && i < 4; i++) if (HH->BC[i] != HH->BC[i-1]) same = false;

	if (same)
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Chosen boundary condition for all edges: %s\n", kind[HH->BC[XLO]]);
	else {
		if (HH->BC[XLO] == HH->BC[XHI])
			GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Chosen boundary condition for left and right edges: %s\n", kind[HH->BC[XLO]]);
		else {
			GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Chosen boundary condition for left   edge: %s\n", kind[HH->BC[XLO]]);
			GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Chosen boundary condition for right  edge: %s\n", kind[HH->BC[XHI]]);
		}
		if (HH->BC[YLO] == HH->BC[YHI])
			GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Chosen boundary condition for bottom and top edges: %s\n", kind[HH->BC[YLO]]);
		else {
			GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Chosen boundary condition for bottom edge: %s\n", kind[HH->BC[YLO]]);
			GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Chosen boundary condition for top    edge: %s\n", kind[HH->BC[YHI]]);
		}
	}
	/* Set this grid's interpolation parameters */

	HH->bcr_interpolant = GMT->common.n.interpolant;
	HH->bcr_threshold = GMT->common.n.threshold;
	HH->bcr_n = (HH->bcr_interpolant == BCR_NEARNEIGHBOR) ? 1 : ((HH->bcr_interpolant == BCR_BILINEAR) ? 2 : 4);

	return (GMT_NOERROR);
}

/*! . */
int gmt_grd_BC_set (struct GMT_CTRL *GMT, struct GMT_GRID *G, unsigned int direction) {
	/* Set two rows of padding (pad[] can be larger) around data according
	   to desired boundary condition info in that header.
	   Returns -1 on problem, 0 on success.
	   If either x or y is periodic, the padding is entirely set.
	   However, if neither is true (this rules out geographical also)
	   then all but three corner-most points in each corner are set.

	   As written, not ready to use with "surface" for GMT 5, because
	   assumes left/right is +/- 1 and down/up is +/- mx.  In "surface"
	   the amount to move depends on the current mesh size, a parameter
	   not used here.

	   This is the revised, two-rows version (WHFS 6 May 1998).
	*/

	uint64_t mx;		/* Width of padded array; width as malloc'ed  */
	uint64_t mxnyp;		/* distance to periodic constraint in j direction  */
	uint64_t i, jmx;		/* Current i, j * mx  */
	uint64_t nxp2;		/* 1/2 the xg period (180 degrees) in cells  */
	uint64_t i180;		/* index to 180 degree phase shift  */
	uint64_t iw, iwo1, iwo2, iwi1, ie, ieo1, ieo2, iei1;  /* see below  */
	uint64_t jn, jno1, jno2, jni1, js, jso1, jso2, jsi1;  /* see below  */
	uint64_t jno1k, jno2k, jso1k, jso2k, iwo1k, iwo2k, ieo1k, ieo2k;
	uint64_t j1p, j2p;	/* j_o1 and j_o2 pole constraint rows  */
	unsigned int n_skip, n_set;
	unsigned int bok;		/* bok used to test that things are OK  */
	bool set[4] = {true, true, true, true};
	struct GMT_GRID_HEADER_HIDDEN *HH = gmt_get_H_hidden (G->header);

	char *kind[5] = {"not set", "natural", "periodic", "geographic", "extended data"};
	char *edge[4] = {"left  ", "right ", "bottom", "top   "};

	if (G->header->complex_mode & GMT_GRID_IS_COMPLEX_MASK) return (GMT_NOERROR);	/* Only set up for real arrays */
	if (HH->no_BC) return (GMT_NOERROR);	/* Told not to deal with BC stuff */
	if (G->data == NULL) return (GMT_NOERROR);	/* Premature call; no grid data yet */

	for (i = n_skip = 0; i < 4; i++) {
		if (HH->BC[i] == GMT_BC_IS_DATA) {set[i] = false; n_skip++;}	/* No need to set since there is data in the pad area */
	}
	if (n_skip == 4) {	/* No need to set anything since there is data in the pad area on all sides */
		GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmt_grd_BC_set: All boundaries set via extended data.\n");
		return (GMT_NOERROR);
	}

	/* Check minimum size:  */
	if (G->header->n_columns < 1 || G->header->n_rows < 1) {
		GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmt_grd_BC_set: Requires n_columns,n_rows at least 1.\n");
		return (GMT_NOERROR);
	}

	/* Check that pad is at least 2 */
	for (i = bok = 0; i < 4; i++) if (G->header->pad[i] < 2) bok++;
	if (bok > 0) {
		if (direction == GMT_IN) GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmt_grd_BC_set: Called with a pad < 2; skipped.\n");
		return (GMT_NOERROR);
	}

	/* Initialize stuff:  */

	mx = G->header->mx;
	nxp2 = HH->nxp / 2;	/* Used for 180 phase shift at poles  */

	iw = G->header->pad[XLO];	/* i for west-most data column */
	iwo1 = iw - 1;		/* 1st column outside west  */
	iwo2 = iwo1 - 1;	/* 2nd column outside west  */
	iwi1 = iw + 1;		/* 1st column  inside west  */

	ie = G->header->pad[XLO] + G->header->n_columns - 1;	/* i for east-most data column */
	ieo1 = ie + 1;		/* 1st column outside east  */
	ieo2 = ieo1 + 1;	/* 2nd column outside east  */
	iei1 = ie - 1;		/* 1st column  inside east  */

	jn = mx * G->header->pad[YHI];	/* j*mx for north-most data row  */
	jno1 = jn - mx;		/* 1st row outside north  */
	jno2 = jno1 - mx;	/* 2nd row outside north  */
	jni1 = jn + mx;		/* 1st row  inside north  */

	js = mx * (G->header->pad[YHI] + G->header->n_rows - 1);	/* j*mx for south-most data row  */
	jso1 = js + mx;		/* 1st row outside south  */
	jso2 = jso1 + mx;	/* 2nd row outside south  */
	jsi1 = js - mx;		/* 1st row  inside south  */

	mxnyp = mx * HH->nyp;

	jno1k = jno1 + mxnyp;	/* data rows periodic to boundary rows  */
	jno2k = jno2 + mxnyp;
	jso1k = jso1 - mxnyp;
	jso2k = jso2 - mxnyp;

	iwo1k = iwo1 + HH->nxp;	/* data cols periodic to bndry cols  */
	iwo2k = iwo2 + HH->nxp;
	ieo1k = ieo1 - HH->nxp;
	ieo2k = ieo2 - HH->nxp;

	/* Duplicate rows and columns if n_columns or n_rows equals 1 */

	if (G->header->n_columns == 1) for (i = jn+iw; i <= js+iw; i += mx) G->data[i-1] = G->data[i+1] = G->data[i];
	if (G->header->n_rows == 1) for (i = jn+iw; i <= jn+ie; i++) G->data[i-mx] = G->data[i+mx] = G->data[i];

	/* Check poles for grid case.  It would be nice to have done this
		in GMT_boundcond_param_prep() but at that point the data
		array isn't passed into that routine, and may not have been
		read yet.  Also, as coded here, this bombs with error if
		the pole data is wrong.  But there could be an option to
		to change the condition to Natural in that case, with warning.  */

	if (G->header->registration == GMT_GRID_NODE_REG) {	/* A pole can only be a grid node with gridline registration */
		if (HH->gn) {	/* North pole case */
			bok = 0;
			if (gmt_M_is_fnan (G->data[jn + iw])) {	/* First is NaN so all should be NaN */
				for (i = iw+1; i <= ie; i++) if (!gmt_M_is_fnan (G->data[jn + i])) bok++;
			}
			else {	/* First is not NaN so all should be identical */
				for (i = iw+1; i <= ie; i++) if (G->data[jn + i] != G->data[jn + iw]) bok++;
			}
			if (bok > 0) GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmt_grd_BC_set: %d (of %d) inconsistent grid values at North pole.\n", bok, G->header->n_columns);
		}

		if (HH->gs) {	/* South pole case */
			bok = 0;
			if (gmt_M_is_fnan (G->data[js + iw])) {	/* First is NaN so all should be NaN */
				for (i = iw+1; i <= ie; i++) if (!gmt_M_is_fnan (G->data[js + i])) bok++;
			}
			else {	/* First is not NaN so all should be identical */
				for (i = iw+1; i <= ie; i++) if (G->data[js + i] != G->data[js + iw]) bok++;
			}
			if (bok > 0) GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmt_grd_BC_set: %d (of %d) inconsistent grid values at South pole.\n", bok, G->header->n_columns);
		}
	}

	/* Start with the case that x is not periodic, because in that case we also know that y cannot be polar.  */

	if (HH->nxp <= 0) {	/* x is not periodic  */

		if (HH->nyp > 0) {	/* y is periodic  */

			for (i = iw, bok = 0; i <= ie; ++i) {
				if (G->header->registration == GMT_GRID_NODE_REG && !doubleAlmostEqualZero (G->data[jn+i], G->data[js+i]))
					++bok;
				if (set[YHI]) {
					G->data[jno1 + i] = G->data[jno1k + i];
					G->data[jno2 + i] = G->data[jno2k + i];
				}
				if (set[YLO]) {
					G->data[jso1 + i] = G->data[jso1k + i];
					G->data[jso2 + i] = G->data[jso2k + i];
				}
			}
			if (bok > 0) GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmt_grd_BC_set: %d (of %d) inconsistent grid values at South and North boundaries for repeated nodes.\n", bok, G->header->n_columns);

			/* periodic Y rows copied.  Now do X naturals.
				This is easy since y's are done; no corner problems.
				Begin with Laplacian = 0, and include 1st outside rows
				in loop, since y's already loaded to 2nd outside.  */

			for (jmx = jno1; jmx <= jso1; jmx += mx) {
				if (set[XLO]) G->data[jmx + iwo1] = (gmt_grdfloat)(4.0 * G->data[jmx + iw]) - (G->data[jmx + iw + mx] + G->data[jmx + iw - mx] + G->data[jmx + iwi1]);
				if (set[XHI]) G->data[jmx + ieo1] = (gmt_grdfloat)(4.0 * G->data[jmx + ie]) - (G->data[jmx + ie + mx] + G->data[jmx + ie - mx] + G->data[jmx + iei1]);
			}

			/* Copy that result to 2nd outside row using periodicity.  */
			if (set[XLO]) {
				G->data[jno2 + iwo1] = G->data[jno2k + iwo1];
				G->data[jso2 + iwo1] = G->data[jso2k + iwo1];
			}
			if (set[XHI]) {
				G->data[jno2 + ieo1] = G->data[jno2k + ieo1];
				G->data[jso2 + ieo1] = G->data[jso2k + ieo1];
			}

			/* Now set d[laplacian]/dx = 0 on 2nd outside column.  Include 1st outside rows in loop.  */
			for (jmx = jno1; jmx <= jso1; jmx += mx) {
				if (set[XLO]) G->data[jmx + iwo2] = (G->data[jmx + iw - mx] + G->data[jmx + iw + mx] + G->data[jmx + iwi1])
					- (G->data[jmx + iwo1 - mx] + G->data[jmx + iwo1 + mx]) + (gmt_grdfloat)(5.0 * (G->data[jmx + iwo1] - G->data[jmx + iw]));
				if (set[XHI]) G->data[jmx + ieo2] = (G->data[jmx + ie - mx] + G->data[jmx + ie + mx] + G->data[jmx + iei1])
					- (G->data[jmx + ieo1 - mx] + G->data[jmx + ieo1 + mx]) + (gmt_grdfloat)(5.0 * (G->data[jmx + ieo1] - G->data[jmx + ie]));
			}

			/* Now copy that result also, for complete periodicity's sake  */
			if (set[XLO]) {
				G->data[jno2 + iwo2] = G->data[jno2k + iwo2];
				G->data[jso2 + iwo2] = G->data[jso2k + iwo2];
				HH->BC[XLO] = GMT_BC_IS_NATURAL;
			}
			if (set[XHI]) {
				G->data[jno2 + ieo2] = G->data[jno2k + ieo2];
				G->data[jso2 + ieo2] = G->data[jso2k + ieo2];
				HH->BC[XHI] = GMT_BC_IS_NATURAL;
			}

			/* DONE with X not periodic, Y periodic case.  Fully loaded.  */
			if (set[YLO] && set[YHI]) {
				HH->BC[YLO] = HH->BC[YHI] = GMT_BC_IS_PERIODIC;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmt_grd_BC_set: Set boundary condition for bottom and top edges: %s\n", kind[HH->BC[YLO]]);
			}
			else if (set[YLO]) {
				HH->BC[YLO] = GMT_BC_IS_PERIODIC;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmt_grd_BC_set: Set boundary condition for %s edge: %s\n", edge[YLO], kind[HH->BC[YLO]]);
			}
			else if (set[YHI]) {
				HH->BC[YHI] = GMT_BC_IS_PERIODIC;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmt_grd_BC_set: Set boundary condition for %s edge: %s\n", edge[YHI], kind[HH->BC[YHI]]);
			}

			return (GMT_NOERROR);
		}
		else {	/* Here begins the X not periodic, Y not periodic case  */

			/* First, set corner points.  Need not merely Laplacian(f) = 0
				but explicitly that d2f/dx2 = 0 and d2f/dy2 = 0.
				Also set d2f/dxdy = 0.  Then can set remaining points.  */

	/* d2/dx2 */	if (set[XLO]) G->data[jn + iwo1]   = (gmt_grdfloat)(2.0 * G->data[jn + iw] - G->data[jn + iwi1]);
	/* d2/dy2 */	if (set[YHI]) G->data[jno1 + iw]   = (gmt_grdfloat)(2.0 * G->data[jn + iw] - G->data[jni1 + iw]);
	/* d2/dxdy */	if (set[XLO] && set[YHI]) G->data[jno1 + iwo1] = G->data[jn + iwo1] + G->data[jno1 + iw] - G->data[jn + iw];

	/* d2/dx2 */	if (set[XHI]) G->data[jn + ieo1]   = (gmt_grdfloat)(2.0 * G->data[jn + ie] - G->data[jn + iei1]);
	/* d2/dy2 */	if (set[YHI]) G->data[jno1 + ie]   = (gmt_grdfloat)(2.0 * G->data[jn + ie] - G->data[jni1 + ie]);
	/* d2/dxdy */	if (set[XHI] && set[YHI]) G->data[jno1 + ieo1] = G->data[jn + ieo1] + G->data[jno1 + ie] - G->data[jn + ie];

	/* d2/dx2 */	if (set[XLO]) G->data[js + iwo1]   = (gmt_grdfloat)(2.0 * G->data[js + iw] - G->data[js + iwi1]);
	/* d2/dy2 */	if (set[YLO]) G->data[jso1 + iw]   = (gmt_grdfloat)(2.0 * G->data[js + iw] - G->data[jsi1 + iw]);
	/* d2/dxdy */	if (set[XLO] && set[YLO]) G->data[jso1 + iwo1] = G->data[js + iwo1] + G->data[jso1 + iw] - G->data[js + iw];

	/* d2/dx2 */	if (set[XHI]) G->data[js + ieo1]   = (gmt_grdfloat)(2.0 * G->data[js + ie] - G->data[js + iei1]);
	/* d2/dy2 */	if (set[YLO]) G->data[jso1 + ie]   = (gmt_grdfloat)(2.0 * G->data[js + ie] - G->data[jsi1 + ie]);
	/* d2/dxdy */	if (set[XHI] && set[YLO]) G->data[jso1 + ieo1] = G->data[js + ieo1] + G->data[jso1 + ie] - G->data[js + ie];

			/* Now set Laplacian = 0 on interior edge points, skipping corners:  */
			for (i = iwi1; i <= iei1; i++) {
				if (set[YHI]) G->data[jno1 + i] = (gmt_grdfloat)(4.0 * G->data[jn + i]) - (G->data[jn + i - 1] + G->data[jn + i + 1] + G->data[jni1 + i]);
				if (set[YLO]) G->data[jso1 + i] = (gmt_grdfloat)(4.0 * G->data[js + i]) - (G->data[js + i - 1] + G->data[js + i + 1] + G->data[jsi1 + i]);
			}
			for (jmx = jni1; jmx <= jsi1; jmx += mx) {
				if (set[XLO]) G->data[iwo1 + jmx] = (gmt_grdfloat)(4.0 * G->data[iw + jmx]) - (G->data[iw + jmx + mx] + G->data[iw + jmx - mx] + G->data[iwi1 + jmx]);
				if (set[XHI]) G->data[ieo1 + jmx] = (gmt_grdfloat)(4.0 * G->data[ie + jmx]) - (G->data[ie + jmx + mx] + G->data[ie + jmx - mx] + G->data[iei1 + jmx]);
			}

			/* Now set d[Laplacian]/dn = 0 on all edge pts, including
				corners, since the points needed in this are now set.  */
			for (i = iw; i <= ie; i++) {
				if (set[YHI]) G->data[jno2 + i] = G->data[jni1 + i] + (gmt_grdfloat)(5.0 * (G->data[jno1 + i] - G->data[jn + i]))
					+ (G->data[jn + i - 1] - G->data[jno1 + i - 1]) + (G->data[jn + i + 1] - G->data[jno1 + i + 1]);
				if (set[YLO]) G->data[jso2 + i] = G->data[jsi1 + i] + (gmt_grdfloat)(5.0 * (G->data[jso1 + i] - G->data[js + i]))
					+ (G->data[js + i - 1] - G->data[jso1 + i - 1]) + (G->data[js + i + 1] - G->data[jso1 + i + 1]);
			}
			for (jmx = jn; jmx <= js; jmx += mx) {
				if (set[XLO]) G->data[iwo2 + jmx] = G->data[iwi1 + jmx] + (gmt_grdfloat)(5.0 * (G->data[iwo1 + jmx] - G->data[iw + jmx]))
					+ (G->data[iw + jmx - mx] - G->data[iwo1 + jmx - mx]) + (G->data[iw + jmx + mx] - G->data[iwo1 + jmx + mx]);
				if (set[XHI]) G->data[ieo2 + jmx] = G->data[iei1 + jmx] + (gmt_grdfloat)(5.0 * (G->data[ieo1 + jmx] - G->data[ie + jmx]))
					+ (G->data[ie + jmx - mx] - G->data[ieo1 + jmx - mx]) + (G->data[ie + jmx + mx] - G->data[ieo1 + jmx + mx]);
			}
			/* DONE with X not periodic, Y not periodic case.  Loaded all but three corner-most points at each corner.  */

			for (i = n_set = 0; i < 4; i++) if (set[i]) {
				n_set++;
				HH->BC[i] = GMT_BC_IS_NATURAL;
			}
			if (n_set == 4) {
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmt_grd_BC_set: Set boundary condition for all edges: %s\n", kind[HH->BC[XLO]]);
			}
			for (i = 0; i < 4; i++) if (set[i]) {
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmt_grd_BC_set: Set boundary condition for %s edge: %s\n", edge[i], kind[HH->BC[i]]);
			}
			return (GMT_NOERROR);
		}
		/* DONE with all X not periodic cases  */
	}
	else {	/* X is periodic.  Load x cols first, then do Y cases.  */
		bool check_repeat = (G->header->registration == GMT_GRID_NODE_REG && HH->grdtype == GMT_GRID_GEOGRAPHIC_EXACT360_REPEAT);
		if (set[XLO]) HH->BC[XLO] = GMT_BC_IS_PERIODIC;
		if (set[XHI]) HH->BC[XHI] = GMT_BC_IS_PERIODIC;
		for (jmx = jn, bok = 0; jmx <= js; jmx += mx) {
			if (check_repeat && !doubleAlmostEqualZero (G->data[jmx+iw], G->data[jmx+ie]))
				++bok;
			if (set[XLO]) {
				G->data[iwo1 + jmx] = G->data[iwo1k + jmx];
				G->data[iwo2 + jmx] = G->data[iwo2k + jmx];
			}
			if (set[XHI]) {
				G->data[ieo1 + jmx] = G->data[ieo1k + jmx];
				G->data[ieo2 + jmx] = G->data[ieo2k + jmx];
			}
		}
		if (bok > 0) GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmt_grd_BC_set: %d (of %d) inconsistent grid values at West and East boundaries for repeated nodes.\n", bok, G->header->n_rows);

		if (HH->nyp > 0) {	/* Y is periodic.  copy all, including boundary cols:  */
			for (i = iwo2, bok = 0; i <= ieo2; ++i) {
				if (G->header->registration == GMT_GRID_NODE_REG && !doubleAlmostEqualZero (G->data[jn+i], G->data[js+i]))
					++bok;
				if (set[YHI]) {
					G->data[jno1 + i] = G->data[jno1k + i];
					G->data[jno2 + i] = G->data[jno2k + i];
				}
				if (set[YLO]) {
					G->data[jso1 + i] = G->data[jso1k + i];
					G->data[jso2 + i] = G->data[jso2k + i];
				}
			}
			if (bok > 0) GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmt_grd_BC_set: %d (of %d) inconsistent grid values at South and North boundaries for repeated nodes.\n", bok, G->header->n_columns);
			/* DONE with X and Y both periodic.  Fully loaded.  */

			if (set[YLO] && set[YHI]) {
				HH->BC[YLO] = HH->BC[YHI] = GMT_BC_IS_PERIODIC;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmt_grd_BC_set: Set boundary condition for bottom and top edges: %s\n", kind[HH->BC[YLO]]);
			}
			else if (set[YLO]) {
				HH->BC[YLO] = GMT_BC_IS_PERIODIC;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmt_grd_BC_set: Set boundary condition for %s edge: %s\n", edge[YLO], kind[HH->BC[YLO]]);
			}
			else if (set[YHI]) {
				HH->BC[YHI] = GMT_BC_IS_PERIODIC;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmt_grd_BC_set: Set boundary condition for %s edge: %s\n", edge[YHI], kind[HH->BC[YHI]]);
			}
			return (GMT_NOERROR);
		}

		/* Do north (top) boundary:  */

		if (HH->gn) {	/* Y is at north pole.  Phase-shift all, incl. bndry cols. */
			if (G->header->registration == GMT_GRID_PIXEL_REG) {
				j1p = jn;	/* constraint for jno1  */
				j2p = jni1;	/* constraint for jno2  */
			}
			else {
				j1p = jni1;		/* constraint for jno1  */
				j2p = jni1 + mx;	/* constraint for jno2  */
			}
			for (i = iwo2; set[YHI] && i <= ieo2; i++) {
				i180 = G->header->pad[XLO] + ((i + nxp2)%HH->nxp);
				G->data[jno1 + i] = G->data[j1p + i180];
				G->data[jno2 + i] = G->data[j2p + i180];
			}
			if (set[YHI]) {
				HH->BC[YHI] = GMT_BC_IS_GEO;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmt_grd_BC_set: Set boundary condition for %s edge: %s\n", edge[YHI], kind[HH->BC[YHI]]);
			}
		}
		else {
			/* Y needs natural conditions.  x bndry cols periodic.
				First do Laplacian.  Start/end loop 1 col outside,
				then use periodicity to set 2nd col outside.  */

			for (i = iwo1; set[YHI] && i <= ieo1; i++) {
				G->data[jno1 + i] = (gmt_grdfloat)(4.0 * G->data[jn + i]) - (G->data[jn + i - 1] + G->data[jn + i + 1] + G->data[jni1 + i]);
			}
			if (set[XLO] && set[YHI]) G->data[jno1 + iwo2] = G->data[jno1 + iwo2 + HH->nxp];
			if (set[XHI] && set[YHI]) G->data[jno1 + ieo2] = G->data[jno1 + ieo2 - HH->nxp];


			/* Now set d[Laplacian]/dn = 0, start/end loop 1 col out,
				use periodicity to set 2nd out col after loop.  */

			for (i = iwo1; set[YHI] && i <= ieo1; i++) {
				G->data[jno2 + i] = G->data[jni1 + i] + (gmt_grdfloat)(5.0 * (G->data[jno1 + i] - G->data[jn + i]))
					+ (G->data[jn + i - 1] - G->data[jno1 + i - 1]) + (G->data[jn + i + 1] - G->data[jno1 + i + 1]);
			}
			if (set[XLO] && set[YHI]) G->data[jno2 + iwo2] = G->data[jno2 + iwo2 + HH->nxp];
			if (set[XHI] && set[YHI]) G->data[jno2 + ieo2] = G->data[jno2 + ieo2 - HH->nxp];

			/* End of X is periodic, north (top) is Natural.  */
			if (set[YHI]) {
				HH->BC[YHI] = GMT_BC_IS_NATURAL;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmt_grd_BC_set: Set boundary condition for %s edge: %s\n", edge[YHI], kind[HH->BC[YHI]]);
			}
		}

		/* Done with north (top) BC in X is periodic case.  Do south (bottom)  */

		if (HH->gs) {	/* Y is at south pole.  Phase-shift all, incl. bndry cols. */
			if (G->header->registration == GMT_GRID_PIXEL_REG) {
				j1p = js;	/* constraint for jso1  */
				j2p = jsi1;	/* constraint for jso2  */
			}
			else {
				j1p = jsi1;		/* constraint for jso1  */
				j2p = jsi1 - mx;	/* constraint for jso2  */
			}
			for (i = iwo2; set[YLO] && i <= ieo2; i++) {
				i180 = G->header->pad[XLO] + ((i + nxp2)%HH->nxp);
				G->data[jso1 + i] = G->data[j1p + i180];
				G->data[jso2 + i] = G->data[j2p + i180];
			}
			if (set[YLO]) {
				HH->BC[YLO] = GMT_BC_IS_GEO;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmt_grd_BC_set: Set boundary condition for %s edge: %s\n", edge[YLO], kind[HH->BC[YLO]]);
			}
		}
		else {
			/* Y needs natural conditions.  x bndry cols periodic.
				First do Laplacian.  Start/end loop 1 col outside,
				then use periodicity to set 2nd col outside.  */

			for (i = iwo1; set[YLO] && i <= ieo1; i++) {
				G->data[jso1 + i] = (gmt_grdfloat)(4.0 * G->data[js + i]) - (G->data[js + i - 1] + G->data[js + i + 1] + G->data[jsi1 + i]);
			}
			if (set[XLO] && set[YLO]) G->data[jso1 + iwo2] = G->data[jso1 + iwo2 + HH->nxp];
			if (set[XHI] && set[YHI]) G->data[jso1 + ieo2] = G->data[jso1 + ieo2 - HH->nxp];


			/* Now set d[Laplacian]/dn = 0, start/end loop 1 col out,
				use periodicity to set 2nd out col after loop.  */

			for (i = iwo1; set[YLO] && i <= ieo1; i++) {
				G->data[jso2 + i] = G->data[jsi1 + i] + (gmt_grdfloat)(5.0 * (G->data[jso1 + i] - G->data[js + i]))
					+ (G->data[js + i - 1] - G->data[jso1 + i - 1]) + (G->data[js + i + 1] - G->data[jso1 + i + 1]);
			}
			if (set[XLO] && set[YLO]) G->data[jso2 + iwo2] = G->data[jso2 + iwo2 + HH->nxp];
			if (set[XHI] && set[YHI]) G->data[jso2 + ieo2] = G->data[jso2 + ieo2 - HH->nxp];

			/* End of X is periodic, south (bottom) is Natural.  */
			if (set[YLO]) {
				HH->BC[YLO] = GMT_BC_IS_NATURAL;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmt_grd_BC_set: Set boundary condition for %s edge: %s\n", edge[YLO], kind[HH->BC[YLO]]);
			}
		}

		/* Done with X is periodic cases.  */

		return (GMT_NOERROR);
	}
}

/* Clipper to ensure a byte stays in 0-255 range */
#if 1
GMT_LOCAL inline unsigned char gmtsupport_clip_to_byte (int byte) { if (byte < 0) return (0); else if (byte > 255) return (255); else return ((unsigned char)byte);}
#else
/* For debugging BC actions for images when the result is outside byte range  */
GMT_LOCAL unsigned char gmtsupport_clip_to_byte (int byte) {
	if (byte < 0) {
		fprintf (stderr, "byte = %d\n", byte);
		return (0);
	}
	if (byte > 255) {
		fprintf (stderr, "byte = %d\n", byte);
		return (255);
	}
	return ((unsigned char)byte);
}
#endif

/*! . */
int gmtlib_image_BC_set (struct GMT_CTRL *GMT, struct GMT_IMAGE *I) {
	/* Set two rows of padding (pad[] can be larger) around data according
	   to desired boundary condition info in edgeinfo.
	   Returns -1 on problem, 0 on success.
	   If either x or y is periodic, the padding is entirely set.
	   However, if neither is true (this rules out geographical also)
	   then all but three corner-most points in each corner are set.

	   As written, not ready to use with "surface" for GMT v4, because
	   assumes left/right is +/- 1 and down/up is +/- mx.  In "surface"
	   the amount to move depends on the current mesh size, a parameter
	   not used here.

	   This is the revised, two-rows version (WHFS 6 May 1998).
	   Based on GMT_boundcont_set but extended to multiple bands and using char * array
	*/

	int byte;
	uint64_t mx;		/* Width of padded array; width as malloc'ed  */
	uint64_t mxnyp;		/* distance to periodic constraint in j direction  */
	uint64_t i, jmx;	/* Current i, j * mx  */
	uint64_t nxp2;		/* 1/2 the xg period (180 degrees) in cells  */
	uint64_t i180;		/* index to 180 degree phase shift  */
	uint64_t iw, iwo1, iwo2, iwi1, ie, ieo1, ieo2, iei1;  /* see below  */
	uint64_t jn, jno1, jno2, jni1, js, jso1, jso2, jsi1;  /* see below  */
	uint64_t jno1k, jno2k, jso1k, jso2k, iwo1k, iwo2k, ieo1k, ieo2k;
	uint64_t j1p, j2p;	/* j_o1 and j_o2 pole constraint rows  */
	unsigned int n_skip, n_set;
	unsigned int b, nb = I->header->n_bands;
	unsigned int bok;		/* bok used to test that things are OK  */
	bool set[4] = {true, true, true, true};
	char *kind[5] = {"not set", "natural", "periodic", "geographic", "extended data"};
	char *edge[4] = {"left  ", "right ", "bottom", "top   "};
	unsigned char *img = NULL;
	struct GMT_GRID_HEADER_HIDDEN *HH = gmt_get_H_hidden (I->header);

	if (I->header->complex_mode & GMT_GRID_IS_COMPLEX_MASK) return (GMT_NOERROR);	/* Only set up for real arrays */

	for (i = n_skip = 0; i < 4; i++) {
		if (HH->BC[i] == GMT_BC_IS_DATA) {set[i] = false; n_skip++;}	/* No need to set since there is data in the pad area */
	}
	if (n_skip == 4) return (GMT_NOERROR);	/* No need to set anything since there is data in the pad area on all sides */
	if (I->data == NULL) return (GMT_NOERROR);	/* Premature call; no image data yet */

	/* Check minimum size:  */
	if (I->header->n_columns < 1 || I->header->n_rows < 1) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "gmtlib_image_BC_set: Requires n_columns,n_rows at least 1.\n");
		return (-1);
	}

	/* Check if pad is requested */
	if (I->header->pad[0] < 2 ||  I->header->pad[1] < 2 ||  I->header->pad[2] < 2 ||  I->header->pad[3] < 2) {
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "gmtlib_image_BC_set: Pad not large enough for BC assignments; no BCs applied\n");
		return (GMT_NOERROR);
	}

	/* Initialize stuff:  */

	img = I->data;	/* Just a shorthand to keep expressions shorter */
	mx = I->header->mx;
	nxp2 = HH->nxp / 2;	/* Used for 180 phase shift at poles  */

	iw = I->header->pad[XLO];	/* i for west-most data column */
	iwo1 = iw - 1;		/* 1st column outside west  */
	iwo2 = iwo1 - 1;	/* 2nd column outside west  */
	iwi1 = iw + 1;		/* 1st column  inside west  */

	ie = I->header->pad[XLO] + I->header->n_columns - 1;	/* i for east-most data column */
	ieo1 = ie + 1;		/* 1st column outside east  */
	ieo2 = ieo1 + 1;	/* 2nd column outside east  */
	iei1 = ie - 1;		/* 1st column  inside east  */

	jn = mx * I->header->pad[YHI];	/* j*mx for north-most data row  */
	jno1 = jn - mx;		/* 1st row outside north  */
	jno2 = jno1 - mx;	/* 2nd row outside north  */
	jni1 = jn + mx;		/* 1st row  inside north  */

	js = mx * (I->header->pad[YHI] + I->header->n_rows - 1);	/* j*mx for south-most data row  */
	jso1 = js + mx;		/* 1st row outside south  */
	jso2 = jso1 + mx;	/* 2nd row outside south  */
	jsi1 = js - mx;		/* 1st row  inside south  */

	mxnyp = mx * HH->nyp;

	jno1k = jno1 + mxnyp;	/* data rows periodic to boundary rows  */
	jno2k = jno2 + mxnyp;
	jso1k = jso1 - mxnyp;
	jso2k = jso2 - mxnyp;

	iwo1k = iwo1 + HH->nxp;	/* data cols periodic to bndry cols  */
	iwo2k = iwo2 + HH->nxp;
	ieo1k = ieo1 - HH->nxp;
	ieo2k = ieo2 - HH->nxp;

	/* Duplicate rows and columns if n_columns or n_rows equals 1 */

	if (I->header->n_columns == 1) for (i = jn+iw; i <= js+iw; i += mx) img[i-1] = img[i+1] = img[i];
	if (I->header->n_rows == 1) for (i = jn+iw; i <= jn+ie; i++) img[i-mx] = img[i+mx] = img[i];

	/* Check poles for grid case.  It would be nice to have done this
		in GMT_boundcond_param_prep() but at that point the data
		array isn't passed into that routine, and may not have been
		read yet.  Also, as coded here, this bombs with error if
		the pole data is wrong.  But there could be an option to
		to change the condition to Natural in that case, with warning.  */

	if (I->header->registration == GMT_GRID_NODE_REG) {	/* A pole can only be a grid node with gridline registration */
		if (HH->gn) {	/* North pole case */
			bok = 0;
			for (i = iw+1; i <= ie; i++) for (b = 0; b < nb; b++) if (img[nb*(jn + i)+b] != img[nb*(jn + iw)+b]) bok++;
			if (bok > 0) GMT_Report (GMT->parent, GMT_MSG_WARNING, "gmtlib_image_BC_set: Inconsistent image values at North pole.\n");
		}
		if (HH->gs) {	/* South pole case */
			bok = 0;
			for (i = iw+1; i <= ie; i++) for (b = 0; b < nb; b++) if (img[nb*(js + i)+b] != img[nb*(js + iw)+b]) bok++;
			if (bok > 0) GMT_Report (GMT->parent, GMT_MSG_WARNING, "gmtlib_image_BC_set: Inconsistent grid values at South pole.\n");
		}
	}

	/* Start with the case that x is not periodic, because in that case we also know that y cannot be polar.  */

	if (HH->nxp <= 0) {	/* x is not periodic  */

		if (HH->nyp > 0) {	/* y is periodic  */

			for (i = iw; i <= ie; i++) {
				for (b = 0; b < nb; b++) {
					if (set[YHI]) {
						img[nb*(jno1 + i)+b] = img[nb*(jno1k + i)+b];
						img[nb*(jno2 + i)+b] = img[nb*(jno2k + i)+b];
					}
					if (set[YLO]) {
						img[nb*(jso1 + i)+b] = img[nb*(jso1k + i)+b];
						img[nb*(jso2 + i)+b] = img[nb*(jso2k + i)+b];
					}
				}
			}

			/* periodic Y rows copied.  Now do X naturals.
				This is easy since y's are done; no corner problems.
				Begin with Laplacian = 0, and include 1st outside rows
				in loop, since y's already loaded to 2nd outside.  */

			for (jmx = jno1; jmx <= jso1; jmx += mx) {
				for (b = 0; b < nb; b++) {
					if (set[XLO]) {
						byte = irint (4.0 * img[nb*(jmx + iw)+b]) - (img[nb*(jmx + iw + mx)+b] + img[nb*(jmx + iw - mx)+b] + img[nb*(jmx + iwi1)+b]);
						img[nb*(jmx + iwo1)+b] = gmtsupport_clip_to_byte (byte);
					}
					if (set[XHI]) {
						byte = irint (4.0 * img[nb*(jmx + ie)+b]) - (img[nb*(jmx + ie + mx)+b] + img[nb*(jmx + ie - mx)+b] + img[nb*(jmx + iei1)+b]);
						img[nb*(jmx + ieo1)+b] = gmtsupport_clip_to_byte (byte);
					}
				}
			}

			/* Copy that result to 2nd outside row using periodicity.  */
			for (b = 0; b < nb; b++) {
				if (set[XLO]) {
					img[nb*(jno2 + iwo1)+b] = img[nb*(jno2k + iwo1)+b];
					img[nb*(jso2 + iwo1)+b] = img[nb*(jso2k + iwo1)+b];
				}
				if (set[XHI]) {
					img[nb*(jno2 + ieo1)+b] = img[nb*(jno2k + ieo1)+b];
					img[nb*(jso2 + ieo1)+b] = img[nb*(jso2k + ieo1)+b];
				}
			}

			/* Now set d[laplacian]/dx = 0 on 2nd outside column.  Include 1st outside rows in loop.  */
			for (jmx = jno1; jmx <= jso1; jmx += mx) {
				for (b = 0; b < nb; b++) {
					if (set[XLO]) {
						byte = irint ((img[nb*(jmx + iw - mx)+b] + img[nb*(jmx + iw + mx)+b] + img[nb*(jmx + iwi1)+b])
							- (img[nb*(jmx + iwo1 - mx)+b] + img[nb*(jmx + iwo1 + mx)+b]) + (5.0 * (img[nb*(jmx + iwo1)+b] - img[nb*(jmx + iw)+b])));
						img[nb*(jmx + iwo2)+b] = gmtsupport_clip_to_byte (byte);
					}
					if (set[XHI]) {
						byte = irint ((img[nb*(jmx + ie - mx)+b] + img[nb*(jmx + ie + mx)+b] + img[nb*(jmx + iei1)+b])
							- (img[nb*(jmx + ieo1 - mx)+b] + img[nb*(jmx + ieo1 + mx)+b]) + (5.0 * (img[nb*(jmx + ieo1)+b] - img[nb*(jmx + ie)+b])));
						img[nb*(jmx + ieo2)+b] = gmtsupport_clip_to_byte (byte);
					}
				}
			}

			/* Now copy that result also, for complete periodicity's sake  */
			for (b = 0; b < nb; b++) {
				if (set[XLO]) {
					img[nb*(jno2 + iwo2)+b] = img[nb*(jno2k + iwo2)+b];
					img[nb*(jso2 + iwo2)+b] = img[nb*(jso2k + iwo2)+b];
					HH->BC[XLO] = GMT_BC_IS_NATURAL;
				}
				if (set[XHI]) {
					img[nb*(jno2 + ieo2)+b] = img[nb*(jno2k + ieo2)+b];
					img[nb*(jso2 + ieo2)+b] = img[nb*(jso2k + ieo2)+b];
					HH->BC[XHI] = GMT_BC_IS_NATURAL;
				}
			}

			/* DONE with X not periodic, Y periodic case.  Fully loaded.  */
			if (set[YLO] && set[YHI]) {
				HH->BC[YLO] = HH->BC[YHI] = GMT_BC_IS_PERIODIC;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmtlib_image_BC_set: Set boundary condition for bottom and top edge: %s\n", kind[HH->BC[YLO]]);
			}
			else if (set[YLO]) {
				HH->BC[YLO] = GMT_BC_IS_PERIODIC;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmtlib_image_BC_set: Set boundary condition for %s edge: %s\n", edge[YLO], kind[HH->BC[YLO]]);
			}
			else if (set[YHI]) {
				HH->BC[YHI] = GMT_BC_IS_PERIODIC;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmtlib_image_BC_set: Set boundary condition for %s edge: %s\n", edge[YHI], kind[HH->BC[YHI]]);
			}

			return (GMT_NOERROR);
		}
		else {	/* Here begins the X not periodic, Y not periodic case  */

			/* First, set corner points.  Need not merely Laplacian(f) = 0
				but explicitly that d2f/dx2 = 0 and d2f/dy2 = 0.
				Also set d2f/dxdy = 0.  Then can set remaining points.  */

			for (b = 0; b < nb; b++) {
				if (set[XLO]) {	/* d2/dx2 */
					byte = irint (2.0 * img[nb*(jn + iw)+b] - img[nb*(jn + iwi1)+b]);
					img[nb*(jn + iwo1)+b]   = gmtsupport_clip_to_byte (byte);
				}
				if (set[YHI]) {	/* d2/dy2 */
					byte = irint (2.0 * img[nb*(jn + iw)+b] - img[nb*(jni1 + iw)+b]);
					img[nb*(jno1 + iw)+b]   = gmtsupport_clip_to_byte (byte);
				}
				if (set[XLO] && set[YHI]) {	/* d2/dxdy */
					byte = irint (img[nb*(jn + iwo1)+b] + img[nb*(jno1 + iw)+b] - img[nb*(jn + iw)+b]);
					img[nb*(jno1 + iwo1)+b] = gmtsupport_clip_to_byte (byte);
				}
				if (set[XHI]) {	/* d2/dx2 */
					byte = irint (2.0 * img[nb*(jn + ie)+b] - img[nb*(jn + iei1)+b]);
					img[nb*(jn + ieo1)+b]   = gmtsupport_clip_to_byte (byte);
				}
				if (set[YHI]) {	/* d2/dy2 */
					byte = irint (2.0 * img[nb*(jn + ie)+b] - img[nb*(jni1 + ie)+b]);
					img[nb*(jno1 + ie)+b]   = gmtsupport_clip_to_byte (byte);
				}
				if (set[XHI] && set[YHI]) {	/* d2/dxdy */
					byte = irint (img[nb*(jn + ieo1)+b] + img[nb*(jno1 + ie)+b] - img[nb*(jn + ie)+b]);
					img[nb*(jno1 + ieo1)+b] = gmtsupport_clip_to_byte (byte);
				}
				if (set[XLO]) {	/* d2/dx2 */
					byte = irint (2.0 * img[nb*(js + iw)+b] - img[nb*(js + iwi1)+b]);
					img[nb*(js + iwo1)+b]   = gmtsupport_clip_to_byte (byte);
				}
				if (set[YLO]) {	/* d2/dy2 */
					byte = irint (2.0 * img[nb*(js + iw)+b] - img[nb*(jsi1 + iw)+b]);
					img[nb*(jso1 + iw)+b]   = gmtsupport_clip_to_byte (byte);
				}
				if (set[XLO] && set[YLO]) {	/* d2/dxdy */
					byte = irint (img[nb*(js + iwo1)+b] + img[nb*(jso1 + iw)+b]  - img[nb*(js + iw)+b]);
					img[nb*(jso1 + iwo1)+b] = gmtsupport_clip_to_byte (byte);
				}
				if (set[XHI]) {	/* d2/dx2 */
					byte = irint (2.0 * img[nb*(js + ie)+b] - img[nb*(js + iei1)+b]);
					img[nb*(js + ieo1)+b]   = gmtsupport_clip_to_byte (byte);
				}
				if (set[YLO]) {	/* d2/dy2 */
					byte = irint (2.0 * img[nb*(js + ie)+b] - img[nb*(jsi1 + ie)+b]);
					img[nb*(jso1 + ie)+b]   = gmtsupport_clip_to_byte (byte);
				}
				if (set[XHI] && set[YLO]) {	/* d2/dxdy */
					byte = irint (img[nb*(js + ieo1)] + img[nb*(jso1 + ie)] - img[nb*(js + ie)+b]);
					img[nb*(jso1 + ieo1)+b] = gmtsupport_clip_to_byte (byte);
				}
			}

			/* Now set Laplacian = 0 on interior edge points, skipping corners:  */
			for (i = iwi1; i <= iei1; i++) {
				for (b = 0; b < nb; b++) {
					if (set[YHI]) {
						byte = irint (4.0 * img[nb*(jn + i)+b]) - (img[nb*(jn + i - 1)+b] + img[nb*(jn + i + 1)+b] + img[nb*(jni1 + i)+b]);
						img[nb*(jno1 + i)+b] = gmtsupport_clip_to_byte (byte);
					}
					if (set[YLO]) {
						byte = irint (4.0 * img[nb*(js + i)+b]) - (img[nb*(js + i - 1)+b] + img[nb*(js + i + 1)+b] + img[nb*(jsi1 + i)+b]);
						img[nb*(jso1 + i)+b] = gmtsupport_clip_to_byte (byte);
					}
				}
			}
			for (jmx = jni1; jmx <= jsi1; jmx += mx) {
				for (b = 0; b < nb; b++) {
					if (set[XLO]) {
						byte = irint (4.0 * img[nb*(iw + jmx)+b]) - (img[nb*(iw + jmx + mx)+b] + img[nb*(iw + jmx - mx)+b] + img[nb*(iwi1 + jmx)+b]);
						img[nb*(iwo1 + jmx)+b] = gmtsupport_clip_to_byte (byte);
					}
					if (set[XHI]) {
						byte = irint (4.0 * img[nb*(ie + jmx)+b]) - (img[nb*(ie + jmx + mx)+b] + img[nb*(ie + jmx - mx)+b] + img[nb*(iei1 + jmx)+b]);
						img[nb*(ieo1 + jmx)+b] = gmtsupport_clip_to_byte (byte);
					}
				}
			}

			/* Now set d[Laplacian]/dn = 0 on all edge pts, including
				corners, since the points needed in this are now set.  */
			for (i = iw; i <= ie; i++) {
				for (b = 0; b < nb; b++) {
					if (set[YHI]) {
						byte = irint (img[nb*(jni1 + i)+b] + (5.0 * (img[nb*(jno1 + i)+b] - img[nb*(jn + i)+b]))
							+ (img[nb*(jn + i - 1)+b] - img[nb*(jno1 + i - 1)+b]) + (img[nb*(jn + i + 1)+b] - img[nb*(jno1 + i + 1)+b]));
						img[nb*(jno2 + i)+b] = gmtsupport_clip_to_byte (byte);
					}
					if (set[YLO]) {
						byte = irint (img[nb*(jsi1 + i)+b] + (5.0 * (img[nb*(jso1 + i)+b] - img[nb*(js + i)+b]))
							+ (img[nb*(js + i - 1)+b] - img[nb*(jso1 + i - 1)+b]) + (img[nb*(js + i + 1)+b] - img[nb*(jso1 + i + 1)+b]));
						img[nb*(jso2 + i)+b] = gmtsupport_clip_to_byte (byte);
					}
				}
			}
			for (jmx = jn; jmx <= js; jmx += mx) {
				for (b = 0; b < nb; b++) {
					if (set[XLO]) {
						byte = irint (img[nb*(iwi1 + jmx)+b] + (5.0 * (img[nb*(iwo1 + jmx)+b] - img[nb*(iw + jmx)+b]))
							+ (img[nb*(iw + jmx - mx)+b] - img[nb*(iwo1 + jmx - mx)+b]) + (img[nb*(iw + jmx + mx)+b] - img[nb*(iwo1 + jmx + mx)+b]));
						img[nb*(iwo2 + jmx)+b] = gmtsupport_clip_to_byte (byte);
					}
					if (set[XHI]) {
						byte = irint (img[nb*(iei1 + jmx)+b] + (5.0 * (img[nb*(ieo1 + jmx)+b] - img[nb*(ie + jmx)+b]))
							+ (img[nb*(ie + jmx - mx)+b] - img[nb*(ieo1 + jmx - mx)+b]) + (img[nb*(ie + jmx + mx)+b] - img[nb*(ieo1 + jmx + mx)+b]));
						img[nb*(ieo2 + jmx)+b] = gmtsupport_clip_to_byte (byte);
					}
				}
			}
			/* DONE with X not periodic, Y not periodic case.  Loaded all but three cornermost points at each corner.  */

			for (i = n_set = 0; i < 4; i++) if (set[i]) {
				HH->BC[i] = GMT_BC_IS_NATURAL;
				n_set++;
			}
			if (n_set == 4)
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmtlib_image_BC_set: Set boundary condition for all edges: %s\n", kind[HH->BC[XLO]]);
			else {
				for (i = 0; i < 4; i++) if (set[i]) {
					GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmtlib_image_BC_set: Set boundary condition for %s edge: %s\n", edge[i], kind[HH->BC[i]]);
				}
			}
			return (GMT_NOERROR);
		}
		/* DONE with all X not periodic cases  */
	}
	else {	/* X is periodic.  Load x cols first, then do Y cases.  */
		if (set[XLO]) HH->BC[XLO] = GMT_BC_IS_PERIODIC;
		if (set[XHI]) HH->BC[XHI] = GMT_BC_IS_PERIODIC;

		for (jmx = jn; jmx <= js; jmx += mx) {
			for (b = 0; b < nb; b++) {
				if (set[XLO]) {
					img[nb*(iwo1 + jmx)+b] = img[nb*(iwo1k + jmx)+b];
					img[nb*(iwo2 + jmx)+b] = img[nb*(iwo2k + jmx)+b];
				}
				if (set[XHI]) {
					img[nb*(ieo1 + jmx)+b] = img[nb*(ieo1k + jmx)+b];
					img[nb*(ieo2 + jmx)+b] = img[nb*(ieo2k + jmx)+b];
				}
			}
		}

		if (HH->nyp > 0) {	/* Y is periodic.  copy all, including boundary cols:  */
			for (i = iwo2; i <= ieo2; i++) {
				for (b = 0; b < nb; b++) {
					if (set[YHI]) {
						img[nb*(jno1 + i)+b] = img[nb*(jno1k + i)+b];
						img[nb*(jno2 + i)+b] = img[nb*(jno2k + i)+b];
					}
					if (set[YLO]) {
						img[nb*(jso1 + i)+b] = img[nb*(jso1k + i)+b];
						img[nb*(jso2 + i)+b] = img[nb*(jso2k + i)+b];
					}
				}
			}
			/* DONE with X and Y both periodic.  Fully loaded.  */

			if (set[YLO] && set[YHI]) {
				HH->BC[YLO] = HH->BC[YHI] = GMT_BC_IS_PERIODIC;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmtlib_image_BC_set: Set boundary condition for bottom and top edge: %s\n", kind[HH->BC[YLO]]);
			}
			else if (set[YLO]) {
				HH->BC[YLO] = GMT_BC_IS_PERIODIC;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmtlib_image_BC_set: Set boundary condition for %s edge: %s\n", edge[YLO], kind[HH->BC[YLO]]);
			}
			else if (set[YHI]) {
				HH->BC[YHI] = GMT_BC_IS_PERIODIC;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmtlib_image_BC_set: Set boundary condition for %s edge: %s\n", edge[YHI], kind[HH->BC[YHI]]);
			}
			return (GMT_NOERROR);
		}

		/* Do north (top) boundary:  */

		if (HH->gn) {	/* Y is at north pole.  Phase-shift all, incl. bndry cols. */
			if (I->header->registration == GMT_GRID_PIXEL_REG) {
				j1p = jn;	/* constraint for jno1  */
				j2p = jni1;	/* constraint for jno2  */
			}
			else {
				j1p = jni1;		/* constraint for jno1  */
				j2p = jni1 + mx;	/* constraint for jno2  */
			}
			for (i = iwo2; set[YHI] && i <= ieo2; i++) {
				i180 = I->header->pad[XLO] + ((i + nxp2)%HH->nxp);
				for (b = 0; b < nb; b++) {
					img[nb*(jno1 + i)+b] = img[nb*(j1p + i180)+b];
					img[nb*(jno2 + i)+b] = img[nb*(j2p + i180)+b];
				}
			}
			if (set[YHI]) {
				HH->BC[YHI] = GMT_BC_IS_GEO;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmtlib_image_BC_set: Set boundary condition for %s edge: %s\n", edge[YHI], kind[HH->BC[YHI]]);
			}
		}
		else {
			/* Y needs natural conditions.  x bndry cols periodic.
				First do Laplacian.  Start/end loop 1 col outside,
				then use periodicity to set 2nd col outside.  */

			for (i = iwo1; set[YHI] && i <= ieo1; i++) {
				for (b = 0; b < nb; b++) {
					byte = irint ((4.0 * img[nb*(jn + i)+b]) - (img[nb*(jn + i - 1)+b] + img[nb*(jn + i + 1)+b] + img[nb*(jni1 + i)+b]));
					img[nb*(jno1 + i)+b] = gmtsupport_clip_to_byte (byte);
				}
			}
			for (b = 0; b < nb; b++) {
				if (set[XLO] && set[YHI]) img[nb*(jno1 + iwo2)+b] = img[nb*(jno1 + iwo2 + HH->nxp)+b];
				if (set[XHI] && set[YHI]) img[nb*(jno1 + ieo2)+b] = img[nb*(jno1 + ieo2 - HH->nxp)+b];
			}

			/* Now set d[Laplacian]/dn = 0, start/end loop 1 col out,
				use periodicity to set 2nd out col after loop.  */

			for (i = iwo1; set[YHI] && i <= ieo1; i++) {
				for (b = 0; b < nb; b++) {
					byte = irint (img[nb*(jni1 + i)+b] + (5.0 * (img[nb*(jno1 + i)+b] - img[nb*(jn + i)+b]))
						+ (img[nb*(jn + i - 1)+b] - img[nb*(jno1 + i - 1)+b]) + (img[nb*(jn + i + 1)+b] - img[nb*(jno1 + i + 1)+b]));
					img[nb*(jno2 + i)+b] = gmtsupport_clip_to_byte (byte);
				}
			}
			for (b = 0; b < nb; b++) {
				if (set[XLO] && set[YHI]) img[nb*(jno2 + iwo2)+b] = img[nb*(jno2 + iwo2 + HH->nxp)+b];
				if (set[XHI] && set[YHI]) img[nb*(jno2 + ieo2)+b] = img[nb*(jno2 + ieo2 - HH->nxp)+b];
			}

			/* End of X is periodic, north (top) is Natural.  */
			if (set[YHI]) {
				HH->BC[YHI] = GMT_BC_IS_NATURAL;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmtlib_image_BC_set: Set boundary condition for %s edge: %s\n", edge[YHI], kind[HH->BC[YHI]]);
			}
		}

		/* Done with north (top) BC in X is periodic case.  Do south (bottom)  */

		if (HH->gs) {	/* Y is at south pole.  Phase-shift all, incl. bndry cols. */
			if (I->header->registration == GMT_GRID_PIXEL_REG) {
				j1p = js;	/* constraint for jso1  */
				j2p = jsi1;	/* constraint for jso2  */
			}
			else {
				j1p = jsi1;		/* constraint for jso1  */
				j2p = jsi1 - mx;	/* constraint for jso2  */
			}
			for (i = iwo2; set[YLO] && i <= ieo2; i++) {
				i180 = I->header->pad[XLO] + ((i + nxp2)%HH->nxp);
				for (b = 0; b < nb; b++) {
					img[nb*(jso1 + i)+b] = img[nb*(j1p + i180)+b];
					img[nb*(jso2 + i)+b] = img[nb*(j2p + i180)+b];
				}
			}
			if (set[YLO]) {
				HH->BC[YLO] = GMT_BC_IS_GEO;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmtlib_image_BC_set: Set boundary condition for %s edge: %s\n", edge[YLO], kind[HH->BC[YLO]]);
			}
		}
		else {
			/* Y needs natural conditions.  x bndry cols periodic.
				First do Laplacian.  Start/end loop 1 col outside,
				then use periodicity to set 2nd col outside.  */

			for (i = iwo1; set[YLO] && i <= ieo1; i++) {
				for (b = 0; b < nb; b++) {
					byte = irint ((4.0 * img[nb*(js + i)+b]) - (img[nb*(js + i - 1)+b] + img[nb*(js + i + 1)+b] + img[nb*(jsi1 + i)+b]));
					img[nb*(jso1 + i)+b] = gmtsupport_clip_to_byte (byte);
				}
			}
			for (b = 0; b < nb; b++) {
				if (set[XLO] && set[YLO]) img[nb*(jso1 + iwo2)+b] = img[nb*(jso1 + iwo2 + HH->nxp)+b];
				if (set[XHI] && set[YHI]) img[nb*(jso1 + ieo2)+b] = img[nb*(jso1 + ieo2 - HH->nxp)+b];
			}


			/* Now set d[Laplacian]/dn = 0, start/end loop 1 col out,
				use periodicity to set 2nd out col after loop.  */

			for (i = iwo1; set[YLO] && i <= ieo1; i++) {
				for (b = 0; b < nb; b++) {
					byte = irint (img[nb*(jsi1 + i)+b] + (5.0 * (img[nb*(jso1 + i)+b] - img[nb*(js + i)+b]))
						+ (img[nb*(js + i - 1)+b] - img[nb*(jso1 + i - 1)+b]) + (img[nb*(js + i + 1)+b] - img[nb*(jso1 + i + 1)+b]));
					img[nb*(jso2 + i)+b] = gmtsupport_clip_to_byte (byte);
				}
			}
			for (b = 0; b < nb; b++) {
				if (set[XLO] && set[YLO]) img[nb*(jso2 + iwo2)+b] = img[nb*(jso2 + iwo2 + HH->nxp)+b];
				if (set[XHI] && set[YHI]) img[nb*(jso2 + ieo2)+b] = img[nb*(jso2 + ieo2 - HH->nxp)+b];
			}

			/* End of X is periodic, south (bottom) is Natural.  */
			if (set[YLO]) {
				HH->BC[YLO] = GMT_BC_IS_NATURAL;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "gmtlib_image_BC_set: Set boundary condition for %s edge: %s\n", edge[YLO], kind[HH->BC[YLO]]);
			}
		}

		/* Done with X is periodic cases.  */

		return (GMT_NOERROR);
	}
}

int gmt_cube_BC_set (struct GMT_CTRL *GMT, struct GMT_CUBE *U, unsigned int direction) {
	int error = GMT_NOERROR;
	unsigned int k;
	struct GMT_GRID *G = gmt_create_grid (GMT);	/* Create a dummy temporary grid structure */

	gmt_copy_gridheader (GMT, G->header, U->header);

	for (k = 0; k < U->header->n_bands; k++) {	/* Do each layer BC separately */
		G->data = &(U->data[k*U->header->size]);	/* Start of next 2-D layer */
		if (gmt_M_err_pass (GMT, gmt_grd_BC_set (GMT, G, direction), "Cube memory")) {	/* Set boundary conditions */
			error = GMT_GRID_BC_ERROR;
			goto cube_clean_up;
		}
	}

cube_clean_up:
	G->data = NULL;
	gmt_free_grid (GMT, &G, true);

	return (error);
}

/*! . */
bool gmt_y_out_of_bounds (struct GMT_CTRL *GMT, int *j, struct GMT_GRID_HEADER *h, bool *wrap_180) {
	/* Adjusts the j (y-index) value if we are dealing with some sort of periodic boundary
	* condition.  If a north or south pole condition we must "go over the pole" and access
	* the longitude 180 degrees away - this is achieved by passing the wrap_180 flag; the
	* shifting of longitude is then deferred to gmt_x_out_of_bounds.
	* If no periodicities are present then nothing happens here.  If we end up being
	* out of bounds we return true (and main program can take action like continue);
	* otherwise we return false.
	* Note: *j may be negative on input.
	*/
	struct GMT_GRID_HEADER_HIDDEN *HH = gmt_get_H_hidden (h);

	gmt_M_unused(GMT);
	if ((*j) < 0) {	/* Depending on BC's we wrap around or we are above the top of the domain */
		if (HH->gn) {	/* N Polar condition - adjust j and set wrap flag */
			(*j) = abs (*j) - h->registration;
			(*wrap_180) = true;	/* Go "over the pole" */
		}
		else if (HH->nyp) {	/* Periodic in y */
			(*j) += HH->nyp;
			(*wrap_180) = false;
		}
		else
			return (true);	/* We are outside the range */
	}
	else if ((*j) >= (int)h->n_rows) {	/* Depending on BC's we wrap around or we are below the bottom of the domain */
		if (HH->gs) {	/* S Polar condition - adjust j and set wrap flag */
			(*j) += h->registration - 2;
			(*wrap_180) = true;	/* Go "over the pole" */
		}
		else if (HH->nyp) {	/* Periodic in y */
			(*j) -= HH->nyp;
			(*wrap_180) = false;
		}
		else
			return (true);	/* We are outside the range */
	}
	else
		(*wrap_180) = false;

	return (false);	/* OK, we are inside grid now for sure */
}

/*! . */
bool gmt_x_out_of_bounds (struct GMT_CTRL *GMT, int *i, struct GMT_GRID_HEADER *h, bool wrap_180) {
	/* Adjusts the i (x-index) value if we are dealing with some sort of periodic boundary
	* condition.  If a north or south pole condition we must "go over the pole" and access
	* the longitude 180 degrees away - this is achieved by examining the wrap_180 flag and take action.
	* If no periodicities are present and we end up being out of bounds we return true (and
	* main program can take action like continue); otherwise we return false.
	* Note: *i may be negative on input.
	*/
	struct GMT_GRID_HEADER_HIDDEN *HH = gmt_get_H_hidden (h);

	/* Depending on BC's we wrap around or leave as is. */

	gmt_M_unused(GMT);
	if ((*i) < 0) {	/* Potentially outside to the left of the domain */
		if (HH->nxp)	/* Periodic in x - always inside grid */
			(*i) += HH->nxp;
		else	/* Sorry, you're outside */
			return (true);
	}
	else if ((*i) >= (int)h->n_columns) {	/* Potentially outside to the right of the domain */
		if (HH->nxp)	/* Periodic in x -always inside grid */
			(*i) -= HH->nxp;
		else	/* Sorry, you're outside */
			return (true);
	}

	if (wrap_180) (*i) = ((*i) + (HH->nxp / 2)) % HH->nxp;	/* Must move 180 degrees */

	return (false);	/* OK, we are inside grid now for sure */
}

/*! . */
bool gmt_row_col_out_of_bounds (struct GMT_CTRL *GMT, double *in, struct GMT_GRID_HEADER *h, openmp_int *row, openmp_int *col) {
	/* Return false and pass back unsigned row,col if inside region, or return true (outside) */
	int signed_row, signed_col;
	gmt_M_unused(GMT);
	signed_row = (int)gmt_M_grd_y_to_row (GMT, in[GMT_Y], h);
	if (signed_row < 0) return (true);
	signed_col = (int)gmt_M_grd_x_to_col (GMT, in[GMT_X], h);
	if (signed_col < 0) return (true);
	*row = (openmp_int)signed_row;
	if (*row >= (openmp_int)h->n_rows) return (true);
	*col = (openmp_int)signed_col;
	if (*col >= (openmp_int)h->n_columns) return (true);
	return (false);	/* Inside the node region */
}

/*! . */
void gmt_set_xy_domain (struct GMT_CTRL *GMT, double wesn_extended[], struct GMT_GRID_HEADER *h) {
	double off;
	/* Sets the domain boundaries to be used to determine if x,y coordinates
	 * are outside the domain of a grid.  If gridline-registered then the
	 * domain is extended by 0.5 the grid interval.  Note that points with
	 * x == x_max and y == y_max are considered inside.
	 */

	off = 0.5 * (1 - h->registration);
	if (gmt_M_x_is_lon (GMT, GMT_IN) && gmt_grd_is_global (GMT, h))	/* Global longitude range */
		wesn_extended[XLO] = h->wesn[XLO], wesn_extended[XHI] = h->wesn[XHI];
	else
		wesn_extended[XLO] = h->wesn[XLO] - off * h->inc[GMT_X], wesn_extended[XHI] = h->wesn[XHI] + off * h->inc[GMT_X];
	/* Latitudes can be extended provided we are not at the poles */
	wesn_extended[YLO] = h->wesn[YLO] - off * h->inc[GMT_Y], wesn_extended[YHI] = h->wesn[YHI] + off * h->inc[GMT_Y];
	if (gmt_M_y_is_lat (GMT, GMT_IN)) {
		if (wesn_extended[YLO] < -90.0) wesn_extended[YLO] = -90.0;
		if (wesn_extended[YHI] > +90.0) wesn_extended[YHI] = +90.0;
	}
}

/*! . */
bool gmt_x_is_outside (struct GMT_CTRL *GMT, double *x, double left, double right) {
	/* Determines if this x is inside the effective x-domain.  This is normally
	 * west to east, but when gridding is concerned it can be extended by +-0.5 * dx
	 * for gridline-registered grids.  Also, if x is longitude we must check for
	 * wrap-arounds by 360 degrees, and x may be modified accordingly.
	 */
	if (gmt_M_is_dnan (*x)) return (true);
	if (gmt_M_x_is_lon (GMT, GMT_IN)) {	/* Periodic longitude test */
		while ((*x) > left) (*x) -= 360.0;	/* Make sure we start west or west */
		while ((*x) < left) (*x) += 360.0;	/* See if we are outside east */
		return (((*x) > right) ? true : false);
	}
	else	/* Cartesian test */
		return (((*x) < left || (*x) > right) ? true : false);
}

/*! . */
int gmt_getinset (struct GMT_CTRL *GMT, char option, char *in_text, struct GMT_MAP_INSET *B) {
	/* Parse the map inset option, which comes in two flavors:
	 * 1) -D<xmin/xmax/ymin/ymax>[+r][+s<file>][+u<unit>]
	 * 2) -Dg|j|J|n|x<refpoint>+w<width>[<u>][/<height>[<u>]][+j<justify>][+o<dx>[/<dy>]][+s<file>]
	 *    Note: the [+s<file>] is only valid in classic mode (via psbasemap)
	 *
	 * For backwards compatibility we also check the deprecated form of (1):
	 *    [<unit>]<xmin/xmax/ymin/ymax>
	 */
	unsigned int col_type[2], k = 0, error = 0;
	int n;
	char txt_a[GMT_LEN256] = {""}, txt_b[GMT_LEN256] = {""}, txt_c[GMT_LEN256] = {""}, txt_d[GMT_LEN256] = {""};
	char string[GMT_BUFSIZ] = {""}, text[GMT_BUFSIZ] = {""}, oldshit[GMT_LEN128] = {""};
	struct GMT_MAP_PANEL *save_panel = B->panel;	/* In case it was set and we wipe it below with gmt_M_memset */

	if (!in_text || in_text[0] == '\0') {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: No argument given\n", option);
		return GMT_PARSE_ERROR;
	}
	gmt_M_memset (B, 1, struct GMT_MAP_INSET);
	B->panel = save_panel;	/* In case it is not NULL */

	if (gmtsupport_ensure_new_mapinset_syntax (GMT, option, in_text, text, oldshit)) return (1);	/* This recasts any old syntax using new syntax and gives a warning */

	/* Determine if we got an reference point or a region */

	if (strchr (GMT_REFPOINT_CODES, text[0])) {	/* Did the reference point thing. */
		/* Syntax is -Dg|j|J|n|x<refpoint>+w<width>[/<height>][+j<justify>][+o<dx>[/<dy>]][+s<file>], with +s<file> only in classic mode */
		unsigned int last;
		char *q[2] = {NULL, NULL};
		size_t len;
		if ((B->refpoint = gmt_get_refpoint (GMT, text, option)) == NULL) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Map inset reference point was not accepted\n", option);
			gmt_refpoint_syntax (GMT, "D", NULL, GMT_ANCHOR_INSET, 1);
			return (1);	/* Failed basic parsing */
		}

		if (gmt_validate_modifiers (GMT, B->refpoint->args, option, "jostw", GMT_MSG_ERROR)) return (1);

		/* Reference point args are +w<width>[/<height>][+j<justify>][+o<dx>[/<dy>]][+s<file>][+t]. */
		/* Required modifier +w */
		if (gmt_get_modifier (B->refpoint->args, 'w', string)) {
			if (string[0] == '\0') {	/* Got nutin' */
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  No dimensions given to +w modifier\n", option);
				error++;
			}
			else {	/* Gave some arguments */
				n = sscanf (string, "%[^/]/%s", txt_a, txt_b);
				/* First deal with inset dimensions and horizontal vs vertical */
				/* Handle either <unit><width>/<height> or <width>/<height> */
				q[GMT_X] = txt_a;	q[GMT_Y] = txt_b;
				last = (n == 1) ? GMT_X : GMT_Y;
				for (k = GMT_X; k <= last; k++) {
					len = strlen (q[k]) - 1;
					if (strchr (GMT_LEN_UNITS2, q[k][len])) {	/* Got dimensions in these units */
						B->unit = q[k][len];
						q[k][len] = 0;
					}
					B->dim[k] = (B->unit) ? atof (q[k]) : gmt_M_to_inch (GMT, q[k]);
				}
				if (last == GMT_X) B->dim[GMT_Y] = B->dim[GMT_X];
			}
		}
		/* Optional modifiers +j, +o, +s */
		if (gmt_get_modifier (B->refpoint->args, 'j', string))	{	/* Got justification of item w.r.t. reference point */
			if (string[0] == '\0') {	/* Got nutin' */
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  No justification argument given to +j modifier\n", option);
				error++;
			}
			else
				B->justify = gmt_just_decode (GMT, string, PSL_BL);
		}
		else	/* With -Dj or -DJ, set default to reference justify point, else BL */
			B->justify = gmt_M_just_default (GMT, B->refpoint, PSL_BL);
		if (gmt_get_modifier (B->refpoint->args, 'o', string)) {	/* Got offsets from reference point */
			if ((n = gmt_get_pair (GMT, string, GMT_PAIR_DIM_DUP, B->off)) < 0) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Failed to parse offset arguments for +o modifier\n", option);
				error++;
			}
		}
		if (gmt_get_modifier (B->refpoint->args, 's', string)) {
			if (GMT->current.setting.run_mode == GMT_MODERN) {	/* Not valid in modern node */
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  +s modifier is valid in classic mode only\n", option);
				error++;
			}
			else if (string[0] == '\0') {	/* Got nutin' */
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  No filename given to +s modifier\n", option);
				error++;
			}
			else
				B->file = strdup (string);
		}
		if (gmt_get_modifier (B->refpoint->args, 't', string))
				B->translate = true;
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Map inset attributes: justify = %d, dx = %g dy = %g\n", B->justify, B->off[GMT_X], B->off[GMT_Y]);
	}
	else {	/* Did the [<unit>]<xmin/xmax/ymin/ymax> thing - this is exact so justify, offsets do not apply. */
		char *c = NULL, p[GMT_LEN128] = {""};
		unsigned int pos;
		/* Syntax is -D<xmin/xmax/ymin/ymax>[+s<file>][+t][+u<unit>] or old -D[<unit>]<xmin/xmax/ymin/ymax>[+s<file>][+t] */
		if ((c = gmt_first_modifier (GMT, text, "rsu"))) {
			/* Syntax is -D<xmin/xmax/ymin/ymax>[+r][+s<file>][+t][+u<unit>] */
			pos = 0;	/* Reset to start of new word */
			while (gmt_getmodopt (GMT, option, c, "rstu", &pos, p, &error) && error == 0) {
				switch (p[0]) {
					case 'r': B->oblique = true;	break;
					case 's':
						if (GMT->current.setting.run_mode == GMT_MODERN) {	/* Not valid in modern node */
							GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  +s modifier is valid in classic mode only\n", option);
							error++;
						}
						else
							B->file = strdup (&p[1]);
						break;
					case 't': B->translate = true;	break;
					case 'u': B->unit = p[1]; break;
					default: break;	/* These are caught in gmt_getmodopt so break is just for Coverity */
				}
			}
			c[0] = '\0';	/* Chop off all modifiers so other items can be determined */
		}
		else if (strchr (GMT_LEN_UNITS2, text[0])) {	/* Deprecated args: Got a rectangular region given in these units */
			/* -D<unit>]<xmin/xmax/ymin/ymax> */
			B->unit = text[0];
			k = 1;
		}
		/* Decode the w/e/s/n part */
		if ((n = sscanf (&text[k], "%[^/]/%[^/]/%[^/]/%s", txt_a, txt_b, txt_c, txt_d)) != 4) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Must specify w/e/s/n or <unit>xmin/xmax/ymin/ymax\n", option);
			return (GMT_PARSE_ERROR);
		}
		if (c) c[0] = '+';	/* Restore original argument */
		col_type[GMT_X] = gmt_M_type (GMT, GMT_IN, GMT_X);	/* Set correct input types */
		col_type[GMT_Y] = gmt_M_type (GMT, GMT_IN, GMT_Y);
		if (k == 0) {	/* Got geographic w/e/s/n or <w/s/e/n>r */
			n = (int)strlen(txt_d) - 1;
			if (B->oblique || txt_d[n] == 'r') {	/* Got <w/s/e/n>r for rectangular box */
				if (!B->oblique) txt_d[n] = '\0';
				error += gmt_verify_expectations (GMT, col_type[GMT_X], gmt_scanf (GMT, txt_a, col_type[GMT_X], &B->wesn[XLO]), txt_a);
				error += gmt_verify_expectations (GMT, col_type[GMT_Y], gmt_scanf (GMT, txt_b, col_type[GMT_Y], &B->wesn[YLO]), txt_b);
				error += gmt_verify_expectations (GMT, col_type[GMT_X], gmt_scanf (GMT, txt_c, col_type[GMT_X], &B->wesn[XHI]), txt_c);
				error += gmt_verify_expectations (GMT, col_type[GMT_Y], gmt_scanf (GMT, txt_d, col_type[GMT_Y], &B->wesn[YHI]), txt_d);
				if (!B->oblique) txt_d[n] = 'r';
				B->oblique = true;
			}
			else {	/* Got  w/e/s/n for box that follows meridians and parallels, which may or may not be rectangular */
				error += gmt_verify_expectations (GMT, col_type[GMT_X], gmt_scanf (GMT, txt_a, col_type[GMT_X], &B->wesn[XLO]), txt_a);
				error += gmt_verify_expectations (GMT, col_type[GMT_X], gmt_scanf (GMT, txt_b, col_type[GMT_X], &B->wesn[XHI]), txt_b);
				error += gmt_verify_expectations (GMT, col_type[GMT_Y], gmt_scanf (GMT, txt_c, col_type[GMT_Y], &B->wesn[YLO]), txt_c);
				error += gmt_verify_expectations (GMT, col_type[GMT_Y], gmt_scanf (GMT, txt_d, col_type[GMT_Y], &B->wesn[YHI]), txt_d);
			}
		}
		else {	/* Got projected xmin/xmax/ymin/ymax for rectangular box */
			B->wesn[XLO] = atof (txt_a);	B->wesn[XHI] = atof (txt_b);
			B->wesn[YLO] = atof (txt_c);	B->wesn[YHI] = atof (txt_d);
		}
	}

	B->plot = true;
	if (oldshit[0] && gmt_getpanel (GMT, 'F', oldshit, &(B->panel))) {
		gmt_mappanel_syntax (GMT, 'F', "Specify the rectangular panel attributes for map inset", 3);
		error++;
	}
	return (error);
}

int gmt_getscale (struct GMT_CTRL *GMT, char option, char *text, struct GMT_MAP_SCALE *ms) {
	/* This function parses the -L map scale syntax:
	 *   -L[g|j|J|n|x]<refpoint>+c[/<slon>]/<slat>+w<length>[e|f|M|n|k|u][+a<align>][+f][+j<just>][+l<label>][+u]
	 * If the required +w is not present we call the backwards compatible parsert for the previous map scale syntax.
	 * An optional background panel is handled by a separate option (typically -F). */

	int error = 0, n;
	bool vertical = false;
	char string[GMT_BUFSIZ] = {""};
	struct GMT_MAP_PANEL *save_panel = ms->panel;	/* In case it was set and we wipe it below with gmt_M_memset */

	if (!text || text[0] == '\0') {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: No argument given\n", option);
		return GMT_PARSE_ERROR;
	}
	vertical = ms->vertical;
	if (!strstr (text, "+w")) return gmtsupport_getscale_old (GMT, option, text, ms);	/* Old-style args */

	gmt_M_memset (ms, 1, struct GMT_MAP_SCALE);
	ms->panel = save_panel;	/* In case it is not NULL */
	ms->measure = 'k';	/* Default distance unit is km */
	ms->alignment = (vertical) ? 'r' : 't';	/* Default label placement is on top for map scale and right for vertical scale */

	if ((ms->refpoint = gmt_get_refpoint (GMT, text, option)) == NULL) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Scale reference point was not accepted\n", option);
		gmt_refpoint_syntax (GMT, "L", NULL, GMT_ANCHOR_MAPSCALE, 3);
		return (1);	/* Failed basic parsing */
	}

	/* refpoint->args are now +c[/<slon>]/<slat>+w<length>[e|f|M|n|k|u][+a<align>][+f][+j<just>][+l<label>][+o<dx>[/<dy>]][+u][+v]. */

	if (gmt_validate_modifiers (GMT, ms->refpoint->args, option, "acfjlouwv", GMT_MSG_ERROR)) return (1);

	/* Required modifier is +w */

	if (gmt_M_is_geographic (GMT, GMT_IN)) ms->origin[GMT_X] = ms->origin[GMT_Y] = GMT->session.d_NaN;	/* One or both may need to set after gmt_map_setup is called */
	if (gmt_get_modifier (ms->refpoint->args, 'c', string)) {	/* Specific scale origin */
		ms->origin_mode = GMT_SCALE_ORIGIN_GIVEN;	/* Presumably we are specifying the actual origin lat/lon */
		if (gmt_M_is_cartesian (GMT, GMT_IN))	/* No use */
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Not allowed for Cartesian projections\n", option);
		else if (string[0] == '\0')	/* No argument means pick map center */
			ms->origin_mode = GMT_SCALE_ORIGIN_MIDDLE;
		else if (strchr (string, '/')) {	/* Got both lon and lat for scale */
			if ((n = gmt_get_pair (GMT, string, GMT_PAIR_COORD, ms->origin)) < 2) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Failed to parse scale <longitude>/<latitude> for +c modifier\n", option);
				error++;
			}
			else if (fabs (ms->origin[GMT_X]) > 360.0) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Scale longitude is out of range for +c modifier\n", option);
				error++;
			}
		}
		else {	/* Just got latitude scale */
			if (gmt_verify_expectations (GMT, GMT_IS_LAT, gmt_scanf (GMT, string, GMT_IS_LON, &(ms->origin[GMT_Y])), string)) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Failed to parse scale latitude for +c modifier\n", option);
				error++;
			}
		}
		if (ms->origin_mode == GMT_SCALE_ORIGIN_GIVEN && fabs (ms->origin[GMT_Y]) > 90.0) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Scale latitude is out of range for +c modifier\n", option);
			error++;
		}
	}
	else	/* Pick the same location for scale origin as the placement of the scale */
		ms->origin_mode = GMT_SCALE_ORIGIN_PLACE;

	if (gmt_get_modifier (ms->refpoint->args, 'w', string)) {	/* Get bar length */
		if (string[0] == '\0') {	/* Got nutin' */
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  No length argument given to +w modifier\n", option);
			error++;
		}
		else if (gmt_M_is_geographic (GMT, GMT_IN) && isalpha ((int)string[n = (int)strlen (string) - 1])) {	/* Letter at end of distance value */
			ms->measure = string[n];
			if (gmt_M_compat_check (GMT, 4) && ms->measure == 'm') {
				GMT_Report (GMT->parent, GMT_MSG_COMPAT, "Distance unit m is deprecated; use M for statute miles\n");
				ms->measure = 'M';
			}
			if (strchr (GMT_LEN_UNITS2, ms->measure))	/* Gave a valid distance unit */
				string[n] = '\0';
			else {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Valid distance units are %s\n", option, GMT_LEN_UNITS2_DISPLAY);
				error++;
			}
		}
		ms->length = atof (string);	/* Length as given, no unit scaling here */
		if (ms->length <= 0.0) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Length must be positive\n", option);
			error++;
		}
	}
	else {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Scale length modifier +w<length> is required\n", option);
		error++;
	}
	/* Optional modifiers +a, +f, +j, +l, +o, +u, +v */
	if (gmt_get_modifier (ms->refpoint->args, 'f', NULL)) {	/* Do fancy label */
		if (gmt_M_is_cartesian (GMT, GMT_IN)) {	/* Not allowed' */
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  No fancy map scale modifier allowed for Cartesian projections\n", option);
			error++;
		}
		else
			ms->fancy = true;
	}
	if (gmt_get_modifier (ms->refpoint->args, 'v', NULL)) {	/* Ask for vertical Cartesian scale */
		if (gmt_M_is_geographic (GMT, GMT_IN)) {	/* Not allowed' */
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  No vertical scale modifier allowed for geographic projections\n", option);
			error++;
		}
		else
			ms->vertical = true;
	}
	if (gmt_get_modifier (ms->refpoint->args, 'j', string))	{	/* Got justification of item w.r.t. reference point */
		if (string[0] == '\0') {	/* Got nutin' */
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  No justification argument given to +j modifier\n", option);
			error++;
		}
		else
			ms->justify = gmt_just_decode (GMT, string, PSL_MC);
	}
	else {	/* With -Dj or -DJ, set default to reference (mirrored) justify point, else MC */
		ms->justify = gmt_M_just_default (GMT, ms->refpoint, PSL_MC);
		if (vertical || ms->vertical || gmt_M_is_cartesian (GMT, GMT_IN)) {
			double out_offset = GMT->current.setting.map_label_offset[GMT_Y] + GMT->current.setting.map_frame_width;
			double in_offset  = GMT->current.setting.map_label_offset[GMT_Y];
			switch (ms->refpoint->justify) {        /* Autoset +a, +o when placed centered on a side: Note: +a, +o may overrule this later */
				case PSL_TC:
					ms->off[GMT_Y] = (ms->refpoint->mode == GMT_REFPOINT_JUST_FLIP) ? out_offset : in_offset;
					break;
				case PSL_BC:
					ms->off[GMT_Y] = (ms->refpoint->mode == GMT_REFPOINT_JUST_FLIP) ? out_offset : in_offset;
					break;
				case PSL_ML:
					ms->alignment = 'l';        /* left side */
					ms->off[GMT_X] = (ms->refpoint->mode == GMT_REFPOINT_JUST_FLIP) ? out_offset : in_offset;
					break;
				case PSL_MR:
					ms->off[GMT_X] = (ms->refpoint->mode == GMT_REFPOINT_JUST_FLIP) ? out_offset : in_offset;
					break;
				default:
					break;
			}
		}
	}
	if (gmt_get_modifier (ms->refpoint->args, 'a', string)) {	/* Set alignment */
		ms->alignment = string[0];
		if (!strchr ("lrtb", ms->alignment)) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Valid label alignments (+a) are l|r|t|b\n", option);
			error++;
		}
	}
	if (gmt_get_modifier (ms->refpoint->args, 'l', string)) {	/* Add label */
		if (string[0]) strncpy (ms->label, string, GMT_LEN64-1);
		ms->do_label = true;
	}
	if (gmt_get_modifier (ms->refpoint->args, 'o', string)) {	/* Got offsets from reference point */
		if ((n = gmt_get_pair (GMT, string, GMT_PAIR_DIM_DUP, ms->off)) < 0) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Failed to parse offset arguments for +o modifier\n", option);
			error++;
		}
	}
	if (gmt_get_modifier (ms->refpoint->args, 'u', NULL))	/* Add units to annotations */
		ms->unit = true;
	if (error)
		gmt_mapscale_syntax (GMT, 'L', "Draw a map scale centered on specified reference point.");
	if (vertical || gmt_M_is_cartesian (GMT, GMT_IN))
		ms->measure = '\0';	/* No units for Cartesian data */

	ms->plot = true;
	return (error);
}

/*! . */
int gmt_getrose (struct GMT_CTRL *GMT, char option, char *text, struct GMT_MAP_ROSE *ms) {
	bool do_f = false;
	unsigned int error = 0, k, order[4] = {3,1,0,2};
	int n;
	char txt_a[GMT_LEN256] = {""}, string[GMT_LEN256] = {""};
	struct GMT_MAP_PANEL *save_panel = ms->panel;	/* In case it was set and we wipe it below with gmt_M_memset */

	/* SYNTAX is -Td|m[g|j|n|x]<refpoint>[+w<width>][+f|F[<kind>]][+i<pen>][+j<justify>][+l<w,e,s,n>][+m[<dec>[/<dlabel>]]][+o<dx>[/<dy>]][+p<pen>][+t<ints>]
	 * 1)  +f: fancy direction rose, <kind> = 1,2,3 which is the level of directions [1]. Use +F to flip W/E/S/N so readable from south
	 * 2)  Tm: magnetic rose.  Optionally, append +d<dec>[/<dlabel>], where <dec> is magnetic declination and dlabel its label [no declination info].
	 * If  -Tm, optionally set annotation interval with +t
	 */

	if (!text || text[0] == '\0') {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: No argument given\n", option);
		return GMT_PARSE_ERROR;
	}
	gmt_M_memset (ms, 1, struct GMT_MAP_ROSE);
	ms->panel = save_panel;	/* In case it is not NULL */
	if (!strstr (text, "+w") && (strchr ("gjn", text[1]) == NULL || strchr ("fm", text[1]))) return gmtsupport_getrose_old (GMT, option, text, ms);	/* Most likely old-style args */

	/* Assign default values */
	ms->type = GMT_ROSE_DIR_PLAIN;
	ms->size = 0.0;
	ms->a_int[GMT_ROSE_PRIMARY] = 30.0;	ms->f_int[GMT_ROSE_PRIMARY] = 5.0;	ms->g_int[GMT_ROSE_PRIMARY] = 1.0;
	ms->a_int[GMT_ROSE_SECONDARY] = 30.0;	ms->f_int[GMT_ROSE_SECONDARY] = 5.0;	ms->g_int[GMT_ROSE_SECONDARY] = 1.0;

	switch (text[0]) {
		case 'd': ms->type = GMT_ROSE_DIR_PLAIN; break;
		case 'm': ms->type = GMT_ROSE_MAG; break;
		default:
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Append d for directional and m for magnetic rose\n", option);
			return (-1);
			break;
	}
	if ((ms->refpoint = gmt_get_refpoint (GMT, &text[1], option)) == NULL) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  Map rose reference point was not accepted\n", option);
		gmt_refpoint_syntax (GMT, "Td|m", NULL, GMT_ANCHOR_MAPROSE, 3);
		return (1);	/* Failed basic parsing */
	}

	if (gmt_validate_modifiers (GMT, ms->refpoint->args, option, "dfFijloptw", GMT_MSG_ERROR)) return (1);

	/* Get optional +d, +f|F, +i, +j, +l, +o, +p, +t, +w modifiers */
	if (gmt_get_modifier (ms->refpoint->args, 'w', string))	{	/* Get rose dimensions */
		if (string[0] == '\0') {	/* Got nutin' */
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c:  No width argument given to +w modifier\n", option);
			error++;
		}
		else if (strchr (string, '%')) {	/* Got size in percentage of map width */
			ms->size = atof (string);
			ms->mode = GMT_ROSE_SIZE_VAR;
		}
		else {	/* Fixed width given */
			ms->size = gmt_M_to_inch (GMT, string);
			ms->mode = GMT_ROSE_SIZE_SET;
		}
	}
	else {	/* Compute once map width is known */
		ms->size = (ms->type == GMT_ROSE_MAG) ? GMT_MAG_ROSE_DEF_WIDTH : GMT_DIR_ROSE_DEF_WIDTH;
		ms->mode = GMT_ROSE_SIZE_VAR;
	}
	if (gmt_get_modifier (ms->refpoint->args, 'd', string)) {	/* Want magnetic directions */
		if (ms->type != GMT_ROSE_MAG) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c:  Cannot specify +d<info> when -Td is selected\n", option);
			return (-1);
		}
		if (string[0]) {	/* Got optional arguments */
			if (strchr (string, '/'))	/* Got both declimation and label */
				sscanf (string, "%[^/]/%s", txt_a, ms->dlabel);
			else
				strcpy (txt_a, string);
			error += gmt_verify_expectations (GMT, GMT_IS_LON, gmt_scanf (GMT, txt_a, GMT_IS_LON, &ms->declination), txt_a);
			ms->kind = 2;	/* Flag that we got declination parameters */
		}
		else
			ms->kind = 1;	/* Flag that we did not get declination parameters */
	}
	if (gmt_get_modifier (ms->refpoint->args, 'F', string)) {	/* Want fancy rose, optionally set what kind; text angle will be -90/90  */
		ms->align = true;	/* Adjust so readable from south */
		do_f = true;
	}
	else if (gmt_get_modifier (ms->refpoint->args, 'f', string))
		do_f = true;
	if (do_f) {	/* Want fancy rose, optionally set what kind */
		if (ms->type == GMT_ROSE_MAG) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c:  Cannot specify +f|F<kind> when -Tm is selected\n", option);
			error++;
		}
		ms->type = GMT_ROSE_DIR_FANCY;
		ms->kind = (string[0]) ? atoi (string) : 1;
		if (ms->kind < 1 || ms->kind > 3) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c:  Modifier +f|F<kind> must be 1, 2, or 3\n", option);
			error++;
		}
	}
	if (gmt_get_modifier (ms->refpoint->args, 'i', string)) {
		if (string[0] && gmt_getpen (GMT, string, &ms->pen[GMT_ROSE_PRIMARY])) error++;
		ms->draw_circle[GMT_ROSE_PRIMARY] = true;
	}
	if (gmt_get_modifier (ms->refpoint->args, 'j', string))	{	/* Got justification of item w.r.t. reference point */
		if (string[0] == '\0') {	/* Got nutin' */
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c:  No justification argument given to +j modifier\n", option);
			error++;
		}
		else
			ms->justify = gmt_just_decode (GMT, string, PSL_MC);
	}
	else	/* With -Dj or -DJ, set default to reference (mirriored) justify point, else MC */
		ms->justify = gmt_M_just_default (GMT, ms->refpoint, PSL_MC);
	if (gmt_get_modifier (ms->refpoint->args, 'l', string)) {	/* Set labels +lw,e,s,n*/
		ms->do_label = true;
		if (string[0] == 0) {	/* Want default labels */
			strcpy (ms->label[0], GMT->current.language.cardinal_name[2][2]);
			strcpy (ms->label[1], GMT->current.language.cardinal_name[2][1]);
			strcpy (ms->label[2], GMT->current.language.cardinal_name[2][3]);
			strcpy (ms->label[3], GMT->current.language.cardinal_name[2][0]);
		}
		else {	/* Decode w,e,s,n strings */
			size_t len;
			unsigned int n_comma = 0;
			char *tmp = string, *pp = NULL;
			/* Check we got 3 commas */
			for (len = strlen (string); len > 0; len--) if (string[len-1] == ',') n_comma++;
			k = 0;
			while (k < 4 && (pp = strsep (&tmp, ",")) != NULL) {	/* Get the four labels */
				if (pp[0] == '\0' || strcmp (pp, "-")) strncpy (ms->label[order[k]], pp, GMT_LEN64-1);
				k++;
			}
			if (n_comma < 3 && k != 4) {	/* Ran out of labels */
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: 4 Labels must be given via modifier +lw,e,s,n\n", option);
				error++;
			}
		}
	}
	if (gmt_get_modifier (ms->refpoint->args, 'o', string)) {	/* Got offsets from reference point */
		if ((n = gmt_get_pair (GMT, string, GMT_PAIR_DIM_DUP, ms->off)) < 0) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c:  Failed to parse offset arguments for +o modifier\n", option);
			error++;
		}
		ms->mode |= GMT_ROSE_OFF_SET;
	}
	if (gmt_get_modifier (ms->refpoint->args, 'p', string)) {
		if (string[0] && gmt_getpen (GMT, string, &ms->pen[GMT_ROSE_SECONDARY])) error++;
		ms->draw_circle[GMT_ROSE_SECONDARY] = true;
	}
	if (gmt_get_modifier (ms->refpoint->args, 't', string)) {	/* Set intervals */
		n = sscanf (string, "%lf/%lf/%lf/%lf/%lf/%lf",
			&ms->a_int[GMT_ROSE_SECONDARY], &ms->f_int[GMT_ROSE_SECONDARY], &ms->g_int[GMT_ROSE_SECONDARY],
			&ms->a_int[GMT_ROSE_PRIMARY], &ms->f_int[GMT_ROSE_PRIMARY], &ms->g_int[GMT_ROSE_PRIMARY]);
		if (!(n == 3 || n == 6)) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c:  Modifier +t<intervals> expects 3 or 6 intervals\n", option);
			error++;
		}
		ms->mode |= GMT_ROSE_INT_SET;
	}
	ms->plot = true;
	return (error);
}

int gmt_get_pair (struct GMT_CTRL *GMT, char *string, unsigned int mode, double par[]) {
	/* Read 2 coordinates or 0-2 dimensions, converted to inch.  Action depends on mode:
	 * mode == GMT_PAIR_COORD:	Expect two coordinates, error otherwise.
	 * mode == GMT_PAIR_DIM_EXACT:	Expect two dimensions, error otherwise.
	 * mode == GMT_PAIR_DIM_DUP:	Expect 0-2 dimensions, if 1 is found set 2 == 1.
	 * mode == GMT_PAIR_DIM_NODUP:	Expect 0-2 dimensions, no duplications.
	 *				Any defaults placed in par will survive.
	 */
	int n, k;
	/* Wrapper around GMT_Get_Values when we know input is either coordinates or plot dimensions */
	if ((n = GMT_Get_Values (GMT->parent, string, par, 2)) < 0) return n;	/* Parsing error */
	if ((mode == GMT_PAIR_COORD || mode == GMT_PAIR_DIM_EXACT) && n != 2) {
		char *kind[2] = {"coordinates", "dimensions"};
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Parsing error: Expected two %s\n", kind[mode]);
		return -1;
	}
	if (mode != GMT_PAIR_COORD) {	/* Since GMT_Get_Values returns default project length unit we scale to inches */
		for (k = 0; k < n; k++)
			par[k] *= GMT->session.u2u[GMT->current.setting.proj_length_unit][GMT_INCH];
	}
	if (mode == GMT_PAIR_DIM_DUP && n == 1)
		par[GMT_Y] = par[GMT_X];	/* Duplicate when second is not given */
	return n;	/* We return items parsed even if duplication means there might be 2 */
}

/*! . */
int gmt_getpanel (struct GMT_CTRL *GMT, char option, char *text, struct GMT_MAP_PANEL **Pptr) {
	/* Gets the specifications for a rectangular panel w/optional reflection that is
	 * used as background for legends, logos, images, and map scales. */

	unsigned int pos = 0, n_errors = 0;
	int n;
	char txt_a[GMT_LEN256] = {""}, txt_b[GMT_LEN256] = {""}, txt_c[GMT_LEN256] = {""}, p[GMT_BUFSIZ] = {""};
	struct GMT_MAP_PANEL *P = NULL;

	if (*Pptr) {	/* Already a panel structure there! */
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "gmt_getpanel: Given a non-null panel pointer!\n");
		return 1;
	}
	/* Initialize the panel settings first */
	P = gmt_M_memory (GMT, NULL, 1, struct GMT_MAP_PANEL);
	P->radius = GMT->session.u2u[GMT_PT][GMT_INCH] * GMT_FRAME_RADIUS;	/* 6 pt */
	gmt_init_fill (GMT, &P->fill, -1.0, -1.0, -1.0);			/* Default is no fill unless specified */
	gmt_init_fill (GMT, &P->sfill, gmt_M_is255 (127), gmt_M_is255 (127), gmt_M_is255 (127));	/* Default if gray shade is used */
	(void) gmt_getpen (GMT, "thicker,black", &P->pen1);			/* Heavier pen for main outline */
	P->pen2 = GMT->current.setting.map_default_pen;			/* Thinner pen for optional inner outline */
	P->debug_pen = GMT->current.setting.map_default_pen;			/* Thinner pen for optional inner outline */
	P->gap = GMT->session.u2u[GMT_PT][GMT_INCH] * GMT_FRAME_GAP;	/* Default is 2p */
	/* Initialize the panel clearances */
	P->padding[XLO] = GMT->session.u2u[GMT_PT][GMT_INCH] * GMT_FRAME_CLEARANCE;	/* Default is 4p */
	for (pos = XHI; pos <= YHI; pos++) P->padding[pos] = P->padding[XLO];
	P->off[GMT_X] = P->padding[XLO];	/* Set the shadow offsets [Default is (4p, -4p)] */
	P->off[GMT_Y] = -P->off[GMT_X];

	if (text == NULL || text[0] == 0) {	/* Blank arg means draw outline with default pen */
		P->mode = GMT_PANEL_OUTLINE;
		*Pptr = P;	/* Pass out the pointer to the panel attributes */
		return 0;
	}
	pos = 0;
	while (gmt_getmodopt (GMT, option, text, "cidgprs", &pos, p, &n_errors) && n_errors == 0) {	/* Looking for +c, [+d], +g, +i, +p, +r, +s */
		switch (p[0]) {
			case 'c':	/* Clearance will expand the rectangle by specified amounts */
				n = GMT_Get_Values (GMT->parent, &p[1], P->padding, 4);
				if (n == 1)	/* Same round in all directions */
					P->padding[XHI] = P->padding[YLO] = P->padding[YHI] = P->padding[XLO];
				else if (n == 2) {	/* Separate round in x and y */
					P->padding[YLO] = P->padding[YHI] = P->padding[XHI];
					P->padding[XHI] = P->padding[XLO];
				}
				else if (n != 4){
					GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Bad number of increment to modifier +%c.\n", option, p[0]);
					n_errors++;
				}
				/* Since GMT_Get_Values returns in default project length unit, convert to inch */
				for (n = 0; n < 4; n++) P->padding[n] *= GMT->session.u2u[GMT->current.setting.proj_length_unit][GMT_INCH];
				P->clearance = true;
				break;
			case 'd':	/* debug mode for developers */
				P->debug = true;
				if (p[1] && gmt_getpen (GMT, &p[1], &P->debug_pen)) n_errors++;
				break;
			case 'g':	/* Set fill */
				if (!p[1] || gmt_getfill (GMT, &p[1], &P->fill)) n_errors++;
				P->mode |= GMT_PANEL_FILL;
				break;
			case 'i':	/* Secondary pen info */
				P->mode |= GMT_PANEL_INNER;
				if (p[1]) {	/* Gave 1-2 attributes */
					n = sscanf (&p[1], "%[^/]/%s", txt_a, txt_b);
					if (n == 2) {	/* Got both gap and pen */
						P->gap = gmt_M_to_inch (GMT, txt_a);
						if (gmt_getpen (GMT, txt_b, &P->pen2)) n_errors++;
					}
					else	/* Only got pen; use default gap */
						if (gmt_getpen (GMT, txt_a, &P->pen2)) n_errors++;
				}
				break;
			case 'p':	/* Set outline and optionally change primary pen info */
				if (p[1] && gmt_getpen (GMT, &p[1], &P->pen1)) n_errors++;
				P->mode |= GMT_PANEL_OUTLINE;
				break;
			case 'r':	/* Corner radius of rounded rectangle */
				if (p[1]) P->radius = gmt_M_to_inch (GMT, &p[1]);
				P->mode |= GMT_PANEL_ROUNDED;
				break;
			case 's':	/* Get shade settings */
				if (p[1]) {
					n = sscanf (&p[1], "%[^/]/%[^/]/%s", txt_a, txt_b, txt_c);
					if (n == 1) {	/* Just got a new fill */
						if (gmt_getfill (GMT, txt_a, &P->sfill)) n_errors++;
					}
					else if (n == 2) {	/* Just got a new offset */
						if (gmt_get_pair (GMT, &p[1], GMT_PAIR_DIM_DUP, P->off) < 0) n_errors++;
					}
					else if (n == 3) {	/* Got offset and fill */
						P->off[GMT_X] = gmt_M_to_inch (GMT, txt_a);
						P->off[GMT_Y] = gmt_M_to_inch (GMT, txt_b);
						if (gmt_getfill (GMT, txt_c, &P->sfill)) n_errors++;
					}
					else n_errors++;
				}
				P->mode |= GMT_PANEL_SHADOW;
				break;
			default:
				n_errors++;
				break;
		}
	}
	*Pptr = P;	/* Pass out the pointer to the panel attributes */
	return ((int)n_errors);
}

/*! . */
unsigned int gmt_minmaxinc_verify (struct GMT_CTRL *GMT, double min, double max, double inc, double slop) {
	double range;
	gmt_M_unused(GMT);

	/* Check for how compatible inc is with the range max - min.
	   We will tolerate a fractional sloppiness <= slop.  The
	   return values are:
	   0 : Everything is ok
	   1 : range is not a whole multiple of inc (within assigned slop)
	   2 : the range (max - min) is < 0
	   3 : inc is <= 0
	*/

	if (inc <= 0.0) return (3);

	range = max - min;
	if (range < 0.0) return (2);

	range = (fmod (range / inc, 1.0));
	if (range > slop && range < (1.0 - slop)) return (1);
	return 0;
}

/*! . */
void gmt_str_tolower (char *value) {
	/* Convert entire string to lower case */
	int i, c;
	for (i = 0; value[i]; i++) {
		c = (int)value[i];
		value[i] = (char) tolower (c);
	}
}

/*! . */
void gmt_str_toupper (char *value) {
	/* Convert entire string to upper case */
	int i, c;
	for (i = 0; value[i]; i++) {
		c = (int)value[i];
		value[i] = (char) toupper (c);
	}
}

/*! . */
void gmt_str_setcase (struct GMT_CTRL *GMT, char *value, int mode) {
	if (mode == 0) return;	/* Do nothing */
	if (mode == -1)
		gmt_str_tolower (value);
	else if (mode == +1)
		gmt_str_toupper (value);
	else
		GMT_Report (GMT->parent, GMT_MSG_WARNING, "Bad mode (%d) passed to gmt_str_setcase\n", mode);
}

char *gmt_first_modifier (struct GMT_CTRL *GMT, char *string, const char *sep) {
	/* Return pointer to the first modifier +<char>, with three conditions:
	 * 1. <char> must be one of the letters in sep,
	 * 2. We must not be inside quoted text, i.e., "my +shit title",
	 * 3. The + must not be escaped, i.e., +t"My \+shit text"
	 *
	 * If the modifier is not found we returns NULL.  This is not an error
	 * but means we did not find anything.
	 */
	size_t len, k = 0;
	bool inside_quote = false, done = false;
	if (sep == NULL) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "gmt_first_modifier: No separation codes given\n");
		return NULL;
	}

	if (string == NULL) return NULL;
	len = strlen (string);
	inside_quote = (string[0] == '\"' || string[0] == '\'');
	while (!done) {
		while (k < len && (inside_quote || string[k] != '+' || (k > 0 && string[k-1] == '\\'))) {
			k++;
			if (string[k] == '\"' || string[k] == '\'') inside_quote = !inside_quote;
		}
		k++;	/* Advance to character after the + */
		if (k >= len) return NULL;
		if (strchr (sep, string[k]))
			done = true;
		else {
			if (isalpha (string[k])) GMT_Report (GMT->parent, GMT_MSG_WARNING, "Modifier +%c detected but not a valid modifier! - ignored\n", string[k]);
			return NULL;
		}
	}
	return (k > 0 && k < len) ? &string[k-1] : NULL;
}

char *gmtlib_last_valid_file_modifier (struct GMTAPI_CTRL *API, char* filename, const char *mods) {
	/* A filename make have sequences that could look like a GMT modifier but is actually just part
	 * of the filename, e.g. My.File+o44.grd.  We do not want to catch such sequences as modifiers and
	 * parse them.  The strategy we use is to start from the end of the filename and work backwards
	 * until the first non-expected "modifier" is found, then return pointer to first actual modifier
	 * found, or NULL.  Any modifier will be of the form +?[<arg>], where ? is a lower or upper-case
	 * letter, and <arg> is optional. */
	bool go = true;	/* Keep scanning backwards until we find an unrecognized modifier */
	bool allow_a;	/* True when "a" is a valid argument to the modifier */
	char *modifiers = NULL;	/* Pointer to the start of valid modifiers in this filename, or NULL */
	size_t k = strlen (filename);	/* k will serve as the index of the current character in the filename string */
	gmt_M_unused (API);

	while (filename[k] != '+' && k) k--;	/* Wind back to last found plus sign */
	if (k == 0 || filename[k+1] == '\0') go = false;	/* No modifiers found at all, or we found a single trailing + in the name (e.g., my.test+) */
	while (go) {	/* Here, filename[k] == '+' and k > 0 */
		if (isalpha (filename[k+1]) && strchr (mods, filename[k+1])) {	/* This is a valid file modifier */
			modifiers = &filename[k];	/* Update the pointer the current start of valid modifiers */
			k--;	/* Step one back from the '+' character; k could become 0 if filename was just valid modifiers (...) */
			while (filename[k] != '+' && k) k--;	/* Wind back to last found plus sign as long as we are not in first position */
			if (k == 0) go = false;	/* Ran out of characters */
		}
		else	/* Not a valid modifier or just part of something like a positive number - stop our scanning */
			go = false;
	}
	if (modifiers) {	/* Check that we have modifiers only and not stuff like +o.myextension */
		bool error = false;
		k = 0;
		while (!error && modifiers[k]) {
			if (modifiers[k] == '+') {
				k++;
				allow_a = false;	/* a is not a valid number */
				switch (modifiers[k]) {	/* The modifier code */
					case 'o': case 's':	/* +o<offset>|a,  +s<scale>|a */
						allow_a = true;	/* Argument "a" for auto is OK for these modifiers */
						/* Fall through on purpose */
					case 'd': case 'h': case 'i': case 'n': 	/* +d<div>, +h[<hinge>], +i<inc>, +n<nodata> */
						k++;	/* Move to start of argument, next modifier, or NULL */
						while (modifiers[k] && modifiers[k] != '+' && strchr ("-+.0123456789eE", modifiers[k])) k++;	/* Skip a numerical argument */
						if (allow_a && modifiers[k] == 'a') k++;	/* Ok with a for this modifier */
						if (!(modifiers[k] == '\0' || modifiers[k] == '+')) error = true;	/* Means we found non-numbers after valid modifier */
						break;
					case 'u': case 'U':	/* +u<unit>, +U<unit */
						k++;	/* Move to start of argument, next modifier, or NULL */
						if (modifiers[k] == '\0' || strchr (GMT_LEN_UNITS2, modifiers[k]) == NULL)
							error = true;	/* Missing the unit argument */
						else	/* Got valid unit */
							k++;
						break;
					default:	/* Modifier not from the global grid/CPT list */
						error = true;
						break;
				}
			}
			else	/* Found some junk */
				error = true;
		}
		if (error) {
			GMT_Report (API, GMT_MSG_WARNING, "Your filename %s has what appears as valid GMT modifiers (from list +%s) but they are embedded rather than appended to the filename - modifiers ignored\n", filename, mods);
			modifiers = NULL;
		}
	}
	return (modifiers);	/* Pass out the start of the valid modifiers or NULL */
}

#if 0
/* Was used to test the tokenizing of +<code>[<args] in cases
 * where <args> may contain an escaped or quoted +, etc.
 * To test, just add option case -N in psbasemap and call
 * psbasemap -N<combination of +a+b+c+d with/without args. */
void gmt_testing (struct GMT_CTRL *GMT, char *string) {
	char *c = NULL, p[GMT_BUFSIZ] = {""}, *sep = "abcde";
	unsigned int pos = 0, uerr = 0;
	c = gmt_first_modifier (GMT, string, sep);
	while (gmt_getmodopt (GMT, 'N', c, sep, &pos, p, &uerr) && uerr == 0) {
		switch (p[0]) {
			case 'a': fprintf (stderr, "From +%c Got %s\n", p[0], (p[1]) ? &p[1] : "nothing");	break;
			case 'b': fprintf (stderr, "From +%c Got %s\n", p[0], (p[1]) ? &p[1] : "nothing");	break;
			case 'c': fprintf (stderr, "From +%c Got %s\n", p[0], (p[1]) ? &p[1] : "nothing");	break;
			case 'd': fprintf (stderr, "From +%c Got %s\n", p[0], (p[1]) ? &p[1] : "nothing");	break;
			default: fprintf (stderr, "Got up empty\n");	break;
		}
	}
}
#endif

/*! . */
char *gmt_assign_text (struct GMT_CTRL *GMT, char *p) {
	/* Deals with duplicating a string and skipping any enclosing quotes.
	 * Note: p is expected to be the result from gmt_getmodopt, hence the p[1] stuff */
	char *txt = NULL;
	gmt_M_unused(GMT);
	if (strchr ("\"\'", p[1]) && p[1] == p[strlen(p)-1]) { /* Eliminate quotes */
		txt = strdup (&p[2]);
		txt[strlen(txt)-1] = '\0';
	}
	else	/* Normal title */
		txt = strdup (&p[1]);
	return (txt);
}

/*! . */
unsigned int gmt_getmodopt (struct GMT_CTRL *GMT, const char option, const char *string, const char *sep, unsigned int *pos, char *token, unsigned int *err) {
	/* Breaks string into tokens separated by one of more modifier separator
	 * characters (in sep) following a "+".  E.g., if you are looking for a
	 * set of modifiers +a, +g<arg>, and +z, set sep = "agz" and any other
	 * +<char> will fail.  Set *pos to 0 before first call.
	 * If any of your <arg> may contain a + (e.g., +t"My +ve experience") then you can
	 * 1) Escape the plus with backslash (e.g., +t"My \+ve experience")
	 * 2) Put everything in quotes (e.g., +t'"My +ve experience"') as we
	 *    will ignore plus-signs inside quotes.  You may also switch around
	 *    and do +t"'My +ve experience'" as long as quotes match properly.
	 * Returns 1 if it finds a token and 0 if no more tokens left.
	 * pos is updated and token is returned.  char *token must point
	 * to memory of length >= strlen (string).
	 * string is not changed by gmt_getmodopt.
	 */

	unsigned int i, j, string_len;
	bool done = false, in_quote = false;
	gmt_M_unused(GMT);

	if (string == NULL) return 0;	/* Nothing to do */
	
	string_len = (unsigned int)strlen (string);
	token[0] = 0;	/* Initialize token to NULL in case we are at end */

	while (!done) {
		/* Wind up *pos to first + sign NOT inside quotes OR escaped */
		while (string[*pos] && (in_quote || string[*pos] != '+' || ((*pos) > 0 && string[(*pos)-1] == '\\'))) {
			(*pos)++;
			if (string[*pos] == '\"' || string[*pos] == '\'') in_quote = !in_quote;	/* Watch if we enter quoted text */
		}

		if (*pos >= string_len || string_len == 0) return 0;	/* Got NULL string or no more string left to search */

		(*pos)++;	/* Go and examine if next char is one of requested modifier options */
		done = (strchr (sep, (int)string[*pos]) != NULL);	/* true if this is our guy */
		if (!done && err) {	/* Unrecognized modifier is an error, unless err is NULL */
			if (option)
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Unrecognized modifier +%c\n", option, string[*pos]);
			else
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Unrecognized modifier +%c\n", string[*pos]);
			(*err)++;
		}
	}

	/* Search for next +sep occurrence */
	/* Search for next +char occurrence */
	i = *pos; j = 0;
	//while (string[i] && (in_quote || string[i] != '+' || (i && string[i-1] == '\\') || !strchr (sep, (int)string[i+1]))) {
	while (string[i] && (in_quote || string[i] != '+' || (i && string[i-1] == '\\'))) {
		if (string[i+1] != '+' || string[i] != '\\') token[j++] = string[i];	/* Do not return the escape char */
		i++;	/* Go to next character */
		if (string[i] == '\"' || string[i] == '\'') in_quote = !in_quote;	/* Check when we get past the quoted section */
	}
	token[j] = 0;	/* Add terminating \0 */
	if (j > 2 && token[1] == '\"' && token[j-1] == '\"') { /* The whole thing was given in quotes */
		memmove (&token[1], &token[2], strlen(token)-3);
		token[j-2] = 0;
	}

	*pos = i;

	return 1;
}

/*! . */
double gmtlib_get_map_interval (struct GMT_CTRL *GMT, unsigned int type, struct GMT_PLOT_AXIS_ITEM *T) {
	switch (T->unit) {
		case 'd':	/* arc Degrees */
			return (T->interval);
			break;
		case 'm':	/* arc Minutes */
			return (T->interval * GMT_MIN2DEG);
			break;
		case 'c':	/* arc Seconds [deprecated] */
			if (gmt_M_compat_check (GMT, 4)) {
				GMT_Report (GMT->parent, GMT_MSG_COMPAT, "Second interval unit c is deprecated; use s instead\n");
			}
			else
				return (T->interval);
			/* Intentionally fall through - to 's' */
		case 's':	/* arc Seconds or time seconds */
			return ((type == GMT_TIME) ? T->interval : T->interval * GMT_SEC2DEG);
			break;
		default:
			return (T->interval);
			break;
	}
}

/*! . */
int gmt_just_validate (struct GMT_CTRL *GMT, char *key, char *def) {
	/* Ensure given justification key is kosher.  If not, then
	 * use def unless NULL, else error */
	if ((strchr ("LCRlcr", key[0]) && strchr ("BMTbmt", key[1])) ||
		(strchr ("LCRlcr", key[1]) && strchr ("BMTbmt", key[0]))) return 0;	/* We are good */
	if (def == NULL) return GMT_RUNTIME_ERROR;	/* No fallback */
	GMT_Report (GMT->parent, GMT_MSG_WARNING, "Malformed justification/position code %s replaced by %s\n", key, def);
	strncpy (key, def, 2U);	/* Override using default code */
	return 0;
}

/*! . */
void gmt_just_to_code (struct GMT_CTRL *GMT, int justify, char *key) {
	/* Converts justify integer code to string.  Assume justify is valid */
	static char *hor = {"LCR"}, *ver = {"BMT"};
	int i, j;
	gmt_M_unused (GMT);
	i = (justify % 4) - 1;
	j = justify / 4;
	assert (i >= 0 && i <= 2);
	assert (j >= 0 && j <= 2);
	key[0] = hor[i];
	key[1] = ver[j];
}

/*! . */
int gmt_just_decode (struct GMT_CTRL *GMT, char *key, int def) {
	/* Converts justification info (key) like BL (bottom left) to justification indices
	 * def = default value.
	 * When def % 4 = 0, horizontal position must be specified
	 * When def / 4 = 3, vertical position must be specified
	 */
	int i, j;
	size_t k;
	const size_t s_length = strlen(key);

	if (isdigit ((int)key[0])) {	/* Apparently got one of the 1-11 codes */
		i = atoi(key);
		if (i < PSL_BL || i > PSL_TR || (i%4) == 0) i = -99;
		return (i);
	}

	i = def % 4;
	j = def / 4;
	for (k = 0; k < s_length; k++) {
		switch (key[k]) {
			case 'b': case 'B':	/* Bottom baseline */
				j = 0;
				break;
			case 'm': case 'M':	/* Middle baseline */
				j = 1;
				break;
			case 't': case 'T':	/* Top baseline */
				j = 2;
				break;
			case 'l': case 'L':	/* Left Justified */
				i = 1;
				break;
			case 'c': case 'C':	/* Center Justified */
				i = 2;
				break;
			case 'r': case 'R':	/* Right Justified */
				i = 3;
				break;
			default:
				return (-99);
		}
	}

	if (i == 0) {
		GMT_Report (GMT->parent, GMT_MSG_WARNING, "Horizontal text justification not set, defaults to L(eft)\n");
		i = 1;
	}
	if (j == 3) {
		GMT_Report (GMT->parent, GMT_MSG_WARNING, "Vertical text justification not set, defaults to B(ottom)\n");
		j = 0;
	}

	return (j * 4 + i);
}

/*! . */
void gmt_smart_justify (struct GMT_CTRL *GMT, int just, double angle, double dx, double dy, double *x_shift, double *y_shift, unsigned int mode) {
	/* mode = 2: Assume a radius offset so that corner shifts are adjusted by 1/sqrt(2) */
	double s, c, xx, yy, f;
	gmt_M_unused(GMT);
	f = (mode == 2) ? 1.0 / M_SQRT2 : 1.0;
	sincosdegree (angle, &s, &c);
	xx = (2 - (just%4)) * dx * f;	/* Smart shift in x */
	yy = (1 - (just/4)) * dy * f;	/* Smart shift in x */
	*x_shift += c * xx - s * yy;	/* Must account for angle of label */
	*y_shift += s * xx + c * yy;
}

/*! . */
unsigned int gmt_verify_expectations (struct GMT_CTRL *GMT, unsigned int wanted, unsigned int got, char *item) {
	/* Compare what we wanted with what we got and see if it is OK */
	unsigned int error = 0;

	if (wanted == GMT_IS_UNKNOWN) {	/* No expectations set */
		switch (got) {
			case GMT_IS_ABSTIME:	/* Found a T in the string - ABSTIME ? */
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "%s appears to be an Absolute Time String: ", item);
				if (gmt_M_is_geographic (GMT, GMT_IN))
					GMT_Report (GMT->parent, GMT_MSG_ERROR, "This is not allowed for a map projection\n");
				else
					GMT_Report (GMT->parent, GMT_MSG_ERROR, "You must specify time data type with option -f.\n");
				error++;
				break;

			case GMT_IS_GEO:	/* Found a : in the string - GEO ? */
				GMT_Report (GMT->parent, GMT_MSG_WARNING, "%s appears to be a Geographical Location String: ", item);
				if (GMT->current.proj.projection_GMT == GMT_LINEAR)
					GMT_Report (GMT->parent, GMT_MSG_WARNING, "You should append d to the -Jx or -JX projection for geographical data.\n");
				else
					GMT_Report (GMT->parent, GMT_MSG_WARNING, "You should specify geographical data type with option -f.\n");
				GMT_Report (GMT->parent, GMT_MSG_WARNING, "Will proceed assuming geographical input data.\n");
				break;

			case GMT_IS_LON:	/* Found a : in the string and then W or E - LON ? */
				GMT_Report (GMT->parent, GMT_MSG_WARNING, "%s appears to be a Geographical Longitude String: ", item);
				if (GMT->current.proj.projection_GMT == GMT_LINEAR)
					GMT_Report (GMT->parent, GMT_MSG_WARNING, "You should append d to the -Jx or -JX projection for geographical data.\n");
				else
					GMT_Report (GMT->parent, GMT_MSG_WARNING, "You should specify geographical data type with option -f.\n");
				GMT_Report (GMT->parent, GMT_MSG_WARNING, "Will proceed assuming geographical input data.\n");
				break;

			case GMT_IS_LAT:	/* Found a : in the string and then S or N - LAT ? */
				GMT_Report (GMT->parent, GMT_MSG_WARNING, "%s appears to be a Geographical Latitude String: ", item);
				if (GMT->current.proj.projection_GMT == GMT_LINEAR)
					GMT_Report (GMT->parent, GMT_MSG_WARNING, "You should append d to the -Jx or -JX projection for geographical data.\n");
				else
					GMT_Report (GMT->parent, GMT_MSG_WARNING, "You should specify geographical data type with option -f.\n");
				GMT_Report (GMT->parent, GMT_MSG_WARNING, "Will proceed assuming geographical input data.\n");
				break;

			case GMT_IS_FLOAT:
				break;
			default:
				break;
		}
	}
	else {
		switch (got) {
			case GMT_IS_NAN:
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Could not decode %s, return NaN.\n", item);
				error++;
				break;

			case GMT_IS_LAT:
				if (wanted == GMT_IS_LON) {
					GMT_Report (GMT->parent, GMT_MSG_ERROR, "Expected longitude, but %s is a latitude!\n", item);
					error++;
				}
				break;

			case GMT_IS_LON:
				if (wanted == GMT_IS_LAT) {
					GMT_Report (GMT->parent, GMT_MSG_ERROR, "Expected latitude, but %s is a longitude!\n", item);
					error++;
				}
				break;
			default:
				break;
		}
	}
	return (error);
}

/*! . */
void gmt_list_custom_symbols (struct GMT_CTRL *GMT) {
	/* Opens up GMT->init.custom_symbols.lis and displays the list of custom symbols */

	FILE *fp = NULL;
	char list[GMT_LEN256] = {""}, buffer[GMT_BUFSIZ] = {""};
	struct GMTAPI_CTRL *API = GMT->parent;

	/* Open the list in $GMT->session.SHAREDIR */

	gmt_getsharepath (GMT, "custom", "gmt_custom_symbols", ".conf", list, R_OK);
	if ((fp = fopen (list, "r")) == NULL) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Cannot open file %s\n", list);
		return;
	}

	GMT_Usage (API, 3, "Available custom symbols (See Appendix N):");
	gmt_message (GMT, "       ---------------------------------------------------------\n");
	while (fgets (buffer, GMT_BUFSIZ, fp)) if (!(buffer[0] == '#' || buffer[0] == 0))
		gmt_message (GMT, "       %s", buffer);
	fclose (fp);
	gmt_message (GMT, "       ---------------------------------------------------------\n");
}

/*! . */
void gmtlib_rotate2D (struct GMT_CTRL *GMT, double x[], double y[], uint64_t n, double x0, double y0, double angle, double xp[], double yp[]) {
	/* Cartesian rotation of x,y in the plane by angle followed by translation by (x0, y0) */
	uint64_t i;
	double s, c;
	gmt_M_unused(GMT);

	sincosdegree (angle, &s, &c);
	for (i = 0; i < n; i++) {	/* Coordinate transformation: Rotate and add new (x0, y0) offset */
		xp[i] = x0 + x[i] * c - y[i] * s;
		yp[i] = y0 + x[i] * s + y[i] * c;
	}
}

/*! . */
unsigned int gmtlib_get_arc (struct GMT_CTRL *GMT, double x0, double y0, double r, double dir1, double dir2, double **x, double **y) {
	/* Create an array with a circular arc. r in inches, angles in degrees */

	unsigned int i, n;
	double da, s, c, *xx = NULL, *yy = NULL;

	n = urint (D2R * fabs (dir2 - dir1) * r / GMT->current.setting.map_line_step);
	if (n < 2) n = 2;	/* To prevent division by 0 below */
	xx = gmt_M_memory (GMT, NULL, n, double);
	yy = gmt_M_memory (GMT, NULL, n, double);
	da = (dir2 - dir1) / (n - 1);
	for (i = 0; i < n; i++) {
		sincosdegree (dir1 + i * da, &s, &c);
		xx[i] = x0 + r * c;
		yy[i] = y0 + r * s;
	}
	*x = xx;
	*y = yy;

	return (n);
}

/*! . */
int gmt_init_track (struct GMT_CTRL *GMT, double y[], uint64_t n, struct GMT_XSEGMENT **S) {
	/* gmt_init_track accepts the y components of an x-y track of length n and returns an array of
	 * line segments that have been sorted on the minimum y-coordinate
	 */

	uint64_t a, b, nl = n - 1;
	struct GMT_XSEGMENT *L = NULL;

	if (nl == 0) {
		GMT_Report (GMT->parent, GMT_MSG_WARNING, "nl = 0 in gmt_init_track\n");
		return 0;
	}

	L = gmt_M_memory (GMT, NULL, nl, struct GMT_XSEGMENT);

	for (a = 0, b = 1; b < n; a++, b++) {
		if (y[b] < y[a]) {
			L[a].start = b;
			L[a].stop = a;
		}
		else {
			L[a].start = a;
			L[a].stop = b;
		}
	}

	/* Sort on minimum y-coordinate, if tie then on 2nd coordinate */
	QSORT_R (L, nl, sizeof (struct GMT_XSEGMENT), gmtsupport_ysort, y);

	*S = L;

	return (GMT_NOERROR);
}

/*! . */
uint64_t gmt_crossover (struct GMT_CTRL *GMT, double xa[], double ya[], uint64_t *sa0, struct GMT_XSEGMENT A[], uint64_t na, double xb[], double yb[], uint64_t *sb0, struct GMT_XSEGMENT B[], uint64_t nb, bool internal, bool geo, struct GMT_XOVER *X) {
	size_t nx_alloc;
	uint64_t nx, this_a, this_b, xa_start = 0, xa_stop = 0, xb_start = 0, xb_stop = 0, ta_start = 0, ta_stop = 0, tb_start, tb_stop, n_seg_a, n_seg_b;
	bool new_a, new_b, new_a_time = false, xa_OK = false, xb_OK = false;
	uint64_t *sa = NULL, *sb = NULL;
	double del_xa, del_xb, del_ya, del_yb, i_del_xa, i_del_xb, i_del_ya, i_del_yb, slp_a, slp_b, xc, yc, tx_a, tx_b;
	double amin, amax, bmin, bmax;
	double xshift = 0.0;	/* This may become +/-360 or 0 depending on longitude shifts for geo, else 0 */
	double dx_ab;		/* Be careful due to longitude jumps are lurking everywhere; use this variable for that */

	if (na < 2 || nb < 2) return (0);	/* Need at least 2 points to make a segment */

	if (geo) {	/* Since our algorithm is Cartesian we must do some extra checking to prevent shits */
		gmtlib_get_lon_minmax (GMT, xa, na, &amin, &amax);
		gmtlib_get_lon_minmax (GMT, xb, nb, &bmin, &bmax);
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "First line lon range: %g %g  Second line lon range: %g %g\n", amin, amax, bmin, bmax);
		if (gmt_M_360_range (amin, amax))
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "First geographic line has 360-degree range.  This may fool the Cartesian crossover algorithm\n");
		if (!internal && gmt_M_360_range (bmin, bmax))
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "Second geographic line has 360-degree range.  This may fool the Cartesian crossover algorithm\n");
		gmt_eliminate_lon_jumps (GMT, xa, na);
		if (!internal) gmt_eliminate_lon_jumps (GMT, xb, nb);
	}
	else {	/* Might still be geographic if user did not indicate with -fg */
		uint64_t k;
		amin = bmin = DBL_MAX;	amax = bmax = -DBL_MAX;
		for (k = 0; k < na; k++) {
			if (xa[k] < amin) amin = xa[k];
			if (xa[k] > amax) amax = xa[k];
		}
		for (k = 0; k < nb; k++) {
			if (xb[k] < bmin) bmin = xb[k];
			if (xb[k] > bmax) bmax = xb[k];
		}

		if (((amin < -150.0 && amax > 150.0) || (bmin < -150.0 && bmax > 150.0)) && ((amax-amin) <= 360.0 && (bmax-bmin) <= 360.0))
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "Your Cartesian tracks could be geographic - did you forget -fg?\n");
	}

	this_a = this_b = nx = 0;
	new_a = new_b = true;
	nx_alloc = GMT_SMALL_CHUNK;

	n_seg_a = na - 1;
	n_seg_b = nb - 1;

	/* Assign pointers to segment info given, or initialize zero arrays if not given */
	sa = (sa0) ? sa0 : gmt_M_memory (GMT, NULL, na, uint64_t);
	sb = (sb0) ? sb0 : gmt_M_memory (GMT, NULL, nb, uint64_t);

	gmtsupport_x_alloc (GMT, X, nx_alloc, true);

	while (this_a < n_seg_a && yb[B[this_b].start] > ya[A[this_a].stop]) this_a++;	/* Go to first possible A segment */

	while (this_a < n_seg_a) {

		/* First check for internal neighboring segments which cannot cross */

		if (internal && (this_a == this_b || (A[this_a].stop == B[this_b].start || A[this_a].start == B[this_b].stop) || (A[this_a].start == B[this_b].start || A[this_a].stop == B[this_b].stop))) {	/* Neighboring segments cannot cross */
			this_b++;
			new_b = true;
		}
		else if (yb[B[this_b].start] > ya[A[this_a].stop]) {	/* Reset this_b and go to next A */
			this_b = n_seg_b;
		}
		else if (yb[B[this_b].stop] < ya[A[this_a].start]) {	/* Must advance B in y-direction */
			this_b++;
			new_b = true;
		}
		else if (sb[B[this_b].stop] != sb[B[this_b].start]) {	/* Must advance B in y-direction since this segment crosses multiseg boundary*/
			this_b++;
			new_b = true;
		}
		else {	/* Current A and B segments overlap in y-range */

			if (new_a) {	/* Must sort this A new segment in x so xa_start points to smallest x */
				if (xa[A[this_a].stop] < xa[A[this_a].start]) {
					xa_start = A[this_a].stop;
					xa_stop  = A[this_a].start;
				}
				else {
					xa_start = A[this_a].start;
					xa_stop  = A[this_a].stop;
				}
				new_a = false;
				new_a_time = true;
				xa_OK = (sa[xa_start] == sa[xa_stop]);	/* false if we cross between multiple segments */
			}

			if (new_b) {	/* Must sort this new B segment in x so xb_start points to smallest x */
				if (xb[B[this_b].stop] < xb[B[this_b].start]) {
					xb_start = B[this_b].stop;
					xb_stop  = B[this_b].start;
				}
				else {
					xb_start = B[this_b].start;
					xb_stop  = B[this_b].stop;
				}
				xb_OK = (sb[xb_start] == sb[xb_stop]);	/* false if we cross between multiple segments */
			}

			/* OK, first check for any overlap in x range */

			if (xa_OK && xb_OK && gmtsupport_x_overlap (xa, xb, &xa_start, &xa_stop, &xb_start, &xb_stop, geo, &xshift)) {

				/* We have segment overlap in x.  Now check if the two segments cross. Note:
				 * For geographic coordinates, the xa and xb for these two segments will be
				 * offset by xshift [0 for Cartesian].  Thus we add xshift to each end of a segment
				 * so the values have no 360-degree offset relative to the coordinates in xb.  */

				if (geo) {	/* Do this once for this segment comparisons */
					xa[xa_start] += xshift;
					xa[xa_stop]  += xshift;
				}
				del_xa = xa[xa_stop] - xa[xa_start];	/* xshift would cancel out */
				del_xb = xb[xb_stop] - xb[xb_start];
				del_ya = ya[xa_stop] - ya[xa_start];
				del_yb = yb[xb_stop] - yb[xb_start];

				if (gmt_M_is_zero (del_xa)) {	/* Vertical A segment: Special case */
					if (gmt_M_is_zero (del_xb)) {	/* Two vertical segments with some overlap */
						double y4[4];
						/* Assign as crossover the middle of the overlapping segments */
						X->x[nx] = xa[xa_start];
						y4[0] = ya[xa_start];	y4[1] = ya[xa_stop];	y4[2] = yb[xb_start];	y4[3] = yb[xb_stop];
						gmt_sort_array (GMT, y4, 4, GMT_DOUBLE);
						if (!doubleAlmostEqual (y4[1], y4[2])) {
							X->y[nx] = 0.5 * (y4[1] + y4[2]);
							X->xnode[0][nx] = 0.5 * (xa_start + xa_stop);
							X->xnode[1][nx] = 0.5 * (xb_start + xb_stop);
							nx++;
						}
					}
					else {	/* B is not vertical so we can solve for intersection */
						dx_ab = xa[xa_start] - xb[xb_start];
						i_del_xb = 1.0 / del_xb;
						yc = yb[xb_start] + dx_ab * del_yb * i_del_xb;
						if (!(yc < ya[A[this_a].start] || yc > ya[A[this_a].stop])) {	/* Did cross within the segment extents */
							/* Only accept xover if occurring before segment end (in time) */

							if (xb_start < xb_stop) {
								tb_start = xb_start;	/* B Node first in time */
								tb_stop = xb_stop;	/* B Node last in time */
							}
							else {
								tb_start = xb_stop;	/* B Node first in time */
								tb_stop = xb_start;	/* B Node last in time */
							}
							if (new_a_time) {
								if (xa_start < xa_stop) {
									ta_start = xa_start;	/* A Node first in time */
									ta_stop = xa_stop;	/* A Node last in time */
								}
								else {
									ta_start = xa_stop;	/* A Node first in time */
									ta_stop = xa_start;	/* A Node last in time */
								}
								new_a_time = false;
							}

							dx_ab = xa[xa_start] - xb[tb_start];
							tx_a = ta_start + fabs ((yc - ya[ta_start]) / del_ya);
							tx_b = tb_start + fabs (dx_ab) * i_del_xb;
							if (tx_a < ta_stop && tx_b < tb_stop) {
								X->x[nx] = xa[xa_start];
								X->y[nx] = yc;
								X->xnode[0][nx] = tx_a;
								X->xnode[1][nx] = tx_b;
								nx++;
							}
						}
					}
				}
				else if (gmt_M_is_zero (del_xb)) {	/* Vertical B segment: Special case */
					dx_ab = xb[xb_start] - xa[xa_start];
					i_del_xa = 1.0 / del_xa;
					yc = ya[xa_start] + dx_ab * del_ya * i_del_xa;
					if (!(yc < yb[B[this_b].start] || yc > yb[B[this_b].stop])) {	/* Did cross within the segment extents */
						/* Only accept xover if occurring before segment end (in time) */

						if (xb_start < xb_stop) {
							tb_start = xb_start;	/* B Node first in time */
							tb_stop = xb_stop;	/* B Node last in time */
						}
						else {
							tb_start = xb_stop;	/* B Node first in time */
							tb_stop = xb_start;	/* B Node last in time */
						}
						if (new_a_time) {
							if (xa_start < xa_stop) {
								ta_start = xa_start;	/* A Node first in time */
								ta_stop = xa_stop;	/* A Node last in time */
							}
							else {
								ta_start = xa_stop;	/* A Node first in time */
								ta_stop = xa_start;	/* A Node last in time */
							}
							new_a_time = false;
						}

						dx_ab = xb[xb_start] - xa[ta_start];
						tx_a = ta_start + fabs (dx_ab) * i_del_xa;
						tx_b = tb_start + fabs ((yc - yb[tb_start]) / del_yb);
						if (tx_a < ta_stop && tx_b < tb_stop) {
							X->x[nx] = xb[xb_start];
							X->y[nx] = yc;
							X->xnode[0][nx] = tx_a;
							X->xnode[1][nx] = tx_b;
							nx++;
						}
					}
				}
				else if (gmt_M_is_zero (del_ya)) {	/* Horizontal A segment: Special case */

					if (gmt_M_is_zero (del_yb)) {	/* Two horizontal segments with some overlap */
						double x4[4];
						/* Assign as crossover the middle of the overlapping segments */
						X->y[nx] = ya[xa_start];
						x4[0] = xa[xa_start];	x4[1] = xa[xa_stop];
						x4[2] = xb[xb_start];	x4[3] = xb[xb_stop];
						gmt_sort_array (GMT, x4, 4, GMT_DOUBLE);
						if (!doubleAlmostEqual (x4[1], x4[2])) {
							X->x[nx] = 0.5 * (x4[1] + x4[2]);
							X->xnode[0][nx] = 0.5 * (xa_start + xa_stop);
							X->xnode[1][nx] = 0.5 * (xb_start + xb_stop);
							nx++;
						}
					}
					else {	/* B is not horizontal so we can solve for intersection */
						i_del_yb = 1.0 / del_yb;
						xc = xb[xb_start] + (ya[xa_start] - yb[xb_start]) * del_xb * i_del_yb;
						if (!(xc < xa[xa_start] || xc > xa[xa_stop])) {	/* Did cross within the segment extents */

							/* Only accept xover if occurring before segment end (in time) */

							if (xb_start < xb_stop) {
								tb_start = xb_start;	/* B Node first in time */
								tb_stop = xb_stop;	/* B Node last in time */
							}
							else {
								tb_start = xb_stop;	/* B Node first in time */
								tb_stop = xb_start;	/* B Node last in time */
							}
							if (new_a_time) {
								if (xa_start < xa_stop) {
									ta_start = xa_start;	/* A Node first in time */
									ta_stop = xa_stop;	/* A Node last in time */
								}
								else {
									ta_start = xa_stop;	/* A Node first in time */
									ta_stop = xa_start;	/* A Node last in time */
								}
								new_a_time = false;
							}

							dx_ab = xc - xa[ta_start];
							tx_a = ta_start + fabs (dx_ab) / del_xa;
							tx_b = tb_start + fabs ((ya[xa_start] - yb[tb_start]) * i_del_yb);
							if (tx_a < ta_stop && tx_b < tb_stop) {
								X->y[nx] = ya[xa_start];
								X->x[nx] = xc;
								X->xnode[0][nx] = tx_a;
								X->xnode[1][nx] = tx_b;
								nx++;
							}
						}
					}
				}
				else if (gmt_M_is_zero (del_yb)) {	/* Horizontal B segment: Special case */

					i_del_ya = 1.0 / del_ya;
					xc = xa[xa_start] + (yb[xb_start] - ya[xa_start]) * del_xa * i_del_ya;
					if (!(xc < xb[xb_start] || xc > xb[xb_stop])) {	/* Did cross within the segment extents */

						/* Only accept xover if occurring before segment end (in time) */

						if (xb_start < xb_stop) {
							tb_start = xb_start;	/* B Node first in time */
							tb_stop = xb_stop;	/* B Node last in time */
						}
						else {
							tb_start = xb_stop;	/* B Node first in time */
							tb_stop = xb_start;	/* B Node last in time */
						}
						if (new_a_time) {
							if (xa_start < xa_stop) {
								ta_start = xa_start;	/* A Node first in time */
								ta_stop = xa_stop;	/* A Node last in time */
							}
							else {
								ta_start = xa_stop;	/* A Node first in time */
								ta_stop = xa_start;	/* A Node last in time */
							}
							new_a_time = false;
						}

						dx_ab = xc - xb[tb_start];
						tx_a = ta_start + fabs ((yb[xb_start] - ya[ta_start]) * i_del_ya);
						tx_b = tb_start + fabs (dx_ab) / del_xb;
						if (tx_a < ta_stop && tx_b < tb_stop) {
							X->y[nx] = yb[xb_start];
							X->x[nx] = xc;
							X->xnode[0][nx] = tx_a;
							X->xnode[1][nx] = tx_b;
							nx++;
						}
					}
				}
				else if (gmt_M_is_dnan(del_yb)) {}	/* Just do nothing and prevent call to doubleAlmostEqual() which would assert fail with NaNs */

				else {	/* General case */

					i_del_xa = 1.0 / del_xa;
					i_del_xb = 1.0 / del_xb;
					slp_a = del_ya * i_del_xa;
					slp_b = del_yb * i_del_xb;
					if (doubleAlmostEqual (slp_a, slp_b)) {	/* Segments are parallel */
						double x4[4];
						/* Assign as possible crossover the middle of the overlapping segments */
						x4[0] = xa[xa_start];	x4[1] = xa[xa_stop];
						x4[2] = xb[xb_start];	x4[3] = xb[xb_stop];
						gmt_sort_array (GMT, x4, 4, GMT_DOUBLE);
						if (!doubleAlmostEqual (x4[1], x4[2])) {
							xc = 0.5 * (x4[1] + x4[2]);
							yc = slp_a * (xc - xa[xa_start]) + ya[xa_start];
							if ((slp_b * (xc - xb[xb_start]) + yb[xb_start]) == yc) {
								X->y[nx] = yc;
								X->x[nx] = xc;
								X->xnode[0][nx] = 0.5 * (xa_start + xa_stop);
								X->xnode[1][nx] = 0.5 * (xb_start + xb_stop);
								nx++;
							}
						}
					}
					else {	/* Segments are not parallel */
						xc = (yb[xb_start] - ya[xa_start] + slp_a * xa[xa_start] - slp_b * xb[xb_start]) / (slp_a - slp_b);
						if (!(xc < xa[xa_start] || xc > xa[xa_stop] || xc < xb[xb_start] || xc > xb[xb_stop])) {	/* Did cross within the segment extents */

							/* Only accept xover if occurring before segment end (in time) */

							if (xb_start < xb_stop) {
								tb_start = xb_start;	/* B Node first in time */
								tb_stop = xb_stop;	/* B Node last in time */
							}
							else {
								tb_start = xb_stop;	/* B Node first in time */
								tb_stop = xb_start;	/* B Node last in time */
							}
							if (new_a_time) {
								if (xa_start < xa_stop) {
									ta_start = xa_start;	/* A Node first in time */
									ta_stop = xa_stop;	/* A Node last in time */
								}
								else {
									ta_start = xa_stop;	/* A Node first in time */
									ta_stop = xa_start;	/* A Node last in time */
								}
								new_a_time = false;
							}

							tx_a = ta_start + fabs (xc - xa[ta_start]) * i_del_xa;
							tx_b = tb_start + fabs (xc - xb[tb_start]) * i_del_xb;
							if (tx_a < ta_stop && tx_b <= tb_stop) {	/* Equality means the crossing occurred on the second data node */
								X->x[nx] = xc;
								X->y[nx] = ya[xa_start] + (xc - xa[xa_start]) * slp_a;
								X->xnode[0][nx] = tx_a;
								X->xnode[1][nx] = tx_b;
								nx++;
							}
						}
					}
				}
				if (nx > 1 && fabs (X->xnode[0][nx-1] - X->xnode[0][nx-2]) < GMT_CONV8_LIMIT && fabs (X->xnode[1][nx-1] - X->xnode[1][nx-2]) < GMT_CONV8_LIMIT) {
					/* Two consecutive crossing of the same node or really close, skip this repeat crossover */
					nx--;
					GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Warning - Two consecutive crossovers appear to be identical, the 2nd one was skipped\n");
				}
				if (nx == nx_alloc) {
					nx_alloc <<= 1;
					gmtsupport_x_alloc (GMT, X, nx_alloc, false);
				}
			} /* End x-overlap */

			this_b++;
			new_b = true;

		} /* End y-overlap */

		if (this_b == n_seg_b) {
			this_a++;
			this_b = (internal) ? this_a : 0;
			new_a = new_b = true;
		}

	} /* End while loop */

	if (!sa0) gmt_M_free (GMT, sa);
	if (!sb0) gmt_M_free (GMT, sb);

	if (nx == 0) gmt_x_free (GMT, X);	/* Nothing to write home about... */

	return (nx);
}

/*! . */
void gmt_x_free (struct GMT_CTRL *GMT, struct GMT_XOVER *X) {
	gmt_M_free (GMT, X->x);
	gmt_M_free (GMT, X->y);
	gmt_M_free (GMT, X->xnode[0]);
	gmt_M_free (GMT, X->xnode[1]);
}

/*! . */
unsigned int gmtlib_linear_array (struct GMT_CTRL *GMT, double min, double max, double delta, double phase, double **array) {
	/* Create an array of values between min and max, with steps delta and given phase.
	   Example: min = 0, max = 9, delta = 2, phase = 1
	   Result: 1, 3, 5, 7, 9
	*/

	int64_t first, last, i, n;
	double *val = NULL;

	if (delta <= 0.0) return (0);

	/* Undo the phase and scale by 1/delta */
	min = (min - phase) / delta;
	max = (max - phase) / delta;

	/* Look for first value */
	first = lrint (floor (min));
	while (min - first > GMT_CONV4_LIMIT) first++;

	/* Look for last value */
	last = lrint (ceil (max));
	while (last - max > GMT_CONV4_LIMIT) last--;

	n = last - first + 1;
	if (n <= 0) return (0);

	/* Create an array of n equally spaced elements */
	val = gmt_M_memory (GMT, NULL, n, double);
	for (i = 0; i < n; i++) val[i] = phase + (first + i) * delta;	/* Rescale to original values */

	*array = val;

	return ((unsigned int)n);
}

/*! . */
unsigned int gmtlib_log_array (struct GMT_CTRL *GMT, double min, double max, double delta, double **array) {
	int64_t first, last, i, n, nticks;
	double *val = NULL, tvals[10];

	/* Because min and max may be tiny values (e.g., 10^-20) we must do all calculations on the log10 (value) */

	if (gmt_M_is_zero (delta))
		return (0);
	min = d_log10 (GMT, min);
	max = d_log10 (GMT, max);
	first = lrint (floor (min));
	last = lrint (ceil (max));

	if (delta < 0) {	/* Coarser than every magnitude */
		n = gmtlib_linear_array (GMT, min, max, fabs (delta), 0.0, array);
		for (i = 0; i < n; i++) (*array)[i] = pow (10.0, (*array)[i]);
		return ((unsigned int)n);
	}

	tvals[0] = 0.0;	/* Common to all */
	switch (lrint (fabs (delta))) {
		case 2:	/* Annotate 1, 2, 5, 10 */
			tvals[1] = d_log10 (GMT, 2.0);
			tvals[2] = d_log10 (GMT, 5.0);
			tvals[3] = 1.0;
			nticks = 3;
			break;
		case 3:	/* Annotate 1, 2, ..., 8, 9, 10 */
			nticks = 9;
			for (i = 1; i <= nticks; i++) tvals[i] = d_log10 (GMT, (double)(i + 1));
			break;
		default:	/* Annotate just 1 and 10 */
			nticks = 1;
			tvals[1] = 1.0;
	}

	/* Assign memory to array (may be a bit too much) */
	n = (last - first + 1) * nticks + 1;
	val = gmt_M_memory (GMT, NULL, n, double);

	/* Find the first logarithm larger than min */
	i = 0;
	val[0] = (double) first;
	while (min - val[0] > GMT_CONV4_LIMIT && i < nticks) {
		i++;
		val[0] = first + tvals[i];
	}

	/* Find the first logarithm larger than max */
	n = 0;
	while (val[n] - max < GMT_CONV4_LIMIT) {
		if (i >= nticks) {
			i -= nticks;
			first++;
		}
		i++; n++;
		val[n] = first + tvals[i];
	}

	/* val[n] is too large, so we use only the first n, until val[n-1] */
	val = gmt_M_memory (GMT, val, n, double);

	/* Convert from log10 to values */
	for (i = 0; i < n; i++) val[i] = pow (10.0, val[i]);

	*array = val;

	return ((unsigned int)n);
}

/*! . */
unsigned int gmtlib_log2_array (struct GMT_CTRL *GMT, double min, double max, double delta, double **array) {
	/* Create an array of values between min and max, with steps delta.
	   However, take log2 first then use the delta as increment in log2 space
	*/

	int64_t first, last, i, n;
	double *val = NULL;

	if (delta <= 0.0) return (0);

	min = d_log2 (GMT, min) / delta;
	max = d_log2 (GMT, max) / delta;

	/* Look for first value */
	first = lrint (floor (min));
	while (min - first > GMT_CONV4_LIMIT) first++;

	/* Look for last value */
	last = lrint (ceil (max));
	while (last - max > GMT_CONV4_LIMIT) last--;

	n = last - first + 1;
	if (n <= 0) return (0);

	/* Create an array of n equally spaced elements */
	val = gmt_M_memory (GMT, NULL, n, double);
	for (i = 0; i < n; i++) val[i] = (first + i) * delta;	/* Rescale to original values */

	/* Convert from log2 to values */
	for (i = 0; i < n; i++) val[i] = pow (2.0, val[i]);
	*array = val;

	return ((unsigned int)n);
}

/*! . */
unsigned int gmtlib_pow_array (struct GMT_CTRL *GMT, double min, double max, double delta, unsigned int x_or_y_or_z, double **array) {
	int i, n = 0;
	double *val = NULL, v0, v1;

	if (delta <= 0.0) return (0);

	if (GMT->current.map.frame.axis[x_or_y_or_z].type != GMT_POW) return (gmtlib_linear_array (GMT, min, max, delta, 0.0, array));

	if (x_or_y_or_z == 0) { /* x-axis */
		GMT->current.proj.fwd_x (GMT, min, &v0);
		GMT->current.proj.fwd_x (GMT, max, &v1);
		n = gmtlib_linear_array (GMT, v0, v1, delta, 0.0, &val);
		for (i = 0; i < n; i++) GMT->current.proj.inv_x (GMT, &val[i], val[i]);
	}
	else if (x_or_y_or_z == 1) { /* y-axis */
		GMT->current.proj.fwd_y (GMT, min, &v0);
		GMT->current.proj.fwd_y (GMT, max, &v1);
		n = gmtlib_linear_array (GMT, v0, v1, delta, 0.0, &val);
		for (i = 0; i < n; i++) GMT->current.proj.inv_y (GMT, &val[i], val[i]);
	}
	else if (x_or_y_or_z == 2) { /* z-axis */
		GMT->current.proj.fwd_z (GMT, min, &v0);
		GMT->current.proj.fwd_z (GMT, max, &v1);
		n = gmtlib_linear_array (GMT, v0, v1, delta, 0.0, &val);
		for (i = 0; i < n; i++) GMT->current.proj.inv_z (GMT, &val[i], val[i]);
	}
	else
		GMT_Report (GMT->parent, GMT_MSG_WARNING, "gmtlib_pow_array internal error: Invalid side (%d) passed - nothing returned!\n", x_or_y_or_z);

	*array = val;

	return (n);
}

/*! . */
GMT_LOCAL uint64_t gmtsupport_time_array (struct GMT_CTRL *GMT, double min, double max, double inc, char unit, bool interval, double **array) {
	/* When T->active is true we must return interval start/stop even if outside min/max range */
	uint64_t n = 0;
	size_t n_alloc = GMT_SMALL_CHUNK;
	struct GMT_MOMENT_INTERVAL I;
	double *val = NULL;

	val = gmt_M_memory (GMT, NULL, n_alloc, double);
	gmt_M_memset (&I, 1, struct GMT_MOMENT_INTERVAL);
	I.unit = unit;
	I.step = urint (inc);
	gmtlib_moment_interval (GMT, &I, min, true);	/* First time we pass true for initialization */
	while (I.dt[0] <= max) {		/* As long as we are not gone way past the end time */
		if (I.dt[0] >= min || interval) val[n++] = I.dt[0];		/* Was inside region */
		gmtlib_moment_interval (GMT, &I, 0.0, false);			/* Advance to next interval */
		if (n == n_alloc) {					/* Allocate more space */
			n_alloc <<= 1;
			val = gmt_M_memory (GMT, val, n_alloc, double);
		}
	}
	if (interval) val[n++] = I.dt[0];	/* Must get end of interval too */
	val = gmt_M_memory (GMT, val, n, double);

	*array = val;

	return (n);
}

/*! . */
unsigned int gmtlib_time_array (struct GMT_CTRL *GMT, double min, double max, struct GMT_PLOT_AXIS_ITEM *T, double **array) {
	/* When T->active is true we must return interval start/stop even if outside min/max range */
	unsigned int n;
	bool interval;

	if (!T->active) return (0);
	interval = (T->type == 'i' || T->type == 'I');	/* Only true for i/I axis items */
	if (T->unit == 's' && T->interval <= 1.0)
		n = gmtlib_linear_array (GMT, min, max, T->interval, 0.0, array);
	else
		n = (unsigned int)gmtsupport_time_array (GMT, min, max, T->interval, T->unit, interval, array);

	return (n);
}

/*! . */
unsigned int gmtlib_load_custom_annot (struct GMT_CTRL *GMT, struct GMT_PLOT_AXIS *A, char item, double **xx, char ***labels) {
	/* Reads a file with one or more records of the form
	 * value	types	[label]
	 * where value is the coordinate of the tickmark, types is a combination
	 * of a|i (annot or interval annot), f (tick), or g (gridline).
	 * The a|i will take a label string (or sentence).
	 * The item argument specifies which type to consider [a|i,f,g].  We return
	 * an array with coordinates and labels, and set interval to true if applicable.
	 */
	int nc, error;
	unsigned int k = 0, save_coltype, save_max_cols_to_read;
	uint64_t row;
	bool text, found, save_trailing;
	//unsigned int n_annot = 0, n_int = 0;
	double *x = NULL, limit[2] = {-DBL_MAX, +DBL_MAX};
	char **L = NULL, type[GMT_LEN8] = {""}, txt[GMT_BUFSIZ] = {""};
	struct GMT_DATASET *D = NULL;
	struct GMT_DATASEGMENT *S = NULL;

	/* Temporarily change what data type col one is */
	save_coltype = gmt_get_column_type (GMT, GMT_IN, GMT_X);
	save_trailing = GMT->current.io.trailing_text[GMT_IN];
	save_max_cols_to_read = GMT->current.io.max_cols_to_read;
	gmt_set_column_type (GMT, GMT_IN, GMT_X, gmt_M_type (GMT, GMT_IN, A->id));
	GMT->current.io.trailing_text[GMT_IN] = true;	/* Since we definitively have that here */
	text = ((item == 'a' || item == 'i') && labels);
	if (!GMT->common.R.oblique)	/* Eliminate items outside rectangular w/e/s/n/z0/z1 bounds */
		limit[0] = GMT->common.R.wesn[2*A->id], limit[1] = GMT->common.R.wesn[2*A->id+1];

	gmt_disable_bghio_opts (GMT);	/* Do not want any -b -g -h -i -o to affect the reading from -F files */
	GMT->current.io.max_cols_to_read = 1;
	if ((error = GMT_Set_Columns (GMT->parent, GMT_IN, 1, GMT_COL_FIX)) != GMT_NOERROR) return (1);
	if ((D = GMT_Read_Data (GMT->parent, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_NONE, GMT_READ_NORMAL, NULL, A->file_custom, NULL)) == NULL) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Unable to open custom annotation file %s!\n", A->file_custom);
		gmt_set_column_type (GMT, GMT_IN, GMT_X, save_coltype);
		return (0);
	}
	gmt_reenable_bghio_opts (GMT);	/* Recover settings provided by user (if -b -g -h -i were used at all) */
	gmt_set_column_type (GMT, GMT_IN, GMT_X, save_coltype);
	GMT->current.io.trailing_text[GMT_IN] = save_trailing;
	GMT->current.io.max_cols_to_read = save_max_cols_to_read;
	S = D->table[0]->segment[0];	/* All we got */

	x = gmt_M_memory (GMT, NULL, S->n_rows, double);
	if (text) L = gmt_M_memory (GMT, NULL, S->n_rows, char *);
	for (row = 0; row < S->n_rows; row++) {
		nc = sscanf (S->text[row], "%s %[^\n]", type, txt);
		found = ((item == 'a' && (strchr (type, 'a') || strchr (type, 'i'))) || (strchr (type, item) != NULL));
		if (!found) continue;	/* Not the type we were requesting */
		if (gmt_M_x_is_lon (GMT, GMT_IN)) {	/* Be careful with periodic data */
			if (!gmt_M_360_range (limit[0], limit[1])) {	/* It is possible to be outside if not global */
				S->data[GMT_X][row] -= 360.0;	/* Ensure we are far west */
				while (S->data[GMT_X][row] < limit[0]) S->data[GMT_X][row] += 360.0;	/* Wind towards east */
				if (S->data[GMT_X][row] > limit[1]) continue;	/* Outside given region */
			}
		}
		else if (S->data[GMT_X][row] < limit[0] || S->data[GMT_X][row] > limit[1]) continue;	/* Cartesian check */
#if 0	/* Old degguging things left commented */
		if (strchr (type, 'i')) n_int++;
		if (strchr (type, 'a')) n_annot++;
#endif
		x[k] = S->data[GMT_X][row];
		if (text && nc == 2) {
			gmtlib_enforce_rgb_triplets (GMT, txt, GMT_BUFSIZ);	/* If @; is used, make sure the color information passed on to ps_text is in r/b/g format */
			L[k] = strdup (txt);
		}
		k++;
	}

	if (k == 0) {	/* No such items */
		gmt_M_free (GMT, x);
		if (text) gmt_M_free (GMT, L);
		return (0);
	}
	if (k < S->n_rows) {
		x = gmt_M_memory (GMT, x, k, double);
		if (text) L = gmt_M_memory (GMT, L, k, char *);
	}
	*xx = x;
	if (text) *labels = L;
	GMT_Destroy_Data (GMT->parent, &D);

	return (k);
}

/*! . */
unsigned int gmtlib_coordinate_array (struct GMT_CTRL *GMT, double min, double max, struct GMT_PLOT_AXIS_ITEM *T, double **array, char ***labels) {
	unsigned int n = 0;

	if (!T->active) return (0);	/* Nothing to do */

	if (T->special && GMT->current.map.frame.axis[T->parent].file_custom) {	/* Want custom intervals */
		n = gmtlib_load_custom_annot (GMT, &GMT->current.map.frame.axis[T->parent], (char)tolower((unsigned char) T->type), array, labels);
		return (n);
	}

	switch (GMT->current.proj.xyz_projection[T->parent]) {
		case GMT_LINEAR:
			n = gmtlib_linear_array (GMT, min, max, gmtlib_get_map_interval (GMT, GMT_LINEAR, T), GMT->current.map.frame.axis[T->parent].phase, array);
			break;
		case GMT_LOG10:
			n = gmtlib_log_array (GMT, min, max, gmtlib_get_map_interval (GMT, GMT_LOG10, T), array);
			break;
		case GMT_POW:
			n = gmtlib_pow_array (GMT, min, max, gmtlib_get_map_interval (GMT, GMT_POW, T), T->parent, array);
			break;
		case GMT_TIME:
			n = gmtlib_time_array (GMT, min, max, T, array);
			break;
		default:
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "gmtlib_coordinate_array internal error: Invalid projection type (%d) passed - nothing returned!\n", GMT->current.proj.xyz_projection[T->parent]);
			return 0;
			break;
	}
	return (n);
}

/*! . */
bool gmtlib_annot_pos (struct GMT_CTRL *GMT, double min, double max, struct GMT_PLOT_AXIS_ITEM *T, double coord[], double *pos) {
	/* Calculates the location of the next annotation in user units.  This is
	 * trivial for tick annotations but can be tricky for interval annotations
	 * since the annotation location is not necessarily centered on the interval.
	 * For instance, if our interval is 3 months we do not want "January" centered
	 * on that quarter.  If the position is outside our range we return true
	 */
	bool is_interval = (T->type == 'i' || T->type == 'I');
	double range, start, stop;

	if (is_interval && T->special) {
		range = 0.5 * (coord[1] - coord[0]);	/* Half width of interval in internal representation */
		start = MAX (min, coord[0]);			/* Start of interval, but not less that start of axis */
		stop  = MIN (max, coord[1]);			/* Stop of interval,  but not beyond end of axis */
		if ((stop - start) < (GMT->current.setting.time_interval_fraction * range)) return (true);		/* Sorry, fraction not large enough to annotate */
		*pos = 0.5 * (start + stop);				/* Set half-way point */
		if (((*pos) - GMT_CONV8_LIMIT) < min || ((*pos) + GMT_CONV8_LIMIT) > max) return (true);	/* Outside axis range */
	}
	else if (is_interval) {
		if (gmt_M_uneven_interval (T->unit) || T->interval != 1.0) {	/* Must find next month to get month centered correctly */
			struct GMT_MOMENT_INTERVAL Inext;
			gmt_M_memset (&Inext, 1, struct GMT_MOMENT_INTERVAL);	/* Wipe it */
			Inext.unit = T->unit;		/* Initialize MOMENT_INTERVAL structure members */
			Inext.step = 1;
			gmtlib_moment_interval (GMT, &Inext, coord[0], true);	/* Get this one interval only */
			range = 0.5 * (Inext.dt[1] - Inext.dt[0]);	/* Half width of interval in internal representation */
			start = MAX (min, Inext.dt[0]);			/* Start of interval, but not less that start of axis */
			stop  = MIN (max, Inext.dt[1]);			/* Stop of interval,  but not beyond end of axis */
		}
		else {
			range = 0.5 * (coord[1] - coord[0]);	/* Half width of interval in internal representation */
			start = MAX (min, coord[0]);			/* Start of interval, but not less that start of axis */
			stop  = MIN (max, coord[1]);			/* Stop of interval,  but not beyond end of axis */
		}
		if ((stop - start) < (GMT->current.setting.time_interval_fraction * range)) return (true);		/* Sorry, fraction not large enough to annotate */
		*pos = 0.5 * (start + stop);				/* Set half-way point */
		if (((*pos) - GMT_CONV8_LIMIT) < min || ((*pos) + GMT_CONV8_LIMIT) > max) return (true);	/* Outside axis range */
	}
	else if (coord[0] < (min - GMT_CONV8_LIMIT) || coord[0] > (max + GMT_CONV8_LIMIT))		/* Outside axis range */
		return (true);
	else if (T->parent == GMT->current.io.cycle_col && GMT->current.io.cycle_interval) {
		*pos = coord[0] + 0.5;	/* Since we know this only happens for "months" (all same width) or weekdays */
		if (*pos > max) return (true);
	}
	else
		*pos = coord[0];

	return (false);
}

/*! . */
int gmtlib_get_coordinate_label (struct GMT_CTRL *GMT, char *string, struct GMT_PLOT_CALCLOCK *P, char *format, struct GMT_PLOT_AXIS_ITEM *T, double coord, double delta) {
	/* Returns the formatted annotation string for the non-geographic axes */
	bool upper = false;
	unsigned int kind = 0, axis, code;
	enum gmt_col_enum type;
	int ival;

	switch (GMT->current.map.frame.axis[T->parent].type) {
		case GMT_LINEAR:
#if 0
			GMT_near_zero_roundoff_fixer_upper (&coord, T->parent);	/* Try to adjust those ~0 "gcc -O" values to exact 0 */
#endif
			code = (GMT->current.io.cycle_col == GMT->current.map.frame.axis[T->parent].id) ? GMT->current.io.cycle_operator : 0;
			switch (code) {	/* Do special treatment for annual and weekly annotations since they are texts but axis is not a time-axis per se... */
				case GMT_CYCLE_WEEK:		/* Must do days of the week or abbreviation */
					gmtlib_set_case_and_kind (GMT, GMT->current.setting.format_time[GMT_PRIMARY], &upper, &kind);
					ival = (irint (coord) + GMT->current.setting.time_week_start + GMT_WEEK2DAY_I) % GMT_WEEK2DAY_I;	/* Wrap around */
					strncpy (string, GMT->current.language.day_name[kind][ival], GMT_LEN16);
					if (upper) gmt_str_toupper (string);
					break;
				case GMT_CYCLE_ANNUAL:	/* Must write month name or abbreviation */
					gmtlib_set_case_and_kind (GMT, GMT->current.setting.format_time[GMT_PRIMARY], &upper, &kind);
					ival = (urint (coord) + 12) % 12;	/* Wrap around */
					strncpy (string, GMT->current.language.month_name[kind][ival], GMT_LEN16);
					if (upper) gmt_str_toupper (string);
					break;
				default:
					if ((type = gmt_get_column_type (GMT, GMT_IN, T->parent)) & GMT_IS_GEO) {	/* Actually a geographic coordinate */
						bool do_minutes = false, do_seconds = false;
						if (!gmt_M_is_dnan (delta)) {
							do_minutes = (fabs (fmod (delta, 1.0)) > GMT_CONV4_LIMIT);
							do_seconds = gmtlib_set_do_seconds (GMT, delta);
						}
						axis = (type & GMT_IS_LON) ? GMT_X : GMT_Y;
						gmtlib_get_annot_label (GMT, coord, string, do_minutes, do_seconds, true, axis, GMT->current.map.is_world);
					}
					else
						gmt_sprintf_float (GMT, string, format, coord);
					break;
			}
			break;
		case GMT_LOG10:
			sprintf (string, "%ld", lrint (d_log10 (GMT, coord)));
			break;
		case GMT_POW:
			if (GMT->current.proj.xyz_projection[T->parent] == GMT_POW)
				sprintf (string, format, coord);
			else
				sprintf (string, "10@+%ld@+", lrint (d_log10 (GMT, coord)));
			break;
		case GMT_TIME:
			gmtlib_get_time_label (GMT, string, P, T, coord);
			break;
		default:
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "gmtlib_get_coordinate_label internal error: Wrong type (%d) passed! No label set\n", GMT->current.map.frame.axis[T->parent].type);
			GMT->parent->error = GMT_NOT_A_VALID_TYPE;
			string[0] = '\0';
			break;
	}
	return (GMT_OK);
}

int gmtlib_polar_prepare_label (struct GMT_CTRL *GMT, double angle, unsigned int side, double *line_angle, double *text_angle, unsigned int *justify) {
	/* Special function to set justification and text angle for polar projections (r/theta, i.e. GMT_POLAR) */
	/* Normally y-min (south) is at r = 0 and y-max (north) is on the perimeter, but +f reverses that */
	/* Normally x-min (west) is the boundary with the region on the leeft, and x-max (east) on the right, but +a reverses that */
	*line_angle = angle;
	if (GMT->current.proj.flip && side%2 == 0) /* Flipping means south is on the outside and north is the inside */
		side = 2 - side;	/* Turns 2 to 0 and 0 to 2 */

	switch (side) {
		case S_SIDE:	/* We are annotating angles on the inner (donut) boundary */
			if (gmt_M_is_zero (angle) || ((angle+GMT_CONV8_LIMIT) >= 180.0 && (angle-GMT_CONV8_LIMIT) < 360.0)) *justify = 10, *text_angle = angle - 270.0;
			else *justify = 2, *text_angle = angle - 90;
			break;
		case E_SIDE:
			if ((angle+GMT_CONV8_LIMIT) >= 90.0 && (angle-GMT_CONV8_LIMIT) < 270.0) *justify = 7, *text_angle = angle - 180;
			else  *justify = 5, *text_angle = angle;
			break;
		case N_SIDE:	/* We are annotating angles on the outer boundary */
			if ((angle+GMT_CONV8_LIMIT) >= 0.0 && (angle-GMT_CONV8_LIMIT) <= 180.0) *justify = 2, *text_angle = angle - 90.0;
			else *justify = 10, *text_angle = angle + 90.0;
			break;
		case W_SIDE:
			if ((angle+GMT_CONV8_LIMIT) >= 90.0 && (angle-GMT_CONV8_LIMIT) < 270.0) *justify = 7, *text_angle = angle - 180;
			else  *justify = 5, *text_angle = angle;
			break;
	}
	return (0);
}

/*! . */
int gmtlib_prepare_label (struct GMT_CTRL *GMT, double angle, unsigned int side, double x, double y, unsigned int type, double *line_angle, double *text_angle, unsigned int *justify) {
	bool set_angle;

	if (!GMT->current.proj.edge[side]) return -1;		/* Side doesn't exist */
	if (GMT->current.map.frame.side[side] < GMT_AXIS_ANNOT) return -1;	/* Don't want labels here */

	if (GMT->current.map.frame.check_side == true && type != side%2) return -1;

	if (GMT->current.proj.projection_GMT == GMT_POLAR) return (gmtlib_polar_prepare_label (GMT, angle, side, line_angle, text_angle, justify));

	if (GMT->current.setting.map_annot_oblique & GMT_OBL_ANNOT_NORMAL_TICKS && !(side%2)) angle = -90.0;	/* gmtsupport_get_label_parameters will make this 0 */

	if (angle < 0.0) angle += 360.0;

	set_angle = ((!GMT->common.R.oblique && !(gmt_M_is_azimuthal(GMT) || gmt_M_is_conical(GMT))) || GMT->common.R.oblique);
	if (!GMT->common.R.oblique && (GMT->current.proj.projection_GMT == GMT_GENPER || GMT->current.proj.projection_GMT == GMT_GNOMONIC || GMT->current.proj.projection_GMT == GMT_POLYCONIC)) set_angle = true;
	if (set_angle) {
		if (side == 0 && angle < 180.0) angle -= 180.0;
		if (side == 1 && (angle > 90.0 && angle < 270.0)) angle -= 180.0;
		if (side == 2 && angle > 180.0) angle -= 180.0;
		if (side == 3 && (angle < 90.0 || angle > 270.0)) angle -= 180.0;
	}

	if (!gmtsupport_get_label_parameters (GMT, side, angle, type, text_angle, justify)) return -1;
	*line_angle = angle;
	if (GMT->current.setting.map_annot_oblique & GMT_OBL_ANNOT_NORMAL_TICKS) *line_angle = (side - 1) * 90.0;

	if (!set_angle) *justify = gmtsupport_polar_adjust (GMT, side, angle, x, y);
	if (set_angle && !GMT->common.R.oblique && GMT->current.proj.projection_GMT == GMT_GNOMONIC) {
		/* Fix until we write something that works for everything.  This is a global gnomonic map
		 * so it is easy to fix the angles.  We get correct justify and make sure
		 * the line_angle points away from the boundary */

		angle = fmod (2.0 * angle, 360.0) / 2.0;	/* 0-180 range */
		if (angle > 90.0) angle -= 180.0;
		*justify = gmtsupport_gnomonic_adjust (GMT, angle, x, y);
		if (*justify == 7) *line_angle += 180.0;
	}

	return 0;
}

/*! . */
void gmtlib_get_annot_label (struct GMT_CTRL *GMT, double val, char *label, bool do_minutes, bool do_seconds, bool do_hemi, unsigned int lonlat, bool worldmap) {
/* val:		Degree value of annotation */
/* label:	String to hold the final annotation */
/* do_minutes:	true if degree and minutes are desired, false for just integer degrees */
/* do_seconds:	true if degree, minutes, and seconds are desired */
/* do_hemi:	true if compass headings (W, E, S, N) are desired */
/* lonlat:	0 = longitudes, 1 = latitudes, 2 non-geographical data passed, 3 = latitudes in longitude positions, 4 = great-circle degrees */
/* worldmap:	T/F, whatever GMT->current.map.is_world is */

	int sign, d, m, s, m_sec;
	unsigned int k, n_items, level, type;
	bool zero_fix = false, lat_special = (lonlat == 3), deg_special = (lonlat == 4);
	char hemi_pre[GMT_LEN16] = {""}, hemi_post[GMT_LEN16] = {""}, text[GMT_LEN64] = {""}, *use_format = NULL;

	/* Must override do_minutes and/or do_seconds if format uses decimal notation for that item */

	if (GMT->current.plot.calclock.geo.order[1] == -1) do_minutes = false;
	if (GMT->current.plot.calclock.geo.order[2] == -1) do_seconds = false;
	for (k = n_items = 0; k < 3; k++) if (GMT->current.plot.calclock.geo.order[k] >= 0) n_items++;	/* How many of d, m, and s are requested as integers */

	if (lat_special) lonlat = 1;	/* Remove the special flag */
	if (deg_special) lonlat = 0;	/* Remove the special flag */
	if (lonlat == 0)	/* Fix longitudes range first */
		gmt_lon_range_adjust (GMT->current.plot.calclock.geo.range, &val);
    else {	/* i.e., for geographical data */
		if (doubleAlmostEqual (val, 360.0) && !worldmap)
			val = 0.0;
		if (doubleAlmostEqual (val, 360.0) && worldmap && GMT->current.proj.projection_GMT == GMT_OBLIQUE_MERC)
			val = 0.0;
	}

	if (GMT->current.plot.calclock.geo.wesn) {	/* Either -2, -1, +1, +2 */
		bool post = (GMT->current.plot.calclock.geo.wesn > 0);	/* Place hemisphere string after numbers */
		if (GMT->current.plot.calclock.geo.wesn == 2) strcat (hemi_post, " ");
		if (!do_hemi || gmt_M_is_zero (val)) { /* Skip adding hemisphere indication */
		}
		else if (lonlat == 0) {	/* Longitudes */
			switch (GMT->current.plot.calclock.geo.range) {
				case GMT_IS_0_TO_P360_RANGE:
				case GMT_IS_0_TO_P360:
					strcat (post ? hemi_post : hemi_pre, GMT->current.language.cardinal_name[1][1]);
					break;
				case GMT_IS_M360_TO_0_RANGE:
				case GMT_IS_M360_TO_0:
					strcat (post ? hemi_post : hemi_pre, GMT->current.language.cardinal_name[2][1]);
					break;
				default:
					if (!(doubleAlmostEqual (val, 180.0) || doubleAlmostEqual (val, -180.0))) strcat (post ? hemi_post : hemi_pre, (val < 0.0) ? GMT->current.language.cardinal_name[1][0] : GMT->current.language.cardinal_name[1][1]);
					break;
			}
		}
		else	/* Latitudes */
			strcat (post ? hemi_post : hemi_pre, (val < 0.0) ? GMT->current.language.cardinal_name[2][2] : GMT->current.language.cardinal_name[2][3]);

		if (GMT->current.plot.calclock.geo.wesn == -2) strcat (hemi_pre, " ");
		if (!deg_special) {
			val = fabs (val);
			if (hemi_post[0] == ' ' && hemi_post[1] == 0) hemi_post[0] = 0;	/* No space if no hemisphere indication */
			if (hemi_pre[0]  == ' ' && hemi_pre[1]  == 0) hemi_pre[0]  = 0;	/* No space if no hemisphere indication */
		}
	}
	if (deg_special)
		hemi_pre[0] = hemi_post[0] = 0;
	else if (GMT->current.plot.calclock.geo.no_sign)
		val = fabs (val);
	sign = (val < 0.0) ? -1 : 1;

	level = do_minutes + do_seconds;		/* 0, 1, or 2 */
	type = (GMT->current.plot.calclock.geo.n_sec_decimals > 0) ? 1 : 0;
	label[0] = '\0';	/* Start with clean slate */
	if (!(lat_special || deg_special) && GMT->current.plot.r_theta_annot && lonlat)	/* Special check for the r in r-theta [set via -Jp|P +fe modifier] */
		gmt_sprintf_float (GMT, label, GMT->current.setting.format_float_map, val);
	else if (GMT->current.plot.calclock.geo.decimal)
		sprintf (label, GMT->current.plot.calclock.geo.format, val, hemi_post);
	else {
		(void) gmtlib_geo_to_dms (val, n_items, GMT->current.plot.calclock.geo.f_sec_to_int, &d, &m, &s, &m_sec);	/* Break up into d, m, s, and remainder */
		if (d == 0 && sign == -1) {	/* Must write out -0 degrees, do so by writing -1 and change 1 to 0 */
			d = -1;
			zero_fix = true;
		}
		if (hemi_pre[0]) strcpy (label, hemi_pre);
        use_format = (lonlat & 1 ? gmt_strrep (GMT->current.plot.format[level][type], "%3.3d", "%2.2d") :strdup (GMT->current.plot.format[level][type]));

		switch (2*level+type) {
			case 0:
				sprintf (text, use_format, d, hemi_post);
				break;
			case 1:
				sprintf (text, use_format, d, m_sec, hemi_post);
				break;
			case 2:
				sprintf (text, use_format, d, m, hemi_post);
				break;
			case 3:
				sprintf (text, use_format, d, m, m_sec, hemi_post);
				break;
			case 4:
				sprintf (text, use_format, d, m, s, hemi_post);
				break;
			case 5:
				sprintf (text, use_format, d, m, s, m_sec, hemi_post);
				break;
		}
		if (zero_fix) text[1] = '0';	/* Undo the fix above */
		strcat (label, text);
	}

	return;
}

/*! . */
int gmt_flip_justify (struct GMT_CTRL *GMT, unsigned int justify) {
	/* Return the mirror-image justification */

	int j;

	switch (justify) {
		case 1:	 j = 11;	break;
		case 2:	 j = 10;	break;
		case 3:	 j = 9;		break;
		case 5:	 j = 7;		break;
		case 6:	 j = 6;		break;
		case 7:	 j = 5;		break;
		case 9:  j = 3;		break;
		case 10: j = 2;		break;
		case 11: j = 1;		break;
		default:
			j = justify;
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "gmt_flip_justify called with incorrect argument (%d)\n", j);
			break;
	}

	return (j);
}

bool gmtlib_invalid_symbolname (struct GMT_CTRL *GMT, char *name) {
	/* Check that a symbol name only contains valid characters,
	 * which are the alphanumerics plus /, _, @, - and . (and :, \ for Windows) */
#ifdef WIN32
#define CUSTOM_EXTRA_CHAR "@_-/.:~\\"
#else
#define CUSTOM_EXTRA_CHAR "@_-/."
#endif

	char *text = strrchr (name ,'/');	/* Only check name of symbol, not leading directory */
	if (text == NULL) text = name;	/* No directory slash found - use entire name */
	for (unsigned int k = 0; k < strlen (name); k++) {
		if (!(isalnum (name[k]) || strchr (CUSTOM_EXTRA_CHAR, name[k]))) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Symbol name %s contains invalid character %c\n", name, name[k]);
			return (true);
		}
	}
	return (false);
}

/*! . */
struct GMT_CUSTOM_SYMBOL * gmtlib_get_custom_symbol (struct GMT_CTRL *GMT, char *name) {
	unsigned int i;
	int found = -1;

	/* First see if we already have loaded this symbol */

	for (i = 0; found == -1 && i < GMT->init.n_custom_symbols; i++) if (!strcmp (name, GMT->init.custom_symbol[i]->name)) found = i;

	if (found >= 0) return (GMT->init.custom_symbol[found]);	/* Return a previously loaded symbol */

	/* Check that symbol names is valid */

	if (gmtlib_invalid_symbolname (GMT, name)) return (NULL);

	/* Must load new symbol */

	GMT->init.custom_symbol = gmt_M_memory (GMT, GMT->init.custom_symbol, GMT->init.n_custom_symbols+1, struct GMT_CUSTOM_SYMBOL *);
	if (gmtsupport_init_custom_symbol (GMT, name, &(GMT->init.custom_symbol[GMT->init.n_custom_symbols]))) return NULL;

	return (GMT->init.custom_symbol[GMT->init.n_custom_symbols++]);
}

/*! . */
void gmtlib_free_custom_symbols (struct GMT_CTRL *GMT) {
	/* Free the allocated list of custom symbols */
	unsigned int i;

	if (GMT->init.n_custom_symbols == 0) return;
	for (i = 0; i < GMT->init.n_custom_symbols; i++)
		gmtsupport_free_one_custom_symbol (GMT, GMT->init.custom_symbol[i]);
	gmt_M_free (GMT, GMT->init.custom_symbol);
	GMT->init.n_custom_symbols = 0;
}

/*! . */
bool gmt_polygon_is_open (struct GMT_CTRL *GMT, double x[], double y[], uint64_t n) {
	/* Returns true if the first and last point is not identical */
	if (n < 3) return false;	/*	A single point or a line is by definition closed */
	if (y == NULL) return true;	/*	A single vector is by definition open */
	if (!doubleAlmostEqualZero (y[0], y[n-1]))
		return true;	/* y difference exceeds threshold: polygon is OPEN */
	if (!doubleAlmostEqualZero (x[0], x[n-1])) {	/* The x values exceeds threshold, check further if by 360 under geo */
		if (gmt_M_type (GMT, GMT_IN, GMT_X) & GMT_IS_GEO) {	/* Geographical coordinates: Worry about a 360 jump */
			double dlon = fabs (x[0] - x[n-1]);	/* If exactly 360 then we are OK */
			if (!doubleAlmostEqualZero (dlon, 360.0))
				return true;	/* x difference exceeds threshold for an exact 360 offset: polygon is OPEN */
		}
		else	/* Cartesian case */
			return true;	/* x difference exceeds threshold: polygon is OPEN */
	}
	/* Here, first and last are ~identical - to be safe we enforce exact closure */
	x[n-1] = x[0];	y[n-1] = y[0];	/* Note: For geo data, this step may change a 0 to 360 or vice versa */
	return false;	/* Passed the tests so polygon is CLOSED */
}

/*! . */
int gmt_polygon_centroid (struct GMT_CTRL *GMT, double *x, double *y, uint64_t n, double *Cx, double *Cy) {
	/* Compute polygon centroid location. */
	uint64_t i, last;
	double A, d, xold, yold;

	A = gmtsupport_polygon_area (GMT, x, y, n);
	last = (n > 2 && gmt_polygon_is_open (GMT, x, y, n)) ? n : n - 1;	/* Skip repeating vertex */
	*Cx = *Cy = 0.0;
	xold = x[last-1];	yold = y[last-1];
	for (i = 0; i < last; i++) {
		d = (xold * y[i] - x[i] * yold);
		*Cx += (x[i] + xold) * d;
		*Cy += (y[i] + yold) * d;
		xold = x[i];	yold = y[i];
	}
	*Cx /= (6.0 * A);
	*Cy /= (6.0 * A);
	return ((A < 0.0) ? -1 : +1);	/* -1 means CCW, +1 means CW */
}

/*! . */
openmp_int * gmt_prep_nodesearch (struct GMT_CTRL *GMT, struct GMT_GRID *G, double radius, unsigned int mode, openmp_int *d_row, openmp_int *actual_max_d_col) {
	/* When we search all nodes within a radius R on a grid, we first rule out nodes that are
	 * outside the circumscribing rectangle.  However, for geographic data the circle becomes
	 * elliptical in lon/lat space due to the cos(lat) shrinking of the length of delta_lon.
	 * Thus, while the +- width of nodes in y is fixed (d_row), the +-width of nodes in x
	 * is a function of latitude.  This is the array d_col (which is constant for Cartesian data).
	 * We expect gmt_init_distaz has been called so the gmt_distance function returns distances
	 * in the same units as the radius.  We also return the widest value in the d_col array via
	 * the actual_max_d_col value.
	 */
	openmp_int row, limit, *d_col = gmt_M_memory (GMT, NULL, G->header->n_rows, unsigned int);
	double dist_x, dist_y, lon, lat;

	lon = G->header->wesn[XLO] + G->header->inc[GMT_X];	/* One step in from west */
	limit = (G->header->registration == GMT_GRID_NODE_REG) ? G->header->n_columns - 1 : G->header->n_columns;
	/* Set limit on +/- delta cols */
	if (mode) {	/* Input data is geographical, so circle widens with latitude due to cos(lat) effect */
		*actual_max_d_col = 0;
		for (row = 0; row < (openmp_int)G->header->n_rows; row++) {
			lat = gmt_M_grd_row_to_y (GMT, row, G->header);
			/* Determine longitudinal width of one grid cell at this latitude */
			dist_x = gmt_distance (GMT, G->header->wesn[XLO], lat, lon, lat);
			d_col[row] = (fabs (lat) == 90.0) ? limit : urint (ceil (radius / dist_x) + 0.1);
			if (d_col[row] > limit) d_col[row] = limit;	/* No point exceeding the upper limit */
			if (d_col[row] > (*actual_max_d_col)) *actual_max_d_col = d_col[row];	/* Update the max range so far */
		}
	}
	else {	/* Plain Cartesian data with rectangular box and no latitude variation */
		dist_x = gmt_distance (GMT, G->header->wesn[XLO], G->header->wesn[YLO], lon, G->header->wesn[YLO]);
		*actual_max_d_col = urint (ceil (radius / dist_x) + 0.1);
		if (*actual_max_d_col > limit) *actual_max_d_col = limit;	/* No point exceeding the upper limit */
		for (row = 0; row < (openmp_int)G->header->n_rows; row++) d_col[row] = *actual_max_d_col;	/* Constant array */
	}

	/* Set fixed limit on +/- delta rows */
	dist_y = gmt_distance (GMT, G->header->wesn[XLO], G->header->wesn[YLO], G->header->wesn[XLO], G->header->wesn[YLO] + G->header->inc[GMT_Y]);
	*d_row = urint (ceil (radius / dist_y) + 0.1);	/* The constant half-width of nodes in y-direction */
	if (*d_row > G->header->n_rows) *d_row = G->header->n_rows;
	GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Max node-search half-widths are: half_x = %d, half_y = %d\n", *d_row, *actual_max_d_col);
	return (d_col);		/* The (possibly variable) half-width of nodes in x-direction as function of y */
}

/* These three functions are used by grdmath and gmtmath only */

/*! . */
int gmt_load_macros (struct GMT_CTRL *GMT, char *mtype, struct GMT_MATH_MACRO **M) {
	/* Load in any gmt/grdmath macros.  These records are of the format
	 * MACRO = ARG1 ARG2 ... ARGN [ : comments on what they do]
	 * The comments, if present, must be preceded by :<space> to distinguish
	 * the flag from any dd:mm:ss or hh:mm:ss constants used in the macro. */

	unsigned int n = 0, k = 0, pos = 0;
	size_t n_alloc = 0;
	char line[GMT_BUFSIZ] = {""}, name[GMT_LEN64] = {""}, item[GMT_LEN64] = {""}, args[GMT_BUFSIZ] = {""}, *c = NULL;
	struct GMT_MATH_MACRO *macro = NULL;
	FILE *fp = NULL;

	if (!gmtlib_getuserpath (GMT, mtype, line)) return (0);

	if ((fp = fopen (line, "r")) == NULL) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Unable to open %s macro file\n", line);
		return -1;
	}

	while (fgets (line, GMT_BUFSIZ, fp)) {
		if (line[0] == '#') continue;
		gmt_chop (line);
		if (gmt_is_a_blank_line (line)) continue;
		if ((c = strstr (line, ": ")))	/* This macro has comments */
			c[0] = '\0';		/* Chop off the comments */
		gmt_strstrip (line, true);	/* Remove leading and trailing whitespace */
		sscanf (line, "%s = %[^\n]", name, args);	/* Get name and everything else */
		if (n == n_alloc) macro = gmt_M_memory (GMT, macro, n_alloc += GMT_TINY_CHUNK, struct GMT_MATH_MACRO);
		macro[n].name = strdup (name);
		pos = 0;
		while (gmt_strtok (args, " \t", &pos, item)) macro[n].n_arg++;		/* Count the arguments */
		macro[n].arg = gmt_M_memory (GMT, macro[n].arg, macro[n].n_arg, char *);	/* Allocate pointers for args */
		pos = k = 0;
		while (gmt_strtok (args, " \t", &pos, item)) macro[n].arg[k++] = strdup (item);	/* Assign arguments */
		n++;
	}
	fclose (fp);
	if (n < n_alloc) macro = gmt_M_memory (GMT, macro, n, struct GMT_MATH_MACRO);

	*M = macro;
	return (n);
}

/*! . */
int gmt_find_macro (char *arg, unsigned int n_macros, struct GMT_MATH_MACRO *M) {
	/* See if the arg matches the name of a macro; return its ID or -1 */

	unsigned int n;

	if (n_macros == 0 || !M) return (GMT_NOTSET);

	for (n = 0; n < n_macros; n++) if (!strcmp (arg, M[n].name)) return (n);

	return (GMT_NOTSET);
}

/*! . */
void gmt_free_macros (struct GMT_CTRL *GMT, unsigned int n_macros, struct GMT_MATH_MACRO **M) {
	/* Free space allocated for macros */

	unsigned int n, k;

	if (n_macros == 0 || !(*M)) return;

	for (n = 0; n < n_macros; n++) {
		gmt_M_str_free ((*M)[n].name);
		for (k = 0; k < (*M)[n].n_arg; k++) gmt_M_str_free ((*M)[n].arg[k]);	/* Free arguments */
		gmt_M_free (GMT, (*M)[n].arg);	/* Free argument list */
	}
	gmt_M_free (GMT, (*M));
}

/*! . */
struct GMT_OPTION *gmt_substitute_macros (struct GMT_CTRL *GMT, struct GMT_OPTION *options, char *mfile) {
	unsigned int n_macros, kk;
	int k;
	struct GMT_MATH_MACRO *M = NULL;
	struct GMT_OPTION *opt = NULL, *ptr = NULL, *list = NULL;
	struct GMTAPI_CTRL *API = GMT->parent;

	n_macros = gmt_load_macros (GMT, mfile, &M);	/* Load in any macros */
	if (n_macros) GMT_Report (API, GMT_MSG_INFORMATION, "Found and loaded %d user macros.\n", n_macros);

	/* Expand any macro with its building blocks */

	for (opt = options; opt; opt = opt->next) {
		if (opt->option == GMT_OPT_INFILE && (k = gmt_find_macro (opt->arg, n_macros, M)) != GMT_NOTSET) {
			/* Add in the replacement commands from the macro */
			for (kk = 0; kk < M[k].n_arg; kk++) {
				ptr = GMT_Make_Option (API, GMT_OPT_INFILE, M[k].arg[kk]);
				if ((list = GMT_Append_Option (API, ptr, list)) == NULL) {
					gmt_free_macros (GMT, n_macros, &M);
					return (NULL);
				}
				if (ptr->arg[0] == '-' && (isalpha (ptr->arg[1]) || ptr->arg[1] == '-')) {
					ptr->option = ptr->arg[1];	/* Change from "file" to an option */
					gmt_strlshift (ptr->arg, 2U);	/* Remove the leading -? part */
				}
			}
			continue;
		}
		else
			ptr = GMT_Make_Option (API, opt->option, opt->arg);

		if (ptr == NULL || (list = GMT_Append_Option (API, ptr, list)) == NULL) {
			gmt_free_macros (GMT, n_macros, &M);
			return (NULL);
		}
	}
	gmt_free_macros (GMT, n_macros, &M);

	return (list);
}

/*! . */
void gmtlib_init_rot_matrix (double R[3][3], double E[]) {
	/* This starts setting up the matrix without knowing the angle of rotation
	 * Call set_rot_angle with R, and omega to complete the matrix
	 * P	Cartesian 3-D vector of rotation pole
	 * R	the rotation matrix without terms depending on omega
	 * See Cox and Hart [1985] Box ?? for details.
	 */

	R[0][0] = E[0] * E[0];
	R[1][1] = E[1] * E[1];
	R[2][2] = E[2] * E[2];
	R[0][1] = R[1][0] = E[0] * E[1];
	R[0][2] = R[2][0] = E[0] * E[2];
	R[1][2] = R[2][1] = E[1] * E[2];
}

/*! . */
void gmtlib_load_rot_matrix (double w, double R[3][3], double E[]) {
	/* Sets R using R(no_omega) and the given rotation angle w in radians */
	double sin_w, cos_w, c, E_x, E_y, E_z;

	sincos (w, &sin_w, &cos_w);
	c = 1.0 - cos_w;

	E_x = E[0] * sin_w;
	E_y = E[1] * sin_w;
	E_z = E[2] * sin_w;

	R[0][0] = R[0][0] * c + cos_w;
	R[0][1] = R[0][1] * c - E_z;
	R[0][2] = R[0][2] * c + E_y;

	R[1][0] = R[1][0] * c + E_z;
	R[1][1] = R[1][1] * c + cos_w;
	R[1][2] = R[1][2] * c - E_x;

	R[2][0] = R[2][0] * c - E_y;
	R[2][1] = R[2][1] * c + E_x;
	R[2][2] = R[2][2] * c + cos_w;
}

#if 0
/*! . */
void gmt_matrix_vect_mult (double a[3][3], double b[3], double c[3]) {
	/* c = A * b */
	int i, j;

	for (i = 0; i < 3; i++) for (j = 0, c[i] = 0.0; j < 3; j++) c[i] += a[i][j] * b[j];
}
#endif

/*! . */
struct GMT_DATASET * gmt_segmentize_data (struct GMT_CTRL *GMT, struct GMT_DATASET *Din, struct GMT_SEGMENTIZE *S) {
	/* Din is a data set with any number of tables and segments and records.
	 * On output we return a pointer to new dataset in which all points in Din are used to
	 * form 2-point line segments.  So output will have lots of segments, all of length 2,
	 * and all these segments are placed in the first (and only) output table.
	 * There are several forms of segmentization:
	 * 1) -Fc: Continuous lines.  By default, lines are drawn on a segment by segment basis.
	 *    Thus, -F or -Fc or -Fcs or -Fs is the same as the input and is not allowed.  However, if we use
	 *    -Fcf or -Ff then we ignore segment headers WITHIN each file, except for the first header
	 *   in each file.  In other words, all points in a file will be considered continuous.
	 *   Finally, using -Fca or -Fa then all points in all fields are considered continuous and
	 *   only the first segment header in the first file is considered.
	 * 2) -Fn: Network.  For each group of points we connect each point with every other point.
	 *   The modifiers a,f,s control what the "group" is.  With s, we construct a separate
	 *   network for each segment, with f we group all segments in a file and construct a
	 *   network for all those points, while with a with consider all points in the dataset
	 *   to be one group.
	 * 3) -Fr: Ref point.  Here, we construct line segments from the given reference point to
	 *   each of the points in the file.  If refpoint is given as two slash-separated coordinates
	 *   then the refpoint is fixed throughout this construction.  However, refpoint may also be
	 *   given as a, f, s and if so we pick the first point in the dataset, or first point in each
	 *   file, or the first point in each segment to update the actual reference point.
	 * 4) -Fv: Vectorize.  Here, consecutive points are turned into vector segments such as used
	 *   by psxy -Sv|=<size>+s or external applications.  Again, appending a|t|s controls if we should
	 *   honor the segment headers [Default is -Fvs if -Fv is given].
	 */
	uint64_t dim[GMT_DIM_SIZE] = {1, 0, 2, 0};	/* Put everything in one table, each segment has 2 points */
	uint64_t tbl, seg, row, col, new_seg;
	unsigned int smode;
	double *data = NULL;
	struct GMT_DATASET *D = NULL;
	struct GMT_DATATABLE *Tin = NULL, *Tout = NULL;

	dim[GMT_COL] = Din->n_columns;	/* Same number of columns as input dataset */
	dim[GMT_ROW] = 2;		/* Two per segment unless for continuous mode */
	/* Determine how many total segments will be created */
	switch (S->method) {
		case SEGM_CONTINUOUS:
			switch (S->level) {
				case SEGM_DATASET:	/* Everything is just one long segment */
					dim[GMT_SEG] = 1;
					dim[GMT_ROW] = Din->n_records;
					break;
				case SEGM_TABLE:	/* Turn all segments in a table into one */
					dim[GMT_SEG] = Din->n_tables;
					dim[GMT_ROW] = 0;	/* Must do this per segment */
					break;
				case SEGM_RECORD:	/* Turn all points into individual points with segment headers */
					dim[GMT_SEG] = Din->n_records;
					dim[GMT_ROW] = 1;	/* Must do this per segment */
					break;
			}
			break;
		case SEGM_REFPOINT:
			switch (S->level) {
				case SEGM_ORIGIN:	/* External origin, so n_records points remain */
					dim[GMT_SEG] = Din->n_records;
					break;
				case SEGM_DATASET:	/* Reset origin to first point in dataset, so n_records-1 points remains */
					dim[GMT_SEG] = Din->n_records - 1;
					break;
				case SEGM_TABLE:	/* Reset origin to first point in table, so n_records-1 points remains */
					for (tbl = 0; tbl < Din->n_tables; tbl++)
						dim[GMT_SEG] += (Din->table[tbl]->n_records - 1);
					break;
				case SEGM_RECORD:	/* Reset origin per point */
				case SEGM_SEGMENT:	/* Reset origin to first point in each segment, so n_rows-1 points remains per segment */
					for (tbl = 0; tbl < Din->n_tables; tbl++) {
						Tin = Din->table[tbl];
						for (seg = 0; seg < Tin->n_segments; seg++)	/* For each segment to resample */
							dim[GMT_SEG] += Tin->segment[seg]->n_rows - 1;
					}
					dim[GMT_SEG] = Din->n_records;
					break;
			}
			data = gmt_M_memory (GMT, NULL, dim[GMT_COL], double);
			break;
		case SEGM_NETWORK:
			switch (S->level) {
				case SEGM_DATASET:	/* Make a single network */
					dim[GMT_SEG] = (Din->n_records * (Din->n_records - 1)) / 2;
					break;
				case SEGM_TABLE:	/* Make a new network for each table */
					for (tbl = 0; tbl < Din->n_tables; tbl++)
						dim[GMT_SEG] += (Din->table[tbl]->n_records * (Din->table[tbl]->n_records - 1)) / 2;
					break;
				case SEGM_SEGMENT:	/* Make a new network for each segment */
					for (tbl = 0; tbl < Din->n_tables; tbl++) {
						Tin = Din->table[tbl];
						for (seg = 0; seg < Tin->n_segments; seg++)	/* For each segment to resample */
							dim[GMT_SEG] += (Tin->segment[seg]->n_rows *(Tin->segment[seg]->n_rows - 1)) / 2;
					}
			}
			break;
		case SEGM_VECTOR:
			dim[GMT_COL] *= 2;	/* Since we are putting two records on the same line */
			switch (S->level) {
				case SEGM_DATASET:	/* Ignore all headers, so n_records-1 pairs remains forming one segment */
					dim[GMT_SEG] = 1;
					dim[GMT_ROW] = Din->n_records - 1;	/* Must do this per segment */
					break;
				case SEGM_TABLE:	/* Ignore all but first header in table, so n_records-1 pairs per table remains */
					dim[GMT_SEG] = Din->n_tables;
					dim[GMT_ROW] = 0;	/* Must do this per segment */
					break;
				case SEGM_SEGMENT:	/* Process per segment segment, so n_rows-1 pairs remains per segment */
					dim[GMT_SEG] = 	Din->n_segments;
					dim[GMT_ROW] = 0;	/* Must do this per segment */
					break;
			}
			data = gmt_M_memory (GMT, NULL, dim[GMT_COL], double);
			break;
	}
	if (S->method == SEGM_CONTINUOUS)
		GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Segmentize input data into %" PRIu64 " variable-length segment lines\n", dim[GMT_SEG]);
	else
		GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Segmentize input data into %" PRIu64 " 2-point segment lines\n", dim[GMT_SEG]);

	/* Allocate the dataset with one large table */
	if ((D = GMT_Create_Data (GMT->parent, GMT_IS_DATASET, GMT_IS_LINE, 0, dim, NULL, NULL, 0, 0, NULL)) == NULL) {
		gmt_M_free (GMT, data);
		return (NULL);	/* Our new dataset */
	}
	Tout = D->table[0];	/* The only output table */

	if (S->method == SEGM_NETWORK) {	/* Make segments that connect every point with every other point */
		struct GMT_DATATABLE *Tin2 = NULL;
		uint64_t tbl2, seg2, row2;
		bool same[2] = {false, false};
		for (tbl = new_seg = 0; tbl < Din->n_tables; tbl++) {
			Tin = Din->table[tbl];	/* First input table */
			for (tbl2 = tbl; tbl2 < Din->n_tables; tbl2++) {
				if (S->level != SEGM_DATASET && tbl2 != tbl) continue;	/* Not working across tables */
				Tin2 = Din->table[tbl2];	/* Second input table (but might be the same as Tin1) */
				same[0] = (tbl == tbl2);
				for (seg = 0; seg < Tin->n_segments; seg++) {	/* For each input segment to resample */
					for (seg2 = (same[0]) ? seg : 0; seg2 < Tin2->n_segments; seg2++) {	/* For each input segment to resample */
						same[1] = (same[0] && seg == seg2);	/* So same[1] is only true for identical segments from same table */
						if (S->level == SEGM_SEGMENT && !same[1] ) continue;	/* Not working across segments */
						for (row = 0; row < Tin->segment[seg]->n_rows; row++) {	/* For each end point in the new 2-point segments */
							for (row2 = (same[1]) ? row+1 : 0; row2 < Tin2->segment[seg2]->n_rows; row2++, new_seg++) {	/* For each end point in the new 2-point segments */
								if (Tin->segment[seg]->header) Tout->segment[new_seg]->header = strdup (Tin->segment[seg]->header);	/* Duplicate first segment header in table */
								for (col = 0; col < Tin->segment[seg]->n_columns; col++) {	/* For every column */
									Tout->segment[new_seg]->data[col][0] = Tin->segment[seg]->data[col][row];
									Tout->segment[new_seg]->data[col][1] = Tin2->segment[seg2]->data[col][row2];
								}
							}
						}
					}
				}
			}
		}
	}
	else if (S->method == SEGM_VECTOR) {	/* Turn lines into a series of x0 y0 ... x1 y1 ... records, e.g., for psxy -Sv+s */
		uint64_t new_row, seg2, off = 0;
		if (S->level == SEGM_DATASET) {	/* Duplicate very first segment header only */
			if (Din->table[0]->segment[0]->header) Tout->segment[0]->header = strdup (Din->table[0]->segment[0]->header);
		}
		for (tbl = new_row = seg2 = 0; tbl < Din->n_tables; tbl++) {
			Tin = Din->table[tbl];	/* Current input table */
			if (S->level == SEGM_TABLE) {	/* Must allocate Tin->n_records for the output table's next segment (one per input table) */
				smode = (Tin->segment[0]->text) ? GMT_WITH_STRINGS : 0;
				gmt_alloc_segment (GMT, Tout->segment[seg2], Tin->n_records-1, Tout->n_columns, smode, false);
				if (Tin->segment[0]->header) Tout->segment[seg2]->header = strdup (Tin->segment[0]->header);	/* Duplicate first segment header in table */
			}
			for (seg = 0; seg < Tin->n_segments; seg++) {	/* For each input segment to resample */
				off = 0;
				if (new_row == 0) {	/* Update the first row */
					for (col = 0; col < Tin->segment[seg]->n_columns; col++) data[col] = Tin->segment[seg]->data[col][0];
					if (Tin->segment[seg]->header) Tout->segment[seg2]->header = strdup (Tin->segment[seg]->header);
					off = 1;
				}
				if (S->level == SEGM_SEGMENT) {	/* Must allocate Tin->n_records for the output table's next segment (one per input table) */
					smode = (Tin->segment[seg]->text) ? GMT_WITH_STRINGS : 0;
					gmt_alloc_segment (GMT, Tout->segment[seg2], Tin->segment[seg]->n_rows-1, Tout->n_columns, smode, false);
					if (Tin->segment[seg]->header) Tout->segment[seg2]->header = strdup (Tin->segment[seg]->header);	/* Duplicate each segment header in table */
				}
				for (row = off; row < Tin->segment[seg]->n_rows; row++, new_row++) {	/* For each end point in the new 2-point segments */
					for (col = 0; col < Tin->segment[seg]->n_columns; col++) {	/* For every column */
						Tout->segment[seg2]->data[col][new_row] = data[col];
						data[col] = Tout->segment[seg2]->data[Din->n_columns+col][new_row] = Tin->segment[seg]->data[col][row];		/* 2nd point */
					}
				}
				if (S->level == SEGM_SEGMENT) {
					Tout->segment[seg2]->n_rows = new_row;
					seg2++;	/* Goto next output segment after each input segment */
					new_row = 0;
				}
			}
			if (S->level == SEGM_TABLE) {	/* Goto next output segment after each table */
				Tout->segment[seg2]->n_rows = new_row;
				seg2++;	/* Goto next output segment after each input segment */
				new_row = 0;
			}
		}
		if (S->level == SEGM_DATASET) {	/* Wrap up the lone segment */
			Tout->segment[0]->n_rows = new_row;
		}
		gmt_M_free (GMT, data);
	}
	else if (S->method == SEGM_CONTINUOUS) {	/* Basically remove various segment boundaries */
		uint64_t seg2, new_row = 0;
		if (S->level == SEGM_DATASET) {	/* Duplicate very first segment header only */
			if (Din->table[0]->segment[0]->header) Tout->segment[0]->header = strdup (Din->table[0]->segment[0]->header);
		}
		for (tbl = seg2 = new_row = 0; tbl < Din->n_tables; tbl++) {
			Tin = Din->table[tbl];	/* Current input table */
			if (S->level == SEGM_TABLE) {	/* Must allocate Tin->n_records for the output table's next segment (one per input table) */
				smode = (Tin->segment[0]->text) ? GMT_WITH_STRINGS : 0;
				gmt_alloc_segment (GMT, Tout->segment[tbl], Tin->n_records, Tin->n_columns, smode, false);
				new_row = 0;	/* Reset output count for this output segment */
				if (Tin->segment[0]->header) Tout->segment[seg2]->header = strdup (Tin->segment[0]->header);	/* Duplicate first segment header in table */
			}
			for (seg = 0; seg < Tin->n_segments; seg++) {	/* For each input segment to resample */
				for (col = 0; col < Tin->segment[seg]->n_columns; col++) {	/* For every column */
					gmt_M_memcpy (&Tout->segment[seg2]->data[col][new_row], Tin->segment[seg]->data[col], Tin->segment[seg]->n_rows, double);
				}
				new_row += Tin->segment[seg]->n_rows;
			}
			if (S->level == SEGM_TABLE) {
				Tout->segment[seg2]->n_rows = new_row;
				seg2++;	/* Goto next output segment */
			}
		}
	}
	else if (S->method == SEGM_REFPOINT) {	/* Make segment lines from various origins to each point */
		uint64_t off = 0;
		if (S->level == SEGM_ORIGIN) gmt_M_memcpy (data, S->origin, 2, double);	/* Initialize the origin of segments once */
		if (S->level == SEGM_DATASET) {	/* Duplicate very first segment header only */
			for (col = 0; col < Din->n_columns; col++) data[col] = Din->table[0]->segment[0]->data[col][0];
			if (Din->table[0]->segment[0]->header) Tout->segment[0]->header = strdup (Din->table[0]->segment[0]->header);
			off = 1;
		}
		for (tbl = new_seg = 0; tbl < Din->n_tables; tbl++) {
			Tin = Din->table[tbl];	/* Current input table */
			if (S->level == SEGM_TABLE) {	/* Initialize the origin as 1st point in this table (or for each table) */
				for (col = 0; col < Din->n_columns; col++) data[col] = Tin->segment[0]->data[col][0];
				if (Tin->segment[0]->header) Tout->segment[new_seg]->header = strdup (Tin->segment[0]->header);	/* Duplicate first segment header in table */
				off = 1;
			}
			for (seg = 0; seg < Tin->n_segments; seg++) {	/* For each input segment to resample */
				if (S->level == SEGM_SEGMENT || S->level == SEGM_RECORD) {	/* Initialize the origin as 1st point in segment */
					for (col = 0; col < Din->n_columns; col++) data[col] = Tin->segment[seg]->data[col][0];
					off = 1;
				}
				for (row = off; row < Tin->segment[seg]->n_rows; row++, new_seg++) {	/* For each end point in the new 2-point segments */
					if (Tin->segment[seg]->header) Tout->segment[new_seg]->header = strdup (Tin->segment[seg]->header);	/* Duplicate first segment header in table */
					for (col = 0; col < Tin->segment[seg]->n_columns; col++) {	/* For every column */
						Tout->segment[new_seg]->data[col][0] = data[col];				/* 1st point */
						Tout->segment[new_seg]->data[col][1] = Tin->segment[seg]->data[col][row];	/* 2nd point */
						if (S->level == SEGM_RECORD) data[col] = Tin->segment[seg]->data[col][row];	/* Update 1st point again */
					}
				}
				off = 0;
			}
		}
		gmt_M_free (GMT, data);
	}
	gmt_set_dataset_minmax (GMT, D);	/* Determine min/max for each column */

	return (D);
}

/*! . */
struct GMT_DATASET * gmt_resample_data (struct GMT_CTRL *GMT, struct GMT_DATASET *Din, double along_ds,  unsigned int mode, unsigned int ex_cols, enum GMT_enum_track smode) {
	/* Din is a data set with at least two columns (x,y or lon/lat);
	 * it can contain any number of tables and segments with lines.
	 * along_ds is the resampling interval along the traces in Din.
	 * It is in the current distance units (set via gmt_init_distaz).
	 * mode is either 0 (just lon,lat), 1 (lon,lat,dist) or 2 (lon,lat,dist,azim)
	 * ex_cols makes space for this many extra empty data columns [0].
	 * smode sets the sampling mode for the track:
	 * smode = GMT_TRACK_FILL	: Keep input points; add intermediates if any gap exceeds step_out.
	 * smode = GMT_TRACK_FILL_M	: Same, but traverse along meridians, then parallels between points.
	 * smode = GMT_TRACK_FILL_P	: Same, but traverse along parallels, then meridians between points.
	 * smode = GMT_TRACK_SAMPLE_FIX	: Resample track equidistantly; old points may be lost. Use given spacing.
	 * smode = GMT_TRACK_SAMPLE_ADJ	: Resample track equidistantly; old points may be lost. Adjust spacing to fit tracklength exactly.
	 *
	 * Dout is the new data set with all the resampled lines;
	 */
	struct GMT_DATASET *D = NULL;
	if (gmt_M_is_geographic (GMT, GMT_IN))
		D = gmtsupport_resample_data_spherical (GMT, Din, along_ds, mode, ex_cols, smode);
	else
		D = gmtsupport_resample_data_cartesian (GMT, Din, along_ds, mode, ex_cols, smode);
	gmt_set_dataset_minmax (GMT, D);	/* Determine min/max for each column */
	return (D);
}

/*! . */
struct GMT_DATASET * gmt_crosstracks (struct GMT_CTRL *GMT, struct GMT_DATASET *Din, double cross_length, double across_ds, double deviation, uint64_t n_cols, unsigned int mode, char unit) {
	/* Call either the spherical or Cartesian version */
	struct GMT_DATASET *D = NULL;
	if (gmt_M_is_geographic (GMT, GMT_IN))
		D = gmtsupport_crosstracks_spherical (GMT, Din, cross_length, across_ds, deviation, n_cols, mode, unit);
	else
		D = gmtsupport_crosstracks_cartesian (GMT, Din, cross_length, across_ds, deviation, n_cols, mode, unit);
	gmt_set_dataset_minmax (GMT, D);	/* Determine min/max for each column */
	return (D);
}

/*! . */
bool gmt_crossing_dateline (struct GMT_CTRL *GMT, struct GMT_DATASEGMENT *S) {
	/* Return true if this line or polygon feature contains points on either side of the Dateline */
	uint64_t k;
	bool east = false, west = false, cross = false;
	gmt_M_unused(GMT);
	for (k = 0; !cross && k < S->n_rows; k++) {
		if ((S->data[GMT_X][k] > 180.0 && S->data[GMT_X][k] < 270.0) || (S->data[GMT_X][k] > -180.0 && S->data[GMT_X][k] <  -90.0)) west = true;
		if ((S->data[GMT_X][k] >  90.0 && S->data[GMT_X][k] < 180.0) || (S->data[GMT_X][k] > -270.0 && S->data[GMT_X][k] < -180.0)) east = true;
		if (east && west) cross = true;
	}
	return (cross);
}

/*! . */
unsigned int gmtlib_split_line_at_dateline (struct GMT_CTRL *GMT, struct GMT_DATASEGMENT *S, struct GMT_DATASEGMENT ***Lout) {
	/* Create two or more feature segments by splitting them across the Dateline.
	 * gmtlib_split_line_at_dateline should ONLY be called when we KNOW we must split. */
	unsigned int n_split;
	unsigned int smode = (S->text) ? GMT_WITH_STRINGS : 0;
	uint64_t k, col, seg, row, start, length, *pos = gmt_M_memory (GMT, NULL, S->n_rows, uint64_t);
	char label[GMT_BUFSIZ] = {""}, *txt = NULL, *feature = "Line";
	double r;
	struct GMT_DATASEGMENT **L = NULL, *Sx = gmt_get_segment (GMT, S->n_columns);
	struct GMT_DATASEGMENT_HIDDEN *LH = NULL, *SH = gmt_get_DS_hidden (S);

	for (k = 0; k < S->n_rows; k++) gmt_lon_range_adjust (GMT_IS_0_TO_P360_RANGE, &S->data[GMT_X][k]);	/* First enforce 0 <= lon < 360 so we don't have to check again */
	gmt_alloc_segment (GMT, Sx, 2*S->n_rows, S->n_columns, smode, true);	/* Temp segment with twice the number of points as we will add crossings*/

	for (k = row = n_split = 0; k < S->n_rows; k++) {	/* Hunt for crossings */
		if (k && gmtsupport_straddle_dateline (S->data[GMT_X][k-1], S->data[GMT_X][k])) {	/* Crossed Dateline */
			r = (180.0 - S->data[GMT_X][k-1]) / (S->data[GMT_X][k] - S->data[GMT_X][k-1]);	/* Fractional distance from k-1'th point to 180 crossing */
			Sx->data[GMT_X][row] = 180.0;	/* Exact longitude is known */
			for (col = 1; col < S->n_columns; col++) Sx->data[col][row] = S->data[col][k-1] + r * (S->data[col][k] - S->data[col][k-1]);	/* Linear interpolation for other fields */
			pos[n_split++] = row++;		/* Keep track of first point (the crossing) in new section */
		}
		for (col = 0; col < S->n_columns; col++) Sx->data[col][row] = S->data[col][k];	/* Append the current point */
		row++;
	}
	Sx->n_rows = row;	/* Number of points in extended feature with explicit crossings */
	if (n_split == 0) {	/* No crossings, should not have been called in the first place */
		GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "No need to insert new points at 180\n");
		gmt_free_segment (GMT, &Sx);
		gmt_M_free (GMT, pos);
		return 0;
	}
	pos[n_split] = Sx->n_rows - 1;
	n_split++;	/* Now means number of segments */
	L = gmt_M_memory (GMT, NULL, n_split, struct GMT_DATASEGMENT *);	/* Number of output segments needed are allocated here */
	txt = (S->label) ? S->label : feature;	/* What to label the features */
	start = 0;
	for (seg = 0; seg < n_split; seg++) {	/* Populate the output segment coordinate arrays */
		length = pos[seg] - start + 1;	/* Length of new segment */
		L[seg] = GMT_Alloc_Segment (GMT->parent, smode, length, S->n_columns, S->header, NULL);	/* Allocate array space for coordinates */
		LH = gmt_get_DS_hidden (L[seg]);
		for (col = 0; col < S->n_columns; col++) gmt_M_memcpy (L[seg]->data[col], &(Sx->data[col][start]), length, double);	/* Copy coordinates */
		LH->range = (L[seg]->data[GMT_X][length/2] > 180.0) ? GMT_IS_M180_TO_P180 : GMT_IS_M180_TO_P180_RANGE;	/* Formatting ID to enable special -180 and +180 formatting on output */
		/* Modify label to part number */
		sprintf (label, "%s part %" PRIu64, txt, seg);
		L[seg]->label = strdup (label);
		if (SH->ogr) gmt_duplicate_ogr_seg (GMT, L[seg], S);
		start = pos[seg];
	}
	gmt_free_segment (GMT, &Sx);
	gmt_M_free (GMT, pos);

	*Lout = L;		/* Pass pointer to the array of segments */

	return (n_split);	/* Return how many segments was made */
}

/*! . */
char *gmt_putusername (struct GMT_CTRL *GMT) {
	/* Calling function must free the result */
	static char *unknown = "unknown";
	gmt_M_unused(GMT);
#ifdef HAVE_GETPWUID
#include <pwd.h>
	struct passwd *pw = NULL;
	pw = getpwuid (getuid ());
	if (pw) return (strdup (pw->pw_name));
#endif
#ifdef WIN32
	{
		char name[GMT_LEN256] = {""}, *U = NULL;
		DWORD Size = (DWORD)_tcslen (name);
		if (GetUserName (name, &Size)) /* Got a user name, return it */
			return (strdup (name));
		if ((U = getenv ("USERNAME")))	/* Got a name from the environment instead */
			return (strdup (U));
	}
#endif
	return (strdup (unknown));
}

/* Various functions from surface that are now used elsewhere as well */

/*! . */
unsigned int gmt_gcd_euclid (unsigned int a, unsigned int b) {
	/* Returns the greatest common divisor of u and v by Euclid's method.
	 * I have experimented also with Stein's method, which involves only
	 * subtraction and left/right shifting; Euclid is faster, both for
	 * integers of size 0 - 1024 and also for random integers of a size
	 * which fits in a long integer.  Stein's algorithm might be better
	 * when the integers are HUGE, but for our purposes, Euclid is fine.
	 *
	 * Walter H. F. Smith, 25 Feb 1992, after D. E. Knuth, vol. II  */

	unsigned int u, v, r;

	u = MAX (a, b);
	v = MIN (a, b);

	while (v > 0) {
		r = u % v;	/* Knuth notes that u < 2v 40% of the time;  */
		u = v;		/* thus we could have tried a subtraction  */
		v = r;		/* followed by an if test to do r = u%v  */
	}
	return (u);
}

/*! . */
unsigned int gmt_optimal_dim_for_surface (struct GMT_CTRL *GMT, unsigned int factors[], unsigned int n_columns, unsigned int n_rows, struct GMT_SURFACE_SUGGESTION **S) {
	/* Calls gmtsupport_guess_surface_time for a variety of trial grid
	 * sizes, where the trials are highly composite numbers
	 * with lots of factors of 2, 3, and 5.  The sizes are
	 * within the range (n_columns,n_rows) - (2*n_columns, 2*n_rows).  Prints to
	 * GMT->session.std[GMT_ERR] the values which are an improvement over the
	 * user's original n_columns,n_rows.
	 * Should be called with n_columns=(x_max-x_min)/dx, and ditto
	 * for n_rows; that is, one smaller than the lattice used
	 * in surface.c
	 *
	 * W. H. F. Smith, 26 Feb 1992.  */

	double users_time;	/* Time for user's n_columns, n_rows  */
	double current_time;	/* Time for current nxg, nyg  */
	unsigned int nxg, nyg;	/* Guessed by this routine  */
	unsigned int nx2, ny2, nx3, ny3, nx5, ny5;	/* For powers  */
	unsigned int xstop, ystop;	/* Set to 2*n_columns, 2*n_rows  */
	unsigned int n_sug = 0;	/* N of suggestions found  */
	struct GMT_SURFACE_SUGGESTION *sug = NULL;

	users_time = gmtsupport_guess_surface_time (GMT, factors, n_columns, n_rows);
	xstop = 2*n_columns;
	ystop = 2*n_rows;

	for (nx2 = 2; nx2 <= xstop; nx2 *= 2) {
		for (nx3 = 1; nx3 <= xstop; nx3 *= 3) {
			for (nx5 = 1; nx5 <= xstop; nx5 *= 5) {
				nxg = nx2 * nx3 * nx5;
				if (nxg < n_columns || nxg > xstop) continue;

				for (ny2 = 2; ny2 <= ystop; ny2 *= 2) {
					for (ny3 = 1; ny3 <= ystop; ny3 *= 3) {
						for (ny5 = 1; ny5 <= ystop; ny5 *= 5) {
							nyg = ny2 * ny3 * ny5;
							if (nyg < n_rows || nyg > ystop) continue;

							current_time = gmtsupport_guess_surface_time (GMT, factors, nxg, nyg);
							if (current_time < users_time) {
								n_sug++;
								sug = gmt_M_memory (GMT, sug, n_sug, struct GMT_SURFACE_SUGGESTION);
								sug[n_sug-1].n_columns = nxg;
								sug[n_sug-1].n_rows = nyg;
								sug[n_sug-1].factor = users_time/current_time;
							}

						}
					}
				}
			}
		}
	}

	if (n_sug) {
		qsort (sug, n_sug, sizeof (struct GMT_SURFACE_SUGGESTION), gmtsupport_compare_sugs);
		*S = sug;
	}

	return n_sug;
}

/*! . */
int gmt_best_dim_choice (struct GMT_CTRL *GMT, unsigned int mode, unsigned int in_dim[], unsigned int out_dim[]) {
	/* Depending on mode, returns the closest out_dim >= in_dim that will speed up computations
	 * in surface (mode = 1) or for FFT work (mode = 2).  We return 0 if we found a better
	 * choice or 1 if the in_dim is the best choice. */
	int retval = 0;
	gmt_M_memcpy (out_dim, in_dim, 2U, unsigned int);	/* Default we return input if we cannot find anything better */

	if (mode == 1) {
		struct GMT_SURFACE_SUGGESTION *S = NULL;
		unsigned int factors[32], n_sugg = gmt_optimal_dim_for_surface (GMT, factors, in_dim[GMT_X], in_dim[GMT_Y], &S);
		if (n_sugg) {
			out_dim[GMT_X] = S[0].n_columns;
			out_dim[GMT_Y] = S[0].n_rows;
			gmt_M_free (GMT, S);
		}
		else
			retval = 1;
	}
	else if (mode == 2) {
		struct GMT_FFT_SUGGESTION fft_sug[GMT_FFT_N_SUGGEST];
		gmtlib_suggest_fft_dim (GMT, in_dim[GMT_X], in_dim[GMT_Y], fft_sug, false);
		if (fft_sug[GMT_FFT_ACCURATE].totalbytes < fft_sug[GMT_FFT_FAST].totalbytes) {
			/* The most accurate solution needs same or less storage
			 * as the fastest solution; use the most accurate's dimensions */
			out_dim[GMT_X] = fft_sug[GMT_FFT_ACCURATE].n_columns;
			out_dim[GMT_Y] = fft_sug[GMT_FFT_ACCURATE].n_rows;
		}
		else {	/* Use the sizes of the fastest solution  */
			out_dim[GMT_X] = fft_sug[GMT_FFT_FAST].n_columns;
			out_dim[GMT_Y] = fft_sug[GMT_FFT_FAST].n_rows;
		}
	}
	else {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Bad mode: %u Must select either 1 or 2\n", mode);
		retval = -1;
	}
	return (retval);
}

/*! . */
void gmt_free_int_selection (struct GMT_CTRL *GMT, struct GMT_INT_SELECTION **S) {
	/* Free the selection structure */
	if (*S == NULL) return;	/* Nothing to free */
	gmt_M_free (GMT, (*S)->item);
	gmt_M_free (GMT, *S);
}

/*! . */
bool gmt_get_int_selection (struct GMT_CTRL *GMT, struct GMT_INT_SELECTION *S, uint64_t this) {
	/* Return true if this item should be used */
	gmt_M_unused(GMT);
	if (S == NULL) return (false);	/* No selection criteria given, so can only return false */
	while (S->current < S->n && S->item[S->current] < this) S->current++;	/* Advance internal counter */
	if (S->current == S->n) return (S->invert);	/* Ran out, return true or false depending on initial setting */
	else if (S->item[S->current] == this) return (!S->invert);	/* Found, return true or false depending on initial setting */
	else return (S->invert);	/* Not found, return initial setting */
}

/*! . */
struct GMT_INT_SELECTION * gmt_set_int_selection (struct GMT_CTRL *GMT, char *item) {
	/* item is of the form [~]<range>[,<range>, <range>]
	 * where each <range> can be
	 * a) A single number [e.g., 8]
	 * b) a range of numbers given as start-stop [e.g., 6-11]
	 * c) A range generator start:step:stop [e.g., 13:2:19]
	 * d) +f<file> a file with a list of range items.
	 * If ~ is given we return the inverse selection.
	 * We return a pointer to struct GMT_INT_SELECTION, which holds the info.
	 */
	unsigned int pos = 0;
	uint64_t k = 0, n = 0, n_items;
	int64_t i, start = -1, stop = -1, step, max_value = 0, value = 0;
	struct GMT_INT_SELECTION *select = NULL;
	char p[GMT_BUFSIZ] = {""}, **list = NULL;

	if (!item || !item[0]) return (NULL);	/* Nothing to do */
	if (item[0] == '~') k = 1;		/* We want the inverse selection */
	if (item[k] == '+' && item[k+1] == 'f') {	/* Gave +f<file> with segment numbers */
		if ((n_items = gmt_read_list (GMT, &item[k+2], &list)) == 0) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Could not find/open file: %s\n", &item[k+2]);
			return (NULL);
		}
	}
	else {	/* Make a list of 1 item */
		list = gmt_M_memory (GMT, NULL, 1, char *);
		list[0] = strdup (&item[k]);
		n_items = 1;
	}
	/* Determine the largest item given or implied; use that for initial array allocation */
	for (n = 0; n < n_items; n++) {
		pos = 0;	/* Reset since gmt_strtok changed it */
		while ((gmt_strtok (list[n], ",-:", &pos, p))) {	/* While it is not empty, process it */
			value = atol (p);
			if (value > max_value) max_value = value;
		}
	}
	max_value++;	/* Since we start at 0, n is the n+1'th item in array */
	select = gmt_M_memory (GMT, NULL, 1, struct GMT_INT_SELECTION);	/* Allocate the selection structure */
	select->item = gmt_M_memory (GMT, NULL, max_value, uint64_t);	/* Allocate the sized array */
	if (k) select->invert = true;		/* Save that we want the inverse selection */
	/* Here we have user-supplied selection information */
	for (k = n = 0; k < n_items; k++) {
		pos = 0;	/* Reset since gmt_strtok changed it */
		while ((gmt_strtok (list[k], ",", &pos, p))) {	/* While it is not empty or there are parsing errors, process next item */
			if ((step = gmtlib_parse_index_range (GMT, p, &start, &stop)) == 0) {
				gmt_free_int_selection (GMT, &select);
				gmt_free_list (GMT, list, n_items);
				return (NULL);
			}

			/* Now set the item numbers for this sub-range */
			assert (stop < max_value);	/* Somehow we allocated too little */

			for (i = start; i <= stop; i += step, n++) select->item[n] = i;
		}
	}
	gmt_free_list (GMT, list, n_items);	/* Done with the list */
	/* Here we got something to return */
	select->n = n;							/* Total number of items */
	select->item = gmt_M_memory (GMT, select->item, n, uint64_t);	/* Trim back array size */
	gmt_sort_array (GMT, select->item, n, GMT_ULONG);		/* Sort the selection */
	GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Number of integer selections returned: %" PRIu64 "\n", n);
#ifdef DEBUG
	if (GMT->current.setting.verbose == GMT_MSG_DEBUG) {
		for (n = 0; n < select->n; n++)
			GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Selection # %" PRIu64 ": %" PRIu64 "\n", n, select->item[n]);
	}
#endif

	return (select);
}

/*! . */
void gmt_free_text_selection (struct GMT_CTRL *GMT, struct GMT_TEXT_SELECTION **S) {
	/* Free the selection structure */
	if (*S == NULL) return;	/* Nothing to free */
	if ((*S)->pattern) gmt_free_list (GMT, (*S)->pattern, (*S)->n);
	gmt_M_free (GMT, (*S)->regexp);
	gmt_M_free (GMT, (*S)->caseless);
	gmt_M_free (GMT, *S);
}

GMT_LOCAL bool gmtsupport_match (char *txt1, char *txt2, bool exact) {
	/* Helper function to do the comparison */
	bool match;
	if (exact)
		match = (strcmp (txt1, txt2) == 0);
	else
		match = (strstr (txt1, txt2) != NULL);
	return (match);
}

/*! . */
bool gmt_get_segtext_selection (struct GMT_CTRL *GMT, struct GMT_TEXT_SELECTION *S, struct GMT_DATASEGMENT *T, bool exact, bool last_match) {
	/* Return true if the pattern was found; see at end for what to check for in calling program */
	bool match;
	struct GMT_DATASEGMENT_HIDDEN *TH = gmt_get_DS_hidden (T);
	if (S == NULL || S->n == 0) return (true);	/* No selection criteria given, so can only return true */
	if (last_match && gmt_polygon_is_hole (GMT, T))	/* Check if current polygon is a hole */
		match = true;	/* Extend a true match on a perimeter to its trailing holes */
	else if (S->ogr_match)	/* Compare to single aspatial value */
		match = (TH->ogr && gmtsupport_match (TH->ogr->tvalue[S->ogr_item], S->pattern[0], exact));		/* true if we matched */
	else if (T->header) {	/* Could be one or n patterns to check */
		uint64_t k = 0;
		match = false;
		while (!match && k < S->n) {
#if !defined(WIN32) || (defined(WIN32) && defined(HAVE_PCRE)) || (defined(WIN32) && defined(HAVE_PCRE2))
			if (S->regexp[k])
				match = gmtlib_regexp_match (GMT, T->header, S->pattern[k], S->caseless[k]);	/* true if we matched */
			else
#endif
				match = gmtsupport_match (T->header, S->pattern[k], exact);
			k++;
		}
	}
	else	/* No segment header, cannot match */
		match = false;
	return (match);	/* Returns true if found */
	/* (Ctrl->S.inverse == match); Calling function will need to perform this test to see if we are to skip it */
}

/*! . */
struct GMT_TEXT_SELECTION * gmt_set_text_selection (struct GMT_CTRL *GMT, char *arg) {
	/* item is of the form [~]<pattern>]
	 * where <pattern> can be
	 * a) A single "string" [e.g., "my pattern"]
	 * b) a name=value for OGR matches [e.g., name="Billy"]
	 * c) A single regex term /regexp/[i] [/tr.t/]; append i for caseless comparison
	 * d) +f<file> a file with a list of the above patterns.
	 * If the leading ~ is given we return the inverse selection (segments that did not match).
	 * Escape ~ or +f at start of an actual pattern with \\~ to bypass their special meanings.
	 * We return a pointer to struct GMT_TEXT_SELECTION, which holds the information.
	 * Programs should call gmt_get_segtext_selection on a segment to determine a match,
	 * and gmt_free_text_selection to free memory when done.
	 */
	uint64_t k = 0, n = 0, n_items, arg_length;
	bool invert = false;
	struct GMT_TEXT_SELECTION *select = NULL;
	char **list = NULL, *item = NULL;

	if (!arg || !arg[0]) return (NULL);	/* Nothing to do */
	item = strdup (arg);
	if (item[0] == '~') {k = 1, invert = true;}	/* We want the inverse selection, then skip the first char */
	if (item[k] == '+' && item[k+1] == 'f') {	/* Gave [~]+f<file> with list of patterns, one per record */
		if ((n_items = gmt_read_list (GMT, &item[k+2], &list)) == 0) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Could not find/open file: %s\n", &item[k+2]);
			gmt_M_str_free (item);
			return (NULL);
		}
	}
	else {	/* Make a list of one item */
		list = gmt_M_memory (GMT, NULL, 1, char *);
		list[0] = strdup (&arg[k]);	/* This skips any leading ~ for inverse indicator */
		n_items = 1;
	}
	select = gmt_M_memory (GMT, NULL, 1, struct GMT_TEXT_SELECTION);	/* Allocate the selection structure */
	select->regexp = gmt_M_memory (GMT, NULL, n_items, bool);		/* Allocate the regexp bool array */
	select->caseless = gmt_M_memory (GMT, NULL, n_items, bool);	/* Allocate the caseless bool array */
	select->invert = invert;
	select->n = n_items;						/* Total number of items */
	for (n = 0; n < n_items; n++) {	/* Processes all the patterns */
		arg_length = strlen (list[n]);
		/* Special case 1: If we start with \~ it means ~ is part of the actual search string, so we must skip the \ */
		/* Special case 2: If we start with \+f it means +f is part of the actual search string and not a file option, so we must skip the \ */
		k = (list[n][0] == '\\' && arg_length > 3 && (list[n][1] == '~' || (list[n][1] == '+' && list[n][2] == 'f'))) ? 1 : 0;
		if (list[n][k] == '/' && list[n][arg_length-2]  == '/'  && list[n][arg_length-1]  == 'i' ) {	/* Case-less regexp string */
			select->regexp[n] = select->caseless[n] = true;
			list[n][arg_length-2] = '\0';	/* remove trailing '/i' from pattern string */
			gmt_strlshift (list[n], 1U);	/* Shift string left to loose the starting '/' */
		}
		else if (list[n][0] == '/' && list[n][arg_length-1]  == '/' ) {	/* Case-honoring regexp string */
			select->regexp[n] = true;
			list[n][arg_length-1] = '\0';	/* remove trailing '/' */
			gmt_strlshift (list[n], 1U);	/* Shift string left to loose the starting '/' */
		}
		/* else we have a fixed pattern string with nothing special to process */
	}
	/* Here we got something to return */
	select->pattern = list;						/* Pass the text list */

	gmt_M_str_free (item);
	return (select);
}

/*! . */
void gmt_just_to_lonlat (struct GMT_CTRL *GMT, int justify, bool geo, double *x, double *y) {
	/* See gmt_just_decode for how text code becomes the justify integer.
	 * If an oblique projection is in effect OR the spacing between graticules is
	 * nonlinear AND we are requesting a justification centered in y, then we must
	 * use the projectioned coordinates and invert for lon,lat, else we can do our
	 * calculation on the original (geographic or Cartesian) coordinates. */
	int i, j;
	double *box = NULL;
	bool use_proj;

	i = justify % 4;	/* Split the 2-D justify code into x just 1-3 */
	j = justify / 4;	/* Split the 2-D justify code into y just 0-2 */
	use_proj = (GMT->common.R.oblique || (j == 1 && gmt_M_is_nonlinear_graticule(GMT)));
	box = (use_proj) ? GMT->current.proj.rect : GMT->common.R.wesn;
	if (!geo) {	/* Check for negative Cartesian scales */
		if (!GMT->current.proj.xyz_pos[GMT_X]) i = 4 - i;	/* Negative x-scale, flip left-to-right */
		if (!GMT->current.proj.xyz_pos[GMT_Y]) j = 2 - j;	/* Negative y-scale, flip top-to-bottom */
	}
	if (i == 1)
		*x = box[XLO];
	else if (i == 2)
		*x = (box[XLO] + box[XHI]) / 2;
	else
		*x = box[XHI];

	if (j == 0)
		*y = box[YLO];
	else if (j == 1)
		*y = (box[YLO] + box[YHI]) / 2;
	else
		*y = box[YHI];
	if (use_proj) {	/* Actually computed x,y in inches for oblique box, must convert to lon lat */
		double xx = *x, yy = *y;
		gmt_xy_to_geo (GMT, x, y, xx, yy);
	}
	GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Converted code %d to i = %d, j = %d and finally x = %g and y = %g\n", justify, i, j, *x, *y);
}

void gmt_just_to_xy (struct GMT_CTRL *GMT, int justify,double *x, double *y) {
	/* See gmt_just_decode for how text code becomes the justify integer.
	 * If an oblique projection is in effect OR the spacing between graticules is
	 * nonlinear AND we are requesting a justification centered in y, then we must
	 * use the projected coordinates directly and return x,y in plot coordinates. */
	int i, j;

	i = justify % 4;	/* Split the 2-D justify code into x just 1-3 */
	j = justify / 4;	/* Split the 2-D justify code into y just 0-2 */
	/* Check for negative Cartesian scales */
	//if (!GMT->current.proj.xyz_pos[GMT_X]) i = 4 - i;	/* Negative x-scale, flip left-to-right */
	//if (!GMT->current.proj.xyz_pos[GMT_Y]) j = 2 - j;	/* Negative y-scale, flip top-to-bottom */
	if (i == 1)
		*x = GMT->current.proj.rect[XLO];
	else if (i == 2)
		*x = (GMT->current.proj.rect[XLO] + GMT->current.proj.rect[XHI]) / 2;
	else
		*x = GMT->current.proj.rect[XHI];

	if (j == 0)
		*y = GMT->current.proj.rect[YLO];
	else if (j == 1)
		*y = (GMT->current.proj.rect[YLO] + GMT->current.proj.rect[YHI]) / 2;
	else
		*y = GMT->current.proj.rect[YHI];
	GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Converted code %d to i = %d, j = %d and finally x = %g and y = %g\n", justify, i, j, *x, *y);
}

/*! . */
void gmtlib_refpoint_to_panel_xy (struct GMT_CTRL *GMT, int refpoint, struct GMT_SUBPLOT *P, double *x, double *y) {
	/* Takes the refpoint value and converts to panel position in inches. */
	int i, j;
	double w = P->w + P->gap[XLO] + P->gap[XHI];
	double h = P->h + P->gap[YLO] + P->gap[YHI];
	gmt_M_unused (GMT);

	i = refpoint % 4;	/* Split the 2-D justify code into x just 1-3 */
	j = refpoint / 4;	/* Split the 2-D justify code into y just 0-2 */
	if (i == 1)
		*x = 0.0;
	else if (i == 2)
		*x = 0.5 * w;
	else
		*x = w;

	if (j == 0)
		*y = 0.0;
	else if (j == 1)
		*y = 0.5 * h;
	else
		*y = h;
}

/*! . */
void gmt_free_refpoint (struct GMT_CTRL *GMT, struct GMT_REFPOINT **Ap) {
	struct GMT_REFPOINT *A = *Ap;
	if (A == NULL) return;	/* Nothing */
	gmt_M_str_free (A->args);
	gmt_M_free (GMT, A);
	A = NULL;
}

/*! . */
struct GMT_REFPOINT * gmt_get_refpoint (struct GMT_CTRL *GMT, char *arg_in, char option) {
	/* Used to decipher option -D in psscale, pslegend, and psimage:
	 * -D[g|j|n|x]<refpoint>[/<remainder]
	 * where g means map coordinates, n means normalized coordinates, and x means plot coordinates.
	 * For j we instead spacify a 2-char justification code and get the reference point from the corresponding
	 * plot box coordinates; the <refpoint> point is the coordinate pair <x0>/<y0>.
	 * All -D flavors except -Dx require -R -J.
	 * Remaining arguments are returned as well via the string A->args.
	 * also used to parse refpoint in scales -L and -T hence the option argument.
	 */
	unsigned int n_errors = 0, k = 1;	/* Assume 1st character tells us the mode */
	int n, justify = 0;
	enum GMT_enum_refpoint mode = GMT_REFPOINT_NOTSET;
	char txt_x[GMT_LEN256] = {""}, txt_y[GMT_LEN256] = {""}, the_rest[GMT_LEN256] = {""};
	static char *kind = GMT_REFPOINT_CODES;	/* The five types of refpoint specifications */
	char *arg = strdup (arg_in);	/* Since it may be a constant */
	struct GMT_REFPOINT *A = NULL;

	switch (arg[0]) {
		case 'n':	mode = GMT_REFPOINT_NORM;		break;	/* Normalized coordinates */
		case 'g':	mode = GMT_REFPOINT_MAP;		break;	/* Map coordinates */
		case 'j':	mode = GMT_REFPOINT_JUST;		break;	/* Map box with justification code */
		case 'J':	mode = GMT_REFPOINT_JUST_FLIP;		break;	/* Map box with mirrored justification code */
		case 'x':	mode = GMT_REFPOINT_PLOT;		break;	/* Plot coordinates */
		default: 	k = 0;	break;	/* None given, reset first arg to be at position 0 */
	}
	if (mode == GMT_REFPOINT_JUST || mode == GMT_REFPOINT_JUST_FLIP) {	/* Here we know k == 1 */
		n = gmtsupport_find_mod_syntax_start (arg, k);	/* Returns position of first modifier +? */
		if (arg[n]) {	/* Separated via +modifiers (or nothing follows), but here we know just is 2 chars */
			strncpy (txt_x, &arg[k], 2);	txt_x[2] = 0;
			strncpy (the_rest, &arg[n], GMT_LEN256-1);
		}
		else {	/* Old syntax with no +modifier and with things separated by slashes */
			if ((n = sscanf (&arg[k], "%[^/]/%s", txt_x, the_rest)) < 1) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Parsing of arguments (%s) failed \n", option, &arg[k]);
				gmt_M_str_free (arg);
				return NULL;	/* Not so good */
			}
		}
		justify = gmt_just_decode (GMT, txt_x, PSL_MC);
	}
	else {	/* Must worry about leading + signs in the numbers that might confuse us w.r.t. modifiers */
		/* E.g., -Dg123.3/+19+jTL we don't want to trip up on +19 as modifier! */
		n = gmtsupport_find_mod_syntax_start (arg, k);
		if (arg[n]) { /* Separated via +modifiers (or nothing follows) */
			int n2;
			strncpy (the_rest, &arg[n], GMT_LEN256-1);
			arg[n] = 0;	/* Chop off modifiers temporarily */
			if (mode == GMT_REFPOINT_NOTSET && strlen (arg) == 2 && strchr ("LMRBCT", toupper(arg[GMT_X])) && strchr ("LMRBCT", toupper(arg[GMT_Y]))) {	/* Apparently a 2-char justification code */
				mode = GMT_REFPOINT_JUST;
				GMT_Report (GMT->parent, GMT_MSG_WARNING, "Your -%c option was interpreted to mean -%c%c\n", option, option, kind[mode]);
			}
			else if (n == 0) {	/* Got no reference point, default to x0/0 */
				strcpy (txt_x, "0");	strcpy (txt_y, "0");
				mode = GMT_REFPOINT_PLOT;
			}
			else if ((n2 = sscanf (&arg[k], "%[^/]/%s", txt_x, txt_y)) < 2) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Parsing of reference point (%s) failed - expected slash-separated pair of coordinates\n", option, &arg[k]);
				arg[n] = '+';	/* Restore modifiers */
				gmt_M_str_free (arg);
				return NULL;	/* Not so good */
			}
		}
		else { /* No such modifiers given, so just slashes or nothing follows */
			if ((n = sscanf (&arg[k], "%[^/]/%[^/]/%s", txt_x, txt_y, the_rest)) < 2) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Parsing of arguments (%s )failed \n", option, &arg[k]);
				gmt_M_str_free (arg);
				return NULL;	/* Not so good */
			}
			if (n == 3 && gmt_count_char (GMT, arg, '/') == 3) {	/* GMT4-style -D<x>/<y>/<w>/<h> setting */
				if (gmt_M_compat_check (GMT, 4)) {
					GMT_Report (GMT->parent, GMT_MSG_COMPAT, "Your -%c option arguments %s were given in an deprecated format, see documentation\n", option, arg_in);
					mode = GMT_REFPOINT_PLOT;	/* The only way in GMT 4 */
				}
				else {
					GMT_Report (GMT->parent, GMT_MSG_ERROR, "Your -%c option arguments %s were given in an obsolete format, see documentation\n", option, arg_in);
					return NULL;
				}
			}
		}
	}

	if (mode == GMT_REFPOINT_NOTSET) {	/* Did not specify what reference point mode to use, must determine it from args */
		if (strchr (GMT_DIM_UNITS, txt_x[strlen(txt_x)-1]))		/* x position included a unit */
			mode = GMT_REFPOINT_PLOT;
		else if (strchr (GMT_DIM_UNITS, txt_y[strlen(txt_y)-1]))	/* y position included a unit */
			mode = GMT_REFPOINT_PLOT;
		else if (strlen (txt_x) == 2 && strchr ("LMRBCT", toupper(txt_x[GMT_X])) && strchr ("LMRBCT", toupper(txt_x[GMT_Y])))	/* Apparently a 2-char justification code */
			mode = GMT_REFPOINT_JUST;
		else if (GMT->common.J.active == false && GMT->common.R.active[RSET] == false)	/* No -R, -J were given so can only mean plot coordinates */
			mode = GMT_REFPOINT_PLOT;
		else {	/* Must assume the user gave map coordinates */
			mode = GMT_REFPOINT_MAP;
		}
		GMT_Report (GMT->parent, GMT_MSG_WARNING, "Your -%c option was interpreted to mean -%c%c\n", option, option, kind[mode]);
	}
	/* Here we know or have assumed the mode and can process coordinates accordingly */

	if (mode != GMT_REFPOINT_PLOT) {	/* Will require -R -J so check that these have been parsed */
		gmt_set_missing_options (GMT, "JR");	/* If mode is modern, they exist in the history, and if an overlay we may add these from history automatically */
		if (GMT->common.J.active == false && GMT->common.R.active[RSET] == false) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Your -%c%c reference point coordinates require both -R -J to be specified\n", option, kind[mode]);
			gmt_M_str_free (arg);
			return NULL;
		}
	}

	/* Here we have something to return */
	A = gmt_M_memory (GMT, NULL, 1, struct GMT_REFPOINT);
	switch (mode) {
		case GMT_REFPOINT_NORM:
			A->x = atof (txt_x);
			A->y = atof (txt_y);
			GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Anchor point specified via normalized coordinates: %g, %g\n", A->x, A->y);
			break;
		case GMT_REFPOINT_PLOT:
			A->x = gmt_M_to_inch (GMT, txt_x);
			A->y = gmt_M_to_inch (GMT, txt_y);
			GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Anchor point specified via plot coordinates (in inches): %g, %g\n", A->x, A->y);
			break;
		case GMT_REFPOINT_JUST:
		case GMT_REFPOINT_JUST_FLIP:
			A->justify = justify;
			GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Anchor point specified via justification code: %s\n", txt_x);
			break;
		case GMT_REFPOINT_MAP:
			n_errors += gmt_verify_expectations (GMT, gmt_M_type (GMT, GMT_IN, GMT_X), gmt_scanf (GMT, txt_x, gmt_M_type (GMT, GMT_IN, GMT_X), &A->x), txt_x);
			n_errors += gmt_verify_expectations (GMT, gmt_M_type (GMT, GMT_IN, GMT_Y), gmt_scanf (GMT, txt_y, gmt_M_type (GMT, GMT_IN, GMT_Y), &A->y), txt_y);
			if (n_errors)
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Could not parse geographic coordinates %s and/or %s\n", option, txt_x, txt_y);
			else
				GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Anchor point specified via map coordinates: %g, %g\n", A->x, A->y);
			break;
		default:		/* Here to prevent a warning */
			break;
	}
	if (n_errors)	/* Failure; free refpoint structure */
		gmt_free_refpoint (GMT, &A);
	else {	/* Assign args */
		A->mode = mode;
		A->args = strdup (the_rest);
	}
	gmt_M_str_free (arg);

	return (A);
}

/*! . */
void gmt_set_refpoint (struct GMT_CTRL *GMT, struct GMT_REFPOINT *A) {
	/* Update settings after -R -J and map setup has taken place */
	double x, y;
	if (A->mode == GMT_REFPOINT_MAP) {	/* Convert from map coordinates to plot coordinates */
		gmt_geo_to_xy (GMT, A->x, A->y, &x, &y);
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Convert map reference point coordinates from %g, %g to %g, %g\n", A->x, A->y, x, y);
		A->x = x;	A->y = y;
	}
	else if (A->mode == GMT_REFPOINT_JUST) {	/* Convert from justify code to map coordinates, then to plot coordinates */
		/* Since intended for inside frame items (scales) we use the bounding box rectangle to get the plot coordinate from the code */
		gmt_just_to_xy (GMT, A->justify, &x, &y);
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Convert code inside reference point coordinates from justification %s to %g, %g\n", GMT_just_code[A->justify], A->x, A->y);
		A->x = x;	A->y = y;
	}
	else if (A->mode == GMT_REFPOINT_JUST_FLIP) {	/* Convert from justify code to plot coordinates */
		/* Since intended for outside frame items (scales) we use the bounding box rectangle to get the plot coordinate from the code */
		gmt_just_to_xy (GMT, A->justify, &x, &y);
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Convert code outside reference point coordinates from justification %s to %g, %g\n", GMT_just_code[A->justify], A->x, A->y);
		A->x = x;	A->y = y;
	}
	else if (A->mode == GMT_REFPOINT_NORM) {	/* Convert relative to plot coordinates */
		x = A->x * (2.0 * GMT->current.map.half_width);
		y = A->y * GMT->current.map.height;
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Convert normalized reference point coordinates from %g, %g to %g, %g\n", A->x, A->y, x, y);
		A->x = x;	A->y = y;
	}
	/* Now the reference point is given in plot coordinates (inches) */
	A->mode = GMT_REFPOINT_PLOT;
}

/*! . */
void gmt_enable_threads (struct GMT_CTRL *GMT) {
	/* Control how many threads to use in Open MP section */
#ifdef _OPENMP
	if (GMT->common.x.active) {
		if (GMT->common.x.n_threads < gmtlib_get_num_processors()) {
			omp_set_dynamic (0);   			/* Explicitly disable dynamic teams */
			omp_set_num_threads (GMT->common.x.n_threads);	/* Use requested threads for all consecutive parallel regions */
		}
		GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Enable %d threads of %d available\n", GMT->common.x.n_threads, gmtlib_get_num_processors());
	}
	else {	/* Default uses all cores */
		GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Enable all available threads (up to %d)\n", gmtlib_get_num_processors());
	}
#else
	gmt_M_unused(GMT);
#endif
}

/*! . */
unsigned int gmt_validate_modifiers (struct GMT_CTRL *GMT, const char *string, const char option, const char *valid_modifiers, unsigned int verbosity) {
	/* Looks for modifiers +<mod> in string and making sure <mod> is
	 * only from the set given by valid_modifiers.  if verbosity is GMT_MSQ_QUIET
	 * we file no errors but just returns the number of valid modifiers found.
	 * Otherwise we return the number of invalid modifiers or 0.
	*/
	bool quoted = false;
	unsigned int n_bad = 0, n_good = 0;
	size_t k, len, start = 0;

	if (!string || string[0] == 0) return 0;	/* Nothing to check */
	len = strlen (string);
	for (k = 0; start == 0 && k < (len-1); k++) {
		if (string[k] == '\"') quoted = !quoted;	/* Initially false, becomes true at start of quote, then false when exits the quote */
		if (quoted) continue;		/* Not consider +<mod> inside quoted strings */
		if (string[k] == '+') {	/* Possibly a modifier */
			if (k && string[k-1] == 'e' && isdigit (string[k+1])) continue;	/* Exponential notation, e.g. 1e+5 */
			if (strchr (valid_modifiers, string[k+1]))	/* Found a recognized valid modifier */
				n_good++;
			else {	/* Found an invalid modifier or some part of a filename that has + in it */
				if (option)
					GMT_Report (GMT->parent, verbosity, "Option -%c option: Modifier +%c unrecognized\n", option, string[k+1]);
				else
					GMT_Report (GMT->parent, verbosity, "Modifier +%c unrecognized\n", string[k+1]);
				n_bad++;
			}
		}
	}
	return ((verbosity == GMT_MSG_QUIET) ? n_good : n_bad);
}

/*! . */
double gmt_pol_area (double x[], double y[], uint64_t n) {
	uint64_t i;
	double area, xold, yold;

	/* Trapezoidal area calculation for Cartesian coordinates.
	 * area will be +ve if polygon is CW, negative if CCW */

	if (n < 3) return (0.0);
	area = yold = 0.0;
	xold = x[n-1];	yold = y[n-1];

	for (i = 0; i < n; i++) {
		area += (xold - x[i]) * (yold + y[i]);
		xold = x[i];	yold = y[i];
	}
	return (0.5 * area);
}

GMT_LOCAL void gmtsupport_cart_centroid (const double *x, const double *y, uint64_t n, double *centroid) {
	double det = 0.0, tempDet, m;
	uint64_t i, j = 1;

	if (n < 4) return;	/* Triangle is smallest polygon */
	n--;	/* Since last point repeats the first */
	centroid[GMT_X] = centroid[GMT_Y] = 0.0;

	for (i = 0; i < n; i++, j++) {
		/* Compute the determinant */
		tempDet = x[i] * y[j] - x[j] * y[i];
		det += tempDet;
		/* Update centroid sum */
		centroid[GMT_X] += (x[i] + x[j]) * tempDet;
		centroid[GMT_Y] += (y[i] + y[j]) * tempDet;
	}

	m = 3 * det;	/* Divide by the total "mass" of the polygon */
	centroid[GMT_X] /= m;
	centroid[GMT_Y] /= m;
}

GMT_LOCAL double gmtsupport_cart_centroid_area (struct GMT_CTRL *GMT, const double *x, const double *y, uint64_t n, double *centroid) {
	double area, *xp = NULL, *yp = NULL;
	uint64_t i;

	if (n < 4) return 0.0;	/* Triangle is smallest polygon */
	gmtsupport_cart_centroid (x, y, n, centroid);

	n--;	/* Since last point repeats the first */

	xp = gmt_M_memory (GMT, NULL, n, double);	yp = gmt_M_memory (GMT, NULL, n, double);
	for (i = 0; i < n; i++) {	/* Just take out centroid coordinates */
		xp[i] = x[i] - centroid[GMT_X];
		yp[i] = y[i] - centroid[GMT_Y];
	}
	area = gmt_pol_area (xp, yp, n);	/* Signed area */
	gmt_M_free (GMT, xp);
	gmt_M_free (GMT, yp);

	return (area);
}

/*! . */
double gmt_centroid_area (struct GMT_CTRL *GMT, double x[], double y[], uint64_t n, int geo, double *pos) {
	/* Estimate centroid and area of a polygon.  geo is 1 if geographic data. Input data remains unchanged.
	 * area will be +ve if polygon is CW, negative if CCW */
	double area;	/* In selected units squared if geographic */
	if (geo)	/* Spherical centroid and area */
		area = gmtlib_geo_centroid_area (GMT, x, y, n, pos);
	else	/* Cartesian centroid and area */
		area = gmtsupport_cart_centroid_area (GMT, x, y, n, pos);
	return (area);
}

unsigned int gmt_polygon_orientation (struct GMT_CTRL *GMT, double x[], double y[], uint64_t n, int geo) {
	/* Estimate area of a polygon.  geo is 1 if geographic data. Input data remains unchanged.
	 * Since area will be +ve if polygon is CW, negative if CCW we return */
	double area, dummy[2];
	if (geo)	/* Spherical centroid and area */
		area = gmtlib_geo_centroid_area (GMT, x, y, n, dummy);
	else	/* Cartesian centroid and area */
		area = gmtsupport_cart_centroid_area (GMT, x, y, n, dummy);
	return ((area < 0.0) ? GMT_POL_IS_CCW : GMT_POL_IS_CW);
}

/*! . */
void gmt_mean_point (struct GMT_CTRL *GMT, double x[], double y[], uint64_t n, int geo, double *pos) {
	/* Estimate mean position.  geo is 1 if geographic data (requiring vector mean).  Input data remains unchanged. */
	uint64_t i, k;

	assert (n > 0);	/* So n is >= 1 below */
	if (n == 1) {	/* Single point means we return the point as is */
		pos[GMT_X] = x[0];	pos[GMT_Y] = y[0];
		return;
	}

	if (geo) {	/* Geographic data, must use vector mean */
		double P[3], M[3] = {0.0, 0.0, 0.0}, yc;
		for (i = 0; i < n; i++) {
			yc = gmt_lat_swap (GMT, y[i], GMT_LATSWAP_G2O);	/* Convert to geocentric */
			gmt_geo_to_cart (GMT, yc, x[i], P, true);
			for (k = 0; k < 3; k++) M[k] += P[k];	/* Add up the three components separately */
		}
		gmt_normalize3v (GMT, M);
		gmt_cart_to_geo (GMT, &pos[GMT_Y], &pos[GMT_X], M, true);
		pos[GMT_Y] = gmt_lat_swap (GMT, pos[GMT_Y], GMT_LATSWAP_O2G);	/* Convert back to geodetic */
	}
	else	/* Cartesian centroid */
		gmtsupport_cart_centroid (x, y, n, pos);
}

/*! . */
void gmt_adjust_refpoint (struct GMT_CTRL *GMT, struct GMT_REFPOINT *ref, double dim[], double off[], int justify, int anchor) {
	/* Adjust reference point based on size and justification of plotted item, towards a given anchor */
	GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Before justify = %d, Dim x = %g y = %g, Reference x = %g y = %g\n",
	            justify, dim[GMT_X], dim[GMT_Y], ref->x, ref->y);
	ref->x += 0.5 * (anchor%4 - justify%4) * dim[GMT_X];
	ref->y += 0.5 * (anchor/4 - justify/4) * dim[GMT_Y];
	GMT_Report (GMT->parent, GMT_MSG_DEBUG, "After justify = %d, Offset x = %g y = %g, Reference x = %g y = %g\n",
	            justify, off[GMT_X], off[GMT_Y], ref->x, ref->y);
	/* Also deal with any justified offsets if given */
	if (justify%4 == 3)	/* Right aligned */
		ref->x -= off[GMT_X];
	else /* Left or center aligned */
		ref->x += off[GMT_X];
	if (justify/4 == 2)	/* Top aligned */
		ref->y -= off[GMT_Y];
	else /* Bottom or middle aligned */
		ref->y += off[GMT_Y];
	GMT_Report (GMT->parent, GMT_MSG_DEBUG, "After shifts, Reference x = %g y = %g\n", ref->x, ref->y);
}

bool gmt_trim_requested (struct GMT_CTRL *GMT, struct GMT_PEN *P) {
	gmt_M_unused(GMT);
	if (P == NULL) return false;	/* No settings given */
	if (gmt_M_is_zero (P->end[BEG].offset) && gmt_M_is_zero (P->end[END].offset) && P->end[BEG].V == NULL && P->end[END].V == NULL)
		return false;	/* No trims given */
	return true;
}

unsigned int gmt_trim_line (struct GMT_CTRL *GMT, double **xx, double **yy, uint64_t *nn, struct GMT_PEN *P) {
	/* Recompute start and end points of line if offset trims are set */
	int64_t last, next, current = 0, inc, n, new_n, start[2] = {0,0}, orig_start[2] = {0,0}, stop[2] = {0,0}, new[2] = {0,0};
	int increment[2] = {1, -1};
	unsigned int k, proj_type, effect;
	double *x = NULL, *y = NULL, dist, ds = 0.0, f1, f2, x0, x1 = 0, y0, y1 = 0, offset;

	if (!gmt_trim_requested (GMT, P)) return 0;	/* No trimming requested */

	/* Here we must do some trimming */
	x = *xx;	y = *yy;	n = (int64_t)*nn;	/* Input arrays and length */
	new[END] = start[END] = orig_start[END] = stop[BEG] = n-1;
	for (effect = 0; effect < 2; effect++) {	/* effect = 0: +o trimming, effect = 1: +v trimming */
		for (k = 0; k < 2; k++) {
			if (effect == 0 && gmt_M_is_zero (P->end[k].offset))	/* No trim at this end */
				continue;
			else if (effect == 1 && (P->end[k].V == NULL || gmt_M_is_zero (P->end[k].length)))	/* No vector of any size at this end */
				continue;
			proj_type = (effect == 0) ? gmt_init_distaz (GMT, P->end[k].unit, P->end[k].type, GMT_MAP_DIST) : GMT_GEO2CART;
			if (proj_type == GMT_NOT_A_VALID_TYPE) return 0;	/* Failure */
			next = start[k];	last = stop[k];	inc = increment[k];
			dist = 0.0;
			if (proj_type == GMT_GEO2CART) gmt_geo_to_xy (GMT, x[next], y[next], &x1, &y1);
			offset = (effect == 0) ? P->end[k].offset : P->end[k].length;
			while (dist < offset && next != last) {	/* Must trim more */
				current = next;
				next += inc;
				if (proj_type == GMT_GEO2CART) {	/* Project and get distances in inches */
					x0 = x1;	y0 = y1;
					gmt_geo_to_xy (GMT, x[next], y[next], &x1, &y1);
					ds = hypot (x0 - x1, y0 - y1);
				}
				else	/* User distances */
					ds = gmt_distance (GMT, x[next], y[next], x[current], y[current]);
				dist += ds;
			}
			if (next == last)	/* Trimmed away the entire line */
				return 1;
			/* Most likely dist now exceeds trim unless by fluke it is equal */
			/* Must revise terminal point */
			f1 = (gmt_M_is_zero (ds)) ? 1.0 : (dist - offset) / ds;
			f2 = 1.0 - f1;
			y[current] = y[current] * f1 + y[next] * f2;
			if (gmt_M_x_is_lon (GMT, GMT_IN)) {	/* Must worry about longitude jump */
				double del = x[next] - x[current];
				gmt_M_set_delta_lon (x[current], x[next], del);
				x[current] += del * f2;
			}
			else	/* Cartesian */
				x[current] = x[current] * f1 + x[next] * f2;
			new[k] = current;	/* First (or last) point in trimmed line */
		}
		start[BEG] = new[BEG];	start[END] = new[END];
		stop[BEG]  = new[END];	stop[END]  = new[BEG];
	}
	if (new[END] <= new[BEG]) return 1;	/* Trimmed past each end */
	if (new[BEG] == orig_start[BEG] && new[END] == orig_start[END]) return 0;	/* No change in segment length so no need to reallocate */
	new_n = new[END] - new[BEG] + 1;	/* New length of line */
	gmt_prep_tmp_arrays (GMT, GMT_NOTSET, new_n, 2);	/* Init or reallocate tmp vectors */
	gmt_M_memcpy (GMT->hidden.mem_coord[GMT_X], &x[new[BEG]], new_n, double);
	gmt_M_memcpy (GMT->hidden.mem_coord[GMT_Y], &y[new[BEG]], new_n, double);
	gmt_M_free (GMT, x);	gmt_M_free (GMT, y);
	*xx = gmtlib_assign_vector (GMT, new_n, GMT_X);
	*yy = gmtlib_assign_vector (GMT, new_n, GMT_Y);
	*nn = (uint64_t)new_n;
	return 0;
}

char * gmt_memory_use (size_t bytes, int width) {
	/* Format the given bytes in terms of kb, Mb, or Gb, or Tb.
	 * Width is the precision, e.g., 1 or 3 probably */
	static char mem_report[GMT_LEN32] = {""};
	static char *unit = "kMGT";	/* bytes, kilo-, Mega-, Giga-, Tera- */
	unsigned int kind = 0;
	if (bytes < 1000)
		snprintf (mem_report, GMT_LEN32, "%d bytes", (int)bytes);
	else {
		double mem = bytes / 1024.0;	/* Report kb unless it is too much */
		while (mem > 1024.0 && kind < strlen(unit)) { mem /= 1024.0; kind++; }	/* Goto next higher unit */
		snprintf (mem_report, GMT_LEN32, "%.*f %cb", width, mem, unit[kind]);
	}
	return mem_report;
}

struct GMT_RECORD *gmt_new_record (struct GMT_CTRL *GMT, double *d, char *t) {
	/* Allocate a new record structure and initialize to d and t */
	struct GMT_RECORD *R = gmt_M_memory (GMT, NULL, 1, struct GMT_RECORD);
	R->data = d;
	R->text = t;
	return R;
}

char * gmt_argv2str (struct GMT_CTRL *GMT, int argc, char *argv[]) {
	/* Consolidate all args into a string */
	int k;
	size_t len = argc;	/* Space for spaces and final 0 */
	char *string = NULL;
	gmt_M_unused(GMT);
	if (argc == 0 || argv == NULL) return NULL;
	for (k = 0; k < argc; k++) len += strlen (argv[k]);
	string = calloc (len, sizeof (char));
	strcat (string, argv[0]);
	for (k = 1; k < argc; k++) {
		strcat (string, " ");
		strcat (string, argv[k]);
	}
	return string;
}

/*
 * Function to Convert Numbers to Roman Numerals
 * [http://www.sanfoundry.com/c-program-convert-numbers-roman/]
 */

GMT_LOCAL void gmtsupport_predigit(char num1, char num2, char string[], unsigned int *i) {
	string[(*i)++] = num1;
	string[(*i)++] = num2;
}

GMT_LOCAL void gmtsupport_postdigit (char c, unsigned int n, char string[], unsigned int *i) {
	unsigned int j;
	for (j = 0; j < n; j++)
		string[(*i)++] = c;
}

char *gmt_arabic2roman (unsigned int number, char string[], size_t size, bool lower) {
	/* Given number, return string to roman numeral, lowercase if lower is true */
	unsigned i = 0;
	if (string == NULL) return NULL;
	gmt_M_memset (string, size, char);
	while (number != 0) {
		if (number >= 1000) {
			gmtsupport_postdigit ('M', number / 1000, string, &i);
			number = number - (number / 1000) * 1000;
		}
		else if (number >= 500) {
			if (number < (500 + 4 * 100)) {
				gmtsupport_postdigit('D', number / 500, string, &i);
				number = number - (number / 500) * 500;
			}
			else {
				gmtsupport_predigit('C','M', string, &i);
				number = number - (1000-100);
			}
		}
		else if (number >= 100) {
			if (number < (100 + 3 * 100)) {
				gmtsupport_postdigit('C', number / 100, string, &i);
				number = number - (number / 100) * 100;
			}
			else {
				gmtsupport_predigit('L', 'D', string, &i);
				number = number - (500 - 100);
			}
		}
		else if (number >= 50) {
			if (number < (50 + 4 * 10)) {
				gmtsupport_postdigit('L', number / 50, string, &i);
				number = number - (number / 50) * 50;
			}
			else {
				gmtsupport_predigit('X','C', string, &i);
				number = number - (100-10);
			}
		}
		else if (number >= 10) {
			if (number < (10 + 3 * 10)) {
				gmtsupport_postdigit('X', number / 10, string, &i);
				number = number - (number / 10) * 10;
			}
			else {
				gmtsupport_predigit('X','L', string, &i);
				number = number - (50 - 10);
			}
		}
		else if (number >= 5) {
			if (number < (5 + 4 * 1)) {
				gmtsupport_postdigit('V', number / 5, string, &i);
				number = number - (number / 5) * 5;
			}
			else {
				gmtsupport_predigit('I', 'X', string, &i);
				number = number - (10 - 1);
			}
		}
		else if (number >= 1) {
			if (number < 4) {
				gmtsupport_postdigit('I', number / 1, string, &i);
				number = number - (number / 1) * 1;
			}
			else {
				gmtsupport_predigit('I', 'V', string, &i);
				number = number - (5 - 1);
			}
		}
	}
	if (lower) gmt_str_tolower (string);
	return string;
}

GMT_LOCAL double *gmtsupport_unique_array (struct GMT_CTRL *GMT, double *array, uint64_t *n) {
	size_t k, j;
	/* Sort the array in case user did not enter values that were monotonically increasing */
	gmt_sort_array (GMT, array, *n, GMT_DOUBLE);
	/* Skip any duplicates in the sorted array */
	k = 0; j = 1;
	while (j < *n) {
		if (doubleAlmostEqualZero (array[j], array[k]))	/* Skip repeated point */
			j++;
		else	/* Copy over unique value */ 
			array[++k] = array[j++];
	}
	k++;	/* (new) total number of unique values */
	if (k < *n) {	/* Update array count */
		*n = k;
		array = gmt_M_memory (GMT, array, *n, double);	/* Reallocate exact length of array */
		GMT_Report (GMT->parent, GMT_MSG_WARNING, "Eliminated %d duplicate values from the sorted array\n", (int)(j-k));
	}
	return array;
}

double *gmt_list_to_array (struct GMT_CTRL *GMT, char *list, unsigned int type, bool unique, uint64_t *n) {
	/* Given a comma-separated string of values of type, parse and return array and its length */
	size_t k;
	unsigned int pos = 0;
	char p[GMT_LEN64] = {""};
	double *array = NULL;
	if (list == NULL || list[0] == '\0') {	/* Got nothing, return nothing; likely an error */
		*n = 0;
		return NULL;
	}
	/* Count the commas but not a trailing comma with nothing after it */
	for (k = 0, *n = 1; k < strlen (list); k++) {
		if (list[k] == ',' && list[k+1])
			(*n)++;
	}
	array = gmt_M_memory (GMT, NULL, *n, double);	/* Allocate exact length of array */
	k = 0;
	while ((gmt_strtok (list, ",", &pos, p))) {	/* March along and convert each string to double */
		if (gmt_verify_expectations (GMT, type, gmt_scanf_arg (GMT, p, type, false, &(array[k])), p)) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Unable to parse value %s from list %s\n", p, list);
			gmt_M_free (GMT, array);
			return NULL;
		}
		k++;
	}
	if (!unique) return array;	/* Return as is */

	/* Return a possibly sorted and monotonically increasing array */
	return (gmtsupport_unique_array (GMT, array, n));
}

uint64_t gmt_make_equidistant_array (struct GMT_CTRL *GMT, double min, double max, double inc, double **array) {
	/* Just makes an equidistant array given vetted input parameters */
	uint64_t k, n;
	double *val = NULL;

	n = (doubleAlmostEqualZero (min, max) || (gmt_M_is_zero (inc) && gmt_M_is_zero ((max - min)/inc))) ? 1 : lrint (fabs (max - min) / fabs (inc)) + 1;
	val = gmt_M_memory (GMT, NULL, n, double);
	if (inc < 0.0) {	/* Reverse direction max:inc:min */
		for (k = 0; k < n; k++) val[k] = max + k * inc;
		val[n-1] = min;	/* To avoid round-off all the way to the end */
	}
	else {
		for (k = 0; k < n; k++) val[k] = min + k * inc;
		val[n-1] = max;	/* To avoid round-off all the way to the end */
	}
	*array = val;
	return (n);
}

double * gmt_duplicate_array (struct GMT_CTRL *GMT, double *array, uint64_t n) {
	/* Simply duplicate the double array */
	double *x = gmt_M_memory (GMT, NULL, n, double);
	gmt_M_memcpy (x, array, n, double);
	return (x);
}

void gmt_reset_array_time (struct GMT_CTRL *GMT, struct GMT_ARRAY *T) {
	/* Check that TIME_UNIT is set to same as given unit in -T
	 * If there is a mix we ensure -T unit and values are in the chosen
	 * -T units and that TIME_UNIT is internally reset, as is -R (if set).
	 * Some modules may need to scale other quantities as well. */

	double conv_scale = GMT->current.setting.time_system.scale;	/* Current scale from seconds to internal time units */
	if (!T->temporal) return;	/* Not a time-series */
	if (!T->unit) return;	/* Gave no unit so TIME_UNIT is used */
	if (T->unit != GMT->current.setting.time_system.unit) return;	/* Internal agreement */

	GMT->current.setting.time_system.unit = T->unit;	/* Override and recompute scales */
	(void) gmt_init_time_system_structure (GMT, &GMT->current.setting.time_system);
	conv_scale *= GMT->current.setting.time_system.i_scale;	/* Scale from whatever unit it was to new unit */
	T->min *= conv_scale;	/* T->inc is already in the specified unit so we leave that one as is */
	T->max *= conv_scale;
	if (GMT->common.R.active[RSET]) {	/* Since -R was already been parsed with initial units [s] */
		GMT->common.R.wesn[XLO] *= conv_scale;
		GMT->common.R.wesn[XHI] *= conv_scale;
	}
}

unsigned int gmt_parse_array (struct GMT_CTRL *GMT, char option, char *argument, struct GMT_ARRAY *T, unsigned int flags, unsigned int tcol) {
	/* Many GMT modules need to set up an equidistant set of values to
	 * serve as output times (or distances), binning boundaries, or similar.
	 * We expect such 1-D arrays to be specified on the command line
	 * via a syntax such as:]
	 *
	 *	-T<argument>
	 *
	 * where <argument> is one of these:
	 *	[<min/max/]<inc>[<unit>|+a|e|i|n|b|l|t|u]
	 *	<file>
	 *
	 * Parsing:
	 *	0) If <argument> is a single value and flags & GMT_ARRAY_SCALAR is set
	 *	   then we create an array of one item. Otherwise <argument> may be
	 *	   interpreted as <inc>.
	 *	1) If <argument> is a file found in our search path then
	 *	   we assume it contains one column with the final values.
	 *	   These are then read in via GMT_Read_Data, which means
	 *	   these values could be passed via VirtualFiles.
	 *	2) If +n is given it means that <inc> is an integer that
	 *	   says how many points we want equidistantly distributed
	 *	   between <min> and <max>.
	 *	3) If +i is given it means that <inc> is the reciprocal of
	 *     what is needed, e.g. use 24i instead of 0.041666...
	 *	4) If <min>/<max> are missing then it means these will
	 *	   be derived from the data extent.  Unless +n is also
	 *	   given then the data extremes will be rounded to the
	 *	   first and last multiple of <inc> that is inside the
	 *	   moin-max data range.
	 *	5) If <unit> is given and is any of the temporal units
	 *	   o|y then we will compute a non-equidistant set of calendar
	 *	   time values.
	 *	6) If <unit> is given and it is any of the spatial length units
	 *	   d|m|s|e|f|k|M|n|u or c (Cartesian), then we will compute
	 *	   distances along a track given by the first two columns and the
	 *	   resulting distances are our time-series values.
	 *  7) If +l is given then we are setting up a log10 array which is
	 *	   equidistant in log10(t).  Here, inc must be 1, 2, or 3 exclusively
	 *	   which translates into
	 *  8) If +b is given then we are setting up a log2 array which is
	 *	   equidistant in log2(t).  Here, inc must be an integer and indicates
	 *	   the log2 increment.
	 *  9) If +a is given then we will add the output array as a new output column.
	 * 10) If +e is given when only an increment is given then we must keep the
	 *	   increment exact and adjust max to ensure (max-min)/inc is an integer.
	 *	   The default adjusts inc instead, if flag GMT_ARRAY_ROUND is passed.
	 *     10) Since -T is a command-line option we enforce ISO calendar string format
	 *	   only (yyyy-mm-ddT, yyyy-jjjT, yyyy-WwwT).
	 *
	 * 11) If +u is given then we ensure the input array has unique and sorted entries
	 *     and that duplicated are eliminated.
	 * Note:   The effects in 4) and 5) are only allowed if the corresponding
	 *	   flags are passed to the parser.
	 */

	char txt[3][GMT_LEN32] = {{""}, {""}, {""}}, *m = NULL;
	int ns = 0;
	size_t len = 0;

	if (argument == NULL || argument[0] == '\0') {	/* A nothingburger */
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: No arguments given\n", option);
		return GMT_PARSE_ERROR;
	}
	gmt_M_str_free (T->file);		/* In case earlier parsing */
	gmt_M_memset (T, 1, struct GMT_ARRAY);	/* Wipe clean the structure */

	if (flags & GMT_ARRAY_UNIQUE)	/* This can also be set by the user via +u */
		T->unique = true;	/* Resulting array must contain unique and sorted entries */

	if (gmt_validate_modifiers (GMT, argument, option, GMT_ARRAY_MODIFIERS, GMT_MSG_ERROR)) return (GMT_PARSE_ERROR);

	if ((m = gmt_first_modifier (GMT, argument, GMT_ARRAY_MODIFIERS))) {	/* Process optional modifiers +a, +b, +e, +i, +l, +n, +t */
		unsigned int pos = 0;	/* Reset to start of new word */
		unsigned int n_errors = 0;
		char p[GMT_LEN32] = {""};
		while (gmt_getmodopt (GMT, 'T', m, GMT_ARRAY_MODIFIERS, &pos, p, &n_errors) && n_errors == 0) {
			switch (p[0]) {
				case 'a':	/* Add spatial distance column to output */
					T->add = true;
					break;
				case 'b':	/* Do a log2 grid */
					T->logarithmic2 = true;
					break;
				case 'e':	/* Increment must be honored exactly */
					T->exact_inc = true;
					break;
				case 'i':	/* Gave reciprocal increment; calculate inc later */
					T->reciprocal = true;
					break;
				case 'n':	/* Gave number of points instead; calculate inc later */
					T->count = true;
					break;
				case 'l':	/* Do a log10 grid */
					T->logarithmic = true;
					break;
				case 't':	/* Do a time vector */
					T->temporal = true;
					break;
				case 'u':	/* Ensure no duplicates; array must contain unique and sorted entries */
					T->unique = true;
					break;
				default:
					GMT_Report (GMT->parent, GMT_MSG_ERROR, "-%cmin/max/inc+ modifier +%s not recognized.\n", option, p);
					break;	/* These are caught in gmt_getmodopt so break is just for Coverity */
			}
		}
		m[0] = '\0';	/* Chop off the modifiers */
	}
	else if (gmt_M_compat_check (GMT, 5) && argument[strlen(argument)-1] == '+') {	/* Old-style + instead of +n */
		GMT_Report (GMT->parent, GMT_MSG_COMPAT, "-%cmin/max/inc+ is deprecated; use -%c[<min>/<max>/]<int>[+a|n] instead.\n", option, option);
		m = strrchr (argument, '+');	/* Position of last + */
		if (m) m[0] = '\0';	/* Chop off the plus */
		T->count = true;
	}

	/* 1a. Check if argument is a remote file */
	if (gmt_file_is_cache (GMT->parent, argument) || gmt_M_file_is_url (argument)) {	/* Remote file, must check */
		char path[PATH_MAX] = {""};
		unsigned int first = gmt_download_file_if_not_found (GMT, argument, GMT_CACHE_DIR);
		if (gmt_getdatapath (GMT, &argument[first], path, R_OK) == NULL) {	/* Remote file was not found? */
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Cannot find/open file %s\n", &argument[first]);
			return (GMT_PARSE_ERROR);
		}
		/* File successfully downloaded, just refer to it by actual name */
		T->file = strdup (&argument[first]);
		return (GMT_NOERROR);
	}

	/* 1b. Check if argument is a memory file */
	if (gmt_M_file_is_memory (argument)) {	/* Yep */
		T->file = strdup (argument);
		return (GMT_NOERROR);
	}

	/* 1c. Check if argument is a local file */
	if (!gmt_access (GMT, argument, F_OK)) {	/* File exists */
		T->file = strdup (argument);
		return (GMT_NOERROR);
	}

	/* 1d. Check if we are given a list t1,t2,t3,... */
	if (strchr (argument, ',')) {
		T->list = strdup (argument);
		if (strchr (argument, 'T')) {	/* Gave list of absolute times */
			gmt_set_column_type (GMT, GMT_IN,  tcol, GMT_IS_ABSTIME);	/* Set input column type as time */
			/* Set output column type as time unless -fo has been set */
			if (!GMT->common.f.active[GMT_OUT]) gmt_set_column_type (GMT, GMT_OUT, tcol, GMT_IS_ABSTIME);
			T->temporal = true;
		}
		return (GMT_NOERROR);
	}

	if (T->count && T->reciprocal) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: Cannot give both +i and +n\n", option);
		return GMT_PARSE_ERROR;
	}
	/* 2. Dealt with the file option, now parse [<min/max/]<inc> */
	if ((ns = sscanf (argument, "%[^/]/%[^/]/%s", txt[GMT_X], txt[GMT_Y], txt[GMT_Z])) < 1) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: Must specify valid min[/max[/inc[<unit>|+n]]] option\n", option);
		return GMT_PARSE_ERROR;
	}
	if ((flags & GMT_ARRAY_RANGE) && ns == 1 && (flags & GMT_ARRAY_SCALAR) == 0) {	/* Need to spell out all 3 items */
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: Must specify valid min/max/inc[<unit>|+n] option\n", option);
		return GMT_PARSE_ERROR;
	}
	if ((flags & GMT_ARRAY_RANGE) == 0 && !(ns == 1 || ns == 3) && (flags & GMT_ARRAY_NOINC) == 0) {	/* Need to give 1 or 3 items unless inc is optional */
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: Must specify valid [min/max/]inc[<unit>|+n] option\n", option);
		return GMT_PARSE_ERROR;
	}
	T->has_inc = (ns != 2);	/* This means we gave an increment */
	if (ns == 1 && (flags & GMT_ARRAY_SCALAR)) T->has_inc = false;	/* Actually, just a single -T<value */
	ns--;	/* ns is now the index to the txt array with the increment or count (2 or 0) */
	len = strlen (txt[ns]);	if (len) len--;	/* Now txt[ns][len] holds a unit (or not) */
	if (!T->has_inc && (T->logarithmic || T->logarithmic2)) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: Logarithmic array requires an increment argument\n", option);
		return GMT_PARSE_ERROR;
	}
	/* 3. Check if we are working with absolute time.  This means there must be a T in both min or max arguments */
	if (ns >= 1 && (strchr (txt[GMT_X], 'T') || strchr (txt[GMT_Y], 'T'))) {	/* Gave absolute time limits */
		T->temporal = true;
		if (!(flags & GMT_ARRAY_TIME)) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: Calendar time not allowed for this module\n", option);
			return GMT_PARSE_ERROR;
		}
#if 0	/* Not sure why I added this, commenting it out because it seems to work fine and why shouldn't it... */
		if (T->count) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: Cannot use +n modifier with calendar time data\n", option);
			return GMT_PARSE_ERROR;
		}
#endif
		/* Now worry about an increment with time units */
		if (T->has_inc) T->unit = txt[ns][len];
	}
	if (ns == 0 && strchr (GMT_TIME_UNITS, txt[ns][len]) && (T->temporal || (gmt_M_type (GMT, GMT_IN, tcol) & GMT_IS_RATIME))) {	/* Giving time increments only so need to switch to temporal */
		T->temporal = true;	/* May already be set but who cares */
		T->unit = txt[ns][len];
	}
	if (ns == 0 && (flags & GMT_ARRAY_SCALAR) && strchr (txt[GMT_X], 'T')) {	/* Giving time constant only so need to switch to temporal */
		T->temporal = true;	/* May already be set but who cares */
	}
	if (T->temporal) {	/* Must set TIME_UNIT and update time system scalings */
		gmt_set_column_type (GMT, GMT_IN, tcol, GMT_IS_ABSTIME);	/* Set input column type as time */
		/* Set output column type as time unless -fo has been set */
		if (!GMT->common.f.active[GMT_OUT]) gmt_set_column_type (GMT, GMT_OUT, tcol, GMT_IS_ABSTIME);
		if (T->has_inc) {	/* Gave a time increment */
			if (strchr (GMT_TIME_UNITS, T->unit))	/* Gave a valid time unit */
				txt[ns][len] = '\0';	/* Chop off time unit since we are done with it */
			else	/* User relied on the setting of TIME_UNIT */
				T->unit = GMT->current.setting.time_system.unit;	/* Set assumed time unit */
			/* Check if unit is a variable increment */
			T->vartime = (strchr (GMT_TIME_VAR_UNITS, T->unit) != NULL);
		}
		else	/* Set assumed time unit */
			T->unit = GMT->current.setting.time_system.unit;
	}
	/* 4. Consider spatial distances */
	if (T->has_inc && !T->temporal && strchr (GMT_LEN_UNITS "c", txt[ns][len])) {	/* Geospatial or Cartesian distances */
		if (!(flags & GMT_ARRAY_DIST)) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: Distance units not allowed for this module\n", option);
			return GMT_PARSE_ERROR;
		}
		if (txt[ns][len] == 'c') txt[ns][len] = '\0';	/* The c unit has served its purpose */
		/* Gave geospatial distance increment, so initialize distance machinery */
		if (txt[ns][0] == '-' && strchr ("-+", txt[ns][1])) {	/* Rare negative increment before -|+ for geospatial calculation mode */
			T->distmode = gmt_get_distance (GMT, &txt[ns][1], &(T->inc), &(T->unit));
			T->reverse = true;	/* Want array to be reversed */
		}
		else
			T->distmode = gmt_get_distance (GMT, txt[ns], &(T->inc), &(T->unit));
		if (T->distmode < 0)
			return GMT_PARSE_ERROR;
		if (gmt_init_distaz (GMT, T->unit, T->distmode, GMT_MAP_DIST) == GMT_NOT_A_VALID_TYPE)
			return GMT_PARSE_ERROR;
		T->spatial = (T->unit == 'X') ? 1 : 2;
	}

	/* 5. Get the increment (or count) */
	if (T->has_inc && !T->spatial) {
		gmt_scanf_float (GMT, txt[ns], &(T->inc));
		if (fabs (T->inc) < DBL_EPSILON) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: Increment is zero\n", option);
			return GMT_PARSE_ERROR;
		}
		if (T->inc < 0.0 && !T->logarithmic) {	/* Flag to be reversed */
			T->inc = -T->inc;
			T->reverse = true;	/* Want array to be reversed */
		}
		if (T->logarithmic || T->logarithmic2) {
			int k_inc = irint (T->inc);
			if (!gmt_M_is_zero (fabs (T->inc - (double)k_inc))) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: Logarithmic increment must be an integer\n", option);
				return GMT_PARSE_ERROR;
			}
			if (T->logarithmic && !(k_inc == 1 || k_inc == 2 || k_inc == 3 || k_inc < 0)) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: Logarithmic increment must be 1, 2, 3 (or a negative integer)\n", option);
				return GMT_PARSE_ERROR;
			}
		}
	}
	/* 6. If the min/max limits were given via argument then it is OK to parse */
	T->set = (T->has_inc) ? 1 : 0;	/* Maybe have inc so far */
	if (ns >= 1) {
		if (!strcmp (txt[GMT_X], "-"))	/* Must get this value later */
			T->delay[GMT_X] = true;
		else if (T->temporal) {
			if (gmt_scanf_argtime (GMT, txt[GMT_X], &(T->min)) == GMT_IS_NAN) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: Unable to parse min temporal value from %s (ISO datetime format required)\n", option, txt[GMT_X]);
				return GMT_PARSE_ERROR;
			}
		}
		else if (gmt_verify_expectations (GMT, gmt_M_type (GMT, GMT_IN, GMT_X), gmt_scanf_arg (GMT, txt[GMT_X], gmt_M_type (GMT, GMT_IN, GMT_X), false, &(T->min)), txt[GMT_X])) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: Unable to parse min value from %s\n", option, txt[GMT_X]);
			return GMT_PARSE_ERROR;
		}
		if (!strcmp (txt[GMT_Y], "-"))	/* Must get this value later */
			T->delay[GMT_Y] = true;
		else if (T->temporal) {
			if (gmt_scanf_argtime (GMT, txt[GMT_Y], &(T->max)) == GMT_IS_NAN) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: Unable to parse max temporal value from %s\n", option, txt[GMT_Y]);
				return GMT_PARSE_ERROR;
			}
		}
		else if (gmt_verify_expectations (GMT, gmt_M_type (GMT, GMT_IN, GMT_X), gmt_scanf_arg (GMT, txt[GMT_Y], gmt_M_type (GMT, GMT_IN, GMT_X), false, &(T->max)), txt[GMT_Y])) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: Unable to parse max value from %s (ISO datetime format required)\n", option, txt[GMT_Y]);
			return GMT_PARSE_ERROR;
		}
		if ((T->delay[GMT_X] || T->delay[GMT_Y]) && !(flags & GMT_ARRAY_NOMINMAX)) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: Cannot specify - as min or max value in this module\n", option);
			return GMT_PARSE_ERROR;
		}
		if (!(T->delay[GMT_X] || T->delay[GMT_Y]) && T->min >= T->max) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: min >= max\n", option);
			return GMT_PARSE_ERROR;
		}
		T->set += 2;	/* Read both min and max */
	}
	else if (ns == 0 && (flags & GMT_ARRAY_SCALAR)) {
		if (T->temporal) {
			if (gmt_scanf_argtime (GMT, txt[GMT_X], &(T->min)) == GMT_IS_NAN) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: Unable to parse min temporal value from %s (ISO datetime format required)\n", option, txt[GMT_X]);
				return GMT_PARSE_ERROR;
			}
			T->unit = GMT->current.setting.time_system.unit;	/* Set currently selected time unit so we don't run into issues later despite only having one time knot */
		}
		else if (gmt_verify_expectations (GMT, gmt_M_type (GMT, GMT_IN, GMT_X), gmt_scanf_arg (GMT, txt[GMT_X], gmt_M_type (GMT, GMT_IN, GMT_X), false, &(T->min)), txt[GMT_X])) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: Unable to parse min value from %s\n", option, txt[GMT_X]);
			return GMT_PARSE_ERROR;
		}
		T->max = T->min;
	}
	if (T->has_inc && ns == 0 && (flags & GMT_ARRAY_NOMINMAX)) {	/* The min/max will be set later */
		T->delay[GMT_X] = T->delay[GMT_Y] = true;
	}
	if (flags & GMT_ARRAY_ROUND)	/* Adjust increment to fit min/max so (max-min)/inc is an integer */
		T->round = true;
	if (T->exact_inc && T->set == 3) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: Modifier +e only applies when increment is given without any range\n", option);
		return GMT_PARSE_ERROR;

	}
	if (m) m[0] = '+';	/* Restore the modifiers */
	T->col = tcol;

	return GMT_NOERROR;
}

bool gmtlib_var_inc (double *x, uint64_t n) {
	/* Determine if spacing in the array is variable or constant */
	bool fixed = true;	/* Start with assumption of fixed increments */
	uint64_t k;
	double fix_inc, dx;
	if (n <= 2) return false;	/* Strange, but a single point or pair do not imply variable increment for sure */
	fix_inc = x[1] - x[0];
	for (k = 2; fixed && k < n; k++) {
		dx = x[k] - x[k-1];
		if (fabs ((fix_inc - dx) / fix_inc) > GMT_CONV8_LIMIT)
			fixed = false;	/* Not equidistant */
	}
	return (!fixed);
}

unsigned int gmt_create_array (struct GMT_CTRL *GMT, char option, struct GMT_ARRAY *T, double *min, double *max) {
	/* If min and max are not NULL then will override what T->min,max says */	char unit = GMT->current.setting.time_system.unit;
	double scale = GMT->current.setting.time_system.scale, inc = T->inc, t0, t1;

	if (T->array) gmt_M_free (GMT, T->array);	/* Free if previously set */

	if (T->file) {	/* Got a file, read first column into the array; must be one segment only */
		/* Temporarily change what data type col zero is */
		struct GMT_DATASET *D = NULL;
		unsigned int save_coltype[2];
		unsigned int save_trailing = GMT->current.io.trailing_text[GMT_IN];
		unsigned int save_max_cols_to_read = GMT->current.io.max_cols_to_read;
		int error;

		save_coltype[GMT_IN]  = gmt_get_column_type (GMT, GMT_IN, GMT_X);
		save_coltype[GMT_OUT] = gmt_get_column_type (GMT, GMT_OUT, GMT_X);
		if (T->temporal) gmt_set_column_type (GMT, GMT_IN, GMT_X, GMT_IS_ABSTIME);
		gmt_disable_bghio_opts (GMT);	/* Do not want any -b -g -h -i -o to affect the reading this file */
		GMT->current.io.record_type[GMT_IN] = GMT_READ_NORMAL;
		GMT->current.io.trailing_text[GMT_IN] = false;
		if ((error = GMT_Set_Columns (GMT->parent, GMT_IN, 1, GMT_COL_FIX_NO_TEXT)) != GMT_NOERROR) return (GMT_PARSE_ERROR);
		if ((D = GMT_Read_Data (GMT->parent, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_NONE, GMT_READ_NORMAL, NULL, T->file, NULL)) == NULL) {
			return (GMT_PARSE_ERROR);
		}
		if (gmt_get_column_type (GMT, GMT_IN, GMT_X) == GMT_IS_ABSTIME) T->temporal = true;	/* We read absolute times from the file */
		gmt_set_column_type (GMT, GMT_IN,  GMT_X, save_coltype[GMT_IN]);
		gmt_set_column_type (GMT, GMT_OUT, GMT_X, save_coltype[GMT_OUT]);
		GMT->current.io.trailing_text[GMT_IN] = save_trailing;
		GMT->current.io.max_cols_to_read = save_max_cols_to_read;
		gmt_reenable_bghio_opts (GMT);	/* Recover settings provided by user (if -b -g -h -i were used at all) */
		if (D->n_segments > 1) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: File %s has more than one segment\n", option, T->file);
			GMT_Destroy_Data (GMT->parent, &D);
			return GMT_PARSE_ERROR;
		}
		T->n = D->n_records;
		T->array = gmt_M_memory (GMT, NULL, T->n, double);
		gmt_M_memcpy (T->array, D->table[0]->segment[0]->data[GMT_X], T->n, double);
		if (D->table[0]->header && strstr (D->table[0]->header[0], "LIST")) {
			T->list = strdup ("LIST_GIVEN_AS_FILE");
			GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Option %c: File %s will be parsed as the equivalent list\n", option, T->file);
		}
		GMT_Destroy_Data (GMT->parent, &D);
		if (T->unique)	/* Must sort and eliminate duplicates */
			T->array = gmtsupport_unique_array (GMT, T->array, &(T->n));
		T->var_inc = gmtlib_var_inc (T->array, T->n);
		return GMT_NOERROR;
	}

	if (T->list) {	/* Got a list, parse and make array */
		if ((T->array = gmt_list_to_array (GMT, T->list, gmt_M_type (GMT, GMT_IN, T->col), T->unique, &(T->n))) == NULL)
			return GMT_PARSE_ERROR;
		T->var_inc = gmtlib_var_inc (T->array, T->n);
		T->min = T->array[0];	T->max = T->array[T->n-1];
		if (T->n > 1) {	/* Got at least min/max */
			if (!T->var_inc) {	/* Just did an alternate way to set an equidistant array */
				T->inc = T->array[1] - T->array[0];
				T->set = 3;
			}
			else
				T->set = 2;
		}
		else	/* Got a single point only */
			T->set = 1;
		return GMT_NOERROR;
	}

	if (min != NULL) {	/* Update min now */
		if (gmt_M_is_dnan (*min)) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: Min value is NaN - cannot create array\n", option);
			return GMT_PARSE_ERROR;
		}
		T->min = *min;
	}
	if (max != NULL) {	/* Update max now */
		if (gmt_M_is_dnan (*max)) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: Max value is NaN - cannot create array\n", option);
			return GMT_PARSE_ERROR;
		}
		T->max = *max;
	}
	if (T->count)	/* This means we gave a count instead of increment  */
		inc = (T->max - T->min) / (T->inc - 1.0);
	else if (T->reciprocal)	/* This means we gave the reciprocal increment  */
		inc = 1.0 / T->inc;

	t0 = T->min;	t1 = T->max;
	if (T->temporal && GMT->current.setting.time_system.unit != T->unit) {	/* Dealing with calendar time and must update time unit */
		GMT->current.setting.time_system.unit = T->unit;
		(void) gmt_init_time_system_structure (GMT, &GMT->current.setting.time_system);
		scale = GMT->current.setting.time_system.scale / scale;
		t0 /= scale;	t1 /= scale;
	}
	if (T->set == 2) return (GMT_NOERROR);	/* Probably makecpt giving just a range */

	if (doubleAlmostEqualZero (t0, t1)) {	/* min = max, probably a single entry */
		if (!T->has_inc || (T->has_inc && gmt_M_is_zero (T->inc) && gmt_M_is_zero ((t1 - t0)/T->inc))) {	/* Got a single item for our "array" */
			T->array = gmt_M_memory (GMT, NULL, 1, double);
			T->array[0] = t0;
			T->n = 1;
		}
	}
	else if (T->vartime)	/* Must call special function that knows about variable months and years */
		T->n = gmtsupport_time_array (GMT, t0, t1, inc, GMT->current.setting.time_system.unit, false, &(T->array));
	else if (T->logarithmic)	/* Must call special function that deals with logarithmic arrays */
		T->n = gmtlib_log_array (GMT, t0, t1, inc, &(T->array));
	else if (T->logarithmic2)	/* Must call special function that deals with logarithmic arrays */
		T->n = gmtlib_log2_array (GMT, t0, t1, inc, &(T->array));
	else {	/* Equidistant intervals are straightforward - make sure the min/max/inc values harmonize and watch out for decreasing time */
		unsigned int nt;
		double range = t1 - t0, tmp_t0, tmp_t1;
		if (T->exact_inc) {	/* Must enforce that max-min is a multiple of inc and adjust max if it is not */
			double new = rint (range / inc) * inc;
			if (!doubleAlmostEqualZero (new, range)) {	/* Must adjust t1 to match proper range */
				t1 = t0 + new;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Range (max - min) is not a whole multiple of inc. Adjusted max to %g\n", option, t1);
			}
		}
		else if (T->round) {	/* Must enforce an increment that fits the given range */
			double new;
			nt = urint (range / inc);
			new = nt * inc;
			if (nt && !doubleAlmostEqualZero (new, range)) {	/* Must adjust inc to match proper range */
				inc = range / nt;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Range (max - min) is not a whole multiple of inc. Adjusted inc to %g\n", option, inc);
			}
		}
		tmp_t0 = t0;	tmp_t1 = t1;
		if (T->reverse) gmt_M_double_swap (tmp_t0, tmp_t1);	/* Needed to trick gmt_minmaxinc_verify which was developed for w/e/s/n checks where we cannot go reverse */
		switch (gmt_minmaxinc_verify (GMT, tmp_t0, tmp_t1, inc, GMT_CONV8_LIMIT)) {
			case 1:	/* Must trim max to give a range in multiple of inc */
				nt = floor ((tmp_t1 - tmp_t0) / inc);
				tmp_t1 = tmp_t0 + inc * nt;
				GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Information from -%c option: (max - min) is not a whole multiple of inc. Adjusted max to %g\n", option, tmp_t1);
				break;
			case 2:
				if (inc != 1.0 && T->has_inc && gmt_M_is_zero (t0) && gmt_M_is_zero (t1) && gmt_M_is_zero ((t1 - t0)/T->inc)) {	/* Allow for somebody explicitly saying -T0/0/1, otherwise an error */
					GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: (max - min) is <= 0\n", option);
					return (GMT_PARSE_ERROR);
				}
				break;
			case 3:
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: inc is <= 0\n", option);
				return (GMT_PARSE_ERROR);
				break;
			default:	/* OK as is */
				break;
		}
		T->n = gmt_make_equidistant_array (GMT, tmp_t0, tmp_t1, T->reverse ? -inc : inc, &(T->array));
	}
	if (T->temporal && GMT->current.setting.time_system.unit != unit) {
		uint64_t k;
		/* Restore to original TIME_UNIT unit and update val array to have same units */
		GMT->current.setting.time_system.unit = unit;
		(void) gmt_init_time_system_structure (GMT, &GMT->current.setting.time_system);
		for (k = 0; k < T->n; k++) T->array[k] *= scale;
	}
	if (T->n == 0) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option %c: Your min/max/inc arguments resulted in no items\n", option);
		return (GMT_PARSE_ERROR);
	}
	T->var_inc = gmtlib_var_inc (T->array, T->n);
	return (GMT_NOERROR);
}

void gmt_free_array (struct GMT_CTRL *GMT, struct GMT_ARRAY *T) {
	/* Free anything that was allocated during parsing and creating a 1D array */
	gmt_M_str_free (T->file);
	gmt_M_str_free (T->list);
	if (T->array) gmt_M_free (GMT, T->array);
}

bool gmt_no_pstext_input (struct GMTAPI_CTRL *API, char *arg) {
	char *c = NULL;
	gmt_M_unused (API);
	/* Determine if -F is such that there is nothing to read */
	if (strstr (arg, "+c") == NULL) return false;	/* Without +c there will be input */
	if (strstr (arg, "+t") == NULL) return false;	/* Without +t there will be input */
	if ((c = strstr (arg, "+A")) && (c[2] == '+' || c[2] == '\0')) return false;	/* With +A and no arg there must be input */
	if ((c = strstr (arg, "+a")) && (c[2] == '+' || c[2] == '\0')) return false;	/* With +a and no arg there must be input */
	if ((c = strstr (arg, "+j")) && (c[2] == '+' || c[2] == '\0')) return false;	/* With +j and no arg there must be input */
	if ((c = strstr (arg, "+f")) && (c[2] == '+' || c[2] == '\0')) return false;	/* With +f and no arg there must be input */
	return true;
}

void gmt_filename_set (char *name) {
	/* Replace spaces with GMT_ASCII_RS */
	gmt_strrepc (name, ' ', GMT_ASCII_RS);
}

void gmt_filename_get (char *name) {
	/* Replace GMT_ASCII_RS with spaces */
	gmt_strrepc (name, GMT_ASCII_RS, ' ');
}

bool gmt_run_process_get_first_line (struct GMT_CTRL *GMT, char *program, char *arg, char *text) {
	/* Determine if a program exists by calling program with arg via popen.  If popen is successful
	 * and text != NULL then we return what popen read as first line. If successful test then
	 * we return true, else false */
	char cmd[PATH_MAX] = {""}, line[GMT_LEN256] = {""};
	FILE *fp = NULL;
	bool answer = false;

	/* Turn off any stderr messages coming to the terminal */
	if (strchr (program, ' ')) {	/* Command has spaces [most likely under Windows] */
		if (!(program[0] == '\'' || program[0] == '\"'))	/* Not in quotes, place double quotes */
			snprintf (cmd, PATH_MAX, "\"%s\"", program);
		else	/* Already has quotes, but these might be double or single */
			strncpy (cmd, program, PATH_MAX-1);
		if (program[0] == '\'')	/* Replace single quotes with double quotes*/
			gmt_strrepc (cmd, '\'', '\"');
	}
	else	/* No spaces, just copy */
		strncpy (cmd, program, PATH_MAX-1);
	if (arg) {	/* Append the command argument */
		strcat (cmd, " ");
		strncat (cmd, arg, PATH_MAX-1);
	}
	/* Finally, append redirection of errors */
#ifdef WIN32
	strcat (cmd, " 2> NUL");
#else
	strcat (cmd, " 2> /dev/null");
#endif
	GMT_Report (GMT->parent, GMT_MSG_DEBUG, "gmt_run_process_get_first_line: Pass to popen: [%s]\n", cmd);

	if ((fp = popen (cmd, "r")))	/* There was such a command */
		gmt_fgets (GMT, line, GMT_LEN256, fp);	/* Read first line */
	if (fp == NULL || line[0] == '\0') {
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "%s failed\n", cmd);
	}
	else {	/* Get here if we passed the test */
		if (text) strcpy (text, line);	/* Want to return the first line */
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "%s was successful\n", cmd);
		answer = true;
	}
	if (fp) pclose (fp);
	if (text) gmt_chop (text);	/* Get rid of newline */
	return (answer);
}

bool gmt_check_executable (struct GMT_CTRL *GMT, char *program, char *arg, char *pattern, char *text) {
	/* To avoid function name change in several GMT files. */
	bool status = gmt_run_process_get_first_line (GMT, program, arg, text);
	if (status && pattern && strstr (text, pattern) == NULL) {
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "gmt_check_executable failed pattern %s test\n", pattern);
	}
	return (status);
}

void gmt_extend_region (struct GMT_CTRL *GMT, double wesn[], unsigned int mode, double inc[]) {
	/* Extend the region outward according to mode */
	gmt_M_unused (GMT);
	if (mode == 0) return;	/* Do nothing */
	if (mode == GMT_REGION_ADD) {	/* Extend the region by increments */
		wesn[XLO] -= inc[XLO];
		wesn[YLO] -= inc[YLO];
		wesn[XHI] += inc[XHI];
		wesn[YHI] += inc[YHI];
	}
	else {	/* Make region be in multiples of increments, possibly with adjustment */
		double adjust = (mode == GMT_REGION_ROUND_EXTEND) ? GMT_REGION_INCFACTOR : 0.0;
		wesn[XLO] = floor ((wesn[XLO] - adjust * inc[XLO]) / inc[XLO]) * inc[XLO];
		wesn[YLO] = floor ((wesn[YLO] - adjust * inc[YLO]) / inc[YLO]) * inc[YLO];
		wesn[XHI] = ceil  ((wesn[XHI] + adjust * inc[XHI]) / inc[XHI]) * inc[XHI];
		wesn[YHI] = ceil  ((wesn[YHI] + adjust * inc[YHI]) / inc[YHI]) * inc[YHI];
	}
}

struct GMT_CONTOUR_INFO * gmt_get_contours_from_table (struct GMT_CTRL *GMT, char *file, bool inner_tics, unsigned int *type, unsigned int *n_contours) {
	/* Read contour info from file with cval [[angle] C|A|c|a [pen]]] records.
	 * The deprecated format was cval C|A|c|a [angle [pen]].
	 * If fix-angle annotations are specified we must pass out the type flag as well.
	 * If only cval is given then we set type to C.
	 */
	bool got_angle;
	char pen[GMT_LEN64] = {""}, txt[GMT_LEN64] = {""};
	unsigned int seg, row, c, save_coltype = gmt_get_column_type (GMT, GMT_IN, GMT_X);
	int nc = 0;
	struct GMT_DATASET *C = NULL;
	struct GMT_DATASEGMENT *S = NULL;
	struct GMT_CONTOUR_INFO * cont = NULL;

	gmt_set_column_type (GMT, GMT_IN, GMT_X, GMT_IS_FLOAT);	/* Since x is likely longitude we must avoid 360 wrapping here */

	if ((C = GMT_Read_Data (GMT->parent, GMT_IS_DATASET, GMT_IS_FILE, GMT_IS_POINT, GMT_IO_ASCII, NULL, file, NULL)) == NULL) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Unable to read contour information file %s - aborting\n", file);
		return (NULL);
	}
	if (C->n_records == 0) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "No records found in contour information file %s - aborting\n", file);
		return (NULL);
	}

	got_angle = (C->n_columns == 2);	/* We either know now (because we got two numerical columns), or we may find out later */
	cont = gmt_M_memory (GMT, NULL, C->n_records, struct GMT_CONTOUR_INFO);
	for (seg = c = 0; seg < C->n_segments; seg++) {
		S = C->table[0]->segment[seg];
		for (row = 0; row < S->n_rows; row++, c++) {
			cont[c].val = S->data[GMT_X][row];
			cont[c].angle = GMT->session.d_NaN;	/* May be overridden below */
			pen[0] = txt[0] = '\0';
			if (S->text && S->text[row])
				nc = sscanf (S->text[row], "%c %s %s", &cont[c].type, txt, pen);
			else
				nc = 0;
			if (nc && strchr ("AaCc", cont[c].type) == NULL) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Not a recognized contour type: %c\n", cont[c].type);
				gmt_M_free (GMT, cont);
				return (NULL);
			}
			if (S->n_columns == 2) {	/* Both value and angle given as part of new syntax */
				cont[c].angle = S->data[GMT_Y][row];
				if (nc == 2) strcpy (pen, txt);	/* Since trailing text here was <type> <pen> */
			}
			else if (nc == 3) {	/* Deprecated format with <type> <angle> <pen> */
				cont[c].angle = atof (txt);
				got_angle = true;
			}
			else if (nc == 2) {	/* Trailing text is either <type> <angle> or <type> <pen> */
				if (gmtsupport_is_pen (GMT, txt))	/* Definitively a pen */
					strcpy (pen, txt);
				else {	/* Could still be a pen if no unit appended */
					cont[c].angle = atof (txt);
					got_angle = true;
					if (cont[c].angle > 0.0 && cont[c].angle < 5.0)
						GMT_Report (GMT->parent, GMT_MSG_WARNING, "Cannot tell if %s is a pen or angle; chose angle. Please use trailing c|i|p units for all pens\n", txt);
				}
			}
			else if (nc == 0)	/* Only got cval, set default type */
				cont[c].type = 'C';
			/* else nc == 1 for record with only type information (no angle nor pen) */
			if (pen[0]) {	/* Got a pen */
				if (gmt_getpen (GMT, pen, &cont[c].pen)) {	/* Bad pen syntax */
					GMT_Report (GMT->parent, GMT_MSG_ERROR, "Unable to parse %s as a proper pen specification - aborting\n", pen);
					gmt_pen_syntax (GMT, 'C', NULL, " ", NULL, 0);
					gmt_M_free (GMT, cont);
					return (NULL);
				}
				cont[c].penset = true;
			}
			cont[c].do_tick = (inner_tics && (cont[c].type == 'C' || cont[c].type == 'A')) ? 1 : 0;
			if (got_angle) *type = 2;	/* Must set this directly if angles are provided */
		}
	}
	gmt_set_column_type (GMT, GMT_IN, GMT_X, save_coltype);

	/* Return information structure array back to the calling environment */

	*n_contours = C->n_records;
	return (cont);
}

bool gmt_is_barcolumn (struct GMT_CTRL *GMT, struct GMT_SYMBOL *S) {
	/* Return true if this is a vertical, horizontal bar or a column */
	gmt_M_unused (GMT);
	if (S->symbol == GMT_SYMBOL_BARX) return true;
	if (S->symbol == GMT_SYMBOL_BARY) return true;
	if (S->symbol == GMT_SYMBOL_COLUMN) return true;
	return false;
}

unsigned int gmt_get_columbar_bands (struct GMT_CTRL *GMT, struct GMT_SYMBOL *S) {
	/* Report how many bands in the 3-D column */
	unsigned int n_z = S->n_required;	/* z normally not counted unless +z|Z was used, so this could be 0 */
	gmt_M_unused (GMT);
	if ((S->base_set & GMT_BASE_READ) && n_z) n_z--;	/* Remove the base column item */
	if (n_z == 0) n_z = 1;	/* 1 means single band column */
	return (n_z);
}

void gmt_init_next_color (struct GMT_CTRL *GMT) {
	/*  Reset the sequential color IDs if starting a new plot or we detect overlay shift via -X -Y */
	bool reset = false;
	if (!GMT->common.O.active)	/* Start of a new plot means reset counters read from history to 0 0 */
		reset = true;
	else if (fabs (GMT->common.X.off) > 0.0 || fabs (GMT->common.Y.off) > 0.0)	/* Overlay but we are moving focus */
		reset = true;
	if (reset) {
		GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Reset sequential color pick IDs to 0,0\n");
		GMT->current.plot.color_seq_id[0] = GMT->current.plot.color_seq_id[1] = 0;
	}
}

void gmt_set_next_color (struct GMT_CTRL *GMT, struct GMT_PALETTE *P, unsigned int type, double rgb[]) {
	/* Cycle through the colors in P and increment sequential ID and only update r,g,b but not alpha */
	static char *kind[2] = {"table", "segment"};
	type--;	/* So 1 and 2 becomes 0 and 1 for array indices */ 
	GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Current %s sequential color pick ID = %u.\n", kind[type], GMT->current.plot.color_seq_id[type]);
	gmt_M_rgb_only_copy (rgb, P->data[GMT->current.plot.color_seq_id[type]].rgb_low);
	GMT->current.plot.color_seq_id[type] = (GMT->current.plot.color_seq_id[type] + 1) % P->n_colors;
}

#if 0	/* Probably not needed after all */
char * gmt_add_options (struct GMT_CTRL *GMT, const char *list) {
	/* Build option string that needs to be passed to GMT_Call_Module */
	static char opts[GMT_BUFSIZ] = {""}, string[4] = {" - "};
	size_t k;
	opts[0] = '\0';
	if (list == NULL) return (opts);
	for (k = 0; k < strlen (list); k++) {
		string[2] = list[k];
		strncat (opts, string, 3U);
		switch (list[k]) {
			case 'a': strcat (opts, GMT->common.a.string); break;
			case 'b': strcat (opts, GMT->common.b.string); break;
			case 'd': strcat (opts, GMT->common.d.string); break;
			case 'f': strcat (opts, GMT->common.f.string); break;
			case 'g': strcat (opts, GMT->common.g.string); break;
			case 'h': strcat (opts, GMT->common.h.string); break;
			case 'i': strcat (opts, GMT->common.i.col.string); break;
			case 'n': strcat (opts, GMT->common.n.string); break;
			case 's': strcat (opts, GMT->common.s.string); break;
			case 'V': string[0] = gmt_set_V (GMT->current.setting.verbose);
				strncat (opts, string, 1U); break;
			default:
				GMT_Report (GMT->parent, GMT_MSG_WARNING, "Unrecognized option %c\n", list[k]);
				return NULL;
		}
	}
	return (opts);
}
#endif

/*! . */
GMT_LOCAL int gmtsupport_sort_moduleinfo (const void *p_1, const void *p_2) {
	const struct GMT_MODULEINFO *point_1 = (const struct GMT_MODULEINFO *)p_1, *point_2 = (const struct GMT_MODULEINFO *)p_2;
	int res = strcmp (point_1->mname, point_2->mname);
	if (res < 0) return -1;
	if (res > 0) return +1;
	return 0;
}

int gmt_write_glue_function (struct GMTAPI_CTRL *API, char* library) {
	/* Called when we get gmt --new-glue=library is run, e.g.,
	 * 	gmt --new-glue=mbsystem > gmt_mbsystem_glue.c
	 */

	char **C = NULL, *lib_purpose = NULL;
	char line[BUFSIZ] = {""}, argument[GMT_LEN256] = {""}, our_glue[GMT_LEN256] = {""};
	bool first, first_purpose = true;
	int error = GMT_NOERROR, k = 0, n_alloc = 0, n = -1;	/* Advance to 0 for first item */
	FILE *fp = NULL;
	struct GMT_MODULEINFO *M = NULL;

	if ((C = gmt_get_dir_list (API->GMT, ".", ".c")) == NULL) {
		GMT_Report (API, GMT_MSG_ERROR, "No C files found in current directory\n");
		return GMT_RUNTIME_ERROR;
	}

	sprintf (our_glue, "%s_glue.c", library);	/* Name of the output although not under our control */

	while (C[k]) {	/* A NULL marks the end of files */
		if (!strcmp (C[k], our_glue)) {	/* Silently skip any file with that name */
			k++;
			continue;
		}
		if ((fp = fopen (C[k], "r")) == NULL) {
			GMT_Report (API, GMT_MSG_ERROR, "Unable to open file %s for reading - permission problem?\n", C[k]);
			error = GMT_RUNTIME_ERROR;
			goto CROAK;
		}
		first = true;	/* Reset for each new C file */
		while (fgets (line, BUFSIZ, fp)) {	/* This leaves the trailing linefeed intact */
			if (strncmp (line, "#define THIS_MODULE_", 20U)) continue;	/* Not found our lines yet */
			if (first) {	/* First time we passed the above if-test */
				n++, first = false;
			}
			if (n >= n_alloc) {	/* Need to allocate more memory */
				n_alloc += 50;
				M = gmt_M_memory (API->GMT, M, n_alloc, struct GMT_MODULEINFO);
			}
			/* Here we know we are looking at one of the preprocessor directives of interest */
			sscanf (line, "%*s %*s %[^\n]\n", argument);	/* Extract the argument */
			if (!strncmp (line, "#define THIS_MODULE_MODERN_NAME", 31U))
				M[n].mname = strdup (argument);
			else if (!strncmp (line, "#define THIS_MODULE_CLASSIC_NAME", 32U))
				M[n].cname = strdup (argument);
			else if (!strncmp (line, "#define THIS_MODULE_NAME", 24U)) {
				M[n].mname = strdup (argument);
				M[n].cname = strdup (argument);
			}
			else if (!strncmp (line, "#define THIS_MODULE_LIB_PURPOSE", 31U)) {
				if (first_purpose) lib_purpose = strdup (argument);
				first_purpose = false;
			}
			else if (!strncmp (line, "#define THIS_MODULE_LIB", 23U))
				M[n].component = strdup (argument);
			else if (!strncmp (line, "#define THIS_MODULE_PURPOSE", 27U))
				M[n].purpose = strdup (argument);
			else if (!strncmp (line, "#define THIS_MODULE_KEYS", 24U))
				M[n].keys = strdup (argument);
		}
		fclose (fp);
		if (first)
			GMT_Report (API, GMT_MSG_NOTICE, "File %s is not a module file - skipped\n", C[k]);
		else if (M[n].mname == NULL && M[n].cname == NULL && M[n].component == NULL && M[n].purpose == NULL && M[n].keys == NULL) { /* Not a module file */
			n--;	/* Counteract the n++ that will happen in the next file */
			GMT_Report (API, GMT_MSG_WARNING, "File %s had incomplete set of #define THIS_MODULE_* parameters; file skipped.\n", C[k]);
		}
		k++;	/* Go to next file */
	}

	if (n == -1) {
		GMT_Report (API, GMT_MSG_ERROR, "No module files found in current directory\n");
		error = GMT_RUNTIME_ERROR;
		goto CROAK;
	}

	n++;
	GMT_Report (API, GMT_MSG_INFORMATION, "%d %s module files found in current directory\n", n, library);

	if (first_purpose) {
		GMT_Report (API, GMT_MSG_WARNING, "No #define THIS_MODULE_LIB_PURPOSE setting found in any module.  Please edit argument in gmtlib_%s_show_all\n", library);
		sprintf (line, "\"GMT %s: The third-party supplements to the Generic Mapping Tools\"", library);
		lib_purpose = strdup (line);
		GMT_Report (API, GMT_MSG_WARNING, "Default purpose assigned: %s\n", lib_purpose);
	}

	qsort (M, n, sizeof (struct GMT_MODULEINFO), gmtsupport_sort_moduleinfo);

	printf ("/*\n * Copyright (c) 2012-2025 by the GMT Team (https://www.generic-mapping-tools.org/team.html)\n");
	printf (" * See LICENSE.TXT file for copying and redistribution conditions.\n */\n");
	printf ("/* gmt_%s_glue.c populates the external array of this shared lib with\n", library);
	printf (" * module parameters such as name, group, purpose and keys strings.\n");
	printf (" * This file also contains the following convenience functions to\n");
	printf (" * display all module purposes, list their names, or return keys or group:\n *\n");
	printf (" *   int %s_module_show_all    (void *API);\n", library);
	printf (" *   int %s_module_list_all    (void *API);\n", library);
	printf (" *   int %s_module_classic_all (void *API);\n *\n", library);
	printf (" * These functions may be called by gmt --help and gmt --show-modules\n *\n");
	printf (" * Developers of external APIs for accessing GMT modules will use this\n");
	printf (" * function indirectly via GMT_Encode_Options to retrieve option keys\n");
	printf (" * needed for module arg processing:\n *\n");
	printf (" *   const char * %s_module_keys  (void *API, char *candidate);\n", library);
	printf (" *   const char * %s_module_group (void *API, char *candidate);\n *\n", library);
	printf (" * All functions are exported by the shared %s library so that gmt can call these\n", library);
	printf (" * functions by name to learn about the contents of the library.\n */\n\n");
	printf ("#include \"gmt_dev.h\"\n\n");
	printf ("/* Sorted array with information for all GMT %s modules */\n", library);
	printf ("static struct GMT_MODULEINFO modules[] = {\n");
	for (k = 0; k < n; k++)
		printf ("\t{%s, %s, %s, %s, %s},\n", M[k].mname, M[k].cname, M[k].component, M[k].purpose, M[k].keys);
	printf ("\t{NULL, NULL, NULL, NULL, NULL} /* last element == NULL detects end of array */\n");
	printf ("};\n\n");
	printf ("/* Pretty print all shared module names and their purposes for gmt --help */\n");
	printf ("EXTERN_MSC int %s_module_show_all (void *API) {\n", library);
	printf ("\treturn (GMT_Show_ModuleInfo (API, modules, %s, GMT_MODULE_HELP));\n}\n\n", lib_purpose);
	printf ("/* Produce single list on stdout of all shared module names for gmt --show-modules */\n");
	printf ("EXTERN_MSC int %s_module_list_all (void *API) {\n", library);
	printf ("\treturn (GMT_Show_ModuleInfo (API, modules, NULL, GMT_MODULE_SHOW_MODERN));\n}\n\n");
	printf ("/* Produce single list on stdout of all shared module names for gmt --show-classic [i.e., classic mode names] */\n");
	printf ("EXTERN_MSC int %s_module_classic_all (void *API) {\n", library);
	printf ("\treturn (GMT_Show_ModuleInfo (API, modules, NULL, GMT_MODULE_SHOW_CLASSIC));\n}\n\n");
	printf ("/* Lookup module id by name, return option keys pointer (for external API developers) */\n");
	printf ("EXTERN_MSC const char *%s_module_keys (void *API, char *candidate) {\n", library);
	printf ("\treturn (GMT_Get_ModuleInfo (API, modules, candidate, GMT_MODULE_KEYS));\n}\n\n");
	printf ("/* Lookup module id by name, return group char name (for external API developers) */\n");
	printf ("EXTERN_MSC const char *%s_module_group (void *API, char *candidate) {\n", library);
	printf ("\treturn (GMT_Get_ModuleInfo (API, modules, candidate, GMT_MODULE_GROUP));\n}\n");

CROAK:	/* We are done or premature return due to error */

	gmt_free_dir_list (API->GMT, &C);
	for (k = 0; k < n; k++) {
		gmt_M_str_free (M[k].mname);
		gmt_M_str_free (M[k].cname);
		gmt_M_str_free (M[k].component);
		gmt_M_str_free (M[k].purpose);
		gmt_M_str_free (M[k].keys);
	}
	gmt_M_free (API->GMT, M);
	gmt_M_str_free (lib_purpose);

	return (error);
}

void gmt_cpt_interval_modifier (struct GMT_CTRL *GMT, char **arg, double *interval) {
	/* CPT files in some programs (grd2kml, grdimage, grdvector, grdview) may have a +i<dz> modifier,
	 * but it may be just one of several valid CPT modifiers.  Here, we wish to remove this
	 * modifier, set the corresponding interval, and update *file to only have the
	 * remaining text items. */
	char *file = NULL, *c = NULL, *f = NULL, new_arg[PATH_MAX] = {""};
	gmt_M_unused (GMT);
	if (arg == NULL || (file = *arg) == NULL || file[0] == '\0') return;	/* NULL argument */
	if ((f = gmt_strrstr (file, GMT_CPT_EXTENSION)))	/* Filename has .cpt extension, look behind it */
		c = gmtlib_last_valid_file_modifier (GMT->parent, f, GMT_CPTFILE_MODIFIERS);
	else	/* Must search the entire filename from the back */
		c = gmtlib_last_valid_file_modifier (GMT->parent, file, GMT_CPTFILE_MODIFIERS);
	if (c == NULL) return;	/* No modifiers present in the filename */
	if ((f = strstr (c, "+i")) == NULL) return;	/* Modifiers are present, but not the +i setting */
	/* Here we have a +i<dz> string in section pointed to by f */
	if (f[2] == '\0' || !(f[2] == '.' || isdigit (f[2]))) {	/* Failed basic sanity checking */
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "CPT filename has +i appended [%s] but sets no valid interval\n", f);
		return;	/* Simply not acting on the bad argument */
	}
	*interval = atof (&f[2]);
	f[0] = '\0';	f++;	/* Chop off and move one char to the right */
	strncpy (new_arg, file, PATH_MAX-1);        /* Everything up to start of +i */
	while (*f && *f != '+') f++;                /* Wind to next modifier or reach end of string */
	if (*f) strncat (new_arg, f, PATH_MAX-1);   /* Append other modifiers given after +i */
	gmt_M_str_free (*arg);
	*arg = strdup (new_arg);
}

/* This set of 14 functions are used by both movie.c and batch.c to deal with understanding
 * input script types and to write shell commands in various syntax variants.
 */

int gmt_sleep (unsigned int microsec) {
	/* Waiting before checking if the completion file has been generated */
#ifdef WIN32
	Sleep ((uint32_t)microsec/1000);	/* msec are microseconds but Sleep wants milliseconds */
	return 0;
#else
	return (usleep ((useconds_t)microsec));
#endif
}

void gmt_set_value (struct GMT_CTRL *GMT, FILE *fp, int mode, int col, char *name, double value) {
	/* Assigns a single named data floating point variable given the script mode
	 * Here, col indicates which input column in case special formatting is implied via -f */
	char string[GMT_LEN64] = {""};
	gmt_ascii_format_one (GMT, string, value, gmt_M_type (GMT, GMT_IN, col));
	switch (mode) {
		case GMT_BASH_MODE: fprintf (fp, "%s=%s", name, string);       break;
		case GMT_CSH_MODE:  fprintf (fp, "set %s = %s", name, string); break;
		case GMT_DOS_MODE:  fprintf (fp, "set %s=%s", name, string);   break;
	}
	fprintf (fp, "\n");
}

void gmt_set_ivalue (FILE *fp, int mode, bool env, char *name, int value) {
	/* Assigns a single named integer variable given the script mode */
	switch (mode) {
		case GMT_BASH_MODE: fprintf (fp, "%s=%d\n", name, value);       break;
		case GMT_CSH_MODE:  if (env)
					fprintf (fp, "%s %d\n", name, value);
				else
					fprintf (fp, "set %s = %d\n", name, value);
				break;
		case GMT_DOS_MODE:  fprintf (fp, "set %s=%d\n", name, value);   break;
	}
}

void gmt_set_dvalue (FILE *fp, int mode, char *name, double value, char unit) {
	/* Assigns a single named Cartesian floating point variable given the script mode */
	switch (mode) {
		case GMT_BASH_MODE: fprintf (fp, "%s=%.12g", name, value);       break;
		case GMT_CSH_MODE:  fprintf (fp, "set %s = %.12g", name, value); break;
		case GMT_DOS_MODE:  fprintf (fp, "set %s=%.12g", name, value);   break;
	}
	if (unit) fprintf (fp, "%c", unit);	/* Append the unit [c|i|p] unless 0 */
	fprintf (fp, "\n");
}

void gmt_set_tvalue (FILE *fp, int mode, bool env, char *name, char *value) {
	/* Assigns a single named text variable given the script mode */
	if (strchr (value, ' ') || strchr (value, '\t') || strchr (value, '|')) {	/* String has spaces, tabs, or bar */
		switch (mode) {
			case GMT_BASH_MODE: fprintf (fp, "%s=\"%s\"\n", name, value);       break;
			case GMT_CSH_MODE:  if (env)
						fprintf (fp, "%s \"%s\"\n", name, value);
					else
						fprintf (fp, "set %s = \"%s\"\n", name, value);
					break;
			case GMT_DOS_MODE:  fprintf (fp, "set %s=\"%s\"\n", name, value);   break;
		}
	}
	else {	/* Single word */
		switch (mode) {
			case GMT_BASH_MODE: fprintf (fp, "%s=%s\n", name, value);       break;
			case GMT_CSH_MODE:  if (env)
						fprintf (fp, "%s %s\n", name, value);
					else
						fprintf (fp, "set %s = %s\n", name, value);
					break;
			case GMT_DOS_MODE:  fprintf (fp, "set %s=%s\n", name, value);   break;
		}
	}
}

void gmt_set_script (FILE *fp, int mode) {
	/* Writes the script's incantation line (or a comment for DOS, turning off default echo) */
	switch (mode) {
		case GMT_BASH_MODE: fprintf (fp, "#!/usr/bin/env bash\n"); break;
		case GMT_CSH_MODE:  fprintf (fp, "#!/usr/bin/env csh\n"); break;
		case GMT_DOS_MODE:  fprintf (fp, "@echo off\nREM Start of script\n"); break;
	}
}

void gmt_set_comment (FILE *fp, int mode, char *comment) {
	/* Write a comment line given the script mode */
	switch (mode) {
		case GMT_BASH_MODE: case GMT_CSH_MODE:  fprintf (fp, "# %s\n", comment); break;
		case GMT_DOS_MODE:  fprintf (fp, "REM %s\n", comment); break;
	}
}

char *gmt_get_strwithtab (const char *txt) {
	/* Replace any literal "\t" strings with the tab character */
	char dummy[GMT_LEN128] = {""};
	if (!strcmp (txt, "\\t")) {
		char new[2] = {'\t', 0};	/* The tab character in a string */
		strncpy (dummy, gmt_strrep (txt, "\\t", new), GMT_LEN128-1);
	}
	else
		strncpy (dummy, txt, GMT_LEN128-1);
	return strdup (dummy);
}

char *gmt_place_var (int mode, char *name) {
	/* Prints a single variable to stdout where needed in the script via the string static variable.
	 * PS!  Only one call per printf statement since static string cannot hold more than one item at the time */
	static char string[GMT_LEN128] = {""};	/* So max length of variable name is 127 */
	if (mode == GMT_DOS_MODE)
		sprintf (string, "%%%s%%", name);
	else
		sprintf (string, "${%s}", name);
	return (string);
}

int gmt_dry_run_only (const char *cmd) {
	/* Dummy function to not actually run the loop script when -Q is used */
	gmt_M_unused (cmd);
	return 0;
}

unsigned int gmt_check_language (struct GMT_CTRL *GMT, unsigned int mode, char *file, unsigned int type, bool *PS) {
	unsigned int n_errors = 0;
	/* Examines file extension and compares to known mode from mainscript.
	 * Here type is 0-2 for background, foreground, or title script/plot which may be either a script of PS/EPS
	 * while type = 0 is script only and will be compared to the mode. */

	if (PS) {	/* Only used in movie.c so far */
		size_t L = strlen (file);
		*PS = false;
		if (type < 3 && L > 4 && (!strncmp (&file[L-3], ".ps", 3U) || !strncmp (&file[L-4], ".eps", 3U))) {
			static char *layer[3] = {"background", "foreground", "title"};
			GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "PostScript/EPS %s layer %s detected\n", layer[type], file);
			*PS = true;	/* Got a PostScript or EPS file */
			return GMT_NOERROR;
		}
	}

	switch (mode) {
		case GMT_BASH_MODE:
			if (!(strstr (file, ".bash") || strstr (file, ".sh"))) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Main script is bash/sh but %s is not!\n", file);
				n_errors++;
			}
			break;
		case GMT_CSH_MODE:
			if (!strstr (file, ".csh")) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Main script is csh but %s is not!\n", file);
				n_errors++;
			}
			break;
		case GMT_DOS_MODE:
			if (!strstr (file, ".bat")) {
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Main script is bat but %s is not!\n", file);
				n_errors++;
			}
			break;
	}
	return (n_errors);
}

bool gmt_script_is_classic (struct GMT_CTRL *GMT, FILE *fp) {
	/* Read script to determine if it is in GMT classic mode or not, then rewind */
	bool modern = false;
	char line[PATH_MAX] = {""};
	while (!modern && gmt_fgets (GMT, line, PATH_MAX, fp)) {
		if (strstr (line, "gmt ") == NULL) continue;	/* Does not start with gmt */
		if (strstr (line, " begin"))		/* A modern mode script */
			modern = true;
		else if (strstr (line, " figure"))	/* A modern mode script */
			modern = true;
		else if (strstr (line, " subplot"))	/* A modern mode script */
			modern = true;
		else if (strstr (line, " inset"))	/* A modern mode script */
			modern = true;
		else if (strstr (line, " end"))		/* A modern mode script */
			modern = true;
	}
	rewind (fp);	/* Go back to beginning of file */
	return (!modern);
}

int gmt_token_check (struct GMT_CTRL *GMT, FILE *fp, char *prefix, unsigned int mode) {
	/* Read main script to determine any *prefix*_*** variables
	 * are found with a missing %,$ token, then rewind */
	int n_errors = 0, e;
	char line[GMT_LEN256] = {""}, record[GMT_LEN256] = {""}, *p = NULL, *prev = NULL, *start = NULL;
	static char var_token[4] = "$$%";
	while (gmt_fgets (GMT, line, GMT_LEN256, fp)) {
		start = line;
		while (strchr (" \t", start[0])) start++;	/* Skip any leading whitespace */
		if (start[0] == '\n' || start[0] == '\r')  continue;	/* Blank line */
		if (mode == GMT_DOS_MODE) {	/* Some DOS-specific checks */
			if (!strcmp (start, "REM") || !strcmp (start, "rem")) continue;	/* DOS comment */
		}
		else {	/* UNIX shells */
			if (start[0] == '#') continue;	/* Shell comment */
			if (mode == GMT_BASH_MODE) {	/* Some bash-specific checks */
				if (strchr (line, '`'))	/* sub-shell call using back-ticks */
					GMT_Report (GMT->parent, GMT_MSG_WARNING, "Main script appears to have a deprecated sub-shell call `...`, please use $(...) instead: %s", start);
				else if (strchr (line, ')') && (p = strchr (line, '(')) && strstr (line, "((") == NULL) {	/* sub-shell call without leading $ and it is not a modern (( )) thing */
					prev = p - 1;	/* Get previous character */
					if (strchr (line, '\"') == NULL && (prev < start || prev[0] != '$'))	/* No double-quotes yet we have ( ...) and no leading $.Give this message: */
						GMT_Report (GMT->parent, GMT_MSG_INFORMATION, "Main script appears to have a sub-shell call $(...) without the leading $: %s", start);
				}
			}
		}
		if ((p = strstr (line, prefix))) {
			/* Got a MOVIE_ or BATCH_ variable here. Check if it is missing the token */
			strncpy (record, start, GMT_LEN256-1);
			prev = p - 1;	/* Get previous character */
			if (prev >= start && prev[0] == '{') prev--, p--;	/* Found {prefix} */
			if (prev < start || prev[0] != var_token[mode]) {	/* Start of line or the previous char is not the token */
				start = line;	/* Reset pointer */
				e = (int)(p - start);	/* Try to find the end of the variable name to make message below clearer */
				while (line[e] && strchr (" \t,/:", line[e]) == NULL) e++;
				line[e] = '\0';
				while (strchr (" \t", start[0])) start++;	/* Skip any leading whitespace */
				GMT_Report (GMT->parent, GMT_MSG_ERROR, "Main script uses %s but missing the required leading %c: %s", p, var_token[mode], record);
				n_errors++;
			}
			else if (mode != GMT_DOS_MODE) {
				if (strchr (start, '{') && !strchr (start, '}'))
					GMT_Report (GMT->parent, GMT_MSG_ERROR, "Main script missing } in variable name: %s", record), n_errors++;
				else if (!strchr (start, '{') && strchr (start, '}'))
					GMT_Report (GMT->parent, GMT_MSG_ERROR, "Main script missing { in variable name: %s", record), n_errors++;
			}
		}
	}
	rewind (fp);	/* Go back to beginning of file */
	return (n_errors);
}

GMT_LOCAL bool gmtsupport_line_is_a_comment (char *line) {
	unsigned int k = 0;
	while (line[k] && isspace (line[k])) k++;	/* Wind past leading whitespace */
	return (line[k] == '#' || !strncasecmp (&line[k], "rem", 3U)) ? true : false;	/* Will return true for lines starting with some tabs, then comment */
}

bool gmt_is_gmtmodule (char *line, char *module) {
	/* Robustly identify the command "gmt begin" */
	char word[GMT_LEN128] = {""};
	unsigned int pos = 0;
	size_t L;
	if (strlen (line) >= GMT_LEN128) return false;	/* Cannot be gmt begin */
	/* To handle cases where there may be more than one space between gmt and module */
	if (gmtsupport_line_is_a_comment (line)) return false;	/* Skip commented lines like "  # anything" */
	if (gmt_strtok (line, " \t\n", &pos, word) == 0) return false;	/* Get first word in the command or fail */
	if (strcmp (word, "gmt")) return false;		/* Not starting with gmt so we are done */
	if (gmt_strtok (line, " \t\n", &pos, word) == 0) return false;	/* Get second word or fail */
	L = strlen (module);				/* How many characters to compare against */
	if (!strncmp (word, module, L)) return true;	/* Command starting with gmt <module> found */
	return false;	/* Not gmt <module> */
}

bool gmt_is_gmt_end_show (char *line) {
	char word[GMT_LEN128] = {""};
	unsigned int pos = 0;
	if (strlen (line) >= GMT_LEN128) return false;	/* Cannot be gmt end show */
	/* Robustly identify the command "gmt end show" */
	/* To handle cases where there may be more than one space between gmt and module */
	if (gmtsupport_line_is_a_comment (line)) return false;	/* Skip commented lines like "  # anything" */
	if (gmt_strtok (line, " \t\n", &pos, word) == 0) return false;	/* Get first word in the command or fail */
	if (strcmp (word, "gmt")) return false;		/* Not starting with gmt so we are done */
	if (gmt_strtok (line, " \t\n", &pos, word) == 0) return false;	/* Get second word or fail */
	if (strcmp (word, "end")) return false;		/* Not continuing with end so we are done */
	if (gmt_strtok (line, " \t\n", &pos, word) == 0) return false;	/* Get third word or fail */
	if (!strcmp (word, "show")) return true;	/* Yes, found gmt end show */
	return false;	/* Not gmt end show */
}

bool gmt_found_modifier (struct GMT_CTRL *GMT, char *string, char *mods) {
	/* Return true if any of the modifiers listed are found in the string */
	char this_modifier[3] = {'+', ' ', '\0'};
	gmt_M_unused (GMT);
	for (unsigned int k = 0; k < strlen (mods); k++) {
		this_modifier[1] = mods[k];
		if (strstr (string, this_modifier)) return (true);	/* Found it */
	}
	return (false);
}

unsigned int gmt_unpack_rgbcolors (struct GMT_CTRL *GMT, struct GMT_IMAGE *I, unsigned char rgbmap[]) {
	unsigned int n, k = 0;
	int red;
	gmt_M_unused (GMT);
	/* Repack column-stored RGBA integer values into a row-stored RGBA byte array */
	for (n = 0; n < (unsigned int)I->n_indexed_colors && (red = gmt_M_get_rgba (I->colormap, n, 0, I->n_indexed_colors)) >= 0; n++) {
		rgbmap[k++] = red;	/* Got this already */
		rgbmap[k++] = gmt_M_get_rgba (I->colormap, n, 1, I->n_indexed_colors);
		rgbmap[k++] = gmt_M_get_rgba (I->colormap, n, 2, I->n_indexed_colors);
		rgbmap[k++] = gmt_M_get_rgba (I->colormap, n, 3, I->n_indexed_colors);
	}
	return (k/4);	/* Number of entries */
}

void gmt_format_region (struct GMT_CTRL *GMT, char *record, double *wesn) {
	/* Fancy ddd:mm:ssF typeset of -Rw/e/s/n if possible, and being aware of 360-range */
	bool wrap = false;
	enum gmt_col_enum type = gmt_get_column_type (GMT, GMT_IN, GMT_X);
	char text[GMT_LEN64] = {""}, save[GMT_LEN64];
	if (gmt_M_is_geographic (GMT, GMT_IN)) {	/* Try formal reporting */
		wrap = gmt_M_360_range (wesn[XLO], wesn[XHI]);
		strcpy (save, GMT->current.setting.format_geo_out);
		strcpy (GMT->current.setting.format_geo_out, "ddd:mm:ssF");
		gmtlib_geo_C_format (GMT);
	}
	if (wrap)	/* Do it directly */
		sprintf (record, "-R180:00:00W/180:00:00E/");
	else {
		gmt_ascii_format_one (GMT, text, wesn[XLO], type);
		sprintf (record, "-R%s/", text);	/* west or xmin */
		gmt_ascii_format_one (GMT, text, wesn[XHI], type);
		strcat (record, text);	strcat (record, "/");/* east or xmax */
	}
	type = gmt_get_column_type (GMT, GMT_IN, GMT_Y);
	gmt_ascii_format_one (GMT, text, wesn[YLO], type);
	strcat (record, text);	strcat (record, "/");/* south or ymin */
	gmt_ascii_format_one (GMT, text, wesn[YHI], type);
	strcat (record, text);	/* north or ymax */
	if (gmt_M_is_geographic (GMT, GMT_IN)) {	/* Reset */
		strcpy (GMT->current.setting.format_geo_out, save);
		gmtlib_geo_C_format (GMT);
	}
}

unsigned int gmt_get_limits (struct GMT_CTRL *GMT, char option, char *text, unsigned int mode, double *min, double *max) {
	/* Parse strings like low/high, NaN/high, low/NaN, /high, low/ and return min/max
	 * with either set to NaN if not given.  However, if mode - 1 then unset min/max becomes
	 * -DBL_MAX or +DBL_MAX instead of NaNs */
	size_t L;
	int n;
	char txt_a[GMT_LEN512] = {""}, txt_b[GMT_LEN32] = {""};
	if (!text || text[0] == '\0') {	/* Gave no argument */
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Argument is required\n", option);
		return GMT_PARSE_ERROR;
	}
	if (strchr (text, '/') == NULL) {	/* Gave no valid argument */
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Dividing slash is required\n", option);
		return GMT_PARSE_ERROR;
	}
	L = strlen (text) - 1;	/* Will be 0 or larger */
	if (text[0] == '/') {	/* Gave /max with min implicitly set to NaN */
		strcpy (txt_a, "NaN");
		strcpy (txt_b, &text[1]);
	}
	else if (text[L] == '/') {	/* Gave min/ with max implicitly set to NaN */
		strcpy (txt_a, text);	txt_a[L] = '\0';	/* Chop off the trailing / */
		strcpy (txt_b, "NaN");
	}
	else if ((n = sscanf (text, "%[^/]/%s", txt_a, txt_b)) < 2) {	/* Got min/max (either could be NaN) */
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Must specify min/max\n", option);
		return GMT_PARSE_ERROR;
	}
	/* Here we got txt_a and txt_b filled */
	if (strcasecmp (txt_a, "NAN") == 0)
		*min = GMT->session.d_NaN;
	else if (gmt_is_float (GMT, txt_a))
		*min = atof (txt_a);
	else {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Unable to parse %s\n", option, txt_a);
		return GMT_PARSE_ERROR;
	}
	if (strcasecmp (txt_b, "NAN") == 0)
		*max = GMT->session.d_NaN;
	else if (gmt_is_float (GMT, txt_b))
		*max = atof (txt_b);
	else {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Unable to parse %s\n", option, txt_b);
		return GMT_PARSE_ERROR;
	}
	if (mode) {	/* Replace any NaNs with min and max doubles */
		if (gmt_M_is_dnan (*min))
			*min = -DBL_MAX;
		if (gmt_M_is_dnan (*max))
			*max = +DBL_MAX;
	}
	else if (gmt_M_is_dnan (*min) && gmt_M_is_dnan (*max)) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: Both limits cannot be NaN\n", option);
		return GMT_PARSE_ERROR;
	}
	if (!(gmt_M_is_dnan (*min) || gmt_M_is_dnan (*max)) && *max <= *min) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: min must be less than max\n", option);
		return GMT_PARSE_ERROR;
	}
	return GMT_NOERROR;
}

double gmt_get_vector_shrinking (struct GMT_CTRL *GMT, struct GMT_VECT_ATTR *v, double magnitude, double length) {
	/* Magnitude is in data units while length is in plot units */
	double s, val;
	gmt_M_unused (GMT);
	if (v->v_norm < 0.0) return 1.0;	/* No shrinking selected */
	/* Select which amplitude to use for comparison: data magnitude or plot length */
	val = (v->v_norm_d) ? magnitude : length;
	s = (val < v->v_norm) ? val / v->v_norm : 1.0;	/* Compute scaling */
	/* Apply minimum scaling limit if set */
	if (s < v->v_norm_limit) s = v->v_norm_limit;
	GMT_Report (GMT->parent, GMT_MSG_DEBUG, "Given vector value %g and shrink limit %g, returned scale = %g\n", val, v->v_norm, s);
	return (s);
}

/* Function to assist in parsing of +w<width>[c|i|p|%][/<height[c|i|p|%]] for legends, scales etc.
 * Some features can completely auto-determine the width (e.g., the legend computes height from
 * the number of items and width from length of texts etc, while other has a default percentage
 * to use if not specified (e.g., 4% of the bar length is default bar height)
 * If +w<arg> was not given then if the def_percent_w/h are set we pass that out via R->scl. */

unsigned int gmt_rectangle_dimension (struct GMT_CTRL *GMT, struct GMT_SCALED_RECT_DIM *R, double def_percent_w, double def_percent_h, char *string) {
	int n;
	unsigned int n_percent;

	if (string == NULL || string[0] == '\0') {	/* Set default scales if given */
		R->scl[GMT_X] = 0.01 * def_percent_w;
		R->scl[GMT_Y] = 0.01 * def_percent_h;
		return (GMT_NOERROR);
	}
	if ((n = gmt_get_pair (GMT, string, GMT_PAIR_DIM_NODUP, R->dim)) == 0)
		return (GMT_RUNTIME_ERROR);
	n_percent = gmt_count_char (GMT, string, '%');

	if (n_percent) { /* Gave at least one dimension as percent of plot dimension */
		char *p = strchr (string, '%'), *slash = strchr (string, '/');	/* Find position of % and / */
		gmt_strrepc (string, '%', ' ');	/* Replace any % with spaces */
		if (n == 2) {	/* Got width/height: Check if we got 1 or 2 percentage(s) */
			slash[0] = ' ';	/* Replace / with space as well */
			if (n_percent == 2) { /* Both length and width given as percentages of plot dimensions */
				R->fraction[GMT_X] = R->fraction[GMT_Y] = true;
				sscanf (string, "%lf %lf", &R->scl[GMT_X], &R->scl[GMT_Y]);
				R->scl[GMT_X] *= 0.01;	R->scl[GMT_Y] *= 0.01;	/* Convert percent to fraction */
				gmt_M_memset (R->dim, 2U, double);	/* Wipe back to zero sine still unknown */
			}
			else {	/* Got one percent and one fixed dimension */
				if (p < slash) {	/* Gave width as percentage of plot width */
					R->fraction[GMT_X] = true;
					sscanf (string, "%lf %*s", &R->scl[GMT_X]);
					R->scl[GMT_X] *= 0.01;	/* Convert to fraction */
					R->dim[GMT_X] = 0.0;	/* Wipe back to zero (height was set by gmt_get_pair) */
				}
				else {	/* Gave height as percentage of plot height */
					R->fraction[GMT_Y] = true;
					sscanf (string, "%*s %lf", &R->scl[GMT_Y]);
					R->scl[GMT_Y] *= 0.01;	/* Convert to fraction */
					R->dim[GMT_Y] = R->dim[GMT_X] * R->scl[GMT_Y];	/* Wipe back to zero (width was set by gmt_get_pair) */
				}
			}
		}
		else {	/* Only gave width in percentage */
			R->fraction[GMT_X] = true;
			R->scl[GMT_X] = atof (string) * 0.01;	/* Convert to fraction */
			R->dim[GMT_X] = 0.0;	/* Wipe back to zero */
		}
	}	/* No percentages, got 1 or 2 dimensions */
	else {	/* If n == 2 then we got both fixed dimensions */
		if (n == 1 && fabs (R->dim[GMT_X]) > 0.0)	/* Set height as <def_percent_h>% of width */
		R->dim[GMT_Y] = R->scl[GMT_Y] * fabs (R->dim[GMT_X]);
	}
	return (GMT_NOERROR);
}

/* Helper functions to handle the parsing of option and modifier arguments that are required.
 * If argument is missing then that is an error, otherwise we parse and return */

GMT_LOCAL unsigned int gmtsupport_print_and_err (struct GMT_CTRL *GMT, char *text, char option, char modifier) {
	unsigned int error = GMT_NOERROR;
	if (!text || !text[0]) {
		if (modifier)
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: No argument provided for modifier +%c\n", option, modifier);
		else
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: No argument provided\n", option);
		error = GMT_PARSE_ERROR;
	}
	return (error);
}

unsigned int gmt_get_required_file (struct GMT_CTRL *GMT, char *text, char option, char modifier, unsigned int family, unsigned int direction, unsigned int mode, char **string) {
	/* Get required file name and do basic path checking */
	unsigned int err;
	if ((err = gmt_get_required_string (GMT, text, option, modifier, string))) return (err);
	/* Got a name, check it */
	if (GMT_Get_FilePath (GMT->parent, family, direction, mode, string))
		err++;
	return (err);
}

unsigned int gmt_get_no_argument (struct GMT_CTRL *GMT, char *text, char option, char modifier) {
	/* Return error if an argument actually was given when none is expected */
	unsigned int error = GMT_NOERROR;
	if (text && text[0]) {
		if (modifier)
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: No argument expected for modifier +%c\n", option, modifier);
		else
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Option -%c: No argument expected\n", option);
		error = GMT_PARSE_ERROR;
	}
	return (error);
}

unsigned int gmt_get_required_int64 (struct GMT_CTRL *GMT, char *text, char option, char modifier, int64_t *value) {
	/* Convert the text arg to an signed 64-bit int and if no arg given we fuss and return error */
	unsigned int err;
	if (!(err = gmtsupport_print_and_err (GMT, text, option, modifier)))
		*value = (int64_t)atol (text);
	return (err);
}

unsigned int gmt_get_required_uint64 (struct GMT_CTRL *GMT, char *text, char option, char modifier, uint64_t *value) {
	/* Convert the text arg to an unsigned 64-bit int and if no arg given we fuss and return error */
	unsigned int err;
	if (!(err = gmtsupport_print_and_err (GMT, text, option, modifier)))
		*value = (uint64_t)atol (text);
	return (err);
}

unsigned int gmt_get_required_uint (struct GMT_CTRL *GMT, char *text, char option, char modifier, unsigned int *value) {
	/* Convert the text arg to an unsigned int and if no arg given we fuss and return error */
	unsigned int err;
	if (!(err = gmtsupport_print_and_err (GMT, text, option, modifier)))
		*value = (unsigned int)atoi (text);
	return (err);
}

unsigned int gmt_get_required_int (struct GMT_CTRL *GMT, char *text, char option, char modifier, int *value) {
	/* Convert the text arg to a signed int and if no arg given we fuss and return error */
	unsigned int err;
	if (!(err = gmtsupport_print_and_err (GMT, text, option, modifier)))
		*value = atoi (text);
	return (err);
}

unsigned int gmt_get_required_float (struct GMT_CTRL *GMT, char *text, char option, char modifier, float *value) {
	/* Convert the text arg to a float and if no arg given we fuss and return error */
	unsigned int err;
	if (!(err = gmtsupport_print_and_err (GMT, text, option, modifier)))
		*value = (float)atof (text);
	return (err);
}

unsigned int gmt_get_required_double (struct GMT_CTRL *GMT, char *text, char option, char modifier, double *value) {
	/* Convert the text arg to a double and if no arg given we fuss and return error */
	unsigned int err;
	if (!(err = gmtsupport_print_and_err (GMT, text, option, modifier)))
		*value = atof (text);
	return (err);
}

unsigned int gmt_get_required_char (struct GMT_CTRL *GMT, char *text, char option, char modifier, char *letter) {
	/* Convert the text arg to a single letter and if no arg given we fuss and return error */
	unsigned int err;
	if (!(err = gmtsupport_print_and_err (GMT, text, option, modifier)))
		*letter = text[0];
	return (err);
}

unsigned int gmt_get_required_string (struct GMT_CTRL *GMT, char *text, char option, char modifier, char **string) {
	/* Convert the text arg to an allocated string and if no arg given we fuss and return error */
	unsigned int err;
	if (!(err = gmtsupport_print_and_err (GMT, text, option, modifier)))
		*string = strdup (text);
	return (err);
}
