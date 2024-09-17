#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <TXLib.h>
#include <sys\stat.h>
#include <stdbool.h>
#include <ctype.h>

#include "write.h"
#include "data.h"

int write_sort_onegin (Text_t *onegin, const char *name_of_file)
{
    assert(onegin);
    assert(name_of_file);

    onegin -> p_file_for_write = fopen (name_of_file, "w");
    if (onegin -> p_file_for_write  == NULL)
    {
        printf("Error opening file to write.\n");
        return FAILED_OPEN_ERROR;
    }

    for (size_t i = 0; i < (onegin -> count_strings); i++)
    {
        if (fputs((onegin -> massive_pointers)[i], onegin -> p_file_for_write) < 0)
            printf("not put\n");
        fputs("\n", onegin -> p_file_for_write);
    }
    fputs("\n", onegin -> p_file_for_write);

    return SUCCESS;
}

int write_origin_onegin (Text_t *onegin)
{
    assert(onegin);

    for (size_t i = 0; i < (onegin -> amount_of_read); i++)
    {
        if ((onegin -> text)[i] =='\0')
            fputs("\n", onegin -> p_file_for_write);
        else
            putc((onegin -> text)[i], onegin -> p_file_for_write);

    }
    return SUCCESS;
}

int write_text_to_file (Text_t *onegin, const char *name_of_file)
{

    assert(onegin);
    assert(name_of_file);

    if (write_sort_onegin (onegin, name_of_file))
        return WRITE_POINTERS_ERROR;

    // if (write_origin_onegin (onegin))
    //     return WRITE_POINTERS_ERROR;

    if (fclose (onegin -> p_file_for_write) == 0)
        return SUCCESS_WRITE_FILE;

    return NOT_CLOSED;

}

