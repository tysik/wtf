#include "Quaternions.h"
#include "MathUtils.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

void qempty(Quat* q) {
    q->s = 0.0;
    vempty(&q->v);
}

void qpure(Quat* q, const Vect* v) {
    q->s = 0.0;
    q->v = *v;
}

void qreal(Quat* q, double s) {
    q->s = s;
    vempty(&q->v);
}

void qrotor(Quat* q, double theta, const Vect* axis) {
    assert(axis->is_normalized && "Using non-versor axis for rotor");
    q->s = cos(theta / 2.0);
    q->v = *axis;
    vscale(&q->v, sin(theta / 2.0));
    q->is_normalized = true;
}

void qconjugate(Quat* q) {
    vnegate(&q->v);
}

void qscale(Quat* q, double k) {
    q->s = k * q->s;
    vscale(&q->v, k);
}

int qnormalize(Quat* q) {
    if (q->is_normalized) {
        return 1;
    } else {
        double norm = qnorm(q);
        if (norm > 0.0) {
            qscale(q, 1.0 / norm);
            q->is_normalized = true;
            return 0;
        } else {
            return -1;
        }
    }
}

int qinverse(Quat* q) {
    qconjugate(q);
    if (q->is_normalized) {
        return 0;
    } else {
        double norm_squared = qnormSquared(q);
        if (norm_squared > 0.0) {
            qscale(q, 1.0 / norm_squared);
            return 0;
        } else {
            return -1;
        }
    }
}

void qadd(Quat* q1, const Quat* q2) {
    q1->s = q1->s + q2->s;
    vadd(&q1->v, &q2->v);
}

void qsub(Quat* q1, const Quat* q2) {
    q1->s = q1->s - q2->s;
    vsub(&q1->v, &q2->v);
}

void qmul(Quat* q, const Quat* q1, const Quat* q2) {
    // q1 * q2 = [s1, v1] * [s2, v2] =
    // [s1 * s2 - dot(v1,v2), s1 * v2 + s2 * v1 + cross(v1,v2)]
    q->s = q1->s * q2->s - vdot(&q1->v, &q2->v);
    vcross(&q->v, &q1->v, &q2->v);

    Vect v_aux = q1->v;
    vscale(&v_aux, q2->s);
    vadd(&q->v, &v_aux);

    v_aux = q2->v;
    vscale(&v_aux, q1->s);
    vadd(&q->v, &v_aux);
}

int qdiv(Quat* q, const Quat* q1, const Quat* q2) {
    Quat q2_inv = *q2;
    if (qinverse(&q2_inv) < 0) {
        return -1;
    }
    qmul(q, q1, &q2_inv);
    return 0;
}

void qrotate(Vect* v, const Quat* q) {
    assert(q->is_normalized && "Using non-unit quaternion for rotation");
    Quat q_v = {.s = 0.0, .v = *v};
    Quat q_inv = *q;
    if (qinverse(&q_inv) < 0) {
        return;
    }

    Quat q_result;
    qmul(&q_result, q, &q_v);
    qmul(&q_result, &q_result, &q_inv);

    q_result.is_normalized = v->is_normalized; // The norm of a vector is preserved
    *v = q_result.v;
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

void qprint(const Quat* q) {
    printf("(% .3f,% .3f,% .3f,% .3f)", q->w, q->i, q->j, q->k);
}