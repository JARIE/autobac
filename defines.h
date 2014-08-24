/* File: defines.h
 * Created: 09, August 2014
 *
 * Copyright (C) 2014 Jarielle Catbagan, Denny Dimalanta
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DEFINES_H
#define DEFINES_H

#include <vector>
#include <string>
#include <stdint.h>
#include <stdio.h>

using namespace std;

#define STDERR(str, ...) fprintf(stderr, "error: " str, ##__VA_ARGS__)
#define DEBUG_PRINT(str, ...) fprintf(stdout, "debug: " str, ##__VA_ARGS__)

typedef enum program_status_t {UNDEFINED = 0, ERROR, NO_ERROR} program_status_t;
typedef enum execution_status_t {EXIT = 0, CONTINUE} execution_status_t;
typedef enum directory_status_t {EMPTY = 0, NON_EMPTY} directory_status_t;
typedef enum change_status_t {NA = 0, VOLATILE, NONVOLATILE} chang_status_t;

typedef struct date_time_st {
	uint16_t month;
	uint16_t day;
	uint16_t year;
	uint16_t hour;
	uint16_t minute;
} date_time_st;

typedef struct file_st {
	string name;
	date_time_st date_time;
} file_st;

typedef struct dir_domain_st {
	vector<file_st> files;
	string relative_path;
	vector<string> directories;
} dir_domain_st;

enum entity_type_t {IS_UNDEFINED = 0, IS_FILE, IS_DIRECTORY};

#endif
