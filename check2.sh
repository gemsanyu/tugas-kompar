mpicxx --std=c++11 -march=native -O3 mpi-integral.cpp -o mpi-integral; mpirun --report-bindings --bind-to hwthread --oversubscribe -np 1 mpi-integral >> time-hwthread.out
sleep 1s;
mpicxx --std=c++11 -march=native -O3 mpi-integral.cpp -o mpi-integral; mpirun --report-bindings --bind-to hwthread --oversubscribe -np 2 mpi-integral >> time-hwthread.out
sleep 1s;
mpicxx --std=c++11 -march=native -O3 mpi-integral.cpp -o mpi-integral; mpirun --report-bindings --bind-to hwthread --oversubscribe -np 3 mpi-integral >> time-hwthread.out
sleep 1s;
mpicxx --std=c++11 -march=native -O3 mpi-integral.cpp -o mpi-integral; mpirun --report-bindings --bind-to hwthread --oversubscribe -np 4 mpi-integral >> time-hwthread.out
sleep 1s;
mpicxx --std=c++11 -march=native -O3 mpi-integral.cpp -o mpi-integral; mpirun --report-bindings --bind-to hwthread --oversubscribe -np 1 mpi-integral >> time-hwthread.out
sleep 1s;
mpicxx --std=c++11 -march=native -O3 mpi-integral.cpp -o mpi-integral; mpirun --report-bindings --bind-to hwthread --oversubscribe -np 2 mpi-integral >> time-hwthread.out
sleep 1s;
mpicxx --std=c++11 -march=native -O3 mpi-integral.cpp -o mpi-integral; mpirun --report-bindings --bind-to hwthread --oversubscribe -np 3 mpi-integral >> time-hwthread.out
sleep 1s;
mpicxx --std=c++11 -march=native -O3 mpi-integral.cpp -o mpi-integral; mpirun --report-bindings --bind-to hwthread --oversubscribe -np 4 mpi-integral >> time-hwthread.out
sleep 1s;
mpicxx --std=c++11 -march=native -O3 mpi-integral.cpp -o mpi-integral; mpirun --report-bindings --bind-to hwthread --oversubscribe -np 1 mpi-integral >> time-hwthread.out
sleep 1s;
mpicxx --std=c++11 -march=native -O3 mpi-integral.cpp -o mpi-integral; mpirun --report-bindings --bind-to hwthread --oversubscribe -np 2 mpi-integral >> time-hwthread.out
sleep 1s;
mpicxx --std=c++11 -march=native -O3 mpi-integral.cpp -o mpi-integral; mpirun --report-bindings --bind-to hwthread --oversubscribe -np 3 mpi-integral >> time-hwthread.out
sleep 1s;
mpicxx --std=c++11 -march=native -O3 mpi-integral.cpp -o mpi-integral; mpirun --report-bindings --bind-to hwthread --oversubscribe -np 4 mpi-integral >> time-hwthread.out
sleep 1s;
