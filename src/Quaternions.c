#include "Quaternions.h"
#include "MathUtils.h"

#include <math.h>

Quat qempty() {
    Quat q = {.s = 0.0, .v = vempty()};
    q.is_normalized = false;
    return q;
}

Quat qconj(const Quat* q) {
    Quat qx = {.s = q->s, .v = vneg(&q->v)};
    return qx;
}

Quat qunit(const Quat* q) {
    if (q->is_normalized) {
        return *q;
    } else {
        double norm = qnorm(q);
        if (norm > 0.0) {
            Quat qx = qscale(1.0 / norm, q);
            qx.is_normalized = true;
            return qx;
        } else {
            return qempty();
        }
    }
}

Quat qinv(const Quat* q) {
    Quat qx = qconj(q);
    if (q->is_normalized) {
        return qx;
    } else {
        double norm_squared = qnormSquared(q);
        return (norm_squared > 0.0) ? qscale(1.0 / norm_squared, &qx) : qempty();
    }
}

Quat qscale(double k, const Quat* q) {
    Quat qx = {.s = k * q->s, .v = vscale(k, &q->v)};
    return qx;
}

Quat qrotor(double theta, const Vect* axis) {
    Vect normalized_axis = vnormal(axis);
    Quat q = {.s = cos(theta / 2.0), .v = vscale(sin(theta / 2.0), &normalized_axis)};
    q.is_normalized = true;
    return q;
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
    // q1 * q2 = [s1, v1] * [s2, v2] =
    // [s1 * s2 - dot(v1,v2), s1 * v2 + s2 * v1 + cross(v1,v2)]
    double s = q1->s * q2->s - vdot(&q1->v, &q2->v);

    Vect v_part1 = vscale(q1->s, &q2->v);
    Vect v_part2 = vscale(q2->s, &q1->v);
    Vect v_part3 = vcross(&q1->v, &q2->v);
    Vect v_part4 = vadd(&v_part1, &v_part2);
    Vect v = vadd(&v_part3, &v_part4);

    Quat q = {.s = s, .v = v};
    return q;
}

Quat qdiv(const Quat* q1, const Quat* q2) {
    Quat q2_inv = qinv(q2);
    return qmul(q1, &q2_inv);
}

Vect qpure(const Quat* q) {
    Vect v = q->v;
    v.is_normalized = false;
    return v;
}

double qreal(const Quat* q) {
    return q->s;
}

double qnorm(const Quat* q) {
    return (q->is_normalized) ? 1.0 : sqrt(qnormSquared(q));
}

double qnormSquared(const Quat* q) {
    return (q->is_normalized) ? 1.0 : q->s * q->s + vnormSquared(&q->v);
}

bool qcmp(const Quat* q1, const Quat* q2) {
    return dcmp(q1->s, q2->s) && vcmp(&q1->v, &q2->v);
}