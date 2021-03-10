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

    for(size_t k = 0; k < 15; ++k){
        in.insert({k, k, static_cast<double>(k+1)});
    }
    CSR<double> C = CSR<double>(15, 15, in);
    std::cout<<C.spectrum();
    return 0;
}
