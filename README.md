# Minishell

## Description

This project aims to create a simple shell, similar to `bash` or `zsh`, as part of the 42 curriculum. It involves parsing user input, handling commands, managing processes, and implementing various shell features like pipes, redirections, and environment variable expansion.

## Features

*   Command execution (with arguments)
*   Path handling (`PATH` variable)
*   Environment variable expansion (`$VAR`) and management (`export`, `unset`, `env`)
*   Input/Output redirection (`<`, `>`, `>>`)
*   Here Documents (`<<`)
*   Pipes (`|`)
*   Built-in commands (`cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`)
*   Signal handling (e.g., `Ctrl-C`, `Ctrl-D`, `Ctrl-\`)

## Installation Instructions

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/axellee1994/minishell.git](https://github.com/axellee1994/minishell.git)
    cd minishell
    ```
2.  **Compile the project:**
    ```bash
    make
    ```
    *Requires `libreadline-dev` (or system equivalent).*
    ```bash
    sudo apt-get update && sudo apt-get install libreadline-dev
    ```

## Usage Instructions

1.  **Run the shell:**
    ```bash
    ./minishell
    ```
2.  **Examples:**
    *   **Basic commands:**
        ```bash
        ls -l
        pwd
        echo "Hello, Minishell!"
        ```
    *   **Environment variables:**
        ```bash
        export MY_VAR="test"
        echo $MY_VAR
        env | grep MY_VAR
        unset MY_VAR
        ```
    *   **Navigation:**
        ```bash
        cd ..
        cd /tmp
        ```
    *   **Output Redirection:**
        ```bash
        ls > file_list.txt          # Overwrite
        echo "Add this line" >> file_list.txt # Append
        ```
    *   **Input Redirection:**
        ```bash
        sort < file_list.txt        # Assumes 'sort' is executable via PATH
        ```
    *   **Pipes:**
        ```bash
        cat Makefile | grep FLAGS
        ls -l | wc -l
        ```
    *   **Here Document:**
        ```bash
        cat << END
        This is line 1.
        This is line 2 with $USER variable.
        END
        ```
    *   **Combined:**
        ```bash
        grep ^a < /etc/passwd | sort > sorted_a_users.txt
        ```
    *   **Exiting:**
        ```bash
        exit
        ```

## Contribution Guidelines

We welcome contributions! Please follow these steps:
1.  Fork the repository.
2.  Create a new branch for your feature or bug fix (`git checkout -b feature/your-feature-name`).
3.  Make your changes, adhering to the 42 Norm coding style.
4.  Ensure your code compiles (`make`) and functions as expected.
5.  Commit your changes (`git commit -am 'Add some feature'`).
6.  Push to the branch (`git push origin feature/your-feature-name`).
7.  Create a new Pull Request.

Please ensure your pull request description clearly explains the changes and the problem they solve.

## License Information

This project is licensed under the [Specify License - e.g., MIT License]. See the `LICENSE` file for details (if applicable).

## Contact Information

*   **Author(s):** axellee1994 - [https://github.com/axellee1994](https://github.com/axellee1994)
*   **Project Link:** [https://github.com/axellee1994/minishell](https://github.com/axellee1994/minishell)

For any inquiries or issues, please open an issue on the GitHub repository.
