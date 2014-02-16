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


#include <argp.h>
#include <assert.h>
#include "config.h"
#include <string.h>
#include "rtc.h"
#include "i2c.h"
#include "log.h"

const char *argp_program_version = PACKAGE_VERSION;

const char *argp_program_bug_address = PACKAGE_BUGREPORT;

/* Program documentation. */
static char doc[] =
  "rtc is a program to interface to the Maxim Integrated DS3231M Real\n"
  "Time Clock (RTC)\n\n"
  "Currently implemented Commands:\n\n"
  "date          --  Retrieves the current data from the device\n"
  "set-date      --  Sets the date on the device.  Without any options, this\n"
  "                  will set the device to the current date\n";

/* A description of the arguments we accept. */
static char args_doc[] = "command";

/* The options we understand. */
static struct argp_option options[] = {
  { 0, 0, 0, 0, "Global Options:", -1},
  {"verbose",  'v', 0,      0,  "Produce verbose output" },
  {"quiet",    'q', 0,      0,  "Don't produce any output" },
  {"silent",   's', 0,      OPTION_ALIAS },
  { 0 }
};

#define NUM_ARGS 1

/* Used by main to communicate with parse_opt. */
struct arguments
{
  char *args[NUM_ARGS];
  int silent, verbose;
  long unsigned int addr;
  char *bus;
};

/* Parse a single option. */
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;

  switch (key)
    {
    case 'q': case 's':
      arguments->silent = 1;
      break;
    case 'v':
      arguments->verbose = 1;
      set_log_level (DEBUG);
      break;
    case ARGP_KEY_ARG:
      if (state->arg_num > NUM_ARGS)
        /* Too many arguments. */
        argp_usage (state);

      arguments->args[state->arg_num] = arg;

      break;
    case ARGP_KEY_END:
      if (state->arg_num < NUM_ARGS)
        /* Not enough arguments. */
        argp_usage (state);
      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

/* Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, doc };

int main (int argc, char **argv)
{
  struct arguments arguments;

  /* Sets arguments defaults and the command list */
  arguments.silent = 0;
  arguments.verbose = 0;
  arguments.addr = 0x68; /* data sheet says D0.  This is a 7 bit addr */
  arguments.bus = "/dev/i2c-1";

  /* Parse our arguments; every option seen by parse_opt will
     be reflected in arguments. */
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  int exit = 1;

  if (0 == strcmp("date", arguments.args[0]))
    {
      int fd = i2c_setup(arguments.bus);
      i2c_acquire_bus (fd, arguments.addr);

      struct tm t = get_time (fd);
      fprintf (stdout, "%s", asctime (&t));
      close (fd);
      exit = 0;

    }
  else if (0 == strcmp("set-date", arguments.args[0]))
    {
      int fd = i2c_setup(arguments.bus);
      i2c_acquire_bus (fd, arguments.addr);

      time_t current_time = time (NULL);
      struct tm * ct_p = gmtime (&current_time);
      assert (NULL != ct_p);

      assert (true == set_time (fd, *ct_p));

      close (fd);
      exit = 0;

    }

  return exit;

}
