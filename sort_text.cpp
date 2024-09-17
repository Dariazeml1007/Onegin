#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <TXLib.h>
#include <sys\stat.h>
#include <stdbool.h>
#include <ctype.h>

#include "sort_text.h"
#include "data.h"

void change (const char **massive_pointers1, const char **massive_pointers2)
{
    assert(massive_pointers1);
    assert(massive_pointers2);
    assert(*massive_pointers1);
    assert(*massive_pointers2);

    const char *temp = *massive_pointers1;
    *massive_pointers1 = *massive_pointers2;
    *massive_pointers2 = temp;
}

int strcmp_ (const char *s1, const char *s2)
{
    assert (s1 != NULL);
    assert (s2 != NULL);

    for ( int i = 0; s1[i] != '\0' && s2[i] != '\0'; i++ )
    {
        if ( s1[i] != s2[i] )
            return s1[i] - s2[i];
    }
    return 0;
}

int strcmp_rev (const char *s1, const char *s2)
{
    assert (s1);
    assert (s2);
    const char *first_pointer = s1;
    const char *second_pointer = s2;

    while (*(first_pointer + 1) != '\0')
        (first_pointer)++;

    while (*(second_pointer + 1) != '\0')
        (second_pointer)++;

    for (;first_pointer != s1  && second_pointer != s2; first_pointer--, second_pointer-- )
    {
        while (!isalpha(*first_pointer) && first_pointer != s1)
            first_pointer --;
        while (!isalpha(*second_pointer) && second_pointer != s2)
            second_pointer --;
        int diff = toupper(*first_pointer) - toupper(*second_pointer);
        if (diff != 0)
            return diff;

    }
    return toupper(*first_pointer) - toupper(*second_pointer);
}

int bubble_sort (Text_t *onegin)
{
    assert(onegin);

    size_t temp_size = onegin  -> count_strings;
    while (temp_size > 1)
    {
        for (size_t index = 1; index < temp_size; index++)
        {

            if (strcmp_rev((onegin -> massive_pointers)[index], (onegin ->  massive_pointers)[index - 1]) < 0)
            {
                change(&(onegin -> massive_pointers)[index], &(onegin ->  massive_pointers)[index - 1]);
            }
        }
        temp_size--;
    }
    return 0;
}




