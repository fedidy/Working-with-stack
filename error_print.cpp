#include "stack.h"
#include "error_print.h"

#include <cstdio>
#include <cassert>


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
