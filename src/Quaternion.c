#include "Quaternion.h"
#include "MathUtils.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

wtf_quat_t wtf_empty_quat() {
    // TODO: Use s and v = wtf_empty_vec()
    return (wtf_quat_t){.w = 0.0, .i = 0.0, .j = 0.0, .k = 0.0};
}

wtf_quat_t wtf_pure_quat(const Vect* v) {
    return (wtf_quat_t){.s = 0.0, .v = *v};
}

wtf_quat_t wtf_real_quat(double s) {
    // TODO: Use s and v = wtf_empty_vec()
    return (wtf_quat_t){.w = s, .i = 0.0, .j = 0.0, .k = 0.0};
}

wtf_quat_t wtf_rotor_quat(double theta, const Vect* axis) {
    assert(wtf_vec_is_normalized(axis) && "Using non-normalized axis for rotor");

    // TODO:    
    // q->s = cos(theta / 2.0);
    // q->v = *axis;
    // vscale(&q->v, sin(theta / 2.0));
    return (wtf_quat_t){.s = cos(theta / 2.0), .v = *axis};
}

wtf_quat_t wtf_quat_conjugate(wtf_quat_t* q) {
    vnegate(&q->v);
}

wtf_quat_t wtf_quat_scaled(wtf_quat_t* q, double k) {
    q->s = k * q->s;
    vscale(&q->v, k);
}

wtf_quat_t wtf_quat_normalized(wtf_quat_t* q) {
    if (q->is_normalized) {
        return 1;
    } else {
        double norm = wtf_quat_norm(q);
        if (norm > 0.0) {
            wtf_quat_scaled(q, 1.0 / norm);
            q->is_normalized = true;
            return 0;
        } else {
            return -1;
        }
    }
}

Vect wtf_quat_rotated(const Vect* v, const wtf_quat_t* q) {
    assert(q->is_normalized && "Using non-unit quaternion for rotation");
    wtf_quat_t qv;
    wtf_pure_quat(&qv, v);

    wtf_quat_t q_inv = *q;
    wtf_quat_conjugate(&q_inv); // Unit quat. inverse is its conjugate.

    wtf_quat_t q_result;
    wtf_quat_multiply(&q_result, q, &qv);
    wtf_quat_multiply(&q_result, &q_result, &q_inv);

    q_result.is_normalized = v->is_normalized; // The norm of a vector is preserved.
    *v = q_result.v;
}

wtf_quat_t wtf_quat_inversed(wtf_quat_t* q) {
    wtf_quat_conjugate(q);
    if (q->is_normalized) {
        return 0;
    } else {
        double norm_squared = wtf_quat_norm_squared(q);
        if (norm_squared > 0.0) {
            wtf_quat_scaled(q, 1.0 / norm_squared);
            return 0;
        } else {
            return -1;
        }
    }
}

wtf_quat_t wtf_quat_add(wtf_quat_t* q1, const wtf_quat_t* q2) {
    q1->s = q1->s + q2->s;
    vadd(&q1->v, &q2->v);
}

wtf_quat_t wtf_quat_subtract(wtf_quat_t* q1, const wtf_quat_t* q2) {
    q1->s = q1->s - q2->s;
    vsub(&q1->v, &q2->v);
}

wtf_quat_t wtf_quat_multiply(wtf_quat_t* q, const wtf_quat_t* q1, const wtf_quat_t* q2) {
    // q1 * q2 = [s1, v1] * [s2, v2] =
    // [s1 * s2 - dot(v1,v2), s1 * v2 + s2 * v1 + cross(v1,v2)]
    wtf_quat_t result;
    result.s = q1->s * q2->s - vdot(&q1->v, &q2->v);
    vcross(&result.v, &q1->v, &q2->v);

    Vect v_aux = q1->v;
    vscale(&v_aux, q2->s);
    vadd(&result.v, &v_aux);

    v_aux = q2->v;
    vscale(&v_aux, q1->s);
    vadd(&result.v, &v_aux);
    *q = result;
}

wtf_quat_t wtf_quat_divide(wtf_quat_t* q, const wtf_quat_t* q1, const wtf_quat_t* q2) {
    wtf_quat_t q2_inv = *q2;
    if (wtf_quat_inversed(&q2_inv) < 0) {
        return -1;
    }
    wtf_quat_multiply(q, q1, &q2_inv);
    return 0;
}

double wtf_quat_norm(const wtf_quat_t* q) {
    return (q->is_normalized) ? 1.0 : sqrt(wtf_quat_norm_squared(q));
}

double wtf_quat_norm_squared(const wtf_quat_t* q) {
    return (q->is_normalized) ? 1.0 : q->s * q->s + vnormSquared(&q->v);
}

bool wtf_quat_is_pure(const wtf_quat_t* q) {
    return q->w == 0.0;
}

bool wtf_quat_is_real(const wtf_quat_t* q) {
    return q->i == 0.0 && q->j == 0.0 && q->k == 0.0;
}

bool wtf_compare_quat(const wtf_quat_t* q1, const wtf_quat_t* q2) {
    return dcmp(q1->s, q2->s) && vcmp(&q1->v, &q2->v);
}

void wtf_print_quat(const wtf_quat_t* q) {
    printf("(% .3f,% .3f,% .3f,% .3f)", q->w, q->i, q->j, q->k);
}