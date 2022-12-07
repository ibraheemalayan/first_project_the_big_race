#include "./child.c"

float randomeSpeed()
{

    float MaxSpeedPerFrame = MAX_SPEED_PER_FRAM - MAX_SPEED_PER_FRAM / 3; // max speed
    // algorithm for creating a random number
    //(float cast) (float cast)	(RAND_MAX) is a costant included in the lib time.h
    float speed = ((float)rand() / (float)(RAND_MAX)) * MaxSpeedPerFrame;
    return speed + MAX_SPEED_PER_FRAM / 3;
}

void handle_ui_signal(int the_sig)
{
    if (sigset(UISIG, handle_ui_signal) == -1) // FIXME keeps emitting a warning
    {
        perror("Sigset can not set the ui signal");
        printf("\n\n\nA Player Died !!!!!! \n\n\n");
        fflush(stdout);
        exit(SIGQUIT);
    }

    send_signal_to_next_player();
}

void handle_start()
{

    msg.playerPid = getpid();

    speed = randomeSpeed();

    msg.speed = speed;

    /* Open the public FIFO for reading and writing */
    if ((team_fifo_fd = open(team_fifo, O_WRONLY | O_NONBLOCK)) == -1)
    {
        perror(team_fifo);
        printf("\n\n\nA Player Died !!!!!! \n\n\n");
        fflush(stdout);
        exit(1);
    }

    // write the speed and pid to the team fifo
    // - speed is used by the ui to render the speed
    // - the pid is passed to allow the ui to tell the player when he reaches his destination
    int wrote_bytes = write(team_fifo_fd, &msg, sizeof(msg));
    if (wrote_bytes == -1)
    {
        perror("write error");
        printf("\n\n\nA Player Died !!!!!! \n\n\n");
        fflush(stdout);
        exit(1);
    }

    close(team_fifo_fd);
}