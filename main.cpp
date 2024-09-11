#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <TXLib.h>
#include <sys\stat.h>

int bubble_sort (const char **massive_pointers, size_t size);
void change (const char **massive_pointers1, const char **massive_pointers2);

int main()
{
    FILE *pFile = fopen ("Onegin.txt", "r");
    if (pFile == NULL)
    {
        printf("Not opened\n");
        return EXIT_FAILURE;
    }

    fseek (pFile, 0, SEEK_END);
    size_t size = ftell(pFile);
    fseek (pFile, 0, SEEK_SET);

    char *text = (char*) calloc (size / sizeof(char) + 1, sizeof(char));
    if (text == NULL)
        printf ("Allocation error");

    if (fread (text, sizeof(char), size, pFile) == 0)
        printf ("Haven't read from file");

    size_t count = 0;
    for (size_t i = 0; text[i] != '\0'; i++)
        if (text[i] == '\n')
            count ++;

    const char **massive_pointers = (const char**) calloc(count, sizeof(char*));

    massive_pointers[0] = text;

    for (size_t i = 0, j = 1; text[i] != '\0'; i++)
        if (text[i] == '\n')
        {
            text[i] = '\0';
            massive_pointers[j++] = text + i + 1;
        }

    bubble_sort (massive_pointers, count);

    FILE *pFile1 = fopen ("SortOnegin.txt", "w");
    if(pFile1 == NULL) {
        printf("Error opening file to write.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++)
    {
        if (fputs(massive_pointers[i], pFile1) < 0)
            printf("not put\n");
        fputs("\n", pFile1);
    }

    fclose (pFile);
    fclose (pFile1);
    return EXIT_SUCCESS;
}


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

int bubble_sort (const char **massive_pointers, size_t size)
{
    assert(massive_pointers);
    assert(*massive_pointers);

    size_t n = size;
    for (size_t j = 0; j < size - 1; j++)
    {
        for (size_t i = 1; i < n; i++)

            if (strcmp(massive_pointers[i], massive_pointers[i - 1]) < 0)
            {
                change(&massive_pointers[i], &massive_pointers[i - 1]);
            }
        n--;
    }
    return 0;
}




