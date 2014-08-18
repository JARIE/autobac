// File: fs.cpp
// Authors:
//		- Jarielle Catbagan
//		- Denny Dimalanta
// Created: 11, August 2014

#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include "defines.h"
#include "fs.h"

using namespace std;

file_system_ct::file_system_ct(string main_path, string root) {
	file_system_ct::main_path = main_path;
	top_level.push_back(root);
	level = 0;
}

void file_system_ct::store_dir_domain(uint16_t level,
				      vector<file_st> files,
				      string relative_path,
				      vector<string> directories) {
	dir_domain_st dir_domain;
	dir_domain.files = files;
	dir_domain.relative_path = relative_path;
	dir_domain.directories = directories;

	if(level < file_system.size()) {	
		file_system[level].push_back(dir_domain);
	} else {
		vector<dir_domain_st> dir_domain_vect;

		dir_domain_vect.push_back(dir_domain);
		file_system.push_back(dir_domain_vect);
	}
}

void file_system_ct::store_main_path(string main_path) {
	file_system_ct::main_path = main_path;
}

string file_system_ct::get_main_path() {
	return main_path;
}

void file_system_ct::display_dir_domains() {
	for(int level = 0; level < file_system.size(); ++level) {
		cout << "level: " << level << endl;
		for(int domain = 0; domain < file_system[level].size(); ++domain) {
			cout << "\tdomain: " << domain << endl;
			cout << "\t\t" << "relative path: " << file_system[level][domain].relative_path.c_str() << endl;
			for(int index = 0; index < file_system[level][domain].directories.size(); ++index)
				cout << "\t\t" << file_system[level][domain].directories[index].c_str() << endl;
			for(int index = 0; index < file_system[level][domain].files.size(); ++index) {
				cout << "\t\t" << file_system[level][domain].files[index].name.c_str() << endl;;
				/*
				cout << " - ";
				cout << file_system[level][domain].files[index].date_time.month << '/';
				cout << file_system[level][domain].files[index].date_time.day << '/';
				cout << file_system[level][domain].files[index].date_time.year << ' ';
				cout << file_system[level][domain].files[index].date_time.hour << ':';
				cout << file_system[level][domain].files[index].date_time.minute << endl;
				*/
			}
		}
	}
}

void file_system_ct::populate_filesys() {
	enum loop_status_t {EXIT = 0, CONTINUE} loop_status;

	char *path_now;
	const char *path_next;
	path_now = _getcwd(NULL, 0);
	path_next = main_path.c_str();

#ifdef DRIVE_CHANGE_ENABLED
	if(path_now[0] != path_next[0]) {
		string drive_letter = path_next;
		drive_letter.resize(2);
		system(drive_letter.c_str());
	}
#endif

	free(path_now);

	_chdir(main_path.c_str());

	path_now = _getcwd(NULL, 0);
	cout << path_now << endl;
	free(path_now);

	loop_status = CONTINUE;
	
	do {
		directory_status_t directory_status;
		dir_domain_st dir_domain;
		string domain_rel_path;

		// extract all file and directory names as well as the file attributes to the corresponding files

		// @dirparser_ct::parse_dir_domain() - modify funtion name to reflect actual task of finding contents ir directory
		// not relative path
		directory_status = dirparser_ct::parse_dir_domain(); 

		if(directory_status == NON_EMPTY) {
			// retrieve the information gathered from previous function call

			// @dirparser_ct::get_dir_domain() - just as the previous call, modify function name to reflect true task
			dir_domain = dirparser_ct::get_dir_domain(); 
			// get the relative path from the start of the main path
			domain_rel_path = obtain_domain_rel_path();
			// store that relative path with the data structure containing the file names/attributes and directory names all in
			// one place
			dir_domain.relative_path = domain_rel_path;
			// store the domain onto the current level
			store_dir_domain(level, dir_domain.files, dir_domain.relative_path, dir_domain.directories);
			for(int index = 0; index < dir_domain.directories.size(); ++index) {
				//save the directories onto to current_level for visiting later to parse the contents

				// @push_back() - strings pushed are only names need to include the path between the main path and the
				// directory
				string path_buffer = dir_domain.relative_path;
				if(dir_domain.relative_path != "/")
					path_buffer += '/';
				path_buffer += dir_domain.directories[index];
				current_level.push_back(path_buffer);
			}
		}

		// remove the directory from top level and attempt to go to the next one
		top_level.pop_back();

		if(top_level.empty() && !current_level.empty()) {
			// since all domains have been resolved, get ready to go fill in the next level
			++level;
			// update top_level with current_level
			top_level = current_level;
			// clear the current level to get ready for the next current level
			current_level.clear();
			// need to change into directory specified at last element of top_level
			uint16_t index = top_level.size() - 1;
			string new_path = main_path;
			//cout << main_path << endl;
			new_path += top_level[index];
			//cout << new_path << endl;
			_chdir(new_path.c_str());
		}
		else if((!top_level.empty() && !current_level.empty()) || 
			(!top_level.empty() && current_level.empty())) {
			// need to change into directory specified at last element of top_level
			uint16_t index = top_level.size() - 1;
			string new_path = main_path;
			//cout << main_path << endl;
			new_path += top_level[index];
			//cout << new_path << endl;
			_chdir(new_path.c_str());
		}
		else { //top_level.empty && current_level.empty()
			loop_status = EXIT;
		}

	} while(loop_status == CONTINUE);

}

