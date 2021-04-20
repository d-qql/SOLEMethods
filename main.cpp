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

    size_t SZ = 50;
    std::set<Triplet<double>> in = GenerateMatrixDiagDominant<double>(SZ);
    DenseMatrix<double> D(SZ, SZ, in);
    CSR<double> A = CSR<double>(SZ, SZ, in);
    std::vector<double> b = GenerateVector<double>(SZ, -1, 1);
    std::cout<<GMRES(A, b, 50)<<GaussMethod(D, b);



    return 0;
}
