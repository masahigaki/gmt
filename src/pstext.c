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
 * Brief synopsis: pstext will read (x, y[, z][, font, angle, justify], text) from input
 * and plot the text strings at (x,y) on a map using the font attributes
 * and justification selected by the user.  Alternatively (with -M), read
 * one or more text paragraphs to be typeset.
 *
 * Author:	Paul Wessel
 * Date:	1-JAN-2010
 * Version:	6 API
 */

#include "gmt_dev.h"
#include "longopt/pstext_inc.h"

#define THIS_MODULE_CLASSIC_NAME	"pstext"
#define THIS_MODULE_MODERN_NAME	"text"
#define THIS_MODULE_LIB		"core"
#define THIS_MODULE_PURPOSE	"Plot or typeset text"
#define THIS_MODULE_KEYS	"<D{,>X},>DL"
#define THIS_MODULE_NEEDS	"JR"
#define THIS_MODULE_OPTIONS "-:>BJKOPRUVXYaefhpqtxyw" GMT_OPT("Ec")

EXTERN_MSC void gmtlib_enforce_rgb_triplets (struct GMT_CTRL *GMT, char *text, unsigned int size);

#define PSTEXT_CLIPPLOT		1
#define PSTEXT_CLIPONLY		2

#define PSTEXT_SHOW_FONTS	128

#define GET_REC_TEXT	0	/* Free-form text as trailing text in the record */
#define GET_SEG_LABEL	1	/* Use the current segment label (-L<label>) as the text */
#define GET_SEG_HEADER	2	/* Use the current segment header as the text */
#define GET_CMD_TEXT	3	/* Use the given +t<text> as the text */
#define GET_CMD_FORMAT	4	/* Format z-column using given format (or FORMAT_FLOAT_OUT) */
#define GET_REC_NUMBER	5	/* Use record number (relative to given offset) as text */

struct PSTEXT_CTRL {
	struct PSTEXT_A {	/* -A */
		bool active;
	} A;
	struct PSTEXT_C {	/* -C[<dx>/<dy>][+to|O|c|C] */
		bool active;
		bool percent;
		double dx, dy;
		char mode;
	} C;
	struct PSTEXT_D {	/* -D[j]<dx>[/<dy>][v[<pen>]] */
		bool active;
		bool line;
		int justify;
		double dx, dy;
		struct GMT_PEN pen;
	} D;
	struct PSTEXT_F {	/* -F[+c+f<fontinfo>+a<angle>+j<justification>+l|h|r|z|t] */
		bool active;
		bool read_font;		/* True if we must read fonts from input file */
		bool orientation;	/* True if we should treat angles as orientations for text */
		bool mixed;		/* True if input record contains a text item */
		bool get_xy_from_justify;	/* True if +c was given and we just get it from input */
		bool word;		/* True if we are to select a single word from the trailing text as the label */
		bool no_input;		/* True if we give a single static text and place it via +c */
		bool no_xy_coord;	/* If -F+c given then we dont read/parse two coordinates */
		struct GMT_FONT font;
		double angle;
		int justify, R_justify, nread, nread_numerics, first, w_col;
		unsigned int get_text;	/* 0 = from data record, 1 = segment label (+l), 2 = segment header (+h), 3 = specified text (+t), 4 = format z using text (+z) */
		char read[4];		/* Contains a|A, c, f, and/or j in order required to be read from input */
		char *text;
	} F;
	struct PSTEXT_G {	/* -G<fill> | -G[+n] */
		bool active;
		unsigned int mode;
		struct GMT_FILL fill;
	} G;
	struct PSTEXT_L {	/* -L */
		bool active;
	} L;
	struct PSTEXT_M {	/* -M */
		bool active;
	} M;
	struct PSTEXT_N {	/* -N */
		bool active;
	} N;
	struct PSTEXT_Q {	/* -Q<case> */
		bool active;
		int mode;	/* 0 = do nothing, -1 = force lower case, +1 = force upper case */
	} Q;
	struct PSTEXT_S {	/* -S[dx>/<dy>/][<fill>] */
		bool active;
		double off[2];
		struct GMT_FILL fill;
	} S;
	struct PSTEXT_S_OLD {	/* -S<pen> GMT 4 syntax - deprecated */
		bool active;
		struct GMT_PEN pen;
	} S_old;
	struct PSTEXT_W {	/* -W[<pen>] */
		bool active;
		struct GMT_PEN pen;
	} W;
	struct PSTEXT_Z {	/* -Z<z_level> */
		bool active;
	} Z;
};

struct PSTEXT_INFO {
	int text_justify;
	int block_justify;
	int boxflag;
	int space_flag;
	double x_offset, y_offset;	/* Offset from reference point */
	double line_spacing;
	double paragraph_width;
	double paragraph_angle;
	double x_space, y_space;	/* Extra spacing between box and text */
	struct GMT_FONT font;
	struct GMT_PEN boxpen;
	struct GMT_PEN vecpen;
	struct GMT_FILL boxfill;
};

static void *New_Ctrl (struct GMT_CTRL *GMT) {	/* Allocate and initialize a new control structure */
	struct PSTEXT_CTRL *C;

	C = gmt_M_memory (GMT, NULL, 1, struct PSTEXT_CTRL);

	/* Initialize values whose defaults are not 0/false/NULL */

	C->D.pen = C->W.pen = GMT->current.setting.map_default_pen;
	C->C.dx = C->C.dy = GMT_TEXT_CLEARANCE;	/* 15% of font size is default clearance */
	C->C.percent = true;
	C->C.mode = 'o';	/* Rectangular box shape */
	C->F.justify = PSL_MC;		/* MC is the default */
	C->F.font = GMT->current.setting.font_annot[GMT_PRIMARY];		/* Default font */
	C->F.font.set = 0;
	gmt_init_fill (GMT, &C->G.fill, -1.0, -1.0, -1.0);	/* No fill */
	C->S_old.pen = GMT->current.setting.map_default_pen;
	C->S.off[GMT_X] = GMT->session.u2u[GMT_PT][GMT_INCH] * GMT_FRAME_CLEARANCE;	/* Default is 4p */
	C->S.off[GMT_Y] = -C->S.off[GMT_X];	/* Set the shadow offsets [default is (4p, -4p)] */
	gmt_init_fill (GMT, &C->S.fill, gmt_M_is255 (127), gmt_M_is255 (127), gmt_M_is255 (127));	/* Default if gray shade is used */

	return (C);
}

static void Free_Ctrl (struct GMT_CTRL *GMT, struct PSTEXT_CTRL *C) {	/* Deallocate control structure */
	if (!C) return;
	gmt_M_str_free (C->F.text);
	gmt_M_free (GMT, C);
}

GMT_LOCAL void pstext_output_words (struct GMT_CTRL *GMT, struct PSL_CTRL *PSL, double x, double y, char *text, struct PSTEXT_INFO *T, struct PSTEXT_CTRL *Ctrl) {
	double offset[2];

	gmt_M_memcpy (PSL->current.rgb[PSL_IS_FILL], GMT->session.no_rgb, 3, double);	/* Reset to -1,-1,-1 since text setting must set the color desired */
	gmt_M_memcpy (PSL->current.rgb[PSL_IS_STROKE], GMT->session.no_rgb, 3, double);	/* Reset to -1,-1,-1 since text setting must set the color desired */
	if (T->space_flag) {	/* Meant % of fontsize */
		offset[0] = 0.01 * T->x_space * T->font.size / PSL_POINTS_PER_INCH;
		offset[1] = 0.01 * T->y_space * T->font.size / PSL_POINTS_PER_INCH;
	}
	else {	/* Gave in distance units */
		offset[0] = T->x_space;
		offset[1] = T->y_space;
	}

	/* Set some paragraph parameters */
	PSL_setparagraph (PSL, T->line_spacing, T->paragraph_width, T->text_justify);
	PSL_setfont (PSL, T->font.id);

	if (T->boxflag & 32) {	/* Need to draw a vector from (x,y) to the offset text */
		gmt_setpen (GMT, &(T->vecpen));
		PSL_plotsegment (PSL, x, y, x + T->x_offset, y + T->y_offset);
	}
	if (Ctrl->D.justify)	/* Smart offset according to justification (from Dave Huang) */
		gmt_smart_justify (GMT, T->block_justify, T->paragraph_angle, T->x_offset, T->y_offset, &x, &y, Ctrl->D.justify);
	else
		x += T->x_offset,	y += T->y_offset;	/* Move to the actual reference point */
	if (T->boxflag) {	/* Need to lay down the box first, then place text */
		int mode = 0;
		struct GMT_FILL *fill = NULL;
		if (T->boxflag & 1) mode = PSL_RECT_STRAIGHT;			/* Set correct box shape */
		if (T->boxflag & 4) mode = PSL_RECT_ROUNDED;
		if (T->boxflag & 8) mode = PSL_RECT_CONCAVE;
		if (T->boxflag & 16) mode = PSL_RECT_CONVEX;
		if (Ctrl->S.active) {	/* Lay down shaded box first */
			PSL_setfill (PSL, Ctrl->S.fill.rgb, 0);	/* shade color */
			PSL_plotparagraphbox (PSL, x + Ctrl->S.off[GMT_X], y + Ctrl->S.off[GMT_Y], T->font.size, text, T->paragraph_angle, T->block_justify, offset, mode);
		}
		if (T->boxflag & 1) gmt_setpen (GMT, &(T->boxpen));		/* Change current pen */
		if (T->boxflag & 2) fill = &(T->boxfill);			/* Determine if fill or not */
		if (T->boxflag & 3) gmt_setfill (GMT, fill, T->boxflag & 1);	/* Change current fill and/or outline */
		/* Compute text box, draw/fill it, and in the process store the text in the PS file for next command */
		PSL_plotparagraphbox (PSL, x, y, T->font.size, text, T->paragraph_angle, T->block_justify, offset, mode);
		/* Passing NULL means we typeset using the last stored paragraph info */
		gmt_setfont (GMT, &T->font);
		PSL_plotparagraph (PSL, x, y, T->font.size, NULL, T->paragraph_angle, T->block_justify);
	}
	else {	/* No box beneath */
		gmt_setfont (GMT, &T->font);
		PSL_plotparagraph (PSL, x, y, T->font.size, text, T->paragraph_angle, T->block_justify);
	}
}

GMT_LOCAL void pstext_load_parameters_pstext (struct GMT_CTRL *GMT, struct PSTEXT_INFO *T, struct PSTEXT_CTRL *C) {
	gmt_M_memset (T, 1, struct PSTEXT_INFO);
	if (C->C.mode != 'o' && C->C.dx == 0.0 && C->C.dy == 0.0) {
		GMT_Report (GMT->parent, GMT_MSG_ERROR, "Cannot have non-rectangular text box if clearance (-C) is zero.\n");
		C->C.mode = 'o';
	}
	T->x_space = C->C.dx;
	T->y_space = C->C.dy;
	T->space_flag = (C->C.percent) ? 1 : 0;
	if (C->D.active) {
		T->x_offset = C->D.dx;
		T->y_offset = C->D.dy;
		if (C->D.line) T->boxflag |= 32;
		T->vecpen = C->D.pen;
	}
	if (C->W.active || C->G.active) {
		if (C->W.active) T->boxflag |= 1;	/* Want box outline */
		if (C->G.active) T->boxflag |= 2;	/* Want filled box */
		if (C->C.mode == 'O') T->boxflag |= 4;	/* Want rounded box outline */
		if (C->C.mode == 'c') T->boxflag |= 8;	/* Want concave box outline */
		if (C->C.mode == 'C') T->boxflag |= 16;	/* Want convex box outline */
		T->boxpen = C->W.pen;
		T->boxfill = C->G.fill;
	}
	/* Initialize default attributes */
	T->font = C->F.font;
	T->paragraph_angle = C->F.angle;
	T->block_justify = C->F.justify;
}

