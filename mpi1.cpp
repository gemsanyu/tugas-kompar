#include<iostream>
#include<mpi.h>
#include<string>

using namespace std;
#define ROOT 0

int* create1DArrayInt(int sizeX){
    int*  array =(int*) malloc(sizeX * sizeof(int));
    return array;
}

double* create1DArrayDouble(int sizeX){
    double*  array =(double*) malloc(sizeX * sizeof(double));
    return array;
}

/*
  Write a matrix then read it if it resulted in the
  same matrix, let's see
*/
int main(int argc, char ** argv){
  MPI_Status status;
  int result;
  int rank;
  int numOfProcess;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numOfProcess);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  double *arr = create1DArrayDouble(5);
  for (int i=0; i<5; i++){
    arr[i]=rank*i;
  }

  /*
    WRITING arr INTO file
  */
  string fileName = "basic-array-at";
  MPI_File file;
  result = MPI_File_open(MPI_COMM_WORLD, fileName.c_str(), MPI_MODE_WRONLY | MPI_MODE_CREATE,
  MPI_INFO_NULL, &file);
  if (result != MPI_SUCCESS){
    cout << "ERROR open file to read with error code: " << result<<"\n";
  }

  MPI_Offset wrOffset = rank * 5 * sizeof(double);
  result = MPI_File_write_at(file, wrOffset, arr, 5, MPI_DOUBLE, &status);
  if (result != MPI_SUCCESS){
    cout << "ERROR write: " << result<<"\n";
  }
  MPI_File_close(&file);

  /*READING file INTO arr, lets reset arr first*/
  for (int i=0; i<5; i++){
    arr[i]=-1;
  }

  result = MPI_File_open(MPI_COMM_WORLD, fileName.c_str(), MPI_MODE_RDONLY,
  MPI_INFO_NULL, &file);
  if (result != MPI_SUCCESS){
    cout << "ERROR open file to read with error code: " << result<<"\n";
  }

  MPI_Offset rdOffset = rank * 5 * sizeof(double);
  result = MPI_File_read_at(file, rdOffset, arr, 5, MPI_DOUBLE, &status);
  if (result != MPI_SUCCESS){
    cout << "ERROR reading: " << result <<"\n";
  }

  string sArr = "";
  for (int i=0; i<5; i++){
    sArr = sArr + " " + to_string(arr[i]);
  }

  cout << "RANK" << rank <<": "<<sArr<<"\n";

  MPI_File_close(&file);

  MPI_Finalize();
}
