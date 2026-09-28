#include "realloc.h"
#include "stack.h"
#include "error_print.h"

#include <cassert>

int StackReallocUp(Stack_t *const stk) {
    ASSERT_OK(stk)

    stk->capacity = stk->capacity * 2;
    stk->data = (stack_elem_t*) realloc(stk->data, stk->capacity);
    if (!stk->data) {
        stk->file = __FILE__;
        stk->line = __LINE__;
        return stk->error = REALLOC_ERR;
    }

    StackVerify(stk);

    return NO_ERR;
}
