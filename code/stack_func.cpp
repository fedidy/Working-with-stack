#include "../headers/stack.h"
#include "../headers/stack_func.h"
#include "../headers/error_print.h"
#include "../headers/realloc.h"

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>

Error_info StackCtor(Stack_t *const stk, const size_t capacity, const char *const stack_name) {
    PRINT_LOG("Started StackCtor\n");
    assert(stk);


    ON_DBG(
    if (!stack_name) {
        RETURN_ERR(STRUCT_NAME_ERR);
    }
    stk->stack_name = stack_name;
    stk->cr_info.file = __FILE__;
    stk->cr_info.func = __func__;
    stk->cr_info.line = __LINE__;
    )

    stk->capacity = capacity;
    stk->data = (stack_elem_t*) calloc(capacity, sizeof(stack_elem_t));
    if (!stk->data) {
        RETURN_ERR(CALLOC_ERR);
    }
    for (size_t i = 0; i < capacity; i++) {
        stk->data[i] = NO_DATA;
    }
    stk->size = 0;
    PRINT_LOG("Ended StackCtor\n");
    RETURN_NO_ERR;
}


Error_info StackPushArray(Stack_t *const stk, const stack_elem_t *const data, const size_t count) {
    PRINT_LOG("Started StackPushArray\n");
    PrintStackInfo(stk);
    ASSERT_OK(stk);

    if (!data) {
        RETURN_ERR(DATA_POINTER_ZERO_ERR);
    }

    for (size_t i = 0; i < count; i++) {
        PRINT_LOG("Before pushing element = " PRINT_DATA "\n", data[i]);
        ON_DBG(
        DataPrint(stk->data, stk->capacity);
        )

        Error_info err_info = StackPush(stk, data[i]);
        RETURN_ERROR_IF_GOT(err_info)
    }

    StackVerify(stk);

    RETURN_NO_ERR;
}

Error_info StackPush(Stack_t *const stk, const stack_elem_t elem) {
    ASSERT_OK(stk);
    Error_info err_info;

    if (stk->size == stk->capacity) {
        err_info = StackReallocUp(stk);
        RETURN_ERROR_IF_GOT(err_info);
        PRINT_LOG("Capacity after realloc = %zu\n", stk->capacity);
    }

    stk->data[stk->size] = elem;

    stk->size++;
    PRINT_LOG("End of push:size = %zu, capacity = %zu\n", stk->size, stk->capacity);

    RETURN_NO_ERR;
}

//remake
Error_info StackPop(Stack_t *const stk, stack_elem_t *const elem) {
    ASSERT_OK(stk)

    *elem = stk->data[stk->size - 1];
    stk->size--;

    if (stk->size == (stk->capacity / CAPACITY_DOWN_COEF)) {
        return StackReallocDown(stk);
    }
    RETURN_NO_ERR;
}

Error_info StackDtor(Stack_t *const stk) {
    ASSERT_OK(stk)

    ON_DBG(
    stk->cr_info.file = 0;
    stk->cr_info.func = 0;
    stk->cr_info.line = 0;
    stk->stack_name = 0;
    )
    free(stk->data);
    stk->size = 0;
    stk->capacity = 0;

    RETURN_NO_ERR;
}
