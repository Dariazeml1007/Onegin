#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <TXLib.h>
#include <sys\stat.h>

typedef enum
{
    SUCCESS_READ_FILE = 0,
    SUCCESS_WRITE_FILE = 0,
    SUCCESS_OPEN = 0,
    FAILED_OPEN_ERROR = 1,
    NOT_CLOSED = 1,
    NOT_READ = 1,
    NOT_WRITE = 1

} StatusFile;

typedef enum
{
    SUCCESS_DEFINE_SIZE = 0,
    SUCCESS = 0,
    STAT_FILE_ERROR = 1,
    MAKE_POINTERS_ERROR = 1,
    MAKE_TEXT_ERROR = 1,
    WRITE_POINTERS_ERROR = 1

} StatusOfRead;

typedef enum
{
    ALLOCCATION_ERROR = 1

} StatusPointer;

struct Text_t
{
    size_t size = 0;
    char *text = NULL;
    const char **massive_pointers = NULL;
    size_t count_strings = 0;
    size_t amount_of_read = 0;
    FILE *p_file_for_read = NULL;
    FILE *p_file_for_write = NULL;

};

int bubble_sort (const char **massive_pointers, size_t size);
void change (const char **massive_pointers1, const char **massive_pointers2);
int read_text_from_file (Text_t *onegin, const char *name_of_file);
int write_text_to_file (Text_t *onegin, const char *name_of_file);
int define_size_of_file (Text_t *onegin, const char *name_of_file);
int open_file (Text_t *onegin,const char *name_of_file);
int make_massive_pointers (Text_t *onegin);
int make_massive_text (Text_t *onegin);
int write_sort_onegin (Text_t *onegin, const char *name_of_file);
int write_origin_onegin(Text_t *onegin);

int main()
{
    struct Text_t onegin = {};

    if (read_text_from_file (&onegin, "Onegin.txt"))
    {
        printf ("Not read");
        return NOT_READ;
    }

    bubble_sort (onegin.massive_pointers, onegin.count_strings);

    if (write_text_to_file (&onegin, "SortOnegin.txt"))
    {
        printf("Not Write");
        return NOT_WRITE;
    }

    free(onegin.text);
    free(onegin.massive_pointers);

    return EXIT_SUCCESS;
}

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

int define_size_of_file (Text_t *onegin, const char *name_of_file)
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

    onegin -> massive_pointers = (const char**) calloc((onegin -> count_strings), sizeof(char*));

    if (onegin -> massive_pointers == NULL)
    {
        printf ("Allocation error");
        free(onegin -> text);
        fclose (onegin -> p_file_for_read);
        return ALLOCCATION_ERROR;
    }

    (onegin -> massive_pointers)[0] = onegin -> text;

    for (size_t i = 0, j = 1; (onegin ->text[i]) != '\0'; i++)
        if ((onegin -> text)[i] == '\n')
        {
            (onegin -> text)[i] = '\0';
            (onegin -> massive_pointers)[j++] = (onegin -> text) + i + 1;
        }

    return SUCCESS;

}

int read_text_from_file (Text_t *onegin, const char *name_of_file)
{
    assert(name_of_file);
    assert(onegin);

    if (open_file (onegin, name_of_file))
        return FAILED_OPEN_ERROR;

    if (define_size_of_file (onegin, name_of_file))
        return STAT_FILE_ERROR;

    if (make_massive_text (onegin))
        return MAKE_TEXT_ERROR;

    if (make_massive_pointers (onegin))
        return MAKE_POINTERS_ERROR;

    if (fclose (onegin -> p_file_for_read) == 0)
        return SUCCESS_READ_FILE;

    return NOT_CLOSED;


}

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

    if (write_origin_onegin (onegin))
        return WRITE_POINTERS_ERROR;

    if (fclose (onegin -> p_file_for_write) == 0)
        return SUCCESS_WRITE_FILE;

    return NOT_CLOSED;

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




