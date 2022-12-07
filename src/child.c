
#include "./std.h"
#include "./include.h"

pid_t next_player_pid;
int team_num;
int team_signal;
int speed;
int player_index;
int distance = 25;

char team_fifo[20];
int team_fifo_fd;

int fifoTeamOne, fifoTeamTwo;

typedef void (*sighandler_t)(int);

sighandler_t sigset(int sig, sighandler_t disp);

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

    return (0);
}

void handle_ui_signal(int the_sig)
{
    // used to allow the ui to send a signal to the player without killing him
}

void start_signal_catcher(int the_sig)
{

    int start_point = player_index;
    int end_point = (player_index) % 5 + 1;

    if (the_sig == team_signal)
    {
        speed = rand() % 20 + 5;
        printf("\n> %d: player %d in team %d has started running with speed %d from A%d to A%d \n", getpid(), player_index, team_num, speed, start_point, end_point);

        // TODO write pid and speed and index to team pipe
        // then pause and wait for ui signal (which is the signal of the second team)

        sleep(distance / speed);

        struct pipe_message msg;

        msg.playerPid = getpid();
        msg.speed = speed;

        /* Open the public FIFO for reading and writing */
        if ((team_fifo_fd = open(team_fifo, O_WRONLY)) == -1)
        {
            perror(team_fifo);
            exit(1);
        }

        // write the speed and pid to the team fifo
        // - speed is used by the ui to render the speed
        // - the pid is passed to allow the ui to tell the player when he reaches his destination
        write(team_fifo_fd, &msg, sizeof(msg));

        pause(); // wait for a signal from the ui

        send_signal_to_next_player();

        return;
    }

    // re set signal handler because it gets removed in some unix systems after the call
    // if (sigset(team_signal, start_signal_catcher) == -1) // FIXME keeps emitting a warning
    // {
    //     perror("Sigset can not reset team signal");
    //     exit(SIGQUIT);
    // }

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