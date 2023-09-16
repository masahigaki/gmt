#!/usr/bin/env bash
#
# Example 9, Set wind barb size in data file by not specifying -Q
#
#            3rd column = length, 4th column = width
ps=psbarb_09.ps
title="$ps Set wind barb size in data file"
gmt set MAP_FRAME_TYPE plain  MAP_FRAME_AXES WeSn  FONT_TITLE 20p,Helvetica,black  MAP_TITLE_OFFSET 0p
awk '{size=$1/360; print $1,$2, size, size/2 ,$3,$4}' wind.txt | \
gmt psbarb -JS180/90/17 -R0/360/-20/90 -Ba30g30 -B+t"$title" > $ps
