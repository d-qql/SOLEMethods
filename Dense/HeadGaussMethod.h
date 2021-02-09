//
// Created by d-qql on 26.01.2021.
//

#ifndef SOLECOURSE_HEADGAUSSMETHOD_H
#define SOLECOURSE_HEADGAUSSMETHOD_H

#include <vector>
#include "DenseMatrix.h"
#include "../utility/Consts.h"
#include "BackSubstitution.h"

template<typename T>
typename DenseMatrix<T>::idx_t col_max(const DenseMatrix<T> &A, const typename DenseMatrix<T>::idx_t& col) {
    using idx_t = typename DenseMatrix<T>::idx_t;
    using elm_t = typename DenseMatrix<T>::elm_t;
    elm_t max = Tabs(A(col,col));
    int maxPos = col;
    for (idx_t i = col+1; i < A.sizeH(); ++i) {     //поиск максимального по модулю элемента в столбце col под диагональю
        elm_t element = Tabs(A(i, col));
        if (element > max) {
            max = element;
            maxPos = i;
        }
    }
    return maxPos;
}

template <typename T>
unsigned int headTriangulation(DenseMatrix<T> &A, std::vector<T> &b) {

    using idx_t = typename DenseMatrix<T>::idx_t;
    using elm_t = typename DenseMatrix<T>::elm_t;

    unsigned int swapCount = 0;

    for (idx_t i = 0; i < A.sizeH()-1; ++i) {
        idx_t imax = col_max(A, i); //индекс максимального по модулю элемента под диагональю
        if(Tabs(A(imax, i)) < tolerance<T>){  //если максимальный равен 0, то пропускаем столбец из рассмотрения
            continue;
        }else {
            if (i != imax) {
                A.swap(i, imax);        //переставляем строку с максимальным по модулю элементом с текущей местами
                std::swap(b[i], b[imax]); //элемент свободного столбца также переставляется
                ++swapCount;
            }

            for (idx_t k = i + 1; k < A.sizeH(); ++k) { //проход по всем строкам под текущей
                elm_t coef = (A(k, i) / A(i, i));
                for (idx_t j = i; j < A.sizeW(); ++j) { //проход по всем элементам строки
                    A(k, j) -= A(i, j) * coef;          //вычитание из строки k строки i, умноженной на коэффициент для зануления элементов столбца i
                }
                b[k] -= b[i] * coef; //вычитание свободного члена уравнения
            }
        }
    }
    return swapCount;   //возвращаем число перестановок(может потребоваться для поиска определителя)
}

template <typename T>
std::vector<T> headGaussMethod(DenseMatrix<T> A,
                             std::vector<T> b) {

    headTriangulation(A, b); //приводим матрицу к верхнетреугольной с выбором главного элемента
    return backSubstTopTriangular(A, b);
}


#endif //SOLECOURSE_HEADGAUSSMETHOD_H
