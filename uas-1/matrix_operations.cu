#include "helper_lib.h"
#include "matrix_operations.h"

void matrixMul(double **A, double **B, double **C, int N){
  for(int m=0;m<N;m++){
    for(int k=0;k<N;k++){
      C[m][k]=0;
      for(int n=0;n<N;n++){
        C[m][k]+= A[m][n]*B[n][k];
      }
    }
  }
}
