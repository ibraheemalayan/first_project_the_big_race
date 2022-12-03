#! /bin/bash   

set -m

BLACK=$(tput setaf 0)
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
YELLOW=$(tput setaf 3)
LIME_YELLOW=$(tput setaf 190)
POWDER_BLUE=$(tput setaf 153)
BLUE=$(tput setaf 4)
MAGENTA=$(tput setaf 5)
CYAN=$(tput setaf 6)
WHITE=$(tput setaf 7)
BRIGHT=$(tput bold)
NORMAL=$(tput sgr0)
BLINK=$(tput blink)
REVERSE=$(tput smso)
UNDERLINE=$(tput smul)

# This script is used to setup & run the container

printf "⏱️${YELLOW}\n⏱️ Building the image...${NORMAL}"

docker build . -t vnc_ubutnu_xfce

printf "${YELLOW}\n⏱️ Killing previouse container if exists...\n\n${NORMAL}"

docker kill open_gl_dev_env 2> /dev/null
docker container rm open_gl_dev_env 2> /dev/null

printf "${YELLOW}\n⏱️ Running the container...${NORMAL}\n\n"

docker run -p 25901:5901 --mount type=bind,source="${PWD}/src",target=/src_code/ -d --rm -e "TERM=xterm-256color" --name open_gl_dev_env vnc_ubutnu_xfce;

CONTAINER_IP=`docker inspect open_gl_dev_env | grep "                    \"IPAddress\":" | cut -d \" -f 4`

printf "\n✅ ${MAGENTA}The container is running with IP: $CONTAINER_IP, and the VNC port ( 5901 ) is mapped to the host port ( 25901 )\n\n"
printf "${MAGENTA}You can connect on the following address (${RED}or paste in your browser${MAGENTA})${GREEN}\n\n👉\tvnc://localhost:25901?VncPassword=headless\n${NORMAL}\n\n"

printf "${CYAN}Running an interactive shell...${NORMAL}\n\n"

docker exec open_gl_dev_env bash -c "echo 'export \"PS1=\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ \"' >> ~/.bashrc"

docker exec -it -w /src_code open_gl_dev_env bash

