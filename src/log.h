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

#ifndef LOG_H
#define LOG_H

#include <stdbool.h>
#include <stdint.h>

enum LOG_LEVEL
  {
    SEVERE = 0,
    WARNING,
    INFO,
    DEBUG
  };

/**
 * Sets the global log level
 *
 * @param lvl The new level to set
 */
void set_log_level(enum LOG_LEVEL lvl);

/**
 * Writes a log message.
 *
 * @param LOG_LEVEL The log level of the message
 * @param format The format string to print
 */
void CTX_LOG(enum LOG_LEVEL, const char *format, ...);

/**
 * Prints out the hex string in a consistent format.
 *
 * @param str The prefix of the mesage
 * @param hex The hex buffer to print
 * @param len The length of the buffer
 */
void print_hex_string(const char *str, const uint8_t *hex, unsigned int len);


#endif /* LOG_H */
