//
// Created by d-qql on 23.03.2021.
//

#ifndef SOLEMETHODS_CG_H
#define SOLEMETHODS_CG_H
#include <vector>
#include "CSR.h"
#include "../utility/Consts.h"
#include "../utility/Overloads.h"

template<typename T>
std::vector<T> CGmethod(const CSR<T>& A, const std::vector<T>& b){
    std::vector<T> x(b.size());
    std::vector<T> Ri = b - A * x;
    std::vector<T> Ri1(b.size());
    std::vector<T> Di = Ri;
    std::vector<T> Di1(b.size());
    auto a = static_cast<T>(0);
    int it = 0;
    T N = norm(Ri);
    while( N > tolerance<T> ){
        a = Ri*Di/(Di * (A * Di));
        x = x + a * Di;
        Ri1 = b - A * x;
        Di1 = Ri1 + (Ri1 * Ri1)/(Ri * Di) * Di;
        Di = Di1;
        Ri = Ri1;
        it++;
        N = norm(Ri);
    }
    std::cout<<"\n"<<it<<std::endl;

    return x;
}
#endif //SOLEMETHODS_CG_H
