#include <stdio.h>

int main(void)
{

    FILE *file;
    char ch;

    file = fopen("drive/MyDrive/cmpsc472Project1/bib", "r");

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


    return 0;
}
