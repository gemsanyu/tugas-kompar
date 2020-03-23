#include<omp.h>
#include<stdio.h>
#include<string.h>
#include<random>
using namespace std;

int N;
int numThreads;

void mergeSortSer(int *array, int left, int right){
  if (left == right){
    return;
  }

  if (left == right-1){
    if (array[left]>array[right]){
      int c=array[left];
      array[left]=array[right];
      array[right]=c;
    }
    return;
  }

  int mid=(left+right)/2;
  int a=left;
  int b=mid;
  int a1=mid+1;
  int b1=right;

  mergeSortSer(array, a, b);
  mergeSortSer(array, a1, b1);


  int *arr = new int[b-a+1];
  for(int i=a;i<=b;i++){
    arr[i-a]=array[i];
  }

  int *arr1 = new int[b1-a1+1];
  for(int i=a1;i<=b1;i++){
    arr1[i-a1]=array[i];
  }

  int c=a;
  int c1=a1;
  for(int idx=left;idx<=right;idx++){
    if(c>b){
      array[idx]=arr1[c1-a1];
      c1++;
      continue;
    }
    if(c1>b1){
      array[idx]=arr[c-a];
      c++;
      continue;
    }
    if(arr[c-a]<=arr1[c1-a1]){
      array[idx]=arr[c-a];
      c++;
      continue;
    }
    array[idx]=arr1[c1-a1];
    c1++;
  }
}


void mergeSortPar(int *array, int left, int right, int threads){
  if (left == right){
    return;
  }

  if (left == right-1){
    if (array[left]>array[right]){
      int c=array[left];
      array[left]=array[right];
      array[right]=c;
    }
    return;
  }

  int mid=(left+right)/2;
  int a=left;
  int b=mid;
  int a1=mid+1;
  int b1=right;

  if(threads>1){
    #pragma omp parallel sections
    {
      #pragma omp section
      {
        mergeSortPar(array, a, b, threads/2);
      }
      #pragma omp section
      {
        mergeSortPar(array, a1, b1, threads-threads/2);
      }
    }
  } else {
    mergeSortSer(array, a, b);
    mergeSortSer(array, a1, b1);
  }

  int *arr = new int[b-a+1];
  for(int i=a;i<=b;i++){
    arr[i-a]=array[i];
  }

  int *arr1 = new int[b1-a1+1];
  for(int i=a1;i<=b1;i++){
    arr1[i-a1]=array[i];
  }

  int c=a;
  int c1=a1;
  for(int idx=left;idx<=right;idx++){
    if(c>b){
      array[idx]=arr1[c1-a1];
      c1++;
      continue;
    }
    if(c1>b1){
      array[idx]=arr[c-a];
      c++;
      continue;
    }
    if(arr[c-a]<=arr1[c1-a1]){
      array[idx]=arr[c-a];
      c++;
      continue;
    }
    array[idx]=arr1[c1-a1];
    c1++;
  }
}

int main(int argv, char**argc){
  omp_set_nested(1);
  numThreads=atoi(argc[2]);
  omp_set_num_threads(numThreads);
  N = atoi(argc[1]);
  int *arr = new int[N];
  for(int i=0; i<N; i++){
    arr[i]=rand()%1000;
  }


  double start, end;
  start = omp_get_wtime();
  #pragma omp parallel
  {
    #pragma omp single
    {
      #pragma omp task
      {
        mergeSortPar(arr, 0, N-1,numThreads);
      }
    }
  }
  end=omp_get_wtime();

  bool notSorted=false;
  for(int i=1;i<N;i++){
    if(arr[i]<arr[i-1]){
      notSorted=true;
      break;
    }
  }
  if (notSorted){
    printf("ERROR NOT SORTED!\n");
  }
  printf("Parallel elapsed time: %.8lf\n",end-start);

  for(int i=0; i<N; i++){
    arr[i]=rand()%1000;
  }
  start=omp_get_wtime();
  mergeSortSer(arr, 0, N-1);
  end=omp_get_wtime();
  printf("Serial elapsed time: %.8lf\n",end-start);
}
