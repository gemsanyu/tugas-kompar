#include<stdio.h>

int main(){
  for (int t=1;t<=50;t++){
    for(int r=1;r<=5;r++){
      printf("./pthread 100000000 %d;\n",t);
      printf("sleep 2;\n");
    }
  }
}
