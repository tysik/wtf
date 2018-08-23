#include "quaternions.h"

#include <stdlib.h>

Quat empty() {
    Quat q = {.w = 1.0, .i = 0.0, .j = 0.0, .k = 0.0};
    return q;
}

Quat from(double w, double i, double j, double k) {
    Quat q = {.w = w, .i = i, .j = j, .k = k};
}