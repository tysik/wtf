#include "Vectors.h"
#include "MathUtils.h"
#include "MinTest.h"

#include <stdio.h>
#include <string.h>

static int tests_run = 0;

static char* testConstruction() {
    wtf_vec_t ve, vx, vy, vz, va;

    wtf_vec_t ve_exp = {.x = 0.0, .y = 0.0, .z = 0.0, .is_normalized = false};
    wtf_vec_t vx_exp = {.x = 1.0, .y = 0.0, .z = 0.0, .is_normalized = true};
    wtf_vec_t vy_exp = {.x = 0.0, .y = 1.0, .z = 0.0, .is_normalized = true};
    wtf_vec_t vz_exp = {.x = 0.0, .y = 0.0, .z = 1.0, .is_normalized = true};
    wtf_vec_t va_exp = {.x = -3.0, .y = 5.0, .z = 0.7};

    wtf_empty_vec(&ve);
    wtf_versor_x(&vx);
    wtf_versor_y(&vy);
    wtf_versor_z(&vz);

    double a[3] = {-3.0, 5.0, 0.7};
    wtf_vec_from_array(&va, &a);

    mu_assert("error, wtf_empty_vec(v) != v_exp", wtf_compare_vec(&ve, &ve_exp));
    mu_assert("error, wtf_empty_vec(v) is normalized", !ve.is_normalized);

    mu_assert("error, wtf_versor_x(v) != v_exp", wtf_compare_vec(&vx, &vx_exp));
    mu_assert("error, wtf_versor_x(v) is not normalized", vx.is_normalized);

    mu_assert("error, wtf_versor_y(v) != v_exp", wtf_compare_vec(&vy, &vy_exp));
    mu_assert("error, wtf_versor_y(v) is not normalized", vy.is_normalized);

    mu_assert("error, wtf_versor_z(v) != v_exp", wtf_compare_vec(&vz, &vz_exp));
    mu_assert("error, wtf_versor_z(v) is not normalized", vz.is_normalized);

    mu_assert("error, wtf_vec_from_array(v,a) != v_exp", wtf_compare_vec(&va, &va_exp));
    return 0;
}

static char* testNegate() {
    wtf_vec_t v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    wtf_vec_t v2 = {.x = -0.001, .y = 20.05, .z = -3000.0};
    wtf_vec_t v3 = {.x = 1.0, .y = 0.0, .z = 0.0, .is_normalized = true};

    wtf_vec_t v1_exp = {.x = -1.0, .y = -2.0, .z = -3.0};
    wtf_vec_t v2_exp = {.x = 0.001, .y = -20.05, .z = 3000.0};
    wtf_vec_t v3_exp = {.x = -1.0, .y = 0.0, .z = 0.0, .is_normalized = true};

    wtf_negate_vec(&v1);
    wtf_negate_vec(&v2);
    wtf_negate_vec(&v3);

    mu_assert("error, wtf_negate_vec(v) != v_exp", wtf_compare_vec(&v1, &v1_exp));
    mu_assert("error, wtf_negate_vec(v) != v_exp", wtf_compare_vec(&v2, &v2_exp));
    mu_assert("error, wtf_negate_vec(v) != v_exp", wtf_compare_vec(&v3, &v3_exp));
    mu_assert("error, norm(vneg(v)) != norm(v_exp)", v3.is_normalized == v3_exp.is_normalized);
    return 0;
}

static char* testScale() {
    wtf_vec_t v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    wtf_vec_t v2 = {.x = 1.0, .y = 0.0, .z = 0.0, .is_normalized = true};

    wtf_vec_t v1_exp = {.x = 2.5, .y = 5.0, .z = 7.5};
    wtf_vec_t v2_exp = {.x = 2.5, .y = 0.0, .z = 0.0, .is_normalized = false};

    double k = 2.5;
    wtf_scale_vec(&v1, k);
    wtf_scale_vec(&v2, k);

    mu_assert("error, wtf_scale_vec(v,k) != v_exp", wtf_compare_vec(&v1, &v1_exp));
    mu_assert("error, wtf_scale_vec(v,k) != v_exp", wtf_compare_vec(&v2, &v2_exp));
    mu_assert("error, norm(wtf_scale_vec(v,k)) != norm(v_exp)",
              v2.is_normalized == v2_exp.is_normalized && dcmp(wtf_vec_norm(&v2), wtf_vec_norm(&v2_exp)));
    return 0;
}

