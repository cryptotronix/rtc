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

#include "i2c.h"
#include "log.h"
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int i2c_setup(const char* bus)
{
  assert(NULL != bus);

  int fd;

  if ((fd = open(bus, O_RDWR)) < 0)
    {
      perror("Failed to open I2C bus\n");
      exit(1);
    }

  return fd;

}

void i2c_acquire_bus(int fd, int addr)
{
  if (ioctl(fd, I2C_SLAVE, addr) < 0)
    {
      perror("Failed to acquire bus access and/or talk to slave.\n");

      exit(1);
  }

}


ssize_t i2c_write(int fd, uint8_t *buf, unsigned int len)
{
  assert(NULL != buf);
  ssize_t bytes = 0;


  bytes = write(fd, buf, len);

  print_hex_string ("Writing", buf, len);

  return bytes;
}

ssize_t i2c_read(int fd, uint8_t *buf, unsigned int len)
{
  assert(NULL != buf);
  ssize_t bytes = 0;

  bytes = read(fd, buf, len);

  print_hex_string ("Reading", buf, len);

  return bytes;
}
