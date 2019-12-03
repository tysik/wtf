#include "Quaternion.h"
#include "MathUtils.h"
#include "MinTest.h"

#include <stdio.h>

static int tests_run = 0;

static char* test_construction() {
    wtf_quat_t qe, qp, qr;

    wtf_quat_t qe_exp = {.w = 0.0, .i = 0.0, .j = 0.0, .k = 0.0};
    wtf_quat_t qp_exp = {.w = 0.0, .i = 1.0, .j = 2.0, .k = 3.0};
    wtf_quat_t qr_exp = {.w = 1.0, .i = 0.0, .j = 0.0, .k = 0.0};

    wtf_empty_quat(&qe);
    Vect v = {.x = 1.0, .y = 2.0, .z = 3.0};
    wtf_pure_quat(&qp, &v);
    wtf_real_quat(&qr, 1.0);

    mu_assert("error, wtf_empty_quat(q) != q_exp", wtf_compare_quat(&qe, &qe_exp));
    mu_assert("error, wtf_pure_quat(q) != q_exp", wtf_compare_quat(&qp, &qp_exp));
    mu_assert("error, wtf_real_quat(q) != q_exp", wtf_compare_quat(&qr, &qr_exp));

    return 0;
}

static char* test_rotor() {
    wtf_quat_t qrx, qry, qrz;

    wtf_quat_t qrx_exp = {.w = 0.707106781, .i = 0.707106781, .j = 0.0, .k = 0.0};
    wtf_quat_t qry_exp = {.w = 0.707106781, .i = 0.0, .j = 0.707106781, .k = 0.0};
    wtf_quat_t qrz_exp = {.w = 0.707106781, .i = 0.0, .j = 0.0, .k = 0.707106781};

    Vect vi, vj, vk;
    vversorX(&vi);
    vversorY(&vj);
    vversorZ(&vk);

    double theta = 90.0 * 3.1415926536 / 180.0;
    wtf_rotor_quat(&qrx, theta, &vi);
    wtf_rotor_quat(&qry, theta, &vj);
    wtf_rotor_quat(&qrz, theta, &vk);

    mu_assert("error, wtf_rotor_quat(q,theta,vi) != q_exp", wtf_compare_quat(&qrx, &qrx_exp));
    mu_assert("error, wtf_rotor_quat(q,theta,vj) != q_exp", wtf_compare_quat(&qry, &qry_exp));
    mu_assert("error, wtf_rotor_quat(q,theta,vk) != q_exp", wtf_compare_quat(&qrz, &qrz_exp));

    mu_assert("error, wtf_rotor_quat(q,theta,vi) is not normalized", qrx.is_normalized);
    mu_assert("error, wtf_rotor_quat(q,theta,vj) is not normalized", qry.is_normalized);
    mu_assert("error, wtf_rotor_quat(q,theta,vk) is not normalized", qrz.is_normalized);

    return 0;
}

static char* test_conjugate() {
    wtf_quat_t q = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    wtf_quat_t qc = q;
    wtf_quat_t q_x_qc;

    wtf_quat_t q_exp = {.w = 1.0, .i = -2.0, .j = -3.0, .k = -4.0};
    wtf_quat_t q2_exp = {.w = 30.0, .i = 0.0, .j = 0.0, .k = 0.0};

    wtf_quat_conjugate(&qc);
    wtf_quat_multiply(&q_x_qc, &q, &qc);

    mu_assert("error, wtf_quat_conjugate(q) != q_expected", wtf_compare_quat(&qc, &q_exp));
    mu_assert("error, wtf_quat_multiply(q,wtf_quat_conjugate(q)) != q_exp", wtf_compare_quat(&q_x_qc, &q2_exp));
    mu_assert("error, wtf_quat_multiply(q,wtf_quat_conjugate(q)) is not real", wtf_quat_is_real(&q_x_qc));

    return 0;
}

static char* test_scale() {
    wtf_quat_t q = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    wtf_quat_t q_exp = {.w = 2.5, .i = 5.0, .j = 7.5, .k = 10.0};

    double k = 2.5;
    wtf_quat_scaled(&q, k);

    mu_assert("error, wtf_quat_scaled(q,k) != q_exp", wtf_compare_quat(&q, &q_exp));

    return 0;
}

static char* testN_normalize() {
    wtf_quat_t q = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0, .is_normalized = false};
    wtf_quat_t q_exp = {.w = 0.5, .i = 0.5, .j = 0.5, .k = 0.5, .is_normalized = true};

    if (wtf_quat_normalized(&q) < 0) {
        return "error, could not normalize";
    }

    mu_assert("error, wtf_quat_normalized(q) != q_exp", wtf_compare_quat(&q, &q_exp));
    mu_assert("error, wtf_quat_normalized(q) is not normalized", q.is_normalized);

    return 0;
}

static char* test_inverse() {
    wtf_quat_t q = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0};
    wtf_quat_t q_exp = {.w = 0.25, .i = -0.25, .j = -0.25, .k = -0.25};

    wtf_quat_t q_inv = q;
    if (wtf_quat_inversed(&q_inv) < 0) {
        return "error, could not inverse";
    }

    wtf_quat_t q_x_qinv, q_exp2;
    wtf_real_quat(&q_exp2, 1.0);
    wtf_quat_multiply(&q_x_qinv, &q, &q_inv);

    mu_assert("error, wtf_quat_inversed(q) != q_exp", wtf_compare_quat(&q_inv, &q_exp));
    mu_assert("error, wtf_quat_multiply(q,wtf_quat_inversed(q)) != q_exp", wtf_compare_quat(&q_x_qinv, &q_exp2));

    return 0;
}

