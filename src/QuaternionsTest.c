#include "Quaternions.h"
#include "MathUtils.h"
#include "MinTest.h"

#include <stdio.h>

static int tests_run = 0;

static char* testCompare() {
    Quat q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q2 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q3 = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0};

    mu_assert("error, q1 != q2", qcmp(&q1, &q2) == true);
    mu_assert("error, q1 == q3", qcmp(&q1, &q3) == false);
    return 0;
}

static char* testAdd() {
    Quat q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q2 = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0};

    Quat q_expected = {.w = 2.0, .i = 3.0, .j = 4.0, .k = 5.0};
    Quat q = qadd(&q1, &q2);

    mu_assert("error, q_expected != q1+q2", qcmp(&q, &q_expected) == true);
    return 0;
}

static char* testSubtract() {
    Quat q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q2 = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0};

    Quat q_expected = {.w = 0.0, .i = 1.0, .j = 2.0, .k = 3.0};
    Quat q = qsub(&q1, &q2);

    mu_assert("error, q_expected != q1-q2", qcmp(&q, &q_expected) == true);
    return 0;
}

static char* testMultiply() {
    Quat q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q2 = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0};

    Quat q_expected = {.w = -8.0, .i = 2.0, .j = 6.0, .k = 4.0};
    Quat q = qmul(&q1, &q2);

    mu_assert("error, q_expected != q1*q2", qcmp(&q, &q_expected) == true);
    return 0;
}

static char* testScale() {
    Quat q = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    double k = 2.0;

    Quat q_expected = {.w = 2.0, .i = 4.0, .j = 6.0, .k = 8.0};
    Quat q1 = qscale(k, &q);

    mu_assert("error, q_expected != k*q", qcmp(&q1, &q_expected) == true);
    return 0;
}

static char* testReal() {
    Quat q = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q_expected = {.w = 1.0, .i = 0.0, .j = 0.0, .k = 0.0};
    Quat q1 = qreal(&q);

    mu_assert("error, q_expected != real(q)", qcmp(&q1, &q_expected) == true);
    return 0;
}

static char* testPure() {
    Quat q = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q_expected = {.w = 0.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q1 = qpure(&q);

    mu_assert("error, q_expected != pure(q)", qcmp(&q1, &q_expected) == true);
    return 0;
}

static char* testConjugate() {
    Quat q = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q_expected = {.w = 1.0, .i = -2.0, .j = -3.0, .k = -4.0};
    Quat q1 = qconj(&q);
    mu_assert("error, q_expected != conj(q)", qcmp(&q1, &q_expected) == true);

    Quat q_x = qmul(&q1, &q);
    Quat q_expected_x = {.w = 30.0, .i = 0.0, .j = 0.0, .k = 0.0};
    mu_assert("error, q_expected != q * conj(q)", qcmp(&q_x, &q_expected_x) == true);
    return 0;
}

static char* testNorm() {
    Quat q = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};

    double n_squared_expected = 30.0;
    double n_squared = qnormSquared(&q);
    double n_expected = 5.477225575;
    double n = qnorm(&q);

    mu_assert("error, norm_expected != norm(q)", dcmp(n, n_expected) == true);
    mu_assert("error, snorm_expected != snorm(q)", dcmp(n_squared, n_squared_expected) == true);
    return 0;
}

static char* all_tests() {
    mu_run_test(testCompare);
    mu_run_test(testAdd);
    mu_run_test(testSubtract);
    mu_run_test(testMultiply);
    mu_run_test(testScale);
    mu_run_test(testReal);
    mu_run_test(testPure);
    mu_run_test(testConjugate);
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