#include "Vectors.h"
#include "MathUtils.h"
#include "MinTest.h"

#include <stdio.h>
#include <string.h>

static int tests_run = 0;

static char* testConstruction() {
    Vect ve, vx, vy, vz, va;

    Vect ve_exp = {.x = 0.0, .y = 0.0, .z = 0.0, .is_normalized = false};
    Vect vx_exp = {.x = 1.0, .y = 0.0, .z = 0.0, .is_normalized = true};
    Vect vy_exp = {.x = 0.0, .y = 1.0, .z = 0.0, .is_normalized = true};
    Vect vz_exp = {.x = 0.0, .y = 0.0, .z = 1.0, .is_normalized = true};
    Vect va_exp = {.x = -3.0, .y = 5.0, .z = 0.7};

    vempty(&ve);
    vversorX(&vx);
    vversorY(&vy);
    vversorZ(&vz);

    double a[3] = {-3.0, 5.0, 0.7};
    vfromArray(&va, &a);

    mu_assert("error, vempty(v) != v_exp", vcmp(&ve, &ve_exp));
    mu_assert("error, vempty(v) is normalized", !ve.is_normalized);

    mu_assert("error, vversorX(v) != v_exp", vcmp(&vx, &vx_exp));
    mu_assert("error, vversorX(v) is not normalized", vx.is_normalized);

    mu_assert("error, vversorY(v) != v_exp", vcmp(&vy, &vy_exp));
    mu_assert("error, vversorY(v) is not normalized", vy.is_normalized);

    mu_assert("error, vversorZ(v) != v_exp", vcmp(&vz, &vz_exp));
    mu_assert("error, vversorZ(v) is not normalized", vz.is_normalized);

    mu_assert("error, vfromArray(v,a) != v_exp", vcmp(&va, &va_exp));
    return 0;
}

static char* testNegate() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = -0.001, .y = 20.05, .z = -3000.0};
    Vect v3 = {.x = 1.0, .y = 0.0, .z = 0.0, .is_normalized = true};

    Vect v1_exp = {.x = -1.0, .y = -2.0, .z = -3.0};
    Vect v2_exp = {.x = 0.001, .y = -20.05, .z = 3000.0};
    Vect v3_exp = {.x = -1.0, .y = 0.0, .z = 0.0, .is_normalized = true};

    vnegate(&v1);
    vnegate(&v2);
    vnegate(&v3);

    mu_assert("error, vnegate(v) != v_exp", vcmp(&v1, &v1_exp));
    mu_assert("error, vnegate(v) != v_exp", vcmp(&v2, &v2_exp));
    mu_assert("error, vnegate(v) != v_exp", vcmp(&v3, &v3_exp));
    mu_assert("error, norm(vneg(v)) != norm(v_exp)", v3.is_normalized == v3_exp.is_normalized);
    return 0;
}

static char* testScale() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = 1.0, .y = 0.0, .z = 0.0, .is_normalized = true};

    Vect v1_exp = {.x = 2.5, .y = 5.0, .z = 7.5};
    Vect v2_exp = {.x = 2.5, .y = 0.0, .z = 0.0, .is_normalized = false};

    double k = 2.5;
    vscale(&v1, k);
    vscale(&v2, k);

    mu_assert("error, vscale(v,k) != v_exp", vcmp(&v1, &v1_exp));
    mu_assert("error, vscale(v,k) != v_exp", vcmp(&v2, &v2_exp));
    mu_assert("error, norm(vscale(v,k)) != norm(v_exp)",
              v2.is_normalized == v2_exp.is_normalized && dcmp(vnorm(&v2), vnorm(&v2_exp)));
    return 0;
}

static char* testNormalize() {
    Vect v1 = {.x = 2.0, .y = 0.0, .z = 0.0, .is_normalized = false};
    Vect v2 = {.x = 0.0, .y = 20.05, .z = -20.05, .is_normalized = false};

    Vect v1_exp = {.x = 1.0, .y = 0.0, .z = 0.0, .is_normalized = true};
    Vect v2_exp = {.x = 0.0, .y = 0.707106781, .z = -0.707106781, .is_normalized = true};

    if (vnormalize(&v1) < 0) {
        return "error, could not normalize";
    }
    if (vnormalize(&v2) < 0) {
        return "error, could not normalize";
    }

    mu_assert("error, vnormalize(v) != v_exp", vcmp(&v1, &v1_exp));
    mu_assert("error, norm(v) != 1.0", v1.is_normalized && dcmp(vnorm(&v1), 1.0));

    mu_assert("error, vnormalize(v) != v_exp", vcmp(&v2, &v2_exp));
    mu_assert("error, norm(v) != 1.0", v2.is_normalized && dcmp(vnorm(&v2), 1.0));
    return 0;
}

static char* testAdd() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = 1.1, .y = 1.2, .z = 1.3};
    Vect v3 = {.x = -0.05, .y = 0.5, .z = -20.3};

    Vect v1_exp = {.x = 2.1, .y = 3.2, .z = 4.3};
    Vect v2_exp = {.x = 1.05, .y = 1.7, .z = -19.0};
    Vect v3_exp = {.x = -0.1, .y = 1.0, .z = -40.6};

    vadd(&v1, &v2);
    vadd(&v2, &v3);
    vadd(&v3, &v3);

    mu_assert("error, vadd(v1,v2) != v_exp", vcmp(&v1, &v1_exp));
    mu_assert("error, vadd(v2,v3) != v_exp", vcmp(&v2, &v2_exp));
    mu_assert("error, vadd(v3,v3) != v_exp", vcmp(&v3, &v3_exp));
    return 0;
}

