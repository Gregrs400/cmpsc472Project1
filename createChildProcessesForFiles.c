#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

int main(void)
{

    pid_t child_processes[7];

    child_processes[0] = fork();

    if (child_processes[0] > 0)
    {

        printf("in parent process\n");

        for (int i = 1; i < 7; i++)
        {

            child_processes[i] = fork();

            if (child_processes[i] == 0)
            {

                printf("in child process %d\n", i);

                exit(0);

            }
            else if (child_processes[i] > 0)
            {

            }
            else
            {

                perror("fork failed\n");
                exit(1);

            }
        }
        wait(NULL);
    }

    else if (child_processes[0] == 0)
    {

        printf("in child process %d\n", 0);

    }
    else
    {

        perror("fork failed\n");

    }

    return 0;

}
