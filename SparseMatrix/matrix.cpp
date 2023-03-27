#ifndef MATRIX_CPP
#define MATRIX_CPP

#include "matrix.h"
#include<iostream>
#include<typeinfo>
template <typename Type>
Matrix<Type>::Matrix(int rows, int cols):numberOfRows(rows), numberOfColumns(cols){
    if(rows < 0 || cols < 0) throw "Nemoguce kreirati matricu sa negativnim brojem dimenzije";
    Matrix<Type>::fillZeros();
}

template <typename Type>
Matrix<Type>::Matrix(int rows, int cols, Vector<Type> elements):numberOfRows(rows), numberOfColumns(cols){
    if(rows < 0 || cols < 0) throw "Nemoguce kreirati matricu sa negativnim brojem dimenzije";

    Matrix<Type>::fillZeros();

    //sortiramo vektor kako bi onda redom ubacivali elemente
    std::sort(elements.begin(), elements.end());

    for(int i = 0; i < elements.size(); i++){
        if(elements[i].first.first < 0 || elements[i].first.first > rows ||
           elements[i].first.second < 0 || elements[i].first.second > cols) throw "Nepostojece koordinate";
    }
    //Nula elemente na odredjenim pozicijama zamjenjujemo sa nenultim vrijednostima
    typename List<List<Type>>::Iterator it;
    int i = 0;
    for(it = matrix.Begin(); it != matrix.End(); it++){
        if(it.getPosition() == elements[i].first.first){
            for(typename List<Type>::Iterator it2 = (*it).Begin(); it2 != (*it).End(); it2++){
                if(it2.getPosition() == elements[i].first.second && it.getPosition() == elements[i].first.first){
                    *it2 = elements[i].second;
                    i++;
                }
            }
        }
    }
    //Brisemo nepotrebne nule
    Matrix<Type>::deleteZeros();
    }


template <typename Type>
void Matrix<Type>::Print(){
    typename List<List<Type>>::Iterator it;
    for(it = matrix.Begin(); it != matrix.End(); it++){
        int i = it.getPosition();
        for(typename List<Type>::Iterator it2 = (*it).Begin(); it2 != (*it).End(); it2++){
            int j = it2.getPosition();
            std::cout <<"Vrijednost: "<< *it2 << ", Pozicija: (" << i <<","<< j << "). " ;
            std::cout << std::endl;
        }
    }
}
template <typename Type>
    Matrix<Type>::Matrix(const Matrix<Type> &Copy):numberOfRows(Copy.numberOfRows), numberOfColumns(Copy.numberOfColumns), matrix(Copy.matrix){
}

template <typename Type>
    Matrix<Type>::Matrix(Matrix<Type> &&Copy):numberOfRows(Copy.numberOfRows), numberOfColumns(Copy.numberOfColumns), matrix(Copy.matrix){
}

template <typename Type>
    Matrix<Type>& Matrix<Type>::operator=(const Matrix<Type> &rhs) {
        if(this == &rhs) return *this;

        numberOfRows = rhs.numberOfRows;
        numberOfColumns = rhs.numberOfColumns;
        matrix = rhs.matrix;

        return *this;
    }

template <typename Type>
    Matrix<Type>& Matrix<Type>::operator=(Matrix<Type> &&rhs) {
        numberOfRows = rhs.numberOfRows;
        numberOfColumns = rhs.numberOfColumns;
        matrix = rhs.matrix;

        rhs.numberOfRows = 0;
        rhs.numberOfColumns = 0;

        return *this;
}

