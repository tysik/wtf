#include "Vectors.h"
#include "MathUtils.h"
#include "MinTest.h"

#include <stdio.h>

static int tests_run = 0;

static char* testNeg() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = -0.001, .y = 20.05, .z = -3000.0};

    Vect v1_neg_expected = {.x = -1.0, .y = -2.0, .z = -3.0};
    Vect v2_neg_expected = {.x = 0.001, .y = -20.05, .z = 3000.0};

    Vect v1_neg = vneg(&v1);
    Vect v2_neg = vneg(&v2);

    mu_assert("error, v1_expected != vneg(v1)", vcmp(&v1_neg, &v1_neg_expected));
    mu_assert("error, v2_expected != vneg(v2)", vcmp(&v2_neg, &v2_neg_expected));
    return 0;
}

static char* testNormal() {
    Vect v1 = {.x = 2.0, .y = 0.0, .z = 0.0};
    Vect v2 = {.x = 0.0, .y = 20.05, .z = -20.05};

    Vect v1_normal_expected = {.x = 1.0, .y = 0.0, .z = 0.0};
    Vect v2_normal_expected = {.x = 0.0, .y = 0.707106781, .z = -0.707106781};

    Vect v1_normal = vnormal(&v1);
    Vect v2_normal = vnormal(&v2);

    mu_assert("error, v1_expected != vnormal(v1)", vcmp(&v1_normal, &v1_normal_expected));
    mu_assert("error, norm(v1_expected) != 1.0",
              v1_normal.is_normalized && dcmp(vnorm(&v1_normal), 1.0));
    mu_assert("error, v2_expected != vnormal(v2)", vcmp(&v2_normal, &v2_normal_expected));
    mu_assert("error, norm(v2_expected) != 1.0",
              v2_normal.is_normalized && dcmp(vnorm(&v2_normal), 1.0));
    return 0;
}

static char* testScale() {
    Vect v = {.x = 1.0, .y = 2.0, .z = 3.0};
    double k = 2.5;

    Vect v_scaled_expected = {.x = 2.5, .y = 5.0, .z = 7.5};
    Vect v_scaled = vscale(k, &v);

    mu_assert("error, v_expected != vscale(k,v)", vcmp(&v_scaled, &v_scaled_expected));
    return 0;
}

static char* testAdd() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = 1.1, .y = 1.2, .z = 1.3};

    Vect v_expected = {.x = 2.1, .y = 3.2, .z = 4.3};
    Vect v_added = vadd(&v1, &v2);

    mu_assert("error, v_expected != vadd(v1,v2)", vcmp(&v_added, &v_expected));
    return 0;
}

static char* testSubtract() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = 1.1, .y = 1.2, .z = 1.3};

    Vect v_expected = {.x = -0.1, .y = 0.8, .z = 1.7};
    Vect v_subtracted = vsub(&v1, &v2);

    mu_assert("error, v_expected != vsub(v1,v2)", vcmp(&v_subtracted, &v_expected));
    return 0;
}

