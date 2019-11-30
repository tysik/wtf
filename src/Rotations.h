#ifndef CTF_ROTATIONS_H_
#define CTF_ROTATIONS_H_

#include "Quaternions.h"

// 3D rotation matrix
typedef double Rot[3][3];

// Construct an identity matrix
void reye(Rot* r);

void rrotX(Rot* r, double theta);
void rrotY(Rot* r, double theta);
void rrotZ(Rot* r, double theta);

// Construct rotation matrix from a quaternion
// Q must be a proper (normalized) rotor 
void rfromQuat(Rot* r, const Quat* q);

void rtoQuat(Quat* q, const Rot* r);

void rrand(Rot* R);

// Scale a matrix by a scalar
void rscale(Rot* r, double k);

// Multiply r1 by r2
void rmul(Rot* r, const Rot* r1, const Rot* r2);

// Print a rotation matrix to stdout
void rprint(const Rot* r);

#endif // CTF_ROTATIONS_H_