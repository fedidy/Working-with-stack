#ifndef REALLOC_H
#define REALLOC_H

Error_info StackReallocUp(Stack_t *const stk);
Error_info StackReallocDown(Stack_t *const stk);
Error_info StackRecalloc(Stack_t *const stk);

#endif
