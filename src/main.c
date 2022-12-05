#include <GL/glut.h> // GLUT, include glu.h and gl.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void display();
void background();
void reshape(int, int);
void timer(int);
#include <unistd.h>

#define A1 -8
#define A2 -4
#define A3 0
#define A4 4
#define A5 8

GLuint fontOffset;

// Initail state for players of  team 1
float x_Position_team1_1 = A1;
float x_Position_team1_2 = A2;
float x_Position_team1_3 = A3;
float x_Position_team1_4 = A4;
float x_Position_team1_5 = A5;

// Initail state for players of  team 2
float x_Position_team2_1 = A1;
float x_Position_team2_2 = A2;
float x_Position_team2_3 = A3;
float x_Position_team2_4 = A4;
float x_Position_team2_5 = A5;

int state_team1 = 1;

// Initail state for player 1 team 2
int state_team2 = 1;

float red_players_x_positions[5];
float green_players_x_positions[5];

// speed and direction of player 1 team 1

// Scores
char scoures[6] = "012345";

// Top roundes number
int roundes = 5;

// Score of team 1
int score1 = 0;

// Score of team 2
int score2 = 0;

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display()
{

   glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)
   glLoadIdentity();             // reset disply

   // Draw Palestine flage
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

   glPointSize(20.0);  // Point Size in pixels
   glBegin(GL_POINTS); // draw The Main 5 points
   glColor3f(0.0f, 0.0f, 0.0f);
   glVertex2f(A1, 0.0f);
   glVertex2f(A2, 0.0f);
   glVertex2f(A3, 0.0f);
   glVertex2f(A4, 0.0f);
   glVertex2f(A5, 0.0f);
   glEnd();

   //(score1 != roundes && score2 != roundes) ||
   if (!(x_Position_team1_5 == -8 && x_Position_team2_5 == -8))
   {
      // Team1 movement
      glPointSize(20.0);  // Point Size in pixels
      glBegin(GL_POINTS); // draw The point for team 1
      glColor3f(0.0f, 1.0f, 0.0f);
      glVertex2f(x_Position_team1_1, 1.0f);
      glEnd();

      glPointSize(20.0);  // Point Size in pixels
      glBegin(GL_POINTS); // draw The point 2 for team 1
      glColor3f(1.0f, 0.0f, 1.0f);
      glVertex2f(x_Position_team1_2, 1.0f);
      glEnd();
      glPointSize(20.0);  // Point Size in pixels
      glBegin(GL_POINTS); // draw The point 3 for team 1
      glColor3f(1.0f, 1.0f, 0.0f);
      glVertex2f(x_Position_team1_3, 1.0f);
      glEnd();

      glPointSize(20.0);  // Point Size in pixels
      glBegin(GL_POINTS); // draw The point 4 for team 1
      glColor3f(0.4f, 0.0f, 1.0f);
      glVertex2f(x_Position_team1_4, 1.0f);
      glEnd();
      glPointSize(20.0);  // Point Size in pixels
      glBegin(GL_POINTS); // draw The point 5 for team 1
      glColor3f(0.0f, 1.0f, 1.0f);
      glVertex2f(x_Position_team1_5, 1.0f);
      glEnd();

      // Team2 movement
      glPointSize(20.0);  // Point Size in pixels
      glBegin(GL_POINTS); // draw The point for team 1
      glColor3f(0.0f, 1.0f, 0.0f);
      glVertex2f(x_Position_team2_1, -1.0f);
      glEnd();

      glPointSize(20.0);  // Point Size in pixels
      glBegin(GL_POINTS); // draw The point 2 for team 1
      glColor3f(1.0f, 0.0f, 1.0f);
      glVertex2f(x_Position_team2_2, -1.0f);
      glEnd();
      glPointSize(20.0);  // Point Size in pixels
      glBegin(GL_POINTS); // draw The point 3 for team 1
      glColor3f(1.0f, 1.0f, 0.0f);
      glVertex2f(x_Position_team2_3, -1.0f);
      glEnd();

      glPointSize(20.0);  // Point Size in pixels
      glBegin(GL_POINTS); // draw The point 4 for team 1
      glColor3f(0.4f, 0.0f, 1.0f);
      glVertex2f(x_Position_team2_4, -1.0f);
      glEnd();
      glPointSize(20.0);  // Point Size in pixels
      glBegin(GL_POINTS); // draw The point 5 for team 1
      glColor3f(0.0f, 1.0f, 1.0f);
      glVertex2f(x_Position_team2_5, -1.0f);
      glEnd();
   }
   else
   {
      // Team1 movement
      glPointSize(20.0);  // Point Size in pixels
      glBegin(GL_POINTS); // draw The point 1 for team 1
      glColor3f(0.0f, 1.0f, 0.0f);
      glVertex2f(-8.0f, 1.0f);
      glEnd();
      x_Position_team1_1 = -8;

      glPointSize(20.0);  // Point Size in pixels
      glBegin(GL_POINTS); // draw The point 2 for team 1
      glColor3f(1.0f, 0.0f, 1.0f);
      glVertex2f(A2, 1.0f);
      glEnd();
      x_Position_team1_2 = A2;

      glPointSize(20.0);  // Point Size in pixels
      glBegin(GL_POINTS); // draw The point 3 for team 1
      glColor3f(1.0f, 1.0f, 0.0f);
      glVertex2f(A3, 1.0f);
      glEnd();
      x_Position_team1_3 = 0;

      glPointSize(20.0);  // Point Size in pixels
      glBegin(GL_POINTS); // draw The point 4 for team 1
      glColor3f(0.4f, 0.0f, 1.0f);
      glVertex2f(4.0f, 1.0f);
      glEnd();
      x_Position_team1_4 = 4;

      glPointSize(20.0);  // Point Size in pixels
      glBegin(GL_POINTS); // draw The point 5 for team 1
      glColor3f(0.0f, 1.0f, 1.0f);
      glVertex2f(8.0f, 1.0f);
      glEnd();
      x_Position_team1_5 = 8;

      // Team2 movement
      glPointSize(20.0);  // Point Size in pixels
      glBegin(GL_POINTS); // draw The point for team 1
      glColor3f(0.0f, 1.0f, 0.0f);
      glVertex2f(-8.0f, -1.0f);
      glEnd();
      x_Position_team2_1 = -8;

      glPointSize(20.0);  // Point Size in pixels
      glBegin(GL_POINTS); // draw The point 2 for team 1
      glColor3f(1.0f, 0.0f, 1.0f);
      glVertex2f(A2, -1.0f);
      glEnd();
      x_Position_team2_2 = A2;

      glPointSize(20.0);  // Point Size in pixels
      glBegin(GL_POINTS); // draw The point 3 for team 1
      glColor3f(1.0f, 1.0f, 0.0f);
      glVertex2f(A3, -1.0f);
      glEnd();
      x_Position_team2_3 = 0;

      glPointSize(20.0);  // Point Size in pixels
      glBegin(GL_POINTS); // draw The point 4 for team 1
      glColor3f(0.4f, 0.0f, 1.0f);
      glVertex2f(4.0f, -1.0f);
      glEnd();
      x_Position_team2_4 = 4;

      glPointSize(20.0);  // Point Size in pixels
      glBegin(GL_POINTS); // draw The point 5 for team 1
      glColor3f(0.0f, 1.0f, 1.0f);
      glVertex2f(8.0f, -1.0f);
      glEnd();
      x_Position_team2_5 = 8;

      // Wait for the signal from paiernt
      // sleep(5);
   }

   // Print Score for team 1
   glColor3f(0.0, 0.0, 1.0);
   glRasterPos2f(-6.5, 3.0); // define position on the screen
   glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoures[score1]);
   glEnd();

   // Print Score for team 2
   glColor3f(0.0, 1.0, 0.0);
   glRasterPos2f(-6.5, -3.0); // define position on the screen
   glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoures[score2]);
   glEnd();

   // print string "The big race"
   glColor3f(1.0, 0.0, 0.0);
   glRasterPos2f(-1.0, 6.0); // define position on the screen
   char *string1 = "The big race";

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

   glutSwapBuffers(); // Display animation
}

