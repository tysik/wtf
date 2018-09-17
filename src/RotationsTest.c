#include "Rotations.h"
#include "MathUtils.h"
#include "MinTest.h"

#include <stdio.h>

static int tests_run = 0;

static char* testRotate() {
    Vect axis = {.x = 1.0, .y = 0.0, .z = 0.0, .is_normalized = true};
    Quat rotor = qrotor(3.1415926536 / 2.0, &axis);

    Vect to_rotate = {.x = 0.0, .y = 1.0, .z = 0.0, .is_normalized = true};
    Vect rotated = rotate(&to_rotate, &rotor);
    Vect expected = {.x = 0.0, .y = 0.0, .z = 1.0, .is_normalized = true};

    mu_assert("error, v_expected != rotate(v,q)", vcmp(&rotated, &expected));
    mu_assert("error, norm(v) != norm(rotate(v,q))",
              dcmp(vnormSquared(&to_rotate), vnormSquared(&rotated)));

    return 0;
}

static char* all_tests() {
    mu_run_test(testRotate);
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