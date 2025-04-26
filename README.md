# Minishell
42 School Project: Recreating a simple shell

## 📚 Project Overview
Minishell is a simplified UNIX shell project developed as part of the 42 School curriculum.
The goal of the project is to understand how a real shell works under the hood by building a fully functional miniature version from scratch.

This shell handles command execution, built-in commands, environment management, redirections, pipes, signal handling, and basic parsing with quotes and expansions.

## 🗂️ Repository Structure
minishell/
├── readline-master/        # Readline library (for input handling)
├── readline-zkarapet/       # Customized readline version
├── builtins.c               # Built-in command implementations
├── builtins2.c
├── builtins_main.c
├── builtins_utils.c
├── cd.c                     # Handling 'cd' command
├── cmd_lst_construct.c      # Constructing command lists
├── env_lst_adding.c          # Managing environment variable lists
├── env_lst_construct.c
├── environment.c
├── error_utils.c             # Error handling utilities
├── error_utils_for_pars.c
├── exec_sum_up.c             # Summarizing execution logic
├── exit.c                    # Handling 'exit' command
├── expanding.c               # Variable expansion logic
├── expanding_utils.c
├── export.c                  # 'export' built-in
├── export_utils.c
├── file_for_red.c            # Handling redirections
├── filling_with_nulls.c
├── free_utils1.c             # Memory management helpers
├── free_utils2.c
├── frees.c
├── ft_itoa.c                 # Integer to ASCII function
├── git_script.sh             # Git automation script
├── group_until_reds.c        # Grouping commands and redirections
├── group_until_reds_utils.c
├── hdoc_expand.c             # Expanding inside heredocs
├── heredoc.c                 # Heredoc implementation
├── joins.c                   # Joining strings (mainly during parsing)
├── lst_construct.c           # List construction utilities
├── main.c                    # Minishell entry point
├── minishell.h               # Project header file
├── parsing_sum.c             # Parsing flow
├── pipex.c                   # Piping between commands
├── pipex_utils.c
├── quote_checks.c            # Quote parsing checks
├── red_lst_construct.c       # Redirection list construction
├── signal.c                  # Signal handling (Ctrl+C, Ctrl+D)
├── split.c                   # Custom split functions
├── split_utils.c
├── split_utils0.c
├── summerize.c               # Summarize parsed elements
├── utils.c                   # General utilities
├── utils0.c
├── utils1.c
├── Makefile                  # Makefile for compilation
└── README.md                 # (this file)

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

