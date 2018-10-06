#include "Quaternions.h"
#include "MathUtils.h"
#include "MinTest.h"

#include <stdio.h>

static int tests_run = 0;

static char* testConstruction() {
    Quat qe, qp, qr;

    Quat qe_exp = {.w = 0.0, .i = 0.0, .j = 0.0, .k = 0.0};
    Quat qp_exp = {.w = 0.0, .i = 1.0, .j = 2.0, .k = 3.0};
    Quat qr_exp = {.w = 1.0, .i = 0.0, .j = 0.0, .k = 0.0};

    qempty(&qe);
    Vect v = {.x = 1.0, .y = 2.0, .z = 3.0};
    qpure(&qp, &v);
    qreal(&qr, 1.0);

    mu_assert("error, qempty(q) != q_exp", qcmp(&qe, &qe_exp));
    mu_assert("error, qpure(q) != q_exp", qcmp(&qp, &qp_exp));
    mu_assert("error, qreal(q) != q_exp", qcmp(&qr, &qr_exp));
    return 0;
}

static char* testRotor() {
    Quat qrx, qry, qrz;

    Quat qrx_exp = {.w = 0.707106781, .i = 0.707106781, .j = 0.0, .k = 0.0};
    Quat qry_exp = {.w = 0.707106781, .i = 0.0, .j = 0.707106781, .k = 0.0};
    Quat qrz_exp = {.w = 0.707106781, .i = 0.0, .j = 0.0, .k = 0.707106781};

    Vect vi, vj, vk;
    vversorX(&vi);
    vversorY(&vj);
    vversorZ(&vk);

    double theta = 90.0 * 3.1415926536 / 180.0;
    qrotor(&qrx, theta, &vi);
    qrotor(&qry, theta, &vj);
    qrotor(&qrz, theta, &vk);

    mu_assert("error, qrotor(q,theta,vi) != q_exp", qcmp(&qrx, &qrx_exp));
    mu_assert("error, qrotor(q,theta,vj) != q_exp", qcmp(&qry, &qry_exp));
    mu_assert("error, qrotor(q,theta,vk) != q_exp", qcmp(&qrz, &qrz_exp));

    mu_assert("error, qrotor(q,theta,vi) is not normalized", qrx.is_normalized);
    mu_assert("error, qrotor(q,theta,vj) is not normalized", qry.is_normalized);
    mu_assert("error, qrotor(q,theta,vk) is not normalized", qrz.is_normalized);
    return 0;
}

static char* testConjugate() {
    Quat q = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat qc = q;
    Quat q_x_qc;

    Quat q_exp = {.w = 1.0, .i = -2.0, .j = -3.0, .k = -4.0};
    Quat q2_exp = {.w = 30.0, .i = 0.0, .j = 0.0, .k = 0.0};

    qconjugate(&qc);
    qmul(&q_x_qc, &q, &qc);

    mu_assert("error, qconjugate(q) != q_expected", qcmp(&qc, &q_exp));
    mu_assert("error, qmul(q,qconjugate(q)) != q_exp", qcmp(&q_x_qc, &q2_exp));
    mu_assert("error, qmul(q,qconjugate(q)) is not real", qisReal(&q_x_qc));
    return 0;
}

static char* testScale() {
    Quat q = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q_exp = {.w = 2.5, .i = 5.0, .j = 7.5, .k = 10.0};

    double k = 2.5;
    qscale(&q, k);

    mu_assert("error, qscale(q,k) != q_exp", qcmp(&q, &q_exp));
    return 0;
}

static char* testNormalize() {
    Quat q = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0, .is_normalized = false};
    Quat q_exp = {.w = 0.5, .i = 0.5, .j = 0.5, .k = 0.5, .is_normalized = true};

    if (qnormalize(&q) < 0) {
        return "error, could not normalize";
    }

    mu_assert("error, qnormalize(q) != q_exp", qcmp(&q, &q_exp));
    mu_assert("error, qnormalize(q) is not normalized", q.is_normalized);
    return 0;
}

