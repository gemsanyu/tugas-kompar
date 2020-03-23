mergesort: mergesort.o link.o
	g++ -g --std=c++11 -O3 $^ -o $@ -I/usr/local/cuda/include -L/usr/local/cuda/lib64  -lcudart -lcuda -lcudadevrt

link.o: mergesort.o
	nvcc -G -dlink -rdc=true -gencode arch=compute_50,code=sm_50 --std=c++11 mergesort.o -o $@ -lcudadevrt

mergesort.o:
	nvcc -G -dc -rdc=true -gencode arch=compute_50,code=sm_50 --std=c++11 mergesort.cu

clean:
	rm -rf *.o mergesort
