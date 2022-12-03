.DEFAULT_GOAL := run_cli

main_gui_file_name := main.c
main_cli_file_name := app.c

PWD := $(shell pwd)

compile_gui:
	@echo "Compiling..."
	gcc ${main_gui_file_name} -lGL -lGLU -lglut -lm -o bin/main_gui


run_gui: compile_gui;
	@echo "Running GUI..."
	./bin/main_gui

compile_cli:
	@echo "Compiling..."
	gcc ${main_cli_file_name} -lm -o bin/main_cli


run_cli: compile_cli;
	@echo "Running CLI..."
	./bin/main_cli


    
