#include "realloc.h"
#include "stack.h"
#include "error_print.h"

#include <cassert>

int StackReallocUp(Stack_t *const stk) {
    ASSERT_OK(stk)

    stk->capacity = stk->capacity * CAPACITY_UP_COEF;
    stk->data = (stack_elem_t*) realloc(stk->data, stk->capacity);
    if (!stk->data) {
        RETURN_ERROR(stk, REALLOC_UP_ERR)
    }

    return StackVerify(stk);
}

int StackReallocDown(Stack_t *const stk) {
    ASSERT_OK(stk)

    stk ->capacity = stk->capacity / CAPACITY_DOWN_COEF;
    stk->data = (stack_elem_t*) realloc(stk->data, stk->capacity);
    if (!stk->data) {
        RETURN_ERROR(stk, REALLOC_DOWN_ERR)
    }
}
