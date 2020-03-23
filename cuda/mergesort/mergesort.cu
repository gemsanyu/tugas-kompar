#include<stdio.h>
#include<random>
using namespace std;

#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort=true)
{
   if (code != cudaSuccess)
   {
      fprintf(stderr,"GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
      if (abort) exit(code);
   }
}


__global__ void mergeSort(int *array, int *left, int *right){
  if (*left == *right){
    return;
  }

  if (*left == *right-1){
    if (array[*left]>array[*right]){
      int c = array[*left];
      array[*left]=array[*right];
      array[*right]=c;
    }
    return;
  }

  printf("%d %d\n", *left, *right);
  cudaStream_t s1,s2;

  int mid = ((*left)+(*right))/2;
  int *a=left;

  int *b=new int(mid);
  int *a1=new int(mid+1);
  int *b1=right;

  int *arr, *arr1;
  cudaMalloc(&arr, (*b-*a+1)*sizeof(int));
  memcpy(arr, array, (*b-*a+1)*sizeof(int));
  cudaStreamCreateWithFlags(&s1, cudaStreamNonBlocking);
  mergeSort<<< 1,1,0,s1 >>>(arr, a, b);

  cudaMalloc(&arr1, (*b1-*a1+1)*sizeof(int));
  memcpy(arr1, array, (*b1-*a1+1)*sizeof(int));
  cudaStreamCreateWithFlags(&s2, cudaStreamNonBlocking);
  mergeSort<<< 1,1,0,s2 >>>(arr1, a1, b1);

  cudaStreamSynchronize(s1);
  int c=*a;
  int c1=*a1;
  for(int idx=*left; idx<=*right; idx++){
    if((c1>*b1) || arr[c]<=arr1[c1]){
      array[idx]=arr[c];
      c++;
    } else {
      array[idx]=arr1[c1];
      c1++;
    }
  }

  for(int i=*left;i<=*right;i++){
    printf("%d-",array[i]);
  }
  printf("\n");

  cudaFree(arr);
  cudaFree(arr1);
  cudaFree(a);
  cudaFree(b);
  cudaFree(a1);
  cudaFree(b1);
  cudaStreamDestroy(s1);
  cudaStreamDestroy(s2);
}

__global__ void invokeMergeSort(int *array, int *left, int *right){
  mergeSort<<<1,1>>>(array, left, right);
}

int main(int argc, char** argv){
  int N = atoi(argv[1])-1;
  int *d_N;
  cudaMalloc(&d_N, sizeof(int));
  cudaMemcpy(d_N, &N, sizeof(int), cudaMemcpyHostToDevice);
  N++;
  int *h_arr, *d_arr;
  h_arr = (int*)malloc(N*sizeof(int));
  for(int i=0;i<N;i++){
    h_arr[i]=rand()%1000;
  }
  for(int i=0;i<N;i++){
    printf("%d-",h_arr[i]);
  }
  printf("\n");

  cudaMalloc(&d_arr, N*sizeof(int));
  cudaMemcpy(d_arr, h_arr, N*sizeof(int), cudaMemcpyHostToDevice);

  int left=0;
  int *d_left;
  cudaMalloc(&d_left, sizeof(int));
  cudaMemcpy(d_left, &left, sizeof(int), cudaMemcpyHostToDevice);

  invokeMergeSort<<< 1,1,0,0 >>>(d_arr, d_left, d_N);
  cudaDeviceSynchronize();
  cudaMemcpy(h_arr, d_arr, N*sizeof(int), cudaMemcpyDeviceToHost);
  // for(int i=0;i<N;i++){
  //   printf("%d-",h_arr[i]);
  // }
  // printf("\n");
}
