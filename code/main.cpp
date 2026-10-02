#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

//???????????????


#include "stack.h"

LOG_DBG(FILE *stack_working_log = fopen("stack_working.log", "w");)
#include "realloc.h"
#include "error_print.h"
#include "file_reading.h"

const int BASE_LENGTH = 5;

#include "realloc.cpp"
#include "error_print.cpp"
#include "file_reading.cpp"
#include "mymath.cpp"

int StackCtor(Stack_t *const stk, const size_t capacity, const char *const stack_name);
int StackPush(Stack_t *const stk, const stack_elem_t *const data, const size_t count);
int PushElem(Stack_t *const stk, const stack_elem_t elem);
int StackPop(Stack_t *const stk, stack_elem_t *const elem);
int StackDtor(Stack_t *const stk);


int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "NO test_filename: argc = %d\n", argc);
        return TEST_FILENAME_ERR;
    }
    char* test_filename = argv[1];
    Stack_t stk1 {};
    StackCtor(&stk1, BASE_LENGTH, "stk1");
    StackVerify(&stk1);

    size_t count = 10;
    stack_elem_t* data = (stack_elem_t*) calloc(count, sizeof(stack_elem_t));
    if (!data) {
        fprintf(stderr, "CAN'T ALLOCATE MEMORY in %s:%d\n", __FILE__, __LINE__);
        return CALLOC_ERR;
    }

    Error_info err_inf= {};
    ReadElemFromFile(data, count, test_filename, &err_inf);
    PRINT_LOG("Data after reading from %s\n", test_filename);
    LOG_DBG(DataPrint(stack_working_log, data, count));

    StackPush(&stk1, data, count);

    stack_elem_t x = 0;
    StackPop(&stk1, &x);

    StackDtor(&stk1);
}


int StackCtor(Stack_t *const stk, const size_t capacity, const char *const stack_name) {
    assert(stk);
    if (capacity <= 0) {
        #ifdef RET_ERR
        RETURN_ERROR(stk->err, CAPACITY_CTOR_ERR)
        #endif
    }
    if (!stack_name) {
        #ifdef RET_ERR
        RETURN_ERROR(stk->err, STRUCT_NAME_ERR)
        #endif
    }

    stk->stack_name = stack_name;

    ON_DBG(
    stk->cr_info.file = __FILE__;
    stk->cr_info.func = __func__;
    stk->cr_info.line = __LINE__;
    )

    stk->capacity = capacity;
    stk->data = (stack_elem_t*) calloc(capacity, sizeof(stack_elem_t));
    if (!stk->data) {
        #ifdef RET_ERR
        RETURN_ERROR(stk->err, CALLOC_ERR);
        #endif
    }
    for (size_t i = 0; i < capacity; i++) {
        stk->data[i] = DATA_ZERO;
    }
    stk->size = 0;
    #ifdef RET_ERR
    RETURN_ERROR(stk->err, NO_ERR)
    #endif
    return 0;
}


int StackPush(Stack_t *const stk, const stack_elem_t *const data, const size_t count) {
    PRINT_LOG("Started StackPush\n");
    ON_DBG(
    PrintStackInfo(stk);
    )
    ASSERT_OK(stk)

    if (!data) {
        #ifdef RET_ERR
        RETURN_ERROR(stk->err, DATA_POINTER_ZERO_ERR);
        #endif
    }

    for (size_t i = 0; i < count; i++) {
        ON_DBG(
        PRINT_LOG("Before pushing element = " PRINT_DATA "\n", data[i]);
        LOG_DBG(DataPrint(stack_working_log, stk->data, stk->capacity);)
        )
        if (PushElem(stk, data[i])) {
            #ifdef RET_ERR
            RETURN_ERROR
            (stk->err, err_code);
            #endif
        }
    }

    StackVerify(stk);

    return NO_ERR;
}

int PushElem(Stack_t *const stk, const stack_elem_t elem) {
    ASSERT_OK(stk)

    if (stk->size + 1 == stk->capacity) {
        if (StackReallocUp(stk)) {
            ON_DBG(
            return stk->err.err_code;
            )
        }
        PRINT_LOG("capacity after realloc = %zu\n", stk->capacity);
    }
    PRINT_LOG("capacity new = %zu\n", stk->capacity);

    stk->data[stk->size] = elem;

    stk->size++;
    PRINT_LOG("size = %zu, capacity = %zu\n", stk->size, stk->capacity);


    return NO_ERR;
}

//remake
int StackPop(Stack_t *const stk, stack_elem_t *const elem) {
    ASSERT_OK(stk)

    *elem = stk->data[stk->size];
    stk->size--;

    if (stk->size == stk->capacity / CAPACITY_DOWN_COEF)
        if (StackReallocDown(stk)) {
            ON_DBG(
            return stk->err.err_code;
            )
        }

    return NO_ERR;
}

int StackDtor(Stack_t *const stk) {
    ASSERT_OK(stk)

    ON_DBG(
    stk->cr_info.file = 0;
    stk->cr_info.func = 0;
    stk->cr_info.line = 0;

    stk->err.file = 0;
    stk->err.func = 0;
    stk->err.line = 0;

    stk->err.err_code = STACK_DESTROYED;
    )

    stk->stack_name = 0;
    free(stk->data);
    stk->size = 0;
    stk->capacity = 0;

    return 0;
}
