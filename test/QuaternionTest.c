#include "Quaternion.h"
#include "MathUtils.h"
#include "MinTest.h"
#include "Vector.h"

#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

static int tests_run = 0;

static char* test_construction() {
    wtf_vec_t v = {.x = 1.0, .y = 2.0, .z = 3.0};

    wtf_quat_t qe_expected = {.w = 0.0, .i = 0.0, .j = 0.0, .k = 0.0};
    wtf_quat_t qp_expected = {.w = 0.0, .i = 1.0, .j = 2.0, .k = 3.0};
    wtf_quat_t qr_expected = {.w = 1.0, .i = 0.0, .j = 0.0, .k = 0.0};

    wtf_quat_t qe = wtf_empty_quat();
    wtf_quat_t qp = wtf_pure_quat(&v);
    wtf_quat_t qr = wtf_real_quat(1.0);

    mu_assert("error, wtf_empty_quat(q) != expected", wtf_compare_quat(&qe, &qe_expected));
    mu_assert("error, wtf_pure_quat(q) != expected", wtf_compare_quat(&qp, &qp_expected));
    mu_assert("error, wtf_real_quat(q) != expected", wtf_compare_quat(&qr, &qr_expected));

    return 0;
}

static char* test_rotor() {
    wtf_scalar_t angle = M_PI / 2.0;

    wtf_vec_t vi = wtf_versor_x();
    wtf_vec_t vj = wtf_versor_y();
    wtf_vec_t vk = wtf_versor_z();

    wtf_quat_t qrx_expected = {.w = 0.707106781, .i = 0.707106781, .j = 0.0, .k = 0.0};
    wtf_quat_t qry_expected = {.w = 0.707106781, .i = 0.0, .j = 0.707106781, .k = 0.0};
    wtf_quat_t qrz_expected = {.w = 0.707106781, .i = 0.0, .j = 0.0, .k = 0.707106781};

    wtf_quat_t qrx = wtf_rotor_quat(&vi, angle);
    wtf_quat_t qry = wtf_rotor_quat(&vj, angle);
    wtf_quat_t qrz = wtf_rotor_quat(&vk, angle);

    mu_assert("error, wtf_rotor_quat(angle,vi) != expected", wtf_compare_quat(&qrx, &qrx_expected));
    mu_assert("error, wtf_rotor_quat(angle,vj) != expected", wtf_compare_quat(&qry, &qry_expected));
    mu_assert("error, wtf_rotor_quat(angle,vk) != expected", wtf_compare_quat(&qrz, &qrz_expected));

    mu_assert("error, wtf_rotor_quat(angle,vi) is not normalized", wtf_quat_is_normalized(&qrx));
    mu_assert("error, wtf_rotor_quat(angle,vj) is not normalized", wtf_quat_is_normalized(&qry));
    mu_assert("error, wtf_rotor_quat(angle,vk) is not normalized", wtf_quat_is_normalized(&qrz));

    return 0;
}

static char* test_conjugate() {
    wtf_quat_t q = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    wtf_quat_t qc_expected = {.w = 1.0, .i = -2.0, .j = -3.0, .k = -4.0};
    wtf_quat_t q_x_qc_expected = {.w = 30.0, .i = 0.0, .j = 0.0, .k = 0.0};

    wtf_quat_t qc = wtf_quat_conjugate(&q);
    wtf_quat_t q_x_qc = wtf_quat_multiply(&q, &qc);

    mu_assert("error, wtf_quat_conjugate(q) != expected", wtf_compare_quat(&qc, &qc_expected));
    mu_assert("error, wtf_quat_multiply(q, wtf_quat_conjugate(q)) != expected",
              wtf_compare_quat(&q_x_qc, &q_x_qc_expected));
    mu_assert("error, wtf_quat_multiply(q, wtf_quat_conjugate(q)) is not real",
              wtf_quat_is_real(&q_x_qc));

    return 0;
}

static char* test_scale() {
    wtf_scalar_t k = 2.5;
    wtf_quat_t q = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    wtf_quat_t q_expected = {.w = 2.5, .i = 5.0, .j = 7.5, .k = 10.0};

    q = wtf_quat_scaled(&q, k);

    mu_assert("error, wtf_quat_scaled(q,k) != expected", wtf_compare_quat(&q, &q_expected));

    return 0;
}

static char* test_normalize() {
    wtf_quat_t q = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0};
    wtf_quat_t q_expected = {.w = 0.5, .i = 0.5, .j = 0.5, .k = 0.5};

    q = wtf_quat_normalized(&q);

    mu_assert("error, wtf_quat_normalized(q) != expected", wtf_compare_quat(&q, &q_expected));
    mu_assert("error, wtf_quat_normalized(q) is not normalized", wtf_quat_is_normalized(&q));

    return 0;
}

