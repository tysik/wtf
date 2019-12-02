#include "Rotations.h"
#include "MathUtils.h"
#include "MinTest.h"

#include <stdio.h>

static int tests_run = 0;

static char* test_construction() {
    mu_assert("error, ", true);
    return 0;
}

static char* all_tests() {
    mu_run_test(test_construction);
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
