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

#ifndef I2C_H
#define I2C_H

#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * Open the I2C bus
 *
 * @param bus The desired I2C bus.
 *
 * @return An open file descriptor or the program will exit.
 */
int i2c_setup(const char* bus);

/**
 * Acquires the bus for the device at the given address.  The program
 * will exit if this fails.
 *
 * @param fd The open file descriptor.
 * @param addr The address to which to write
 */
void i2c_acquire_bus(int fd, int addr);

/**
 * Wrapper for write
 *
 * @param fd The open file descriptor
 * @param buf The buffer to write
 * @param len The length to write
 *
 * @return the result of write
 */
ssize_t i2c_write(int fd, uint8_t *buf, unsigned int len);

/**
 * Wrapper for read
 *
  */
ssize_t i2c_read(int fd, uint8_t *buf, unsigned int len);


#endif /* I2C_H */
