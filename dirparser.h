/* File: dirparser.h
 * Created: 14, August 2014
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

#ifndef DIRPARSER_H
#define DIRPARSER_H

#include <cstdio>
#include <vector>
#include <string>
#include "defines.h"

using namespace std;

class dirparser_ct {
public:
	directory_status_t parse_dir_domain();
	dir_domain_st get_dir_domain();
	void display_dir_domain();
	
private:
	void goto_poi(FILE **cmd_pipe);
	entity_type_t parse_entity(char *buffer);
	string extract_dir_name(char *buffer);
	void extract_file_attributes(char *buffer, file_st *file);
	void extract_file_name(char *buffer, file_st *file);
	void clear_dir_domain_buffer();

	dir_domain_st dir_curr_domain;
};

#endif
