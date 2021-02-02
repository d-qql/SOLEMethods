//
// Created by d-qql on 02.02.2021.
//

#ifndef SOLEMETHODS_TESTS_H
#define SOLEMETHODS_TESTS_H
#include "../Dense/GaussMethod.h"
#include <ctime>

std::vector<std::pair<double, double>> testGaussMethod_Time(std::size_t maxDim) {
    srand(time(0));
    std::vector<std::pair<double, double>> time;

    std::set<Triplet<double>> in;
    for (int k = 3; k <= maxDim; ++k) { //замер времени для систем размерностью 3..maxDim
        std::vector<double> b(k);
        for (std::size_t i = 0; i < k; ++i) {
            for (std::size_t j = 0; j < k; ++j) {
                in.insert({i, j, double(rand() % 100000)});
            }
            b[i] = double(rand() % 100000);
        }
        DenseMatrix<double> A = DenseMatrix<double>(k, k, in);

        clock_t end, start = clock();               //замеряем время решения
        std::vector<double> res = GaussMethod(A, b);
        end = clock();
        for (auto i : res) {
            std::cout << i << " ";
        }
        time.emplace_back(k, double(end-start)/CLOCKS_PER_SEC); // сохраняем в вектора пару "размерность, время в секундах"
    }
    return time;
}

#endif //SOLEMETHODS_TESTS_H
