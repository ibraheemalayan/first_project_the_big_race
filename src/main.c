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

GLuint fontOffset;

int team_1_running_direction = 1;

// Initail state for player 1 team 2
int team_2_running_direction = 1;

float team_1_x_positions[5];
float team_2_x_positions[5];

// Scores FIXME TODO
char scores[6] = "012345";

// Top roundes number
int roundes = 5;

// Score of team 1
int score1 = 0;

// Score of team 2
int score2 = 0;

void draw_rect(int x, int y, float size, int R, int G, int B)
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
   glColor3f(1.0f, 0.0f, 0.0f);
   glVertex2f(-10.0f, 10.0f);
   glVertex2f(A2, 0.0f);
   glVertex2f(A2, 0.0f);
   glVertex2f(-10.0f, -10.0f);
   glEnd();

   glBegin(GL_QUADS);
   glColor3f(0.0f, 0.0f, 0.0f);
   glVertex2f(-10.0f, 10.0f);
   glVertex2f(-7.0f, 5.0f);
   glVertex2f(10.0f, 5.0f);
   glVertex2f(10.0f, 10.0f);
   glEnd();
   glBegin(GL_QUADS);
   glColor3f(0.0f, 1.0f, 0.0f);
   glVertex2f(-10.0f, -10.0f);
   glVertex2f(-7.0f, -5.0f);
   glVertex2f(10.0f, -5.0f);
   glVertex2f(10.0f, -10.0f);
   glEnd();
}

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display()
{

   glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)
   glLoadIdentity();             // reset disply

   // Draw Palestine flage
   // draw_palestine_flag();

   draw_rect(A1, 0, PLAYER_SIZE, 0, 0, 0);
   draw_rect(A2, 0, PLAYER_SIZE, 0, 0, 0);
   draw_rect(A3, 0, PLAYER_SIZE, 0, 0, 0);
   draw_rect(A4, 0, PLAYER_SIZE, 0, 0, 0);
   draw_rect(A5, 0, PLAYER_SIZE, 0, 0, 0);

   // if game has ended, reset locations
   if (!(team_1_x_positions[4] == A1 && team_2_x_positions[4] == A1))
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
   glColor3f(0.0, 0.0, 1.0);
   glRasterPos2f(-6.5, 3.0); // define position on the screen
   glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scores[score1]);
   glEnd();

   // Print Score for team 2
   glColor3f(0.0, 1.0, 0.0);
   glRasterPos2f(-6.5, -3.0); // define position on the screen
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
   glColor3f(0.0, 0.0, 1.0);
   glRasterPos2f(-9.5, 3.0); // define position on the screen
   char *string2 = "Score of Team 1:";

   while (*string2)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string2++);
   }

   // print string "score of team 2"
   glColor3f(0.0, 1.0, 0.0);
   glRasterPos2f(-9.5, -3.0); // define position on the screen
   char *string3 = "Score of Team 2:";

   while (*string3)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string3++);
   }

   if (score1 == roundes)
   {
      // print string "The winner is team 1 (^_^)"
      glColor3f(0.0, 0.0, 1.0);
      glRasterPos2f(-1.5, -3.0); // define position on the screen
      char *string4 = "The winner is team 1 (^_^)";

      while (*string4)
      {
         glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string4++);
      }
   }

   if (score2 == roundes)
   {
      // print string "The winner is team 2 (^_^)"
      glColor3f(0.0, 1.0, 0.0);
      glRasterPos2f(-1.5, -3.0); // define position on the screen
      char *string4 = "The winner is team 2 (^_^)";

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
   glViewport(0, 0, 900, 900);

   // Projection
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(-10, 10, -10, 10); // FIXME left, right, bottom, top change to 100
   glMatrixMode(GL_MODELVIEW);
}

float randomeSpeed()
{

   float max = 0.05; // max speed
   // algorithm for creating a random number
   //(float cast) (float cast)	(RAND_MAX) is a costant included in the lib time.h
   float speed = ((float)rand() / (float)(RAND_MAX)) * max;
   return speed;
}

