#include "Rotations.h"

Vect rotate(const Vect* v, const Quat* q) {
    Quat q_v = {.s = 0.0, .v = *v};
    // TODO Consider removing this check and force user to provide proper rotor
    Quat q_unit = qunit(q);
    Quat q_inv = qinv(&q_unit);

    Quat q_result = qmul(&q_unit, &q_v);
    q_result = qmul(&q_result, &q_inv);
    q_result.is_normalized = v->is_normalized; // The norm of a vector is preserved
    return q_result.v;
}