static char* testCross() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = 1.0, .y = 1.0, .z = 1.0};

    Vect v_expected = {.x = -1.0, .y = 2.0, .z = -1.0};
    Vect v_cross = vcross(&v1, &v2);
    Vect v_cross_neg = vcross(&v2, &v1);
    Vect v_cross_negx = vneg(&v_cross_neg);

    mu_assert("error, v_expected != vcross(v1,v2)", vcmp(&v_cross, &v_expected));
    mu_assert("error, vcross(v1,v2) != vneg(vcross(v2,v1))", vcmp(&v_cross, &v_cross_negx));

    Vect v0 = vempty();
    Vect vi = {.x = 1.0, .y = 0.0, .z = 0.0, .is_normalized = true};
    Vect vj = {.x = 0.0, .y = 1.0, .z = 0.0, .is_normalized = true};
    Vect vk = {.x = 0.0, .y = 0.0, .z = 1.0, .is_normalized = true};

    Vect vni = vneg(&vi);
    Vect vnj = vneg(&vj);
    Vect vnk = vneg(&vk);

    Vect vii = vcross(&vi, &vi);
    Vect vij = vcross(&vi, &vj);
    Vect vik = vcross(&vi, &vk);

    Vect vji = vcross(&vj, &vi);
    Vect vjj = vcross(&vj, &vj);
    Vect vjk = vcross(&vj, &vk);

    Vect vki = vcross(&vk, &vi);
    Vect vkj = vcross(&vk, &vj);
    Vect vkk = vcross(&vk, &vk);

    mu_assert("error, vcross(vi,vi) != 0", vcmp(&vii, &v0));
    mu_assert("error, vcross(vi,vj) != vk", vcmp(&vij, &vk));
    mu_assert("error, vcross(vi,vk) != -vj", vcmp(&vik, &vnj));

    mu_assert("error, vcross(vj,vi) != -vk", vcmp(&vji, &vnk));
    mu_assert("error, vcross(vj,vj) != 0", vcmp(&vjj, &v0));
    mu_assert("error, vcross(vj,vk) != vi", vcmp(&vjk, &vi));

    mu_assert("error, vcross(vk,vi) != vj", vcmp(&vki, &vj));
    mu_assert("error, vcross(vk,vj) != -vi", vcmp(&vkj, &vni));
    mu_assert("error, vcross(vk,vk) != 0", vcmp(&vkk, &v0));

    return 0;
}

static char* testDot() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = 1.0, .y = 1.0, .z = 1.0};

    double dot_expected = 6.0;
    double dot = vdot(&v1, &v2);

    mu_assert("error, dot_expected != dot(v1,v2)", dcmp(dot, dot_expected));

    Vect vi = {.x = 1.0, .y = 0.0, .z = 0.0, .is_normalized = true};
    Vect vj = {.x = 0.0, .y = 1.0, .z = 0.0, .is_normalized = true};
    Vect vk = {.x = 0.0, .y = 0.0, .z = 1.0, .is_normalized = true};

    mu_assert("error, vdot(vi,vi) != 1", dcmp(vdot(&vi, &vi), 1.0));
    mu_assert("error, vdot(vi,vj) != 0", dcmp(vdot(&vi, &vj), 0.0));
    mu_assert("error, vdot(vi,vk) != 0", dcmp(vdot(&vi, &vk), 0.0));

    mu_assert("error, vdot(vj,vi) != 0", dcmp(vdot(&vj, &vi), 0.0));
    mu_assert("error, vdot(vj,vj) != 1", dcmp(vdot(&vj, &vj), 1.0));
    mu_assert("error, vdot(vj,vk) != 0", dcmp(vdot(&vj, &vk), 0.0));

    mu_assert("error, vdot(vk,vi) != 0", dcmp(vdot(&vk, &vi), 0.0));
    mu_assert("error, vdot(vk,vj) != 0", dcmp(vdot(&vk, &vj), 0.0));
    mu_assert("error, vdot(vk,vk) != 1", dcmp(vdot(&vk, &vk), 1.0));

    return 0;
}

static char* testNorm() {
    Vect v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    Vect v2 = {.x = 0.1, .y = 0.2, .z = 0.3};

    double n1_sqr_expected = 14.0;
    double n2_sqr_expected = 0.14;

    double n1_sqr = vnormSquared(&v1);
    double n2_sqr = vnormSquared(&v2);

    mu_assert("error, snorm_expected != snorm(v1)", dcmp(n1_sqr, n1_sqr_expected));
    mu_assert("error, snorm_expected != snorm(v2)", dcmp(n2_sqr, n2_sqr_expected));

    double n1_expected = 3.741657387;
    double n2_expected = 0.374165738;

    double n1 = vnorm(&v1);
    double n2 = vnorm(&v2);

    mu_assert("error, norm_expected != norm(v1)", dcmp(n1, n1_expected));
    mu_assert("error, norm_expected != norm(v2)", dcmp(n2, n2_expected));

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
    mu_run_test(testNeg);
    mu_run_test(testNormal);
    mu_run_test(testScale);
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