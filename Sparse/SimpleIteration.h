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
    int i = 0;
    while ( N > tolerance<T> ){
        x = x - tao * r;
        r = A * x - b;
        N = norm(r);
        ++i;
    }
    std::cout<<i<<std::endl;
    return x;
}

template<typename T>
std::vector<T> FastSimpleIteration(const CSR<T>& A, const std::vector<T>& b, const std::vector<T>& ChebRoots){
    std::vector<T> x(b.size());
    std::vector<T> r = b - A * x;

    T N = norm(r);
    bool flag = true;
    int i =0;
    while(flag){
        for(auto root : ChebRoots){
            x = -static_cast<T>(1)/root * r + x;
            r = b - A * x;
            N = norm(r);
            ++i;
            if( N < tolerance<T>){
                flag = false;
                break;
            }
        }
    }
    std::cout<<i<<std::endl;
    return x;
}

#endif //SOLEMETHODS_SIMPLEITERATION_H
