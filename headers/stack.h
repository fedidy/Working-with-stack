#define STACK_DEBUG 1

#if STACK_DEBUG == 1
#define ON_DBG(...) __VA_ARGS__
#else
#define ON_DBG(...)
#endif


#ifndef STACK_H
#define STACK_H

#include <stddef.h>

struct Error_info {
    int err_code;
    const char* file;
    const char* func;
    int line;
};

struct Stack_t {
    ON_DBG(Error_info err;
    const char* creation_file;
    const char* creation_func;
    const char* creation_line;
    )
    char* struct_name;
    stack_elem_t* data;
    size_t size;
    size_t capacity;
};

enum Stack_Errors {
    NO_ERR = 0,
    STACK_DESTROYED,
    TEMP_ERR,
    CAPACITY_CTOR_ERR,
    CALLOC_ERR,
    DATA_POINTER_ZERO_ERR,
    COUNT_ERR,
    TEST_FILENAME_ERR,
    FILE_OPEN_ERR,
    FILE_POINTER_ZERO_ERR,
    INSUFFICIENT_ELEM_ERR,
    REALLOC_UP_ERR,
    REALLOC_DOWN_ERR,
    DATA_RECALLOC_ERR,
    PUSH_ERR,
    STRUCT_NAME_ERR,
    FILE_NAME_ERR,
    LINE_NUM_ERR,
    CAPACITY_ERR
};

#define ASSERT_OK(stk) {\
    assert((stk));\
    assert(!(stk)->err.err_code);\
    assert((stk)->data);\
    /*assert((stk)->capacity > 0);*/\
}

#define RETURN_ERROR(err_info, err) {\
(err_info).file = __FILE__;\
(err_info).func = __func__;\
(err_info).line = __LINE__;\
return (err_info).err_code = (err);\
}

const int CAPACITY_UP_COEF = 2;
const int CAPACITY_DOWN_COEF = 4;

#endif
