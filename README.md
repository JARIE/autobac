#autobac

######Introduction

The name of this project is Autobac, and consequently the name of the program
is `autobac`.  What `autobac` is, and as its name might already imply, is a 
program that automatically backs up files and folders from a source location to 
a destination location.  These locations are specified by the user either at 
runtime or before program execution depending on how `autobac` has been 
configured to do so.  This program was created with the goal to alleviate the 
necessity of having to individually track each and every file and folder that 
needs to be backed up.  As a result this will increase productivity and provide 
peace of mind knowing that your files and folders are safely secured with little 
hassle.

By default, the source code compiles the program to provide a menu system where 
the user can ask for help on the sort of options available with the program, 
whether they want to back up files and folders, or to exit the program.  This 
continues in a loop until the user specifies that he/she wants to exit the 
program.

`autobac` can also be compiled to represent a similar structure to a UNIX 
command where execution of the program is done by invoking the name of the 
program and optionally providing options and arguments on the command line.  
This kind of configuration is more ideal for executing the program in a shell 
script, or a batch file within Windows, to automate the task of backing up 
multiple files and folders from different source locations to optionally 
different destination locations.

######Structure

When the program has been initiated to back up files and folders from a source 
to a destination, regardless of what configuration `autobac` has been compiled 
into, the first thing that the program must do is try to figure out what sort 
of structure it is working with.  In a typical file system, the folders and 
files within that system represent a directory tree structure where there is a 
root folder that contains folders and files, and those folders contain folders 
and files and so on.  An example of a directory tree is shown in figure 1 below.

![Directory Tree Structure](https://raw.github.com/JARIE/autobac/misc/images/directory-tree-structure.png
