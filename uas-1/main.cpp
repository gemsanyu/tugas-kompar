#include <iomanip>
#include <chrono>
#include <iostream>

#include "helper_lib.h"
#include "matrix_operations.h"

int main(int argc, char **argv){
  for(int N=2;N<=1024;N<<=1){
    double **A = create2DArray(N,N);
    double **B = create2DArray(N,N);
    double **C = create2DArray(N,N);

    for(int n=0;n<N;n++){
      for(int m=0;m<N;m++){
        A[n][m] = (rand()%10);
      }
    }

    for(int n=0;n<N;n++){
      for(int m=0;m<N;m++){
        B[n][m] = (rand()%10);
      }
    }

    for(int iter=0;iter<5;iter++){
      std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
      matrixMul(A, B, C, N);
      std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
      std::cout << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count()<<",";
    }
    std::cout<<"\n";


    free(A);
    free(B);
    free(C);
  }
}
