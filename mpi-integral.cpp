/* C Example */
#include <cmath>
#include <mpi.h>
#include <math.h>
#include <stdio.h>

using namespace std;
double fct(double x){
      return (cos(x));
}
/* Prototype */
double integral(double a, int n, double h);
int main(int argc, char **argv){
/***********************************************************************
 *                                                                     *
 * This is one of the MPI versions on the integration example          *
 * It demonstrates the use of :                                        *
 *                                                                     *
 * 1) MPI_Init                                                         *
 * 2) MPI_Comm_rank                                                    *
 * 3) MPI_Comm_size                                                    *
 * 4) MPI_Recv                                                         *
 * 5) MPI_Send                                                         *
 * 6) MPI_Finalize                                                     *
 *                                                                     *
 ***********************************************************************/
      double start, end;
      int n, p, i, j, ierr,num;
      double h, result, a, b, pi;
      double my_a, my_range;

      int myid, source, dest, tag;
      MPI_Status status;
      double my_result;

      start = MPI_Wtime();
      pi = acos(-1.0);  /* = 3.14159... */
      a = 0.;           /* lower limit of integration */
      b = pi*1. /2.;     /* upper limit of integration */
      n = 100000000;          /* number of increment within each process */

      dest = 0;         /* define the process that computes the final result */
      tag = 123;        /* set the tag to identify this particular job */

/* Starts MPI processes ... */

      MPI_Init(&argc,&argv);              /* starts MPI */
      MPI_Comm_rank(MPI_COMM_WORLD, &myid);  /* get current process id */
      MPI_Comm_size(MPI_COMM_WORLD, &p);     /* get number of processes */

      h = (b-a)/n;    /* length of increment */
      num = n/p;	/* number of intervals calculated by each process*/
      my_range = (b-a)/p;
      my_a = a + myid*my_range;
      my_result = integral(my_a,num,h);

      // printf("Process %d has the partial result of %f\n", myid,my_result);

      if(myid == 0) {
        result = my_result;
        for (i=1;i<p;i++) {
          source = i;           /* MPI process number range is [0,p-1] */
          MPI_Recv(&my_result, 1, MPI_REAL, source, tag,
                        MPI_COMM_WORLD, &status);
          result += my_result;
        }
        // printf("The result =%f\n",result);
      }
      else
        MPI_Send(&my_result, 1, MPI_REAL, dest, tag,
                      MPI_COMM_WORLD);      /* send my_result to intended dest.
                      */
      if (myid == 0){
        end = MPI_Wtime();
        printf("%.8lf\n",end-start);
        printf("%.8lf\n",result);
      }
      MPI_Finalize();                       /* let MPI finish up ... */
}
double integral(double a, int n, double h)
{
      int j;
      double h2, aij, integ;

      integ = 0.0;                 /* initialize integral */
      h2 = h/2.;
      for (j=0;j<n;j++) {             /* sum over all "j" integrals */
        aij = a + j*h;        /* lower limit of "j" integral */
        integ += fct(aij+h2)*h;
      }
      return (integ);
}
