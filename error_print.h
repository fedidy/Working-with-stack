#ifndef ERROR_PRINT
#define ERROR_PRINT

#include <cstdio>

int StackVerify(Stack_t *const stk);
int StackError(const Stack_t *const stk);
void PrintError(const Stack_t *const stk);
void DataPrint(const stack_elem_t *const data, const size_t capacity);

#endif
