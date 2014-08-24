// File: main.cpp
// Authors:
//		- Jarielle Catbagan
//		- Denny Dimalanta
// Created: 09, August 2014

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <direct.h>
#include "optarg.h"
#include "defines.h"
#include "prog.h"
#include "fs.h"
#include "dirparser.h"
#include <conio.h>

using namespace std;

#define APP_STYLE
										
int main(int argc, char **argv) {
#if defined APP_STYLE
	execution_status_t loop_status = CONTINUE;
	char option, *message;
	program_status_t program_status;
	prog_ct program;
	string src_path, dest_path;
	char file_change_status;
	change_status_t file_status;

	cout << "welcome and thank you for using autobac!" << endl;
	cout << "what would you like to do?" << endl;
	cout << "\th = display details about the program and supported options" << endl;
	cout << "\tb = backup files" << endl;
	cout << "\te = exit the program" << endl;

	do {
		cout << "> ";
		cin >> option;

		switch(option) {
		case 'h':
			cout << "\th = display details about the program and supported options" << endl;
			cout << "\tb = backup files" << endl;
			cout << "\te = exit the program" << endl;
			break;
		case 'b':
			cout << "source: ";
			cin.sync();
			getline(cin, src_path);
			cout << "destination: ";
			cin.sync();
			getline(cin, dest_path);
			cout << "would you like to overwrite old files with new files? (y/n)" << endl;
			cout << "> ";
			cin >> file_change_status;

			program_status = program.check_paths_validity(src_path, dest_path, &message);
			switch(file_change_status) {
			case 'y':
				file_status = VOLATILE;
				break;
			case 'n':
				file_status = NONVOLATILE;
				break;
			default:
				program_status = ERROR;
				cout << "invalid input specified for overwrite verification" << endl;
				break;
			}
			if(program_status == ERROR) {
				cout << message << endl;
				cout << "the backup process has been terminated" << endl;
			}
			else {
				file_system_ct src_fs(src_path, ".", NA);
				file_system_ct dest_fs(dest_path, ".", file_status);

				src_fs.populate_filesys();
				dest_fs.populate_filesys();

				program_status = dest_fs << src_fs;

				if(program_status == ERROR) 
					cout << "backup unsuccessful" << endl;
				else
					cout << "backup successful" << endl;
			}

			cout << "what would you like to do now? (enter 'h' to list options)" << endl;

			break;
		case 'e':
			cout << "thank you for using autobac" << endl;
			cout << "program will now terminate" << endl;
			loop_status = EXIT;
			break;
		default:
			cout << "Invalid option specified, please try again" << endl << "> ";
			break;
		}
	} while(loop_status == CONTINUE);
#elif defined CLI_STYLE
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

	// obtain the source location to backup from and store it into a string
	// dedicated for the source path
	src_loc = optarg_parser.s_opt_ct::get_argument();
	// obtain the destination location to backup from and store it into a 
	//string dedicated for the source path
	dest_loc = optarg_parser.d_opt_ct::get_argument();

	// check whether both the source and/or destination paths are valid,
	// i.e. they exist
	program_status = program.check_paths_validity(src_loc, dest_loc, 
						      &message);

	// update the current status of the whole program based on the status
	// returned from the previous call about the validity of both the 
	// source and destination paths
	program.set_progstat(program_status);
	program.exit_iferror(message);
	

	// create a file_system_ct object that will hold informaiton about
	// all the directories and files at the source location specified by 
	// the source path
	
	// the root of the file system in the context of the source path is the 
	// source path itself
	
	// the constructors initializes the objects with the main path and the 
	// top level structure for keeping track the number of domains in the 
	// current level with the with the current directory in the context of 
	// the main path
	
	// starting off this is the only domain, and since backing up a location 
	// is executed with the notion that it is one single entity, backing up 
	// files and directories recursively within that location is implied

	// the destination is the same as the source
	file_system_ct src_fs(src_loc, ".", NA);
	file_system_ct dest_fs(dest_loc, ".", VOLATILE);

	// the above file_system_ct objects only creates a container for the
	// information of the files and directories specified at the respective
	// locations and initializes them

	// below is where the objects are filled with information
	src_fs.populate_filesys();
	dest_fs.populate_filesys();
	
#ifdef DEBUG
	cout << "SOURCE:" << endl;
	src_fs.display_dir_domains();
	cout << "DESTINATION:" << endl;
	dest_fs.display_dir_domains();
#endif

	// backup of the source files and directories from the source to the
	// destination is accomplished through the overloaded operator "<<"

	// retrieve the status for later analysis
	program_status = dest_fs << src_fs;

	// store the program status obtained about regarding the backup from the
	// source to the destination into the program module
	program.set_progstat(program_status);
	program.exit_iferror("back up unsuccessful");
#endif
	
	return 0;
}