#!/usr/bin/env bash
#
# Example 2, Equidistant Cylindrical Projection -JQ
#
ps=grdbarb_02.ps
title="$ps Equidistant Cylindrical Projection -JQ"
gmt set MAP_FRAME_TYPE plain  MAP_FRAME_AXES WeSn  FONT_TITLE 20p,Helvetica,black  MAP_TITLE_OFFSET 0p
gmt grdbarb u.grd v.grd -W -JQ24 -Rg -Ba30 -B+t"$title" -N > $ps
