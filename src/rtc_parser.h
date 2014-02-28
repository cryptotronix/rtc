/* -*- mode: c; c-file-style: "gnu" -*-
 * Copyright (C) 2013 Cryptotronix, LLC.
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
#ifndef RTC_PARSER_H
#define RTC_PARSER_H

#include <stdio.h>
#include <time.h>

/**
 * Populates the time structure.
 *
 * @param seconds_10 The value of 10s Seconds from the device
 * @param seconds The value of seconds from the device
 * @param minutes_10 The value of 10s Minutes from the device
 * @param minutes The value of minutes from the device
 * @param twelve_24 The twelve or 24 hour flag (1 is 12 hour mode)
 * @param am_pm If in twelve hour mode, 1 is PM.  In 24 hour mode,
 * this is the 20s value
 * @param hours_10 The value of 10s hour from the device
 * @param hour The value of hours from the device
 * @param day The value of the day of the week from the device
 * @param date_10 The value of the 10s date (month) from the device
 * @param date The value of the date from the device
 * @param century If 1, the years has overflowed from 99
 * @param month_10 The 10s month value from the device
 * @param month The month value from the device
 * @param year_10 The 10s year value from the device
 * @param year The years from the device
 */
void set_rtc_time (int seconds_10, int seconds, int minutes_10, int minutes,
                   int twelve_24, int am_pm, int hours_10, int hour, int day,
                   int date_10, int date, int century, int month_10, int month,
                   int year_10, int year);

/**
 * Returns the parsed time structure.  The structure will be 0 if the
 * data is not parsed.
 *
 *
 * @return The standard c time structure.
 */
struct tm get_rtc_time ();

/**
 * Initiate the parsing
 * Included to prevent compile warnings
 *
 * @return 0 on success
 */
int scan_string(const char* str);

/* Declarations to make flex happy */
typedef struct yy_buffer_state *YY_BUFFER_STATE;

YY_BUFFER_STATE yy_scan_string( const char * );
void            yy_delete_buffer( YY_BUFFER_STATE );

#endif
