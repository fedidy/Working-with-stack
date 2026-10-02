#include "stack.h"
#include "realloc.h"
#include "error_print.h"

int StackReallocUp(Stack_t *const stk) {
    ASSERT_OK(stk)

    stk->capacity = stk->capacity * CAPACITY_UP_COEF;
    stk->data = StackRecalloc(stk);
    if (stk->err.err_code)
        return stk->err.err_code;
    if (!stk->data) {
        RETURN_ERROR(stk->err, REALLOC_UP_ERR)
    }

    DataPrint(stack_working_log, stk->data, stk->capacity);

    return StackVerify(stk);
}

//rewrite
int StackReallocDown(Stack_t *const stk) {
    ASSERT_OK(stk)

    stk->capacity = stk->capacity / CAPACITY_DOWN_COEF;
    stk->data = (stack_elem_t*) realloc(stk->data, stk->capacity);
    if (!stk->data) {
        RETURN_ERROR(stk->err, REALLOC_DOWN_ERR)
    }

    return StackVerify(stk);
}


stack_elem_t* StackRecalloc(Stack_t *const stk) {
    assert(stk);

    stk->data = (stack_elem_t*) realloc(stk->data, sizeof(stack_elem_t) * stk->capacity);
    if (!stk->data) {
        stk->err.err_code = DATA_RECALLOC_ERR;
        return 0;
    }

    for (size_t i = stk->size + 1; i < stk->capacity; i++) {
        stk->data[i] = EDA;
    }

    return stk->data;
}

