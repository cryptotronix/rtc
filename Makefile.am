# Copyright (C) 2014 Cryptotronix, LLC.

# This file is part of rtc.

# rtc is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.

# rtc is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with rtc.  If not, see <http://www.gnu.org/licenses/>.

AUTOMAKE_OPTIONS = subdir-objects

ACLOCAL_AMFLAGS = -I m4
AM_CPPFLAGS = $(DEPS_CFLAGS)
rtc_LDADD = $(DEPS_LIBS)

SUBDIRS = .

AM_YFLAGS = -d

bin_PROGRAMS = rtc
rtc_SOURCES = src/i2c.h src/i2c.c src/rtc.h src/rtc.c \
	      src/rtc_parser.h src/rtc_parser.c \
	      src/rtc_flex.l src/rtc_bison.y \
	      src/log.h src/log.c \
	      src/main.c

BUILT_SOURCES = src/rtc_bison.h

rtc_CFLAGS = -Wall


dist_noinst_SCRIPTS = autogen.sh

TESTS = src/tests/test_cli.sh
EXTRA_DIST = src/tests/test_cli.sh
