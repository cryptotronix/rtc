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
%{
#include <stdio.h>
#include "rtc_parser.h"
#include <stdbool.h>
#include <string.h>


void yyerror (const char *error);
int yylex(void);

%}

%union
{
  int bit;
  int result;
}

%token BIT

%type<bit> BIT
%type<result> seconds_10
%type<result> seconds
%type<result> minutes_10
%type<result> minutes
%type<result> twelve_24
%type<result> am_pm
%type<result> hours_10
%type<result> hour
%type<result> day
%type<result> date_10
%type<result> date
%type<result> century
%type<result> month_10
%type<result> month
%type<result> year_10
%type<result> year

%%


encoded_time : ds3231m_time { }

ds3231m_time : BIT seconds_10 seconds BIT minutes_10 minutes BIT twelve_24 am_pm hours_10 hour BIT BIT BIT BIT BIT day BIT BIT date_10 date century BIT BIT month_10 month year_10 year
{ set_rtc_time ($2, $3, $5, $6, $8, $9, $10, $11, $17, $20, $21, $22, $25, $26, $27, $28);}

seconds_10 : BIT BIT BIT { $$ = $1 * 4 + $2 * 2 + $3 * 1; }
seconds    : BIT BIT BIT BIT { $$ = $1 * 8 + $2 * 4 + $3 * 2 + $4 * 1; }
minutes_10 : BIT BIT BIT { $$ = $1 * 4 + $2 * 2 + $3 * 1; }
minutes    : BIT BIT BIT BIT { $$ = $1 * 8 + $2 * 4 + $3 * 2 + $4 * 1; }
twelve_24  : BIT { $$ = $1 * 1; }
am_pm      : BIT { $$ = $1 * 1; }
hours_10   : BIT { $$ = $1 * 1; }
hour       : BIT BIT BIT BIT { $$ = $1 * 8 + $2 * 4 + $3 * 2 + $4 * 1; }
day        : BIT BIT BIT { $$ = $1 * 4 + $2 * 2 + $3 * 1; }
date_10    : BIT BIT { $$ = $1 * 2 + $2 * 1; }
date       : BIT BIT BIT BIT { $$ = $1 * 8 + $2 * 4 + $3 * 2 + $4 * 1; }
century    : BIT { $$ = $1 * 1; }
month_10   : BIT { $$ = $1 * 1; }
month      : BIT BIT BIT BIT { $$ = $1 * 8 + $2 * 4 + $3 * 2 + $4 * 1; }
year_10    : BIT BIT BIT BIT { $$ = $1 * 8 + $2 * 4 + $3 * 2 + $4 * 1; }
year       : BIT BIT BIT BIT { $$ = $1 * 8 + $2 * 4 + $3 * 2 + $4 * 1; }

%%



void yyerror (const char *error)
{
  fprintf (stderr,"%s: %s", "Parser error", error);

}

int scan_string (const char* str)
{
  YY_BUFFER_STATE bs = yy_scan_string (str);
  int my_parse_result  = yyparse ();
  yy_delete_buffer (bs);

  return my_parse_result;

}
