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
std::vector<T> GMRES(const CSR<T>& A, const std::vector<T>& b){
    std::vector<T> x(b.size());
    std::vector<T> r = b - A*x;
    int m = A.sizeW();
    T N = norm(r);

    std::vector<T> B;
    while ( N > tolerance<T> ){
        for(int i = 2; i <= m + 1; ++i){
            B.resize(i, 0);
            B[0] = N;
            auto [V, H] = KrylovSubSpace(A, r, i);
            HessenbergRot(H, B);
            if( Tabs(B.back()) < tolerance<T> || i == m + 1 ){
                H.deleteLastRow();
                B.pop_back();
                x = x + V * backSubstTopTriangular(H, B);
                r = b - A * x;
                N = norm(r);
                B.clear();
                break;
            }
            B.clear();
        }
    }
    return x;
}

#endif //SOLEMETHODS_GMRES_H
