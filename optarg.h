/* File: optarg.h
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

#ifndef OPTARG_H
#define OPTARG_H

#include <string>
#include "defines.h"

using namespace std;

enum set_status_t {NOT_SET = 0, SET};
enum existence_t {ARG_VOID = 0, ARG_PRESENT};

class opt_ct {
public:
	// initialize class attributes
	opt_ct(existence_t existence);
	// set option status since option was specified
	void set_opt_status();
	// return the status whether the option was specified or not
	set_status_t get_opt_status();
private:
	// variable to track whether an option was specified
	set_status_t opt_status;		
	// determines whether an argument to an option can exist
	existence_t arg_existence;
};

class arg_ct {
public:
	// initialize class attributes
	arg_ct();
	// set argument status since argument was supplied to option
	~arg_ct();
	void set_arg_status();
	// return the status whether argument was set or not
	set_status_t get_arg_status();
	// store the argument given to the option
	void set_argument(char *arg);
	// return the argument stored
	string get_argument();
private:
	// variable to track whether an argument was supplied
	set_status_t arg_status;
	// pointer to storage where argument will be stored;
	// storage must first be dynamically allocated before
	// storing the argument
	char *argument;
};

class h_opt_ct : public opt_ct {
public:
	h_opt_ct(existence_t existence);
	void show_help();
};

class d_opt_ct : public opt_ct, public arg_ct {
public:
	d_opt_ct(existence_t existence);
};

class s_opt_ct : public opt_ct, public arg_ct {
public:
	s_opt_ct(existence_t existence);
};

class optarg_parser_ct : public h_opt_ct, public d_opt_ct, public s_opt_ct {
public:
	// this class is at the top of abstraction;
	// initializes the existence of arguments to the possible options
	optarg_parser_ct(existence_t hopt_arg_exist, 
			 existence_t dopt_arg_exist, 
			 existence_t sopt_arg_exist);
	program_status_t parse_cli_input(int argc, char **argv, 
					 char **msg_buffer);
	execution_status_t execute_method();
private:
	// @start utility function declarations
	void message_tobuffer(char **buffer, char *message);
	program_status_t determine_option(int index, char **argv);
	char option_buffer;
	program_status_t option_set_validity(char **msg_buffer);
	program_status_t argument_set_validity(char **msg_buffer);
	program_status_t parse_option(char **argv, char **buffer,
				      int index);
	// @end utility function declarations
};

#endif
