//
// Created by d-qql on 23.03.2021.
//

#ifndef SOLEMETHODS_KRYLOV_H
#define SOLEMETHODS_KRYLOV_H
#include "../Sparse/CSR.h"
#include "../utility/Consts.h"
#include "../utility/Overloads.h"
#include <tuple>

template<typename T>
void KrylovSubSpace(const CSR<T>& A, std::vector<std::vector<T>>& Basis, DenseMatrix<T>& H, size_t N){

    std::vector<T> v = Basis.back();

    T h;

    v = A * Basis[N];
    for(size_t i = 0; i <= N; ++i){
        h = Basis[i] * v;
        v = v - h * Basis[i];
        if( Tabs(h) > tolerance<T> ) H(i, N) = h;
    }
    h = norm(v);
    if( Tabs(h) > tolerance<T> ) H(N+1, N) = h;
    v = 1. / h * v;
    Basis.push_back(v);
}

#endif //SOLEMETHODS_KRYLOV_H
