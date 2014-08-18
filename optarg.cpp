// File: optarg.cpp
// Authors:
//		- Jarielle Catbagan
//		- Denny Dimalanta
// Created: 09, August 2014

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "optarg.h"
#include "defines.h"

using namespace std;

// class opt_ct implementation
opt_ct::opt_ct(existence_t existence) : arg_existence(existence) {
	opt_status = NOT_SET;
}

void opt_ct::set_opt_status() {
	opt_status = SET;
}

set_status_t opt_ct::get_opt_status() {
	return opt_status;
}

// class arg_ct implementation
arg_ct::arg_ct() {
	arg_status = NOT_SET;
	argument = NULL;
}

arg_ct::~arg_ct() {
	delete[] argument;
}

void arg_ct::set_arg_status() {
	arg_status = SET;
}

set_status_t arg_ct::get_arg_status() {
	return arg_status;
}

void arg_ct::set_argument(char *arg) {
	size_t arg_size = strlen(arg);

	argument = new char[arg_size + 1];

	strcpy(argument, arg);
	argument[arg_size] = '\0';
}

string arg_ct::get_argument() {
	if(argument == NULL) 
		return "";
	else
		return argument;
}


// class h_opt implementation
h_opt_ct::h_opt_ct(existence_t existence) : opt_ct(existence) {
}

void h_opt_ct::show_help() {
	cout << "usage: autobac [options/arguments]" << endl;
	cout << endl;
	cout << "-h\tdisplays the available options and their descriptions" << endl;
	cout << "-d\tspecifies the destination location to backup to" << endl;
	cout << "-s\tspecifies the source location to backup from" << endl;
}

// class d_opt implementation
d_opt_ct::d_opt_ct(existence_t existence) : opt_ct(existence) {
}

// class s_opt implementation
s_opt_ct::s_opt_ct(existence_t existence) : opt_ct(existence) {
}

// class optarg_parse_ct implementation

optarg_parser_ct::optarg_parser_ct(existence_t hopt_arg_exist, existence_t dopt_arg_exist, existence_t sopt_arg_exist) :
	h_opt_ct(hopt_arg_exist), d_opt_ct(dopt_arg_exist), s_opt_ct(sopt_arg_exist) {
}

program_status_t optarg_parser_ct::parse_cli_input(int argc, char **argv, char **msg_buffer) {
	enum parse_status_t {OPTIONS = 0, ARGUMENTS} parse_status;

	if(argc == 1) {
		message_tobuffer(msg_buffer, "no arguments specified");
		return ERROR;
	}

	parse_status = OPTIONS;

	for(int index = 1; index < argc; ++index) {
		if(parse_status == OPTIONS) {
			if(strlen(argv[index]) == 2) {
				if(argv[index][0] == '-') {
					if(determine_option(index, argv) == ERROR) {
						message_tobuffer(msg_buffer, "invalid option specified");
						return ERROR;
					}
				} else {
					message_tobuffer(msg_buffer, "invalid option specified");
					return ERROR;
				}
			} else {
				message_tobuffer(msg_buffer, "invalid option specified");
				return ERROR;
			}
			parse_status = ARGUMENTS;
		} else { //parse_status == ARGUMENTS
			switch(option_buffer) {
			case 'h':
				message_tobuffer(msg_buffer, "no additional options/arguments can be specified with 'h' option");
				return ERROR;
			case 'd':
				d_opt_ct::set_argument(argv[index]);
				d_opt_ct::set_arg_status();
				break;
			case 's':
				s_opt_ct::set_argument(argv[index]);
				s_opt_ct::set_arg_status();
				break;
			}
			parse_status = OPTIONS;	
		}
	}

	if(option_set_validity(msg_buffer) == ERROR)
		return ERROR;

	if(argument_set_validity(msg_buffer) == ERROR)
		return ERROR;

	return NO_ERROR;
}

execution_status_t optarg_parser_ct::execute_method() {
	if(h_opt_ct::get_opt_status() == SET) {
		h_opt_ct::show_help();
		return EXIT;
	} else {
		return CONTINUE;
	}
}

program_status_t optarg_parser_ct::option_set_validity(char **msg_buffer) {
	if(h_opt_ct::get_opt_status() == SET && (d_opt_ct::get_opt_status() == SET || s_opt_ct::get_opt_status() == SET)) {
		message_tobuffer(msg_buffer, "no additional options/arguments can be specified with 'h' option");
		return ERROR;
	}
	return NO_ERROR;
}

program_status_t optarg_parser_ct::argument_set_validity(char **msg_buffer) {
	if((d_opt_ct::get_opt_status() == SET && d_opt_ct::get_arg_status() == NOT_SET) ||
	   (s_opt_ct::get_opt_status() == SET && s_opt_ct::get_arg_status() == NOT_SET)) {
		message_tobuffer(msg_buffer, "incomplete argument(s)");
		return ERROR;
	}
	return NO_ERROR;
}

void optarg_parser_ct::message_tobuffer(char **buffer, char *message) {
	size_t message_size = strlen(message);
	*buffer = new char[message_size + 1];
	strcpy(*buffer, message);
}

program_status_t optarg_parser_ct::determine_option(int index, char **argv) {
	switch(argv[index][1]) {
	case 'h':
		h_opt_ct::set_opt_status();
		option_buffer = 'h';
		break;
	case 'd':
		d_opt_ct::set_opt_status();
		option_buffer = 'd';
		break;
	case 's':
		s_opt_ct::set_opt_status();
		option_buffer = 's';
		break;
	default:
		return ERROR;
		break;
	}
	return NO_ERROR;
}