#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


struct arg {
  int *data;
  long tid;
  long startIdx, stopIdx;
  long fourCount;
};

int* create1DArrayInt(long sizeX){
    int*  array =(int*) malloc(sizeX * sizeof(int));
    return array;
}

struct arg* create1DArrayArg(long sizeX){
    struct arg*  array =(struct arg*) malloc(sizeX * sizeof(struct arg));
    return array;
}

void *countFour(void *vargp){
  struct arg *tArg = (struct arg *)vargp;
  for(int idx=tArg->startIdx;idx<tArg->stopIdx;idx++){
    if (tArg->data[idx]==4){
      tArg->fourCount++;
    }
  }
}

/**
  2 argument to run is N (number of elements) and NUM_T
  ./pthread N NUM_T
  example for 20 data and 5 threads:
  ./pthread 20 5
**/

int main(int argc, char ** argv){
  clock_t start, end;
  double elapsed_cpu_time;

  start = clock();
  pthread_t tid;
  long N = atol(argv[1]);
  long NUM_T = atol(argv[2]);

  /**
    initializing N random numbers
  **/
  int *arr = create1DArrayInt(N);
  for(int idx=0;idx<N;idx++){
      arr[idx]=rand()%10;
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
  /**
    creating the split size of elements for each threads
    example of splits of 11 elements for 3 thread
    4 4 3
    because 11/3 = 3 and 11%3 = 2
    so there will be 2 threads handling (3+1) elements
    while the rest will handle 3 elements
  **/
  int *elementSplitSize = create1DArrayInt(NUM_T);
  int elementSplitSizeRemainder = N % NUM_T;
  int elementCount = N / NUM_T;
  for (int t=0; t<NUM_T; t++){
    elementSplitSize[t]=elementCount;
    if (t < elementSplitSizeRemainder){
      elementSplitSize[t]++;
    }
  }
  for (int t=1;t<NUM_T;t++){
    elementSplitSize[t]+=elementSplitSize[t-1];
  }

  /**
    because we are passing arguments by reference
    then we have to prepare different argument for every thread
  **/
  struct arg *argList = create1DArrayArg(NUM_T);
  for(int t=0;t<NUM_T;t++){
    argList[t].data = arr;
    argList[t].tid = t;
    if (t==0){
      argList[t].startIdx = 0;
    } else {
      argList[t].startIdx = elementSplitSize[t-1];
    }
    argList[t].stopIdx = elementSplitSize[t];
    pthread_create(&tid, NULL, countFour, (void *) &argList[t]);
  }

  for(int t=0;t<NUM_T;t++){
    pthread_join(tid, NULL);
  }

  long fourCount = 0;
  for(int t=0;t<NUM_T;t++){
    fourCount += argList[t].fourCount;
  }
  printf("Found %ld elements of '4'\n",fourCount);

  // if (NUM_T<100){
  //   for(int t=0;t<NUM_T;t++){
  //     printf("Thread ID: %ld counts '4' in range index %ld to %ld\n FOUND %ld elements\n",
  //       argList[t].tid, argList[t].startIdx, argList[t].stopIdx-1, argList[t].fourCount);
  //   }
  // } else {
  //   printf("TOO MANY THREADS, count per threads not printed!\n");
  // }

  end = clock();
  elapsed_cpu_time = ((double)end-(double)start)/CLOCKS_PER_SEC;

  printf("ELAPSED CPU TIME to search on %ld elements with %ld threads: %.10lf seconds\n",N,NUM_T,elapsed_cpu_time);
  FILE *fp;
  fp = fopen("pthread_rtime.csv", "a+");
  fprintf(fp, "%d,%.5lf\n",NUM_T,elapsed_cpu_time);
  fclose(fp);
}
