#include "./parent.c"

char child_binary_path[50] = "./bin/attached_child";

int get_if_attached()
{
    return 1;
}

void start_gui_process()
{
    // start the gui process
    if ((gui_pid = fork()) == -1)
    {
        perror("Fork can not create gui process");
        exit(SIGQUIT);
    }
    else if (gui_pid == 0)
    {

        char players_pids_0_arg[3];
        sprintf(players_pids_0_arg, "%d", players_pids[0]);

        char players_pids_4_arg[3];
        sprintf(players_pids_4_arg, "%d", players_pids[4]);

        char max_score_arg[3];
        sprintf(max_score_arg, "%d", max_score);

        // gui process

        execlp("./bin/attached_gui", "attached_gui", players_pids_0_arg, players_pids_4_arg, max_score_arg, (char *)NULL);

        perror("Execlp can not start gui process");
        exit(SIGQUIT);
    }
    else
    {
    }
}

void stop_gui_process()
{
    kill(gui_pid, UISIG); // send finish signal

    sleep(5);

    kill(gui_pid, SIGQUIT); // send stop signal
}
