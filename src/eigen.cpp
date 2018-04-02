#include <cblas.h>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <chrono>
#include <iostream>
#include <Eigen/Dense>

double f_rand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatrixXXd;

int main(int argv, char* argc[]) {
    int i=0;

    omp_set_num_threads(4);
    Eigen::setNbThreads(4);

    size_t sz = std::stoi(argc[1]);

    MatrixXXd A = MatrixXXd::Zero(sz, sz);
    MatrixXXd B = MatrixXXd::Zero(sz, sz);
    MatrixXXd C = MatrixXXd::Zero(sz, sz);

    for(unsigned int i=0; i<sz; i++) {
        for(unsigned int j=0; j<sz; j++) {
            A(i,j) = f_rand(0, 10);
            B(i,j) = f_rand(0, 10);
        }
    }

    // A: m rows by k columns
    // B: k rows by n columns
    // C: m rows by n columns

    auto start = std::chrono::system_clock::now();

    C = A * B;

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;

    std::cout << elapsed_seconds.count() << " seconds passed." << std::endl;

    return 0;
}
