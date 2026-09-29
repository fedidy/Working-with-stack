#ifdef STACK_DEBUG
#define ON_DBG(...) __VA_ARGS__
#else
#define ON_DBG(...)
#endif


#ifndef STACK_H
#define STACK_H

//ON_DBG(__FILE__, __LINE__);

/*
struct error_data {
    const char* file;
    int line;
    int error;
};
*/
#include <cstddef>

struct Stack_t {
    const char* file;
    int line;
    int error;
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

#define ASSERT_OK(stk) \
    assert((stk));\
    assert(!(stk)->error);\
    assert((stk)->data);\
    assert((stk)->capacity > 0);

#define RETURN_ERROR(stk, err) {\
(stk)->file = __FILE__;\
(stk)->line = __LINE__;\
return (stk)->error = (err);}

const int CAPACITY_UP_COEF = 2;
const int CAPACITY_DOWN_COEF = 4;

#endif
