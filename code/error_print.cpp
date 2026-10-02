#include "error_print.h"

#if STACK_DEBUG == 1
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


#if STACK_DEBUG > 0
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
#else
int PrintStackError(const Stack_t *const stk) {return 0;}
#endif


void DataPrint(FILE* output_file, const stack_elem_t *const data, const size_t capacity) {
    assert(data);
    assert(capacity > 0);

    for (size_t i = 0; i < capacity; i++) {
        if (CompareDouble(data[i], DATA_ZERO))
            fprintf(output_file, "data[%zu] = " PRINT_DATA "\n", i, data[i]);
        else
            fprintf(output_file, "(*) data[%zu] = " PRINT_DATA "\n", i, data[i]);
    }
}


#ifdef LOG_DBG
int PrintStackInfo(const Stack_t *const stk) {
    assert(stk);

    PRINT_LOG("======================Stack_t %s======================\n", stk->stack_name);

    PRINT_LOG("Pointer to structure = [%p]\n", stk);

    PRINT_LOG("Error info:\n");
    PRINT_LOG("    Error code = %d\n", stk->err.err_code);
    PRINT_LOG("    Filename: %s\n", stk->err.file);
    PRINT_LOG("    Func: %s\n", stk->err.func);
    PRINT_LOG("    Line number = %d\n", stk->err.line);

    PRINT_LOG("Data creation info:\n");
    PRINT_LOG("    Filename: %s\n", stk->cr_info.file);
    PRINT_LOG("    Func: %s\n", stk->cr_info.func);
    PRINT_LOG("    Line number = %d\n", stk->cr_info.line);

    PRINT_LOG("Stack capacity = %zu\n", stk->capacity);
    PRINT_LOG("size = %zu\n", stk->size);

    LOG_DBG(
    DataPrint(stack_working_log, stk->data, stk->capacity);
    )

    PRINT_LOG("======================Ended======================\n");

    ON_DBG(
    return stk->err.err_code;
    )
    return 0; //ебаные варнинги некрасиво выглядят
}
#else
int PrintStackInfo(const Stack_t *const stk) {
    return 0;
}
#endif

