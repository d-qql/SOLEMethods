#include <iostream>
#include "Dense/DenseMatrix.h"
#include "Dense/HeadGaussMethod.h"
#include "Tests/Tests.h"
#include "Dense/LU.h"
#include "Generators/RandVectorGenerator.h"
#include <cmath>
#include "Sparse/Jacobi.h"
#include "Sparse/GaussSeidel.h"
#include "Sparse/SimpleIteration.h"
#include "Chebyshev/Chebyshev.h"
int main() {
    std::set<Triplet<double>> in;
    std::vector<double> b = GenerateVector<double>(300, -1, 1);
    for(size_t k = 0; k < 300; ++k){
        in.insert({k, k, 1 + double(k+1)/598});
    }
    DenseMatrix<double> D = DenseMatrix<double>(300, 300, in);
    CSR<double> C = CSR<double>(300, 300, in);

    std::cout<<Jacobi(C, b)<<GaussSeidel(C, b)<<SimpleIteration(C, b, 1.);
    return 0;
}
