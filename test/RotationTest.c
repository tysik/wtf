#include "Rotation.h"
#include "MathUtils.h"
#include "Matrix.h"
#include "MinTest.h"
#include "Vector.h"

#include <stdio.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

static int tests_run = 0;

static char* test_construction() {
    wtf_rot_t r_x_expected = {.data = {{1.0, 0.0, 0.0}, {0.0, 0.0, -1.0}, {0.0, 1.0, 0.0}}};
    wtf_rot_t r_y_expected = {.data = {{0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {-1.0, 0.0, 0.0}}};
    wtf_rot_t r_z_expected = {.data = {{0.0, -1.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}}};

    wtf_rot_t r_x = wtf_rot_x(M_PI / 2.0);
    wtf_rot_t r_y = wtf_rot_y(M_PI / 2.0);
    wtf_rot_t r_z = wtf_rot_z(M_PI / 2.0);

    mu_assert("error, r_x != expected", wtf_compare_mat(&r_x, &r_x_expected));
    mu_assert("error, r_y != expected", wtf_compare_mat(&r_y, &r_y_expected));
    mu_assert("error, r_z != expected", wtf_compare_mat(&r_z, &r_z_expected));

    return 0;
}

static char* test_rotate() {
    wtf_rot_t r_x = wtf_rot_x(M_PI / 2.0);
    wtf_rot_t r_y = wtf_rot_y(M_PI / 2.0);
    wtf_rot_t r_z = wtf_rot_z(M_PI / 2.0);
    wtf_rot_t r_xy = wtf_mat_multiply(&r_x, &r_y);
    wtf_rot_t r_xyz = wtf_mat_multiply(&r_xy, &r_z);

    wtf_vec_t v = wtf_versor_x();
    wtf_vec_t v1_expected = {.x = 1.0, .y = 0.0, .z = 0.0};
    wtf_vec_t v2_expected = {.x = 0.0, .y = 0.0, .z = -1.0};
    wtf_vec_t v3_expected = {.x = 0.0, .y = 1.0, .z = 0.0};
    wtf_vec_t v4_expected = {.x = 0.0, .y = 1.0, .z = 0.0};
    wtf_vec_t v5_expected = {.x = 0.0, .y = 0.0, .z = 1.0};

    wtf_vec_t v1 = wtf_rot_rotate(&r_x, &v);
    wtf_vec_t v2 = wtf_rot_rotate(&r_y, &v);
    wtf_vec_t v3 = wtf_rot_rotate(&r_z, &v);
    wtf_vec_t v4 = wtf_rot_rotate(&r_xy, &v);
    wtf_vec_t v5 = wtf_rot_rotate(&r_xyz, &v);

    mu_assert("error, v1 != expected", wtf_compare_vec(&v1, &v1_expected));
    mu_assert("error, v2 != expected", wtf_compare_vec(&v2, &v2_expected));
    mu_assert("error, v3 != expected", wtf_compare_vec(&v3, &v3_expected));
    mu_assert("error, v4 != expected", wtf_compare_vec(&v4, &v4_expected));
    mu_assert("error, v5 != expected", wtf_compare_vec(&v5, &v5_expected));

    return 0;
}

static char* test_norms() {
    wtf_rot_t r1 = wtf_rot_x(M_PI / 4.0);
    wtf_rot_t r2 = wtf_rot_y(M_PI / 6.0);
    wtf_rot_t r3 = wtf_rot_z(M_PI / 12.0);
    wtf_rot_t r4 = wtf_mat_multiply(&r1, &r2);
    wtf_rot_t r5 = wtf_mat_multiply(&r3, &r4);
    wtf_vec_t expected_norms = {.x = 1.0, .y = 1.0, .z = 1.0};

    wtf_vec_t r1_norms = wtf_rot_norms(&r1);
    wtf_vec_t r2_norms = wtf_rot_norms(&r2);
    wtf_vec_t r3_norms = wtf_rot_norms(&r3);
    wtf_vec_t r4_norms = wtf_rot_norms(&r4);
    wtf_vec_t r5_norms = wtf_rot_norms(&r5);

    mu_assert("error, r1 norms != expected", wtf_compare_vec(&r1_norms, &expected_norms));
    mu_assert("error, r2 norms != expected", wtf_compare_vec(&r2_norms, &expected_norms));
    mu_assert("error, r3 norms != expected", wtf_compare_vec(&r3_norms, &expected_norms));
    mu_assert("error, r4 norms != expected", wtf_compare_vec(&r4_norms, &expected_norms));
    mu_assert("error, r5 norms != expected", wtf_compare_vec(&r5_norms, &expected_norms));

    return 0;
}

static char* test_compare() {
    wtf_rot_t r1 = wtf_rot_y(M_PI / 2.0);
    wtf_rot_t r2 = {.data = {{0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {-1.0, 0.0, 0.0}}};
    wtf_rot_t r3 = wtf_rot_z(M_PI / 2.0);

    mu_assert("error, r1 != r2", wtf_compare_mat(&r1, &r2) == true);
    mu_assert("error, r1 == r3", wtf_compare_mat(&r1, &r3) == false);

    return 0;
}

static char* all_tests() {
    mu_run_test(test_construction);
    mu_run_test(test_rotate);
    mu_run_test(test_norms);
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