static char* testInverse() {
    Quat q = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0};
    Quat q_exp = {.w = 0.25, .i = -0.25, .j = -0.25, .k = -0.25};

    Quat q_inv = q;
    if (qinverse(&q_inv) < 0) {
        return "error, could not inverse";
    }

    Quat q_x_qinv, q_exp2;
    qreal(&q_exp2, 1.0);
    qmul(&q_x_qinv, &q, &q_inv);

    mu_assert("error, qinverse(q) != q_exp", qcmp(&q_inv, &q_exp));
    mu_assert("error, qmul(q,qinverse(q)) != q_exp", qcmp(&q_x_qinv, &q_exp2));
    return 0;
}

static char* testAdd() {
    Quat q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q2 = {.w = 1.1, .i = 1.2, .j = 1.3, .k = 1.4};
    Quat q_exp = {.w = 2.1, .i = 3.2, .j = 4.3, .k = 5.4};

    qadd(&q1, &q2);

    mu_assert("error, qadd(q1,q2) != q_exp", qcmp(&q1, &q_exp));
    return 0;
}

static char* testSubtract() {
    Quat q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q2 = {.w = 1.1, .i = 1.2, .j = 1.3, .k = 1.4};

    Quat q_exp = {.w = -0.1, .i = 0.8, .j = 1.7, .k = 2.6};

    qsub(&q1, &q2);

    mu_assert("error, qsub(q1,q2) != q_exp", qcmp(&q1, &q_exp));
    return 0;
}

static char* testMultiply() {
    Quat q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    Quat q2 = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0};

    Quat q_exp = {.w = -8.0, .i = 2.0, .j = 6.0, .k = 4.0};

    Quat q_mul;
    qmul(&q_mul, &q1, &q2);

    Quat q_mul_conj;
    Quat q1_conj = q1;
    qconjugate(&q1_conj);
    qmul(&q_mul_conj, &q1, &q1_conj);

    mu_assert("error, qmul(q1,q2) != q_exp", qcmp(&q_mul, &q_exp));
    mu_assert("error, qmul(q,qconjugate(q)) is not real", qisReal(&q_mul_conj));
    mu_assert("error, qmul(q1,qconjugate(q1)).w != qnormSquared(q)",
              dcmp(q_mul_conj.w, qnormSquared(&q1)));
    return 0;
}

static char* testDivide() {
    Quat q = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0};

    Quat q_exp;
    qreal(&q_exp, 1.0);

    Quat qd;
    if (qdiv(&qd, &q, &q) < 0) {
        return "error, could not inverse";
    }

    mu_assert("error, qdiv(q,q) != qreal(1)", qcmp(&qd, &q_exp));
    return 0;
}

static char* testRotate() {
    Vect v_exp = {.x = 0.0, .y = 0.0, .z = 2.0, .is_normalized = false};

    Vect axis;
    vversorX(&axis);

    Quat rotor;
    qrotor(&rotor, 3.1415926536 / 2.0, &axis);
    // qprint(&rotor);
    // printf("\n");

    Vect to_rotate;
    vversorY(&to_rotate);
    vscale(&to_rotate, 2.0);
    // vprint(&to_rotate);
    // printf("\n");

    Vect rotated = to_rotate;
    qrotate(&rotated, &rotor);
    // vprint(&rotated);
    // printf("\n");

    mu_assert("error, qrotate(v,q) != v_exp", vcmp(&rotated, &v_exp));
    mu_assert("error, norm(v) != norm(rotate(v,q))",
              to_rotate.is_normalized == rotated.is_normalized &&
                  dcmp(vnorm(&to_rotate), vnorm(&rotated)));

    return 0;
}

static char* testNorm() {
    Quat q = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};

    double norm_exp = 5.477225575;
    double norm_sqrd_exp = 30.0;

    double norm = qnorm(&q);
    double norm_sqrd = qnormSquared(&q);

    mu_assert("error, qnorm(q) != norm_exp", dcmp(norm, norm_exp));
    mu_assert("error, qnormSquared(q) != norm_exp", dcmp(norm_sqrd, norm_sqrd_exp));
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
    mu_run_test(testConstruction);
    mu_run_test(testRotor);
    mu_run_test(testConjugate);
    mu_run_test(testScale);
    mu_run_test(testNormalize);
    mu_run_test(testInverse);
    mu_run_test(testAdd);
    mu_run_test(testSubtract);
    mu_run_test(testMultiply);
    mu_run_test(testDivide);
    mu_run_test(testRotate);
    mu_run_test(testNorm);
    mu_run_test(testCompare);
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