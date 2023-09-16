#!/usr/bin/env bash
#
# Example 11, Justify wind barb position with -Q+jc
#
ps=psbarb_11.ps
title="$ps Justify wind barb position with -Q+jc"
gmt set MAP_FRAME_TYPE plain  MAP_FRAME_AXES WeSn  FONT_TITLE 20p,Helvetica,black  MAP_TITLE_OFFSET 0p
gmt psbarb wind_C.txt -Q0.2i+jc -C./wind.cpt -Wdefault,black+c -JS180/90/17 -R0/360/-20/90 -Ba30g30 -B+t"$title" > $ps
