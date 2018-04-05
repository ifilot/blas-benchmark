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

#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <chrono>
#include <iostream>
#include <Eigen/Dense>
#include <thread>
#include "f_rand.h"
#include "get_proc.h"

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatrixXXd;

int main(int argv, char* argc[]) {
    int i=0;

    // allocate number of physical cores
    int numthreads = get_proc();
    omp_set_num_threads(numthreads);
    Eigen::setNbThreads(numthreads);

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

    C.noalias() = A * B;

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;

    std::cout << elapsed_seconds.count() << " seconds passed using " << numthreads << " threads." << std::endl;

    return 0;
}