GMT_LOCAL int pstext_get_input_format_version (struct GMT_CTRL *GMT, char *buffer, int mode) {
	/* Try to determine if input is the old GMT4-style format.
	 * mode = 0 means normal text records, mode = 1 means paragraph mode.
	 * Return 4 if GMT 4, 5 if GMT 5, -1 if nothing can be done */

	int n, k;
	char size[GMT_LEN256] = {""}, angle[GMT_LEN256] = {""}, font[GMT_LEN256] = {""}, just[GMT_LEN256] = {""}, txt[GMT_BUFSIZ] = {""};
	char spacing[GMT_LEN256] = {""}, width[GMT_LEN256] = {""}, pjust[GMT_LEN256] = {""};

	if (!buffer || !buffer[0]) return (-1);	/* Nothing to work with */

	if (mode) {	/* Paragraph control record */
		n = sscanf (buffer, "%s %s %s %s %s %s %s\n", size, angle, font, just, spacing, width, pjust);
		if (n < 7) return (5);	/* Clearly not the old format since missing items */
	}
	else {		/* Regular text record */
		n = sscanf (buffer, "%s %s %s %s %[^\n]", size, angle, font, just, txt);
		if (n < 5) return (5);	/* Clearly not the old format since missing items */
	}
	if (gmt_not_numeric (GMT, angle)) return (5);	/* Since angle is not a number */
	k = (int)strlen (size) - 1;
	if (size[k] == 'c' || size[k] == 'i' || size[k] == 'm' || size[k] == 'p') size[k] = '\0';	/* Chop of unit */
	if (gmt_not_numeric (GMT, size)) return (5);	/* Since size is not a number */
	if (gmt_just_decode (GMT, just, PSL_NO_DEF) == -99) return (5);	/* Since justify not in correct format */
	if (mode) {	/* A few more checks for paragraph mode */
		k = (int)strlen (spacing) - 1;
		if (spacing[k] == 'c' || spacing[k] == 'i' || spacing[k] == 'm' || spacing[k] == 'p') spacing[k] = '\0';	/* Chop of unit */
		if (gmt_not_numeric (GMT, spacing)) return (5);	/* Since spacing is not a number */
		k = (int)strlen (width) - 1;
		if (width[k] == 'c' || width[k] == 'i' || width[k] == 'm' || width[k] == 'p') width[k] = '\0';	/* Chop of unit */
		if (gmt_not_numeric (GMT, width)) return (5);		/* Since width is not a number */
		if (!(pjust[0] == 'j' && pjust[1] == '\0') && gmt_just_decode (GMT, pjust, PSL_NONE) == -99) return (5);
	}

	/* Well, seems like the old format so far */
	GMT_Report (GMT->parent, GMT_MSG_COMPAT, "Use of old style pstext input is deprecated.\n");
	return (4);
}

static int usage (struct GMTAPI_CTRL *API, int level) {
	/* This displays the pstext synopsis and optionally full usage information */
	bool show_fonts = false;

	const char *name = gmt_show_name_and_purpose (API, THIS_MODULE_LIB, THIS_MODULE_CLASSIC_NAME, THIS_MODULE_PURPOSE);
	if (level & PSTEXT_SHOW_FONTS) show_fonts = true, level -= PSTEXT_SHOW_FONTS;	/* Deal with the special bitflag for showing the fonts */
	if (level == GMT_MODULE_PURPOSE) return (GMT_NOERROR);
	GMT_Usage (API, 0, "usage: %s [<table>] %s %s [-A] [%s] [-C[<dx>[/<dy>]][+tc|C|o|O]] [-D[j|J]<dx>[/<dy>][+v[<pen>]]] "
		"[-F[+a[<angle>]][+c[<justify>]][+f[<font>]][+h|l|r[<first>]|+t<text>|+z[<fmt>]][+j[<justify>]]] %s "
		"[-G[<color>][+n]] [-L] [-M] [-N] %s%s[-Ql|u] [-S[<dx>/<dy>/][<shade>]] [%s] [%s] [-W<pen>] [%s] [%s] [-Z] "
		"[%s] %s[%s] [%s] [%s] [-it<word>] [%s] [%s] [%s] [%s] [%s] [%s]\n",
		name, GMT_J_OPT, GMT_Rgeoz_OPT, GMT_B_OPT, API->K_OPT, API->O_OPT, API->P_OPT, GMT_U_OPT, GMT_X_OPT, GMT_Y_OPT,
		GMT_V_OPT, GMT_a_OPT, API->c_OPT, GMT_e_OPT, GMT_f_OPT, GMT_h_OPT, GMT_p_OPT, GMT_qi_OPT, GMT_tv_OPT,
		GMT_w_OPT, GMT_colon_OPT, GMT_PAR_OPT);
	GMT_Usage (API, -2, "Note: Reads <x,y[,fontinfo,angle,justify],text> records from <table> [or standard input], "
		"OR (with -M) one or more text paragraphs with formatting info in the segment headers. "
		"Built-in escape sequences:");
	GMT_Usage (API, 3, "%s @~ toggles between current font and Symbol font.", GMT_LINE_BULLET);
	GMT_Usage (API, 3, "%s @%%<no>%% switches to font number <no>; @%%%% resets font.", GMT_LINE_BULLET);
	GMT_Usage (API, 3, "%s @:<size>: switches font size; @:: resets font size.", GMT_LINE_BULLET);
	GMT_Usage (API, 3, "%s @;<color>; switches font color; @;; resets font color.", GMT_LINE_BULLET);
	GMT_Usage (API, 3, "%s @+ toggles between normal and superscript mode.", GMT_LINE_BULLET);
	GMT_Usage (API, 3, "%s @- toggles between normal and subscript mode.", GMT_LINE_BULLET);
	GMT_Usage (API, 3, "%s @# toggles between normal and Small Caps mode.", GMT_LINE_BULLET);
	GMT_Usage (API, 3, "%s @_ toggles between normal and underlined text.", GMT_LINE_BULLET);
	GMT_Usage (API, 3, "%s @!<char1><char2> makes one composite character.", GMT_LINE_BULLET);
	GMT_Usage (API, 3, "%s @. prints the degree symbol.", GMT_LINE_BULLET);
	GMT_Usage (API, 3, "%s @@ prints the @ sign itself.", GMT_LINE_BULLET);
	GMT_Usage (API, 3, "%s @[<LaTeX expression>@[ may be used (except for -M).", GMT_LINE_BULLET);
	GMT_Usage (API, -2, "Use @a|c|e|i|n|o|s|u|A|C|E|N|O|U for accented European characters. "
		"See module documentation for more information.\n");

	if (show_fonts) {	/* List fonts */
		unsigned int i;
		char divider[38] = {"------------------------------------"};
		int L = MAX (MIN (API->terminal_width-5, 37), 0);	/* Number of dashes to print in divider line */
		divider[L] = '\0';	/* Truncate the line */
		GMT_Usage (API, -2, "Font Number and Name:");
		gmt_message (API->GMT, "     %s\n", divider);
		for (i = 0; i < API->GMT->session.n_fonts; i++) {
			gmt_message (API->GMT, "%7ld: ", i);
			GMT_Usage (API, -9, "%s", API->GMT->session.font[i].name);
		}
		gmt_message (API->GMT, "     %s\n", divider);
		GMT_Usage (API, -2, "For additional fonts, see \"Using non-default fonts with GMT\" in the documentation.");
	}

	if (show_fonts) return (GMT_NOERROR);
	if (level == GMT_SYNOPSIS) return (GMT_MODULE_SYNOPSIS);

	GMT_Message (API, GMT_TIME_NONE, "  REQUIRED ARGUMENTS:\n");
	GMT_Usage (API, 1, "\n<table> is one or more ASCII files with text to be plotted. If no files are given, standard input is read.");
	GMT_Option (API, "J-Z,R");
	GMT_Message (API, GMT_TIME_NONE, "\n  OPTIONAL ARGUMENTS:\n");
	GMT_Usage (API, 1, "\n-A Angles given as azimuths; convert to directions using current projection.");
	GMT_Option (API, "B-");
	GMT_Usage (API, 1, "\n-C[<dx>[/<dy>]][+tc|C|o|O]");
	GMT_Usage (API, -2, "Set the clearance between characters and surrounding box. Only used "
		"if -W has been set. If <dy> is not given it equals <dx>. Append units {%s} or %% of fontsize [%d%%]. "
		"Optionally append +t<shape> when -G and/or -W is used. Append a shape:", GMT_DIM_UNITS_DISPLAY, GMT_TEXT_CLEARANCE);
	GMT_Usage (API, 3, "c: Concave rectangle (requires -M).");
	GMT_Usage (API, 3, "C: Convex rectangle (requires -M).");
	GMT_Usage (API, 3, "o: Rectangle [Default].");
	GMT_Usage (API, 3, "O: Rectangle with rounded corners.");
	GMT_Usage (API, 1, "\n-D[j|J]<dx>[/<dy>][+v[<pen>]]");
	GMT_Usage (API, -2, "Add <dx>,<dy> to the text origin AFTER projecting with -J. If <dy> is not given it equals <dx> [0/0]. "
		"Use -Dj to move text origin away from point (direction determined by text's justification). "
		"Upper case -DJ will shorten diagonal shifts at corners by sqrt(2). Cannot be used with -M. Optional modifier:");
	GMT_Usage (API, 3, "+v: Draw line from text to original point; optionally append a <pen> [%s].", gmt_putpen (API->GMT, &API->GMT->current.setting.map_default_pen));
	GMT_Usage (API, 1, "\n-F[+a[<angle>]][+c[<justify>]][+f[<font>]][+h|l|r[<first>]|+t<text>|+z[<fmt>]][+j[<justify>]]");
	GMT_Usage (API, -2, "Specify values for text attributes that apply to all text records:");
	GMT_Usage (API, 3, "+a Specify baseline <angle> for all text [0].");
	GMT_Usage (API, 3, "+A As +a but force text-baselines in the -90/+90 range.");
	GMT_Usage (API, 3, "+c Append <justify> to get the corresponding coordinate from the -R string instead of a given (x,y).");
	GMT_Usage (API, 3, "+f Set size, font, and optionally the text color [%s].",
		gmt_putfont (API->GMT, &API->GMT->current.setting.font_annot[GMT_PRIMARY]));
	GMT_Usage (API, 3, "+j Set text justification relative to given (x,y) coordinate. "
		"Give a 2-char combo from [T|M|B][L|C|R] (top/middle/bottom/left/center/right) [CM].");
	GMT_Usage (API, -2, "Normally, the text is read from the data records.  Alternative ways to provide text:");
	GMT_Usage (API, 3, "+h Use as text the most recent segment header.");
	GMT_Usage (API, 3, "+l Use as text the label specified via -L<label> in the most recent segment header.");
	GMT_Usage (API, 3, "+r Use the current record number, starting at <first> [0].");
	GMT_Usage (API, 3, "+t Use the appended <text> as is. Add modifier last if text contains + characters.");
	GMT_Usage (API, 3, "+z Use formatted input z values (but see -Z) via format <fmt> [FORMAT_FLOAT_MAP].");
	GMT_Usage (API, -2, "Note: If modifiers +f|a|j are not followed by a value then we read the information from the "
		"data file in the order given by the -F option.  Only one of +h or +l can be specified "
		"and neither can be used in paragraph mode (-M).");
	GMT_Usage (API, 1, "\n-G[<color>][+n]");
	GMT_Usage (API, -2, "Paint the box underneath the text with specified color [Default is no paint]. "
		"Alternatively, give no fill to plot text then activate clip paths based on text (and -C). "
		"Use [ps]clip -C to deactivate the clipping.  Cannot be used with paragraph mode (-M).");
	GMT_Usage (API, 3, "+n Do NOT plot the text but only activate clipping.");
	GMT_Option (API, "K");
	GMT_Usage (API, 1, "\n-L List the font-numbers and font-names available, then exits.");
	GMT_Usage (API, 1, "\n-M Set paragraph text mode [Default is single item mode]. "
		"Expects <x y fontinfo angle justify linespace parwidth parjust> in segment header "
		"followed by lines with one or more paragraphs of text. "
		"<parjust> is one of (l)eft, (c)enter, (r)ight, or (j)ustified.");
	GMT_Usage (API, 1, "\n-N Do Not clip text that exceeds the map boundaries [Default will clip].");
	GMT_Option (API, "O,P");
	GMT_Usage (API, 1, "\n-Ql|u");
	GMT_Usage (API, -2, "Force all text to be (l)lower or (u)pper-case [Default leaves text as is].");
	GMT_Usage (API, 1, "\n-S[<dx>/<dy>/][<shade>]");
	GMT_Usage (API, -2, "Plot a shadow behind the text box. Requires -G<color> to be given as well. "
		"Append <dx>/<dy> to change offset [%gp/%gp] and/or <shade> to change the shade [gray50].", GMT_FRAME_CLEARANCE, -GMT_FRAME_CLEARANCE);
	GMT_Option (API, "U,V");
	gmt_pen_syntax (API->GMT, 'W', NULL, "Draw a box around the text with the specified pen [Default pen is %s].", NULL, 0);
	GMT_Option (API, "X");
	GMT_Usage (API, 1, "\n-Z For 3-D plots: Expect records to have a z-value in the 3rd column (i.e., x y z ...). "
		"Note 1: -Z also sets -N.  Note 2: If -F+z is used the text is based on the 4th data column.");
	GMT_Option (API, "a,c,e,f,h");
	GMT_Usage (API, 1, "\n-it<word>");
	GMT_Usage (API, -2, "Append -it<word> to use word number <word> (0 is first) in the text as the label [all the text].");
	GMT_Option (API, "p,qi,t");
	GMT_Usage (API, -2, "Note: For plotting text with variable transparency read from file, give no value.");
	GMT_Option (API, "w,:,.");

	return (GMT_MODULE_USAGE);
}

