#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "../headers/stack.h"

LOG_DBG(FILE *stack_working_log = fopen("stack_working.log", "w");)
#include "../headers/error_print.h"

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    /*
    if (argc < 2) {
        fprintf(stderr, "NO test_filename: argc = %d\n", argc);
        return TEST_FILENAME_ERR;
    }
    char* test_filename = argv[1];
    */
    Stack_t stk1 {};
    StackCtor(&stk1, BASE_LENGTH, "stk1");
    StackVerify(&stk1);


    size_t count = 10;
    stack_elem_t* data = (stack_elem_t*) calloc(count, sizeof(stack_elem_t));
    if (!data) {
        fprintf(stderr, "CAN'T ALLOCATE MEMORY in %s:%d\n", __FILE__, __LINE__);
        return -1;
    }




    StackPushArray(&stk1, data, count);

    stack_elem_t x = 0;
    StackPop(&stk1, &x);

    StackDtor(&stk1);
}
