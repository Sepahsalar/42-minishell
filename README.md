# 42-minishell
A minimal shell implementation built for the `42` curriculum, providing basic Unix shell functionalities with custom command handling and process management. This project is built in `C`, focusing on replicating core behaviors of a typical Unix shell and enhancing understanding of process management, I/O handling, and system calls.

This project is developed collaboratively by [Alireza Sohrabizadeh](https://github.com/Sepahsalar) and [Nima Nourinejad](https://github.com/nima-nourinejad).

</br>

# Content

1. [Usage](#usage)
2. [Description](#description)
3. [Algorithm](#algorithm)
4. [Features](#features)
5. [Supported Commands](#supported-commands)

</br>

## Usage

To build and run the project, clone the repository and compile it:

```bash
git clone https://github.com/Sepahsalar/42-minishell.git
cd 42-minishell
make
```

After building, start the shell by running:

```bash
./minishell
```

You can exit the shell with the `exit` command.



## Description

Minishell is a simple command-line interpreter that mimics the behavior of Unix shells. It was developed as a project for the `42` school curriculum to strengthen skills in process management, memory handling, and Unix system calls. The shell processes user input, executes commands, and supports features like redirection, piping, and signal handling, all while managing custom environment variables and built-in commands.



## Algorithm

The core algorithm for Minishell can be broken down into several key steps:

1. **Initialize Environment**: Load environment variables and set up essential data structures.
2. **Read Input**: Continuously prompt the user for input, handling signals like `Ctrl+C` and `Ctrl+D`.
3. **Parse Input**: Tokenize the input string to identify commands, arguments, redirections, and pipes.
4. **Command Execution**:
- **Built-in Command Check**: Determine if the command is built-in (e.g., `cd`, `echo`, `exit`). If so, execute directly.
- **External Command Execution**: For external commands, `fork` a child process and use `execve()` to execute the command.
5. **Redirection and Piping**: Handle I/O redirections and set up `pipe`s to chain commands.
6. **Cleanup**: Free allocated memory and reset states after each command.
7. **Exit**: Terminate gracefully on `exit` command or `Ctrl+D`.



## Features

- **Command Parsing**: Supports input parsing to identify commands and arguments.
- **Execution**: Runs executables located in system paths.
- **Pipes and Redirection**: Implements piping between commands and basic redirection.
- **Built-in Commands**: Includes several custom built-in commands (e.g., `cd`, `echo`, `exit`, etc.).
- **Environment Variables**: Supports accessing and modifying environment variables.
- **Signal Handling**: Gracefully handles `Ctrl+C` and `Ctrl+D` signals.



## Supported Commands

Minishell supports both built-in commands and external commands found in your system’s `PATH`.

**Built-in Commands**

- `cd`: Change the directory.
- `echo`: Display a line of text.
- `exit`: Exit the shell.
- `env`: Print environment variables.
- `export`: Set an environment variable.
- `unset`: Remove an environment variable.
