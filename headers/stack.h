#if STACK_DEBUG > 0
#define ON_DBG(...) __VA_ARGS__
#else
#define ON_DBG(...)
#endif

#if STACK_DEBUG > 1
#define LOG_DBG(...) __VA_ARGS__
#define PRINT_LOG(...) fprintf(stack_working_log, __VA_ARGS__)
#else
#define LOG_DBG(...)
#define PRINT_LOG(...)
#endif


#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef double stack_elem_t;
#define PRINT_DATA "%lg"
const double DATA_ZERO = NAN;

struct Error_info {
    int err_code;
    const char* file;
    const char* func;
    int line;
};

struct Creation_info {
    const char* file;
    const char* func;
    int line;
};

struct Stack_t {
    ON_DBG(
    Error_info err;
    Creation_info cr_info;
    )
    const char* stack_name;
    stack_elem_t* data;
    size_t size;
    size_t capacity;
};

enum Stack_Errors {
    NO_ERR = 0,
    UNKNOWN_ERR,
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
    FUNC_NAME_ERR,
    LINE_NUM_ERR,
    CAPACITY_ERR
};

#define ASSERT_OK(stk) {\
    assert((stk));\
    assert((stk)->data);\
    ON_DBG(\
    assert((stk)->err.err_code == 0);\
    )\
    /*assert((stk)->capacity > 0);*/\
}

#if STACK_DEBUG > 0
#define RET_ERR
#define RETURN_ERROR(err_info, err) {\
(err_info).file = __FILE__;\
(err_info).func = __func__;\
(err_info).line = __LINE__;\
return (err_info).err_code = (err);\
}
#else
#define RETURN_ERROR(err_info, err) {abort();}
#endif

const int CAPACITY_UP_COEF = 2;
const int CAPACITY_DOWN_COEF = 4;

#endif
