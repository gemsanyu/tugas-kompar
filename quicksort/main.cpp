#include<algorithm>
#include<omp.h>
#include<stdio.h>
using namespace std;

int N;
int numThreads;

void partition (int *arr, int low, int high, int *pi){
  // pivot (Element to be placed at right position)
  int pivot = arr[high];
  int i = (low - 1);  // Index of smaller element
  for (int j = low; j < high; j++){
    // If current element is smaller than the pivot
    if (arr[j] < pivot){
      i++; // increment index of smaller element
      int c=arr[i];
      arr[i]=arr[j];
      arr[j]=c;
    }
  }
  int c=arr[i+1];
  arr[i+1]=arr[high];
  arr[high]=c;
  *pi=(i+1);
}

void quickSortSer(int *arr, int low, int high){
  if (low < high){
    /* pi is partitioning index, arr[pi] is now
       at right place */
    int *pi = new int;
    partition(arr, low, high, pi);
    quickSortSer(arr, low, *pi - 1);  // Before pi
    quickSortSer(arr, *pi + 1, high); // After pi
  }
}

void quickSortPar(int *arr, int low, int high, int threads){
  if (low < high){
    /* pi is partitioning index, arr[pi] is now
       at right place */
    int *pi = new int;
    partition(arr, low, high, pi);

    if(threads>1){
      #pragma omp parallel sections
      {
        #pragma omp section
        {
          quickSortPar(arr, low, *pi - 1, threads/2);  // Before pi
        }
        #pragma omp section
        {
          quickSortPar(arr, *pi + 1, high, threads-threads/2); // After pi
        }
      }
    } else {
      quickSortSer(arr, low, *pi - 1);  // Before pi
      quickSortSer(arr, *pi + 1, high); // After pi
    }
  }
}

int main(int argv, char **argc){
  omp_set_nested(1);
  numThreads = atoi(argc[2]);
  omp_set_num_threads(numThreads);

  double start,end;
  N = atoi(argc[1]);
  int *arr = new int[N];
  for(int i=0; i<N; i++){
    arr[i]=rand()%100;
  }

  start=omp_get_wtime();
  #pragma omp parallel
  {
    #pragma omp single
    {
      #pragma omp task
      {
        quickSortPar(arr, 0, N-1, numThreads);
      }
    }
  }
  end=omp_get_wtime();
  printf("Parallel elapsed time: %.8lf\n",end-start);

  for(int i=0; i<N; i++){
    arr[i]=rand()%100;
  }
  start=omp_get_wtime();
  quickSortSer(arr, 0, N-1);
  end=omp_get_wtime();
  printf("Serial elapsed time: %.8lf\n",end-start);
}
