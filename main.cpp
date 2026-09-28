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


int StackCtor(Stack_t *const stk, const int capacity);
int StackPush(const Stack_t *const stk, int count);
int PushElem(Stack_t *const stk, const stack_elem_t elem);
int StackPop(Stack_t *const stk, stack_elem_t *elem);


int main() {
    Stack_t stk1 {};
    StackCtor(&stk1, BASE_LENGTH);
    StackVerify(&stk1);

    StackPush(&stk1, 10);
    StackVerify(&stk1);

    stack_elem_t x = 0;
    StackPop(&stk1, &x);
    StackVerify(&stk1);

    StackDtor(&stk1);
}


int StackCtor(Stack_t *const stk, const int capacity) {
    assert(stk);
    if (capacity <= 0) {
        return stk->error = CAPACITY_CTOR_ERR;
    }

    stk->capacity = capacity;
    stk->data = (stack_elem_t*) calloc(capacity, sizeof(stack_elem_t));
    if (!stk->data) {
        RETURN_ERROR(stk, CALLOC_ERR);
    }
    for (int i = 0; i < capacity; i++) {
        stk->data[i] = EDA;
    }
    stk->error = 0;
    stk->size = 0;
    return NO_ERR;
}


int StackPush(Stack_t *const stk, const int count) {
    ASSERT_OK(stk)

    stack_elem_t* tmp = (stack_elem_t*) calloc(count, sizeof(stack_elem_t));
    ReadElementsFromFile(tmp, count);

    for (int i = 0; i < count; i++) {
        if (PushElem(stk, tmp[i]))
            return stk->error;
    }

    free(tmp);
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


int StackPop(Stack_t *const stk, stack_elem_t *elem) {
    ASSERT_OK(stk)

    *elem = stk->data[stk->size];
    stk->size--;

    if (stk->size == stk->capacity / CAPACITY_DOWN_COEF)
        if (StackReallocDown(stk))
            return stk->error;

    return NO_ERR;
}
