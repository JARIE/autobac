// File: main.cpp
// Authors:
//		- Jarielle Catbagan
//		- Denny Dimalanta
// Created: 09, August 2014

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <direct.h>
#include "optarg.h"
#include "defines.h"
#include "prog.h"
#include "fs.h"
#include "dirparser.h"

using namespace std;

#define TEST

int main(int argc, char **argv) {
	optarg_parser_ct optarg_parser(ARG_VOID, ARG_PRESENT, ARG_PRESENT);
	char *message;
	program_status_t program_status;
	prog_ct program;
	execution_status_t execution_status;

	// make sure that sufficient arguments are supplied, and if so
	// determine whether they are valid and store values/return status
	// appropriately
	program_status = optarg_parser.parse_cli_input(argc, argv, &message);
	
	// store the program status obtained in the program module
	program.set_progstat(program_status);
	// determine how the program should act based on the stored program
	// status
	program.exit_iferror(message);

	// this point is reached if the options/arguments supplied are valid;
	// based on the options specified determine whether the program 
	// should continue or exit
	execution_status = optarg_parser.execute_method();
	if(execution_status == EXIT)
		exit(0);

	string src_loc, dest_loc;

	src_loc = optarg_parser.s_opt_ct::get_argument();
	dest_loc = optarg_parser.d_opt_ct::get_argument();

	program_status = program.check_paths_validity(src_loc, dest_loc, &message);

	program.set_progstat(program_status);
	program.exit_iferror(message);
	
	file_system_ct src_fs(src_loc, ".");
	file_system_ct dest_fs(dest_loc, ".");

	src_fs.populate_filesys();
	dest_fs.populate_filesys();
	
	
	cout << "SOURCE:" << endl;
	src_fs.display_dir_domains();
	cout << "DESTINATION:" << endl;
	dest_fs.display_dir_domains();
	

	program_status = dest_fs << src_fs;
	
	return 0;
}