string file_system_ct::obtain_domain_rel_path() {
	string rel_path, new_path = "/";
	char *path_buffer;

	path_buffer = _getcwd(NULL, 0);

	

	rel_path = path_buffer;
	free(path_buffer);

	uint16_t boundary = rel_path.size() - main_path.size();
	boundary -= 1;


	if(main_path.size() < rel_path.size()) {
		rel_path.erase(rel_path.begin(), rel_path.end() - boundary);
		new_path += rel_path;
		rel_path = new_path;
	}
	else if(main_path.size() == rel_path.size()) {
		rel_path = new_path;
	}
		
	return rel_path;
}

// below is still under development

program_status_t file_system_ct::operator<<(const file_system_ct &src_fs) {
	
	for(int level = 0; level < src_fs.file_system.size(); ++level) {
		DEBUG("level: %i", level);
		for(int domain = 0; domain < src_fs.file_system[level].size(); ++domain) {
			DEBUG(" - domain: %i\n", domain);
			vector<string> path_to_path;
			
			path_to_path = extract_path2path(src_fs.file_system[level][domain].relative_path);


			_chdir(this->main_path.c_str());
			if(path_to_path.size() > 1 || path_to_path[0] != "/") {
				for(int dir_index = 0; dir_index < path_to_path.size(); ++dir_index) {
					if(_chdir(path_to_path[dir_index].c_str())) {
						_mkdir(path_to_path[dir_index].c_str());
						_chdir(path_to_path[dir_index].c_str());
					}
				}
			}

			path_to_path.clear();

			DEBUG("path_to_path cleared\n");

			if(!this->file_system.empty()) {
				DEBUG("not empty\n");
				if(level < this->file_system.size() && domain < this->file_system[level].size()) {

					enum existence_status_t {NONEXISTENT = 0, EXISTING} direxistence_status, fileexistence_status;

					for(int src_dir_index = 0; src_dir_index < src_fs.file_system[level][domain].directories.size(); ++src_dir_index) {
						DEBUG("checking directores\n");
						direxistence_status = NONEXISTENT;

						// NEED TO WATCH LEVEL AND DOMAIN, THERE MIGHT BE FEWER LEVELS/DOMAINS IN DESTINATION THAN SOURCE
						// FIX THIS BUG!!!
						for(int dest_dir_index = 0; dest_dir_index < this->file_system[level][domain].directories.size(); ++dest_dir_index) {
							if(src_fs.file_system[level][domain].directories[src_dir_index] ==
								this->file_system[level][domain].directories[dest_dir_index])
								direxistence_status = EXISTING;
						}
				
						if(direxistence_status == NONEXISTENT) {
							_mkdir(src_fs.file_system[level][domain].directories[src_dir_index].c_str());
						}
					}

					DEBUG("directories checked\n");

					enum epoch_status_t {UNKNOWN = 0, OUTDATED, NEW} fileepoch_status;

					for(int src_file_index = 0; src_file_index < src_fs.file_system[level][domain].files.size(); ++src_file_index) {
						DEBUG("checking source file\n");
						fileexistence_status = NONEXISTENT;
						fileepoch_status = UNKNOWN;
						for(int dest_file_index = 0; dest_file_index < this->file_system[level][domain].files.size(); ++dest_file_index) {
							if(src_fs.file_system[level][domain].files[src_file_index].name ==
								this->file_system[level][domain].files[dest_file_index].name)
								fileexistence_status = EXISTING;

							if(fileexistence_status == EXISTING) {
								if((src_fs.file_system[level][domain].files[src_file_index].date_time.month >
								    this->file_system[level][domain].files[dest_file_index].date_time.month) ||
								   (src_fs.file_system[level][domain].files[src_file_index].date_time.day >
								    this->file_system[level][domain].files[dest_file_index].date_time.day) ||
								   (src_fs.file_system[level][domain].files[src_file_index].date_time.year >
								    this->file_system[level][domain].files[dest_file_index].date_time.year) ||
								   (src_fs.file_system[level][domain].files[src_file_index].date_time.hour >
								    this->file_system[level][domain].files[dest_file_index].date_time.hour) ||
								   (src_fs.file_system[level][domain].files[src_file_index].date_time.minute >
								    this->file_system[level][domain].files[dest_file_index].date_time.minute)) {
									fileepoch_status = OUTDATED;
								}
							}	
						}

						if(fileexistence_status == NONEXISTENT || fileepoch_status == OUTDATED) {
							string input_file = src_fs.main_path;
							string output_file = this->main_path;

							cout << "main path: " << src_fs.main_path << endl;
					
							input_file += src_fs.file_system[level][domain].relative_path;
							output_file += src_fs.file_system[level][domain].relative_path;

						
							cout << "rel path: " << src_fs.file_system[level][domain].relative_path << endl;

							cout << "name: " << src_fs.file_system[level][domain].files[src_file_index].name << endl;

							int index = src_fs.file_system[level][domain].relative_path.size();
							if(src_fs.file_system[level][domain].relative_path[index - 1] != '/' &&
								src_fs.file_system[level][domain].relative_path[index - 1] != '\\') {
								input_file += '/';
								output_file += '/';
							}

							input_file += src_fs.file_system[level][domain].files[src_file_index].name;
							output_file += src_fs.file_system[level][domain].files[src_file_index].name;

							cout << "input: " << input_file << endl;
							cout << "output: " << output_file << endl;

							ifstream input_file_fd(input_file.c_str(), ios::in | ios::binary);
							ofstream output_file_fd(output_file.c_str(), ios::out | ios::binary);

							output_file_fd << input_file_fd.rdbuf();
						
							input_file_fd.close();
							output_file_fd.close();
						}
						DEBUG("input and ouput file printed\n");
			
					}
					DEBUG("done checking source files in current domain\n");
				}
			}
			else {
				for(int src_dir_index = 0; src_dir_index < src_fs.file_system[level][domain].directories.size();
					++src_dir_index) {
					_mkdir(src_fs.file_system[level][domain].directories[src_dir_index].c_str());
				}
				for(int src_file_index = 0; src_file_index < src_fs.file_system[level][domain].files.size();
					++src_file_index) {
					string input_file = src_fs.main_path;
					string output_file = this->main_path;
					
					input_file += src_fs.file_system[level][domain].relative_path;
					output_file += this->file_system[level][domain].relative_path;

					input_file += src_fs.file_system[level][domain].files[src_file_index].name;
					output_file += src_fs.file_system[level][domain].files[src_file_index].name;

					cout << "input: " << input_file << endl;
					cout << "output: " << output_file << endl;

					ifstream input_file_fd(input_file.c_str(), ios::in | ios::binary);
					ofstream output_file_fd(output_file.c_str(), ios::out | ios::binary);

					output_file_fd << input_file_fd.rdbuf();

					input_file_fd.close();
					output_file_fd.close();
				}
			}
		}
		DEBUG("done with level\n");
	}

	return NO_ERROR;
}

vector<string> file_system_ct::extract_path2path(string path) {
	vector<string> path_to_path;
	string path_buffer;
	int index;


	if(path.size() > 1) {
		if(path.at(0) == '/' || path.at(0) == '\\') 
			index = 1;
		else
			index = 0;
	
		for(; index < path.size(); ++index) {
			char c = path.at(index);
			if(c != '/' && c != '\\') {
				path_buffer.append(1, c);
				if(index == (path.size() - 1))
					path_to_path.push_back(path_buffer);
			}
			else {
				path_to_path.push_back(path_buffer);
				path_buffer.clear();
			}
		}
	}
	else {
		path_to_path.push_back("/");
	}
	
	return path_to_path;
}
	

