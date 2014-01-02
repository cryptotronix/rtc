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

#ifndef RTC_H
#define RTC_H

#include <stdint.h>
#include <time.h>
#include <stdbool.h>

struct time_serialized
{
  uint8_t time[7];
};

/**
 * Convert the standard c time into the device's time structure,
 * serialized for an on-the-wire transmission.
 *
 * @param t The time to convert
 *
 * @return The converted time
 */
struct time_serialized serialize_time (struct tm t);

/**
 * Retrieve the current time from the device
 *
 * @param fd The open file descriptor
 *
 * @return A malloc'd time structure or NULL on error
 */
struct time_serialized* get_time_from_device (int fd);

/**
 * Get the time from the device and convert it
 *
 * @param fd The open file descriptor
 *
 * @return The device's time.
 */
struct tm get_time (int fd);

/**
 * Utility function to convert a byte into a ASCII binary string
 *
 * @param s The buffer to fill
 * @param b The byte to convert
 */
void sprintfb (char *s, uint8_t b);

/**
 * Utility function to convert a buffer into an ASCII binary string
 *
 * @param s the buffer to fill
 * @param buf the buffer to convert
 * @param len the length of the buffer to convert
 */
void hex2bin (char *s, uint8_t *buf, unsigned int len);


/**
 * Set the device's clock.
 *
 * @param fd The open file descriptor
 * @param t The standard c time structure to set.
 *
 * @return True if successful, otherwise false.
 */
bool set_time (int fd, struct tm t);

/**
 * Utility function to convert a value into a BCD encoded form
 * required by the device
 *
 * @param d The value to convert
 * @param hour True if the value is hours, which requires special handling
 *
 * @return the byte representing the encoded result
 */
uint8_t digit2bits (unsigned int d, bool hour);




#endif
