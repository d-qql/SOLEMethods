//
// Created by d-qql on 02.02.2021.
//

#ifndef SOLEMETHODS_CONSTS_H
#define SOLEMETHODS_CONSTS_H

template<typename T>
auto tolerance = static_cast<T>(1e-10);

template<typename T>
T Tabs(const T& a){
    if(a < T(0)) return -a;
    else return a;
}
#endif //SOLEMETHODS_CONSTS_H
