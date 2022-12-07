
#include "./ui.c"

int team_1_fifo_fd;
int team_2_fifo_fd;

void setup_signals()
{
   // do nothing in standalone mode
}
void close_pipes()
{
}

void open_pipes()
{
   // do nothing in standalone mode
}
void validate_args(int argc, char *argv[])
{
   // do nothing in standalone mode
}

void update_team_1_speed()
{
   if (moving_player_team_1_before_update != currently_moving_player_team_1)
   {
      printf("team 1 was moving player %d and now moving player %d\n", moving_player_team_1_before_update, currently_moving_player_team_1);
      team_1_speed = randomeSpeed();

      moving_player_team_1_before_update = currently_moving_player_team_1;
   }
}
void update_team_2_speed()
{
   if (moving_player_team_2_before_update != currently_moving_player_team_2)
   {
      printf("team 2 was moving player %d and now moving player %d\n", moving_player_team_2_before_update, currently_moving_player_team_2);
      team_2_speed = randomeSpeed();
      moving_player_team_2_before_update = currently_moving_player_team_2;
   }
}
