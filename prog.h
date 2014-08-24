/* File: prog.h
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

#ifndef PROG_H
#define PROG_H

#include "defines.h"

class prog_ct {
// this class keeps track of the current state of the program with the 
// object created
public:
	prog_ct();
	program_status_t check_paths_validity(string src_path, 
					      string dest_path, 
					      char **msg_buffer);
	void set_progstat(program_status_t prog_stat);
	void exit_iferror(char *err_msg);
private:
	program_status_t program_status;
	execution_status_t execution_status;
};

#endif
