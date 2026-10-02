#ifndef ERROR_PRINT
#define ERROR_PRINT

#include <stdio.h>
#include <assert.h>
#include <stdio.h>

#include "stack.h"
#include "error_print.h"
#include "mymath.h"

int StackVerify(Stack_t *const stk);
int PrintStackError(const Stack_t *const stk);
void DataPrint(FILE* output_file, const stack_elem_t *const data, const size_t capacity);
int PrintStackInfo(const Stack_t *const stk);

#endif
