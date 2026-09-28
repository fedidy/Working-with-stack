#ifdef STACK_DEBUG // поменять на ifdef
#define ON_DBG(file, line) (file); (line)
#else
#define ON_DBG(file, line)
#endif


#ifndef STACK_H
#define STACK_H

    //ON_DBG(__FILE__, __LINE__);
struct Stack_t {
    const char* file;
    int line;
    char* struct_name;
    stack_elem_t* data;
    int size;
    int capacity;
    int error;
};

enum Stack_Errors {
    NO_ERR = 0,
    CAPACITY_CTOR_ERR,
    CALLOC_ERR,
    REALLOC_UP_ERR,
    REALLOC_DOWN_ERR,
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

#define RETURN_ERROR(stk, err)\
(stk)->file = __FILE__;\
(stk)->line = __LINE__;\
return (stk)->error = (err);

const int CAPACITY_UP_COEF = 2;
const int CAPACITY_DOWN_COEF = 4;

#endif
