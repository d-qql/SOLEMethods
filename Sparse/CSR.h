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
    CSR(const idx_t &h, const idx_t &w, const std::vector<T>& v,const std::vector<T>& c, const std::vector<T>& r){
        values = v;
        cols = c;
        rows = r;
    }
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

    elm_t spectrum(){
        std::vector<elm_t> x = GenerateVector<elm_t>(this->W, -1, 1);
        x = static_cast<elm_t>(1) / norm(x) * x;
        std::vector<elm_t> prev_x(this->W);

        auto lambda = static_cast<elm_t>(0);
        elm_t prev_lambda;

        auto err = static_cast<elm_t>(100);
        while (err > tolerance<elm_t>){
            prev_x = x;
            x = this->operator*(x);
            prev_lambda = lambda;
            lambda = x * prev_x;
            x = static_cast<elm_t>(1) / norm(x) * x;
            err = Tabs(prev_lambda - lambda) / std::max(Tabs(prev_lambda), Tabs(lambda));
        }
        return lambda;
    }

    CSR transpose() const{
        idx_t NonZero = values.size();
        std::vector<T> tVals(NonZero);
        std::vector<T> tCols(NonZero);
        std::vector<T> tRows(W + 1);
        for(idx_t i = 0; i < NonZero; ++i) tRows[cols[i] + 1]++;
        idx_t S = 0;
        idx_t tmp;
        for(idx_t i = 1; i <= W; ++i){
            tmp = tRows[i];
            tRows[i] = S;
            S += tmp;
        }
        idx_t j1, j2, Col, RIndex, IIndex;
        elm_t V;
        for(idx_t i = 0; i < H; ++i){
            j1 = rows[i];
            j2 = rows[i+1];
            Col = i;
            for(idx_t j = j1; j < j2; ++j){
                V = values[j];
                RIndex = cols[j];
                IIndex = tRows[RIndex + 1];
                tVals[IIndex] = V;
                tCols[IIndex] = Col;
                tRows[RIndex + 1]++;
            }
        }
        return CSR(W, H, tVals, tCols, tRows);
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
template<typename T>
std::ostream& operator<<(std::ostream& os, const CSR<T>& A){
    os<<std::endl;
    for(std::size_t i = 0; i < A.sizeH(); ++i){
        for(std::size_t j = 0; j < A.sizeW(); ++j){
            os<<A(i, j)<<" ";
        }
        os<<std::endl;
    }
    return os;
}
#endif //SOLEMETHODS_CSR_H
