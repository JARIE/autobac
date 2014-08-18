// File: prog.h
// Authors:
//		- Jarielle Catbagan
//		- Denny Dimalanta
// Created: 09, August 2014

#ifndef PROG_H
#define PROG_H

#include "defines.h"

class prog_ct {
public:
	prog_ct();
	program_status_t check_paths_validity(string src_path, string dest_path, char **msg_buffer);
	void set_progstat(program_status_t prog_stat);
	void exit_iferror(char *err_msg);
private:
	program_status_t program_status;
	execution_status_t execution_status;
};

#endif