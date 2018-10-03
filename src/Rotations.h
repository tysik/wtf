#ifndef CTF_ROTATIONS_H_
#define CTF_ROTATIONS_H_

#include "Quaternions.h"
#include "Vectors.h"

typedef struct Rot {
    double R[3][3];
} Rot;

#endif // CTF_ROTATIONS_H_