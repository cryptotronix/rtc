# Copyright (C) 2013 Cryptotronix, LLC.

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

AC_INIT([rtc], [0.1.0], [bugs@cryptotronix.com], [rtc], [http://www.github.com/cryptotronix/rtc/])
AC_PREREQ([2.59])
AM_INIT_AUTOMAKE([1.10 -Wall no-define])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])
AC_CHECK_HEADERS([linux/i2c-dev.h sys/ioctl.h fcntl.h])
AC_PROG_CC
AM_PROG_CC_C_O
AC_CONFIG_FILES([Makefile])
PKG_PROG_PKG_CONFIG
#Check for libs

AM_PROG_LEX
AC_PROG_YACC
AC_PROG_LIBTOOL


AC_OUTPUT
