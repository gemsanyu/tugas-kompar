#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

using namespace std;

const int numT=3;
const int N=10;
int sum=0;

struct arg {
  int *data;
  int startIdx, stopIdx;
};

int* create1DArrayInt(int sizeX){
    int*  array =(int*) malloc(sizeX * sizeof(int));
    return array;
}

void *myThreadSum(void *vargp){
  arg *tArg = (arg *)vargp;
  for(int idx=tArg->startIdx;idx<tArg->stopIdx;idx++){
    sum += tArg->data[idx];
  }
  printf("%d %d\n", tArg->startIdx, tArg->stopIdx);
}

int main(){
  pthread_t tid;
  int *arr = create1DArrayInt(N);
  for(int idx=0;idx<N;idx++){
      arr[idx]=idx;
  }

  int *elementSplitSize = create1DArrayInt(numT);
  int elementSplitSizeRemainder = N % numT;
  int elementCount = N / numT;
  for (int t=0; t<numT; t++){
    elementSplitSize[t]=elementCount;
    if (t < elementSplitSizeRemainder){
      elementSplitSize[t]++;
    }
  }
  for (int t=1;t<numT;t++){
    elementSplitSize[t]+=elementSplitSize[t-1];
  }

  arg argList[N];
  for(int t=0;t<numT;t++){

    argList[t].data = arr;
    if (t==0){
      argList[t].startIdx = 0;
    } else {
      argList[t].startIdx = elementSplitSize[t-1];
    }
    argList[t].stopIdx = elementSplitSize[t];
    pthread_create(&tid, NULL, myThreadSum, (void *) &argList[t]);
  }

  for(int t=0;t<numT;t++){
    pthread_join(tid, NULL);
  }

  printf("sum : %d\n", sum);

}
