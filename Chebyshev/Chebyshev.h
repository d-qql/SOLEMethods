//
// Created by d-qql on 16.02.2021.
//

#ifndef SOLEMETHODS_CHEBYSHEV_H
#define SOLEMETHODS_CHEBYSHEV_H
#include <vector>
#include <ctgmath>

template<typename T>
unsigned long long int C(int n, int k){
    unsigned long long int res = 1;
    for(int i = k + 1; i <= n; ++i){
        res *= i;
    }
    for(int i = 1; i <= n-k; ++i){
        res /= i;
    }
    return res;
}

template<typename T>
std::vector<T> ChebyshevRoots(std::pair<T, T> section, size_t PowOf2){
    size_t PolyOrder = std::pow(2, PowOf2);
    std::vector<T> roots(PolyOrder);
    for(size_t i = 1; i <= PolyOrder; ++i){
        roots[i-1] = (section.first+section.second) / 2 +
                (section.second - section.first) / 2 *
                static_cast<T>(cos(static_cast<double >(2 * i - 1) * M_PI_2 / PolyOrder ));
    }
    std::vector<size_t> idx;
    idx.push_back(0);
    idx.push_back(1);
    std::vector<size_t> next_idx;
    size_t curOrder;
    for(size_t i = 1; i < PowOf2; ++i){
        curOrder = pow(2, double(i+1));
        next_idx.resize(curOrder);
        for(size_t j = 0; j < curOrder - 1; j+=2){
            next_idx[j] = idx[j/2];
            next_idx[j + 1] = curOrder - 1 - next_idx[j];
        }
        idx = next_idx;
    }
    std::vector<T> res(roots.size());
    for(size_t i = 0; i < PolyOrder; ++i){
        res[i] = roots[idx[i]];
    }
    return res;
}

template<typename T>
std::vector<T> ChebyshevCoefs(std::pair<T, T> sec, size_t polyOrder){
    std::vector<T> coefs_f, coefs_s, coefs_new;

    coefs_f.emplace_back(static_cast<T>(1));

    coefs_s.emplace_back(static_cast<T>(0));
    coefs_s.emplace_back(static_cast<T>(1));

    for(size_t k = 1; k < polyOrder; ++k){
        coefs_new.resize(k+2);
        for(size_t i = 0; i < k + 1; ++i){
            coefs_new[i] -= coefs_f[i];
            coefs_new[i+1] += 2 * coefs_s[i];
            if(Tabs(coefs_new[i]) < tolerance<T>) coefs_new[i] = static_cast<T>(0);
            if(Tabs(coefs_new[i+1]) < tolerance<T>) coefs_new[i] = static_cast<T>(0);
        }
        coefs_f = coefs_s;
        coefs_s = coefs_new;
        coefs_new.clear();
    }
    coefs_new.resize(polyOrder + 1);
    for(int n = 0; n <= polyOrder; ++n){
        for(int k = 0; k <= n; ++k){
            coefs_new[n-k] += coefs_s[n] * C<T>(n, k) * pow(-(sec.first + sec.second)/(sec.second - sec.first), k) *
                    pow(static_cast<T>(2)/(sec.second-sec.first), n-k);
        }
    }
    T sum = static_cast<T>(0);
    for(auto i : coefs_new) sum += i;
    for(size_t i = 0; i <= polyOrder; ++i) coefs_new[i]/=sum;

    return coefs_new;
}
#endif //SOLEMETHODS_CHEBYSHEV_H
