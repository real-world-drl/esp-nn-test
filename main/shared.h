//
// Created by bohm on 13/02/23.
//

#ifndef ESP_NN_TEST_SHARED_H
#define ESP_NN_TEST_SHARED_H

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define MULT_MAX    INT32_MAX
#define MULT_MIN    0

#define CHECK_EQUAL(ARRAY1, ARRAY2, size) ({    \
    bool res = true;                            \
    for (int _i = 0; _i < size; _i++) {         \
        if (ARRAY1[_i] != ARRAY2[_i]) {         \
            res = false;                        \
            break;                              \
        }                                       \
    }                                           \
    res;                                        \
})


#endif //ESP_NN_TEST_SHARED_H
