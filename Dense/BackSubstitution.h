//
// Created by d-qql on 02.02.2021.
//

#ifndef SOLEMETHODS_BACKSUBSTITUTION_H
#define SOLEMETHODS_BACKSUBSTITUTION_H
#include "DenseMatrix.h"

template<typename T>
std::vector<T> backSubstTopTriangular(const DenseMatrix<T>& A, const std::vector<T>& b){
    std::vector<T> res(b.size());
    res.back() = b.back()/A(A.sizeH()-1, A.sizeW()-1);
    T sum;
    for(int i = b.size() - 2; i >= 0; --i){
        sum = 0;
        for(size_t j = i + 1; j < b.size(); ++j){
            sum += A(i, j) * res[j];
        }
        res[i] = (b[i] - sum) / A(i, i);
    }
    return res;
}
#endif //SOLEMETHODS_BACKSUBSTITUTION_H
