/* -*- mode: c; c-file-style: "gnu" -*-
 * Copyright (C) 2014 Cryptotronix, LLC.
 *
 * This file is part of rtc.
 *
 * rtc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * rtc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with rtc.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "rtc_parser.h"
#include <assert.h>
#include <string.h>


extern FILE *yyin;

struct tm t ={0};

int combine (int tens, int ones)
{
  return tens * 10 + ones;
}

void set_rtc_time (int seconds_10, int seconds, int minutes_10, int minutes,
                   int twelve_24, int am_pm, int hours_10, int hour, int day,
                   int date_10, int date, int century, int month_10, int month,
                   int year_10, int year)
{
  t.tm_sec = combine (seconds_10, seconds);
  t.tm_min = combine (minutes_10, minutes);

  if (1 == twelve_24)
    {
      /* twelve hour mode is selected */
      t.tm_hour = combine (hours_10, hour);
      t.tm_hour += (1 == am_pm) ? 12 : 0;
    }
  else
    {
      /* 24 hour mode */
      t.tm_hour = am_pm * 20 + combine (hours_10, hour);
    }

  t.tm_wday = day;
  t.tm_mday = combine (date_10, date);
  t.tm_mon = combine (month_10, month);

  const int YEARS_BETWEEN_1900_2000 = 100;
  /* This calculation will only work until 2099 */
  t.tm_year = combine (year_10, year) + YEARS_BETWEEN_1900_2000;
}

struct tm get_rtc_time ()
{
  return t;
}
