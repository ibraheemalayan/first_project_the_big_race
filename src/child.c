#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#include "./std.h"

pid_t next_player_pid;

int speed;
int distance = 100;
// #define foo4random() (arc4random() % ((unsigned)RAND_MAX + 1))

void validate_args(int argc, char *argv[])
{

    if (argc < 2)
    {
        errno = EINVAL;
        red_stderr();
        perror("\nMissing the pid of next child argument");
        reset_stderr();
        exit(-1);
    }

    if (!(next_player_pid = atoi(argv[1])))
    {
        errno = EINVAL;
        red_stderr();
        perror("\nThe first argument must be the pid of next player");
        reset_stderr();
        exit(-1);
    };
}

int main(int argc, char *argv[])
{

    validate_args(argc, argv);

    srand(time(NULL) ^ (getpid() << 16));

    speed = rand() % 10 + 5;

    magenta_stdout();

    printf("\nChild Process Generated Speed (%d) and has argument %d and pid : %d and parent id : %d\n", speed, next_player_pid, getpid(), getppid());

    reset_stdout();

    return (0);
}
