#!/bin/bash
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

arch=$(uname -a)

if [[ "${arch}" != *arm* ]]; then
    echo Not building on arm, exiting
    exit 0
fi

test_exit(){
    if [[ $? == $1 ]]; then
        echo $2 passed
    else
        echo $2 failed
        exit 1
    fi
}


SUCCESS=0
FAIL=1

BUS=/dev/i2c-1
EXE=./rtc

if [[ ! -e $BUS ]]; then
    echo Tests only make sense on a device with $BUS
    exit 0
fi

RSP=$($EXE set-date)

test_exit $SUCCESS set date check

SYSDATE=$(date | awk '{sub(/UTC /,""); print}')
DEVDATE=$($EXE date)

test_exit $SUCCESS get date check

if [[ $SYSDATE == $DEVDATE ]]; then
    echo Date set properly
    exit $SUCCESS
else
    echo Date set failed
    exit $FAIL
fi
