#include <cblas.h>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <chrono>
#include <iostream>

double f_rand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main() {
    int i=0;

    openblas_set_num_threads(4);

    static const size_t sz = 10000;

    std::vector<double> A(sz * sz);
    std::vector<double> B(sz * sz);
    std::vector<double> C(sz * sz);

    for(unsigned int i=0; i<sz; i++) {
        for(unsigned int j=0; j<sz; j++) {
            A[i * sz + j] = f_rand(0, 10);
            B[i * sz + j] = f_rand(0, 10);
        }
    }

    // A: m rows by k columns
    // B: k rows by n columns
    // C: m rows by n columns

    auto start = std::chrono::system_clock::now();

    cblas_dgemm(CblasColMajor,
                CblasNoTrans,
                CblasTrans,
                sz,         // m
                sz,         // n
                sz,         // k
                1,          // alpha
                &A[0],
                sz,         // leading dimension of A
                &B[0],
                sz,         // leading dimensions of B
                0,          // beta
                &C[0],
                sz          // leading dimension of C
                );

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;

    std::cout << elapsed_seconds.count() << " seconds passed." << std::endl;
}
