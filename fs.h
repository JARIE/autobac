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
	void store_dir_domain(uint16_t level, vector<file_st> files, 
			      string relative_path, 
			      vector<string> directories);
	void store_main_path(string main_path);
	string get_main_path();
	void display_dir_domains();
	string obtain_domain_rel_path();
	void populate_filesys();
	program_status_t operator<<(const file_system_ct &src_fs);
private:
	// @start - utility function declarations
	vector<string> extract_path2path(string path);
	void display_contents(int level, int domain);
	// @end - utility function declarations

	// the directories and files and recursive directories and their 
	// associated files are stored in a two-dimensional array-like 
	// structure

	// the directory tree is visualized through the aforementioned 
	// two-dimensional array-like strucuture, whose root is specified 
	// in the context of the main path that will be specified as the 
	// location that will either be backed up from or backed up to, 
	// where dimensionsare divided among levels and domains

	// levels refer to the position of a current directory relative to the
	// main path; this means the number of directories it takes to change
	// from the main path to the current directory dictates the level it 
	// is on; e.g. the root is considered to be at level 0, and a child 
	// directory is one level higher then its parent directory

	// before talking about domains, the term "root" will be used in this
	// file and any other files associated with this file to mean the
	// main path of the location that will be specified by the user

	// domains divide the current level to group associated files and
	// directories that belong to the same parent directory on the 
	// previous level; the root only has one domain which is all the files
	// and directories that are specified in the root

	// to help visualize this even further, please refer to the the 
	// figure below
	vector< vector<dir_domain_st> > file_system;

	// this is string variable that keeps track of the main path; this
	// is specified by the user
	string main_path;
	// top_level is used for keeping track the number of domains to 
	// analyze in any given level; i.e. extracting directory names as well
	// as file names and their attributes
	vector<string> top_level;
	// current_level is used for keeping track of the next domains to 
	// analyze once program execution reaches the next level
	vector<string> current_level;
	// keeps track of what level to store a given domain
	uint16_t level;
};

/*

d = domain
l = level
                               -------------
  l0 --------->                | root (d0) |
                               -------------
                              /      |      \  
                           ------ ------ ------
  l1 --------->            | d0 | | d1 | | d2 |
                           ------ ------ ------
                        /    |       |      |    \   
                   ------ ------   ------  ------ ------
  l2 --------->    | d0 | | d1 |   | d2 |  | d3 | | d4 |
                   ------ ------   ------  ------ ------

*/

#endif





