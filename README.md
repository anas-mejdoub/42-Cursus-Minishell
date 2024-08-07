
<div align="center">
  
# MINISHELL
  ![Minishell](https://img.shields.io/badge/Minishell-42-blue)
### let's build a beautiful mini bash like brian fox 

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/3/35/BrianJFox.png/1200px-BrianJFox.png" alt="Brian Fox" width="300"/>

</div>


## Table of Contents

- [Authors](#Authors)
- [Introduction](#Introduction)
- [features](#features)
- [Installation](#Installation)
- [Usage](#Usage)
- [Contributing](#Contributing)


## Authors

- [nourddine benyahya](https://github.com/nourddine-benyahya) [(42 profile)](https://profile.intra.42.fr/users/nbenyahy)
- [anas-mejdoub](https://github.com/anas-mejdoub) [(42 profile)](https://profile.intra.42.fr/users/amejdoub)

## Introduction

Minishell is a simple shell implementation project for 42 School. The goal of this project is to create a small, yet functional shell that can execute commands, manage processes, and handle basic shell functionalities.

## features

This project recreates a basic shell with essential functionalities, including:

* **Command parsing and execution**
* **Built-in commands** (e.g., cd, echo, exit, env, export, unset, pwd)
* **subshell** (e.g., (command1 | (command2)))
* **AND / OR** (e.g., command1 || command2, command1 && command2)
* **Process management** (fork, exec, wait)
* **Input/output redirection** (>, <, >>)
* **woldcacrd** (command *)
* **Pipes** (command1 | command2)
* **Signal handling** (Ctrl+C, Ctrl+D, Ctrl+\)
* **here doc** (<< lim)
* **Error handling** (syntax error, ambiguous error)


## Installation

To install Minishell, follow these steps:

1. Clone the repository:
    ```sh
    git clone https://github.com/1337-Med/42-Cursus-Minishell
    ```

2. Navigate to the project directory:
    ```sh
    cd minishell
    ```

3. Compile the source code:
    ```sh
    make
    ```

## Usage

To run Minishell, execute the following command in the project directory:

```sh
./minishell
```
then enjoy with out beautiful bash :)

Once running, you can enter commands just like you would in a regular Unix shell.

## Contributing

Contributions are welcome! Please follow these steps to contribute:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature/YourFeature`).
3. Commit your changes (`git commit -m 'Add some feature'`).
4. Push to the branch (`git push origin feature/YourFeature`).
5. Open a pull request.


![image](https://github.com/user-attachments/assets/45c358cd-d6b8-42fd-818c-72893bbba1f4)
