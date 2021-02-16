//
// Created by d-qql on 16.02.2021.
//

#ifndef SOLEMETHODS_JACOBI_H
#define SOLEMETHODS_JACOBI_H
#include "CSR.h"
#include "../utility/Overloads.h"
#include "../utility/Consts.h"

template<typename T>
std::vector<T> Jacobi(const CSR<T>& A, const std::vector<T>& b){
    using idx_t = typename CSR<T>::idx_t ;

    std::vector<T> r(b.size());
    std::vector<T> x(b.size());
    std::vector<T> temp_x(b.size());

    T sum;
    r = A * x - b;
    while( norm(r) > tolerance<T> ){
        for(size_t i = 0; i < A.H; ++i){
            for(idx_t j = A.rows[i]; j < A.rows[i+1]; ++j){
                if( i != A.cols[j] ) sum += A.values[j] * b[A.cols[j]];
                else continue;
            }
            temp_x[i] = (b[i] - sum)/A(i, i);
        }
        x = temp_x;
        r = A * x - b;
    }
    return x;
}
#endif //SOLEMETHODS_JACOBI_H
