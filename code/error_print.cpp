#include "error_print.h"

#ifdef STACK_DEBUG
int StackVerify(Stack_t *const stk) {
    assert(stk);

    if (stk->err.err_code != 0)
        return StackError(stk);
    else {
        if (stk->struct_name)
            stk->err.err_code = STRUCT_NAME_ERR;
        else if (stk->file)
            stk->err.err_code = FILE_NAME_ERR;
        else if (stk->line)
            stk->err.err_code = LINE_NUM_ERR;
        else if (stk->capacity == 0)
            stk->err.err_code = CAPACITY_ERR;
    }

    if (stk->err.err_code != 0)
        return StackError(stk);
    else
        return NO_ERR;
}
#else
int StackVerify(Stack_t *const stk) {
    return NO_ERR;
}
#endif


int PrintStackError(const Stack_t *const stk) {
    assert(stk);

    if (!stk->err.err_code) {
        fprintf(stderr, "GOT NO ERROR\n");
    }

    fprintf(stderr, "Error code = %d\n", stk->err.err_code);

    if (stk->struct_name)
        fprintf(stderr, "Error in structure named %s\n", stk->struct_name);
    else
        fprintf(stderr, "NO STRUCTURE NAME\n");

    fprintf(stderr, "Pointer to structure = [%p]\n", stk);

    if (stk->err.file)
            fprintf(stderr, "FILE = %s\n", stk->err.file);
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

    return stk->err.err_code;
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
