#!/usr/bin/env bash
#
# Example 1, Linear x-y plot -JX
#
ps=psbarb_01.ps
title="$ps Linear x-y plot -JX"
gmt set MAP_FRAME_TYPE plain  MAP_FRAME_AXES WeSn  FONT_TITLE 20p,Helvetica,black  MAP_TITLE_OFFSET 0p
gmt psbarb wind.txt -Q0.2i -JX24/12 -Rg -Ba30 -B+t"$title" -N > $ps
