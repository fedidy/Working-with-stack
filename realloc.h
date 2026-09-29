#ifndef REALLOC_H
#define REALLOC_H

#include <cstddef>
#include <cassert>

int StackReallocUp(Stack_t *const stk);
int StackReallocDown(Stack_t *const stk);
stack_elem_t* StackRecalloc(Stack_t *const stk);

#endif
