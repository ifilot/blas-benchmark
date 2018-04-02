#!/bin/bash

# load libs
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/openblas/lib

# test openblas
echo 'Testing OpenBLAS compilation'
g++ -I /opt/openblas/include/ -L /opt/openblas/lib -lopenblas -lpthread -fopenmp src/openblas.cpp -o test -O3 -DNDEBUG -march=native
echo -ne '512\t'
./test 512
echo -ne '1024\t'
./test 1024
echo -ne '2048\t'
./test 2048
echo -ne '4096\t'
./test 4096
echo ""

# test eigen
echo 'Testing Eigen3 compilation'
g++ src/eigen.cpp -fopenmp `pkg-config --cflags eigen3` -o test -march=native -DNDEBUG -O3
echo -ne '512\t'
./test 512
echo -ne '1024\t'
./test 1024
echo -ne '2048\t'
./test 2048
echo -ne '4096\t'
./test 4096
echo ""
