#!/bin/bash

# load libs
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/openblas/lib

# test openblas
echo 'Testing OpenBLAS compilation'
g++ -lopenblas -lpthread -lhwloc -fopenmp src/openblas.cpp -o test -O3 -DNDEBUG -march=native
echo -ne '512\t'
./test 512
echo -ne '1024\t'
./test 1024
echo -ne '2048\t'
./test 2048
echo -ne '4096\t'
./test 4096
echo -ne '8192\t'
./test 8192
echo ""

# test intel
echo 'Testing Intel compilation'
icpc -lhwloc src/intel.cpp -o test -O3 -xHost -DMKL_ILP64 -I${MKLROOT}/include -L${MKLROOT}/lib/intel64  -lmkl_rt -lpthread -lm -ldl
echo -ne '512\t'
./test 512
echo -ne '1024\t'
./test 1024
echo -ne '2048\t'
./test 2048
echo -ne '4096\t'
./test 4096
echo -ne '8192\t'
./test 8192
echo ""

# test eigen
echo 'Testing Eigen3 compilation'
g++ src/eigen.cpp -fopenmp -lhwloc `pkg-config --cflags eigen3` -o test -march=native -DNDEBUG -O3
echo -ne '512\t'
./test 512
echo -ne '1024\t'
./test 1024
echo -ne '2048\t'
./test 2048
echo -ne '4096\t'
./test 4096
echo -ne '8192\t'
./test 8192
echo ""
