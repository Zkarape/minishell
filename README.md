# Minishell
42 School Project: Recreating a simple shell

## 📚 Project Overview
Minishell is a simplified UNIX shell project developed as part of the 42 School curriculum.
The goal of the project is to understand how a real shell works under the hood by building a fully functional miniature version from scratch.

This shell handles command execution, built-in commands, environment management, redirections, pipes, signal handling, and basic parsing with quotes and expansions.


## ✨ Features
Prompt display and input handling

Execute system commands (via execve)

Built-in commands:

cd

pwd

echo

exit

export

unset

env

Environment variable handling

Pipes (|) between commands

Redirections:

Output redirection >

Output appending >>

Input redirection <

Heredoc <<

Quote parsing (', ")

Variable expansion ($VAR_NAME)

Signal handling (Ctrl+C, Ctrl+D, etc.)

Memory management to avoid leaks (tested with valgrind)

⚙️ How to Compile and Run
bash
make
./minishell

## 📋 Requirements
OS: Linux / macOS

Compiler: clang or gcc

Libraries: readline

Make sure you have readline installed:

bash
sudo apt-get install libreadline-dev
or on macOS:

bash

## 🧹 Coding Standards
Follows the 42 Norminette rules

No memory leaks

Proper use of error handling

Clear separation of concerns across files

## ⚠️ Known Issues
Parsing very complex nested quotes may cause unexpected behavior

Some edge cases for heredocs are simplified compared to a real bash

Ctrl+C during heredoc may behave slightly differently from bash

## ✍️ Authors
Zkarape

Project developed at [42 Yerevan / 42 Network]

## 🏆 Acknowledgements
42 School and its community

GNU readline documentation

Bash manual pages

## 📜 License
This project is for educational purposes only under the 42 Network guidelines.

