/* File: prog.cpp
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

#include <iostream>
#include <direct.h>
#include "prog.h"
#include "defines.h"

using namespace std;

prog_ct::prog_ct() {
	program_status = NO_ERROR;
}

void prog_ct::set_progstat(program_status_t prog_stat) {
	program_status = prog_stat;
}

void prog_ct::exit_iferror(char *err_msg) {
	if(program_status == ERROR) {
		cerr << "error: " << err_msg << endl;
		exit(1);
	}
}

program_status_t prog_ct::check_paths_validity(string src_path, 
					       string dest_path, 
					       char **msg_buffer) {
	// this function checks to see whether the source path and 
	// destination path are both valid and if not an appropriate error
	// message is created
	char *current_path;
	program_status_t src_path_status = UNDEFINED;
	program_status_t dest_path_status = UNDEFINED;

	if(src_path.size() == 0) {
		char *message = "source path was not specified";
		size_t message_size = strlen(message);
		*msg_buffer = new char[message_size + 1];
		strcpy(*msg_buffer, message);
		return ERROR;
	}
	else if(dest_path.size() == 0) {
		char *message = "destination path was not specified";
		size_t message_size = strlen(message);
		*msg_buffer = new char[message_size + 1];
		strcpy(*msg_buffer, message);
		return ERROR;
	}

	current_path = _getcwd(NULL, 0);

	if(_chdir(src_path.c_str()))
		src_path_status = ERROR;
	else 
		src_path_status = NO_ERROR;

	if(_chdir(dest_path.c_str()))
		dest_path_status = ERROR;
	else
		dest_path_status = NO_ERROR;

	if(src_path_status == ERROR && dest_path_status == NO_ERROR) {
		char *message = "source path specified is invalid";
		size_t message_size = strlen(message);
		*msg_buffer = new char[message_size + 1];
		strcpy(*msg_buffer, message);
	}
	else if(src_path_status == NO_ERROR && dest_path_status == ERROR) {
		char *message = "destination path specified is invalid";
		size_t message_size = strlen(message);
		*msg_buffer = new char[message_size + 1];
		strcpy(*msg_buffer, message);
	}
	else if(src_path_status == ERROR && dest_path_status == ERROR) {
		char *message = 
			"source and destination path specified is invalid";
		size_t message_size = strlen(message);
		*msg_buffer = new char[message_size + 1];
		strcpy(*msg_buffer, message);
	}

	if(src_path_status == ERROR || dest_path_status == ERROR) {
		free(current_path);
		return ERROR;
	}
	else {
		_chdir(current_path);
		free(current_path);
		return NO_ERROR;
	}
}
