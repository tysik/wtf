#include "Vector.h"
#include "MathUtils.h"
#include "MinTest.h"

#include <stdio.h>
#include <string.h>

static int tests_run = 0;

static char* test_construction() {
    wtf_vec_t ve = wtf_empty_vec();
    wtf_vec_t vx = wtf_versor_x();
    wtf_vec_t vy = wtf_versor_y();
    wtf_vec_t vz = wtf_versor_z();

    double a[3] = {-3.0, 5.0, 0.7};
    wtf_vec_t va = wtf_vec_from_array(&a);

    wtf_vec_t ve_exp = {.x = 0.0, .y = 0.0, .z = 0.0};
    wtf_vec_t vx_exp = {.x = 1.0, .y = 0.0, .z = 0.0};
    wtf_vec_t vy_exp = {.x = 0.0, .y = 1.0, .z = 0.0};
    wtf_vec_t vz_exp = {.x = 0.0, .y = 0.0, .z = 1.0};
    wtf_vec_t va_exp = {.x = -3.0, .y = 5.0, .z = 0.7};

    mu_assert("error, wtf_empty_vec() != expected", wtf_compare_vec(&ve, &ve_exp));
    mu_assert("error, wtf_empty_vec() is normalized", !wtf_vec_is_normalized(&ve));

    mu_assert("error, wtf_versor_x(v) != expected", wtf_compare_vec(&vx, &vx_exp));
    mu_assert("error, wtf_versor_x(v) is not normalized", wtf_vec_is_normalized(&vx));

    mu_assert("error, wtf_versor_y(v) != expected", wtf_compare_vec(&vy, &vy_exp));
    mu_assert("error, wtf_versor_y(v) is not normalized", wtf_vec_is_normalized(&vy));

    mu_assert("error, wtf_versor_z(v) != expected", wtf_compare_vec(&vz, &vz_exp));
    mu_assert("error, wtf_versor_z(v) is not normalized", wtf_vec_is_normalized(&vz));

    mu_assert("error, wtf_vec_from_array(a) != expected", wtf_compare_vec(&va, &va_exp));
    mu_assert("error, wtf_vec_from_array(a) is normalized", !wtf_vec_is_normalized(&va));

    return 0;
}

static char* test_negate() {
    wtf_vec_t v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    wtf_vec_t v2 = {.x = -0.001, .y = 20.05, .z = -3000.0};
    wtf_vec_t v3 = {.x = 1.0, .y = 0.0, .z = 0.0};

    wtf_vec_t v1_exp = {.x = -1.0, .y = -2.0, .z = -3.0};
    wtf_vec_t v2_exp = {.x = 0.001, .y = -20.05, .z = 3000.0};
    wtf_vec_t v3_exp = {.x = -1.0, .y = 0.0, .z = 0.0};

    v1 = wtf_vec_negated(&v1);
    v2 = wtf_vec_negated(&v2);
    v3 = wtf_vec_negated(&v3);
    bool both_normalized = wtf_vec_is_normalized(&v3) == wtf_vec_is_normalized(&v3_exp);

    mu_assert("error, wtf_vec_negated(v) != expected", wtf_compare_vec(&v1, &v1_exp));
    mu_assert("error, wtf_vec_negated(v) != expected", wtf_compare_vec(&v2, &v2_exp));
    mu_assert("error, wtf_vec_negated(v) != expected", wtf_compare_vec(&v3, &v3_exp));
    mu_assert("error, norm(wtf_vec_negated(v)) != norm(v)", both_normalized);

    return 0;
}

static char* test_scale() {
    wtf_vec_t v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    wtf_vec_t v2 = {.x = 1.0, .y = 0.0, .z = 0.0};

    wtf_vec_t v1_exp = {.x = 2.5, .y = 5.0, .z = 7.5};
    wtf_vec_t v2_exp = {.x = 2.5, .y = 0.0, .z = 0.0};

    double k = 2.5;
    v1 = wtf_vec_scaled(&v1, k);
    v2 = wtf_vec_scaled(&v2, k);
    bool equal_norms = wtf_vec_is_normalized(&v2) == wtf_vec_is_normalized(&v2_exp) &&
                       wtf_dcmp(wtf_vec_norm(&v2), wtf_vec_norm(&v2_exp));

    mu_assert("error, wtf_vec_scaled(v,k) != expected", wtf_compare_vec(&v1, &v1_exp));
    mu_assert("error, wtf_vec_scaled(v,k) != expected", wtf_compare_vec(&v2, &v2_exp));
    mu_assert("error, norm(wtf_vec_scaled(v,k)) != norm(expected)", equal_norms);

    return 0;
}

