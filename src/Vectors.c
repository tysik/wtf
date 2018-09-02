#include "Vectors.h"
#include "MathUtils.h"

#include <math.h>

Vect vEmpty() {
    Vect v = {.x = 0.0, .y = 0.0, .z = 0.0};
    return v;
}

Vect vFrom(double x, double y, double z) {
    Vect v = {.x = x, .y = y, .z = z};
    return v;
}

Vect vadd(const Vect* v1, const Vect* v2) {
    Vect v = {.x = v1->x + v2->x, .y = v1->y + v2->y, .z = v1->z + v2->z};
    return v;
}

Vect vsub(const Vect* v1, const Vect* v2) {
    Vect v = {.x = v1->x - v2->x, .y = v1->y - v2->y, .z = v1->z - v2->z};
    return v;
}

double vdot(const Vect* v1, const Vect* v2) {
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

Vect vcross(const Vect* v1, const Vect* v2) {
    Vect v = {.x = v1->y * v2->z - v1->z * v2->y,
              .y = v1->z * v2->x - v1->x * v2->z,
              .z = v1->x * v2->y - v1->y * v2->x};
    return v;
}

Vect vscale(double k, const Vect* v) {
    Vect vx = {.x = k * v->x, .y = k * v->y, .z = k * v->z};
    return vx;
}

bool vcmp(const Vect* v1, const Vect* v2) {
    return dcmp(v1->x, v2->x) && dcmp(v1->y, v2->y) && dcmp(v1->z, v2->z);
}

double vnorm(const Vect* v) { return sqrt(vnormSquared(v)); }

double vnormSquared(const Vect* v) { return v->x * v->x + v->y * v->y + v->z * v->z; }