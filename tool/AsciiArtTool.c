#include "AsciiArtTool.h"
#include <stdlib.h>


RLEList asciiArtRead(FILE* in_stream)
{
    char value;

    RLEList list = RLEListCreate();

    while (fscanf(in_stream, "%c", &value) == 1)
    {
        if (RLEListAppend(list, value) != RLE_LIST_SUCCESS)
        {
            RLEListDestroy(list);

            return NULL;
        }
    }

    return list;
}


RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    if (list == NULL || out_stream == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    int size = RLEListSize(list);

    for (int i = 0; i < size; i++)
    {
        fprintf(out_stream, "%c", RLEListGet(list, i, NULL));
    }

    return RLE_LIST_SUCCESS;
}


RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if (list == NULL || out_stream == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    while (list != NULL)
    {
        fprintf(out_stream, "%c%d\n", list->val, list->num);

        list = list->next;
    }

    return RLE_LIST_SUCCESS;
}