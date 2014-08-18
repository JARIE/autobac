// File: dirparser.cpp
// Authors:
//		- Jarielle Catbagan
//		- Denny Dimalanta
// Created: 14, August 2014

#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <direct.h>
#include "dirparser.h"

using namespace std;

directory_status_t dirparser_ct::parse_dir_domain() {
	enum contents_t {NO_MORE = 0, MORE} contents;
	FILE *cmd_pipe;
	char buffer[150], *c_loc, *path_buffer;

	clear_dir_domain_buffer();
	
	cmd_pipe = _popen("dir", "r");
	goto_poi(&cmd_pipe);

	fgets(buffer, 150, cmd_pipe);

	c_loc = strchr(buffer, '/');
	if(c_loc == NULL) {
		_pclose(cmd_pipe);
		return EMPTY;
	}

	contents = MORE;

	do {
		if(parse_entity(buffer) == IS_DIRECTORY) {
			string dir_name;
			dir_name = extract_dir_name(buffer);
			
			dir_curr_domain.directories.push_back(dir_name);
		} 
		else {
			file_st file;
			extract_file_attributes(buffer, &file);
			extract_file_name(buffer, &file);

			cout << "file: " << file.name << endl;

			dir_curr_domain.files.push_back(file);
		}
		fgets(buffer, 150, cmd_pipe);

		c_loc = strchr(buffer, '/');
		if(c_loc == NULL)
			contents = NO_MORE;
	} while(contents == MORE);

	_pclose(cmd_pipe);
	return NON_EMPTY;
}

dir_domain_st dirparser_ct::get_dir_domain() {
	return dir_curr_domain;
}

void dirparser_ct::display_dir_domain() {
	cout << "directories: " << endl;
	for(int index = 0; index < dir_curr_domain.directories.size(); ++index)
		cout << dir_curr_domain.directories[index] << endl;
	cout << "files: " << endl;
	for(int index = 0; index < dir_curr_domain.files.size(); ++index) {
		cout << dir_curr_domain.files[index].name.c_str() << " - ";
		cout << dir_curr_domain.files[index].date_time.month << '-';
		cout << dir_curr_domain.files[index].date_time.day << '-';
		cout << dir_curr_domain.files[index].date_time.year << "   ";
		cout << dir_curr_domain.files[index].date_time.hour << ':';
		cout << dir_curr_domain.files[index].date_time.minute << endl;
	}
}


void dirparser_ct::goto_poi(FILE **cmd_pipe) {
	enum loop_status_t {EXIT = 0, CONTINUE} loop_status;
	char c;

	for(int i = 0; i < 2; ++i) {
		loop_status = CONTINUE;
		do {
			c = fgetc(*cmd_pipe);
			if(c == '/')
				loop_status = EXIT;
		} while(loop_status == CONTINUE);

		loop_status = CONTINUE;
		do {
			c = fgetc(*cmd_pipe);
			if(c == '\n')
				loop_status = EXIT;
		} while(loop_status == CONTINUE);
	}
}

entity_type_t dirparser_ct::parse_entity(char *buffer) {
	char *entity_literal;

	entity_literal = strstr(buffer, "<DIR>");

	if(entity_literal != NULL)
		return IS_DIRECTORY;
	else
		return IS_FILE;
}

string dirparser_ct::extract_dir_name(char *buffer) {
	char *c_loc;
	string dir_name;
	int c_size;

	c_loc = strstr(buffer, "<DIR>");

	while(*c_loc != ' ')
		++c_loc;
	while(*c_loc == ' ')
		++c_loc;

	c_size = strlen(c_loc);
	c_size -= 1;
	c_loc[c_size] = '\0';

	dir_name = c_loc;

	return dir_name;
}

void dirparser_ct::extract_file_attributes(char *buffer, file_st *file) {
	char month[3];
	char day[3];
	char year[5];
	char hour[3];
	char minute[3];

	month[0] = *buffer++;
	month[1] = *buffer;
	month[2] = '\0';
	buffer += 2;
	day[0] = *buffer++;
	day[1] = *buffer;
	day[2] = '\0';
	buffer += 2;
	year[0] = *buffer++;
	year[1] = *buffer++;
	year[2] = *buffer++;
	year[3] = *buffer;
	year[4] = '\0';
	buffer += 3;
	hour[0] = *buffer++;
	hour[1] = *buffer;
	hour[2] = '\0';
	buffer += 2;
	minute[0] = *buffer++;
	minute[1] = *buffer;
	minute[2] = '\0';
	
	file->date_time.month = (uint16_t) atol(month);
	file->date_time.day = (uint16_t) atol(day);
	file->date_time.year = (uint16_t) atol(year);
	file->date_time.hour = (uint16_t) atol(hour);
	file->date_time.minute = (uint16_t) atol(minute);
}

void dirparser_ct::extract_file_name(char *buffer, file_st *file) {
	char *c_loc, *newline_loc;
	//string file_name;

	c_loc = strstr(buffer, "M");
	++c_loc;

	while(*c_loc == ' ')
		++c_loc;
	while(*c_loc != ' ')
		++c_loc;

	++c_loc;
	newline_loc = strchr(c_loc, '\n');
	if(newline_loc != NULL)
		*newline_loc = '\0';

	file->name = c_loc;
}

void dirparser_ct::clear_dir_domain_buffer() {
	dir_curr_domain.directories.clear();
	dir_curr_domain.files.clear();
}

