# The Big Race

A simple racing game, written in C & OpenGL.    

> this project is a part of the **Real Time Applications & Embedded Systems (ENCS4330)** course at [BZU](https://www.birzeit.edu).

## Installation

to make the project portable, [Docker](https://www.docker.com) containers were used as a runtime enviroment.

### Prerequisites

* Docker


--------------------------------------

to run gui from an ssh session

```
export DISPLAY=:0
```

### Make Commands

> run the followiung commands in src directory

* `make run_cli <num_of_rounds>` - run the project in cli mode
* `make debug <num_of_rounds>` - run the project in debug mode (gdb)

### Debugging in gdb

* to follow child in forks
```
set follow-fork-mode child
```


* to follow exec 
```
set follow-exec-mode new
```