static char* testSubtract() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = 1.1, .y = 1.2, .z = 1.3};
    Vect v3 = {.x = -0.05, .y = 0.5, .z = -20.3};

    Vect v1_exp = {.x = -0.1, .y = 0.8, .z = 1.7};
    Vect v2_exp = {.x = 1.15, .y = 0.7, .z = 21.6};
    Vect v3_exp = {.x = 0.0, .y = 0.0, .z = 0.0};

    vsub(&v1, &v2);
    vsub(&v2, &v3);
    vsub(&v3, &v3);

    mu_assert("error, vsub(v1,v2) != v_exp", vcmp(&v1, &v1_exp));
    mu_assert("error, vsub(v2,v3) != v_exp", vcmp(&v2, &v2_exp));
    mu_assert("error, vsub(v3,v3) != v_exp", vcmp(&v3, &v3_exp));
    return 0;
}

static char* testCross() {
    Vect v0;
    Vect vi, vj, vk;
    Vect vni, vnj, vnk;

    vempty(&v0);
    vversorX(&vi);
    vversorY(&vj);
    vversorZ(&vk);

    vni = vi, vnegate(&vni);
    vnj = vj, vnegate(&vnj);
    vnk = vk, vnegate(&vnk);

    Vect vii, vij, vik;
    Vect vji, vjj, vjk;
    Vect vki, vkj, vkk;

    vcross(&vii, &vi, &vi);
    vcross(&vij, &vi, &vj);
    vcross(&vik, &vi, &vk);

    vcross(&vji, &vj, &vi);
    vcross(&vjj, &vj, &vj);
    vcross(&vjk, &vj, &vk);

    vcross(&vki, &vk, &vi);
    vcross(&vkj, &vk, &vj);
    vcross(&vkk, &vk, &vk);

    mu_assert("error, vcross(vi,vi) != 0", vcmp(&vii, &v0));
    mu_assert("error, vcross(vi,vj) != vk", vcmp(&vij, &vk));
    mu_assert("error, vcross(vi,vk) != -vj", vcmp(&vik, &vnj));

    mu_assert("error, vcross(vj,vi) != -vk", vcmp(&vji, &vnk));
    mu_assert("error, vcross(vj,vj) != 0", vcmp(&vjj, &v0));
    mu_assert("error, vcross(vj,vk) != vi", vcmp(&vjk, &vi));

    mu_assert("error, vcross(vk,vi) != vj", vcmp(&vki, &vj));
    mu_assert("error, vcross(vk,vj) != -vi", vcmp(&vkj, &vni));
    mu_assert("error, vcross(vk,vk) != 0", vcmp(&vkk, &v0));

    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = 1.0, .y = 1.0, .z = 1.0};

    Vect v_exp = {.x = -1.0, .y = 2.0, .z = -1.0};

    Vect v_cross, v_cross_inv;
    vcross(&v_cross, &v1, &v2);
    vcross(&v_cross_inv, &v2, &v1);
    vnegate(&v_cross_inv);

    mu_assert("error, vcross(v1,v2) != v_exp", vcmp(&v_cross, &v_exp));
    mu_assert("error, vcross(v1,v2) != vnegate(vcross(v2,v1))", vcmp(&v_cross, &v_cross_inv));
    return 0;
}

static char* testDot() {
    Vect vi, vj, vk;
    vversorX(&vi);
    vversorY(&vj);
    vversorZ(&vk);

    mu_assert("error, vdot(vi,vi) != 1", dcmp(vdot(&vi, &vi), 1.0));
    mu_assert("error, vdot(vi,vj) != 0", dcmp(vdot(&vi, &vj), 0.0));
    mu_assert("error, vdot(vi,vk) != 0", dcmp(vdot(&vi, &vk), 0.0));

    mu_assert("error, vdot(vj,vi) != 0", dcmp(vdot(&vj, &vi), 0.0));
    mu_assert("error, vdot(vj,vj) != 1", dcmp(vdot(&vj, &vj), 1.0));
    mu_assert("error, vdot(vj,vk) != 0", dcmp(vdot(&vj, &vk), 0.0));

    mu_assert("error, vdot(vk,vi) != 0", dcmp(vdot(&vk, &vi), 0.0));
    mu_assert("error, vdot(vk,vj) != 0", dcmp(vdot(&vk, &vj), 0.0));
    mu_assert("error, vdot(vk,vk) != 1", dcmp(vdot(&vk, &vk), 1.0));

    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = 1.0, .y = 1.0, .z = 1.0};

    double dot_exp = 6.0;
    mu_assert("error, vdot(v1,v2) != dot_exp", dcmp(vdot(&v1, &v2), dot_exp));
    return 0;
}

static char* testNorm() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = 0.1, .y = 0.2, .z = 0.3};

    double n1_exp = 14.0;
    double n2_exp = 0.14;

    mu_assert("error, vnormSquared(v1) != norm_exp", dcmp(vnormSquared(&v1), n1_exp));
    mu_assert("error, vnormSquared(v2) != norm_exp", dcmp(vnormSquared(&v2), n2_exp));

    n1_exp = 3.741657387;
    n2_exp = 0.374165738;

    mu_assert("error, vnorm(v1) != norm_exp", dcmp(vnorm(&v1), n1_exp));
    mu_assert("error, vnorm(v2) != norm_exp", dcmp(vnorm(&v2), n2_exp));
    return 0;
}

static char* testCompare() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v3 = {.x = 1.0, .y = 1.0, .z = 1.0};

    mu_assert("error, v1 != v2", vcmp(&v1, &v2));
    mu_assert("error, v1 == v3", !vcmp(&v1, &v3));

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