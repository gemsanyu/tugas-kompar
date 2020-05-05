#ifndef MAT_OPR_H
#define MAT_OPR_H

#include "helper_lib.h"

void matrixMul(double **A, double **B, double **C, int N);
void matrixMulGPU(double3word *A, double3word *B, double3word*C, int N);

#endif
