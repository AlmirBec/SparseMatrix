#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include "list.h"
#include <vector>
#include <utility>
#include<algorithm>

template <typename Type>
using Vector = std::vector<std::pair<std::pair<int, int>, Type>>;

template <typename Type>
class Matrix{
    List<List<Type>> matrix;
    int numberOfRows;
    int numberOfColumns;
    //Dvije pomocne funkcije
    void fillZeros(){
        for(int i = 0; i < numberOfRows; i++){
        List<Type> l;
            for(int j = 0; j < numberOfColumns; j++){
                l.PushBack(0);
            }
        matrix.PushBack(l);
        }
    }
    void deleteZeros(){
         typename List<List<Type>>::Iterator it;
        for(it = matrix.Begin(); it != matrix.End(); it++){
            for(typename List<Type>::Iterator it2 = (*it).Begin(); it2 != (*it).End(); it2++){
                if(*it2 == 0){
                    (*it).Erase(it2);
                }
            }
        }
    }
public:

    void setRows(int r){
        numberOfRows = r;
    }
    void setColumns(int c){
        numberOfColumns = c;
    }
    int getRows(){
        return numberOfRows;
    }
    int getColumns(){
        return numberOfColumns;
    }
    Matrix(){
        numberOfRows = 0;
        numberOfColumns = 0;
    }
    Matrix(int row, int col);
    Matrix(int row, int col, std::vector<std::pair<std::pair<int, int>, Type>> elements);

    ~Matrix(){};

    Matrix(const Matrix<Type> &Copy);
    Matrix(Matrix<Type> &&Copy);

    Matrix<Type>& operator=(const Matrix<Type> &rhs);
    Matrix<Type>& operator=(Matrix<Type> &&rhs);

    Matrix<Type> &exponentiate(int n);

    Matrix<Type>& transpose();

    void Print();

    template <typename Type1>
    friend Matrix<Type1>& operator+(Matrix<Type1> &m1, Matrix<Type1> &m2);

    template <typename Type1>
    friend Matrix<Type1>& operator-(Matrix<Type1> &m1, Matrix<Type1> &m2){
        return m1 + (m2^(-1));
    }

    //Mnozenje matrica
    template <typename Type1>
    friend Matrix<Type1>& operator^(Matrix<Type1> &m1, Matrix<Type1> &m2);

    //Mnozenje matrica sa skalarom
    template <typename Type1, typename Type2>
    friend Matrix<Type1>& operator^(Matrix<Type1> &m1, Type2 number);

    template <typename Type1, typename Type2>
    friend Matrix<Type1>& operator^(Type2 number, Matrix<Type1> &m1){
        return m1^number;
    }
};

#include "matrix.cpp"

#endif // MATRIX_H_INCLUDED
