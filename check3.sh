mpicxx --std=c++11 -march=native -O3 mpi-integral.cpp -o mpi-integral; mpirun --report-bindings --bind-to core --oversubscribe -np 1 mpi-integral >> time-core.out
sleep 1s;
mpicxx --std=c++11 -march=native -O3 mpi-integral.cpp -o mpi-integral; mpirun --report-bindings --bind-to core --oversubscribe -np 2 mpi-integral >> time-core.out
sleep 1s;
mpicxx --std=c++11 -march=native -O3 mpi-integral.cpp -o mpi-integral; mpirun --report-bindings --bind-to core --oversubscribe -np 1 mpi-integral >> time-core.out
sleep 1s;
mpicxx --std=c++11 -march=native -O3 mpi-integral.cpp -o mpi-integral; mpirun --report-bindings --bind-to core --oversubscribe -np 2 mpi-integral >> time-core.out
sleep 1s;
mpicxx --std=c++11 -march=native -O3 mpi-integral.cpp -o mpi-integral; mpirun --report-bindings --bind-to core --oversubscribe -np 1 mpi-integral >> time-core.out
sleep 1s;
mpicxx --std=c++11 -march=native -O3 mpi-integral.cpp -o mpi-integral; mpirun --report-bindings --bind-to core --oversubscribe -np 2 mpi-integral >> time-core.out
sleep 1s;

