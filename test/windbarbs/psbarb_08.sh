#!/usr/bin/env bash
#
# Example 8, 3-D plot with -JZ -p
#
ps=psbarb_08.ps
title="$ps 3-D plot with -JZ -p"
gmt set MAP_FRAME_TYPE plain  MAP_FRAME_AXES WeSn  FONT_TITLE 20p,Helvetica,black  MAP_TITLE_OFFSET 0p
awk '{print $1,$2,$2,$4,$3,$4}' wind.txt > wind_C_3d.txt  # add z-value
gmt psbarb wind_C_3d.txt -Q0.2i -C./wind.cpt -Wdefault,black+c -JQ20 -R0/360/-90/90/-90/90 -Ba30g30 -BWeSnZ1234+t"$title" -JZ5 -Bza30 -p150/45 > $ps
