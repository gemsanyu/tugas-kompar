#include <stdlib.h>

#include "helper_lib.h"

double** create2DArray(int sizeX, int sizeY){
  double **array = (double**)malloc(sizeof(double*)*sizeX);
  array[0] = (double*)malloc(sizeof(double)*sizeX*sizeY);

  for(int i=1;i<sizeX;i++){
    array[i]=array[i-1]+sizeY;
  }
  return array;
}

double3word** create2DArrayd3w(int sizeX, int sizeY){
  double3word **array = (double3word**)malloc(sizeof(double3word*)*sizeX);
  array[0] = (double3word*)malloc(sizeof(double3word)*sizeX*sizeY);

  for(int i=1;i<sizeX;i++){
    array[i]=array[i-1]+sizeY;
  }
  return array;
}
