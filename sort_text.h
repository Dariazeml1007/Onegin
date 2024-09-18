#ifndef SORT_TEXT
#define SORT_TEXT

#include <data.h>

void bubble_sort (void *massive_pointers, size_t size, size_t l_size, int (* Compare_func)(const void*, const void*));
void change (void *massive_pointers1, void *massive_pointers2, size_t size);
int strcmp_rev (const void *s1, const void *s2);
int strcmp_ (const void *s1, const void *s2);

#endif
