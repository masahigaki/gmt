#!/usr/bin/env bash
#
# Example 7, test for -T (no difference can not be seen comparing with Ex2)
#
ps=grdbarb_07.ps
title="$ps Test for -T"
gmt set MAP_FRAME_TYPE plain  MAP_FRAME_AXES WeSn  FONT_TITLE 20p,Helvetica,black  MAP_TITLE_OFFSET 0p
gmt grdbarb u.grd v.grd -W -JQ24 -T -R0/360/-90/90 -Ba30 -B+t"$title" -N > $ps