static char* test_add() {
    wtf_vec_t v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    wtf_vec_t v2 = {.x = 1.1, .y = 1.2, .z = 1.3};
    wtf_vec_t v3 = {.x = -0.05, .y = 0.5, .z = -20.3};

    wtf_vec_t v12_exp = {.x = 2.1, .y = 3.2, .z = 4.3};
    wtf_vec_t v23_exp = {.x = 1.05, .y = 1.7, .z = -19.0};
    wtf_vec_t v33_exp = {.x = -0.1, .y = 1.0, .z = -40.6};

    wtf_vec_t v12 = wtf_vec_add(&v1, &v2);
    wtf_vec_t v23 = wtf_vec_add(&v2, &v3);
    wtf_vec_t v33 = wtf_vec_add(&v3, &v3);

    mu_assert("error, wtf_vec_add(v1,v2) != expected", wtf_compare_vec(&v12, &v12_exp));
    mu_assert("error, wtf_vec_add(v2,v3) != expected", wtf_compare_vec(&v23, &v23_exp));
    mu_assert("error, wtf_vec_add(v3,v3) != expected", wtf_compare_vec(&v33, &v33_exp));

    return 0;
}

static char* test_subtract() {
    wtf_vec_t v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    wtf_vec_t v2 = {.x = 1.1, .y = 1.2, .z = 1.3};
    wtf_vec_t v3 = {.x = -0.05, .y = 0.5, .z = -20.3};

    wtf_vec_t v12_exp = {.x = -0.1, .y = 0.8, .z = 1.7};
    wtf_vec_t v23_exp = {.x = 1.15, .y = 0.7, .z = 21.6};
    wtf_vec_t v33_exp = {.x = 0.0, .y = 0.0, .z = 0.0};

    wtf_vec_t v12 = wtf_vec_subtract(&v1, &v2);
    wtf_vec_t v23 = wtf_vec_subtract(&v2, &v3);
    wtf_vec_t v33 = wtf_vec_subtract(&v3, &v3);
    bool norm_zero = wtf_vec_norm(&v33);

    mu_assert("error, wtf_vec_subtract(v1,v2) != expected", wtf_compare_vec(&v12, &v12_exp));
    mu_assert("error, wtf_vec_subtract(v2,v3) != expected", wtf_compare_vec(&v23, &v23_exp));
    mu_assert("error, wtf_vec_subtract(v3,v3) != expected", wtf_compare_vec(&v33, &v33_exp));
    mu_assert("error, norm(wtf_vec_subtract(v3,v3)) != 0", wtf_dcmp(norm_zero, 0));

    return 0;
}

static char* test_cross() {
    wtf_vec_t v0 = wtf_empty_vec();

    wtf_vec_t vi = wtf_versor_x();
    wtf_vec_t vj = wtf_versor_y();
    wtf_vec_t vk = wtf_versor_z();

    wtf_vec_t vni = wtf_vec_negated(&vi);
    wtf_vec_t vnj = wtf_vec_negated(&vj);
    wtf_vec_t vnk = wtf_vec_negated(&vk);

    wtf_vec_t vii = wtf_vec_cross(&vi, &vi);
    wtf_vec_t vij = wtf_vec_cross(&vi, &vj);
    wtf_vec_t vik = wtf_vec_cross(&vi, &vk);

    wtf_vec_t vji = wtf_vec_cross(&vj, &vi);
    wtf_vec_t vjj = wtf_vec_cross(&vj, &vj);
    wtf_vec_t vjk = wtf_vec_cross(&vj, &vk);

    wtf_vec_t vki = wtf_vec_cross(&vk, &vi);
    wtf_vec_t vkj = wtf_vec_cross(&vk, &vj);
    wtf_vec_t vkk = wtf_vec_cross(&vk, &vk);

    mu_assert("error, wtf_vec_cross(vi,vi) != 0", wtf_compare_vec(&vii, &v0));
    mu_assert("error, wtf_vec_cross(vi,vj) != vk", wtf_compare_vec(&vij, &vk));
    mu_assert("error, wtf_vec_cross(vi,vk) != -vj", wtf_compare_vec(&vik, &vnj));

    mu_assert("error, wtf_vec_cross(vj,vi) != -vk", wtf_compare_vec(&vji, &vnk));
    mu_assert("error, wtf_vec_cross(vj,vj) != 0", wtf_compare_vec(&vjj, &v0));
    mu_assert("error, wtf_vec_cross(vj,vk) != vi", wtf_compare_vec(&vjk, &vi));

    mu_assert("error, wtf_vec_cross(vk,vi) != vj", wtf_compare_vec(&vki, &vj));
    mu_assert("error, wtf_vec_cross(vk,vj) != -vi", wtf_compare_vec(&vkj, &vni));
    mu_assert("error, wtf_vec_cross(vk,vk) != 0", wtf_compare_vec(&vkk, &v0));

    wtf_vec_t v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    wtf_vec_t v2 = {.x = 1.0, .y = 1.0, .z = 1.0};
    wtf_vec_t v_exp = {.x = -1.0, .y = 2.0, .z = -1.0};

    wtf_vec_t v_cross = wtf_vec_cross(&v1, &v2);
    wtf_vec_t v_cross_inv = wtf_vec_cross(&v2, &v1);
    wtf_vec_t v_cross_inv_neg = wtf_vec_negated(&v_cross_inv);

    mu_assert("error, wtf_vec_cross(v1,v2) != expected", wtf_compare_vec(&v_cross, &v_exp));
    mu_assert("error, wtf_vec_cross(v1,v2) != wtf_vec_negated(wtf_vec_cross(v2,v1))",
              wtf_compare_vec(&v_cross, &v_cross_inv_neg));

    return 0;
}

