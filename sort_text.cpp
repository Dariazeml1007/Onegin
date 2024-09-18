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

void change (void *massive_pointers1, void *massive_pointers2, size_t size)
{
    assert(massive_pointers1);
    assert(massive_pointers2);

    for (size_t i = 0; i < size; i++)
    {
        char temp = *((char *)massive_pointers1 + i);
        *((char *)massive_pointers1 + i) = *((char *)massive_pointers2 + i);
        *((char *)massive_pointers2 + i) = temp;
    }
}

int strcmp_ (const void *s1, const void *s2)
{
    assert (s1);
    assert (s2);

    const char *first_pointer = *(const char* const *)s1;
    const char *second_pointer = *(const char* const *)s2;

    for (; *first_pointer  != '\0' && *second_pointer != '\0'; first_pointer++, second_pointer++ )
    {
        while (!isalpha(*first_pointer) && *first_pointer != '\0')
            first_pointer++;
        while (!isalpha(*second_pointer) && *second_pointer != '\0')
            second_pointer++;
        int diff = toupper(*first_pointer) - toupper(*second_pointer);
        if (diff != 0)
            return diff;
    }
    return toupper(*first_pointer) - toupper(*second_pointer);
}

int strcmp_rev (const void *s1, const void *s2)
{
    assert (s1);
    assert (s2);
    const char *first_pointer = *(const char* const *)s1;
    const char *second_pointer = *(const char* const *)s2;

    while (*(first_pointer + 1) != '\0')
        (first_pointer)++;

    while (*(second_pointer + 1) != '\0')
        (second_pointer)++;

    for (;first_pointer != *(const char* const *)s1  &&
         second_pointer != *(const char* const *)s2;
         first_pointer--, second_pointer-- )
    {
        while (!isalpha(*first_pointer) && first_pointer != *(const char* const *)s1)
            first_pointer --;
        while (!isalpha(*second_pointer) && second_pointer != *(const char* const *)s2)
            second_pointer --;
        int diff = toupper(*first_pointer) - toupper(*second_pointer);
        if (diff != 0)
            return diff;

    }
    return toupper(*first_pointer) - toupper(*second_pointer);
}

void bubble_sort (void *massive_pointers, size_t size, size_t l_size, int (* Compare_func)(const void*, const void*))
{
    assert(massive_pointers);

    size_t temp_size = size;
    while (temp_size > 1)
    {
        for (size_t index = 1; index < temp_size; index++)
        {

            if (Compare_func(((char *)massive_pointers + index * l_size),
                ((char *)massive_pointers + (index - 1) * l_size)) < 0)
            {
                change(((char *)massive_pointers + index * l_size),
                       ((char *)massive_pointers + (index - 1) * l_size), l_size);
            }
        }
        temp_size--;
    }
}









