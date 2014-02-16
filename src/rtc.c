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
#include <argp.h>
#include <assert.h>
#include "config.h"
#include <string.h>
#include <stdlib.h>
#include "rtc_parser.h"
#include "rtc.h"
#include "log.h"

void sprintfb (char *s, uint8_t b)
{
  assert (NULL != s);

  const unsigned int BITS_IN_BYTE = 8;

  int x = 0;

  for (x=0;x<BITS_IN_BYTE;x++)
    {

      strcat (s, (b & ~127) ? "1" : "0");

      b <<= 1;

    }
}

void hex2bin (char *s, uint8_t *buf, unsigned int len)
{
  int x = 0;
  assert (NULL != buf);
  char temp[9] = {0};

  for (x=0; x<len; x++)
    {
      memset (temp, 0, sizeof (temp));
      sprintfb (temp, buf[x]);
      strcat (s, temp);
    }
}

struct time_serialized serialize_time (struct tm t)
{
  struct time_serialized ts = {};
  uint8_t *p = ts.time;

  *p++ = digit2bits (t.tm_sec, false);
  *p++ = digit2bits (t.tm_min, false);
  *p++ = digit2bits (t.tm_hour, true);
  *p++ = digit2bits (t.tm_wday, false);
  *p++ = digit2bits (t.tm_mday, false);
  *p++ = digit2bits (t.tm_mon, false);

  /* t.tm_year is years from 1900, which is different than how this
     module encodes the year */
  assert (100 <= t.tm_year && t.tm_year < 200);
  *p = digit2bits ((t.tm_year - 100)/ 10, false);
  *p <<= 4;
  *p |= digit2bits ((t.tm_year - 100) % 10, false);


  return ts;

}

struct time_serialized* get_time_from_device (int fd)
{
  struct time_serialized* t = NULL;

  if ((t = (struct time_serialized *)
       malloc (sizeof (struct time_serialized))) != NULL)
    {
      uint8_t addr = 0;
      if (sizeof (addr) == i2c_write (fd, &addr, sizeof (addr)))
        {
          if (sizeof (t->time) != i2c_read (fd, t->time, sizeof (t->time)))
            {
              free (t);
              t = NULL;
            }
        }
      else
        {
          free (t);
          t = NULL;
        }
    }

  return t;

}

bool set_time (int fd, struct tm t)
{
  bool result = false;
  struct time_serialized ts = serialize_time (t);

  /* The first byte is the address to which to write */
  const unsigned int LEN = sizeof (ts.time) + 1;
  uint8_t *buf = malloc (LEN);
  assert (NULL != buf);
  memset (buf, 0, LEN);

  memcpy (buf+1, ts.time, sizeof (ts.time));

  if (LEN == i2c_write (fd, buf, LEN))
      result = true;

  free (buf);

  return result;
}

uint8_t digit2bits (unsigned int d, bool hour)
{
  uint8_t result = 0;

  const uint8_t MASK_20 = 0b00100000;

  if (hour && d/20 >= 1)
    {
      result |= MASK_20;
      result += d % 20;
    }
  else if (d/10 >= 1)
    {
      unsigned int tens = d/10;
      tens <<= 4;
      result = tens & 0xF0;
      result += d % 10;
    }
  else
    {
      result = d;
    }

  return result;

}

struct tm get_time (int fd)
{
  struct time_serialized* t = get_time_from_device (fd);
  struct tm c_time = {0};

  if (NULL == t)
    return c_time;

  const unsigned int BIT_TIME_LEN = 56;

  /* Convert the time in an ASCII bit string */
  char *s = malloc (BIT_TIME_LEN);
  assert (NULL != s);
  memset (s, 0, BIT_TIME_LEN);
  hex2bin (s, t->time, sizeof (t->time));

  /* Parse the string */
  if (0 == scan_string (s))
    {
      c_time = get_rtc_time ();
    }

  free (t);
  return c_time;

}