static char* test_dot() {
    wtf_vec_t vi = wtf_versor_x();
    wtf_vec_t vj = wtf_versor_y();
    wtf_vec_t vk = wtf_versor_z();

    mu_assert("error, wtf_vec_dot(vi,vi) != 1", wtf_dcmp(wtf_vec_dot(&vi, &vi), 1.0));
    mu_assert("error, wtf_vec_dot(vi,vj) != 0", wtf_dcmp(wtf_vec_dot(&vi, &vj), 0.0));
    mu_assert("error, wtf_vec_dot(vi,vk) != 0", wtf_dcmp(wtf_vec_dot(&vi, &vk), 0.0));

    mu_assert("error, wtf_vec_dot(vj,vi) != 0", wtf_dcmp(wtf_vec_dot(&vj, &vi), 0.0));
    mu_assert("error, wtf_vec_dot(vj,vj) != 1", wtf_dcmp(wtf_vec_dot(&vj, &vj), 1.0));
    mu_assert("error, wtf_vec_dot(vj,vk) != 0", wtf_dcmp(wtf_vec_dot(&vj, &vk), 0.0));

    mu_assert("error, wtf_vec_dot(vk,vi) != 0", wtf_dcmp(wtf_vec_dot(&vk, &vi), 0.0));
    mu_assert("error, wtf_vec_dot(vk,vj) != 0", wtf_dcmp(wtf_vec_dot(&vk, &vj), 0.0));
    mu_assert("error, wtf_vec_dot(vk,vk) != 1", wtf_dcmp(wtf_vec_dot(&vk, &vk), 1.0));

    wtf_vec_t v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    wtf_vec_t v2 = {.x = 1.0, .y = 1.0, .z = 1.0};
    double dot_exp = 6.0;

    double dot = wtf_vec_dot(&v1, &v2);

    mu_assert("error, wtf_vec_dot(v1,v2) != expected", wtf_dcmp(dot, dot_exp));

    return 0;
}

static char* test_norm() {
    wtf_vec_t v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    wtf_vec_t v2 = {.x = 0.1, .y = 0.2, .z = 0.3};

    double n1_exp = 14.0;
    double n2_exp = 0.14;

    mu_assert("error, wtf_vec_squared_norm(v1) != expected",
              wtf_dcmp(wtf_vec_squared_norm(&v1), n1_exp));
    mu_assert("error, wtf_vec_squared_norm(v2) != expected",
              wtf_dcmp(wtf_vec_squared_norm(&v2), n2_exp));

    n1_exp = 3.741657387;
    n2_exp = 0.374165738;

    mu_assert("error, wtf_vec_norm(v1) != norm_exp", wtf_dcmp(wtf_vec_norm(&v1), n1_exp));
    mu_assert("error, wtf_vec_norm(v2) != norm_exp", wtf_dcmp(wtf_vec_norm(&v2), n2_exp));

    return 0;
}

static char* test_normalize() {
    wtf_vec_t v1 = {.x = 0.0, .y = 2.0, .z = 0.0};
    wtf_vec_t v2 = {.x = 0.0, .y = 20.05, .z = -20.05};

    wtf_vec_t v1_exp = {.x = 0.0, .y = 1.0, .z = 0.0};
    wtf_vec_t v2_exp = {.x = 0.0, .y = 0.707106781, .z = -0.707106781};

    v1 = wtf_vec_normalized(&v1);
    v2 = wtf_vec_normalized(&v2);

    mu_assert("error, wtf_vec_normalized(v) != expected", wtf_compare_vec(&v1, &v1_exp));
    mu_assert("error, norm(v) != 1.0", wtf_vec_is_normalized(&v1));

    mu_assert("error, wtf_vec_normalized(v) != expected", wtf_compare_vec(&v2, &v2_exp));
    mu_assert("error, norm(v) != 1.0", wtf_vec_is_normalized(&v2));

    return 0;
}

static char* test_compare() {
    wtf_vec_t v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    wtf_vec_t v2 = {.x = 1.0, .y = 2.0, .z = 3.0};
    wtf_vec_t v3 = {.x = 1.0, .y = 1.0, .z = 1.0};

    mu_assert("error, v1 != v2", wtf_compare_vec(&v1, &v2));
    mu_assert("error, v1 == v3", !wtf_compare_vec(&v1, &v3));

    return 0;
}

static char* all_tests() {
    mu_run_test(test_construction);
    mu_run_test(test_negate);
    mu_run_test(test_scale);
    mu_run_test(test_add);
    mu_run_test(test_subtract);
    mu_run_test(test_cross);
    mu_run_test(test_dot);
    mu_run_test(test_norm);
    mu_run_test(test_normalize);
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