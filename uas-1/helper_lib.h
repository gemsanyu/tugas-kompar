#ifndef HLP_LIB_H
#define HLP_LIB_H

struct double3word{
  double data;
  float padding;
};

double** create2DArray(int sizeX, int sizeY);
double3word** create2DArrayd3w(int sizeX, int sizeY);
#endif
