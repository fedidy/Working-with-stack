#include "stack.h"
#include "error_print.h"
#include "mymath.h"

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
        else if (stk->capacity == 0)
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

    /*
    switch (stk->error) {
        case NO_ERR: return 0;

        case CALLOC_ERR: case P
            fprintf(stderr, "CALLOC_ERR\n");
            PrintError(stk); break;
        case PUSH_ERR:
            fprintf(stderr, "PUSH_ERR\n");
            PrintError(stk); break;
        default:
            fprintf(stderr, "UNKNOWN_ERR\n");
            PrintError(stk); break;
    }
    */

    if (!stk->error)
        return NO_ERR;
    fprintf(stderr, "Error code = %d\n", stk->error);
    PrintError(stk);

    return stk->error;


    /*
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

    fprintf(stderr, "stack capacity = %zu\n", stk->capacity);
    if (stk->capacity > 0)
        DataPrint(stderr, stk->data, stk->capacity);
    else
        fprintf(stderr, "CAPACITY IS BELOW ZERO\n");

    fprintf(stderr, "size = %zu\n", stk->size);
    */
}


void PrintError(const Stack_t *const stk) {
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
            fprintf(stderr, "LINE = %d\n", stk->line);
    else
            fprintf(stderr, "NO LINE NUMBER\n");

    fprintf(stderr, "stack capacity = %zu\n", stk->capacity);
    if (stk->capacity > 0)
        DataPrint(stderr, stk->data, stk->capacity);
    else
        fprintf(stderr, "CAPACITY IS BELOW ZERO\n");

    fprintf(stderr, "size = %zu\n", stk->size);

}


void DataPrint(FILE* output_file, const stack_elem_t *const data, const size_t capacity) {
    assert(data);
    assert(capacity > 0);

    for (size_t i = 0; i < capacity; i++) {
        if (CompareDouble(data[i], EDA))
            fprintf(output_file, "data[%zu] = " PRINT_DATA "\n", i, data[i]);
        else
            fprintf(output_file, "(*) data[%zu] = " PRINT_DATA "\n", i, data[i]);
    }
}