static char* test_add() {
    wtf_quat_t q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    wtf_quat_t q2 = {.w = 1.1, .i = 1.2, .j = 1.3, .k = 1.4};
    wtf_quat_t q_exp = {.w = 2.1, .i = 3.2, .j = 4.3, .k = 5.4};

    wtf_quat_add(&q1, &q2);

    mu_assert("error, wtf_quat_add(q1,q2) != q_exp", wtf_compare_quat(&q1, &q_exp));

    return 0;
}

static char* test_subtract() {
    wtf_quat_t q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    wtf_quat_t q2 = {.w = 1.1, .i = 1.2, .j = 1.3, .k = 1.4};

    wtf_quat_t q_exp = {.w = -0.1, .i = 0.8, .j = 1.7, .k = 2.6};

    wtf_quat_subtract(&q1, &q2);

    mu_assert("error, wtf_quat_subtract(q1,q2) != q_exp", wtf_compare_quat(&q1, &q_exp));

    return 0;
}

static char* test_multiply() {
    wtf_quat_t q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    wtf_quat_t q2 = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0};

    wtf_quat_t q_exp = {.w = -8.0, .i = 2.0, .j = 6.0, .k = 4.0};

    wtf_quat_t q_mul;
    wtf_quat_multiply(&q_mul, &q1, &q2);

    wtf_quat_t q_mul_conj;
    wtf_quat_t q1_conj = q1;
    wtf_quat_conjugate(&q1_conj);
    wtf_quat_multiply(&q_mul_conj, &q1, &q1_conj);

    mu_assert("error, wtf_quat_multiply(q1,q2) != q_exp", wtf_compare_quat(&q_mul, &q_exp));
    mu_assert("error, wtf_quat_multiply(q,wtf_quat_conjugate(q)) is not real", wtf_quat_is_real(&q_mul_conj));
    mu_assert("error, wtf_quat_multiply(q1,wtf_quat_conjugate(q1)).w != wtf_quat_norm_squared(q)",
              dcmp(q_mul_conj.w, wtf_quat_norm_squared(&q1)));

    return 0;
}

static char* test_divide() {
    wtf_quat_t q = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0};

    wtf_quat_t q_exp;
    wtf_real_quat(&q_exp, 1.0);

    wtf_quat_t qd;
    if (wtf_quat_divide(&qd, &q, &q) < 0) {
        return "error, could not inverse";
    }

    mu_assert("error, wtf_quat_divide(q,q) != wtf_real_quat(1)", wtf_compare_quat(&qd, &q_exp));

    return 0;
}

static char* test_rotate() {
    Vect v_exp = {.x = 0.0, .y = 0.0, .z = 2.0, .is_normalized = false};

    Vect axis;
    vversorX(&axis);

    wtf_quat_t rotor;
    wtf_rotor_quat(&rotor, 3.1415926536 / 2.0, &axis);
    // wtf_print_quat(&rotor);
    // printf("\n");

    Vect to_rotate;
    vversorY(&to_rotate);
    vscale(&to_rotate, 2.0);
    // vprint(&to_rotate);
    // printf("\n");

    Vect rotated = to_rotate;
    wtf_quat_rotated(&rotated, &rotor);
    // vprint(&rotated);
    // printf("\n");

    mu_assert("error, wtf_quat_rotated(v,q) != v_exp", vcmp(&rotated, &v_exp));
    mu_assert("error, norm(v) != norm(rotate(v,q))",
              to_rotate.is_normalized == rotated.is_normalized &&
                  dcmp(vnorm(&to_rotate), vnorm(&rotated)));

    return 0;
}

static char* test_norm() {
    wtf_quat_t q = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};

    double norm_exp = 5.477225575;
    double norm_sqrd_exp = 30.0;

    double norm = wtf_quat_norm(&q);
    double norm_sqrd = wtf_quat_norm_squared(&q);

    mu_assert("error, wtf_quat_norm(q) != norm_exp", dcmp(norm, norm_exp));
    mu_assert("error, wtf_quat_norm_squared(q) != norm_exp", dcmp(norm_sqrd, norm_sqrd_exp));

    return 0;
}

static char* test_compare() {
    wtf_quat_t q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    wtf_quat_t q2 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    wtf_quat_t q3 = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0};

    mu_assert("error, q1 != q2", wtf_compare_quat(&q1, &q2) == true);
    mu_assert("error, q1 == q3", wtf_compare_quat(&q1, &q3) == false);

    return 0;
}

static char* all_tests() {
    mu_run_test(test_construction);
    mu_run_test(test_rotor);
    mu_run_test(test_conjugate);
    mu_run_test(test_scale);
    mu_run_test(test_normalize);
    mu_run_test(test_inverse);
    mu_run_test(test_add);
    mu_run_test(test_subtract);
    mu_run_test(test_multiply);
    mu_run_test(test_divide);
    mu_run_test(test_rotate);
    mu_run_test(test_norm);
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