#include <GL/glut.h> // GLUT, include glu.h and gl.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void display();
void background();
void reshape(int, int);
void update_locations(int);
#include <unistd.h>

#define A1 -8
#define A2 -4
#define A3 0
#define A4 4
#define A5 8
#define PLAYER_SIZE 0.2
#define TEAM_1_Y_VALUE 1
#define TEAM_2_Y_VALUE -1

#define RIGHT_DIRECTION 1
#define LEFT_DIRECTION -1

#define FPS 120
#define MAX_SPEED_PER_FRAM 0.15

GLuint fontOffset;

int team_1_running_direction = RIGHT_DIRECTION;
int team_2_running_direction = RIGHT_DIRECTION;

float team_1_x_positions[5];
float team_2_x_positions[5];

float team_1_speed;
float team_2_speed;

int team_1_finished_round = 0;
int team_2_finished_round = 0;

int currently_moving_player_team_1 = 0;
int currently_moving_player_team_2 = 0;

// used to trigger pipe reads when player changes
int moving_player_team_1_before_update = -1;
int moving_player_team_2_before_update = -1;

// Scores FIXME TODO
char scores[6] = "012345";

// Top roundes number
int roundes = 2;

// Score of team 1
int score1 = 0;

// Score of team 2
int score2 = 0;

void draw_rect(float x, float y, float size, int R, int G, int B);
void update_team_1_speed();
void update_team_2_speed();

void draw_rect(float x, float y, float size, int R, int G, int B)
{

   glPushMatrix();
   glTranslatef(x, y, 0.0f);
   glScalef(size, size, 1.0f);
   glBegin(GL_QUADS);
   glColor3ub(R, G, B);
   glVertex2f(-1, -1);
   glVertex2f(1, -1);
   glVertex2f(1, 1);
   glVertex2f(-1, 1);
   glEnd();
   glPopMatrix();
}

