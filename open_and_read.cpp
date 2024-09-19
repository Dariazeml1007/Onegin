#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <TXLib.h>
#include <sys\stat.h>
#include <stdbool.h>
#include <ctype.h>

#include "open_and_read.h"
#include "data.h"

int open_file (Text_t *onegin, const char *name_of_file)
{
    assert(name_of_file);
    assert(onegin);
    onegin -> p_file_for_read = fopen (name_of_file, "r");
    if (onegin -> p_file_for_read == NULL)
    {
        printf("Not opened\n");
        return FAILED_OPEN_ERROR;
    }
    return SUCCESS_OPEN;
}

int get_size_of_file (Text_t *onegin, const char *name_of_file)
{
    assert(name_of_file);
    assert(onegin);
    int info_of_file = 0;
    struct stat buffer;
    if ((info_of_file = stat(name_of_file, &buffer)) != 0)
    {
        printf("stat failure error .%d\n", info_of_file);
        fclose (onegin -> p_file_for_read);
        return STAT_FILE_ERROR;
    }
    onegin -> size = buffer.st_size;
    return SUCCESS_DEFINE_SIZE;
}

int make_massive_text (Text_t *onegin)
{
    assert(onegin);
    onegin -> text = (char*) calloc (onegin -> size + 1, sizeof(char));
    if (onegin -> text == NULL)
    {
        printf ("Allocation error");
        return ALLOCCATION_ERROR;
    }
    if ((onegin -> amount_of_read = fread (onegin -> text, sizeof(char), onegin -> size, onegin -> p_file_for_read)) == 0)
    {
      printf ("Haven't read from file");
      free(onegin -> text);
      fclose (onegin -> p_file_for_read);
      return NOT_READ;
    }
    for (size_t i = onegin -> amount_of_read; i < onegin -> size; i++)
        (onegin -> text)[i] = '\0';

    for (size_t i = 0; onegin -> text[i] != '\0'; i++)
        if ((onegin -> text)[i] == '\n')
            (onegin -> count_strings)++;
    return SUCCESS;
}

int make_massive_pointers (Text_t *onegin)
{
    assert(onegin);
    (onegin -> massive_struct) = (String_pointers *) calloc ((onegin -> count_strings), sizeof(String_pointers));
    if (onegin -> massive_struct == NULL)
    {
        printf ("Allocation error");
        free(onegin -> text);
        fclose (onegin -> p_file_for_read);
        return ALLOCCATION_ERROR;
    }

    (onegin -> massive_struct)[0].start_str = onegin -> text;
    size_t i = 0;
    for (size_t j = 1; (onegin ->text[i]) != '\0'; i++)
        if ((onegin -> text)[i] == '\n')
        {
            (onegin -> massive_struct)[j - 1].end_str = (onegin -> text) + i - 1;
            if (onegin -> text[i + 1] != '\0')
                (onegin -> massive_struct)[j++].start_str = (onegin -> text) + i + 1;
            (onegin -> text)[i] = '\0';
        }
    (onegin -> massive_struct)[onegin -> count_strings - 1].end_str = (onegin -> text) + i - 2;

    return SUCCESS;
}

int read_text_from_file (Text_t *onegin, const char *name_of_file)
{
    assert(name_of_file);
    assert(onegin);
    if (open_file (onegin, name_of_file))
        return FAILED_OPEN_ERROR;
    if (get_size_of_file (onegin, name_of_file))
        return STAT_FILE_ERROR;
    if (make_massive_text (onegin))
        return MAKE_TEXT_ERROR;
    if (make_massive_pointers (onegin))
        return MAKE_POINTERS_ERROR;
    if (fclose (onegin -> p_file_for_read) == 0)
        return SUCCESS_READ_FILE;
    return NOT_CLOSED;
}
