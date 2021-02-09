#include <iostream>
#include "Dense/DenseMatrix.h"
#include "Dense/HeadGaussMethod.h"
#include "Tests/Tests.h"
#include "Dense/LU.h"
#include "Generators/RandVectorGenerator.h"
#include <cmath>
int main() {
    DenseMatrix<double> A = DenseMatrix<double>(10, 10, GenerateMatrix<double>(10, -100, 100));\
    std::vector<double> b = GenerateVector<double>(10, -1, 1);

    std::cout<<GaussMethod(A, b)<<solveByLU(A, b);
    return 0;
}
