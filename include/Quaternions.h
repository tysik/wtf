#ifndef QUATERNIONS_H_
#define QUATERNIONS_H_

#include <stdbool.h>

typedef struct Quat {
    double w, i, j, k;
} Quat;

typedef struct ResultQuat {
    bool ok;
    Quat q;
} ResultQuat;

Quat empty();
Quat from(double w, double i, double j, double k);
Quat fromRPY(double roll, double pitch, double yaw);

Quat qadd(const Quat* q1, const Quat* q2);
Quat qsub(const Quat* q1, const Quat* q2);

Quat qmul(const Quat* q1, const Quat* q2);
Quat qdiv(const Quat* q1, const Quat* q2);

#endif // QUATERNIONS_H_