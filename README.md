
# Minishell

## Project Overview

Minishell is a project focused on building a simple shell, offering a practical understanding of process management, file descriptors, and command-line parsing. It is a minimalist version of `bash`.

The core of the project involves implementing a shell that can:
*   Display an interactive prompt and maintain a command history.
*   Execute commands using the `PATH` variable or relative/absolute paths.
*   Handle I/O redirections (`<`, `>`, `>>`) and here-documents (`<<`).
*   Implement pipes (`|`) to chain commands.
*   Expand environment variables, including the exit status (`$?`).
*   Correctly interpret single (`'`) and double (`"`) quotes to manage metacharacters.
*   Handle `ctrl-C`, `ctrl-D`, and `ctrl-\` signals appropriately.
*   Include essential built-in commands: `echo` (with `-n` option), `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.

For an additional challenge, the bonus part includes advanced features:
*   Logical operators (`&&` and `||`) for conditional execution.
*   Parentheses `()` to group commands and establish priority.
*   The `*` wildcard for filename expansion in the current directory.

## Getting Started

Follow these instructions to get a copy of the project up and running on your local machine.

### Prerequisites

You will need `make` and a C compiler like `gcc` installed on your system to build the project.

### Installation and Execution

1.  **Clone the repository:**
    ```sh
    git clone https://github.com/your-username/minishell.git
    ```

2.  **Navigate to the project directory:**
    ```sh
    cd minishell
    ```

3.  **Compile the project:**
    Run the `Makefile` provided in the root directory. This will compile the source files and generate an executable file named `minishell`.
    ```sh
    make
    ```

4.  **Run the shell:**
    Execute the program by typing `./minishell`.
    ```sh
    ./minishell
    ```

## Usage

Once you run the executable, you will be greeted with the `minishell>` prompt. From here, you can run commands just like you would in a standard bash terminal.

**Examples:**

```sh
minishell> ls -l
minishell> echo "Hello, World!" > greeting.txt
minishell> cat greeting.txt
minishell> cat greeting.txt | wc -c
minishell> exit

Generated code
IGNORE_WHEN_COPYING_START
content_copy
download
Use code with caution.
IGNORE_WHEN_COPYING_END
