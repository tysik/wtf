#include "Rotation.h"
#include "MathUtils.h"
#include "MinTest.h"

#include <stdio.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

static int tests_run = 0;

static char* test_construction() {
    wtf_rot_t rot_eye = wtf_rot_eye();
    wtf_rot_t rot_x = wtf_rot_x(M_PI / 2.0);
    wtf_rot_t rot_y = wtf_rot_y(M_PI / 2.0);
    wtf_rot_t rot_z = wtf_rot_z(M_PI / 2.0);

    wtf_rot_t rot_eye_exp = {.matrix = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}}};
    wtf_rot_t rot_x_exp = {.matrix = {{1.0, 0.0, 0.0}, {0.0, 0.0, -1.0}, {0.0, 1.0, 0.0}}};
    wtf_rot_t rot_y_exp = {.matrix = {{0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {-1.0, 0.0, 0.0}}};
    wtf_rot_t rot_z_exp = {.matrix = {{0.0, -1.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}}};

    wtf_print_rot(&rot_x);
    wtf_print_rot(&rot_y);
    wtf_print_rot(&rot_z);

    mu_assert("error, rot_eye != expected", wtf_compare_rot(&rot_eye, &rot_eye_exp));
    mu_assert("error, rot_x != expected", wtf_compare_rot(&rot_x, &rot_x_exp));
    mu_assert("error, rot_y != expected", wtf_compare_rot(&rot_y, &rot_y_exp));
    mu_assert("error, rot_z != expected", wtf_compare_rot(&rot_z, &rot_z_exp));

    return 0;
}

static char* all_tests() {
    mu_run_test(test_construction);
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
