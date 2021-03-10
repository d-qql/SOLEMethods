//
// Created by d-qql on 16.02.2021.
//

#ifndef SOLEMETHODS_GAUSSSEIDEL_H
#define SOLEMETHODS_GAUSSSEIDEL_H
#include "CSR.h"
#include "../utility/Overloads.h"
#include "../utility/Consts.h"

template<typename T>
std::vector<T> GaussSeidel(const CSR<T>& A, const std::vector<T>& b){
    using idx_t = typename CSR<T>::idx_t ;

    std::vector<T> r(b.size());
    std::vector<T> x(b.size());

    T sum;
    r = A * x - b;

    while( norm(r) > tolerance<T> ){
        for(size_t i = 0; i < A.H; ++i){
            sum = 0;
            for(idx_t j = A.rows[i]; j < A.rows[i+1]; ++j){
                if( i != A.cols[j] ) sum += A.values[j] * x[A.cols[j]];
                else continue;
            }
            x[i] = (b[i] - sum)/A(i, i);
        }
        r = A * x - b;

    }
    //std::cout<<i<<std::endl;
    return x;
}
#endif //SOLEMETHODS_GAUSSSEIDEL_H