static char* testNormalize() {
    wtf_vec_t v1 = {.x = 2.0, .y = 0.0, .z = 0.0, .is_normalized = false};
    wtf_vec_t v2 = {.x = 0.0, .y = 20.05, .z = -20.05, .is_normalized = false};

    wtf_vec_t v1_exp = {.x = 1.0, .y = 0.0, .z = 0.0, .is_normalized = true};
    wtf_vec_t v2_exp = {.x = 0.0, .y = 0.707106781, .z = -0.707106781, .is_normalized = true};

    if (wtf_normalize_vec(&v1) < 0) {
        return "error, could not normalize";
    }
    if (wtf_normalize_vec(&v2) < 0) {
        return "error, could not normalize";
    }

    mu_assert("error, wtf_normalize_vec(v) != v_exp", wtf_compare_vec(&v1, &v1_exp));
    mu_assert("error, norm(v) != 1.0", v1.is_normalized && dcmp(wtf_vec_norm(&v1), 1.0));

    mu_assert("error, wtf_normalize_vec(v) != v_exp", wtf_compare_vec(&v2, &v2_exp));
    mu_assert("error, norm(v) != 1.0", v2.is_normalized && dcmp(wtf_vec_norm(&v2), 1.0));
    return 0;
}

static char* testAdd() {
    wtf_vec_t v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    wtf_vec_t v2 = {.x = 1.1, .y = 1.2, .z = 1.3};
    wtf_vec_t v3 = {.x = -0.05, .y = 0.5, .z = -20.3};

    wtf_vec_t v1_exp = {.x = 2.1, .y = 3.2, .z = 4.3};
    wtf_vec_t v2_exp = {.x = 1.05, .y = 1.7, .z = -19.0};
    wtf_vec_t v3_exp = {.x = -0.1, .y = 1.0, .z = -40.6};

    wtf_add_vec(&v1, &v2);
    wtf_add_vec(&v2, &v3);
    wtf_add_vec(&v3, &v3);

    mu_assert("error, wtf_add_vec(v1,v2) != v_exp", wtf_compare_vec(&v1, &v1_exp));
    mu_assert("error, wtf_add_vec(v2,v3) != v_exp", wtf_compare_vec(&v2, &v2_exp));
    mu_assert("error, wtf_add_vec(v3,v3) != v_exp", wtf_compare_vec(&v3, &v3_exp));
    return 0;
}

static char* testSubtract() {
    wtf_vec_t v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    wtf_vec_t v2 = {.x = 1.1, .y = 1.2, .z = 1.3};
    wtf_vec_t v3 = {.x = -0.05, .y = 0.5, .z = -20.3};

    wtf_vec_t v1_exp = {.x = -0.1, .y = 0.8, .z = 1.7};
    wtf_vec_t v2_exp = {.x = 1.15, .y = 0.7, .z = 21.6};
    wtf_vec_t v3_exp = {.x = 0.0, .y = 0.0, .z = 0.0};

    wtf_subtract_vec(&v1, &v2);
    wtf_subtract_vec(&v2, &v3);
    wtf_subtract_vec(&v3, &v3);

    mu_assert("error, wtf_subtract_vec(v1,v2) != v_exp", wtf_compare_vec(&v1, &v1_exp));
    mu_assert("error, wtf_subtract_vec(v2,v3) != v_exp", wtf_compare_vec(&v2, &v2_exp));
    mu_assert("error, wtf_subtract_vec(v3,v3) != v_exp", wtf_compare_vec(&v3, &v3_exp));
    return 0;
}

