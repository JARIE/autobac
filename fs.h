// File: fs.h
// Authors:
//		- Jarielle Catbagan
//		- Denny Dimalanta
// Created: 11, August 2014

#ifndef FS_H
#define FS_H

#include <vector>
#include <string>
#include "defines.h"
#include "dirparser.h"

using namespace std;

class file_system_ct : public dirparser_ct {
public:
	file_system_ct(string main_path, string root);
	void store_dir_domain(uint16_t level, vector<file_st> files, string relative_path, vector<string> directories);
	void store_main_path(string main_path);
	string get_main_path();
	void display_dir_domains();
	string obtain_domain_rel_path();
	void populate_filesys();
	program_status_t operator<<(const file_system_ct &src_fs);
private:
	vector<string> extract_path2path(string path);

	
	vector< vector<dir_domain_st> > file_system;
	string main_path;
	vector<string> top_level;
	vector<string> current_level;
	uint16_t level;
};

#endif





