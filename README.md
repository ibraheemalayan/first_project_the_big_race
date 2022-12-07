# The Big Race

A simple racing simulation, written in C & OpenGL. 

> this project is a part of the **Real Time Applications & Embedded Systems (ENCS4330)** course at [BZU](https://www.birzeit.edu).

## Installation

to make the project portable, [Docker](https://www.docker.com) containers were used as a runtime enviroment.

### Prerequisites

* Docker
* VNC client

### Running the project

1. setup the container
    * windows
        ```bash
        bash windows_setup.sh
        ```
    * unix/linux
        ```bash
        bash setup_container.sh
        ```
2. connect the VNC client to the url shown in the output od the setup script (password is `headless`)


3. inside the container shell, run the intended make command.


> Note: before running the gui from an ssh session
> 
> ```
> export DISPLAY=:0
> ```

### Available Make Commands

> makeFile is inside the `src` directory

Available make commands:

* `make run <num_of_rounds>` - run the project in gui mode
* `make run_gui` - run the standalone gui code with default number of rounds and random speeds **(for testing)**
* `make run_cli <num_of_rounds>` - run the project in cli mode without gui **(for testing)**

Debugging (GDB)

* `make debug <num_of_rounds>` - run the project inside gdb
* `make debug_cli <num_of_rounds>` - run the project in cli mode without gui inside gdb **(for testing)**
* `make debug_gui` - run the project in gui mode inside gdb **(for testing)**


> there other make commands, but they are not intended to be used directly.

#### Debugging in gdb

* to follow child in forks
```
set follow-fork-mode child
```


* to follow exec 
```
set follow-exec-mode new
```


### TODOs

* [X] solve ui issue in ubuntu
* [X] draw all players as different objects
* [X] create pipes for communication between processes
* [X] pass pipes to childs and ui
* [X] create a function that will read the new speeds from the pipes instead of random
* [X] let the timer function use the new speeds
* [X] update styling (colors & fonts)
* [X] document make available commands
* [ ] add contributors names/ids
* [ ] add a demo GIF in this README



