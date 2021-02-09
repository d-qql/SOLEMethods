//
// Created by d-qql on 09.02.2021.
//

#ifndef SOLEMETHODS_LU_H
#define SOLEMETHODS_LU_H
#include "DenseMatrix.h"
template<typename T>
std::pair<DenseMatrix<T>, DenseMatrix<T>> LUdecomp(const DenseMatrix<T>& A){
    using idx_t = typename DenseMatrix<T>::idx_t;

    DenseMatrix<T> L = DenseMatrix<T>(A.sizeH(), A.sizeW());
    DenseMatrix<T> U = DenseMatrix<T>(A.sizeH(), A.sizeW());

    for(idx_t i = 0; i < L.sizeW(); ++i){
        L(i, i) = 1;
    }
    T sum;
    for(idx_t i = 0; i < A.sizeH(); ++i){
        for(idx_t j = 0; j < A.sizeW(); ++j){
            sum = 0;
            if( i <= j){
                for(idx_t k = 0; k < j; ++k){
                    sum += L(i, k) * U(k, j);
                }
                U(i, j) = A(i, j) - sum;
            }else{
                for(idx_t k = 0; k < j; ++k){
                    sum += L(i, k) * U(k, j);
                }
                L(i, j) = (A(i, j) - sum)/U(j, j);
            }
        }
    }
    return {L, U};
}
template<typename T>
std::vector<T> solveByLU(const DenseMatrix<T>& A, const std::vector<T>& b){
    std::pair<DenseMatrix<T>, DenseMatrix<T>> LU = LUdecomp(A);
    return backSubstTopTriangular(LU.second, backSubstLowerTriangular(LU.first, b));
}

#endif //SOLEMETHODS_LU_H
