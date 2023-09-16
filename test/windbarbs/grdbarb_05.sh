#!/usr/bin/env bash
#
# Example 5, Set color palette with -C
#
ps=grdbarb_05.ps
title="$ps Set color palette with -C"
gmt set MAP_FRAME_TYPE plain  MAP_FRAME_AXES WeSn  FONT_TITLE 20p,Helvetica,black  MAP_TITLE_OFFSET 0p
gmt grdbarb u.grd v.grd -C./wind.cpt -JS180/90/17 -R0/360/-20/90 -Ba30g30 -B+t"$title" > $ps
