#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
using namespace std;

const long num_steps = 100000000;

double* create1DArray(long sizeX){
    double*  array =(double*) malloc(sizeX * sizeof(double));
    return array;
}

int main(int argv, char** argc){
  for (int num_threads=1;num_threads<=50;num_threads++){
    for (int rep=1;rep<=5;rep++){
      // int num_threads = atoi(argc[1]);
      // printf("num thread : %d\n", num_threads);
      double start, end;
      start = omp_get_wtime();
      double pi;
      double *sum=create1DArray(num_threads);
      for (int n=0;n<num_threads;n++){
        sum[n]=0.0;
      }
      double step = 1.0/(double)num_steps;



      #pragma omp parallel num_threads(num_threads)
      {
        int id = omp_get_thread_num();
        #pragma omp for
        for(int i=0;i<num_steps;i++){
          double x = (i+0.5)*step;
          sum[id] += 4.0/(1.0+x*x);
        }
      }

      double sumTot = 0.0;
      for (int n=0;n<num_threads;n++){
        sumTot+= sum[n];
      }
      pi=sumTot*step;
      // printf("pi=%.8lf\n", pi);
      end = omp_get_wtime();
      printf("%.8lf",end-start);
      if (rep<5){
        printf(",");
      } else {
        printf("\n");
      }
    }
  }
}
