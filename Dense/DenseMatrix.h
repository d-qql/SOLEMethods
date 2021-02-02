//
// Created by d-qql on 02.02.2021.
//

#ifndef SOLEMETHODS_DENSEMATRIX_H
#define SOLEMETHODS_DENSEMATRIX_H
#include <vector>
#include "../utility/Tripet.h"
#include "set"

template<typename T>
class DenseMatrix{
public:
    using elm_t = T;
    using idx_t = std::size_t;

private:

    std::vector<T> matrix;
    idx_t H, W;

public:
    DenseMatrix(const idx_t &h, const idx_t& w, const std::set<Triplet<T>>& in): H(h), W(w){
        matrix.resize(W*H);
        for(auto i: in){
            matrix[i.i*W +i.j] = i.value;
        }
    }

    elm_t& operator()(const idx_t& i, const idx_t& j){
        return matrix[i * W + j];
    }
    const elm_t& operator()(const idx_t& i, const idx_t& j) const {
        return matrix[i * W + j];
    }
    [[nodiscard]] const idx_t& sizeH() const {
        return H;
    }
    [[nodiscard]] const idx_t& sizeW() const {
        return W;
    }

    void swap(const idx_t& first, const idx_t& second){
        for(idx_t j = 0; j < W; ++j){
            std::swap(matrix[first * W + j], matrix[second * W + j]);
        }
    }

};
template<typename T>
std::ostream& operator<<(std::ostream& os, const DenseMatrix<T>& A){
    for(std::size_t i = 0; i < A.sizeH(); ++i){
        for(std::size_t j = 0; j < A.sizeW(); ++j){
            os<<A(i, j)<<" ";
        }
        os<<std::endl;
    }
    return os;
}

#endif //SOLEMETHODS_DENSEMATRIX_H
