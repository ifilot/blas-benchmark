/************************************************************************************
 *                                                                                  *
 * Copyright 2018 Ivo Filot                                                         *
 *                                                                                  *
 * Permission is hereby granted, free of charge, to any person obtaining a copy     *
 * of this software and associated documentation files (the "Software"), to deal    *
 * in the Software without restriction, including without limitation the rights     *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell        *
 * copies of the Software, and to permit persons to whom the Software is            *
 * furnished to do so, subject to the following conditions:                         *
 *                                                                                  *
 * The above copyright notice and this permission notice shall be included in       *
 * all copies or substantial portions of the Software.                              *
 *                                                                                  *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS          *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE      *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER           *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING          *
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS     *
 * IN THE SOFTWARE.                                                                 *
 *                                                                                  *
 ************************************************************************************/

#include <cblas.h>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <chrono>
#include <iostream>
#include "f_rand.h"
#include "get_proc.h"


int main(int argv, char* argc[]) {
    int i=0;

    // allocate number of physical cores
    int numthreads = get_proc();
    openblas_set_num_threads(numthreads);

    size_t sz = std::stoi(argc[1]);

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

    std::cout << elapsed_seconds.count() << " seconds passed using " << numthreads << " threads." << std::endl;

    return 0;
}
