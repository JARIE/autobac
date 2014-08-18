// File: dirparser.h
// Authors:
//		- Jarielle Catbagan
//		- Denny Dimalanta
// Created: 14, August 2014

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