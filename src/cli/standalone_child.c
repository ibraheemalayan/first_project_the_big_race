#include "./child.c"

void handle_start()
{
    int start_point = player_index;
    int end_point = (player_index) % 5 + 1;
    speed = rand() % 20 + 5;
    printf("\n> %d: player %d in team %d has started running with speed %f from A%d to A%d \n", getpid(), player_index, team_num, speed, start_point, end_point);
    sleep(distance / speed);
    send_signal_to_next_player();
}

void handle_ui_signal(int the_sig)
{
    //
}