static int parse (struct GMT_CTRL *GMT, struct PSTEXT_CTRL *Ctrl, struct GMT_OPTION *options) {
	/* This parses the options provided to pstext and sets parameters in Ctrl.
	 * Note Ctrl has already been initialized and non-zero default values set.
	 * Any GMT common options will override values set previously by other commands.
	 * It also replaces any file names specified as input or output with the data ID
	 * returned when registering these sources/destinations with the API.
	 */

	int j, k;
	unsigned int pos, n_errors = 0;
	bool explicit_justify = false, mess = false;
	char txt_a[GMT_LEN256] = {""}, txt_b[GMT_LEN256] = {""}, txt_c[GMT_LEN256] = {""}, p[GMT_BUFSIZ] = {""}, *c = NULL, *q = NULL;
	struct GMT_OPTION *opt = NULL;
	struct GMTAPI_CTRL *API = GMT->parent;

	for (opt = options; opt; opt = opt->next) {	/* Process all the options given */

		switch (opt->option) {

			case '<':	/* Input files */
				if (GMT_Get_FilePath (API, GMT_IS_DATASET, GMT_IN, GMT_FILE_REMOTE, &(opt->arg))) n_errors++;
				break;

			/* Processes program-specific parameters */

			case 'A':	/* Getting azimuths rather than directions, must convert via map projection */
				n_errors += gmt_M_repeated_module_option (API, Ctrl->A.active);
				n_errors += gmt_get_no_argument (GMT, opt->arg, opt->option, 0);
				break;
			case 'C':
				n_errors += gmt_M_repeated_module_option (API, Ctrl->C.active);
				c = strstr (opt->arg, "+t");
				if ((c = strstr (opt->arg, "+t"))) {
					if (c[2]) Ctrl->C.mode = c[2];
					n_errors += gmt_M_check_condition (GMT, !strchr("oOcC", Ctrl->C.mode), "Option -C: Modifier +t must add o, O, c, or C\n");
					c[0] = '\0';	/* Hide modifier */
				}
				if (opt->arg[0]) {	/* Replace default settings with user settings */
					Ctrl->C.percent = (strchr (opt->arg, '%')) ? true : false;
					k = sscanf (opt->arg, "%[^/]/%s", txt_a, txt_b);
					for (j = 0; txt_a[j]; j++) if (txt_a[j] == '%') txt_a[j] = '\0';	/* Remove % signs before processing values */
					for (j = 0; k == 2 && txt_b[j]; j++) if (txt_b[j] == '%') txt_b[j] = '\0';
					Ctrl->C.dx = (Ctrl->C.percent) ? atof (txt_a) : gmt_M_to_inch (GMT, txt_a);
					Ctrl->C.dy = (k == 2) ? ((Ctrl->C.percent) ? atof (txt_b) : gmt_M_to_inch (GMT, txt_b)) : Ctrl->C.dx;
				}
				if (c) c[0] = '+';	/* Restore */
				break;
			case 'D':
				n_errors += gmt_M_repeated_module_option (API, Ctrl->D.active);
				k = 0;
				if (opt->arg[k] == 'j') { Ctrl->D.justify = 1, k++; }
				else if (opt->arg[k] == 'J') { Ctrl->D.justify = 2, k++; }
				for (j = k; opt->arg[j] && opt->arg[j] != 'v'; j++);
				if (opt->arg[j] == 'v') {	/* Want to draw a line from point to offset point */
					Ctrl->D.line = true;
					n_errors += gmt_M_check_condition (GMT, opt->arg[j+1] && gmt_getpen (GMT, &opt->arg[j+1], &Ctrl->D.pen), "Option -D: Give pen after +v\n");
					if (opt->arg[j-1] == '+')	/* New-style syntax */
						opt->arg[j-1] = 0;
					else
						opt->arg[j] = 0;
				}
				j = sscanf (&opt->arg[k], "%[^/]/%s", txt_a, txt_b);
				Ctrl->D.dx = gmt_M_to_inch (GMT, txt_a);
				Ctrl->D.dy = (j == 2) ? gmt_M_to_inch (GMT, txt_b) : Ctrl->D.dx;
				break;
			case 'F':
				n_errors += gmt_M_repeated_module_option (API, Ctrl->F.active);
				pos = 0;
				Ctrl->F.no_input = gmt_no_pstext_input (API, opt->arg);
				if ((c = strstr (opt->arg, "+t")) && (q = strchr (&c[1], '+'))) {	/* Worry about plus symbols in the text. If not a valid modifier then we hide the plus symbol for now */
					c++;	/* Advance past the + in +t */
					gmt_strrepc (c, '+', 1);	/* Replace any other + characters with 1 */
					mess = true;
				}

				while (gmt_getmodopt (GMT, 'F', opt->arg, "Aafjclhrtz", &pos, p, &n_errors) && n_errors == 0 && Ctrl->F.nread < 4) {	/* Looking for +f, +a|A, +j, +c, +l|h */
					switch (p[0]) {
							/* A|a, f, j may be read from input */
						case 'A':	/* orientation */
							Ctrl->F.orientation = true;
							/* Intentionally fall through - to next case */
						case 'a':	/* Angle */
							if (p[1] == '+' || p[1] == '\0') {	/* Must read angle from input */
								Ctrl->F.read[Ctrl->F.nread] = p[0];
								Ctrl->F.nread++;
								Ctrl->F.nread_numerics++;
							}
							else	/* Gave a fixed angle here */
								Ctrl->F.angle = atof (&p[1]);
							break;
						case 'f':	/* Font info */
							if (p[1] == '+' || p[1] == '\0') {	/* Must read font from input */
								Ctrl->F.read[Ctrl->F.nread] = p[0];
								Ctrl->F.nread++;
								Ctrl->F.read_font = true;
								Ctrl->F.mixed = true;
							}
							else	/* Gave a fixed font here */
								n_errors += gmt_getfont (GMT, &p[1], &(Ctrl->F.font));
							break;
						case 'j':	/* Justification */
							if (p[1] == '+' || p[1] == '\0') {	/* Must read justification from input */
								Ctrl->F.read[Ctrl->F.nread] = p[0];
								Ctrl->F.nread++;
								Ctrl->F.mixed = true;
								}
							else {	/* Gave a fixed code here */
								Ctrl->F.justify = gmt_just_decode (GMT, &p[1], PSL_NO_DEF);
								explicit_justify = true;
							}
							break;
						case 'c':	/* -R corner justification */
							if (p[1] == '+' || p[1] == '\0') {	/* Must read corner justification from input */
								Ctrl->F.read[Ctrl->F.nread] = p[0];
								Ctrl->F.nread++;
								Ctrl->F.mixed = Ctrl->F.get_xy_from_justify = true;
							}
							else {	/* Gave a fixed code here */
								Ctrl->F.R_justify = gmt_just_decode (GMT, &p[1], PSL_NO_DEF);
								if (!explicit_justify)	/* If not set explicitly, default to same justification as corner */
									Ctrl->F.justify = Ctrl->F.R_justify;
							}
							Ctrl->F.no_xy_coord = true;	/* Not reading lon,lat or x,y in this case */
							break;
						case 'l':	/* Segment label request */
							if (Ctrl->F.get_text) {
								GMT_Report (API, GMT_MSG_ERROR, "Option -F: Only one of +l, +h, +r, +t, +z can be selected.\n");
								n_errors++;
							}
							else
								Ctrl->F.get_text = GET_SEG_LABEL;
							break;
						case 'h':	/* Segment header request */
							if (Ctrl->F.get_text) {
								GMT_Report (API, GMT_MSG_ERROR, "Option -F: Only one of +l, +h, +r, +t, +z can be selected.\n");
								n_errors++;
							}
							else
								Ctrl->F.get_text = GET_SEG_HEADER;
							break;
						case 'r':	/* Record number */
							if (Ctrl->F.get_text) {
								GMT_Report (API, GMT_MSG_ERROR, "Option -F: Only one of +l, +h, +r, +t, +z can be selected.\n");
								n_errors++;
							}
							else if (p[1])
								Ctrl->F.first = atoi (&p[1]);
							Ctrl->F.get_text = GET_REC_NUMBER;
							break;
						case 't':	/* Use specified text string */
							if (Ctrl->F.get_text) {
								GMT_Report (API, GMT_MSG_ERROR, "Option -F: Only one of +l, +h, +r, +t, +z can be selected.\n");
								n_errors++;
							}
							else
								Ctrl->F.text = strdup (&p[1]);
							if (mess)	/* Restore ASCII 1 to + */
								gmt_strrepc (Ctrl->F.text, 1, '+');	/* Put back the + characters */
							Ctrl->F.get_text = GET_CMD_TEXT;
							break;
						case 'z':	/* z-column formatted */
							if (Ctrl->F.get_text) {
								GMT_Report (API, GMT_MSG_ERROR, "Option -F: Only one of +l, +h, +r, +t, +z can be selected.\n");
								n_errors++;
							}
							else
								Ctrl->F.text = (p[1]) ? strdup (&p[1]) : strdup (GMT->current.setting.format_float_map);
							Ctrl->F.get_text = GET_CMD_FORMAT;
							break;
						default: break;	/* These are caught in gmt_getmodopt so break is just for Coverity */
					}
				}
				if (mess)	/* Put back the + characters */
					gmt_strrepc (opt->arg, 1, '+');
				break;
			case 'G':
				n_errors += gmt_M_repeated_module_option (API, Ctrl->G.active);
				if (!strcmp (opt->arg, "+n") || (opt->arg[0] == 'C' && !opt->arg[1]))	/* Accept -GC or -G+n */
					Ctrl->G.mode = PSTEXT_CLIPONLY;
				else if (!opt->arg[0] || (opt->arg[0] == 'c' && !opt->arg[1]))	/* Accept -Gc or -G */
					Ctrl->G.mode = PSTEXT_CLIPPLOT;
				else if (gmt_getfill (GMT, opt->arg, &Ctrl->G.fill)) {
					gmt_fill_syntax (GMT, 'G', NULL, " ");
					n_errors++;
				}
				break;
			case 'L':
				n_errors += gmt_M_repeated_module_option (API, Ctrl->L.active);
				n_errors += gmt_get_no_argument (GMT, opt->arg, opt->option, 0);
				break;
			case 'm':
				if (gmt_M_compat_check (GMT, 4)) /* Warn and pass through */
					GMT_Report (API, GMT_MSG_COMPAT, "-m option is deprecated and reverted back to -M to indicate paragraph mode.\n");
				else
					n_errors += gmt_default_option_error (GMT, opt);
				/* Intentionally fall through */
			case 'M':	/* Paragraph mode */
				n_errors += gmt_M_repeated_module_option (API, Ctrl->M.active);
				n_errors += gmt_get_no_argument (GMT, opt->arg, opt->option, 0);
				break;
			case 'N':	/* Do not clip at border */
				n_errors += gmt_M_repeated_module_option (API, Ctrl->N.active);
				n_errors += gmt_get_no_argument (GMT, opt->arg, opt->option, 0);
				break;
			case 'S':
				if (opt->arg[0] == '\0' || (k = gmt_count_char (GMT, opt->arg, '/')) > 0 || gmt_is_fill (GMT, opt->arg)) {
					/* -S[<dx>/<dy>/][>shade>]; requires -G */
					n_errors += gmt_M_repeated_module_option (API, Ctrl->S.active);
					if (opt->arg[0]) {
						k = sscanf (opt->arg, "%[^/]/%[^/]/%s", txt_a, txt_b, txt_c);
						if (k == 1) {	/* Just got a new fill */
							if (gmt_getfill (GMT, txt_a, &Ctrl->S.fill)) n_errors++;
						}
						else if (k == 2) {	/* Just got a new offset */
							if (gmt_get_pair (GMT, opt->arg, GMT_PAIR_DIM_DUP, Ctrl->S.off) < 0) n_errors++;
						}
						else if (k == 3) {	/* Got offset and fill */
							Ctrl->S.off[GMT_X] = gmt_M_to_inch (GMT, txt_a);
							Ctrl->S.off[GMT_Y] = gmt_M_to_inch (GMT, txt_b);
							if (gmt_getfill (GMT, txt_c, &Ctrl->S.fill)) n_errors++;
						}
						else n_errors++;
					} /* else we stick with the defaults */
				}
				else if (gmt_M_compat_check (GMT, 4)) { /* Warn and pass through */
					GMT_Report (API, GMT_MSG_COMPAT, "-S<pen> option is deprecated; use font pen setting instead.\n");
					n_errors += gmt_M_repeated_module_option (API, Ctrl->S_old.active);
					if (gmt_getpen (GMT, opt->arg, &Ctrl->S_old.pen)) {
						gmt_pen_syntax (GMT, 'S', NULL, "draws outline of characters.  Append pen attributes [Default pen is %s]", NULL, 0);
						n_errors++;
					}
				}
				else
					n_errors += gmt_default_option_error (GMT, opt);
				break;
			case 'Q':
				n_errors += gmt_M_repeated_module_option (API, Ctrl->Q.active);
				if (opt->arg[0] == 'l') Ctrl->Q.mode = -1;
				if (opt->arg[0] == 'u') Ctrl->Q.mode = +1;
				break;
			case 'T':
				if (gmt_M_compat_check (GMT, 5)) { /* Warn and pass through */
					GMT_Report (API, GMT_MSG_COMPAT, "-T option is deprecated; use modifier +t in -C instead.\n");
					if (opt->arg[0]) Ctrl->C.mode = opt->arg[0];
					n_errors += gmt_M_check_condition (GMT, !strchr("oOcC", Ctrl->C.mode), "Option -T: must add o, O, c, or C\n");
				}
				else
					n_errors += gmt_default_option_error (GMT, opt);
				break;
			case 'W':
				n_errors += gmt_M_repeated_module_option (API, Ctrl->W.active);
				if (gmt_getpen (GMT, opt->arg, &Ctrl->W.pen)) {
					gmt_pen_syntax (GMT, 'W', NULL, "draws a box around the text with the specified pen [Default pen is %s]", NULL, 0);
					n_errors++;
				}
				break;
			case 'Z':
				/* For backward compatibility we will see -Z+ as the current -Z
				 * and -Z<level> as an alternative to -p<az>/<el>/<level> */
				if (opt->arg[0] == '+' && !opt->arg[1])	{	/* Deprecated -Z+ option */
					n_errors += gmt_M_repeated_module_option (API, Ctrl->Z.active);
				}
				else if (opt->arg[0])	/* Deprecated -Z<level> option */
					GMT->current.proj.z_level = atof(opt->arg);
				else {	/* Normal -Z only */
					n_errors += gmt_M_repeated_module_option (API, Ctrl->Z.active);
				}
				break;

			case 'i':	/* Local -i option for pstext to select a specific word in the text */
				if (opt->arg[0] != 't') {
					GMT_Report (API, GMT_MSG_ERROR, "Option -i: Must give -it<word> from 0 (first) to nwords-1.\n");
					n_errors++;
				}
				else {
					Ctrl->F.word = true;
					Ctrl->F.w_col = atoi (&opt->arg[1]);
					if (Ctrl->F.w_col < 0) {
						GMT_Report (API, GMT_MSG_ERROR, "Option -it<word>: Must select <word> from 0 (first) to nwords-1.\n");
						n_errors++;
					}
					else
						Ctrl->F.w_col++;	/* So 0th word is 1 */
				}
				break;

			default:	/* Report bad options */
				n_errors += gmt_default_option_error (GMT, opt);
				break;
		}
	}

	/* Check that the options selected are mutually consistent */

	if (API->external && Ctrl->F.active && Ctrl->F.nread) {	/* Impose order on external interfaces */
		n_errors += gmt_M_check_condition (GMT, Ctrl->F.nread == 2 && tolower (Ctrl->F.read[1]) == 'a', "Option -F: Must list +a before +c, +f, +j for external API\n");
		n_errors += gmt_M_check_condition (GMT, Ctrl->F.nread == 3 && (tolower (Ctrl->F.read[1]) == 'a' || tolower (Ctrl->F.read[2]) == 'a'), "Option -F: Must list +a before +c, +f, +j for external API\n");
		n_errors += gmt_M_check_condition (GMT, Ctrl->F.nread == 4 && (tolower (Ctrl->F.read[2]) == 'a' || tolower (Ctrl->F.read[2]) == 'a' || tolower (Ctrl->F.read[3]) == 'a'), "Option -F: Must list +a before +c, +f, +j for external API\n");
	}
	n_errors += gmt_M_check_condition (GMT, !Ctrl->L.active && !GMT->common.R.active[RSET], "Must specify -R option\n");
	n_errors += gmt_M_check_condition (GMT, !Ctrl->L.active && !GMT->common.J.active, "Must specify a map projection with the -J option\n");
	n_errors += gmt_M_check_condition (GMT, Ctrl->C.dx < 0.0 || Ctrl->C.dy < 0.0, "Option -C: clearances cannot be negative!\n");
	n_errors += gmt_M_check_condition (GMT, Ctrl->C.dx == 0.0 && Ctrl->C.dy == 0.0  && Ctrl->C.mode != 'o', "Option -C: Non-rectangular text boxes require a non-zero clearance\n");
	n_errors += gmt_M_check_condition (GMT, Ctrl->D.dx == 0.0 && Ctrl->D.dy == 0.0 && Ctrl->D.line, "-D<x/y>v requires one nonzero <x/y>\n");
	n_errors += gmt_M_check_condition (GMT, Ctrl->Q.active && abs (Ctrl->Q.mode) > 1, "Option -Q: Use l or u for lower/upper-case.\n");
	n_errors += gmt_M_check_condition (GMT, Ctrl->G.mode && Ctrl->M.active, "Option -Gc: Cannot be used with -M.\n");
	n_errors += gmt_M_check_condition (GMT, Ctrl->G.mode && Ctrl->W.active, "Option -Gc: Cannot be used with -W.\n");
	n_errors += gmt_M_check_condition (GMT, Ctrl->G.mode && Ctrl->D.line, "Option -Gc: Cannot be used with -D...v<pen>.\n");
	n_errors += gmt_M_check_condition (GMT, Ctrl->M.active && Ctrl->F.get_text, "Option -M: Cannot be used with -F...+l|h|r|t|z.\n");
	n_errors += gmt_M_check_condition (GMT, Ctrl->S.active && !(Ctrl->G.active && Ctrl->G.mode == 0), "Option -S: Requires -G as well.\n");
	n_errors += gmt_M_check_condition (GMT, strchr ("cC", Ctrl->C.mode) && !Ctrl->M.active, "Option -C: Box shape mode +tc|C is only available when -M is selected.\n");

	return (n_errors ? GMT_PARSE_ERROR : GMT_NOERROR);
}

