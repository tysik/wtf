#include "Matrix.h"
#include "MathUtils.h"
#include "MinTest.h"

#include <stdio.h>
#include <string.h>

static int tests_run = 0;

static char* test_constructors() {
    wtf_scalar_t s = 2.5;
    wtf_vec_t v1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    wtf_vec_t v2 = {.x = 5.0, .y = 10.0, .z = 15.0};

    wtf_mat_t eye_expected = {.data = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}}};
    wtf_mat_t diag_expected = {.data = {{2.5, 0.0, 0.0}, {0.0, 2.5, 0.0}, {0.0, 0.0, 2.5}}};
    wtf_mat_t diag_vec_expected = {.data = {{1.0, 0.0, 0.0}, {0.0, 2.0, 0.0}, {0.0, 0.0, 3.0}}};
    wtf_mat_t skew_expected = {.data = {{0.0, -15.0, 10.0}, {15.0, 0.0, -5.0}, {-10.0, 5.0, 0.0}}};
    wtf_mat_t outer_prod_expected = {
        .data = {{5.0, 10.0, 15.0}, {10.0, 20.0, 30.0}, {15.0, 30.0, 45.0}}};

    wtf_mat_t eye = wtf_mat_eye();
    wtf_mat_t diag = wtf_mat_diag(s);
    wtf_mat_t diag_vec = wtf_mat_diag_vec(&v1);
    wtf_mat_t skew = wtf_mat_skew(&v2);
    wtf_mat_t outer_prod = wtf_mat_outer_product(&v1, &v2);

    mu_assert("error, eye != expected", wtf_compare_mat(&eye, &eye_expected));
    mu_assert("error, diag != expected", wtf_compare_mat(&diag, &diag_expected));
    mu_assert("error, diag_vec != expected", wtf_compare_mat(&diag_vec, &diag_vec_expected));
    mu_assert("error, skew != expected", wtf_compare_mat(&skew, &skew_expected));
    mu_assert("error, outer_prod != expected", wtf_compare_mat(&outer_prod, &outer_prod_expected));

    return 0;
}

// static char* test_multiply() {
//     wtf_rot_t r_x = wtf_rot_x(M_PI / 2.0);
//     wtf_rot_t r_y = wtf_rot_y(M_PI / 2.0);
//     wtf_rot_t r_z = wtf_rot_z(M_PI / 2.0);
//     wtf_rot_t r_xy_expected = {.matrix = {{0.0, 0.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}}};
//     wtf_rot_t r_xyz_expected = {.matrix = {{0.0, 0.0, 1.0}, {0.0, -1.0, 0.0}, {1.0, 0.0, 0.0}}};

//     wtf_rot_t r_xy = wtf_rot_multiply(&r_x, &r_y);
//     wtf_rot_t r_xyz = wtf_rot_multiply(&r_xy, &r_z);

//     mu_assert("error, r_xy != expected", wtf_compare_rot(&r_xy, &r_xy_expected));
//     mu_assert("error, r_xyz != expected", wtf_compare_rot(&r_xyz, &r_xyz_expected));

//     return 0;
// }

// static char* test_determinant() {
//     PREPARE_TEST_MATRICES();
//     wtf_scalar_t det_expected = 1.0;

//     wtf_scalar_t det_r1 = wtf_rot_determinant(&r1);
//     wtf_scalar_t det_r2 = wtf_rot_determinant(&r2);
//     wtf_scalar_t det_r3 = wtf_rot_determinant(&r3);
//     wtf_scalar_t det_r4 = wtf_rot_determinant(&r4);
//     wtf_scalar_t det_r5 = wtf_rot_determinant(&r5);

//     mu_assert("error, det(r1) != 1", wtf_dcmp(det_r1, det_expected));
//     mu_assert("error, det(r2) != 1", wtf_dcmp(det_r2, det_expected));
//     mu_assert("error, det(r3) != 1", wtf_dcmp(det_r3, det_expected));
//     mu_assert("error, det(r4) != 1", wtf_dcmp(det_r4, det_expected));
//     mu_assert("error, det(r5) != 1", wtf_dcmp(det_r5, det_expected));

//     return 0;
// }

static char* test_orthogonal() {
    // wtf_rot_t r1 = wtf_rot_x(M_PI / 4.0);
    // wtf_rot_t r2 = wtf_rot_y(M_PI / 6.0);
    // wtf_rot_t r3 = wtf_rot_z(M_PI / 12.0);
    // wtf_rot_t r4 = wtf_rot_multiply(&r1, &r2);
    // wtf_rot_t r5 = wtf_rot_multiply(&r3, &r4);

    // bool r1_orthogonal = wtf_rot_is_orthogonal(&r1);
    // bool r2_orthogonal = wtf_rot_is_orthogonal(&r2);
    // bool r3_orthogonal = wtf_rot_is_orthogonal(&r3);
    // bool r4_orthogonal = wtf_rot_is_orthogonal(&r4);
    // bool r5_orthogonal = wtf_rot_is_orthogonal(&r5);

    // mu_assert("error, r1 is not ortogonal", r1_orthogonal);
    // mu_assert("error, r2 is not ortogonal", r2_orthogonal);
    // mu_assert("error, r3 is not ortogonal", r3_orthogonal);
    // mu_assert("error, r4 is not ortogonal", r4_orthogonal);
    // mu_assert("error, r5 is not ortogonal", r5_orthogonal);

    return 0;
}

static char* all_tests() {
    mu_run_test(test_constructors);
    mu_run_test(test_orthogonal);

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