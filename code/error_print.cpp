#include "error_print.h"

#ifdef STACK_DEBUG
int StackVerify(Stack_t *const stk) {
    assert(stk);

    if (stk->err.err_code != 0)
        return PrintStackError(stk);
    else {
        if (!stk->stack_name)
            RETURN_ERROR(stk->err, STRUCT_NAME_ERR)
        else if (!stk->cr_info.file)
            RETURN_ERROR(stk->err, FILE_NAME_ERR)
        else if (!stk->cr_info.func)
            RETURN_ERROR(stk->err, FUNC_NAME_ERR)
        else if (!stk->cr_info.line)
            RETURN_ERROR(stk->err, LINE_NUM_ERR)
        else if (stk->capacity == 0)
            RETURN_ERROR(stk->err, CAPACITY_ERR)
        else if (!stk->data)
            RETURN_ERROR(stk->err, DATA_POINTER_ZERO_ERR)
    }

    if (stk->err.err_code != 0)
        return PrintStackError(stk);
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

    fprintf(stderr, "Error in stack named: %s:\n", stk->stack_name);

    if (!stk->err.err_code) {
        fprintf(stderr, "GOT NO ERROR\n");
    }

    fprintf(stderr, "Error code = %d\n", stk->err.err_code);

    if (stk->stack_name)
        fprintf(stderr, "Error in stack named %s\n", stk->stack_name);
    else
        fprintf(stderr, "NO STRUCTURE NAME\n");

    fprintf(stderr, "Pointer to structure = [%p]\n", stk);

    fprintf(stderr, "Error info:\n");
    if (stk->err.file)
        fprintf(stderr, "Filename: %s\n", stk->err.file);
    else
        fprintf(stderr, "NO FILE NAME\n");
    if (stk->err.func)
        fprintf(stderr, "Func: %s\n", stk->err.func);
    else
        fprintf(stderr, "NO FUNCTION NAME\n");
    if (stk->err.line)
        fprintf(stderr, "Line number = %d\n", stk->err.line);
    else
        fprintf(stderr, "NO LINE NUMBER\n");

    fprintf(stderr, "Data creation info:\n");
    if (stk->cr_info.file)
            fprintf(stderr, "Filename: %s\n", stk->cr_info.file);
    else
            fprintf(stderr, "NO FILE NAME\n");
    if (stk->cr_info.func)
            fprintf(stderr, "Func: %s\n", stk->cr_info.func);
    else
            fprintf(stderr, "NO FUNCTION NAME\n");
    if (stk->cr_info.line)
            fprintf(stderr, "Line number = %d\n", stk->cr_info.line);
    else
            fprintf(stderr, "NO LINE NUMBER\n");

    fprintf(stderr, "Stack capacity = %zu\n", stk->capacity);
    if (stk->capacity == 0)
        fprintf(stderr, "STACK CAPACITY IS ZERO\n");

    fprintf(stderr, "size = %zu\n", stk->size);

    DataPrint(stderr, stk->data, stk->capacity);



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


int PrintStackInfo(const Stack_t *const stk) {
    assert(stk);

    fprintf(stack_working_log, "======================Stack_t %s======================\n", stk->stack_name);

    fprintf(stack_working_log, "Pointer to structure = [%p]\n", stk);

    fprintf(stack_working_log, "Error info:\n");
    fprintf(stack_working_log, "   Error code = %d\n", stk->err.err_code);
    fprintf(stack_working_log, "   Filename: %s\n", stk->err.file);
    fprintf(stack_working_log, "   Func: %s\n", stk->err.func);
    fprintf(stack_working_log, "    Line number = %d\n", stk->err.line);

    fprintf(stack_working_log, "Data creation info:\n");
        fprintf(stack_working_log, "   Filename: %s\n", stk->cr_info.file);
        fprintf(stack_working_log, "   Func: %s\n", stk->cr_info.func);
        fprintf(stack_working_log, "   Line number = %d\n", stk->cr_info.line);

    fprintf(stack_working_log, "Stack capacity = %zu\n", stk->capacity);
    fprintf(stack_working_log, "size = %zu\n", stk->size);

    DataPrint(stack_working_log, stk->data, stk->capacity);

    fprintf(stack_working_log, "======================Ended======================\n");

    return stk->err.err_code;
}
