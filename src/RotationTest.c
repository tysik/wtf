#include "Rotation.h"
#include "MathUtils.h"
#include "MinTest.h"
#include "Vector.h"

#include <stdio.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

#define PREPARE_TEST_MATRICES()                                                                    \
    wtf_rot_t r1 = wtf_rot_x(M_PI / 4.0);                                                          \
    wtf_rot_t r2 = wtf_rot_y(M_PI / 6.0);                                                          \
    wtf_rot_t r3 = wtf_rot_z(M_PI / 12.0);                                                         \
    wtf_rot_t r4 = wtf_rot_multiply(&r1, &r2);                                                     \
    wtf_rot_t r5 = wtf_rot_multiply(&r3, &r4)

static int tests_run = 0;

static char* test_construction() {
    wtf_rot_t r_eye_expected = {.matrix = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}}};
    wtf_rot_t r_x_expected = {.matrix = {{1.0, 0.0, 0.0}, {0.0, 0.0, -1.0}, {0.0, 1.0, 0.0}}};
    wtf_rot_t r_y_expected = {.matrix = {{0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {-1.0, 0.0, 0.0}}};
    wtf_rot_t r_z_expected = {.matrix = {{0.0, -1.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}}};

    wtf_rot_t r_eye = wtf_rot_eye();
    wtf_rot_t r_x = wtf_rot_x(M_PI / 2.0);
    wtf_rot_t r_y = wtf_rot_y(M_PI / 2.0);
    wtf_rot_t r_z = wtf_rot_z(M_PI / 2.0);

    mu_assert("error, r_eye != expected", wtf_compare_rot(&r_eye, &r_eye_expected));
    mu_assert("error, r_x != expected", wtf_compare_rot(&r_x, &r_x_expected));
    mu_assert("error, r_y != expected", wtf_compare_rot(&r_y, &r_y_expected));
    mu_assert("error, r_z != expected", wtf_compare_rot(&r_z, &r_z_expected));

    return 0;
}

static char* test_multiply() {
    wtf_rot_t r_x = wtf_rot_x(M_PI / 2.0);
    wtf_rot_t r_y = wtf_rot_y(M_PI / 2.0);
    wtf_rot_t r_z = wtf_rot_z(M_PI / 2.0);
    wtf_rot_t r_xy_expected = {.matrix = {{0.0, 0.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}}};
    wtf_rot_t r_xyz_expected = {.matrix = {{0.0, 0.0, 1.0}, {0.0, -1.0, 0.0}, {1.0, 0.0, 0.0}}};

    wtf_rot_t r_xy = wtf_rot_multiply(&r_x, &r_y);
    wtf_rot_t r_xyz = wtf_rot_multiply(&r_xy, &r_z);

    mu_assert("error, r_xy != expected", wtf_compare_rot(&r_xy, &r_xy_expected));
    mu_assert("error, r_xyz != expected", wtf_compare_rot(&r_xyz, &r_xyz_expected));

    return 0;
}

static char* test_rotate() {
    wtf_rot_t r_x = wtf_rot_x(M_PI / 2.0);
    wtf_rot_t r_y = wtf_rot_y(M_PI / 2.0);
    wtf_rot_t r_z = wtf_rot_z(M_PI / 2.0);
    wtf_rot_t r_xy = wtf_rot_multiply(&r_x, &r_y);
    wtf_rot_t r_xyz = wtf_rot_multiply(&r_xy, &r_z);

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
    PREPARE_TEST_MATRICES();
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

static char* test_determinant() {
    PREPARE_TEST_MATRICES();
    wtf_scalar_t det_expected = 1.0;

    wtf_scalar_t det_r1 = wtf_rot_determinant(&r1);
    wtf_scalar_t det_r2 = wtf_rot_determinant(&r2);
    wtf_scalar_t det_r3 = wtf_rot_determinant(&r3);
    wtf_scalar_t det_r4 = wtf_rot_determinant(&r4);
    wtf_scalar_t det_r5 = wtf_rot_determinant(&r5);

    mu_assert("error, det(r1) != 1", wtf_dcmp(det_r1, det_expected));
    mu_assert("error, det(r2) != 1", wtf_dcmp(det_r2, det_expected));
    mu_assert("error, det(r3) != 1", wtf_dcmp(det_r3, det_expected));
    mu_assert("error, det(r4) != 1", wtf_dcmp(det_r4, det_expected));
    mu_assert("error, det(r5) != 1", wtf_dcmp(det_r5, det_expected));

    return 0;
}

static char* test_orthogonal() {
    PREPARE_TEST_MATRICES();

    bool r1_orthogonal = wtf_rot_is_orthogonal(&r1);
    bool r2_orthogonal = wtf_rot_is_orthogonal(&r2);
    bool r3_orthogonal = wtf_rot_is_orthogonal(&r3);
    bool r4_orthogonal = wtf_rot_is_orthogonal(&r4);
    bool r5_orthogonal = wtf_rot_is_orthogonal(&r5);

    mu_assert("error, r1 is not ortogonal", r1_orthogonal);
    mu_assert("error, r2 is not ortogonal", r2_orthogonal);
    mu_assert("error, r3 is not ortogonal", r3_orthogonal);
    mu_assert("error, r4 is not ortogonal", r4_orthogonal);
    mu_assert("error, r5 is not ortogonal", r5_orthogonal);

    return 0;
}

static char* test_compare() {
    wtf_rot_t r1 = wtf_rot_y(M_PI / 2.0);
    wtf_rot_t r2 = {.matrix = {{0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {-1.0, 0.0, 0.0}}};
    wtf_rot_t r3 = wtf_rot_z(M_PI / 2.0);

    mu_assert("error, r1 != r2", wtf_compare_rot(&r1, &r2) == true);
    mu_assert("error, r1 == r3", wtf_compare_rot(&r1, &r3) == false);

    return 0;
}

static char* all_tests() {
    mu_run_test(test_construction);
    mu_run_test(test_multiply);
    mu_run_test(test_rotate);
    mu_run_test(test_norms);
    mu_run_test(test_determinant);
    mu_run_test(test_orthogonal);
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
