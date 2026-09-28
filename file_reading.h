#ifndef FILE_READING_H
#define FILE_READING_H

#include <cstdio>

int ReadElemFromFile(stack_elem_t *data, size_t count, const char *const test_filename);
int ScanFile(FILE* fp, stack_elem_t *data, size_t count);

#endif