void background()
{
   glClearColor(1.0, 1.0, 1.0, 1.0);
}

void reshape(int w, int h)
{
   // ViewPort
   glViewport(0, 0, 1200, 600);

   // Projection
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(-10, 10, -10, 10);
   glMatrixMode(GL_MODELVIEW);
}

float randomeSpeed()
{

   float max = 0.1; // max speed
   // algorithm for creating a random number
   //(float cast) (float cast)	(RAND_MAX) is a costant included in the lib time.h
   float speed = ((float)rand() / (float)(RAND_MAX)) * max;
   return speed;
}

// Control the speed
void timer(int t)
{
   glutPostRedisplay(); // call display funation
   if ((score1 != roundes && score2 != roundes))
      glutTimerFunc(1000 / 60, timer, 0);
   // printf("%f\n",x_Position_team1_2);

   int flage_of_displacment = rand() % 2;
   if (flage_of_displacment)
   {
      // SPEED of team1
      switch (state_team1)
      {
      case 1:
         if (x_Position_team1_5 == 8)
         {
            if (x_Position_team1_1 < A2)
               x_Position_team1_1 += randomeSpeed();
            else
               x_Position_team1_1 = A2;
            if (x_Position_team1_1 == A2)
            {
               if (x_Position_team1_2 < 0)
                  x_Position_team1_2 += randomeSpeed();
               else
                  x_Position_team1_2 = 0;
            }

            if (x_Position_team1_2 == 0)
            {
               if (x_Position_team1_3 < 4)
                  x_Position_team1_3 += randomeSpeed();
               else
                  x_Position_team1_3 = 4;
            }

            if (x_Position_team1_3 == 4)
            {
               if (x_Position_team1_4 < 8)
                  x_Position_team1_4 += randomeSpeed();
               else
               {
                  x_Position_team1_4 = 8;
                  state_team1 = -1;
               }
            }
         }
         break;

      case -1:
         if (x_Position_team1_5 > A1)
            x_Position_team1_5 -= randomeSpeed();
         else
         {
            x_Position_team1_5 = A1;
            state_team1 = 1;
            if (x_Position_team2_5 > A1)
               score1 += 1;
         }
         break;
      }
   }
   else
   {
      // SPEED of team2
      switch (state_team2)
      {
      case 1:
         if (x_Position_team2_5 == 8)
         {
            if (x_Position_team2_1 < A2)
               x_Position_team2_1 += randomeSpeed();
            else
               x_Position_team2_1 = A2;
            if (x_Position_team2_1 == A2)
            {
               if (x_Position_team2_2 < 0)
                  x_Position_team2_2 += randomeSpeed();
               else
                  x_Position_team2_2 = 0;
            }

            if (x_Position_team2_2 == 0)
            {
               if (x_Position_team2_3 < 4)
                  x_Position_team2_3 += randomeSpeed();
               else
                  x_Position_team2_3 = 4;
            }

            if (x_Position_team2_3 == 4)
            {
               if (x_Position_team2_4 < 8)
                  x_Position_team2_4 += randomeSpeed();
               else
               {
                  x_Position_team2_4 = 8;
                  state_team2 = -1;
               }
            }
         }
         break;

      case -1:
         if (x_Position_team2_5 > A1)
            x_Position_team2_5 -= randomeSpeed();
         else
         {
            x_Position_team2_5 = A1;
            state_team2 = 1;
            if (x_Position_team1_5 > A1)
               score2 += 1;
         }
         break;
      }
   }
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
   glutInit(&argc, argv);                       // Initialize GLUT
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // for animation

   glutInitWindowSize(1200, 600);       // Set the window's initial width & height
   glutInitWindowPosition(50, 50);      // Position the window's initial top-left corner
   glutCreateWindow("Free Palestine "); // Create a window with the given title
   glutDisplayFunc(display);            // Register display callback handler for window re-paint
   glutReshapeFunc(reshape);            // Static display
   glutTimerFunc(0, timer, 0);          // Call function after specified amount of time
   background();                        // Background color
   glutMainLoop();                      // Enter the event-processing loop
   return 0;
}