
#include "../include.h"
#include "../std.h"

pid_t next_player_pid;
struct pipe_message msg;

int team_num;
int team_signal;
float speed;
int sent_signal_this_round = 0;
int player_index;
int distance = 25;

char team_fifo[20];
int team_fifo_fd;

int fifoTeamOne, fifoTeamTwo;

typedef void (*sighandler_t)(int);

sighandler_t sigset(int sig, sighandler_t disp);

void handle_start();
void handle_ui_signal(int the_sig);

#define init_random() (srand(time(NULL) ^ (getpid() << 16)))

void send_signal_to_next_player();
void start_signal_catcher(int the_sig);

void validate_args(int argc, char *argv[])
{

    if (argc < 4)
    {
        errno = EINVAL;
        red_stderr();
        perror("\nMust pass three arguments: pid of next player, team number, index of player");
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

    if (!(player_index = atoi(argv[3])) || player_index > 9 || player_index < 0)
    {
        errno = EINVAL;
        red_stdout();
        printf("\nThe third argument must be the player number in the team which can be between 1 and 10, not %s", argv[3]);
        fflush(stdout);
        reset_stdout();
        exit(-1);
    };

    team_signal = (team_num == 1) ? SIGUSR1 : SIGUSR2;
    strcpy(team_fifo, (team_num == 1) ? TEAM1FIFO : TEAM2FIFO);
}

int main(int argc, char *argv[])
{

    validate_args(argc, argv);

    init_random();

    if (sigset(team_signal, start_signal_catcher) == -1) // FIXME keeps emitting a warning
    {
        perror("Sigset can not set team signal");
        exit(SIGQUIT);
    }
    if (sigset(UISIG, handle_ui_signal) == -1) // FIXME keeps emitting a warning
    {
        perror("Sigset can not set the ui signal");
        exit(SIGQUIT);
    }

    while (1)
    {
        pause(); // wait for a signal
    }
    printf("\n\n\nA Player Died !!!!!! \n\n\n");
    fflush(stdout);

    return (0);
}

void start_signal_catcher(int the_sig)
{

    if (the_sig == team_signal)
    {

        sent_signal_this_round = 0;

        handle_start();

        return;
    }

    // re set signal handler because it gets removed in some unix systems after the call
    // if (sigset(team_signal, start_signal_catcher) == -1) // FIXME keeps emitting a warning
    // {
    //     perror("Sigset can not reset team signal");
    //     exit(SIGQUIT);
    // }

    printf("\n\n\nA Player Died !!!!!! \n\n\n");
    fflush(stdout);
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

    sent_signal_this_round = 1;
}