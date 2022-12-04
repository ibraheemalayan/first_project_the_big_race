

/*
 * The fork() function
 */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, pid;

    printf("My process ID is %d\n", getpid());

    for (i = 0; i < 3; i++)
    {
        if ((pid = fork()) == -1)
        {
            printf("fork failure ... getting out\n");
            exit(-1);
        }

        if (pid != 0)
        {
            printf("I am the parent => PID = %d, child ID = %d\n", getpid(), pid);
            // exit(0);
            // while(1);
        }
        else
        {
            printf("I am the child  => PID = %d\n", getpid());
            // while(1);
        }
    }
    while (1)
        ;

    return (0);
}

/* print string
glColor3f (1.0, 0.0, 0.0);
        glRasterPos2f(-240, 120); //define position on the screen
        char *string = "Text";

      while(*string){
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *string++);
      }*/