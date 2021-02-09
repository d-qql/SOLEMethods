//
// Created by d-qql on 09.02.2021.
//

#ifndef SOLEMETHODS_OVERLOADS_H
#define SOLEMETHODS_OVERLOADS_H
#include <vector>
template<typename T>
std::vector<T> operator-(const std::vector<T>& a, const std::vector<T>& b){
    std::vector<T> res(a.size());
    for(size_t i = 0; i < a.size(); ++i){
        res[i] = a[i] - b[i];
    }
    return res;
}


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& b){
    os<<"\n";
    for(auto i : b){
        os<<i<<" ";
    }
    return os;
}
#endif //SOLEMETHODS_OVERLOADS_H
