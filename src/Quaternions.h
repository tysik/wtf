#ifndef QUATERNIONS_H_
#define QUATERNIONS_H_

#include <stdbool.h>

typedef struct Quat { double w, i, j, k; } Quat;

typedef struct ResultQuat {
    bool ok;
    Quat q;
} ResultQuat;

Quat qEmpty();
Quat qFrom(double w, double i, double j, double k);
Quat qFromRPY(double roll, double pitch, double yaw);

Quat qreal(const Quat* q);
Quat qpure(const Quat* q);
Quat qconj(const Quat* q);

Quat qadd(const Quat* q1, const Quat* q2);
Quat qsub(const Quat* q1, const Quat* q2);

Quat qmul(const Quat* q1, const Quat* q2);
Quat qdiv(const Quat* q1, const Quat* q2);

Quat qscale(double k, const Quat* q);

bool qcmp(const Quat* q1, const Quat* q2);

double qnorm(const Quat* q);

#endif // QUATERNIONS_H_