//
// Created by d-qql on 02.02.2021.
//

#ifndef SOLEMETHODS_TESTS_H
#define SOLEMETHODS_TESTS_H
#include "../Dense/GaussMethod.h"
#include "../Dense/HeadGaussMethod.h"
#include "../Generators/RandMatrixGenerator.h"
#include "../Generators/RandVectorGenerator.h"
#include "../utility/gnuplot-iostream.h"
#include "../utility/Overloads.h"
#include "../utility/Consts.h"
#include <ctime>

void testGaussMethods_Norm(size_t dim){
    std::vector<std::pair<double, double>> plotData1;
    std::vector<std::pair<double, double>> plotData2;
    for(int i = 3; i < dim; ++i){
        DenseMatrix<double> A = DenseMatrix<double>(i, i, GenerateMatrix<double>(i, -1000, 1000));
        std::vector<double> b = GenerateVector<double>(i, -1, 1);
        std::vector<double> res = GaussMethod(A, b);

        plotData1.emplace_back(i, log(norm(b-A*res)));
        res = headGaussMethod(A, b);
        plotData2.emplace_back(i, log(norm(b-A*res)));

    }
    Gnuplot gp;
    gp<<"set xlabel 'Matrix Dimension' \n"
        "set ylabel 'ln(|r|))'\n"
        "set grid\n"
        "set title 'Зависимость логарифма модуля невязки от размера матрицы headGaussMethod' font 'Helvetica Bold, 10'\n";
    gp << "plot '-' with lines title 'pureGauss' lc rgb 'blue',"
          "     '-' with lines title 'headGauss' lc rgb 'red'\n";
    gp.send1d(plotData1);
    gp.send1d(plotData2);
}

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
