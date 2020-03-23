#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int* create1DArrayInt(long sizeX){
    int*  array =(int*) malloc(sizeX * sizeof(int));
    return array;
}

int **create2DArrayInt(int rows, int cols) {
    int *data = (int *)malloc(rows*cols*sizeof(int));
    int **array= (int **)malloc(rows*sizeof(int*));
    for (int i=0; i<rows; i++)
        array[i] = &(data[cols*i]);
    return array;
}

/**
  2 argument to run is N (number of elements) and NUM_T
  ./forkpipe N NUM_T
  example for 20 data and 5 threads:
  ./forkpipe 20 5
**/


int main(int argc, char **argv){
  clock_t start, end;
  double elapsed_cpu_time;

  start=clock();
  int N = atoi(argv[1]);
  int NUM_P = atoi(argv[2]);
  pid_t pid=1;

  /**
    Make pipe channels for every process
    to send and receive
    channel[n][0] for read end
    channel[n][1] for write end
  **/
  int **channel = create2DArrayInt(NUM_P, 2);
  for (int p=0;p<NUM_P;p++){
      pipe(channel[p]);
  }

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
    creating the split size of elements for each process
    example of splits of 11 elements for 3 processes
    4 4 3
    because 11/3 = 3 and 11%3 = 2
    so there will be 2 processess handling (3+1) elements
    while the rest will handle 3 elements
  **/
  int *elementSplitSize = create1DArrayInt(NUM_P);
  int elementSplitSizeRemainder = N % NUM_P;
  int elementCount = N / NUM_P;
  for (int t=0; t<NUM_P; t++){
    elementSplitSize[t]=elementCount;
    if (t < elementSplitSizeRemainder){
      elementSplitSize[t]++;
    }
  }
  for (int t=1;t<NUM_P;t++){
    elementSplitSize[t]+=elementSplitSize[t-1];
  }

  for (int p=1;p<NUM_P;p++){
    /**
      By doing this, only parent fork
      therefore there will be exactly NUM_P processes
    **/
    if (pid!=0){
        pid=fork();
        if (pid==0){
          // newborn child will do the job
          // first close the reading channel
          close(channel[p][0]);
          int fourCount=0;
          int startIdx=elementSplitSize[p-1], stopIdx=elementSplitSize[p];
          for(int idx=startIdx;idx<stopIdx;idx++){
            if(arr[idx]==4){
              fourCount++;
            }
          }
          printf("Process:%d handles elements from %d to %d, Found %d elements\n",
            p,elementSplitSize[p-1],elementSplitSize[p]-1,fourCount);

          // Write fourCount to corresponding channel then
          // close the write channel
          write(channel[p][1], &fourCount, sizeof(int));
          close(channel[p][1]);
          exit(0);
        }
    }
  }

  /**
    Now the parent process will search the first split
    and summarize the whole processes' counts
  **/
  int fourCount = 0;
  if (pid>0){
    int stopIdx = elementSplitSize[0];
    for(int idx=0;idx<stopIdx;idx++){
      if (arr[idx]==4){
        fourCount++;
      }
    }
    printf("Parent Process handles elements from %d to %d, Found %d elements\n",
      0,elementSplitSize[0]-1,fourCount);
  }

  for(int p=1;p<NUM_P;p++){
    wait(NULL);
  }

  for(int p=1;p<NUM_P;p++){
    // close the write channel
    close(channel[p][1]);
    int pFourCount;

    // read and close read channel
    read(channel[p][0], &pFourCount, sizeof(int));
    close(channel[p][0]);
    fourCount+=pFourCount;
  }

  printf("In summary, there are %d elements of '4'\n", fourCount);
  end = clock();
  elapsed_cpu_time = ((double)end - (double)start)/CLOCKS_PER_SEC;
  printf("ELAPSED TIME: %.5lf seconds\n", elapsed_cpu_time);

  FILE *fp;
  fp = fopen("forkpipe_rtime.csv", "a+");
  fprintf(fp, "%d,%.5lf\n",NUM_P,elapsed_cpu_time);
  fclose(fp);
  return 0;
}
