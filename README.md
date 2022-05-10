# SIMPLE SHELL
This project is about writing a simple UNIX command interpreter. 







<img src="https://i.njkhanh.com/img/simple-shell-ls-l-c.png?v=1630163126" alt="Simple Shell">

# DESCRIPTION
Simple_shell is an sh-compatible command language interpreter that executes commands read from the standard input or from a file.

The simple_shell is a command that reads lines from either a file or the terminal, interprets them, and generally executes other commands. The simple_shell implements a language that has flow control constructs, a macro facility that provides a variety of features in addition to data storage, along with built in history and line editing capabilities. It incorporates many features to aid interactive use and has the advantage that the interpretative language is common to both interactive and non-interactive use(shell scripts). That is, commands can be typed directly to the running shell or can be put into a file and the file can be executed directly by the shell.

# REQUIREMENTS
In this project, We are expected to look indepthly into:
1. How does a shell work
2. What is a pid and a ppid
3. How to manipulate the environment of the current process
4. What is the difference between a function and a system call
5. How to create processes
6. What are the three prototypes of main
7. How does the shell use the PATH to find the programs
8. How to execute another program with the execve system call
9. How to suspend the execution of a process until one of its children terminates
10. What is EOF / “end-of-file”?

# Shell Features
Display a prompt and wait for the user to type a command. A command line always ends with a new line.
The prompt is displayed again each time a command has been executed.
The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
The command lines are made only of one word. No arguments will be passed to programs.
If an executable cannot be found, print an error message and display the prompt again.
Handle errors.
You have to handle the “end of file” condition (Ctrl+D)

# Compilation
All the files will be compiled with following:
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

# Authors
Nwachukwu Promise Chizaram and Christianah Olorunda
