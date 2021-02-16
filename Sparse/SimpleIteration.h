//
// Created by d-qql on 16.02.2021.
//

#ifndef SOLEMETHODS_SIMPLEITERATION_H
#define SOLEMETHODS_SIMPLEITERATION_H

#include "CSR.h"
#include "../utility/Overloads.h"
#include "../utility/Consts.h"

template<typename T>
std::vector<T> SimpleIteration(const CSR<T>& A, const std::vector<T>& b, const T& tao){
    std::vector<T> x(b.size());
    std::vector<T> r = A * x - b;
    T N = norm(r);
    while ( N > tolerance<T> ){
        x = x - tao * r;
        r = A * x - b;
        N = norm(r);
    }
    return x;
}

#endif //SOLEMETHODS_SIMPLEITERATION_H
