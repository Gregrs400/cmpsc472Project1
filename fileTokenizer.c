#include <stdio.h>
#include <stdlib.h>
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

    for (int i = 0; i < sizeof(filePaths)/sizeof(filePaths[0]); i++)
    {

        split_sentences(filePaths[i]);

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
        if (sentence != "/n")
        {
            char *word = strtok(sentence, " \t\n");
            while (word != NULL)
            {
                if (word != "/s")
                {
                    printf("Word: %s\n", word);
                    word = strtok(NULL, " \n\t");
                }
            }
        }
    }

    fclose(file);
}
