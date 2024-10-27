#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <string.h>

int main(void)
{

    typedef struct
    {

        char* filePath;
        int fileSize;

    } FilePathAndSize;

    typedef struct
    {

        char* word;
        int count;

    } WordCount;

    FILE *file;
    char ch;
    void split_sentences(const char *filename);

    FilePathAndSize files[] =
    {(FilePathAndSize){"drive/MyDrive/cmpsc472Project1/bib",111261},
    (FilePathAndSize){"drive/MyDrive/cmpsc472Project1/paper1", 53161},
    (FilePathAndSize){"drive/MyDrive/cmpsc472Project1/paper2", 82199},
    (FilePathAndSize){"drive/MyDrive/cmpsc472Project1/progc",39611},
    (FilePathAndSize){"drive/MyDrive/cmpsc472Project1/progl",71646},
    (FilePathAndSize){"drive/MyDrive/cmpsc472Project1/progp",49379},
    (FilePathAndSize){"drive/MyDrive/cmpsc472Project1/trans", 93695}};

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

        // printf("in parent process\n");

        close(pipe_parentToChildren[0][0]);
        close(pipe_childrenToParent[0][1]);

        write(pipe_parentToChildren[0][1], &files[0], sizeof(files[0]));

        close(pipe_parentToChildren[0][1]);

        for (int i = 1; i < 7; i++)
        {

            child_processes[i] = fork();

            if (child_processes[i] == 0)
            {
                close(pipe_childrenToParent[i][1]);
                close(pipe_parentToChildren[i][1]);

                printf("in child process %d\n", i);

                FilePathAndSize fileAndSize;

                read(pipe_parentToChildren[i][0], &fileAndSize, sizeof(fileAndSize));

                printf("child process file path: %s\n", fileAndSize.filePath);

                close(pipe_parentToChildren[i][0]);

                // split_sentences(fileAndSize.filePath);

                exit(0);

            }
            else if (child_processes[i] > 0)
            {

                close(pipe_parentToChildren[i][0]);
                close(pipe_childrenToParent[i][1]);

                write(pipe_parentToChildren[i][1], &files[i], sizeof(files[i]));
                
                close(pipe_parentToChildren[i][1]);

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

        close(pipe_parentToChildren[0][1]);
        printf("in child process %d\n", 0);

        FilePathAndSize fileAndSize;

        read(pipe_parentToChildren[0][0], &fileAndSize, sizeof(fileAndSize));

        close(pipe_parentToChildren[0][0]);

        printf("child process 0 file path: %s\n", fileAndSize.filePath);

       // split_sentences(fileAndSize.filePath);

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
