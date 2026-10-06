#include "../headers/stack.h"
#include "../headers/realloc.h"
#include "../headers/error_print.h"

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>

Error_info StackReallocUp(Stack_t *const stk) {
    ASSERT_OK(stk)

    stk->capacity = stk->capacity * CAPACITY_UP_COEF;
    Error_info err_info = StackRecalloc(stk);
    RETURN_ERROR_IF_GOT(err_info);
    ON_DBG(
    if (!stk->data) {
        RETURN_ERR(REALLOC_UP_ERR)
    })

    LOG_DBG(
    DataPrint(stk->data, stk->capacity);
    )

    return StackVerify(stk);
}

//rewrite
Error_info StackReallocDown(Stack_t *const stk) {
    ASSERT_OK(stk)

    stk->capacity = stk->capacity / CAPACITY_DOWN_COEF;
    stk->data = (stack_elem_t*) realloc(stk->data, stk->capacity);
    if (!stk->data) {
        RETURN_ERR(REALLOC_DOWN_ERR);
    }

    return StackVerify(stk);
}


Error_info StackRecalloc(Stack_t *const stk) {
    assert(stk);

    stk->data = (stack_elem_t*) realloc(stk->data, sizeof(stack_elem_t) * stk->capacity);
    if (!stk->data) {
        RETURN_ERR(DATA_RECALLOC_ERR);
    }

    for (size_t i = stk->size + 1; i < stk->capacity; i++) {
        stk->data[i] = NO_DATA;
    }

    RETURN_NO_ERR;
}
