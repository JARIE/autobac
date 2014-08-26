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
program and optionally providing options and arguments on the command line.  This
kind of configuration is more ideal for executing the program in a shell 
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

![Directory Tree Structure](https://raw.github.com/JARIE/autobac/master/misc/images/directory-tree-structure.png)

When a user specifies a location, either as the source or the destination, this 
path in the context of the program effectively becomes the root.  It is this 
user-defined path that lets the program know that the user wishes to backup all 
files and folders from that given path.  It is obvious that when a single 
location is getting backed up that location can be represented as a single 
entity, in this case a folder.  This folder is viewed as the root and that when 
this folder is backed up by the program, all the files and folders from this 
root (folder) are the ones implicitly getting backed up.

Going back to figure 1, the tree structure would be very difficult, if not 
impossible, to store in a linear array.  As a result implementing a 
multidimensional array to visualize the tree structure would be easier. 
The format of the multidimensional array is explained in more detail shortly.

The reason why the directory tree has to be extracted, both for the source and 
the destination, is that this will let the program know where the folders and 
files are situated in the tree which will be used to compare the source and 
destination to see which files and folders need to be backed up.  This 
directory tree, whose root is specified by the path given by the user, needs 
to be stored in a particular structure that is designed with consideration to 
avoid decreasing the performance of the program.  This will in turn provide a 
systematic and efficient way of storing the directory for easy access later on.

The directory tree has been represented with a two-dimensional array divided 
among levels and domains where the first dimension pertains to the level and 
the other pertaining to the domain.  Given a file or folder, the number of 
folders it takes to change from the main path, either the source or the 
destination, dictates the level it is on.  For example, let us say that the user 
specified the main path as *C:/Users/Guest/Documents/* and then the program does 
some execution and is now at *C:/Users/Guest/Documents/Books/Technology/Robots.pdf*.  
Looking at the new current directory that the program is in, we see that it took two 
folders to change into before accessing Robots.pdf.  Here the files and folders under
the root is considered a level on its own and also the pdf file is also on a level on 
its own.  Therefore this makes the pdf document on level four.  Domains on the other 
hand contain a set of files and folders that share the same parent folder.  
So the file *C:/Users/Guest/Documents/Books/Technology/Robots.pdf* and the folder 
*C:/Users/Guest/Documents/Books/Technology/Misc* belong to the same domain because 
they share the same parent folder Technology.  On the other 
*C:/Users/Guest/Documents/Books/Cooking/Spaghetti.txt* would be on a different domain 
because it has a different parent folder, Cooking, than the previous two but belong on 
the same level.  Further a domain contains a list of files and their attributes as 
well as a list of directories that share the same parent folder.

######Algorithm

Now that a structure has been created to systematically and efficiently store 
the information about the directory tree(s) for easy access later on in the 
program, a way of extracting the information about the folders and files within 
the directory tree so that it can be stored in the newly created structure has 
to be developed.  For this a search algorithm must be utilized in order to search
each individual directory and the directories within those directories while at 
the same time extracting information about the folders and files within those 
directories to see what domain and level they belong to and saving them in the 
appropriate location in the data structure.  

The algorithm that was implemented for searching and extracting information 
about the various parts of the directory tree is the Breadth-first Search 
algorithm.  Here the program starts at the root (main path specified by the user) 
and inspects the nearby nodes that appear on the same level.  Until all the nodes 
are inspected of which are on the same level, the program goes to the next level 
and repeats the process.  This process is repeated until no more levels remain.  
A typical path that the program would travel on the directory tree by 
implementing the Bread-first Search algorithm is shown in figure 2 below.

![Breadth-First Search Graph](https://raw.github.com/JARIE/autobac/master/misc/images/breadth-first-search-graph.png)

To give a more better picture in the context of how autobac implements the 
algorithm mentioned is to first think of each node as an arbitrary folder.  For the 
simplicity of explanation, folders will only be mentioned even though the concepts 
still apply to files.  Here starting a node 1, which is the main path or in other 
words the root folder in the context of the main path, the program extracts (searches)
node 1 for all the directories and files that exist in the root folder.  These 
directories obtained from node 1 are what makes up node 2, 3, 4 and 5 by referring to 
the tree graph in figure 2.  Once the level is exhausted the program jumps to the next
level and instead of only having to deal with one domain it searches all the domains; 
in this case nodes 2 through 5 and conducts the same process as it did for node 1.  
This is repeated until there are no more levels, or more specifically nodes to search 
and extract information from.

![Flowchart](https://raw.github.com/JARIE/autobac/master/mics/images/flowchart.png)
