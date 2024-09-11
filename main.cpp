#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <TXLib.h>
#include <sys\stat.h>

struct Text_t
{
    size_t size = 0;
    char *text = NULL;
    const char **massive_pointers = NULL;
    size_t count_strings = 0;

};

int bubble_sort (const char **massive_pointers, size_t size);
void change (const char **massive_pointers1, const char **massive_pointers2);
void ReadTextFromFile (Text_t *onegin, const char *name_of_file);
void WriteTextToFile (Text_t *onegin, const char *name_of_file);

int main()
{
    struct Text_t onegin = {};
    ReadTextFromFile (&onegin, "Onegin.txt");

    bubble_sort (onegin.massive_pointers, onegin.count_strings);

    WriteTextToFile (&onegin, "SortOnegin.txt");

    return EXIT_SUCCESS;
}

void ReadTextFromFile (Text_t *onegin, const char *name_of_file)
{
    FILE *pFile = fopen (name_of_file, "r");
    if (pFile == NULL)
    {
        printf("Not opened\n");
    }

    int ret;
    struct stat buf;

    if ((ret = stat(name_of_file, &buf)) != 0)
    {
        printf("stat failure error .%d", ret);
    }

    onegin -> size = buf.st_size;

    onegin -> text = (char*) calloc (onegin -> size / sizeof(char) + 1, sizeof(char));
    if (onegin -> text == NULL)
        printf ("Allocation error");
    size_t amount_of_read = 0;
    if ((amount_of_read = fread (onegin -> text, sizeof(char), onegin -> size, pFile)) == 0)
        printf ("Haven't read from file");


    for (size_t i = 0; (onegin -> text)[i] != '\0'; i++)
        if ((onegin -> text)[i] == '\n')
            (onegin -> count_strings) ++;

    onegin -> massive_pointers = (const char**) calloc((onegin -> count_strings), sizeof(char*));

    (onegin -> massive_pointers)[0] = onegin -> text;

    for (size_t i = 0, j = 1; (onegin ->text[i]) != '\0'; i++)
        if ((onegin -> text)[i] == '\n')
        {
            (onegin -> text)[i] = '\0';
            (onegin -> massive_pointers)[j++] = (onegin -> text) + i + 1;
        }

    fclose (pFile);


}

void WriteTextToFile (Text_t *onegin, const char *name_of_file)
{
    FILE *pFile1 = fopen (name_of_file, "w");
    if(pFile1 == NULL) {
        printf("Error opening file to write.\n");
    }

    for (size_t i = 0; i < (onegin -> count_strings); i++)
    {
        if (fputs((onegin ->massive_pointers)[i], pFile1) < 0)
            printf("not put\n");
        fputs("\n", pFile1);
    }


    fclose (pFile1);
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




