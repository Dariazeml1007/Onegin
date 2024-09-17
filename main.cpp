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

int main()
{
    struct Text_t onegin = {};
    if (read_text_from_file (&onegin, "Onegin.txt"))
    {
        printf ("Not read");
        return NOT_READ;
    }

    bubble_sort (&onegin);

    if (write_text_to_file (&onegin, "SortOnegin.txt"))
    {
        printf("Not Write");
        return NOT_WRITE;
    }

    free(onegin.text);
    free(onegin.massive_pointers);

    return EXIT_SUCCESS;
}





