#include "Quaternions.h"
#include "MathUtils.h"
#include "MinTest.h"

#include <stdio.h>

static int tests_run = 0;

static char* testEmpty() {
    Quat q1 = {.w = 0.0, .i = 0.0, .j = 0.0, .k = 0.0, .is_normalized = false};
    Quat q2 = {.s = 0.0, .v = vempty(), .is_normalized = false};
    Quat q_empty = qempty();

    mu_assert("error, q_empty is normalized", !q_empty.is_normalized);
    mu_assert("error, q1 != q2", qcmp(&q1, &q2));
    mu_assert("error, q_empty != q1", qcmp(&q_empty, &q1));
    mu_assert("error, q_empty != q2", qcmp(&q_empty, &q2));

    return 0;
}

static char* testConjugate() {
    Quat q = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};

    Quat q_expected = {.w = 1.0, .i = -2.0, .j = -3.0, .k = -4.0};
    Quat q_conj = qconj(&q);

    mu_assert("error, q_expected != qconj(q)", qcmp(&q_conj, &q_expected));

    Quat q_x = qmul(&q_conj, &q);
    Quat q_expected_x = {.w = 30.0, .i = 0.0, .j = 0.0, .k = 0.0};

    mu_assert("error, q_expected != qmul(q,qconj(q))", qcmp(&q_x, &q_expected_x));

    return 0;
}

static char* testUnit() {
    Quat q1 = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0, .is_normalized = false};
    Quat q_expected = {.w = 0.5, .i = 0.5, .j = 0.5, .k = 0.5, .is_normalized = true};
    Quat q = qunit(&q1);
    
    mu_assert("error, q_expected != qunit(q)", qcmp(&q, &q_expected));
    mu_assert("error, q_expected is not normalized", q.is_normalized);

    return 0;
}

static char* testInv() {
    Quat q1 = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0};
    Quat q_expected = {.w = 0.25, .i = -0.25, .j = -0.25, .k = -0.25};
    Quat q = qinv(&q1);
    
    Quat q_expected2 = {.s = 1.0, .v = vempty()};
    Quat q2 = qmul(&q1, &q);

    mu_assert("error, q_expected != qinv(q)", qcmp(&q, &q_expected));
    mu_assert("error, q_expected2 != qmul(q,qinv(q))", qcmp(&q2, &q_expected2));

    return 0;
}

static char* testScale() {
    Quat q = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    double k = 2.5;

    Quat q_expected = {.w = 2.5, .i = 5.0, .j = 7.5, .k = 10.0};
    Quat q1 = qscale(k, &q);

    mu_assert("error, q_expected != qscale(k,q)", qcmp(&q1, &q_expected));
    return 0;
}

static char* testRotor() {
    Vect axis = {.x = 1.0, .y = 0.0, .z = 0.0, .is_normalized = true};
    double theta = 90.0 * 3.1415926536 / 180.0;

    Quat q_expected = {.w = 0.707106781, .i = 0.707106781, .j = 0.0, .k = 0.0};
    Quat q = qrotor(theta, &axis);

    mu_assert("error, q_expected != qrotor(theta,v)", qcmp(&q, &q_expected));
    mu_assert("error, q_expected is not normalized", q.is_normalized);
    return 0;
}

static char* testAdd() {
    Quat q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q2 = {.w = 1.1, .i = 1.2, .j = 1.3, .k = 1.4};

    Quat q_expected = {.w = 2.1, .i = 3.2, .j = 4.3, .k = 5.4};
    Quat q_added = qadd(&q1, &q2);

    mu_assert("error, q_expected != qadd(q1,q2)", qcmp(&q_added, &q_expected));
    return 0;
}

static char* testSubtract() {
    Quat q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q2 = {.w = 1.1, .i = 1.2, .j = 1.3, .k = 1.4};

    Quat q_expected = {.w = -0.1, .i = 0.8, .j = 1.7, .k = 2.6};
    Quat q_subtracted = qsub(&q1, &q2);

    mu_assert("error, q_expected != qsub(q1,q2)", qcmp(&q_subtracted, &q_expected));
    return 0;
}

static char* testMultiply() {
    Quat q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q2 = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0};

    Quat q_expected = {.w = -8.0, .i = 2.0, .j = 6.0, .k = 4.0};
    Quat q = qmul(&q1, &q2);

    mu_assert("error, q_expected != q1*q2", qcmp(&q, &q_expected));
    return 0;
}

static char* testDivide() {
    Quat q1 = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0};
    Quat q_expected = {.w = 1.0, .i = 0.0, .j = 0.0, .k = 0.0};
    Quat q = qdiv(&q1, &q1);

    mu_assert("error, q_expected != qdiv(q1,q2)", qcmp(&q, &q_expected));
    return 0;
}

static char* testReal() {
    Quat q = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    double real_expected = 1.0;
    double real = qreal(&q);

    mu_assert("error, real_expected != real(q)", dcmp(real, real_expected));
    return 0;
}

static char* testPure() {
    Quat q = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Vect pure_expected = {.x = 2.0, .y = 3.0, .z = 4.0};
    Vect pure = qpure(&q);

    mu_assert("error, pure_expected != pure(q)", vcmp(&pure, &pure_expected));
    return 0;
}

static char* testRotate() {
    Vect axis = {.x = 1.0, .y = 0.0, .z = 0.0, .is_normalized = true};
    Quat rotor = qrotor(3.1415926536 / 2.0, &axis);

    Vect to_rotate = {.x = 0.0, .y = 1.0, .z = 0.0, .is_normalized = true};
    Vect rotated = qrotate(&to_rotate, &rotor);
    Vect expected = {.x = 0.0, .y = 0.0, .z = 1.0, .is_normalized = true};

    mu_assert("error, v_expected != rotate(v,q)", vcmp(&rotated, &expected));
    mu_assert("error, norm(v) != norm(rotate(v,q))",
              dcmp(vnormSquared(&to_rotate), vnormSquared(&rotated)));

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

static char* testCompare() {
    Quat q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q2 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q3 = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0};

    mu_assert("error, q1 != q2", qcmp(&q1, &q2) == true);
    mu_assert("error, q1 == q3", qcmp(&q1, &q3) == false);
    return 0;
}

static char* all_tests() {
    mu_run_test(testEmpty);
    mu_run_test(testConjugate);
    mu_run_test(testUnit);
    mu_run_test(testInv);
    mu_run_test(testScale);
    mu_run_test(testRotor);
    mu_run_test(testCompare);
    mu_run_test(testAdd);
    mu_run_test(testSubtract);
    mu_run_test(testMultiply);
    mu_run_test(testDivide);
    mu_run_test(testReal);
    mu_run_test(testPure);
    mu_run_test(testRotate);
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