void draw_palestine_flag()
{

   glBegin(GL_QUADS);
   glColor3ub(206, 17, 38); // palestine flag red
   glVertex2f(-14.0f, 5.0f);
   glVertex2f(-8, 0.0f);
   glVertex2f(-8, 0.0f);
   glVertex2f(-14.0f, -5.0f);
   glEnd();

   glBegin(GL_QUADS);
   glColor3f(0.0f, 0.0f, 0.0f); // palestine flag black
   glVertex2f(-14.0f, 5.0f);
   glVertex2f(-11.0f, 2.5f);
   glVertex2f(14.0f, 2.5f);
   glVertex2f(14.0f, 5.0f);
   glEnd();
   glBegin(GL_QUADS);
   glColor3ub(0, 122, 61); // palestine flag green
   glVertex2f(-14.0f, -5.0f);
   glVertex2f(-11.0f, -2.5f);
   glVertex2f(14.0f, -2.5f);
   glVertex2f(14.0f, -5.0f);
   glEnd();
}

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display()
{

   glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)
   glLoadIdentity();             // reset disply

   // Draw Palestine flage
   draw_palestine_flag();

   draw_rect(A1, 0, PLAYER_SIZE, 0, 0, 0);
   draw_rect(A2, 0, PLAYER_SIZE, 0, 0, 0);
   draw_rect(A3, 0, PLAYER_SIZE, 0, 0, 0);
   draw_rect(A4, 0, PLAYER_SIZE, 0, 0, 0);
   draw_rect(A5, 0, PLAYER_SIZE, 0, 0, 0);

   update_team_1_speed();
   update_team_2_speed();

   // if game has ended, reset locations
   if (!(team_1_x_positions[4] <= A1 && team_2_x_positions[4] <= A1))
   {
      // Team1 movement
      draw_rect(team_1_x_positions[0], TEAM_1_Y_VALUE, PLAYER_SIZE, 0, 255, 0);
      draw_rect(team_1_x_positions[1], TEAM_1_Y_VALUE, PLAYER_SIZE, 255, 0, 255);
      draw_rect(team_1_x_positions[2], TEAM_1_Y_VALUE, PLAYER_SIZE, 255, 255, 0);
      draw_rect(team_1_x_positions[3], TEAM_1_Y_VALUE, PLAYER_SIZE, 40, 0, 255);
      draw_rect(team_1_x_positions[4], TEAM_1_Y_VALUE, PLAYER_SIZE, 0, 255, 255);

      // Team1 movement
      draw_rect(team_2_x_positions[0], TEAM_2_Y_VALUE, PLAYER_SIZE, 0, 255, 0);
      draw_rect(team_2_x_positions[1], TEAM_2_Y_VALUE, PLAYER_SIZE, 255, 0, 255);
      draw_rect(team_2_x_positions[2], TEAM_2_Y_VALUE, PLAYER_SIZE, 255, 255, 0);
      draw_rect(team_2_x_positions[3], TEAM_2_Y_VALUE, PLAYER_SIZE, 40, 0, 255);
      draw_rect(team_2_x_positions[4], TEAM_2_Y_VALUE, PLAYER_SIZE, 0, 255, 255);
   }
   else
   {

      printf("\n-----------------------\nNEW ROUND\n-----------------------\n");

      team_1_finished_round = 0;
      team_2_finished_round = 0;

      currently_moving_player_team_1 = 0;
      currently_moving_player_team_2 = 0;

      team_1_running_direction = RIGHT_DIRECTION;
      team_2_running_direction = RIGHT_DIRECTION;

      // Team1 movement

      draw_rect(A1, TEAM_1_Y_VALUE, PLAYER_SIZE, 0, 255, 0);
      team_1_x_positions[0] = A1;

      draw_rect(A2, TEAM_1_Y_VALUE, PLAYER_SIZE, 255, 0, 255);
      team_1_x_positions[1] = A2;

      draw_rect(A2, TEAM_1_Y_VALUE, PLAYER_SIZE, 255, 255, 0);
      team_1_x_positions[2] = A3;

      draw_rect(A2, TEAM_1_Y_VALUE, PLAYER_SIZE, 40, 0, 255);
      team_1_x_positions[3] = A4;

      draw_rect(A2, TEAM_1_Y_VALUE, PLAYER_SIZE, 0, 255, 255);
      team_1_x_positions[4] = A5;

      // Team2 movement

      draw_rect(A1, TEAM_2_Y_VALUE, PLAYER_SIZE, 0, 255, 0);
      team_2_x_positions[0] = A1;

      draw_rect(A2, TEAM_2_Y_VALUE, PLAYER_SIZE, 255, 0, 255);
      team_2_x_positions[1] = A2;

      draw_rect(A2, TEAM_2_Y_VALUE, PLAYER_SIZE, 255, 255, 0);
      team_2_x_positions[2] = A3;

      draw_rect(A2, TEAM_2_Y_VALUE, PLAYER_SIZE, 40, 0, 255);
      team_2_x_positions[3] = A4;

      draw_rect(A2, TEAM_2_Y_VALUE, PLAYER_SIZE, 0, 255, 255);
      team_2_x_positions[4] = A5;
   }

   // Print Score for team 1
   glColor3ub(0, 122, 61);   // palestine flag greed
   glRasterPos2f(-4.0, 4.0); // define position on the screen
   glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scores[score1]);
   glEnd();

   // Print Score for team 2
   glColor3f(0.0, 0.0, 0.0);
   glRasterPos2f(-4.0, -4.0); // define position on the screen
   glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scores[score2]);
   glEnd();

   // print string "The big race"
   glColor3f(1.0, 0.0, 0.0);
   glRasterPos2f(-1.0, 6.0); // define position on the screen
   char *string1 = "The Big Race";

   while (*string1)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string1++);
   }

   // print string "score of team 1"
   glColor3ub(0, 122, 61);   // palestine flag green
   glRasterPos2f(-9.5, 4.0); // define position on the screen
   char *string2 = "Score of Team 1: ";

   while (*string2)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string2++);
   }

   // print string "score of team 2"
   glColor3f(0.0, 0.0, 0.0);
   glRasterPos2f(-9.5, -4.0); // define position on the screen
   char *string3 = "Score of Team 2: ";

   while (*string3)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string3++);
   }

   if (score1 == roundes)
   {
      glColor3ub(206, 17, 38); // palestine flag red
      glRasterPos2f(-1, 4.0);  // define position on the screen
      char *string4 = "Winner (^_^)";

      while (*string4)
      {
         glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string4++);
      }
   }

   if (score2 == roundes)
   {
      glColor3ub(206, 17, 38); // palestine flag red
      glRasterPos2f(-1, -4.0); // define position on the screen
      char *string4 = "Winner (^_^)";

      while (*string4)
      {
         glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string4++);
      }
   }

   glutSwapBuffers(); // Swap the buffers (replace current frame with the new one)
}

void background()
{
   glClearColor(1.0, 1.0, 1.0, 1.0);
}

void reshape(int w, int h)
{
   // ViewPort
   glViewport(0, 0, 800, 400);

   // Projection
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(-14, 10, -5, 5); // FIXME left, right, bottom, top change to 100
   glMatrixMode(GL_MODELVIEW);
}

float randomeSpeed()
{

   float MaxSpeedPerFrame = MAX_SPEED_PER_FRAM - MAX_SPEED_PER_FRAM / 3; // max speed
   // algorithm for creating a random number
   //(float cast) (float cast)	(RAND_MAX) is a costant included in the lib time.h
   float speed = ((float)rand() / (float)(RAND_MAX)) * MaxSpeedPerFrame;
   return speed + MAX_SPEED_PER_FRAM / 3;
}

