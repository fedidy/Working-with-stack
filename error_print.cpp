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
int StackVerify(Stack_t *const stk) {
    return NO_ERR;
}
#endif


int StackError(const Stack_t *const stk) {
    assert(stk);

    switch (stk->error) {
        case NO_ERR: return 0;
        case CALLOC_ERR:
            fprintf(stderr, "CALLOC_ERR\n");
            Print_Error(stk);
            break;
        case PUSH_ERR:;
            fprintf(stderr, "PUSH_ERR\n");
            Print_Error(stk);
            break;
        default:
            fprintf(stderr, "UNKNOWN_ERR\n");
            Print_Error(stk);
            break;
    }
}

void Print_Error(const Stack_t *const stk) {
    assert(stk);

    if (stk->struct_name)
        fprintf(stderr, "Error in structure of type Stack_t named %s\n", stk->struct_name);
    else
        fprintf(stderr, "NO STRUCTURE NAME OF TYPE Stack_t\n");

    fprintf(stderr, "pointer to structure = [%p]\n", stk);

    if (stk->file)
            fprintf(stderr, "FILE = %s\n", stk->file);
    else
            fprintf(stderr, "NO FILE NAME\n");

    if (stk->line)
            fprintf(stderr, "FILE = %d\n", stk->line);
    else
            fprintf(stderr, "NO LINE NUMBER\n");

    fprintf(stderr, "stack capacity = %d\n", stk->capacity);
    if (stk->capacity > 0)
        StackPrint(stk);
    else
        fprintf(stderr, "CAPACITY IS BELOW ZERO\n");

    fprintf(stderr, "size = %d\n", stk->size);
}

void StackPrint(const Stack_t *const stk) {
    assert(stk->data);
    assert(stk->capacity > 0);

    for (int i = 0; i < stk->capacity; i++) {
        if (stk->data[i] == EDA)
            fprintf(stderr, "data[%d] = " PRINT_DATA "\n", i, stk->data[i]);
        else
            fprintf(stderr, "(*) data[%d] = " PRINT_DATA "\n", i, stk->data[i]);
    }
}
