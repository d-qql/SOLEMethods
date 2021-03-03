//
// Created by d-qql on 02.03.2021.
//

#ifndef SOLEMETHODS_SSOR_H
#define SOLEMETHODS_SSOR_H
#include "CSR.h"
#include "../utility/Overloads.h"
#include "../utility/Consts.h"

template<typename T>
std::vector<T> SSOR(const CSR<T>& A, const std::vector<T>& b, const T& w){
    std::vector<T> x(b.size());
    std::vector<T> r = b - A * x;
    std::vector<T> temp_x(x.size());

    T sum;
    T N = norm(r);
int k = 0;
    while( N > tolerance<T>){
        temp_x = x;
        for(size_t i = 0; i < x.size(); ++i){
            sum = static_cast<T>(0);
            for(size_t j = A.rows[i]; j < A.rows[i+1]; ++j){
                if( i != A.cols[j] ) sum += A.values[j] * x[A.cols[j]];
                else continue;
            }
            sum *= w;
            x[i] = (w * b[i] - sum)/A(i, i) + (static_cast<T>(1) - w) * temp_x[i];
        }
        temp_x = x;
        for(int i = x.size() - 1; i >= 0; --i){
            sum = static_cast<T>(0);
            for(size_t j = A.rows[i]; j < A.rows[i+1]; ++j){
                if( i != A.cols[j] ) sum += A.values[j] * x[A.cols[j]];
                else continue;
            }
            sum *= w;
            x[i] = (w * b[i] - sum)/A(i, i) + (static_cast<T>(1) - w) * temp_x[i];
        }
        r = b - A * x;
        N = norm(r);
        ++k;
    }
    std::cout<<"\n"<<k<<"\n";
    return x;
}


#endif //SOLEMETHODS_SSOR_H
