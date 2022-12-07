# The Big Race

A simple racing game, written in C & OpenGL.    

> this project is a part of the **Real Time Applications & Embedded Systems (ENCS4330)** course at [BZU](https://www.birzeit.edu).

## Installation

to make the project portable, [Docker](https://www.docker.com) containers were used as a runtime enviroment.

### Prerequisites

* Docker
* VNC client

### Running the project

* windows
    ```bash
    bash windows_setup.sh
    ```
* unix/linux
    ```bash
    bash setup_container.sh
    ```

Then inside the container, run the intended make command.


> Note: to run gui from an ssh session
> 
> ```
> export DISPLAY=:0
> ```

### Make Commands

> run them inside the `src` directory\

Available make commands:

* `make run_gui` - run the standalone gui code with default number of rounds
* `make run_cli <num_of_rounds>` - run the project in cli mode
* `make debug <num_of_rounds>` - run the project in debug mode (inside gdb)

### Debugging in gdb

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
* [ ] create pipes for communication between processes
* [ ] pass pipes to childs and ui
* [ ] create a function that will read the new speeds from the pipes
* [X] let the timer function use the new speeds
* [X] update styling (colors & fonts)