template <typename Type1>
    Matrix<Type1>& operator+(Matrix<Type1> &m1, Matrix<Type1> &m2){
        if(m1.numberOfRows != m2.numberOfRows || m1.numberOfColumns != m2.numberOfColumns)
            throw "Matrice nisu pogodne za sabiranje";
        //Vrijednosti i pozicije iz liste pushamo u vektor;
        Vector<Type1> elements;
        for(auto it = m1.matrix.Begin(); it != m1.matrix.End(); it++){
            for(auto it2 = (*it).Begin(); it2 != (*it).End(); it2++){
                elements.push_back(std::make_pair(std::make_pair(it.getPosition(), it2.getPosition()), *it2));
            }
        }
        for(auto it = m2.matrix.Begin(); it != m2.matrix.End(); it++){
            for(auto it2 = (*it).Begin(); it2 != (*it).End(); it2++){
                elements.push_back(std::make_pair(std::make_pair(it.getPosition(), it2.getPosition()), *it2));
            }
        }
        std::sort(elements.begin(), elements.end());

        for(int i = 0; i < elements.size()-1; i++){
            if(elements[i].first.first == elements[i+1].first.first && elements[i].first.second == elements[i+1].first.second){
                elements[i].second += elements[i+1].second;
                elements.erase(elements.begin() + i+1);
            }
        }
        Matrix<Type1>* result = new Matrix<Type1>(m1.numberOfRows, m1.numberOfColumns, elements);
        //std::cout << m1.numberOfRows << m1.numberOfColumns;
        return *result;

}
template <typename Type1, typename Type2>
    Matrix<Type1>& operator^(Matrix<Type1> &m1, Type2 number){
        for(auto it = m1.matrix.Begin(); it != m1.matrix.End(); it++){
            for(auto it2 = (*it).Begin(); it2 != (*it).End(); it2++){
                (*it2) *= number;
            }
        }
        return m1;
    }


template <typename Type>
    Matrix<Type>& Matrix<Type>::transpose(){
        Vector<Type> elements;
        for(auto it = matrix.Begin(); it != matrix.End(); it++){
            for(auto it2 = (*it).Begin(); it2 != (*it).End(); it2++){
                elements.push_back(std::make_pair(std::make_pair(it2.getPosition(), it.getPosition()), *it2));
            }
        }
        Matrix<Type>* result = new Matrix<Type>(numberOfColumns, numberOfRows, elements);
        return *result;
}
template <typename Type1>
    Matrix<Type1>& operator^(Matrix<Type1> &m1, Matrix<Type1> &m2){
        Matrix<Type1> pom;
        pom = m2.transpose();
        Vector<Type1> elements;
        auto it = m1.matrix.Begin();
        while(it != m1.matrix.End()){
            for(auto it2 = pom.matrix.Begin(); it2 != pom.matrix.End(); it2++){
                auto it4 = (*it2).Begin();
                auto it3 = (*it).Begin();
                double result = 0;
                while(it3 != (*it).End() && it4 != (*it2).End()){
                    if(it3.getPosition() < it4.getPosition()){
                        it3++;
                    }
                    else if(it4.getPosition() < it3.getPosition()){
                        it4++;
                    }
                    else{
                        result += ((*it3) * (*it4));
                        it3++;
                        it4++;
                    }
                }
                //Ako rezultat nije defaultna vrijednost za tip(tj. 0), smjestamo u vektor;
                if(result != 0){
                    //std::cout << result << " " << it.getPosition() << " "<< it2.getPosition()<<std::endl;
                    elements.push_back(std::make_pair(std::make_pair(it.getPosition(), it2.getPosition()), result));
                }

            }
            //Ako smo dosli do kraja prelazimo u sljedeci red prve matrice
            it++;
        }
        Matrix<Type1>*res = new Matrix<Type1>(m1.numberOfRows, m2.numberOfColumns, elements);
        return *res;
    }

template <typename Type>
Matrix<Type>& Matrix<Type>::exponentiate(int n){
    if(n < 0) throw "Stepen mora biti pozitivan";
    if (n == 0){
        for(auto it = matrix.Begin(); it != matrix.End(); it++){
            for(auto  it2 = (*it).Begin(); it2 != (*it).End(); it2++){
                *it = 1;
            }
        }
    }
    if(n == 1){
        return *this;
    }
    if(n%2 == 0){
        Matrix<Type> result = (*this).exponentiate(n/2);
        return result ^ result;
    }
    else{
       Matrix<Type> result = (*this).exponentiate((n-1)/2);
        return (*this) ^ result ^ result;
    }
}


#endif // MATRIX_CPP