void update_locations(int t)
{
   if ((score1 != roundes && score2 != roundes))
      glutTimerFunc(1000 / 24, update_locations, 0);
   // printf("%f\n",team_1_x_positions[1]);

   glutPostRedisplay(); // marks the current window as needing to be redisplayed

   int flage_of_displacment = rand() % 2;
   if (flage_of_displacment)
   {
      // SPEED of team1
      switch (team_1_running_direction)
      {
      case 1:
         if (team_1_x_positions[4] == A5)
         {
            if (team_1_x_positions[0] < A2)
               team_1_x_positions[0] += randomeSpeed();
            else
               team_1_x_positions[0] = A2;
            if (team_1_x_positions[0] == A2)
            {
               if (team_1_x_positions[1] < 0)
                  team_1_x_positions[1] += randomeSpeed();
               else
                  team_1_x_positions[1] = 0;
            }

            if (team_1_x_positions[1] == A3)
            {
               if (team_1_x_positions[2] < A4)
                  team_1_x_positions[2] += randomeSpeed();
               else
                  team_1_x_positions[2] = A4;
            }

            if (team_1_x_positions[2] == A4)
            {
               if (team_1_x_positions[3] < A5)
                  team_1_x_positions[3] += randomeSpeed();
               else
               {
                  team_1_x_positions[3] = A5;
                  team_1_running_direction = -1;
               }
            }
         }
         break;

      case -1:
         if (team_1_x_positions[4] > A1)
            team_1_x_positions[4] -= randomeSpeed();
         else
         {
            team_1_x_positions[4] = A1;
            team_1_running_direction = 1;
            if (team_2_x_positions[4] > A1)
               score1 += 1;
         }
         break;
      }
   }
   else
   {
      // SPEED of team2
      switch (team_2_running_direction)
      {
      case 1:
         if (team_2_x_positions[4] == 8)
         {
            if (team_2_x_positions[0] < A2)
               team_2_x_positions[0] += randomeSpeed();
            else
               team_2_x_positions[0] = A2;
            if (team_2_x_positions[0] == A2)
            {
               if (team_2_x_positions[1] < 0)
                  team_2_x_positions[1] += randomeSpeed();
               else
                  team_2_x_positions[1] = 0;
            }

            if (team_2_x_positions[1] == 0)
            {
               if (team_2_x_positions[2] < 4)
                  team_2_x_positions[2] += randomeSpeed();
               else
                  team_2_x_positions[2] = 4;
            }

            if (team_2_x_positions[2] == 4)
            {
               if (team_2_x_positions[3] < 8)
                  team_2_x_positions[3] += randomeSpeed();
               else
               {
                  team_2_x_positions[3] = 8;
                  team_2_running_direction = -1;
               }
            }
         }
         break;

      case -1:
         if (team_2_x_positions[4] > A1)
            team_2_x_positions[4] -= randomeSpeed();
         else
         {
            team_2_x_positions[4] = A1;
            team_2_running_direction = 1;
            if (team_1_x_positions[4] > A1)
               score2 += 1;
         }
         break;
      }
   }

   glutPostRedisplay(); // marks the current window as needing to be redisplayed
}

// TODO
// void get_speed_for_player(int player index)){
//  if pipe not empty read new speed and return it, (save in global)
//  else return old speed (from global)
// }

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

   glutInitWindowSize(900, 900);          // Set the window's initial width & height
   glutInitWindowPosition(50, 50);        // Position the window's initial top-left corner
   glutCreateWindow("Free Palestine ");   // Create a window with the given title
   glutDisplayFunc(display);              // Register display callback handler for window re-paint
   glutReshapeFunc(reshape);              // Static display
   glutTimerFunc(0, update_locations, 0); // Call function after specified amount of time
   background();                          // Background color
   glutMainLoop();                        // Enter the event-processing loop
   return 0;
}