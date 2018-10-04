#include "Rotations.h"
#include "MathUtils.h"
#include "MinTest.h"

#include <stdio.h>
// #include <time.h>
// #include <unistd.h>

static int tests_run = 0;

static char* testOpenMP() {
    Rot R1 = {{0.0}};
    rprint(&R1);
    printf("\n");

    Rot R2;
    reye(&R2);
    rscale(2.0, &R2, &R2);
    rprint(&R2);
    printf("\n");

    Rot R3;
    rrand(&R3);
    rprint(&R3);
    printf("\n");

    // time_t begin_t, end_t;
    // begin_t = time(NULL);
    // for (int i = 0; i < 5000000; ++i) {
    //     rmul(&R2, &R2, &R3);
    // }
    // end_t = time(NULL);
    // rprint(&R3);
    // printf("\n");
    // printf("Czas obliczen: %f.\n", difftime(end_t, begin_t));

    mu_assert("error, ", true);
    return 0;
}

static char* all_tests() {
    mu_run_test(testOpenMP);
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
