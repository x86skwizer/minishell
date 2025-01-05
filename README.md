# Minishell

This project is a simplified shell implementation inspired by the traditional Unix shell. It supports a subset of typical shell features such as command execution, pipes, redirections, environment variable management, and built-in commands.

---

## Table of Contents

1. [Overview](#overview)  
2. [Features](#features)  
3. [Project Structure](#project-structure)  
4. [Dependencies](#dependencies)  
5. [Installation & Compilation](#installation--compilation)  
6. [Usage](#usage)  
7. [Built-in Commands](#built-in-commands)  
8. [Environment Variables](#environment-variables)  
9. [Signals](#signals)  
10. [Credits](#credits)

---

## Overview

**Minishell** is a project that replicates (in part) the functionality of a real shell. Some features include:

- Parsing user input with support for quotes (`" "` and `' '`)  
- Executing commands and piping output between multiple commands  
- Redirecting input and output (using `>`, `>>`, `<`, `<<`)  
- Managing environment variables (creating, modifying, and removing)  
- Handling signals such as `Ctrl-C` and `Ctrl-\`  
- Built-in commands, including `echo`, `cd`, `pwd`, `env`, `export`, `unset`, and `exit`.

This shell uses the `readline` library (for line editing and command history), and it organizes functions across several modules for parsing, execution, and built-in functionalities.

---

## Features

- **Command execution**: Run external programs found in the system `PATH` or via an absolute/relative path.
- **Built-ins**: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.
- **Pipes**: The `|` character can connect multiple commands, passing the output from one as input to the next.
- **Redirections**: `>`, `>>`, `<`, `<<` (output redirection, append, input redirection, and here-doc).
- **Environment management**: Automatically populated from `envp`; dynamically updated on `export`/`unset`.
- **Signal handling**: Catch `SIGINT` (Ctrl-C) and `SIGQUIT` (Ctrl-\) for interactive editing.
- **History**: Store commands so they can be accessed with the up/down arrow keys (through `readline`).

---

## Project Structure

Below is a condensed summary of the directories and key files:

```
.
├── Makefile
├── main.c
├── merge.h
├── execution
│   ├── builtins
│   │   ├── cd.c
│   │   ├── echo.c
│   │   ├── env.c
│   │   ├── exit.c
│   │   ├── export.c
│   │   ├── export_utils.c
│   │   ├── pwd.c
│   │   └── unset.c
│   ├── end_prog.c
│   ├── execution.c
│   ├── signals.c
│   ├── utils.c
│   ├── utils2.c
│   └── utils
│       ├── env_fill.c
│       ├── get_next_line.c
│       ├── heredoc.c
│       ├── libft_str.c
│       ├── linked_list.c
│       └── search.c
└── parsing
    ├── check_path.c
    ├── expansion.c
    ├── expansion_utils.c
    ├── parsing.c
    ├── parsing_utils.c
    ├── split_arg.c
    ├── utils.c
    ├── utils2.c
    └── utils
        ├── ft_itoa.c
        ├── ft_lstadd_back.c
        ├── ft_lstlast.c
        ├── ft_lstnew.c
        ├── ft_split.c
        ├── ft_strchr.c
        ├── ft_strcmp.c
        ├── ft_strdup.c
        ├── ft_strjoin.c
        ├── ft_strlen.c
        ├── ft_strnstr.c
        └── ft_substr.c
```

**Key modules**:

- **`main.c`**  
  Entry point of the program. Initializes signals, environment, and starts the main loop (prompt).

- **`merge.h`**  
  Central header file with all forward declarations, structs, and global variables (`g_global`).

- **`execution/`**  
  Contains files responsible for executing commands, managing pipes, redirections, signals, and built-in commands.

- **`parsing/`**  
  Handles parsing user input, handling quotes, expansions, splitting into tokens, etc.

- **`Makefile`**  
  Defines compilation rules and targets (`make`, `make clean`, etc.).

---

## Dependencies

- **C compiler** (clang or gcc)  
- **`readline`** library (for command-line editing and history). On some systems, you may need to install development headers, e.g.,

  ```bash
  # On macOS (with Homebrew)
  brew install readline

  # On Ubuntu or Debian
  sudo apt-get install libreadline-dev
  ```

Ensure the linker flags (`-lreadline -L ... -I ...`) are pointed to the correct location if not in a standard path.

---

## Installation & Compilation

1. **Clone or Download** this repository.

2. In the project root directory, run:
   ```bash
   make
   ```
   This will compile all source files and produce the `minishell` executable.

3. **Clean** your build (optional):
   ```bash
   make clean
   ```
   Removes object (`.o`) files.

4. **Full Cleanup** (optional):
   ```bash
   make fclean
   ```
   Removes object files and the `minishell` executable.

5. **Recompile** from scratch (optional):
   ```bash
   make re
   ```

---

## Usage

Once compiled successfully:

```bash
./minishell
```

You will be presented with a prompt:

```
minishell$ 
```

Type your commands just like in a standard Unix shell. Examples:

- `ls -l`  
- `echo "Hello World"`  
- `pwd`  
- `export MYVAR=42 && echo $MYVAR`  
- `unset MYVAR`  
- `cat file1 | grep something > outputfile`  

Use `Ctrl-C` (SIGINT) to interrupt a running process, `Ctrl-D` (EOF) to exit the shell if the line is empty, or type `exit` explicitly.

---

## Built-in Commands

The following built-ins are provided:

1. **cd**  
   Change the current working directory. Usage:
   ```bash
   cd [directory]
   ```
   If no directory is given, it goes to `/`.

2. **echo**  
   Prints arguments to standard output. Recognizes `-n` for no trailing newline.

3. **pwd**  
   Prints the current working directory.

4. **env**  
   Prints the current environment variables that have a value.

5. **export**  
   Sets or updates environment variables.
   ```bash
   export KEY=value
   ```
   If run with no arguments, prints a sorted list of environment variables.

6. **unset**  
   Removes environment variables by name.

7. **exit**  
   Exits the shell with a given exit code (or `0` by default).

---

## Environment Variables

- The shell automatically inherits the parent environment and maintains its own list.
- Commands like `export` and `unset` modify this environment at runtime.
- Use `$VARIABLE` syntax in commands or expansions.

---

## Signals

- **Ctrl-C (SIGINT)**: Interrupts the current process or the prompt input, returning to a new prompt.
- **Ctrl-\ (SIGQUIT)**: By default does nothing in the prompt; in child processes, it can quit the process (like in the real bash).
- **Ctrl-D**: In an empty line, logs out (EOF). If typed mid-line, it sends EOF to stdin.

---

## Credits

Developed by [yamrire](mailto:yamrire@student.42.fr) as part of the 42 school curriculum.  

Feel free to open issues or contribute! Enjoy exploring **Minishell**.