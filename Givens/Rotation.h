//
// Created by d-qql on 30.03.2021.
//

#ifndef SOLEMETHODS_ROTATION_H
#define SOLEMETHODS_ROTATION_H

#include "../Dense/DenseMatrix.h"
#include "../utility/Consts.h"
#include "../utility/Overloads.h"

template<typename T>
void HessenbergRot(DenseMatrix<T>& H, std::vector<T>& b, size_t SZ, std::vector<std::pair<T, T>>& rotations){
    T cos;
    T sin;
    T up, down;
    T Bup, Bdown;
    for(size_t k = 0; k < rotations.size(); ++k){
        cos = rotations[k].first;
        sin = rotations[k].second;
        up = cos * H(k, SZ) + sin * H(k + 1, SZ);
        down = -sin * H(k, SZ) + cos * H(k + 1, SZ);
        if(Tabs(down) < tolerance<T>) down = 0;
        H(k, SZ) = up;
        H(k + 1, SZ) = down;
    }
    cos = H(SZ, SZ) / sqrt(H(SZ, SZ) * H(SZ, SZ) + H(SZ + 1 , SZ) * H(SZ + 1, SZ));
    sin = H(SZ + 1, SZ) / sqrt(H(SZ, SZ) * H(SZ, SZ) + H(SZ + 1 , SZ) * H(SZ + 1, SZ));
    Bup = cos * b[SZ] + sin * b[SZ + 1];
    Bdown = -sin * b[SZ] + cos * b[SZ + 1];
    b[SZ] = Bup;
    b[SZ + 1] = Bdown;
    up = cos * H(SZ, SZ) + sin * H(SZ + 1, SZ);
    down = -sin * H(SZ, SZ) + cos * H(SZ + 1, SZ);
    if(Tabs(down) < tolerance<T>) down = 0;
    H(SZ, SZ) = up;
    H(SZ + 1, SZ) = down;
    rotations.push_back({cos, sin});
}

#endif //SOLEMETHODS_ROTATION_H
