#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int* create1DArrayInt(long sizeX){
    int*  array =(int*) malloc(sizeX * sizeof(int));
    return array;
}

/**
  1 Argument to run is N (number of elements)
  ./serial N
  ex : ./serial 100
**/

int main(int argc, char ** argv){
  clock_t start, end;
  double elapsed_cpu_time;

  start = clock();
  pthread_t tid;
  long N = atol(argv[1]);


  /**
    initializing N random numbers
  **/
  int *arr = create1DArrayInt(N);
  long fourCount = 0;
  for(int idx=0;idx<N;idx++){
      arr[idx]=rand()%10;
      if (arr[idx]==4){
        fourCount++;
      }
  }

  if (N<100){
    printf("The generated random numbers are : ");
    for(int idx=0;idx<N;idx++){
        printf("%d ", arr[idx]);
    }
    printf("\n");
  } else {
    printf("!Too many data, elements not printed\n");
  }

  end = clock();
  elapsed_cpu_time = ((double)end-(double)start)/CLOCKS_PER_SEC;

  printf("Found %d elements of '4'\n", fourCount);
  printf("ELAPSED CPU TIME to search on %ld elements: %.10lf seconds\n",N,elapsed_cpu_time);
}
