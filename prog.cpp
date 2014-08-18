// File: prog.cpp
// Authors:
//		- Jarielle Catbagan
//		- Denny Dimalanta
// Created: 09, August 2014

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

program_status_t prog_ct::check_paths_validity(string src_path, string dest_path, char **msg_buffer) {
	char *current_path;
	program_status_t src_path_status = UNDEFINED, dest_path_status = UNDEFINED;

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
		char *message = "source and destination path specified is invalid";
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