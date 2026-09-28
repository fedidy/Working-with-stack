#define STACK_DEBUG 1

#include "stdio.h"
#include "cassert"
#include "stdlib.h"



typedef double stack_elem_t;
#define PRINT_DATA "%lg"
#include "stack.h"

#include "realloc.h"
#include "error_print.h"



#include "realloc.cpp"

int StackCtor(Stack_t *const stk, const int capacity);
int StackPush(const Stack_t *const stk, int count);
void PushElem(Stack_t *const stk, const stack_elem_t elem);



int main() {
    Stack_t stk1 {};
    StackCtor(&stk1, BASE_LENGTH);
    StackVerify(&stk1);

    StackPush(&stk1, 10);
    StackVerify(&stk1);

    double x = StackPop(&stk1);
    StackVerify(&stk1);

    StackDtor(&stk1);
}


int StackCtor(Stack_t *const stk, const int capacity) {
    assert(stk);
    assert(capacity > 0);

    stk->capacity = capacity;
    stk->data = (stack_elem_t*) calloc(capacity, sizeof(stack_elem_t));
    if (!stk->data) {
        stk->file = __FILE__;
        stk->line = __LINE__;
        return stk->error = CALLOC_ERR;
    }
    for (int i = 0; i < capacity; i++) {
        stk->data[i] = EDA;
    }
    stk->error = 0;
    stk->size = 0;
}





int StackPush(Stack_t *const stk, const int count) {
    ASSERT_OK(stk)

    stack_elem_t* tmp = (stack_elem_t*) calloc(count, sizeof(stack_elem_t));
    ReadElementsFromFile(tmp, count);

    for (int i = 0; i < count; i++) {
        PushElem(stk, tmp[i]);
    }

    free(tmp);
}

void PushElem(Stack_t *const stk, const stack_elem_t elem) {
    ASSERT_OK(stk)

    (stk->size)++;

    if (stk->size == stk->capacity)
        StackReallocUp(stk);

    stk->data[stk->size] = elem;
}