GMT_LOCAL void pstext_add_xy_via_justify (struct GMT_CTRL *GMT, int justify) {
	/* If -F+c, compute the missing x,y and place in current input record */
	int ix, iy;

	ix = (GMT->current.setting.io_lonlat_toggle[GMT_IN]);	iy = 1 - ix;
	gmt_just_to_xy (GMT, justify, &GMT->current.io.curr_rec[ix], &GMT->current.io.curr_rec[iy]);
	GMT->current.io.curr_rec[GMT_Z] = GMT->current.proj.z_level;
}

GMT_LOCAL int pstext_validate_coord_and_text (struct GMT_CTRL *GMT, struct PSTEXT_CTRL *Ctrl, int rec_no, char *record, char buffer[]) {
	/* Paragraph mode: Parse x,y [and z], check for validity, and return the rest of the text in buffer */
	int ix, iy, nscan = 0;
	unsigned int pos = 0;
	char txt_x[GMT_LEN256] = {""}, txt_y[GMT_LEN256] = {""}, txt_z[GMT_LEN256] = {""}, txt_t[GMT_LEN256] = {""};

	ix = (GMT->current.setting.io_lonlat_toggle[GMT_IN]);	iy = 1 - ix;
	buffer[0] = '\0';	/* Initialize buffer to NULL */

	if (Ctrl->Z.active) {	/* Expect z in 3rd column */
		if (gmt_strtok (record, GMT->current.io.scan_separators, &pos, txt_x)) nscan++;	/* Returns xcol and update pos */
		if (gmt_strtok (record, GMT->current.io.scan_separators, &pos, txt_y)) nscan++;	/* Returns ycol and update pos */
		if (gmt_strtok (record, GMT->current.io.scan_separators, &pos, txt_z)) nscan++;	/* Returns zcol and update pos */
		if (GMT->common.t.variable && gmt_strtok (record, GMT->current.io.scan_separators, &pos, txt_t)) nscan++;	/* Returns first tcol and update pos */
		if (GMT->common.t.n_transparencies == 2 && gmt_strtok (record, GMT->current.io.scan_separators, &pos, txt_t)) nscan++;	/* Returns second tcol and update pos */
		strcpy (buffer, &record[pos]);
		sscanf (&record[pos], "%[^\n]\n", buffer);	nscan++;	/* Since sscanf could return -1 if nothing we increment nscan always */
		if ((gmt_scanf (GMT, txt_z, gmt_M_type (GMT, GMT_IN, GMT_Z), &GMT->current.io.curr_rec[GMT_Z]) == GMT_IS_NAN)) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Record %d had bad z coordinate, skipped)\n", rec_no);
			return (-1);
		}
		if ((gmt_scanf (GMT, txt_t, GMT_IS_FLOAT, &GMT->current.io.curr_rec[3]) == GMT_IS_NAN)) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Record %d had bad transparency, skipped)\n", rec_no);
			return (-1);
		}
	}
	else if (Ctrl->F.R_justify) {
		gmt_just_to_xy (GMT, Ctrl->F.R_justify, &GMT->current.io.curr_rec[ix], &GMT->current.io.curr_rec[iy]);
		nscan = 2;	/* Since x,y are implicit */
		nscan += sscanf (record, "%[^\n]\n", buffer);
		GMT->current.io.curr_rec[GMT_Z] = GMT->current.proj.z_level;
	}
	else {
		if (gmt_strtok (record, GMT->current.io.scan_separators, &pos, txt_x)) nscan++;	/* Returns xcol and update pos */
		if (gmt_strtok (record, GMT->current.io.scan_separators, &pos, txt_y)) nscan++;	/* Returns ycol and update pos */
		if (GMT->common.t.variable && gmt_strtok (record, GMT->current.io.scan_separators, &pos, txt_t)) nscan++;	/* Returns first tcol and update pos */
		if (GMT->common.t.n_transparencies == 2 && gmt_strtok (record, GMT->current.io.scan_separators, &pos, txt_t)) nscan++;	/* Returns first tcol and update pos */
		sscanf (&record[pos], "%[^\n]\n", buffer);	nscan++;	/* Since sscanf could return -1 if nothing we increment nscan always */
		GMT->current.io.curr_rec[GMT_Z] = GMT->current.proj.z_level;
		if ((gmt_scanf (GMT, txt_t, GMT_IS_FLOAT, &GMT->current.io.curr_rec[2]) == GMT_IS_NAN)) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Record %d had bad transparency, skipped)\n", rec_no);
			return (-1);
		}
	}

	if (!Ctrl->F.R_justify) {
		if (gmt_scanf (GMT, txt_x, gmt_M_type (GMT, GMT_IN, GMT_X), &GMT->current.io.curr_rec[ix]) == GMT_IS_NAN) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Record %d had bad x coordinate, skipped)\n", rec_no);
			return (-1);
		}
		if (gmt_scanf (GMT, txt_y, gmt_M_type (GMT, GMT_IN, GMT_Y), &GMT->current.io.curr_rec[iy]) == GMT_IS_NAN) {
			GMT_Report (GMT->parent, GMT_MSG_ERROR, "Record %d had bad y coordinate, skipped)\n", rec_no);
			return (-1);
		}
	}
	return (nscan);
}

