#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
using namespace std;

const long num_steps = 100000000;
double step;

int main(int argv, char** argc){
  int num_threads = atoi(argc[1]);
  printf("num thread : %d\n", num_threads);
  double start, end;
  start = omp_get_wtime();
  double pi, sum=0.0;


  step = 1.0/(double)num_steps;
  #pragma omp parallel num_threads(num_threads)
  {
    #pragma omp for
    for(int i=0;i<num_steps;i++){
      double x = (i+0.5)*step;
      #pragma omp atomic
      sum += 4.0/(1.0+x*x);
    }
  }

  pi=step*sum;
  printf("pi=%.8lf\n", pi);
  end = omp_get_wtime();
  printf("elapsed time=%.8lf\n",end-start);
}
