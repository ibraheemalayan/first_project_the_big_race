.DEFAULT_GOAL := run_cli

main_gui_file_name := main.c
child_cli_file_name := child.c
main_cli_file_name := parent.c

# use the rest as arguments for "run"
RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
# ...and turn them into do-nothing targets
$(eval $(RUN_ARGS):;@:)

PWD := $(shell pwd)

compile_gui:
	@echo "Compiling..."
	gcc ${main_gui_file_name} -lGL -lGLU -lglut -lm -o bin/main_gui


run_gui: compile_gui;
	@echo "Running GUI..."
	$(shell export DISPLAY=:0)
	./bin/main_gui $(RUN_ARGS)

compile_cli:
	@echo "Compiling..."
	gcc ${main_cli_file_name} -lm -o bin/main_cli
	gcc ${child_cli_file_name} -lm -o bin/child


run_cli: compile_cli;
	@echo "Running CLI..."
	./bin/main_cli $(RUN_ARGS)

debug_compile_cli:
	@echo "Compiling CLI with -g ..."
	gcc ${main_cli_file_name} -g -lGL -lGLU -lglut -lm -o bin/main_cli
	gcc ${child_cli_file_name} -g -lm -o bin/child

debug: debug_compile_cli;
	@echo "Running GDB..."
	gdb --args ./bin/main_cli $(RUN_ARGS)
    
