

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include "./std.h"

#define PLAYERS_PER_TEAM 5

int rounds;
int current_round = 0;

int current_round_result = 0;

int team_1_score = 0, team_2_score = 0;

void signal_catcher(int the_sig);

// green team from 0-4 , red team 5-9
pid_t players_pids[PLAYERS_PER_TEAM * 2];

void validate_args(int argc, char *argv[])
{

    if (argc < 2)
    {
        errno = EINVAL;
        red_stderr();
        perror("\nMissing the number of childs argument");
        reset_stderr();
        exit(-1);
    }

    if (!(rounds = atoi(argv[1])))
    {
        errno = EINVAL;
        red_stderr();
        perror("\nThe first argument must be an integer");
        reset_stderr();
        exit(-1);
    };
}

int main(int argc, char *argv[])
{

    srand(time(NULL)); // Initialization, should only be called once.

    validate_args(argc, argv);

    int status, i = PLAYERS_PER_TEAM * 2 - 1;

    green_stdout();
    printf("\n\n\n\nParent process ID is %d\n", getpid());

    // set to zero for the last child [means send signal to parent on finish]
    char next_player_pid_arg[8];
    sprintf(next_player_pid_arg, "-1");

    char team_arg[3];
    sprintf(team_arg, "2");

    magenta_stdout();
    fflush(stdout);

    for (; i > -1; i--)
    {
        pid_t current_fork_pid;

        if ((current_fork_pid = fork()) == -1)
        {
            perror("fork failure ... getting out\n");
            // TODO kill other children
            exit(-1);
        }

        if (current_fork_pid == 0)
        {
            // execute child with next player pid as argument
            execlp("./bin/child", "child", next_player_pid_arg, team_arg, (char *)NULL);
            perror("exec failure ");
            exit(-2);
        }
        else
        {
            // parent
            players_pids[i] = current_fork_pid;
            if (i == 5)
            {
                printf("Switching to team 1");
                sprintf(next_player_pid_arg, "-1");
                sprintf(team_arg, "1");
            }
            else
            {
                sprintf(next_player_pid_arg, "%d", current_fork_pid);
            }
        }

        // breakpoint here
    }

    reset_stdout();
    fflush(stdout);

    if (sigset(SIGUSR1, signal_catcher) == -1) // FIXME keeps emitting a warning
    {
        perror("Sigset can not set SIGUSR1 catcher");
        exit(SIGQUIT);
    }

    if (sigset(SIGUSR2, signal_catcher) == -1) // FIXME keeps emitting a warning
    {
        perror("Sigset can not set SIGUSR2 catcher");
        exit(SIGQUIT);
    }

    for (current_round = 0; current_round < rounds;)
    {
        green_stdout();
        run_round(current_round);
    }

    for (i = 0; i < PLAYERS_PER_TEAM * 2; i++)
    {
        pid_t c_id = wait(&status);
        printf("\nchild with id %d has exited with status %d\n", c_id, status);
        fflush(stdout);
        sleep(1);
    }

    return (0);
}

void signal_catcher(int the_sig)
{

    // SIGUSR1 will be used by team 1
    // SIGUSR2 will be used by team 2

    if (current_round_result == 1)
    {
        current_round_result++;
        if (the_sig == SIGUSR1)
        {
            printf("\n\n!!! Team 1 has lost this round !!!\n\n");
            current_round_result = 2;
            current_round++;
            return;
        }
        else if (the_sig == SIGUSR2)
        {
            printf("\n\n!!! Team 2 has lost this round !!!\n\n");
            current_round_result = 2;
            current_round++;
            return;
        }
        exit(-1);
    }

    if (the_sig == SIGUSR1)
    {
        team_1_score++;
        printf("\n\n!!! Team 1 has won this round !!!\n\n");
        current_round_result = 1;
        return;
    }
    else if (the_sig == SIGUSR2)
    {
        team_2_score++;
        printf("\n\n!!! Team 2 has won this round !!!\n\n");
        current_round_result = 1;
        return;
    }

    exit(1);
}

void run_round(running_round)
{

    // SIGCLD is used to start next round

    green_stdout();
    printf("\n\n> Round #%d out of #%d will start in 3 second ...\n\n", current_round + 1, rounds);
    reset_stdout();

    sleep(3);

    current_round_result = 0;

    kill(players_pids[0], SIGUSR1);
    kill(players_pids[5], SIGUSR2);

    printf("\n\nWaiting for round #%d to finish ...\n\n", current_round + 1);

    // wait for current round to finish ( finishes when both teams have finished )
    while (running_round == current_round)
    {
        pause(); // this will return after a signal handler returns
    }

    printf("\n\nRound #%d finished and current scores are\n\tteam green - %d\n\t team red - %d\n\n", current_round + 1, team_1_score, team_2_score);
}