#!/usr/bin/env bash
#
# Example 6, Set color palette and pen with -C and -W
#
ps=psbarb_06.ps
title="$ps Set color and pen with -C and -W"
gmt set MAP_FRAME_TYPE plain  MAP_FRAME_AXES WeSn  FONT_TITLE 20p,Helvetica,black  MAP_TITLE_OFFSET 0p
gmt psbarb wind_C.txt -Q0.2i -C./wind.cpt -W -JS180/90/17 -R0/360/-20/90 -Ba30g30 -B+t"$title" > $ps
