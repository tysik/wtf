#include "Vectors.h"
#include "MathUtils.h"

#include <math.h>

Vect vempty() {
    Vect v = {.x = 0.0, .y = 0.0, .z = 0.0, .is_normalized = false};
    return v;
}

Vect vneg(const Vect* v) {
    Vect vx = {.x = -v->x, .y = -v->y, .z = -v->z, .is_normalized = v->is_normalized};
    return vx;
}

Vect vnormal(const Vect* v) {
    if (v->is_normalized) {
        return *v;
    } else {
        double norm = vnorm(v);
        if (norm > 0.0) {
            Vect vx = vscale(1.0 / norm, v);
            vx.is_normalized = true;
            return vx;
        } else {
            return vempty();
        }
    }
}

Vect vscale(double k, const Vect* v) {
    Vect vx = {.x = k * v->x, .y = k * v->y, .z = k * v->z, .is_normalized = false};
    return vx;
}

Vect vadd(const Vect* v1, const Vect* v2) {
    Vect v = {.x = v1->x + v2->x, .y = v1->y + v2->y, .z = v1->z + v2->z, .is_normalized = false};
    return v;
}

Vect vsub(const Vect* v1, const Vect* v2) {
    Vect v = {.x = v1->x - v2->x, .y = v1->y - v2->y, .z = v1->z - v2->z, .is_normalized = false};
    return v;
}

Vect vcross(const Vect* v1, const Vect* v2) {
    Vect v = {.x = v1->y * v2->z - v1->z * v2->y,
              .y = v1->z * v2->x - v1->x * v2->z,
              .z = v1->x * v2->y - v1->y * v2->x,
              .is_normalized = v1->is_normalized && v2->is_normalized};
    return v;
}

double vdot(const Vect* v1, const Vect* v2) {
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

double vnorm(const Vect* v) {
    return (v->is_normalized) ? 1.0 : sqrt(vnormSquared(v));
}

double vnormSquared(const Vect* v) {
    return (v->is_normalized) ? 1.0 : v->x * v->x + v->y * v->y + v->z * v->z;
}

bool vcmp(const Vect* v1, const Vect* v2) {
    return dcmp(v1->x, v2->x) && dcmp(v1->y, v2->y) && dcmp(v1->z, v2->z);
}
