#ifndef READ_TEXT
#define READ_TEXT

#include <data.h>

int read_text_from_file (Text_t *onegin, const char *name_of_file);
int make_massive_pointers (Text_t *onegin);
int make_massive_text (Text_t *onegin);
int get_size_of_file (Text_t *onegin, const char *name_of_file);
int open_file (Text_t *onegin,const char *name_of_file);

#endif
