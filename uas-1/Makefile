OMPFLAG= -fopenmp
NVCCCOMPILERFLAG = -Xcompiler
CPP= g++
CPPFLAGS= -g -O3 -march=native --std=c++11
NVCC= nvcc
NVCCFLAGS= -g -G -arch=sm_50 -std=c++11
CUDAINCLUDE = -I/usr/local/cuda/include -L/usr/local/cuda/lib64
LCUDAFLAGS= -lcudart -lcuda -lcudadevrt
MPICC= mpic++

main: helper_lib.o main.cpp
	$(CPP) $(CPPFLAGS) $? -o $@

helper_lib.o: helper_lib.cpp
	$(CPP) $(CPPFLAGS) -c $? -o $@

clean:
	rm -rf *.o main
