#include <GL/glut.h> // GLUT, include glu.h and gl.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void display();
void background();
void reshape(int ,int);
void timer(int);
GLuint fontOffset;




//Initail state for player 1 team 1
float x_Position_team1 = -8.0;
int state_team1 = 1;


//Initail state for player 1 team 2
float x_Position_team2 = -8.0;
int state_team2 = 1;

//Scores
char scoures[6]="012345";

//Top roundes number
int roundes =5;

//Score of team 1
int score1=0;

//Score of team 2
int score2=0;



/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {

   glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)
   glLoadIdentity(); // reset disply 
  
   // Draw Palestine flage
   glBegin(GL_QUADS);
      glColor3f(1.0f, 0.0f, 0.0f); 
      glVertex2f(-10.0f, 10.0f);   
      glVertex2f(-4.0f, 0.0f);
      glVertex2f(-4.0f,  0.0f);
      glVertex2f(-10.0f,  -10.0f);
   glEnd();
   glBegin(GL_QUADS);              
      glColor3f(0.0f, 0.0f, 0.0f);
      glVertex2f(-10.0f, 10.0f); 
      glVertex2f(-7.0f, 5.0f);
      glVertex2f(10.0f,  5.0f);
      glVertex2f(10.0f,  10.0f);
   glEnd();
   glBegin(GL_QUADS);              
      glColor3f(0.0f, 1.0f, 0.0f); 
      glVertex2f(-10.0f, -10.0f); 
      glVertex2f(-7.0f, -5.0f);
      glVertex2f(10.0f,  -5.0f);
      glVertex2f(10.0f,  -10.0f);
    glEnd();
 
   glPointSize(20.0);// Point Size in pixels
   glBegin(GL_POINTS);// draw The Main 5 points
      glColor3f(0.0f, 0.0f, 0.0f);
      glVertex2f(-8.0f, 0.0f);
      glVertex2f(-4.0f, 0.0f);
      glVertex2f(0.0f, 0.0f);
      glVertex2f(4.0f, 0.0f);
      glVertex2f(8.0f, 0.0f);
   glEnd();

 if (score1 != roundes && score2 != roundes){
   //Team1 movement 
   glPointSize(20.0);// Point Size in pixels
   glBegin(GL_POINTS);// draw The point for team 1
      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex2f(x_Position_team1, 1.0f);
   glEnd();

   //Team2 movement
   glPointSize(20.0);// Point Size in pixels
   glBegin(GL_POINTS);// draw The point for team 1
      glColor3f(0.0f, 1.0f, 0.0f);
      glVertex2f(x_Position_team2, -1.0f);
   glEnd();
   }
  else{
   //Team1 movement 
   glPointSize(20.0);// Point Size in pixels
   glBegin(GL_POINTS);// draw The point for team 1
      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex2f(-8.0, 1.0f);
   glEnd();

   //Team2 movement
   glPointSize(20.0);// Point Size in pixels
   glBegin(GL_POINTS);// draw The point for team 1
      glColor3f(0.0f, 1.0f, 0.0f);
      glVertex2f(-8.0, -1.0f);
   glEnd();
   }

   //Print Score for team 1
   glColor3f (0.0, 0.0, 1.0);
   glRasterPos2f(-6.5, 3.0); //define position on the screen
   glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoures[score1]);
   glEnd();


   //Print Score for team 2
   glColor3f (0.0, 1.0, 0.0);
   glRasterPos2f(-6.5, -3.0); //define position on the screen
   glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoures[score2]);
   glEnd();

   // print string "The big race"
    glColor3f (1.0, 0.0, 0.0);
   glRasterPos2f(-1.0, 6.0); //define position on the screen
   char *string1 = "The big race";
      
   while(*string1){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string1++);
      }


   // print string "score of team 1"
    glColor3f (0.0, 0.0, 1.0);
   glRasterPos2f(-9.5, 3.0); //define position on the screen
   char *string2 = "Score of Team 1:";
      
   while(*string2){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string2++);
   }

    // print string "score of team 2"
    glColor3f (0.0, 1.0, 0.0);
   glRasterPos2f(-9.5, -3.0); //define position on the screen
   char *string3 = "Score of Team 2:";
      
   while(*string3){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string3++);
   }


   if(score1 == roundes){
   // print string "The winner is team 1 (^_^)"
    glColor3f (0.0, 0.0, 1.0);
   glRasterPos2f(-1.5, -3.0); //define position on the screen
   char *string4 = "The winner is team 1 (^_^)";
      
   while(*string4){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string4++);
   }
   }

   if(score2 == roundes){
   // print string "The winner is team 2 (^_^)"
    glColor3f (0.0, 1.0, 0.0);
   glRasterPos2f(-1.5, -3.0); //define position on the screen
   char *string4 = "The winner is team 2 (^_^)";
      
   while(*string4){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string4++);
   }
   }
  


   glutSwapBuffers(); //Display animation 
}

void background(){
   glClearColor(1.0, 1.0, 1.0,1.0);
}


void reshape(int w,int h){
   //ViewPort
   glViewport(0, 0, 1200, 600);

   //Projection
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(-10,10,-10,10);
   glMatrixMode(GL_MODELVIEW);
}

float randomeSpeed(){

   //srand(time(NULL));
    float max = 0.07; //max speed
  	//algorithm for creating a random number 
  	//(float cast) (float cast)	(RAND_MAX) is a costant included in the lib time.h
    float speed =((float)rand()/(float)(RAND_MAX)) * max;
    return speed;

}


//Control the speed 
void timer(int t){
   glutPostRedisplay();//call display funation
   if (score1 != roundes && score2 != roundes)
      glutTimerFunc(1000/60,timer,0);




   //SPEED of team2
   switch (state_team2){
      case 1:
         if(x_Position_team2 < 8)
            x_Position_team2+= 0.1;
         else{
           state_team2 =-1;
           }

         break;   


      case -1:
          if(x_Position_team2 > -8)
             x_Position_team2-= randomeSpeed();
          else{
            state_team2 = 1;
            if(score1 != roundes)
               score2+=1;
              }
         break;   
   


}


//SPEED of team1
   switch (state_team1){
      case 1:
         if(x_Position_team1 < 8)
            x_Position_team1+= randomeSpeed();
         else
           state_team1 =-1;
         break;   


      case -1:
          if(x_Position_team1 > -8)
             x_Position_team1-= randomeSpeed();
          else{
            state_team1 = 1;
            if(score2 != roundes)
               score1+=1;
              }
         break;   
   


}


}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
   glutInit(&argc, argv); // Initialize GLUT
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // for animation
   
   glutInitWindowSize(1200,600); // Set the window's initial width & height
   glutInitWindowPosition(50, 50);// Position the window's initial top-left corner
   glutCreateWindow("Free Palestine "); // Create a window with the given title
   glutDisplayFunc(display); // Register display callback handler for window re-paint
   glutReshapeFunc(reshape); // Static display 
   glutTimerFunc(0,timer,0); //Call function after specified amount of time
   background();//Background colore 
   glutMainLoop();// Enter the event-processing loop
   return 0;

}