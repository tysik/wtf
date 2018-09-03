#include "Quaternions.h"
#include "MathUtils.h"

#include <math.h>

Quat qempty() {
    Quat q = {.w = 1.0, .v = vempty()};
    return q;
}

Quat qreal(const Quat* q) {
    Quat qx = {.s = q->s, .v = vempty()};
    return qx;
}

Quat qpure(const Quat* q) {
    Quat qx = {.s = 0.0, .v = q->v};
    return qx;
}

Quat qconj(const Quat* q) {
    Quat qx = {.s = q->s, .v = vneg(&q->v)};
    return qx;
}

bool qcmp(const Quat* q1, const Quat* q2) {
    return dcmp(q1->s, q2->s) && vcmp(&q1->v, &q2->v);
}

Quat qadd(const Quat* q1, const Quat* q2) {
    Quat q = {.s = q1->s + q2->s, .v = vadd(&q1->v, &q2->v)};
    return q;
}

Quat qsub(const Quat* q1, const Quat* q2) {
    Quat q = {.s = q1->s - q2->s, .v = vsub(&q1->v, &q2->v)};
    return q;
}

Quat qmul(const Quat* q1, const Quat* q2) {
    // Quat q = {.w = q1->w * q2->w - q1->i * q2->i - q1->j * q2->j - q1->k * q2->k,
    //           .i = q1->w * q2->i + q1->i * q2->w + q1->j * q2->k - q1->k * q2->j,
    //           .j = q1->w * q2->j + q1->j * q2->w + q1->k * q2->i - q1->i * q2->k,
    //           .k = q1->w * q2->k + q1->k * q2->w + q1->i * q2->j - q1->j * q2->i};
    Vect v1 = vscale(q1->s, &q2->v);
    Vect v2 = vscale(q2->s, &q1->v);
    Vect v3 = vcross(&q1->v, &q2->v);
    Vect vx = vadd(&v1, &v2);
    
    double s = q1->s * q2->s - vdot(&q1->v, &q2->v);
    Vect v = vadd(&vx, &v3);
    Quat q = {.s = s, .v = v};
    return q;
}

Quat qscale(double k, const Quat* q) {
    Quat qx = {.s = k * q->s, .v = vscale(k, &q->v)};
    return qx;
}

double qnorm(const Quat* q) {
    return sqrt(qnormSquared(q));
}

double qnormSquared(const Quat* q) {
    return q->s * q->s + vnormSquared(&q->v);
}