// void update_moving_player(int t)
// {
//    if ((score1 != roundes && score2 != roundes))
//       glutTimerFunc(1000 / FPS, update_locations, 0);
// }

void update_positions_of_team(int team_num)
{

   float *current_team_x_positions = (team_num == 1) ? team_1_x_positions : team_2_x_positions;
   float *other_team_x_positions = (team_num != 1) ? team_1_x_positions : team_2_x_positions;

   int *current_team_score = (team_num == 1) ? &score1 : &score2;
   int *current_team_running_direction = (team_num == 1) ? &team_1_running_direction : &team_2_running_direction;
   int *current_team_finished_round = (team_num == 1) ? &team_1_finished_round : &team_2_finished_round;
   int *currently_moving_player_in_this_team = (team_num == 1) ? &currently_moving_player_team_1 : &currently_moving_player_team_2;

   if (current_team_x_positions[0] < A2)
      *currently_moving_player_in_this_team = 0;

   else
      current_team_x_positions[0] = A2;

   if (current_team_x_positions[0] == A2)
   {
      if (current_team_x_positions[1] < A3)
         *currently_moving_player_in_this_team = 1;
      else
         current_team_x_positions[1] = A3;
   }

   if (current_team_x_positions[1] == A3)
   {
      if (current_team_x_positions[2] < A4)
         *currently_moving_player_in_this_team = 2;
      else
         current_team_x_positions[2] = A4;
   }

   if (current_team_x_positions[2] == A4)
   {
      if (current_team_x_positions[3] < A5)
         *currently_moving_player_in_this_team = 3;
      else
      {
         current_team_x_positions[3] = A5;
         *current_team_running_direction = LEFT_DIRECTION;
      }
   }

   if (current_team_x_positions[3] == A5) // 4th player reached A5
   {

      if (current_team_x_positions[4] > A1)
         *currently_moving_player_in_this_team = 4;
      else
      {
         current_team_x_positions[4] = A1;
         if (other_team_x_positions[4] > A1 && !*current_team_finished_round)
         {
            *current_team_score += 1;
            *current_team_finished_round = 1;
            *currently_moving_player_in_this_team = 0;
         }
      }
   }
}

void update_locations(int t)
{
   if ((score1 != roundes && score2 != roundes))
      glutTimerFunc(1000 / FPS, update_locations, 0);

   glutPostRedisplay(); // marks the current window as needing to be redisplayed

   update_positions_of_team(1);
   if (!team_1_finished_round)
   {
      // update position of running player in team 1
      team_1_x_positions[currently_moving_player_team_1] += team_1_speed * team_1_running_direction;
   }

   update_positions_of_team(2);
   if (!team_2_finished_round)
   {
      // update position of running player in team 1
      team_2_x_positions[currently_moving_player_team_2] += team_2_speed * team_2_running_direction;
   }
}

void update_team_1_speed()
{
   if (moving_player_team_1_before_update != currently_moving_player_team_1)
   {
      printf("team 1 was moving player %d and now moving player %d\n", moving_player_team_1_before_update, currently_moving_player_team_1);
      team_1_speed = randomeSpeed(); // TODO read from pipe
      //  if pipe not empty read new speed and return it, (save in global)
      //  else return old speed (from global)

      moving_player_team_1_before_update = currently_moving_player_team_1;
   }
}
void update_team_2_speed()
{
   if (moving_player_team_2_before_update != currently_moving_player_team_2)
   {
      printf("team 2 was moving player %d and now moving player %d\n", moving_player_team_2_before_update, currently_moving_player_team_2);
      team_2_speed = randomeSpeed(); // TODO read from pipe
      moving_player_team_2_before_update = currently_moving_player_team_2;
   }
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char **argv)
{
   srand(time(NULL));

   team_1_x_positions[0] = A1;
   team_1_x_positions[1] = A2;
   team_1_x_positions[2] = A3;
   team_1_x_positions[3] = A4;
   team_1_x_positions[4] = A5;

   team_2_x_positions[0] = A1;
   team_2_x_positions[1] = A2;
   team_2_x_positions[2] = A3;
   team_2_x_positions[3] = A4;
   team_2_x_positions[4] = A5;

   glutInit(&argc, argv);                       // Initialize GLUT
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // for animation

   glutInitWindowSize(800, 400);          // Set the window's initial width & height
   glutInitWindowPosition(50, 50);        // Position the window's initial top-left corner
   glutCreateWindow("Free Palestine ");   // Create a window with the given title
   glutDisplayFunc(display);              // Register display callback handler for window re-paint
   glutReshapeFunc(reshape);              // Static display
   glutTimerFunc(0, update_locations, 0); // Call function after specified amount of time
   background();                          // Background color
   glutMainLoop();                        // Enter the event-processing loop
   return 0;
}