static char* testCross() {
    wtf_vec_t v0;
    wtf_vec_t vi, vj, vk;
    wtf_vec_t vni, vnj, vnk;

    wtf_empty_vec(&v0);
    wtf_versor_x(&vi);
    wtf_versor_y(&vj);
    wtf_versor_z(&vk);

    vni = vi, wtf_negate_vec(&vni);
    vnj = vj, wtf_negate_vec(&vnj);
    vnk = vk, wtf_negate_vec(&vnk);

    wtf_vec_t vii, vij, vik;
    wtf_vec_t vji, vjj, vjk;
    wtf_vec_t vki, vkj, vkk;

    wtf_vec_cross(&vii, &vi, &vi);
    wtf_vec_cross(&vij, &vi, &vj);
    wtf_vec_cross(&vik, &vi, &vk);

    wtf_vec_cross(&vji, &vj, &vi);
    wtf_vec_cross(&vjj, &vj, &vj);
    wtf_vec_cross(&vjk, &vj, &vk);

    wtf_vec_cross(&vki, &vk, &vi);
    wtf_vec_cross(&vkj, &vk, &vj);
    wtf_vec_cross(&vkk, &vk, &vk);

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

    wtf_vec_t v_cross, v_cross_inv;
    wtf_vec_cross(&v_cross, &v1, &v2);
    wtf_vec_cross(&v_cross_inv, &v2, &v1);
    wtf_negate_vec(&v_cross_inv);

    mu_assert("error, wtf_vec_cross(v1,v2) != v_exp", wtf_compare_vec(&v_cross, &v_exp));
    mu_assert("error, wtf_vec_cross(v1,v2) != wtf_negate_vec(wtf_vec_cross(v2,v1))", wtf_compare_vec(&v_cross, &v_cross_inv));
    return 0;
}

static char* testDot() {
    wtf_vec_t vi, vj, vk;
    wtf_versor_x(&vi);
    wtf_versor_y(&vj);
    wtf_versor_z(&vk);

    mu_assert("error, wtf_vec_dot(vi,vi) != 1", dcmp(wtf_vec_dot(&vi, &vi), 1.0));
    mu_assert("error, wtf_vec_dot(vi,vj) != 0", dcmp(wtf_vec_dot(&vi, &vj), 0.0));
    mu_assert("error, wtf_vec_dot(vi,vk) != 0", dcmp(wtf_vec_dot(&vi, &vk), 0.0));

    mu_assert("error, wtf_vec_dot(vj,vi) != 0", dcmp(wtf_vec_dot(&vj, &vi), 0.0));
    mu_assert("error, wtf_vec_dot(vj,vj) != 1", dcmp(wtf_vec_dot(&vj, &vj), 1.0));
    mu_assert("error, wtf_vec_dot(vj,vk) != 0", dcmp(wtf_vec_dot(&vj, &vk), 0.0));

    mu_assert("error, wtf_vec_dot(vk,vi) != 0", dcmp(wtf_vec_dot(&vk, &vi), 0.0));
    mu_assert("error, wtf_vec_dot(vk,vj) != 0", dcmp(wtf_vec_dot(&vk, &vj), 0.0));
    mu_assert("error, wtf_vec_dot(vk,vk) != 1", dcmp(wtf_vec_dot(&vk, &vk), 1.0));

    wtf_vec_t v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    wtf_vec_t v2 = {.x = 1.0, .y = 1.0, .z = 1.0};

    double dot_exp = 6.0;
    mu_assert("error, wtf_vec_dot(v1,v2) != dot_exp", dcmp(wtf_vec_dot(&v1, &v2), dot_exp));
    return 0;
}

static char* testNorm() {
    wtf_vec_t v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    wtf_vec_t v2 = {.x = 0.1, .y = 0.2, .z = 0.3};

    double n1_exp = 14.0;
    double n2_exp = 0.14;

    mu_assert("error, wtf_vec_squared_norm(v1) != norm_exp", dcmp(wtf_vec_squared_norm(&v1), n1_exp));
    mu_assert("error, wtf_vec_squared_norm(v2) != norm_exp", dcmp(wtf_vec_squared_norm(&v2), n2_exp));

    n1_exp = 3.741657387;
    n2_exp = 0.374165738;

    mu_assert("error, wtf_vec_norm(v1) != norm_exp", dcmp(wtf_vec_norm(&v1), n1_exp));
    mu_assert("error, wtf_vec_norm(v2) != norm_exp", dcmp(wtf_vec_norm(&v2), n2_exp));
    return 0;
}

static char* testCompare() {
    wtf_vec_t v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    wtf_vec_t v2 = {.x = 1.0, .y = 2.0, .z = 3.0};
    wtf_vec_t v3 = {.x = 1.0, .y = 1.0, .z = 1.0};

    mu_assert("error, v1 != v2", wtf_compare_vec(&v1, &v2));
    mu_assert("error, v1 == v3", !wtf_compare_vec(&v1, &v3));

    return 0;
}

static char* all_tests() {
    mu_run_test(testConstruction);
    mu_run_test(testNegate);
    mu_run_test(testScale);
    mu_run_test(testNormalize);
    mu_run_test(testAdd);
    mu_run_test(testSubtract);
    mu_run_test(testCross);
    mu_run_test(testDot);
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