#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "AsciiArtTool.h"


#define FILENAME_SIZE 100


char invert(char value)
{
    switch (value)
    {
        case ' ':
            value = '@';
            break;
        
        case '@':
            value = ' ';
            break;
    }
    
    return value;
}


int main(int argc, char **argv)
{
    bool inverted = false;
    bool encoded = false;

    for (int i = 1; i < argc - 2; i++)
    {
        char* flag = argv[i];

        if (strcmp(flag, "-i") == 0)
        {
            inverted = true;
        }

        if (strcmp(flag, "-e") == 0)
        {
            encoded = true;
        }
    }

    char* source = argv[argc - 2];

    char* target = argv[argc - 1];

    FILE* in_stream = fopen(source, "r");

    if (in_stream == NULL)
    {
        printf("\n%s File not found!\n", source);
        return 2;
    }
    
    FILE* out_stream = fopen(target, "w");

    if (out_stream == NULL)
    {
        printf("\n%s File not found!\n", target);
        return 4;
    }

    RLEList list = asciiArtRead(in_stream);

    if (inverted)
    {
        printf("inverted!");
        //RLEListMap(list, invert);
    }

    if (!encoded)
    {
        asciiArtPrint(list, out_stream);
    }
    else
    {
        printf("encoded!");
        //asciiArtPrintEncoded(list, out_stream);
    }

    fclose(in_stream);
    fclose(out_stream);

    RLEListDestroy(list);

    return 0;
}