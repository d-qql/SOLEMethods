//
// Created by d-qql on 28.01.2021.
//

#ifndef SOLECOURSE_RANDVECTORGENERATOR_H
#define SOLECOURSE_RANDVECTORGENERATOR_H

#include <vector>

template<typename T>
std::vector<T> GenerateVector(const size_t& size, const int &a, const int &b){
    std::vector<T> out(size);
    for(size_t i = 0; i < size; ++i){
        out[i] = a + static_cast <T> (rand()) /( static_cast <T> (RAND_MAX/(b-a)));
    }
    return out;
}

#endif //SOLECOURSE_RANDVECTORGENERATOR_H
