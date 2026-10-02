#ifndef FILE_READING_H
#define FILE_READING_H

#include <stdlib.h>
#include <stdio.h>

int ReadElemFromFile(stack_elem_t *data, size_t count, const char *const test_filename, Error_info *err_inf);
int ScanFile(FILE* fp, stack_elem_t *data, size_t count, Error_info *err_inf);

#endif
