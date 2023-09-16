#!/usr/bin/env bash
#
# Example 3, Stereographic Projection -JS
#
ps=psbarb_03.ps
title="$ps Stereographic Projection -JS"
gmt set MAP_FRAME_TYPE plain  MAP_FRAME_AXES WeSn  FONT_TITLE 20p,Helvetica,black  MAP_TITLE_OFFSET 0p
gmt psbarb wind.txt -Q0.2i -JS180/90/17 -R0/360/-20/90 -Ba30g30 -B+t"$title" > $ps
