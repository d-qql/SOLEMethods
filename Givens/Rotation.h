//
// Created by d-qql on 30.03.2021.
//

#ifndef SOLEMETHODS_ROTATION_H
#define SOLEMETHODS_ROTATION_H

#include "../Dense/DenseMatrix.h"
#include "../utility/Consts.h"
#include "../utility/Overloads.h"

template<typename T>
void HessenbergRot(DenseMatrix<T>& H, std::vector<T>& b){
    T cos;
    T sin;
    T up, down;
    T Bup, Bdown;
    for(size_t k = 0; k < H.sizeW(); ++k){
        cos = H(k, k)/sqrt(H(k, k)*H(k, k) + H(k + 1, k)*H(k + 1, k));
        sin = H(k + 1, k)/sqrt(H(k, k)*H(k, k) + H(k + 1, k)*H(k + 1, k));
        Bup = cos * b[k] + sin * b[k + 1];
        Bdown = -sin * b[k] + cos * b[k + 1];
        b[k] = Bup;
        b[k+1] = Bdown;
        for(size_t j = 0; j < H.sizeW(); ++j){
            up = cos * H(k, j) + sin * H(k + 1, j);
            down = -sin * H(k, j) + cos * H(k + 1, j);
            if(Tabs(down) < tolerance<T>) down = 0;
            H(k, j) = up;
            H(k + 1, j) = down;
        }
    }
}

#endif //SOLEMETHODS_ROTATION_H
