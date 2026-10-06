#ifndef STACK_FUNC_H
#define STACK_FUNC_H

Error_info StackCtor(Stack_t *const stk, const size_t capacity, const char *const stack_name);
Error_info StackPushArray(Stack_t *const stk, const stack_elem_t *const data, const size_t count);
Error_info StackPush(Stack_t *const stk, const stack_elem_t elem);
Error_info StackPop(Stack_t *const stk, stack_elem_t *const elem);
Error_info StackDtor(Stack_t *const stk);
//StackTop
//int CheckError(const Error_info err_inf);
//void StackDump(const Stack_t *const stk);

#endif
