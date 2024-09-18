#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <TXLib.h>
#include <sys\stat.h>
#include <stdbool.h>
#include <ctype.h>

#include "data.h"
#include "write.h"
#include "sort_text.h"
#include "open_and_read.h"

const char* INPUT_FILE_NAME = "Onegin.txt";
const char* OUTPUT_FILE_NAME = "SortOnegin.txt";

int main()
{
    struct Text_t onegin = {};
    if (read_text_from_file (&onegin, INPUT_FILE_NAME))
    {
        printf ("Not read");
        return NOT_READ;
    }

    bubble_sort (onegin.massive_pointers, onegin.count_strings, sizeof(char *), strcmp_);

    if (write_text_to_file (&onegin, OUTPUT_FILE_NAME))
    {
        printf("Not Write");
        return NOT_WRITE;
    }

    free(onegin.text);
    free(onegin.massive_pointers);

    return EXIT_SUCCESS;
}





