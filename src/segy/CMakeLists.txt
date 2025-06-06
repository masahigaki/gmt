#
# Copyright (c) 1991-2025 by the GMT Team (https://www.generic-mapping-tools.org/team.html)
# See LICENSE.TXT file for copying and redistribution conditions.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; version 3 or any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# Contact info: www.generic-mapping-tools.org
#-------------------------------------------------------------------------------
#
# CMake settings for supplemental package:
#
#   SUPPL_NAME:          name of the supplemental package
#   SUPPL_HEADERS:       header files. Will be installed if BUILD_DEVELOPER is TRUE
#   SUPPL_PROGS_SRCS:    list of C source codes for supplemental modules
#   SUPPL_LIB_SRCS:      list of C source codes for supplemental library
#   SUPPL_EXAMPLE_FILES: README and other example files
#   SUPPL_EXAMPLE_PROGS: Example scripts
#

set (SUPPL_NAME segy)
set (SUPPL_HEADERS segy.h segy_io.h segyreel.h)
AUX_SOURCE_DIRECTORY (longopt SUPPL_LONG_OPT_H) 
set (SUPPL_PROGS_SRCS segy2grd.c pssegy.c pssegyz.c ${SUPPL_LONG_OPT_H})
set (SUPPL_LIB_SRCS ${SUPPL_PROGS_SRCS} segy_io.c)
set (SUPPL_EXAMPLE_FILES README.segy)
