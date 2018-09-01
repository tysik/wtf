#include "Quaternions.h"

#include <stdio.h>

#define mu_assert(message, test)                                               \
    do {                                                                       \
        if (!(test))                                                           \
            return message;                                                    \
    } while (0)

#define mu_run_test(test)                                                      \
    do {                                                                       \
        char* message = test();                                                \
        tests_run++;                                                           \
        if (message)                                                           \
            return message;                                                    \
    } while (0)

static int tests_run = 0;

static char* testCompare() {
    Quat q1 = {.w = 1.0, .i = 0.0, .j = 0.0, .k = 0.0};
    Quat q2 = {.w = 1.0, .i = 0.0, .j = 0.0, .k = 0.0};
    Quat q3 = {.w = 1.0, .i = 0.0, .j = 0.0, .k = 1.0};
    
    mu_assert("error, q1 != q2", qcmp(&q1, &q2) == true);
    mu_assert("error, q1 == q3", qcmp(&q1, &q3) == false);
}

static char* testAdd() {
    Quat q1 = {.w = 1.0, .i = 0.0, .j = 0.0, .k = 0.0};
    Quat q2 = {.w = 1.0, .i = 0.0, .j = 0.0, .k = 0.0};
    Quat q_expected = {.w = 2.0, .i = 0.0, .j = 0.0, .k = 0.0};
    
    Quat q = qadd(&q1, &q2);

    mu_assert("error, q != q1+q2", qcmp(&q, &q_expected) == true);
}

static char* all_tests() {
    mu_run_test(testCompare);
    mu_run_test(testAdd);
    return 0;
}

int main(int argc, char** argv) {
    char* result = all_tests();

    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}