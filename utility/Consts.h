//
// Created by d-qql on 02.02.2021.
//

#ifndef SOLEMETHODS_CONSTS_H
#define SOLEMETHODS_CONSTS_H
#include <cmath>
template<typename T>
auto tolerance = static_cast<T>(1e-10);

template<typename T>
T Tabs(const T& a){
    if(a < T(0)) return -a;
    else return a;
}

template<typename T>
T norm(const std::vector<T>& a){
    T sum = 0;
    for(size_t i = 0; i < a.size(); ++i){
        sum += a[i]*a[i];
    }
    return sqrt(sum);
}
#endif //SOLEMETHODS_CONSTS_H
