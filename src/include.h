
/*
 * local header file for pipe client-server
 */

#ifndef __INCLUDE_H_
#define __INCLUDE_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <errno.h>

#define PLAYERS_PER_TEAM 5
#define DEFAULT_MAX_SCORE 5

#define TEAM1FIFO "/tmp/TEAM1FIFO"
#define TEAM2FIFO "/tmp/TEAM2FIFO"

#define UISIG 7

struct pipe_message
{
  int playerPid;
  float speed;
};

#endif
