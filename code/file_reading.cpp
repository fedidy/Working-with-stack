#include <stdlib.h>
#include <stdio.h>

#include "file_reading.h"
#include "stack.h"
#include "error_print.h"

int ReadElemFromFile(stack_elem_t *data, const size_t count, const char *const test_filename) {
    fprintf(stack_working_log , "Started reading from file:"
                    "count = %zu, pointer to data = %p, filename = %s\n",
                     count, data, test_filename);


    if (!test_filename) {
        fprintf(stderr, "GOT NO test_filename, CAN'T GET ANY ELEMENTS\n");
        return TEST_FILENAME_ERR;
    }

    FILE* fp = fopen(test_filename, "r");
    if (!fp) {
        fprintf(stderr, "CAN'T OPEN FILE WITH TESTS: test_filename = %s\n", test_filename);
        return FILE_OPEN_ERR;
    }

    if (!data) {
        fprintf(stderr, "CAN'T ALLOCATE MEMORY in %s:%d\n", __FILE__, __LINE__);
        return CALLOC_ERR;
    }

    int err = ScanFile(fp, data, count);
    fclose(fp);
    return err;
}


int ScanFile(FILE *const fp, stack_elem_t *const data, const size_t count) {
    assert(data);

    if (!fp) {
        fprintf(stderr, "POINTER IN FILE TO SCAN IS ZERO\n");
        return FILE_POINTER_ZERO_ERR;
    }

    /*
    if (count < 0) {
        fprintf(stderr, "GOT count (OF ELEMENTS IN data) BELOW ZERO:"
                        "count = %zu, pointer to data = %p, file pointer = %p\n",
                         count, data, fp);
        return COUNT_ERR;
    }
    */

// ПЕРЕДЕЛАТЬ ФАЙЛ РИД

    //size_t read_num = fread(data, sizeof(stack_elem_t), count, fp);
    size_t read_num = 0;
    for (size_t i = 0; i < count; i++) {
        if (!fscanf(fp, PRINT_DATA, &data[i]))
            break;
        read_num++;
    }

    //кринге не там выводится
    if (read_num < count) {
        fprintf(stderr, "READ NOT ALL ELEMENTS: got %zu elements, expected %zu\n", read_num, count);
        fprintf(stderr, "file: %s, line: %d\n", __FILE__, __LINE__);
        DataPrint(stderr, data, count);
        return INSUFFICIENT_ELEM_ERR;
    }

    return NO_ERR;
}
