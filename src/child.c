#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <errno.h>

#include "./std.h"

pid_t next_player_pid;
int team_num;
int team_signal;
int speed;
int distance = 25;

typedef void (*sighandler_t)(int);

sighandler_t sigset(int sig, sighandler_t disp);

#define init_random() (srand(time(NULL) ^ (getpid() << 16)))

void send_signal_to_next_player();
void start_signal_catcher(int the_sig);

void validate_args(int argc, char *argv[])
{

    if (argc < 3)
    {
        errno = EINVAL;
        red_stderr();
        perror("\nMust pass two arguments: pid of next player, team number");
        reset_stderr();
        exit(-1);
    }

    // the first argument is -1 if last child
    if (!(next_player_pid = atoi(argv[1])))
    {
        errno = EINVAL;
        red_stdout();
        printf("\nThe first argument must be the pid of next player, instead of %s", argv[1]);
        fflush(stdout);
        reset_stdout();
        exit(-1);
    };

    if (!(team_num = atoi(argv[2])) || (team_num != 1 && team_num != 2))
    {
        errno = EINVAL;
        red_stdout();
        printf("\nThe second argument must be the team number which can be only 1 or 2 instead of %s", argv[2]);
        fflush(stdout);
        reset_stdout();
        exit(-1);
    };

    team_signal = (team_num == 1) ? SIGUSR1 : SIGUSR2;
}

int main(int argc, char *argv[])
{

    validate_args(argc, argv);

    init_random();

    speed = rand() % 15 + 5;

    if (sigset(team_signal, start_signal_catcher) == -1) // FIXME keeps emitting a warning
    {
        perror("Sigset can not set team signal");
        exit(SIGQUIT);
    }

    printf("\n%d: Child generated with speed=%d, next_player_pid=%d, team=%d", getpid(), speed, next_player_pid, team_num);
    fflush(stdout);

    while (1)
    {
        pause(); // wait for a signal
    }

    return (0);
}

void start_signal_catcher(int the_sig)
{

    // SIGUSR1 will be used for start
    // SIGUSR2 will be used for reset

    printf("\nStart signal for pid %d in team %d was received.\n", getpid(), team_num);

    if (the_sig == team_signal)
    {
        sleep(distance / speed);
        send_signal_to_next_player();
    }

    exit(1);
}

void send_signal_to_next_player()
{

    if (next_player_pid != -1)
    {
        kill(next_player_pid, team_signal); // send team signal to next player
    }
    else
    {
        kill(getppid(), team_signal); // send team signal to parent
    }
}