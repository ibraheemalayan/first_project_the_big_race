FROM accetto/ubuntu-vnc-xfce-opengl-g3:latest
LABEL Description="Build environment"

USER root

ENV HOME /root

RUN apt update && apt -y --no-install-recommends install \
    build-essential \
    gcc \
    cmake \
    gdb \
    freeglut3-dev