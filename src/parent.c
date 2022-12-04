

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
#define DEFAULT_MAX_SCORE 5

int max_score;
int current_round = 0;

int current_round_result = 0;

int team_1_score = 0, team_2_score = 0;

void signal_catcher(int the_sig);

// green team from 0-4 , red team 5-9
pid_t players_pids[PLAYERS_PER_TEAM * 2];

void validate_args(int argc, char *argv[])
{

    if (argc >= 2)
    {
        if (!(max_score = atoi(argv[1])))
        {
            errno = EINVAL;
            red_stderr();
            perror("\nThe first argument must be an integer");
            reset_stderr();
            exit(-1);
        };
    }
    else
    {
        max_score = DEFAULT_MAX_SCORE;
    }
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

    char player_index_arg[3];
    sprintf(player_index_arg, "5");

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
            execlp("./bin/child", "child", next_player_pid_arg, team_arg, player_index_arg, (char *)NULL);
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
                sprintf(player_index_arg, "%d", i);
            }
            else
            {
                sprintf(next_player_pid_arg, "%d", current_fork_pid);
                sprintf(player_index_arg, "%d", i);
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

    int current_bigger_score = 0;

    current_round = 0;

    do
    {
        current_bigger_score = get_max_score();
        green_stdout();
        run_round(current_round);

    } while (current_bigger_score < max_score - 1);

    // kill all children
    for (i = 0; i < PLAYERS_PER_TEAM * 2; i++)
    {
        kill(players_pids[i], SIGQUIT);
    }

    return (0);
}

void signal_catcher(int the_sig)
{

    // SIGUSR1 will be used by team 1
    // SIGUSR2 will be used by team 2

    if (current_round_result == 1)
    {
        if (the_sig == SIGUSR1)
        {
            red_stdout();
            printf("\nLast player of team 1 has arrived to A1, they've lost the round\n");
            reset_stdout();
            current_round++;
            return;
        }
        else if (the_sig == SIGUSR2)
        {
            red_stdout();
            printf("\nLast player of team 2 has arrived to A1, they've lost the round\n");
            reset_stdout();
            current_round++;
            return;
        }
        exit(-1);
    }

    if (the_sig == SIGUSR1)
    {
        team_1_score++;
        green_stdout();
        printf("\nLast player of team 1 has arrived to A1, they've won the round !\n");
        reset_stdout();
        current_round_result = 1;
        return;
    }
    else if (the_sig == SIGUSR2)
    {
        team_2_score++;
        green_stdout();
        printf("\nLast player of team 2 has arrived to A1, they've won the round !\n");
        reset_stdout();
        current_round_result = 1;
        return;
    }

    exit(1);
}

void run_round(running_round)
{

    // SIGCLD is used to start next round

    green_stdout();
    printf("\n\n> Round #%d will start in 1 second ...\n\n", current_round + 1);
    reset_stdout();

    sleep(1);

    current_round_result = 0;

    if (kill(players_pids[0], SIGUSR1) == -1)
    {
        perror("Can not send SIGUSR1 to team 1");
        exit(-1);
    }

    if (kill(players_pids[5], SIGUSR2) == -1)
    {
        perror("Can not send SIGUSR2 to team 2");
        exit(-1);
    }

    printf("\n\nWaiting for round #%d to finish ...\n\n", current_round + 1);

    // wait for current round to finish ( finishes when both teams have finished )
    do
    {
        pause(); // this will return after a signal handler returns
        fflush(stdout);
    } while (running_round == current_round);

    magenta_stdout();
    printf("\n\nRound #%d finished and current scores are\n\tteam green - %d\n\tteam red - %d\n\n", current_round, team_1_score, team_2_score);
    reset_stdout();
}

int get_max_score()
{
    return team_1_score > team_2_score ? team_1_score : team_2_score;
}