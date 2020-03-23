#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv){
  printf("--beginning of program\n");
  int numOfProcess=10;
  int realNumOfProcess=0;
  int counter = 0, status=0;
  pid_t pid = fork();
  pid_t wpid;
  for (int p=2;p<=numOfProcess;p++){
    if (pid>0){
      pid=fork();
    }
  }

  if (pid==0){
    // child process
    realNumOfProcess++;
    exit(1);
  } else {
    realNumOfProcess++;
  }

  while ((wpid = wait(&status)) > 0);
  printf("real num of process = %d\n", realNumOfProcess);


  // if (pid == 0){
  //   // child process
  //   int i;
  //   for (i=0; i < 10; ++i){
  //     printf("child process: counter=%d pid=%d\n", ++counter, pid);
  //   }
  // }
  // else if (pid > 0) {
  //   // parent process
  //   int j;
  //
  //   for (j=0; j < 10; ++j){
  //     printf("parent process: counter=%d pid=%d\n", ++counter, pid);
  //   }
  // }
  // else {
  // // fork failed
  // printf("fork() failed!\n");
  //   return 1;
  // }
  //
  // printf("--end of program--\n");

  return 0;
}
