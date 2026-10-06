#ifndef STACK_H
#define STACK_H

#if STACK_DEBUG > 0
#define ON_DBG(...) __VA_ARGS__
#else
#define ON_DBG(...)
typedef int Error_info;
#endif

#if STACK_DEBUG > 1
#define LOG_DBG(...) __VA_ARGS__
#define PRINT_LOG(...) fprintf(stderr, __VA_ARGS__)
#else
#define LOG_DBG(...)
#define PRINT_LOG(...)
#endif

// вынести в main
#include <stddef.h>
#include <math.h>


typedef double stack_elem_t;
#define PRINT_DATA "%lg"
const double NO_DATA = NAN; // отказаться согласовано


// сделать макрос для заполнения
#if STACK_DEBUG > 0
struct Position_info {
    const char* file;
    const char* func;
    int line;
};
#define GET_POSITION(position) {\
(position).file = __FILE__;\
(position).func = __func__;\
(position).line = __LINE__;\
}

// переделать под структуру местоположения в коде
struct Error_info {
    Position_info pos;
    int error_code;
    //const char* comment;
};
#define WRITE_ERR(err_struct, err_code) {\
GET_POSITION((err_struct).pos);\
(err_struct).error_code = (err_code);\
}
#define RETURN_ERR(err_code) {\
Error_info err_info_do_not_use = {};\
WRITE_ERR(err_info_do_not_use, (err_code))\
return err_info_do_not_use;\
}
#define RETURN_NO_ERR {\
Error_info err_info_do_not_use = {};\
WRITE_ERR(err_info_do_not_use, NO_ERR)\
return err_info_do_not_use;\
}
#define RETURN_ERROR_IF_GOT(err_info) {\
    if (!(err_info).error_code) {\
        return (err_info);\
    }\
}
#else
#define GET_POSITION(position) {}
#define WRITE_ERR(err_struct, err_code) {err_struct = -1;}
#define RETURN_ERR(err_code) {return (err_code);}
#define RETURN_NO_ERR {return 0;}
#define RETURN_ERROR_IF_GOT(err_code) {\
    if (!(err_code)) {\
        return (err_code);\
    }\
}
#endif


enum Stack_Errors {
    NO_ERR = 0,
    STACK_DESTROYED,
    CALLOC_ERR,
    DATA_POINTER_ZERO_ERR,
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

enum Other_Error {
    FILE_OPEN_ERR = 1000,
    TEST_FILENAME_ERR
};

#define ASSERT_OK(stk) {\
    assert((stk));\
    assert((stk)->data);\
    assert((stk)->stack_name);\
}

struct Stack_t {
    ON_DBG(
    //Error_info err; не хранить ошибку в стике
    Position_info cr_info;
    const char* stack_name;
    )
    stack_elem_t* data;
    // подумать над size что это
    size_t size;
    size_t capacity;
};

const int CAPACITY_UP_COEF = 2;
const int CAPACITY_DOWN_COEF = 4;
const int BASE_LENGTH = 5;

#include "stack_func.h"

#endif
