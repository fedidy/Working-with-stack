#define STACK_DEBUG 1

#include "stdio.h"
#include "cassert"
#include "stdlib.h"



typedef double stack_elem_t;
#define PRINT_DATA "%lg"
#include "stack.h"

#define ASSERT_OK(stk) \
    assert((stk));\
    assert((stk)->error);\
    assert((stk)->data);\
    assert((stk)->capacity > 0);\
    assert((stk)->file);\
    assert((stk)->line);\
    assert((stk)->error);



const int BASE_LENGTH = 5;
const int EDA = 3802;

enum Stack_Errors {
    NO_ERR = 0,
    CALLOC_ERR,
    REALLOC_ERR,
    PUSH_ERR,
    STRUCT_NAME_ERR,
    FILE_NAME_ERR,
    LINE_NUM_ERR,
    CAPACITY_ERR
};

int StackCtor(Stack_t *const stk, const int capacity);
int StackVerify(Stack_t *const stk);
int StackError(const Stack_t *const stk);
void Print_Error(const Stack_t *const stk);
void StackPrint(const Stack_t *const stk);
int StackPush(const Stack_t *const stk, int count);
void PushElem(Stack_t *const stk, const stack_elem_t elem);
int StackRealloc(Stack_t *const stk);



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


#ifdef STACK_DEBUG
int StackVerify(Stack_t *const stk) {
    assert(stk);

    if (stk->error != 0)
        return StackError(stk);
    else { // дописать file и line
        if (stk->struct_name)
            stk->error = STRUCT_NAME_ERR;
        else if (stk->file)
            stk->error = FILE_NAME_ERR;
        else if (stk->line)
            stk->error = LINE_NUM_ERR;
        else if (stk->capacity <= 0)
            stk->error = CAPACITY_ERR;
    }

    if (stk->error != 0)
        return StackError(stk);
    else
        return NO_ERR;
}
#else
int StackVerify(Stack_t *const stk) {}
#endif


int StackError(const Stack_t *const stk) {
    assert(stk);

    switch (stk->error) {
        case NO_ERR: return 0;
        case CALLOC_ERR:
            printf("CALLOC_ERR\n");
            Print_Error(stk);
            break;
        case PUSH_ERR:;
            printf("PUSH_ERR\n");
            Print_Error(stk);
            break;
    }
    return 1;
}

void Print_Error(const Stack_t *const stk) {
    assert(stk);

    if (stk->struct_name)
        printf("Error in structure of type Stack_t named %s\n", stk->struct_name);
    else
        printf("NO STRUCTURE NAME OF TYPE Stack_t\n");

    printf("pointer to structure = [%p]", stk);

    if (stk->file)
            printf("FILE = %s\n", stk->file);
    else
            printf("NO FILE NAME\n");

    if (stk->line)
            printf("FILE = %d\n", stk->line);
    else
            printf("NO LINE NUMBER\n");

    printf("stack capacity = %d\n", stk->capacity);
    if (stk->capacity > 0)
        StackPrint(stk);
    else
        printf("CAPACITY IS BELOW ZERO\n");

    printf("size = %d\n", stk->size);

}

void StackPrint(const Stack_t *const stk) {
    assert(stk->data);
    assert(stk->capacity > 0);

    for (int i = 0; i < stk->capacity; i++) {
        if (stk->data[i] == EDA)
            printf("data[%d] = " PRINT_DATA "\n", i, stk->data[i]);
        else
            printf("(*) data[%d] = " PRINT_DATA "\n", i, stk->data[i]);
    }
}


int StackPush(Stack_t *const stk, const int count) {
    ASSERT_OK(stk)

    stack_elem_t* tmp = (stack_elem_t*) calloc(count, sizeof(stack_elem_t));

    for (int i = 0; i < count; i++) {
        PushElem(stk, tmp[i]);
    }

    free(tmp);
}

void PushElem(Stack_t *const stk, const stack_elem_t elem) {
    ASSERT_OK(stk)

    (stk->size)++;

    if (stk->size == stk->capacity)
        StackRealloc(stk);

    stk->data[stk->size] = elem;
}

int StackRealloc(Stack_t *const stk) {
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
