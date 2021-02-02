//
// Created by d-qql on 02.02.2021.
//

#ifndef SOLEMETHODS_TRIPET_H
#define SOLEMETHODS_TRIPET_H

template<typename T>
struct Triplet{
    std::size_t i;
    std::size_t j;
    T value;
    bool operator<(Triplet<T> const & rgh) const{
        return this->i<rgh.i || (this->i == rgh.i && this->j < rgh.j);
    }
};
#endif //SOLEMETHODS_TRIPET_H
