#!/usr/bin/env bash
#
# Example 4, Lambert Projection -JL
#
ps=grdbarb_04.ps
title="$ps Lambert Projection -JL"
gmt set MAP_FRAME_TYPE plain  MAP_FRAME_AXES WeSn  FONT_TITLE 20p,Helvetica,black  MAP_TITLE_OFFSET 0p
ropt=`
( echo -10000 -5000 ; echo 10000 7500 ) \
| gmt mapproject -Jl180/30/30/60/1:1 -R180/181/30/31 -Fk -I \
| awk '{ lo = $1; la = $2 ; getline ; printf "%f/%f/%f/%f", lo,la,$1,$2 }'`
gmt grdbarb u.grd v.grd -W -JL180/30/60/30/24 -R${ropt}+r -Ba30g30 -B+t"$title" > $ps
