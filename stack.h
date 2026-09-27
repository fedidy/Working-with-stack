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

#endif
