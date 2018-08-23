#ifndef QUATERNIONS_H_
#define QUATERNIONS_H_

typedef struct Quat {
    double w, i, j, k;
} Quat;

Quat* empty();
Quat* from(double w, double i, double j, double k);
Quat* fromRPY(double roll, double pitch, double yaw);

Quat add(const Quat* q1, const Quat* q2);
Quat sub(const Quat* q1, const Quat* q2);

Quat mul(const Quat* q1, const Quat* q2);
Quat div(const Quat* q1, const Quat* q2);

#endif // QUATERNIONS_H_