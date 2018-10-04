#ifndef CTF_ROTATIONS_H_
#define CTF_ROTATIONS_H_

#include "Quaternions.h"

typedef double Rot[3][3];

void reye(Rot* R);

void rfromQuat(const Quat* q, Rot* result);

void rrand(Rot* R);

void rscale(double d, const Rot* R, Rot* result);

void rmul(const Rot* R1, const Rot* R2, Rot* result);

void rprint(const Rot* R);

#endif // CTF_ROTATIONS_H_