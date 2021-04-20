//
// Created by d-qql on 30.03.2021.
//

#ifndef SOLEMETHODS_GMRES_H
#define SOLEMETHODS_GMRES_H

#include "../Sparse/CSR.h"
#include "../Dense/BackSubstitution.h"
#include "../Givens/Rotation.h"
#include "../Krylov/Krylov.h"

template<typename T>
std::vector<T> GMRES(const CSR<T>& A, const std::vector<T>& b, int m){
    std::vector<T> x(b.size());
    std::vector<T> r = b - A * x;
    T N = norm(r);

    std::vector<T> B;
    std::vector<std::pair<T, T>> rotations;
    DenseMatrix<T> H(m+1, m);
    DenseMatrix<T> V(r.size(), m);
    std::vector<std::vector<T>> Basis;
    Basis.push_back(1./N * r);
    B.resize(m+1, 0);
    B[0] = N;
    for(int i = 2; i <= m + 1; ++i){
        KrylovSubSpace(A, Basis, H, i-2);
        HessenbergRot(H, B, i - 2, rotations);
        if( Tabs(B[i - 1]) < tolerance<T> || i == m + 1 ){
            for(size_t j = 0; j < i-1; ++j){
                for(size_t k = 0; k < r.size(); ++k){
                    V(k, j) = Basis[j][k];
                }
            }
            x = x + V * backSubstTopTriangular(H, B, i - 1);
            r = b - A * x;
            N = norm(r);
            std::cout<<"\n"<<N<<"\n";
            break;
        }
    }

    return x;
}

#endif //SOLEMETHODS_GMRES_H
