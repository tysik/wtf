#include "Quaternions.h"
#include "MathUtils.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

void qempty(Quat* q) {
    q->s = 0.0;
    wtf_empty_vec(&q->v);
}

void qpure(Quat* q, const wtf_vec_t* v) {
    q->s = 0.0;
    q->v = *v;
}

void qreal(Quat* q, double s) {
    q->s = s;
    wtf_empty_vec(&q->v);
}

void qrotor(Quat* q, double theta, const wtf_vec_t* axis) {
    assert(axis->is_normalized && "Using non-versor axis for rotor");
    q->s = cos(theta / 2.0);
    q->v = *axis;
    wtf_scale_vec(&q->v, sin(theta / 2.0));
    q->is_normalized = true;
}

void qconjugate(Quat* q) {
    wtf_negate_vec(&q->v);
}

void qscale(Quat* q, double k) {
    q->s = k * q->s;
    wtf_scale_vec(&q->v, k);
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
    wtf_add_vec(&q1->v, &q2->v);
}

void qsub(Quat* q1, const Quat* q2) {
    q1->s = q1->s - q2->s;
    wtf_subtract_vec(&q1->v, &q2->v);
}

void qmul(Quat* q, const Quat* q1, const Quat* q2) {
    // q1 * q2 = [s1, v1] * [s2, v2] =
    // [s1 * s2 - dot(v1,v2), s1 * v2 + s2 * v1 + cross(v1,v2)]
    Quat result;
    result.s = q1->s * q2->s - wtf_vec_dot(&q1->v, &q2->v);
    wtf_vec_cross(&result.v, &q1->v, &q2->v);

    wtf_vec_t v_aux = q1->v;
    wtf_scale_vec(&v_aux, q2->s);
    wtf_add_vec(&result.v, &v_aux);

    v_aux = q2->v;
    wtf_scale_vec(&v_aux, q1->s);
    wtf_add_vec(&result.v, &v_aux);
    *q = result;
}

int qdiv(Quat* q, const Quat* q1, const Quat* q2) {
    Quat q2_inv = *q2;
    if (qinverse(&q2_inv) < 0) {
        return -1;
    }
    qmul(q, q1, &q2_inv);
    return 0;
}

void qrotate(wtf_vec_t* v, const Quat* q) {
    assert(q->is_normalized && "Using non-unit quaternion for rotation");
    Quat qv;
    qpure(&qv, v);

    Quat q_inv = *q;
    qconjugate(&q_inv); // Unit quat. inverse is its conjugate.

    Quat q_result;
    qmul(&q_result, q, &qv);
    qmul(&q_result, &q_result, &q_inv);

    q_result.is_normalized = v->is_normalized; // The norm of a vector is preserved.
    *v = q_result.v;
}

double qnorm(const Quat* q) {
    return (q->is_normalized) ? 1.0 : sqrt(qnormSquared(q));
}

double qnormSquared(const Quat* q) {
    return (q->is_normalized) ? 1.0 : q->s * q->s + wtf_vec_squared_norm(&q->v);
}

bool qisPure(const Quat* q) {
    return q->w == 0.0;
}

bool qisReal(const Quat* q) {
    return q->i == 0.0 && q->j == 0.0 && q->k == 0.0;
}

bool qcmp(const Quat* q1, const Quat* q2) {
    return dcmp(q1->s, q2->s) && wtf_compare_vec(&q1->v, &q2->v);
}

void qprint(const Quat* q) {
    printf("(% .3f,% .3f,% .3f,% .3f)", q->w, q->i, q->j, q->k);
}