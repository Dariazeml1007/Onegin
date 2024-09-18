#ifndef TEXT_DATA
#define TEXT_DATA

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


#endif
