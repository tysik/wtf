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
}

static char* testAdd() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = 1.0, .y = 1.0, .z = 1.0};
    Vect v_expected = {
        .x = 2.0,
        .y = 3.0,
        .z = 4.0,
    };
    Vect v = vadd(&v1, &v2);
    mu_assert("error, v != v1+v2", vcmp(&v, &v_expected) == true);
}

static char* testSubtract() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = 1.0, .y = 1.0, .z = 1.0};
    Vect v_expected = {.x = 0.0, .y = 1.0, .z = 2.0};
    Vect v = vsub(&v1, &v2);
    mu_assert("error, v != v1-v2", vcmp(&v, &v_expected) == true);
}

static char* testDot() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = 1.0, .y = 1.0, .z = 1.0};
    double dot_expected = 6.0;
    double dot = vdot(&v1, &v2);
    mu_assert("error, dot != dot(v1,v2)", dcmp(dot, dot_expected) == true);
}

static char* testCross() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = 1.0, .y = 1.0, .z = 1.0};
    Vect v_expected = {.x = -1.0, .y = 2.0, .z = -1.0};   
    Vect v = vcross(&v1, &v2);
    mu_assert("error, cross != cross(v1,v2)", vcmp(&v, &v_expected) == true);
}

static char* testScale() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    double k = 2.0;
    Vect v_expected = {.x = 2.0, .y = 4.0, .z = 6.0};
    Vect v = vscale(k, &v1);
    mu_assert("error, v != k*v1", vcmp(&v, &v_expected) == true);
}

static char* testNorm() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    double n_squared_expected = 14.0;
    double n_expected = 3.741657;
    double n_squared = vnormSquared(&v1);
    double n = vnorm(&v1);
    mu_assert("error, nSquared != normSquared(v1)",
              dcmp(n_squared, n_squared_expected) == true);
    //FIXME:
    //mu_assert("error, n != norm(v1)", dcmp(n, n_expected) == true);
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