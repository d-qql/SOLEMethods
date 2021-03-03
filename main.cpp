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
#include "Sparse/SOR.h"
#include "Sparse/SSOR.h"
int main() {
    std::set<Triplet<double>> in;
    std::vector<double> b = GenerateVector<double>(300, -1, 1);
    for(size_t k = 0; k < 300; ++k){
        in.insert({k, k, 1 + double(k+1)/598});
    }
    CSR<double> C = CSR<double>(300, 300, in);

    std::cout<<SOR(C, b, 0.9)<<SSOR(C, b, 0.9);
    return 0;
}
