.DEFAULT_GOAL := run_cli

# use the rest as arguments for "run"
RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
# ...and turn them into do-nothing targets
$(eval $(RUN_ARGS):;@:)

PWD := $(shell pwd)

# Standalone GUI
compile_gui:
	@echo "Compiling..."
	gcc ui/standalone_ui.c -lGL -lGLU -lglut -lm -o bin/standalone_gui


run_gui: compile_gui;
	@echo "Running GUI..."
	$(shell export DISPLAY=:0)
	./bin/standalone_gui

# Debug Standalone GUI
compile_gui_debug:
	@echo "Compiling..."
	gcc ui/standalone_ui.c -g -lGL -lGLU -lglut -lm -o bin/standalone_gui


debug_gui: compile_gui_debug;
	@echo "Running GUI..."
	$(shell export DISPLAY=:0)
	gdb ./bin/standalone_gui

# StandAlone CLI
compile_cli:
	@echo "Compiling..."
	gcc cli/standalone_parent.c -lm -o bin/standalone_parent
	gcc cli/standalone_child.c -lm -o bin/standalone_child


run_cli: compile_cli;
	@echo "Running CLI..."
	./bin/standalone_parent $(RUN_ARGS)

# Debug StandAlone CLI
debug_compile_cli:
	@echo "Compiling CLI with -g ..."
	gcc cli/standalone_parent.c -lm -g -o bin/standalone_parent
	gcc cli/standalone_child.c -lm -g -o bin/standalone_child

debug_cli: debug_compile_cli;
	@echo "Running GDB..."
	gdb --args ./bin/standalone_parent $(RUN_ARGS)

# Compile all
compile:
	@echo "Compiling..."
	gcc ui/attached_ui.c -lGL -lGLU -lglut -lm -o bin/attached_gui
	gcc cli/attached_parent.c -lm -o bin/attached_parent
	gcc cli/attached_child.c -lm -o bin/attached_child

run: compile;
	@echo "Running..."
	$(shell export DISPLAY=:0)
	./bin/attached_parent $(RUN_ARGS)


# Compile all
compile_debug_all:
	@echo "Compiling for debug..."
	gcc ui/attached_ui.c -lGL -lGLU -g -lglut -lm -o bin/attached_gui
	gcc cli/attached_parent.c -lm -g -o bin/attached_parent
	gcc cli/attached_child.c -lm -g -o bin/attached_child

debug: compile_debug_all;
	@echo "Debugging All..."
	$(shell export DISPLAY=:0)
	gdb --args ./bin/attached_parent $(RUN_ARGS)