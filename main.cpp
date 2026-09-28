#define STACK_DEBUG 1

#include "stdio.h"
#include "cassert"
#include "stdlib.h"
#include <cmath>


typedef double stack_elem_t;
#define PRINT_DATA "%lg"
const double EDA = NAN;
#include "stack.h"

#include "realloc.h"
#include "error_print.h"
#include "file_reading.h"

const int BASE_LENGTH = 5;

#include "realloc.cpp"
#include "error_print.cpp"
#include "file_reading.cpp"
#include "mymath.cpp"


int StackCtor(Stack_t *const stk, const size_t capacity);
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
    StackCtor(&stk1, BASE_LENGTH);
    StackVerify(&stk1);


    stack_elem_t* data = {};
    ReadElemFromFile(data, 10, test_filename);
    StackPush(&stk1, data, 10);
    StackVerify(&stk1);

    stack_elem_t x = 0;
    StackPop(&stk1, &x);
    StackVerify(&stk1);

    StackDtor(&stk1);
}


int StackCtor(Stack_t *const stk, const size_t capacity) {
    assert(stk);
    if (capacity <= 0) {
        return stk->error = CAPACITY_CTOR_ERR;
    }

    stk->capacity = capacity;
    stk->data = (stack_elem_t*) calloc(capacity, sizeof(stack_elem_t));
    if (!stk->data) {
        RETURN_ERROR(stk, CALLOC_ERR);
    }
    for (size_t i = 0; i < capacity; i++) {
        stk->data[i] = EDA;
    }
    stk->error = 0;
    stk->size = 0;
    return NO_ERR;
}


int StackPush(Stack_t *const stk, const stack_elem_t *const data, const size_t count) {
    ASSERT_OK(stk)

    if (!data)
        return stk->error = DATA_POINTER_ZERO_ERR;

    for (size_t i = 0; i < count; i++) {
        if (PushElem(stk, data[i]))
            return stk->error;
    }

    return NO_ERR;
}

int PushElem(Stack_t *const stk, const stack_elem_t elem) {
    ASSERT_OK(stk)

    (stk->size)++;

    if (stk->size == stk->capacity)
        if (StackReallocUp(stk))
            return stk->error;

    stk->data[stk->size] = elem;
    return NO_ERR;
}


int StackPop(Stack_t *const stk, stack_elem_t *const elem) {
    ASSERT_OK(stk)

    *elem = stk->data[stk->size];
    stk->size--;

    if (stk->size == stk->capacity / CAPACITY_DOWN_COEF)
        if (StackReallocDown(stk))
            return stk->error;

    return NO_ERR;
}

int StackDtor(Stack_t *const stk) {
    ASSERT_OK(stk)

    stk->file = 0;
    stk->line = 0;
    stk->struct_name = 0;
    free(stk->data);
    stk->size = 0;
    stk->capacity = 0;
    stk->error = STACK_DESTROYED;

    return 0;
}
