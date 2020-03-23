#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
using namespace std;

const long num_steps = 100000000;
int main(int argv, char** argc){
  for (int num_threads=1;num_threads<=20;num_threads++){
    for (int rep=1;rep<=5;rep++){
      double start, end;
      start = omp_get_wtime();
      double pi;
      double sum = 0.0;
      double step = 1.0/(double)num_steps;

      #pragma omp parallel num_threads(num_threads)
      {
        int id = omp_get_thread_num();
        #pragma omp for reduction(+:sum)
        for(int i=0;i<num_steps;i++){
          double x = (i+0.5)*step;
          sum += 4.0/(1.0+x*x);
        }
      }

      pi=sum*step;
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