static char* test_inverse() {
    wtf_quat_t q = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0};
    wtf_quat_t q_inv_expected = {.w = 0.25, .i = -0.25, .j = -0.25, .k = -0.25};
    wtf_quat_t q_x_q_inv_expected = wtf_real_quat(1.0);

    wtf_quat_t q_inv = wtf_quat_inversed(&q);
    wtf_quat_t q_x_q_inv = wtf_quat_multiply(&q, &q_inv);

    mu_assert("error, wtf_quat_inversed(q) != expected", wtf_compare_quat(&q_inv, &q_inv_expected));
    mu_assert("error, wtf_quat_multiply(q,wtf_quat_inversed(q)) != expected",
              wtf_compare_quat(&q_x_q_inv, &q_x_q_inv_expected));

    return 0;
}

static char* test_add() {
    wtf_quat_t q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    wtf_quat_t q2 = {.w = 1.1, .i = 1.2, .j = 1.3, .k = 1.4};
    wtf_quat_t q_expected = {.w = 2.1, .i = 3.2, .j = 4.3, .k = 5.4};

    q1 = wtf_quat_add(&q1, &q2);

    mu_assert("error, wtf_quat_add(q1,q2) != expected", wtf_compare_quat(&q1, &q_expected));

    return 0;
}

static char* test_subtract() {
    wtf_quat_t q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    wtf_quat_t q2 = {.w = 1.1, .i = 1.2, .j = 1.3, .k = 1.4};
    wtf_quat_t q_exp = {.w = -0.1, .i = 0.8, .j = 1.7, .k = 2.6};

    q1 = wtf_quat_subtract(&q1, &q2);

    mu_assert("error, wtf_quat_subtract(q1,q2) != expected", wtf_compare_quat(&q1, &q_exp));

    return 0;
}

static char* test_multiply() {
    wtf_quat_t q1 = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    wtf_quat_t q2 = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0};
    wtf_quat_t q1_conj = wtf_quat_conjugate(&q1);
    wtf_quat_t q_mul_expected = {.w = -8.0, .i = 2.0, .j = 6.0, .k = 4.0};

    wtf_quat_t q_mul = wtf_quat_multiply(&q1, &q2);
    wtf_quat_t q_mul_conj = wtf_quat_multiply(&q1, &q1_conj);

    mu_assert("error, wtf_quat_multiply(q1,q2) != expected",
              wtf_compare_quat(&q_mul, &q_mul_expected));
    mu_assert("error, wtf_quat_multiply(q,wtf_quat_conjugate(q)) is not real",
              wtf_quat_is_real(&q_mul_conj));
    mu_assert("error, wtf_quat_multiply(q1,wtf_quat_conjugate(q1)).w != wtf_quat_squared_norm(q) ",
              wtf_dcmp(q_mul_conj.w, wtf_quat_squared_norm(&q1)));

    return 0;
}

static char* test_divide() {
    wtf_quat_t q = {.w = 1.0, .i = 1.0, .j = 1.0, .k = 1.0};
    wtf_quat_t q_expected = wtf_real_quat(1.0);

    q = wtf_quat_divide(&q, &q);

    mu_assert("error, wtf_quat_divide(q,q) != wtf_real_quat(1)", wtf_compare_quat(&q, &q_expected));

    return 0;
}

static char* test_rotate() {
    wtf_vec_t axis = wtf_versor_x();
    wtf_quat_t rotor = wtf_rotor_quat(&axis, M_PI / 2.0);
    wtf_vec_t to_rotate = {.x = 0.0, .y = 2.0, .z = 0.0};
    wtf_vec_t rotated_expected = {.x = 0.0, .y = 0.0, .z = 2.0};

    wtf_vec_t rotated = wtf_quat_rotate(&rotor, &to_rotate);
    bool equal_norms = wtf_dcmp(wtf_vec_norm(&to_rotate), wtf_vec_norm(&rotated));

    mu_assert("error, wtf_quat_rotate(q,v) != expected",
              wtf_compare_vec(&rotated, &rotated_expected));
    mu_assert("error, norm(v) != norm(rotate(v,q))", equal_norms);

    return 0;
}

static char* test_norm() {
    wtf_quat_t q = {.w = 1.0, .i = 2.0, .j = 3.0, .k = 4.0};
    wtf_scalar_t norm_expected = 5.477225575;
    wtf_scalar_t norm_squared_expected = 30.0;

    wtf_scalar_t norm = wtf_quat_norm(&q);
    wtf_scalar_t norm_squared = wtf_quat_squared_norm(&q);

    mu_assert("error, wtf_quat_norm(q) != expected", wtf_dcmp(norm, norm_expected));
    mu_assert("error, wtf_quat_squared_norm(q) != expected",
              wtf_dcmp(norm_squared, norm_squared_expected));

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