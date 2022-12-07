
#include "./ui.c"

int team_1_fifo_fd;
int team_2_fifo_fd;

pid_t team_1_first_player_pid;
pid_t team_2_first_player_pid;

struct pipe_message team_1_message;
struct pipe_message team_2_message;

// validate that the UI received the correct arguments:
// - first player pid in team 1
// - first player pid in team 2
// - max score

void game_finished_signal_handler(int s)
{

    printf("Game finished signal received !, will terminate in 60 seconds...\n");
    close_pipes();

    game_finished = 1;

    glutPostRedisplay();
}

void increment_score_signal(int s)
{
    if (s == SIGUSR1)
    {
        score1++;
    }
    else if (s == SIGUSR2)
    {
        score2++;
    }

    team_1_finished_round = 0;
    team_2_finished_round = 0;

    team_1_message.playerPid = -1;
    team_2_message.playerPid = -1;

    team_1_running_direction = RIGHT_DIRECTION;
    team_2_running_direction = RIGHT_DIRECTION;

    sigset(SIGUSR1, increment_score_signal);
    sigset(SIGUSR2, increment_score_signal);
}

void setup_signals()
{
    if (sigset(UISIG, game_finished_signal_handler) == -1) // FIXME keeps emitting a warning
    {
        perror("Sigset can not set the ui signal");
        exit(SIGQUIT);
    }
    if (sigset(SIGUSR1, increment_score_signal) == -1) // FIXME keeps emitting a warning
    {
        perror("Sigset can not set the SIGUSR1 signal");
        exit(SIGQUIT);
    }
    if (sigset(SIGUSR2, increment_score_signal) == -1) // FIXME keeps emitting a warning
    {
        perror("Sigset can not set the SIGUSR2 signal");
        exit(SIGQUIT);
    }
}

void validate_args(int argc, char *argv[])
{

    if (argc < 4)
    {
        errno = EINVAL;
        red_stderr();
        perror("\nMust pass three arguments: team_1_first_player_pid, team_2_first_player_pid, max_score");
        reset_stderr();
        exit(-1);
    }

    if (!(max_score = atoi(argv[3])))
    {
        errno = EINVAL;
        red_stderr();
        perror("\nThe third argument must be an integer, the max score");
        reset_stderr();
        exit(-1);
    };

    team_1_message.playerPid = -1;
    team_2_message.playerPid = -1;
}

void open_pipes()
{
    if ((team_2_fifo_fd = open(TEAM2FIFO, O_RDONLY | O_NONBLOCK)) == -1)
    {
        perror(TEAM2FIFO);
        exit(1);
    }

    if ((team_1_fifo_fd = open(TEAM1FIFO, O_RDONLY | O_NONBLOCK)) == -1)
    {
        perror(TEAM1FIFO);
        exit(1);
    }
}

void close_pipes()
{
    close(team_1_fifo_fd);
    close(team_2_fifo_fd);
}

// reading is a blocking operation so the ui will hang until the player sends a message
int read_team_1_speed()
{
    return read(team_1_fifo_fd, &team_1_message, sizeof(struct pipe_message));
}
int read_team_2_speed()
{
    return read(team_2_fifo_fd, &team_2_message, sizeof(struct pipe_message));
}

void signal_currently_moving_player_team_1()
{
    if (team_1_message.playerPid == -1)
    {
        // printf("team 1 player pid is -1\n");
        return;
    }

    // printf("signaling team 1 player %d, currently_moving_player %d\n", team_1_message.playerPid, currently_moving_player_team_1);
    if (kill(team_1_message.playerPid, UISIG) == -1)
    {
        perror("error sending UISIG to team 1 player");
        exit(1);
    }

    usleep(10000);
}
void signal_currently_moving_player_team_2()
{
    if (team_2_message.playerPid == -1)
    {
        // printf("team 2 player pid is -1\n");
        return;
    }

    // printf("signaling team 2 player %d, currently_moving_player %d\n", team_2_message.playerPid, currently_moving_player_team_2);
    if (kill(team_2_message.playerPid, UISIG) == -1)
    {
        perror("error sending UISIG to team 2 player");
        exit(1);
    }
    usleep(10000);
}

void update_team_1_speed()
{
    if (moving_player_team_1_before_update != currently_moving_player_team_1)
    {

        int speed_update = 0;

        while ((speed_update == 0 || speed_update == -1) && !team_1_finished_round && !game_finished)
        {
            signal_currently_moving_player_team_1(); // send UISIG to the player that is currently moving
            speed_update = read_team_1_speed();
            usleep(30000); // sleep 30ms
        }

        team_1_speed = team_1_message.speed;

        moving_player_team_1_before_update = currently_moving_player_team_1;
    }
}

void update_team_2_speed()
{
    if (moving_player_team_2_before_update != currently_moving_player_team_2)
    {

        int speed_update = 0;

        while ((speed_update == 0 || speed_update == -1) && !team_2_finished_round && !game_finished)
        {
            signal_currently_moving_player_team_2(); // send UISIG to the player that is currently moving
            speed_update = read_team_2_speed();
            usleep(30000); // sleep 30ms
        }

        team_2_speed = team_2_message.speed;

        // printf("team 2 was moving player %d and now moving player %d\n", moving_player_team_2_before_update, currently_moving_player_team_2);

        moving_player_team_2_before_update = currently_moving_player_team_2;
    }
}
