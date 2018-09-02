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
}

static char* testAdd() {
    Quat q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q2 = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0};
    Quat q_expected = {.w = 2.0, .i = 3.0, .j = 4.0, .k = 5.0};
    Quat q = qadd(&q1, &q2);
    mu_assert("error, q != q1+q2", qcmp(&q, &q_expected) == true);
}

static char* testSubtract() {
    Quat q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q2 = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0};
    Quat q_expected = {.w = 0.0, .i = 1.0, .j = 2.0, .k = 3.0};
    Quat q = qsub(&q1, &q2);
    mu_assert("error, q != q1-q2", qcmp(&q, &q_expected) == true);
}

static char* testMultiply() {
    Quat q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q2 = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0};
    Quat q_expected = {.w = -8.0, .i = 2.0, .j = 6.0, .k = 4.0};
    Quat q = qmul(&q1, &q2);
    mu_assert("error, q != q1*q2", qcmp(&q, &q_expected) == true);
}

static char* testScale() {
    Quat q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    double k = 2.0;
    Quat q_expected = {.w = 2.0, .i = 4.0, .j = 6.0, .k = 8.0};
    Quat q = qscale(k, &q1);
    mu_assert("error, q != k*q1", qcmp(&q, &q_expected) == true);
}

static char* testReal() {
    Quat q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q_expected = {.w = 1.0, .i = 0.0, .j = 0.0, .k = 0.0};
    Quat q = qreal(&q1);
    mu_assert("error, q != real(q1)", qcmp(&q, &q_expected) == true);
}

static char* testPure() {
    Quat q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q_expected = {.w = 0.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q = qpure(&q1);
    mu_assert("error, q != pure(q1)", qcmp(&q, &q_expected) == true);
}

static char* testConjugate() {
    Quat q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q_expected = {.w = 1.0, .i = -2.0, .j = -3.0, .k = -4.0};
    Quat q = qconj(&q1);
    Quat q_x = qmul(&q1, &q);
    Quat q_expected_x = {.w = 30.0, .i = 0.0, .j = 0.0, .k = 0.0};
    mu_assert("error, q != conj(q1)", qcmp(&q, &q_expected) == true);
    mu_assert("error, q != q1 * conj(q1)", qcmp(&q_x, &q_expected_x) == true);
}

static char* testNorm() {
    Quat q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    double norm_expected = 30.0;
    double norm = qnorm(&q1);
    mu_assert("error, norm != norm(q1)", dcmp(norm, norm_expected) == true);
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