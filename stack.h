#ifdef STACK_DEBUG // поменять на ifdef
#define ON_DBG(file, line) (file); (line)
#else
#define ON_DBG(file, line)
#endif


#ifndef STACK_H
#define STACK_H // вынести в main

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
    CALLOC_ERR,
    REALLOC_ERR,
    PUSH_ERR,
    STRUCT_NAME_ERR,
    FILE_NAME_ERR,
    LINE_NUM_ERR,
    CAPACITY_ERR
};

#define ASSERT_OK(stk) \
    assert((stk));\
    assert((stk)->error);\
    assert((stk)->data);\
    assert((stk)->capacity > 0);\
    assert((stk)->file);\
    assert((stk)->line);\
    assert((stk)->error);

const int BASE_LENGTH = 5;
const int EDA = 3802;

#endif
