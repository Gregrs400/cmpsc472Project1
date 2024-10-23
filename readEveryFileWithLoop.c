#include <stdio.h>

int main(void)
{

    FILE *file;
    char ch;

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

        file = fopen(filePaths[i], "r");
        if (file == NULL) {
            perror("Error opening file");
            return -1;
        }
        else
        {

            while ((ch = fgetc(file)) != EOF)
            {
                putchar(ch);
            }

        }

        fclose(file);

    }


return 0;
}
