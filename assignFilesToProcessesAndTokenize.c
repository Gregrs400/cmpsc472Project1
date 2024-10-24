#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <string.h>

int main(void)
{

    FILE *file;
    char ch;
    void split_sentences(const char *filename);

    char* filePaths[] =
    {"drive/MyDrive/cmpsc472Project1/bib",
    "drive/MyDrive/cmpsc472Project1/paper1",
    "drive/MyDrive/cmpsc472Project1/paper2",
    "drive/MyDrive/cmpsc472Project1/progc",
    "drive/MyDrive/cmpsc472Project1/progl",
    "drive/MyDrive/cmpsc472Project1/progp",
    "drive/MyDrive/cmpsc472Project1/trans"};

    pid_t child_processes[7];

    int pipe_parentToChildren[7][2];
    int pipe_childrenToParent[7][2];

    for (int i = 0; i < 7; i++)
    {

        if (pipe(pipe_parentToChildren[i]) == -1 || pipe(pipe_childrenToParent[i]) == -1) 
        {
            perror("Pipe creation failed");
            return 1;
        }

    }

    child_processes[0] = fork();

    if (child_processes[0] > 0)
    {

        printf("in parent process\n");

        for (int i = 1; i < 7; i++)
        {

            child_processes[i] = fork();

            if (child_processes[i] == 0)
            {
                close(pipe_childrenToParent[i][1]);
                close(pipe_parentToChildren[i][1]);

                printf("in child process %d\n", i);

                char* filePath = malloc(1024 * sizeof(char));
                
                read(pipe_parentToChildren[i][0], filePath, 1024);

                close(pipe_parentToChildren[i][0]);

                printf("%s\n", filePath);

                split_sentences(filePath);

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

        for (int i = 0; i < 7; i++)
        {

                close(pipe_parentToChildren[i][0]);
                close(pipe_childrenToParent[i][1]);

        }
        for (int i = 0; i < 7; i++)
        {

                write(pipe_parentToChildren[i][1], filePaths[i], 1024);
                close(pipe_parentToChildren[i][1]);
                printf("writing\n");

        }

        wait(NULL);

    }

    else if (child_processes[0] == 0)
    {

        close(pipe_parentToChildren[0][1]);
        printf("in child process %d\n", 0);

        char* filePath = malloc(1024 * sizeof(char));

        read(pipe_parentToChildren[0][0], filePath, 1024);
        close(pipe_parentToChildren[0][0]);

        split_sentences(filePath);

        printf("%s\n", filePath);

        exit(0);

    }
    else
    {

        perror("fork failed\n");

    }

    return 0;

}
void split_sentences(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Unable to open file");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file))
    {
        char *sentence = strtok(line, ".!?");
        if (sentence != "\n")
        {
            char *word = strtok(sentence, " \t\n");
            while (word != NULL)
            {
                if (word != " ")
                {
                    printf("Word: %s\n", word);
                    word = strtok(NULL, " \n\t");
                }
            }
        }
    }

    fclose(file);
}
