#include "Vectors.h"
#include "MathUtils.h"
#include "MinTest.h"

#include <stdio.h>

static int tests_run = 0;

static char* testCompare() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v3 = {.x = 1.0, .y = 1.0, .z = 1.0};

    mu_assert("error, v1 != v2", vcmp(&v1, &v2) == true);
    mu_assert("error, v1 == v3", vcmp(&v1, &v3) == false);
    return 0;
}

static char* testAdd() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = 1.0, .y = 1.0, .z = 1.0};

    Vect v_expected = {.x = 2.0, .y = 3.0, .z = 4.0};
    Vect v = vadd(&v1, &v2);

    mu_assert("error, v_expected != v1+v2", vcmp(&v, &v_expected) == true);
    return 0;
}

static char* testSubtract() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = 1.0, .y = 1.0, .z = 1.0};

    Vect v_expected = {.x = 0.0, .y = 1.0, .z = 2.0};
    Vect v = vsub(&v1, &v2);

    mu_assert("error, v_expected != v1-v2", vcmp(&v, &v_expected) == true);
    return 0;
}

static char* testDot() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = 1.0, .y = 1.0, .z = 1.0};

    double dot_expected = 6.0;
    double dot = vdot(&v1, &v2);

    mu_assert("error, dot_expected != dot(v1,v2)", dcmp(dot, dot_expected) == true);
    return 0;
}

static char* testCross() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = 1.0, .y = 1.0, .z = 1.0};

    Vect v_expected = {.x = -1.0, .y = 2.0, .z = -1.0};
    Vect v = vcross(&v1, &v2);

    mu_assert("error, cross_expected != cross(v1,v2)", vcmp(&v, &v_expected) == true);
    return 0;
}

static char* testScale() {
    Vect v = {.x = 1.0, .y = 2.0, .z = 3.0};
    double k = 2.0;

    Vect v_expected = {.x = 2.0, .y = 4.0, .z = 6.0};
    Vect v1 = vscale(k, &v);

    mu_assert("error, v_expected != k*v", vcmp(&v1, &v_expected) == true);
    return 0;
}

static char* testNorm() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = 0.1, .y = 0.2, .z = 0.3};

    double n1_sqr_expected = 14.0;
    double n1_sqr = vnormSquared(&v1);
    double n2_sqr_expected = 0.14;
    double n2_sqr = vnormSquared(&v2);
    mu_assert("error, snorm_expected != snorm(v1)", dcmp(n1_sqr, n1_sqr_expected) == true);
    mu_assert("error, snorm_expected != snorm(v2)", dcmp(n2_sqr, n2_sqr_expected) == true);

    double n1_expected = 3.741657387;
    double n1 = vnorm(&v1);
    double n2_expected = 0.374165738;
    double n2 = vnorm(&v2);
    mu_assert("error, norm_expected != norm(v1)", dcmp(n1, n1_expected) == true);
    mu_assert("error, norm_expected != norm(v2)", dcmp(n2, n2_expected) == true);
    return 0;
}

static char* testNeg() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = -0.001, .y = 20.05, .z = -3000.0};

    Vect v1_expected = {.x = -1.0, .y = -2.0, .z = -3.0};
    Vect v2_expected = {.x = 0.001, .y = -20.05, .z = 3000.0};

    mu_assert("error, v_expected != -v1", vcmp(&v1, &v1_expected) == true);
    mu_assert("error, v_expected != -v2", vcmp(&v2, &v2_expected) == true);
    return 0;
}

static char* all_tests() {
    mu_run_test(testCompare);
    mu_run_test(testAdd);
    mu_run_test(testSubtract);
    mu_run_test(testDot);
    mu_run_test(testCross);
    mu_run_test(testScale);
    mu_run_test(testNorm);
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