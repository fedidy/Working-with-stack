#ifndef ERROR_PRINT
#define ERROR_PRINT

Error_info StackVerify(Stack_t *const stk);
void PrintStackError(const Stack_t *const stk);
void DataPrint(const stack_elem_t *const data, const size_t capacity);
void PrintStackInfo(const Stack_t *const stk);

#endif
