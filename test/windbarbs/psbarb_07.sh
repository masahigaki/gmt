#!/usr/bin/env bash
#
# Example 7, Set color palette and color pen with -C and -W+c
#
ps=psbarb_07.ps
title="$ps Set color with -C and -W+c"
gmt set MAP_FRAME_TYPE plain  MAP_FRAME_AXES WeSn  FONT_TITLE 20p,Helvetica,black  MAP_TITLE_OFFSET 0p
gmt psbarb wind_C.txt -Q0.2i -C./wind.cpt -Wdefault,black+c -JS180/90/17 -R0/360/-20/90 -Ba30g30 -B+t"$title" > $ps
