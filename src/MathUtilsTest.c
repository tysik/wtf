#include "MathUtils.c"
#include "MinTest.h"

#include <stdio.h>

static int tests_run = 0;

static char* testMax() {
    mu_assert("error, max != 4.0", wtf_dmax(4, 1.0, 2.0, 3.0, 4.0) == 4.0);
    mu_assert("error, max != -1.0", wtf_dmax(4, -1.0, -2.0, -3.0, -4.0) == -1.0);
    mu_assert("error, max != 0.001", wtf_dmax(4, 0.0, 0.001, -3.001, -40.0) == 0.001);
    return 0;
}

static char* test_compare() {
    double a1 = 0.0001;
    double a2 = 0.00012;
    double a3 = 0.000100001;
    mu_assert("error, a1 == a2", wtf_dcmp(a1, a2) == false);
    mu_assert("error, a1 != a3", wtf_dcmp(a1, a3) == true);

    double b1 = 1.0;
    double b2 = 0.99999;
    double b3 = 1.000000001;
    mu_assert("error, b1 == b2", wtf_dcmp(b1, b2) == false);
    mu_assert("error, b1 != b3", wtf_dcmp(b1, b3) == true);

    double c1 = 1000.0;
    double c2 = 1000.001;
    double c3 = 1000.00001;
    mu_assert("error, c1 == c2", wtf_dcmp(c1, c2) == false);
    mu_assert("error, c1 != c3", wtf_dcmp(c1, c3) == true);
    return 0;
}

static char* all_tests() {
    mu_run_test(testMax);
    mu_run_test(test_compare);
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