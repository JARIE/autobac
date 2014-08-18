// File: optarg.h
// Authors:
//		- Jarielle Catbagan
//		- Denny Dimalanta
// Created: 09, August 2014

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
	optarg_parser_ct(existence_t hopt_arg_exist, existence_t dopt_arg_exist, existence_t sopt_arg_exist);
	program_status_t parse_cli_input(int argc, char **argv, char **msg_buffer);
	execution_status_t execute_method();
private:
	void message_tobuffer(char **buffer, char *message);
	program_status_t determine_option(int index, char **argv);
	char option_buffer;
	program_status_t option_set_validity(char **msg_buffer);
	program_status_t argument_set_validity(char **msg_buffer);
};

#endif