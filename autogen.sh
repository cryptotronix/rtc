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

test_exit(){
    if [[ $? == 0 ]]; then
        echo $1 passed
    else
        echo $1 failed
        exit $?
    fi
}

if [ ! -d "m4" ]; then
    mkdir m4
fi

autoreconf --force --install
test_exit autoreconf

./configure
test_exit configure

make
test_exit make
