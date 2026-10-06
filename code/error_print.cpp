#include "../headers/stack.h"
#include "../headers/error_print.h"

#include <stdio.h>
#include <assert.h>
#include <stdio.h>

Error_info StackVerify(Stack_t *const stk) {
#if STACK_DEBUG > 0
    assert(stk);
    Error_info err = {};
    WRITE_ERR(err, NO_ERR)

    if (!stk->stack_name)
        WRITE_ERR(err, STRUCT_NAME_ERR)
    else if (!stk->cr_info.file)
        WRITE_ERR(err, FILE_NAME_ERR)
    else if (!stk->cr_info.func)
        WRITE_ERR(err, FUNC_NAME_ERR)
    else if (!stk->cr_info.line)
        WRITE_ERR(err, LINE_NUM_ERR)
    else if (stk->capacity == 0)
        WRITE_ERR(err, CAPACITY_ERR)
    else if (!stk->data)
        WRITE_ERR(err, DATA_POINTER_ZERO_ERR)

    return err;
#else
    (void)stk;
    return 0;
#endif
}


void PrintStackError(const Stack_t *const stk, const Error_info err) {
#if STACK_DEBUG > 0
    assert(stk);

    fprintf(stderr, "Error in stack named: %s:\n", stk->stack_name);

    if (err.error_code) {
        fprintf(stderr, "GOT NO ERROR\n");
    }

    fprintf(stderr, "Error code = %d\n", err.error_code);

    if (stk->stack_name)
        fprintf(stderr, "Error in stack named %s\n", stk->stack_name);
    else
        fprintf(stderr, "NO STRUCTURE NAME\n");

    fprintf(stderr, "Pointer to structure = [%p]\n", stk);

    fprintf(stderr, "Error info:\n");
    if (err.pos.file)
        fprintf(stderr, "Filename: %s\n", err.pos.file);
    else
        fprintf(stderr, "NO FILE NAME\n");
    if (err.pos.func)
        fprintf(stderr, "Func: %s\n", err.pos.func);
    else
        fprintf(stderr, "NO FUNCTION NAME\n");
    if (err.pos.line)
        fprintf(stderr, "Line number = %d\n", err.pos.line);
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

    DataPrint(stk->data, stk->capacity);
#else
    (void)stk;
#endif
}


void DataPrint(const stack_elem_t *const data, const size_t capacity) {
    assert(data);
    assert(capacity > 0);

    // через сравнение с size сделать
    for (size_t i = 0; i < capacity; i++) {
        if (data[i] == NO_DATA || isnan(data[i]))
            fprintf(stderr, "data[%zu] = " PRINT_DATA "\n", i, data[i]);
        else
            fprintf(stderr, "(*) data[%zu] = " PRINT_DATA "\n", i, data[i]);
    }
}


void PrintStackInfo(const Stack_t *const stk) {
#if STACK_DEBUG > 1
    assert(stk);

    PRINT_LOG("======================Stack_t %s======================\n", stk->stack_name);

    PRINT_LOG("Pointer to structure = [%p]\n", stk);

    PRINT_LOG("Error info:\n");
    PRINT_LOG("\tError code = %d\n", stk->err.err_code);
    PRINT_LOG("\tFilename: %s\n", stk->err.file);
    PRINT_LOG("\tFunc: %s\n", stk->err.func);
    PRINT_LOG("\tLine number = %d\n", stk->err.line);

    PRINT_LOG("Data creation info:\n");
    PRINT_LOG("\tFilename: %s\n", stk->cr_info.file);
    PRINT_LOG("\tFunc: %s\n", stk->cr_info.func);
    PRINT_LOG("\tLine number = %d\n", stk->cr_info.line);

    PRINT_LOG("Stack capacity = %zu\n", stk->capacity);
    PRINT_LOG("size = %zu\n", stk->size);

    LOG_DBG(
    DataPrint(stk->data, stk->capacity);
    )

    PRINT_LOG("======================Ended======================\n");
#else
    (void)stk;
#endif
}
