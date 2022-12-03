FROM accetto/ubuntu-vnc-xfce-opengl-g3:latest
LABEL Description="Build environment"

USER root

ENV HOME /root

# to include man pages
RUN sed -i 's:^path-exclude=/usr/share/man:#path-exclude=/usr/share/man:' \
        /etc/dpkg/dpkg.cfg.d/excludes

RUN apt update && apt -y --no-install-recommends install \
    build-essential \
    gcc \
    cmake \
    gdb \
    freeglut3-dev \
    man \
    manpages-posix \
    man-db
