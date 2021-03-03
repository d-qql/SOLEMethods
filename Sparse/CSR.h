//
// Created by d-qql on 09.02.2021.
//

#ifndef SOLEMETHODS_CSR_H
#define SOLEMETHODS_CSR_H
#include <vector>
#include <set>
#include "../utility/Triplet.h"
#include <algorithm>

template<typename T>
class CSR{
public:
    using elm_t = T;
    using idx_t = std::size_t;
private:
    const idx_t H, W;
    std::vector<elm_t> values;
    std::vector<idx_t> cols;
    std::vector<idx_t> rows;

    template<typename EL>
    friend std::vector<EL> Jacobi(const CSR<EL>& A, const std::vector<EL>& b);
    template<typename EL>
    friend std::vector<EL> GaussSeidel(const CSR<EL>& A, const std::vector<EL>& b);
    template<typename EL>
    friend std::vector<EL> SOR(const CSR<EL>& A, const std::vector<EL>& b, const EL& w);
    template<typename EL>
    friend std::vector<EL> SSOR(const CSR<EL>& A, const std::vector<EL>& b, const EL& w);
public:
    CSR(const idx_t &h, const idx_t &w, const std::set<Triplet<elm_t>>& in): H(h), W(w){
        values.resize(in.size());
        cols.resize(in.size());
        rows.resize(H+1);
        int countInRow = 0;
        int currRow = 0;
        auto it = in.begin();
        for(idx_t k = 0; k < in.size(); ++k){
            while(currRow < it->i){
                rows[currRow+1] = rows[currRow] + countInRow;
                ++currRow;
                countInRow = 0;
            }
            values[k] = it->value;
            cols[k] = it->j;
            ++countInRow;
            it = next(it);
        }
        for(++currRow; currRow <= H; ++currRow){
            rows[currRow] = in.size();
        }
    }
    [[nodiscard]] idx_t sizeH() const{
        return H;
    }
    [[nodiscard]] idx_t sizeW() const{
        return W;
    }

    std::vector<elm_t> operator*(const std::vector<elm_t> &b) const{
        std::vector<elm_t> res(this->H);
        for(idx_t i = 0; i < H; ++i){
            for(idx_t j = rows[i]; j < rows[i+1]; ++j) res[i] += values[j] * b[cols[j]];
        }
        return res;
    }

    elm_t operator()(idx_t const i, idx_t const j) const{
        idx_t skip = this->rows[i];
        idx_t count = this->rows[i+1] - skip;
        for(idx_t k = skip; k < skip + count; ++k){
            if(this->cols[k] == j) return this->values[k];
        }
        return static_cast<elm_t>(0);
    }

};
#endif //SOLEMETHODS_CSR_H
