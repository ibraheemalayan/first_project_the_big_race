

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include "./std.h"

int rounds;
int current_round = 0;

void validate_args(int argc, char *argv[])
{

    if (argc < 2)
    {
        errno = EINVAL;
        red_stderr();
        perror("\nMissing the number of childs argument");
        reset_stderr();
        exit(-1);
    }

    if (!(rounds = atoi(argv[1])))
    {
        errno = EINVAL;
        red_stderr();
        perror("\nThe first argument must be an integer");
        reset_stderr();
        exit(-1);
    };
}

int main(int argc, char *argv[])
{

    srand(time(NULL)); // Initialization, should only be called once.

    validate_args(argc, argv);

    for (current_round = 0; current_round < rounds; current_round++)
    {
        green_stdout();
        printf("\n\n> Round #%d out of #%d ...\n\n", current_round + 1, rounds);
        reset_stdout();
    }

    int status, i = 0, num_of_forks = rounds;

    pid_t children_pids[num_of_forks];

    printf("\n\nParent process ID is %d\n", getpid());

    for (; i < num_of_forks; i++)
    {

        pid_t current;

        if ((current = fork()) == -1)
        {
            perror("fork failure ... getting out\n");
            exit(-1);
        }

        if (current == 0)
        {
            // child
            execlp("./bin/child", "child", "4", (char *)NULL);
            exit(-1);
        }
        else
        {
            // parent
            children_pids[i] = current;
        }
    }

    for (i = 0; i < num_of_forks; i++)
    {
        wait(&status);
    }

    return (0);
}
