//
// Created by d-qql on 02.02.2021.
//

#ifndef SOLEMETHODS_GAUSSMETHOD_H
#define SOLEMETHODS_GAUSSMETHOD_H
#include "DenseMatrix.h"
#include "../utility/Consts.h"
#include "BackSubstitution.h"

template<typename T>
typename DenseMatrix<T>::idx_t col_nonzero(const DenseMatrix<T>& A, const typename DenseMatrix<T>::idx_t& col){
    using idx_t = typename DenseMatrix<T>::idx_t;
    if( Tabs(A(col, col)) > tolerance<T> ) return col;
    else {
        for(idx_t i = col + 1; i < A.sizeH(); ++i){
            if(Tabs( A(i, col) ) > tolerance<T>) return i;
        }
    }
    return col;
}

template<typename T>
std::size_t triangulation(DenseMatrix<T>& A, std::vector<T>& b){
    using idx_t = typename DenseMatrix<T>::idx_t;
    using elm_t = typename DenseMatrix<T>::elm_t;

    std::size_t swapCount = 0;

    for(idx_t i = 0; i < A.sizeH()-1; ++i){
        idx_t iNonZero = col_nonzero(A, i);
        if(Tabs(A(iNonZero, i)) > tolerance<T>){
            A.swap(i, iNonZero);
            std::swap(b[i], b[iNonZero]);
            ++swapCount;
        } else { continue; }
        for(idx_t k = i+1; k<A.sizeH(); ++k){
            elm_t coef = A(k, i)/A(i, i);
            for(idx_t j = 0; j < A.sizeW(); ++j){
                A(k, j) -= A(i, j)*coef;
            }
            b[k] -= b[i] * coef;
        }
    }
    return swapCount;
}
template<typename T>
std::vector<T> GaussMethod(DenseMatrix<T> A, std::vector<T> b){
    triangulation(A, b);
    return backSubstTopTriangular(A, b);
}
#endif //SOLEMETHODS_GAUSSMETHOD_H
