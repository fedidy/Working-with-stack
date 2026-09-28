#include "file_reading.h"
#include "stack.h"
#include "error_print.h"

#include <cstdio>
#include <cstdlib>

int ReadElemFromFile(stack_elem_t *data, size_t count, const char *const test_filename) {
    assert(data);

    if (count < 0) {
        fprintf(stderr, "GOT count (OF ELEMENTS IN data) BELOW ZERO:"
                        "count = %zu, pointer to data = %p, filename = %s\n",
                         count, data, test_filename);
        return COUNT_ERR;
    }

    if (!test_filename) {
        fprintf(stderr, "GOT NO test_filename, CAN'T GET ANY ELEMENTS\n");
        return TEST_FILENAME_ERR;
    }

    FILE* fp = fopen(test_filename, "r");
    if (!fp) {
        fprintf(stderr, "CAN'T OPEN FILE WITH TESTS: test_filename = %s\n", test_filename);
        return FILE_OPEN_ERR;
    }

    int err = ScanFile(fp, data, count);
    free(fp);
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

    size_t read_num = fread(data, sizeof(stack_elem_t), count, fp);
    if (read_num < count) {
        fprintf(stderr, "READ NOT ALL ELEMENTS: got %zu elements, expected %zu\n", read_num, count);
        fprintf(stderr, "file: %s, line: %d\n", __FILE__, __LINE__);
        DataPrint(data, count);
        return INSUFFICIENT_ELEM_ERR;
    }

    return NO_ERR;
}
