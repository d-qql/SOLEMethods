//
// Created by d-qql on 23.03.2021.
//

#ifndef SOLEMETHODS_GRADIENTDESCENT_H
#define SOLEMETHODS_GRADIENTDESCENT_H
#include "CSR.h"
#include "../utility/Overloads.h"
#include "../utility/Consts.h"

template<typename T>
std::vector<T> GradientDescent(const CSR<T>& A, const std::vector<T>& b){
    std::vector<T> r(b.size());
    std::vector<T> x(b.size());
    T a;
    r = b - A * x;
    T N = norm(r);
    int it = 0;
    while( N > tolerance<T> ){
        a = r*r/(r * (A * r));
        x = x + a * r;
        r = b - A * x;
        N = norm(r);
        it++;
    }
    std::cout<<"\n"<<it<<std::endl;
    return x;
}
#endif //SOLEMETHODS_GRADIENTDESCENT_H
