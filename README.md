**Purpose**

This is a 42 School project focusing on pipe() and fork() C functions. Purpose is to develop a program which recreates a pipe ("|") behaviour like in bash, using fork(), pipe(), dup2().

**Installation**

the library compiles with gcc or clang, using "cc" alias command.
In your terminal run "make" in the main directory, which compiles all files and creates a program named pipex
launch in your terminal "./pipex" with four (4) arguments containing (i) input filename, (ii) first command, (iii) second command and (iv) output filename.

"make clean" removes object files created.
"make fclean" removes object files and the program.
"make re" does a "make fclean" followed by a "make" to regenerate all files.

**Dependencies**

My own library "Libft" which was developed as part of the school to mimic C standard functions is shipped with this project. We are restricted by the school in the external functions we can use for each project, but allowed to use our own functions and library such as Libft.

*Tested on Linux Debian Trixie and Ubuntu*

**Additional information**

*For C Projects, 42 School imposes a norm to follow strictly. Amongst many things, we are restricted to write no more than 25 lines per function, and 5 functions per file. I really do love norms, but just mentioning this to explain why sometimes we split functions and multiply files :)*
