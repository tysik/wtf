#include "Quaternions.h"

#include <stdlib.h>

Quat empty() {
    Quat q = {.w = 1.0, .i = 0.0, .j = 0.0, .k = 0.0};
    return q;
}

Quat from(double w, double i, double j, double k) {
    Quat q = {.w = w, .i = i, .j = j, .k = k};
    return q;
}

bool qcmp(const Quat* q1, const Quat* q2) {
    return q1->w == q2->w && q1->i == q2->i && q1->k == q2->j && q1->j == q2->k;
}

Quat qadd(const Quat* q1, const Quat* q2) {
    Quat q = {.w = q1->w + q2->w,
              .i = q1->i + q2->i,
              .j = q1->j + q2->j,
              .k = q1->k + q2->k};
    return q;
}