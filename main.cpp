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
#include "Sparse/GradientDescent.h"
#include "Sparse/CG.h"
#include "Krylov/Krylov.h"
#include "Sparse/GMRES.h"

int main() {
    std::set<Triplet<double>> in;


    std::vector<double> b = GenerateVector<double>(300, -1, 1);
    CSR<double> C = CSR<double>(300, 300, GenerateMatrix<double>(300, -100, 100));
    std::vector<double> x = GenerateVector<double>(300, -100, 100);


    return 0;
}
