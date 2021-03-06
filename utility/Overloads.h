//
// Created by d-qql on 09.02.2021.
//

#ifndef SOLEMETHODS_OVERLOADS_H
#define SOLEMETHODS_OVERLOADS_H
#include <vector>
template<typename T>
std::vector<T> operator*(const T& k, const std::vector<T>& b){
    std::vector<T> res(b.size());
    for(size_t i = 0; i < b.size(); ++i){
        res[i] = b[i] * k;
    }
    return res;
}

template<typename T>
T operator*(const std::vector<T>& a, const std::vector<T>& b){
    T sum = 0;
    for(size_t i = 0; i < b.size(); ++i){
        sum += b[i] * a[i];
    }
    return sum;
}

template<typename T>
std::vector<T> operator-(const std::vector<T>& a, const std::vector<T>& b){
    std::vector<T> res(a.size());
    for(size_t i = 0; i < a.size(); ++i){
        res[i] = a[i] - b[i];
    }
    return res;
}

template<typename T>
std::vector<T> operator+(const std::vector<T>& a, const std::vector<T>& b){
    std::vector<T> res(a.size());
    for(size_t i = 0; i < a.size(); ++i){
        res[i] = a[i] + b[i];
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
