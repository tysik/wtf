#include "Quaternions.h"
#include "MathUtils.h"

#include <stdlib.h>

Quat empty() {
    Quat q = {.w = 1.0, .i = 0.0, .j = 0.0, .k = 0.0};
    return q;
}

Quat from(double w, double i, double j, double k) {
    Quat q = {.w = w, .i = i, .j = j, .k = k};
    return q;
}

Quat qreal(const Quat* q) {
    Quat qx = {.w = q->w, .i = 0.0, .j = 0.0, .k = 0.0};
    return qx;
}

Quat qpure(const Quat* q) {
    Quat qx = {.w = 0.0, .i = q->i, .j = q->j, .k = q->k};
    return qx;
}

Quat qconj(const Quat* q) {
    Quat qx = {.w = q->w, .i = -q->i, .j = -q->j, .k = -q->k};
    return qx;
}

bool qcmp(const Quat* q1, const Quat* q2) {
    return dcmp(q1->w, q2->w) && dcmp(q1->i, q2->i) && dcmp(q1->j, q2->j) && dcmp(q1->k, q2->k);
}

Quat qadd(const Quat* q1, const Quat* q2) {
    Quat q = {.w = q1->w + q2->w, .i = q1->i + q2->i, .j = q1->j + q2->j, .k = q1->k + q2->k};
    return q;
}

Quat qsub(const Quat* q1, const Quat* q2) {
    Quat q = {.w = q1->w - q2->w, .i = q1->i - q2->i, .j = q1->j - q2->j, .k = q1->k - q2->k};
    return q;
}

Quat qmul(const Quat* q1, const Quat* q2) {
    Quat q = {.w = q1->w * q2->w - q1->i * q2->i - q1->j * q2->j - q1->k * q2->k,
              .i = q1->w * q2->i + q1->i * q2->w + q1->j * q2->k - q1->k * q2->j,
              .j = q1->w * q2->j + q1->j * q2->w + q1->k * q2->i - q1->i * q2->k,
              .k = q1->w * q2->k + q1->k * q2->w + q1->i * q2->j - q1->j * q2->i};
    return q;
}

Quat qscale(double k, const Quat* q) {
    Quat qx = {.w = q->w * k, .i = q->i * k, .j = q->j * k, .k = q->k * k};
    return qx;
}

double qnorm(const Quat* q) { return q->w * q->w + q->i * q->i + q->j * q->j + q->k * q->k; }
