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
std::tuple<DenseMatrix<T>, DenseMatrix<T>> KrylovSubSpace(const CSR<T>& A, const std::vector<T>& r, size_t N){
    std::set<Triplet<T>> H;
    std::vector<std::vector<T>> Basis;
    DenseMatrix<T> V(r.size(), N-1);
    std::vector<T> v = r;

    v = 1./norm(v) * v;
    Basis.push_back(v);
    T h;
    for(size_t j = 0; j < N-1; ++j){
        v = A * Basis[j];
        for(size_t i = 0; i <= j; ++i){
            h = Basis[i] * v;
            v = v - h * Basis[i];
            if( Tabs(h) > tolerance<T> ) H.insert({i, j, h});
        }
        h = norm(v);
        if( Tabs(h) > tolerance<T> ) H.insert({j+1, j, h});
        v = 1. / h * v;
        Basis.push_back(v);
    }
    for(size_t j = 0; j < N-1; ++j){
        for(size_t i = 0; i < r.size(); ++i){
            V(i, j) = Basis[j][i];
        }
    }
    return std::tuple<DenseMatrix<T>, DenseMatrix<T>>(V, DenseMatrix<T>(N, N - 1, H));
}

#endif //SOLEMETHODS_KRYLOV_H
