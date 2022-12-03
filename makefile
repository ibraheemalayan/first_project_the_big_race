# .DEFAULT_GOAL := run

# main_file_name := main.c
# PWD := $(shell pwd)

# build_container:
# 	@echo "Rebuilding container"
# 	docker build . -t vnc_ubutnu_xfce

# run_container: build_container;
# 	@echo "Running container"
# 	docker run -p 25901:5901 --mount type=bind,source="${PWD}/src",target=/src_code/ --rm --name open_gl_dev_env vnc_ubutnu_xfce;

# compile:
# 	@echo "Compiling..."
# 	docker exec -w /src_code open_gl_dev_env gcc ${main_file_name} -lGL -lGLU -lglut -lm -o bin/main


# run: compile;
# 	@echo "Running..."
# 	docker exec -w /src_code open_gl_dev_env ./bin/main

# # docker run -it --mount src=`pwd`,target=/test_container,type=bind k3_s3



    
