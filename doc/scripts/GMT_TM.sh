#!/usr/bin/env bash
gmt coast -R0/360/-80/80 -JT330/-45/10c -Ba30g -BWSne -Dc -A2000 -Slightblue -G0 --MAP_ANNOT_OBLIQUE=lon_horizontal --GMT_THEME=cookbook -view GMT_TM