#define bailout(code) {gmt_M_free_options (mode); return (code);}
#define Return(code) {Free_Ctrl (GMT, Ctrl); gmt_end_module (GMT, GMT_cpy); bailout (code);}

GMT_LOCAL char *pstext_get_label (struct GMT_CTRL *GMT, struct PSTEXT_CTRL *Ctrl, char *txt) {
	char *out = NULL;
	if (Ctrl->F.word) {	/* Must output a specific word from the trailing text only */
		char *word = NULL, *orig = strdup (txt), *trail = orig;
		int col = 0;
		while (col != Ctrl->F.w_col && (word = strsep (&trail, GMT_TOKEN_SEPARATORS)) != NULL) {
			if (*word != '\0')	/* Skip empty strings */
				col++;
		}
		if (word)	/* Only write word if not NULL */
			out = strdup (word);
		else {
			GMT_Report (GMT->parent, GMT_MSG_WARNING, "Trailing text did not have %d words (only %d found) - no label selected.\n", Ctrl->F.w_col, col);
			out = strdup ("");
		}
		gmt_M_str_free (orig);
	}
	else	/* Return copy of the whole enchilada */
		out = strdup (txt);
	return (out);	/* The main program must free this at the end of each record processing */
}

EXTERN_MSC int GMT_pstext (void *V_API, int mode, void *args) {
	/* High-level function that implements the pstext task */

	int  error = 0, k, fmode, nscan = 0, *c_just = NULL;
	int input_format_version = GMT_NOTSET, rec_number = 0;

	bool master_record = false, skip_text_records = false, old_is_world, clip_set = false, no_in_txt, check_if_outside;

	unsigned int length = 0, n_paragraphs = 0, n_add, m = 0, pos, text_col, rec_mode, a_col = 0, tcol_f = 0, tcol_s = 0;
	unsigned int n_read = 0, n_processed = 0, txt_alloc = 0, add, n_expected_cols, z_col = GMT_Z, n_skipped = 0;

	size_t n_alloc = 0;

	double plot_x = 0.0, plot_y = 0.0, save_angle = 0.0, xx[2] = {0.0, 0.0}, yy[2] = {0.0, 0.0}, *in = NULL;
	double offset[2], tmp, *c_x = NULL, *c_y = NULL, *c_angle = NULL;

	char text[GMT_BUFSIZ] = {""}, cp_line[GMT_BUFSIZ] = {""}, label[GMT_BUFSIZ] = {""}, buffer[GMT_BUFSIZ] = {""};
	char pjust_key[5] = {""}, txt_a[GMT_LEN256] = {""}, txt_b[GMT_LEN256] = {""}, txt_f[GMT_LEN256] = {""};
	char *paragraph = NULL, *line = NULL, *curr_txt = NULL, *in_txt = NULL, **c_txt = NULL, *use_text = NULL;
	char this_size[GMT_LEN256] = {""}, this_font[GMT_LEN256] = {""}, just_key[5] = {""}, save_h_chars[GMT_LEN32] = {""};

	enum GMT_enum_geometry geometry;

	struct GMT_FONT *c_font = NULL;
	struct PSTEXT_INFO T;
	struct GMT_RECORD *In = NULL;
	struct PSTEXT_CTRL *Ctrl = NULL;
	struct GMT_CTRL *GMT = NULL, *GMT_cpy = NULL;		/* General GMT internal parameters */
	struct GMT_OPTION *options = NULL;
	struct PSL_CTRL *PSL = NULL;		/* General PSL internal parameters */
	struct GMTAPI_CTRL *API = gmt_get_api_ptr (V_API);	/* Cast from void to GMTAPI_CTRL pointer */

	/*----------------------- Standard module initialization and parsing ----------------------*/

	if (API == NULL) return (GMT_NOT_A_SESSION);
	if (mode == GMT_MODULE_PURPOSE) return (usage (API, GMT_MODULE_PURPOSE));	/* Return the purpose of program */
	options = GMT_Create_Options (API, mode, args);	if (API->error) return (API->error);	/* Set or get option list */

	if ((error = gmt_report_usage (API, options, 0, usage)) != GMT_NOERROR) bailout (error);	/* Give usage if requested */

	/* Parse the command-line arguments; return if errors are encountered */

	if ((GMT = gmt_init_module (API, THIS_MODULE_LIB, THIS_MODULE_CLASSIC_NAME, THIS_MODULE_KEYS, THIS_MODULE_NEEDS, module_kw, &options, &GMT_cpy)) == NULL) bailout (API->error); /* Save current state */
	if (GMT_Parse_Common (API, THIS_MODULE_OPTIONS, options)) Return (API->error);
	Ctrl = New_Ctrl (GMT);	/* Allocate and initialize a new control structure */
	if ((error = parse (GMT, Ctrl, options)) != 0) Return (error);
	if (Ctrl->L.active) Return (usage (API, GMT_SYNOPSIS | PSTEXT_SHOW_FONTS));	/* Return the synopsis with font listing */

	/*---------------------------- This is the pstext main code ----------------------------*/

	GMT_Report (API, GMT_MSG_INFORMATION, "Processing input text table data\n");
	pstext_load_parameters_pstext (GMT, &T, Ctrl);	/* Pass info from Ctrl to T */
	tcol_f = 2 + Ctrl->Z.active;	tcol_s = tcol_f + 1;
	/* Since pstext input is complicated we need to help gmtio_examine_current_record by determining how many leading numerical columns to expect */
	API->n_numerical_columns = (Ctrl->F.no_xy_coord) ? 0 : 2;	/* Normally first 2 columns are x/y coordinates but not if -F+c */
	if (Ctrl->F.get_text == GET_CMD_FORMAT) API->n_numerical_columns++;	/* Expect a 3rd column value for formatting */ 
	if (Ctrl->Z.active) API->n_numerical_columns++;	/* Expect a 3-D z coordinate */
	if (Ctrl->F.nread_numerics) API->n_numerical_columns++;	/* Will read angle from input file */
	n_expected_cols = 2 + Ctrl->Z.active + Ctrl->F.nread + GMT->common.t.n_transparencies;	/* Normal number of columns to read, plus any text. This includes x,y */
	if (Ctrl->M.active) n_expected_cols += 3;
	no_in_txt = (Ctrl->F.get_text > 1);	/* No text in the input record */

	if (gmt_map_setup (GMT, GMT->common.R.wesn)) Return (GMT_PROJECTION_ERROR);

	if (Ctrl->G.mode) GMT->current.ps.nclip = (Ctrl->N.active) ? +1 : +2;	/* Signal that this program initiates clipping that will outlive this process */

	if ((PSL = gmt_plotinit (GMT, options)) == NULL) Return (GMT_RUNTIME_ERROR);

	gmt_plane_perspective (GMT, GMT->current.proj.z_project.view_plane, GMT->current.proj.z_level);
	if (Ctrl->G.mode)	/* Delayed clipping so plot -B first */
		gmt_set_basemap_orders (GMT, GMT_BASEMAP_FRAME_BEFORE, GMT_BASEMAP_GRID_BEFORE, GMT_BASEMAP_ANNOT_BEFORE);
	else
		gmt_set_basemap_orders (GMT, Ctrl->N.active ? GMT_BASEMAP_FRAME_BEFORE : GMT_BASEMAP_FRAME_AFTER, GMT_BASEMAP_GRID_BEFORE, GMT_BASEMAP_ANNOT_BEFORE);
	gmt_plotcanvas (GMT);	/* Fill canvas if requested */
	gmt_map_basemap (GMT);

	if (gmt_M_is_dnan (Ctrl->F.font.size))
		Ctrl->F.font.size = GMT->current.setting.font_annot[GMT_PRIMARY].size;

	pstext_load_parameters_pstext (GMT, &T, Ctrl);	/* Pass info from Ctrl to T */
	add = !(T.x_offset == 0.0 && T.y_offset == 0.0);
	if (add && Ctrl->D.justify) T.boxflag |= 64;

	if (!(Ctrl->N.active || Ctrl->Z.active)) {
		gmt_BB_clip_on (GMT, GMT->session.no_rgb, 3);
		clip_set = true;
	}

	if (Ctrl->F.nread && tolower (Ctrl->F.read[0]) == 'a') a_col = 1;	/* Must include the a col among the numerics */
	/* Find start column of plottable text in the trailing text string */
	text_col = Ctrl->F.nread - a_col;

	old_is_world = GMT->current.map.is_world;
	GMT->current.map.is_world = true;
	check_if_outside = !(Ctrl->N.active || Ctrl->F.get_xy_from_justify || Ctrl->F.R_justify);

	if (Ctrl->F.no_input) {	/* Plot the single label and bail.  However, must set up everything else as normal */
		int ix, iy;
		double coord[2];
		ix = (GMT->current.setting.io_lonlat_toggle[GMT_IN]);	iy = 1 - ix;

		/* Here, in_txt holds the text we wish to plot */

		strcpy (text, Ctrl->F.text);	/* Since we may need to do some replacements below */
		in_txt = text;
		gmtlib_enforce_rgb_triplets (GMT, in_txt, GMT_BUFSIZ);	/* If @; is used, make sure the color information passed on to ps_text is in r/b/g format */
		if (Ctrl->Q.active) gmt_str_setcase (GMT, in_txt, Ctrl->Q.mode);
		use_text = pstext_get_label (GMT, Ctrl, in_txt);	/* In case there are words */
		pstext_add_xy_via_justify (GMT, Ctrl->F.R_justify);
		plot_x = GMT->current.io.curr_rec[ix]; plot_y = GMT->current.io.curr_rec[iy];
		xx[0] = plot_x;	yy[0] = plot_y;

		if (Ctrl->A.active) {
			gmt_xy_to_geo (GMT, &coord[GMT_X], &coord[GMT_Y], plot_x, plot_y);	/* Need original coordinates */
			save_angle = T.paragraph_angle;	/* Since we might overwrite the default */
			tmp = gmt_azim_to_angle (GMT, coord[GMT_X], coord[GMT_Y], 0.1, save_angle);
			T.paragraph_angle = fmod (tmp + 360.0 + 90.0, 180.0) - 90.0;	/* Ensure usable angles for text plotting */
			if (fabs (T.paragraph_angle - tmp) > 179.0) T.block_justify -= 2 * (T.block_justify%4 - 2);	/* Flip any L/R code */
		}
		if (Ctrl->F.orientation) {
			if (T.paragraph_angle > 180.0) T.paragraph_angle -= 360.0;
			if (T.paragraph_angle > 90.0) T.paragraph_angle -= 180.0;
			else if (T.paragraph_angle < -90.0) T.paragraph_angle += 180.0;
		}
		if (add) {
			if (Ctrl->D.justify)	/* Smart offset according to justification (from Dave Huang) */
				gmt_smart_justify (GMT, T.block_justify, T.paragraph_angle, T.x_offset, T.y_offset, &plot_x, &plot_y, Ctrl->D.justify);
			else {	/* Default hard offset */
				plot_x += T.x_offset;
				plot_y += T.y_offset;
			}
			xx[1] = plot_x;	yy[1] = plot_y;
		}

		PSL_setfont (PSL, T.font.id);
		gmt_plane_perspective (GMT, GMT->current.proj.z_project.view_plane, 0.0);
		if (T.boxflag & 32) {	/* Draw line from original point to shifted location */
			gmt_setpen (GMT, &T.vecpen);
			PSL_plotsegment (PSL, xx[0], yy[0], xx[1], yy[1]);
		}
		if (!Ctrl->G.mode && T.boxflag & 3) {	/* Plot the box beneath the text */
			if (T.space_flag) {	/* Meant % of fontsize */
				offset[0] = 0.01 * T.x_space * T.font.size / PSL_POINTS_PER_INCH;
				offset[1] = 0.01 * T.y_space * T.font.size / PSL_POINTS_PER_INCH;
			}
			else {
				offset[0] = T.x_space;
				offset[1] = T.y_space;
			}
			if (Ctrl->S.active) {	/* Lay down shaded box first */
				PSL_setfill (PSL, Ctrl->S.fill.rgb, 0);	/* shade color */
				PSL_plottextbox (PSL, plot_x + Ctrl->S.off[GMT_X], plot_y + Ctrl->S.off[GMT_Y], T.font.size, use_text, T.paragraph_angle, T.block_justify, offset, T.boxflag & 4);
			}
			gmt_setpen (GMT, &T.boxpen);			/* Box pen */
			PSL_setfill (PSL, T.boxfill.rgb, T.boxflag & 1);	/* Box color */
			PSL_plottextbox (PSL, plot_x, plot_y, T.font.size, use_text, T.paragraph_angle, T.block_justify, offset, T.boxflag & 4);
			curr_txt = NULL;	/* Text has now been encoded in the PS file */
		}
		else
			curr_txt = use_text;
		fmode = gmt_setfont (GMT, &T.font);

		PSL_plottext (PSL, plot_x, plot_y, T.font.size, curr_txt, T.paragraph_angle, T.block_justify, fmode);

		if (clip_set)
			gmt_map_clip_off (GMT);
		gmt_map_basemap (GMT);
		gmt_plane_perspective (GMT, -1, 0.0);
		gmt_plotend (GMT);
		gmt_M_str_free (use_text);

		Return (GMT_NOERROR);
	}

	in = GMT->current.io.curr_rec;	/* Since text gets parsed and stored in this record */
	if (Ctrl->F.read_font)
		GMT->current.io.scan_separators = GMT_TOKEN_SEPARATORS_PSTEXT;		/* Characters that may separate columns in ASCII records */
	if (Ctrl->M.active) {	/* There are no coordinates, just text lines */
		rec_mode = GMT_READ_TEXT;
		geometry = GMT_IS_TEXT;
		GMT_Set_Columns (API, GMT_IN, 0, GMT_COL_FIX);
		strncpy (save_h_chars, GMT->current.setting.io_head_marker_in, GMT_LEN32);	/* Must allow quotes and percentage signs in paragraph text */
		strcpy (GMT->current.setting.io_head_marker_in, "#");
	}
	else {
		unsigned int ncol = Ctrl->Z.active;	/* Input will have z */
		unsigned int cmode = GMT_COL_FIX;	/* Normally there will be trailing text */
		unsigned int code = 0;
		char *cmode_type[2] = {"with", "with no"}, *rtype[4] = {"", "data", "text", "mixed"};
		if (!Ctrl->F.get_xy_from_justify && Ctrl->F.R_justify == 0) ncol += 2;	/* Expect input to have x,y */
		ncol += a_col;				/* Might also have the angle among the numerical columns */
		if (Ctrl->F.get_text == GET_CMD_FORMAT) {	/* Format z column into text */
            		z_col = ncol - a_col;    /* Normally this would be GMT_Z */
			ncol++;	/* One more numerical column to read */
			rec_mode = (Ctrl->F.mixed) ? GMT_READ_MIXED : GMT_READ_DATA;
			geometry = (Ctrl->F.mixed) ? GMT_IS_NONE : GMT_IS_POINT;
			if (!Ctrl->F.mixed) cmode =  GMT_COL_FIX_NO_TEXT;
			code = 1;
			PSL_settextmode (PSL, PSL_TXTMODE_MINUS);	/* Replace hyphens with minus signs */
		}
		else if (Ctrl->F.get_text == GET_REC_NUMBER) {	/* Format record number into text */
			rec_mode = (ncol) ? GMT_READ_MIXED : GMT_READ_DATA;
			geometry = (ncol) ? GMT_IS_NONE : GMT_IS_POINT;
			if (ncol == 0) cmode = GMT_COL_FIX_NO_TEXT;
			code = 1;
		}
		else {	/* Text is part of the record */
			rec_mode = (ncol) ? GMT_READ_MIXED : GMT_READ_TEXT;
			geometry = (ncol) ? GMT_IS_NONE : GMT_IS_TEXT;
		}
		if (a_col) a_col = ncol - 1;	/* Now refers to numerical column with the angle */
		if (GMT->common.t.variable) {
			if (GMT->common.t.mode & GMT_SET_FILL_TRANSP) {
				ncol++;	/* Read fill transparencies from data file */
				tcol_f = ncol - 1;	/* If there is fill transparency then this is the column to use */
				gmt_set_column_type (GMT, GMT_IN, tcol_f, GMT_IS_FLOAT);
			}
			if (GMT->common.t.mode & GMT_SET_PEN_TRANSP) {
				ncol++;	/* Read stroke transparencies from data file */
				tcol_s = ncol - 1;
				gmt_set_column_type (GMT, GMT_IN, tcol_s, GMT_IS_FLOAT);
			}
		}
		GMT_Report (API, GMT_MSG_DEBUG, "Expects a %s record with %d leading numerical columns, followed by %d text parameters and %s trailing text\n",
			rtype[rec_mode], ncol, Ctrl->F.nread - a_col, cmode_type[code]);
		GMT_Set_Columns (API, GMT_IN, ncol, cmode);
		GMT->current.io.curr_rec[GMT_Z] = GMT->current.proj.z_level;	/* In case there are 3-D going on */
	}
	if (GMT_Init_IO (API, GMT_IS_DATASET, geometry, GMT_IN, GMT_ADD_DEFAULT, 0, options) != GMT_NOERROR) {	/* Register data input */
		Return (API->error);
	}
	if (GMT_Begin_IO (API, GMT_IS_DATASET, GMT_IN, GMT_HEADER_ON) != GMT_NOERROR) {	/* Enables data input and sets access mode */
		Return (API->error);
	}

	if (Ctrl->G.mode) {	/* Need arrays to keep all the information until we lay it down in PSL */
		n_alloc = 0;
		gmt_M_malloc3 (GMT, c_angle, c_x, c_y, GMT_SMALL_CHUNK, &n_alloc, double);
		c_txt = gmt_M_memory (GMT, NULL, n_alloc, char *);
		c_just = gmt_M_memory (GMT, NULL, n_alloc, int);
		c_font = gmt_M_memory (GMT, NULL, n_alloc, struct GMT_FONT);
	}
	rec_number = Ctrl->F.first;	/* Number of first output record label if -F+r<first> was selected */

	do {	/* Keep returning records until we have no more files */
		if ((In = GMT_Get_Record (API, rec_mode, NULL)) == NULL) {	/* Keep returning records until we have no more files */
			if (gmt_M_rec_is_error (GMT)) {
				Return (GMT_RUNTIME_ERROR);
			}
			if (gmt_M_rec_is_table_header (GMT))
				continue;	/* Skip table headers */
			if (gmt_M_rec_is_eof (GMT)) 		/* Reached end of file */
				break;
			/* Note: Blank lines may call through below - this is OK; hence no extra continue here */
		}

		/* Data record or segment header (line == NULL) to process */

		if (Ctrl->M.active) {	/* Paragraph mode */
			if (gmt_M_rec_is_segment_header (GMT)) {
				line = GMT->current.io.segment_header;
				if (line[0] == '\0') continue;	/* Can happen if reading from API memory */
				skip_text_records = false;
				if (n_processed) {	/* Must output what we got */
					pstext_output_words (GMT, PSL, plot_x, plot_y, paragraph, &T, Ctrl);
					n_processed = length = 0;
					paragraph[0] = 0;	/* Empty existing text */
					n_paragraphs++;
				}

				if (line && (nscan = pstext_validate_coord_and_text (GMT, Ctrl, n_read, line, buffer)) == -1) continue;	/* Failure */

				if (Ctrl->F.R_justify) pstext_add_xy_via_justify (GMT, Ctrl->F.R_justify);

				pos = 0;

				if (gmt_M_compat_check (GMT, 4)) {
					if (input_format_version == GMT_NOTSET) input_format_version = pstext_get_input_format_version (GMT, buffer, 1);
				}
				if (input_format_version == 4) {	/* Old-style GMT 4 records */
					nscan += sscanf (buffer, "%s %lf %s %s %s %s %s\n", this_size, &T.paragraph_angle, this_font, just_key, txt_a, txt_b, pjust_key);
					T.block_justify = gmt_just_decode (GMT, just_key, PSL_NO_DEF);
					T.line_spacing = gmt_M_to_inch (GMT, txt_a);
					T.paragraph_width  = gmt_M_to_inch (GMT, txt_b);
					T.text_justify = (pjust_key[0] == 'j') ? PSL_JUST : gmt_just_decode (GMT, pjust_key, PSL_NONE);
					sprintf (txt_f, "%s,%s,", this_size, this_font);	/* Merge size and font to be parsed by gmt_getfont */
					T.font = Ctrl->F.font;
					if (gmt_getfont (GMT, txt_f, &T.font)) GMT_Report (API, GMT_MSG_ERROR, "Record %d had bad font (set to %s)\n", n_read, gmt_putfont (GMT, &T.font));
					in_txt = NULL;
					n_expected_cols = 9 + Ctrl->Z.active;
				}
				else if (!Ctrl->F.nread)	/* All attributes given via -F (or we accept defaults); skip to paragraph attributes */
					in_txt = buffer;
				else {	/* Must pick up 1-3 attributes from data file */
					for (k = 0; k < Ctrl->F.nread; k++) {
						nscan += gmt_strtok (buffer, GMT->current.io.scan_separators, &pos, text);
						switch (Ctrl->F.read[k]) {
							case 'f':
								T.font = Ctrl->F.font;
								if (gmt_getfont (GMT, text, &T.font)) GMT_Report (API, GMT_MSG_ERROR, "Record %d had bad font (set to %s)\n", n_read, gmt_putfont (GMT, &T.font));
								break;
							case 'a': case 'A':
								T.paragraph_angle = atof (text);
								break;
							case 'j':
								T.block_justify = gmt_just_decode (GMT, text, PSL_NO_DEF);
								break;
						}
					}
					in_txt = &buffer[pos];
				}

				if (in_txt) {	/* Get the remaining parameters */
					nscan += sscanf (in_txt, "%s %s %s\n", txt_a, txt_b, pjust_key);
					T.text_justify = (pjust_key[0] == 'j') ? PSL_JUST : gmt_just_decode (GMT, pjust_key, PSL_NONE);
					T.line_spacing = gmt_M_to_inch (GMT, txt_a);
					T.paragraph_width  = gmt_M_to_inch (GMT, txt_b);
				}
				if (T.block_justify == -99) {
					GMT_Report (API, GMT_MSG_ERROR, "Record %d had bad justification info (set to LB)\n", n_read);
					T.block_justify = 1;
				}
				if (nscan < (int)n_expected_cols) {
					GMT_Report (API, GMT_MSG_ERROR, "Record %d had incomplete paragraph information, skipped)\n", n_read);
					continue;
				}
				gmt_geo_to_xy (GMT, in[GMT_X], in[GMT_Y], &plot_x, &plot_y);
				if (check_if_outside) {
					skip_text_records = true;	/* If this record should be skipped we must skip the whole paragraph */
					gmt_map_outside (GMT, in[GMT_X], in[GMT_Y]);
					if (abs (GMT->current.map.this_x_status) > 1 || abs (GMT->current.map.this_y_status) > 1) continue;
					skip_text_records = false;	/* Since we got here we do not want to skip */
				}
				if (Ctrl->A.active) {
					save_angle = T.paragraph_angle;	/* Since we might overwrite the default */
					tmp = gmt_azim_to_angle (GMT, in[GMT_X], in[GMT_Y], 0.1, save_angle);
					T.paragraph_angle = fmod (tmp + 360.0 + 90.0, 180.0) - 90.0;	/* Ensure usable angles for text plotting */
					if (fabs (T.paragraph_angle - tmp) > 179.0) T.block_justify -= 2 * (T.block_justify%4 - 2);	/* Flip any L/R code */
				}
				if (Ctrl->F.orientation) {
					if (T.paragraph_angle > 180.0) T.paragraph_angle -= 360.0;
					if (T.paragraph_angle > 90.0) T.paragraph_angle -= 180.0;
					else if (T.paragraph_angle < -90.0) T.paragraph_angle += 180.0;
				}
				master_record = true;
			}
			else {	/* Text block record */
				line = In->text;
				if (line == NULL) {
					GMT_Report (API, GMT_MSG_ERROR, "Text record line %d is NULL! Skipped but this is trouble)\n", n_read);
					continue;
				}
				if (skip_text_records) continue;	/* Skip all records for this paragraph */
				if (!master_record) {
					GMT_Report (API, GMT_MSG_ERROR, "Text record line %d not preceded by paragraph information, skipped)\n", n_read);
					continue;
				}
				strncpy (cp_line, line, GMT_BUFSIZ);	/* Make a copy because in_line may be pointer to a strdup-ed line that we cannot enlarge */
				line = cp_line;

				gmt_chop (line);	/* Chop of line feed */
				gmtlib_enforce_rgb_triplets (GMT, line, GMT_BUFSIZ);	/* If @; is used, make sure the color information passed on to ps_text is in r/b/g format */

				if (line[0] == 0) {	/* Blank line marked by single NULL character, replace by \r */
					n_add = 1;
					while ((length + n_add) > txt_alloc) {
						txt_alloc += GMT_BUFSIZ;
						paragraph = gmt_M_memory (GMT, paragraph, txt_alloc, char);
					}
					strcat (paragraph, "\r");
				}
				else {
					if (Ctrl->Q.active) gmt_str_setcase (GMT, line, Ctrl->Q.mode);
					n_add = (int)strlen (line) + 1;
					while ((length + n_add) > txt_alloc) {
						txt_alloc += GMT_BUFSIZ;
						paragraph = gmt_M_memory (GMT, paragraph, txt_alloc, char);
					}
					if (length) strcat (paragraph, " ");
					strcat (paragraph, line);

				}
				length += n_add;
				n_processed++;
			}
			n_read++;
		}
		else {	/* Plain style pstext input */
			double coord[2];
			int justify;
			if (gmt_M_rec_is_segment_header (GMT)) continue;	/* Skip segment headers (line == NULL) */
			in   = In->data;
			line = In->text;
			if (!no_in_txt) {
				if (line == NULL) {
					GMT_Report (API, GMT_MSG_ERROR, "Text record line %d is NULL! Skipped but this is trouble)\n", n_read);
					continue;
				}
				if (gmt_is_a_blank_line (line)) {
					n_skipped++;
					continue;	/* Skip blank lines or # comments */
				}
				strncpy (cp_line, line, GMT_BUFSIZ-1);	/* Make a copy because in_line may be pointer to a strdup-ed line that we cannot enlarge */
				line = cp_line;
			}

			if (Ctrl->F.R_justify) pstext_add_xy_via_justify (GMT, Ctrl->F.R_justify);
			pos = 0;	nscan = 3;

			if (gmt_M_compat_check (GMT, 4)) {
				if (input_format_version == GMT_NOTSET) input_format_version = pstext_get_input_format_version (GMT, line, 0);
			}
			if (input_format_version == 4) {	/* Old-style GMT 4 records */
				nscan--; /* Since we have already counted "text" */
				nscan += sscanf (line, "%s %lf %s %s %[^\n]\n", this_size, &T.paragraph_angle, this_font, just_key, text);
				T.block_justify = gmt_just_decode (GMT, just_key, PSL_NO_DEF);
				sprintf (txt_f, "%s,%s,", this_size, this_font);	/* Merge size and font to be parsed by gmt_getfont */
				T.font = Ctrl->F.font;
				if (gmt_getfont (GMT, txt_f, &T.font)) GMT_Report (API, GMT_MSG_ERROR, "Record %d had bad font (set to %s)\n", n_read, gmt_putfont (GMT, &T.font));
				in_txt = text;
				n_expected_cols = 7 + Ctrl->Z.active;
			}
			else if (!Ctrl->F.nread)	/* All attributes given via -F (or we accept defaults); just need text */
				in_txt = line;
			else {	/* Must pick up 1-3 attributes from data file */
				for (k = 0; k < Ctrl->F.nread; k++) {
					switch (Ctrl->F.read[k]) {
						case 'a': case 'A':
							if (a_col)
								T.paragraph_angle = in[a_col];
							else {
								nscan += gmt_strtok (line, GMT->current.io.scan_separators, &pos, text);
								T.paragraph_angle = atof (text);
							}
							break;
						case 'c':	/* Get x,y via code */
							nscan += gmt_strtok (line, GMT->current.io.scan_separators, &pos, text);
							justify = gmt_just_decode (GMT, text, PSL_NO_DEF);
							gmt_just_to_xy (GMT, justify, &coord[GMT_X], &coord[GMT_Y]);
							GMT->current.io.curr_rec[GMT_Z] = GMT->current.proj.z_level;
							break;
						case 'f':
							nscan += gmt_strtok (line, GMT->current.io.scan_separators, &pos, text);
							T.font = Ctrl->F.font;
							if (gmt_getfont (GMT, text, &T.font)) GMT_Report (API, GMT_MSG_ERROR, "Record %d had bad font (set to %s)\n", n_read, gmt_putfont (GMT, &T.font));
							if (gmt_M_compat_check (GMT, 4)) {
								if (Ctrl->S_old.active) {
									T.font.form |= 2;
									T.font.pen = Ctrl->S_old.pen;
								}
							}
							break;
						case 'j':
							nscan += gmt_strtok (line, GMT->current.io.scan_separators, &pos, text);
							T.block_justify = gmt_just_decode (GMT, text, PSL_NO_DEF);
							break;
					}
				}
				if (Ctrl->F.get_text == GET_REC_TEXT) in_txt = &line[pos];
			}
			if (Ctrl->F.get_text == GET_SEG_HEADER) {
				if (GMT->current.io.segment_header[0] == 0)
					GMT_Report (API, GMT_MSG_ERROR, "No active segment header to use; text is blank\n");
				strcpy (label, GMT->current.io.segment_header);
				in_txt = label;
			}
			else if (Ctrl->F.get_text == GET_SEG_LABEL) {
				if (!gmt_parse_segment_item (GMT, GMT->current.io.segment_header, "-L", label))
					GMT_Report (API, GMT_MSG_ERROR, "No active segment label to use; text is blank\n");
				in_txt = label;
			}
			else if (Ctrl->F.get_text == GET_CMD_TEXT) {
				strcpy (text, Ctrl->F.text);	/* Since we may need to do some replacements below */
				in_txt = text;
			}
			else if (Ctrl->F.get_text == GET_REC_NUMBER) {
				sprintf (label, "%d", rec_number++);
				in_txt = label;
			}
			else if (Ctrl->F.get_text == GET_CMD_FORMAT) {
				sprintf (text, Ctrl->F.text, in[z_col]);
				in_txt = text;
			}

			nscan += gmt_load_aspatial_string (GMT, GMT->current.io.OGR, text_col, in_txt);	/* Substitute OGR attribute if used */

			if (nscan < (int)n_expected_cols) {
				GMT_Report (API, GMT_MSG_ERROR, "Record %d is incomplete (skipped)\n", n_read);
				continue;
			}
			if (T.block_justify == -99) {
				GMT_Report (API, GMT_MSG_ERROR, "Record %d had bad justification info (set to LB)\n", n_read);
				T.block_justify = 1;
			}

			/* Here, in_txt holds the text we wish to plot */

			gmtlib_enforce_rgb_triplets (GMT, in_txt, GMT_BUFSIZ);	/* If @; is used, make sure the color information passed on to ps_text is in r/b/g format */
			if (Ctrl->Q.active) gmt_str_setcase (GMT, in_txt, Ctrl->Q.mode);
			use_text = pstext_get_label (GMT, Ctrl, in_txt);	/* In case there are words */
			if (gmt_text_is_latex (GMT, use_text)) {
				if (T.boxflag & 3) {
					GMT_Report (API, GMT_MSG_WARNING, "Record %d has LaTeX which cannot be used with box filling - skipping\n", n_read);
					gmt_M_str_free (use_text);
					continue;
				}
				else if (Ctrl->G.mode) {
					GMT_Report (API, GMT_MSG_WARNING, "Record %d has LaTeX which cannot be used with -G - skipping\n", n_read);
					gmt_M_str_free (use_text);
					continue;
				}
			}
			n_read++;
			if (Ctrl->F.get_xy_from_justify) {
				plot_x = coord[GMT_X], plot_y = coord[GMT_Y];
			}
			else if (Ctrl->F.R_justify)
				plot_x = in[GMT_X], plot_y = in[GMT_Y];
			else
				gmt_geo_to_xy (GMT, in[GMT_X], in[GMT_Y], &plot_x, &plot_y);
			xx[0] = plot_x;	yy[0] = plot_y;
			if (check_if_outside) {
				gmt_map_outside (GMT, in[GMT_X], in[GMT_Y]);
				if (abs (GMT->current.map.this_x_status) > 1 || abs (GMT->current.map.this_y_status) > 1) continue;
			}

			if (Ctrl->A.active) {
				save_angle = T.paragraph_angle;	/* Since we might overwrite the default */
				tmp = gmt_azim_to_angle (GMT, in[GMT_X], in[GMT_Y], 0.1, save_angle);
				T.paragraph_angle = fmod (tmp + 360.0 + 90.0, 180.0) - 90.0;	/* Ensure usable angles for text plotting */
				if (fabs (T.paragraph_angle - tmp) > 179.0) T.block_justify -= 2 * (T.block_justify%4 - 2);	/* Flip any L/R code */
			}
			if (Ctrl->F.orientation) {
				if (T.paragraph_angle > 180.0) T.paragraph_angle -= 360.0;
				if (T.paragraph_angle > 90.0) T.paragraph_angle -= 180.0;
				else if (T.paragraph_angle < -90.0) T.paragraph_angle += 180.0;
			}
			if (add) {
				if (Ctrl->D.justify)	/* Smart offset according to justification (from Dave Huang) */
					gmt_smart_justify (GMT, T.block_justify, T.paragraph_angle, T.x_offset, T.y_offset, &plot_x, &plot_y, Ctrl->D.justify);
				else {	/* Default hard offset */
					plot_x += T.x_offset;
					plot_y += T.y_offset;
				}
				xx[1] = plot_x;	yy[1] = plot_y;
			}
			n_paragraphs++;

			if (GMT->common.t.variable)	{	/* Update the transparencies for current string (if -t was given) */
				double transp[2] = {0.0, 0.0};	/* None selected */
				if (GMT->common.t.n_transparencies == 2) {	/* Requested two separate values to be read from file */
					transp[GMT_FILL_TRANSP] = 0.01 * in[tcol_f];
					transp[GMT_PEN_TRANSP]  = 0.01 * in[tcol_s];
				}
				else if (GMT->common.t.mode & GMT_SET_FILL_TRANSP) {	/* Gave fill transparency */
					transp[GMT_FILL_TRANSP] = 0.01 * in[tcol_f];
					if (GMT->common.t.n_transparencies == 0) transp[GMT_PEN_TRANSP] = transp[GMT_FILL_TRANSP];	/* Implied to be used for stroke also */
				}
				else {	/* Gave stroke transparency */
					transp[GMT_PEN_TRANSP] = 0.01 * in[tcol_s];
					if (GMT->common.t.n_transparencies == 0) transp[GMT_FILL_TRANSP] = transp[GMT_PEN_TRANSP];	/* Implied to be used for fill also */
				}
				if (gmt_M_is_dnan (transp[GMT_FILL_TRANSP])) {
					GMT_Report (API, GMT_MSG_WARNING, "Record %d had bad fill transparency (NaN) - set to 0.0\n", n_read);
					transp[GMT_FILL_TRANSP] = 0.0;
				}
				else if (transp[GMT_FILL_TRANSP] < 0.0 || transp[GMT_FILL_TRANSP] > 100.0) {
					GMT_Report (API, GMT_MSG_WARNING, "Record %d had fill transparency out of range (%g) - set to 0.0\n", n_read, transp[GMT_FILL_TRANSP]);
					transp[GMT_FILL_TRANSP] = 0.0;
				}
				if (gmt_M_is_dnan (transp[GMT_PEN_TRANSP])) {
					GMT_Report (API, GMT_MSG_WARNING, "Record %d had bad stroke transparency (NaN) - set to 0.0\n", n_read);
					transp[GMT_PEN_TRANSP] = 0.0;
				}
				else if (transp[GMT_PEN_TRANSP] < 0.0 || transp[GMT_PEN_TRANSP] > 100.0) {
					GMT_Report (API, GMT_MSG_WARNING, "Record %d had stroke transparency out of range (%g) - set to 0.0\n", n_read, transp[GMT_PEN_TRANSP]);
					transp[GMT_PEN_TRANSP] = 0.0;
				}
				PSL_settransparencies (PSL, transp);
			}
			PSL_setfont (PSL, T.font.id);
			gmt_plane_perspective (GMT, GMT->current.proj.z_project.view_plane, in[GMT_Z]);
			if (T.boxflag & 32) {	/* Draw line from original point to shifted location */
				gmt_setpen (GMT, &T.vecpen);
				PSL_plotsegment (PSL, xx[0], yy[0], xx[1], yy[1]);
			}
			if (!Ctrl->G.mode && T.boxflag & 3) {	/* Plot the box beneath the text */
				if (T.space_flag) {	/* Meant % of fontsize */
					offset[0] = 0.01 * T.x_space * T.font.size / PSL_POINTS_PER_INCH;
					offset[1] = 0.01 * T.y_space * T.font.size / PSL_POINTS_PER_INCH;
				}
				else {
					offset[0] = T.x_space;
					offset[1] = T.y_space;
				}
				if (Ctrl->S.active) {	/* Lay down shaded box first */
					PSL_setfill (PSL, Ctrl->S.fill.rgb, 0);	/* shade color */
					PSL_plottextbox (PSL, plot_x + Ctrl->S.off[GMT_X], plot_y + Ctrl->S.off[GMT_Y], T.font.size, use_text, T.paragraph_angle, T.block_justify, offset, T.boxflag & 4);
				}
				gmt_setpen (GMT, &T.boxpen);			/* Box pen */
				PSL_setfill (PSL, T.boxfill.rgb, T.boxflag & 1);	/* Box color */
				PSL_plottextbox (PSL, plot_x, plot_y, T.font.size, use_text, T.paragraph_angle, T.block_justify, offset, T.boxflag & 4);
				curr_txt = NULL;	/* Text has now been encoded in the PS file */
			}
			else
				curr_txt = use_text;
			fmode = gmt_setfont (GMT, &T.font);
			if (Ctrl->G.mode) {
				if (m <= n_alloc) {
					gmt_M_malloc3 (GMT, c_angle, c_x, c_y, m, &n_alloc, double);
					c_just = gmt_M_memory (GMT, c_just, n_alloc, int);
					c_txt = gmt_M_memory (GMT, c_txt, n_alloc, char *);
					c_font = gmt_M_memory (GMT, c_font, n_alloc, struct GMT_FONT);
				}
				c_angle[m] = T.paragraph_angle;
				c_txt[m] = strdup (curr_txt);
				c_x[m] = plot_x;
				c_y[m] = plot_y;
				c_just[m] = T.block_justify;
				c_font[m] = T.font;
				m++;
			}
			else
				gmt_map_text (GMT, plot_x, plot_y, &T.font, curr_txt, T.paragraph_angle, T.block_justify, fmode);
			if (Ctrl->A.active) T.paragraph_angle = save_angle;	/* Restore original angle */
			gmt_M_str_free (use_text);
		}

	} while (true);

	if (GMT_End_IO (API, GMT_IN, 0) != GMT_NOERROR) {	/* Disables further data input */
		Return (API->error);
	}

	if (n_skipped && n_read == 0)
		GMT_Report (API, GMT_MSG_WARNING, "Skipped %u records as blank - please check input data.\n", n_skipped);
	PSL_settextmode (PSL, PSL_TXTMODE_HYPHEN);	/* Back to leave as is */

	if (GMT->common.t.variable) {	/* Reset the transparencies */
		double transp[2] = {0.0, 0.0};	/* None selected */
		PSL_settransparencies (PSL, transp);
	}

	if (Ctrl->M.active) {
		if (n_processed) {	/* Must output the last paragraph */
			pstext_output_words (GMT, PSL, plot_x, plot_y, paragraph, &T, Ctrl);
			n_paragraphs++;
		}
	 	gmt_M_free (GMT, paragraph);
	 	strncpy (GMT->current.setting.io_head_marker_in, save_h_chars, GMT_LEN32);	/* Restore original default */
	}
	if (Ctrl->G.mode && m) {
		int n_labels = m, form = (T.boxflag & 4) ? PSL_TXT_ROUND : 0;	/* PSL_TXT_ROUND = Rounded rectangle */
		unsigned int kk;
		char *font = NULL, **fonts = NULL;

		form |= PSL_TXT_INIT;	/* To lay down all PSL attributes */
		if (Ctrl->G.mode == PSTEXT_CLIPPLOT) form |= PSL_TXT_SHOW;	/* To place text */
		form |= PSL_TXT_CLIP_ON;	/* To set clip path */
		gmt_textpath_init (GMT, &Ctrl->W.pen, Ctrl->G.fill.rgb);
		if (Ctrl->C.percent) {	/* Meant % of fontsize */
			offset[0] = 0.01 * T.x_space * T.font.size / PSL_POINTS_PER_INCH;
			offset[1] = 0.01 * T.y_space * T.font.size / PSL_POINTS_PER_INCH;
		}
		else {
			offset[0] = T.x_space;
			offset[1] = T.y_space;
		}
		fonts = gmt_M_memory (GMT, NULL, m, char *);
		for (kk = 0; kk < m; kk++) {
			PSL_setfont (PSL, c_font[kk].id);
#if 0
			psl_encodefont (PSL, PSL->current.font_no);
#endif
			font = PSL_makefont (PSL, c_font[kk].size, c_font[kk].fill.rgb);
			fonts[kk] = strdup (font);
		}
		psl_set_int_array (PSL, "label_justify", c_just, m);
		psl_set_txt_array (PSL, "label_font", fonts, m);
		/* Turn clipping ON after [optionally] displaying the text */
		PSL_plottextline (PSL, NULL, NULL, NULL, 1, c_x, c_y, c_txt, c_angle, &n_labels, T.font.size, T.block_justify, offset, form);
		for (kk = 0; kk < m; kk++) {
			gmt_M_str_free (c_txt[kk]);
			gmt_M_str_free (fonts[kk]);
		}
		gmt_M_free (GMT, c_angle);
		gmt_M_free (GMT, c_x);
		gmt_M_free (GMT, c_y);
		gmt_M_free (GMT, c_txt);
		gmt_M_free (GMT, c_just);
		gmt_M_free (GMT, c_font);
		gmt_M_free (GMT, fonts);
	}
	else if (clip_set)
		gmt_map_clip_off (GMT);

	GMT->current.map.is_world = old_is_world;
	GMT->current.io.scan_separators = GMT_TOKEN_SEPARATORS;		/* Reset */
    API->n_numerical_columns = GMT_NOTSET;

	gmt_map_basemap (GMT);
	gmt_plane_perspective (GMT, -1, 0.0);
	gmt_plotend (GMT);

	GMT_Report (API, GMT_MSG_INFORMATION, Ctrl->M.active ? "pstext: Plotted %d text blocks\n" : "pstext: Plotted %d text strings\n", n_paragraphs);

	Return (GMT_NOERROR);
}

EXTERN_MSC int GMT_text (void *V_API, int mode, void *args) {
	/* This is the GMT6 modern mode name */
	struct GMTAPI_CTRL *API = gmt_get_api_ptr (V_API);	/* Cast from void to GMTAPI_CTRL pointer */
	if (API == NULL) return (GMT_NOT_A_SESSION);
	if (API->GMT->current.setting.run_mode == GMT_CLASSIC && !API->usage) {
		struct GMT_OPTION *options = GMT_Create_Options (API, mode, args);
		bool list_fonts = false;
		if (API->error) return (API->error);	/* Set or get option list */
		list_fonts = (GMT_Find_Option (API, 'L', options) != NULL);
		gmt_M_free_options (mode);
		if (!list_fonts) {
			GMT_Report (API, GMT_MSG_ERROR, "Shared GMT module not found: text\n");
			return (GMT_NOT_A_VALID_MODULE);
		}
	}
	return GMT_pstext (V_API, mode, args);
}
