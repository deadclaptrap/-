#ifndef LABMATRIX_MATRIX_H
#define LABMATRIX_MATRIX_H

#include <iostream>
#include <initializer_list>
#include <exception>
#include <vector>
#include "mexcep.h"
using namespace std;

template <typename T>
class Matrix
{
private:
    T** M; // матрица
    int m; // количество строк
    int n; // количество столбцов

public:
    // конструкторы
    Matrix()
    {
        n = m = 0;
        M = nullptr;
    }
    int get_n() const noexcept{
        return n;
    }
    int get_m() const noexcept{
        return m;
    }


    // конструктор с двумя параметрами
    Matrix(int _m, int _n)
    {
        try {
            if (_m < 0 || _n < 0) {
                throw negative();
            }
        }
        catch (negative){
            cout << "check input!" << endl;
            if(_m < 0)
                _m = (-1)*_m;
            if(_n < 0)
                _n = (-1)*_n;
        }

        m = _m;
        n = _n;
        // Выделить память для матрицы
        // Выделить пам'ять для массива указателей
        M = (T**) new T*[m]; // количество строк, количество указателей

        // Выделить память для каждого указателя
        for (int i = 0; i < m; i++)
            M[i] = (T*)new T[n];

        // заполнить массив M нулями
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = 0;
    }
    // конструктор с 1 параметром
    Matrix(int _m)
    {
        try {
            if (_m <= 0) {
                throw negative();
            }
        }
        catch (negative){
            cout << "check input!" << endl;
            _m = (-1)*_m;
        }
        m = _m;
        n = 1;
        M = (T**) new T*[m]; // количество строк, количество указателей
        for (int i = 0; i < m; i++)
            M[i] = (T*)new T[n];

        for (int i = 0; i < m; i++)
            M[i][0] = 0;
    }

   Matrix( initializer_list<vector<T>> lst)
    {
       // cout << "correct";
        int m1 = lst.size();
        int n1;
        for (const auto& l : lst)
        {
            n1 = l.size();
            break;
        }
        // cout << "m: " << m1 << "  n: " << n1 << endl;
        n = n1, m = m1;
        M = (T**) new T*[m]; // количество строк, количество указателей

        // Выделить память для каждого указателя
        for (int i = 0; i < m; i++)
            M[i] = (T*)new T[n];
        int i = 0, j = 0;
        for (const auto& l : lst)
        {
            for (const auto& v : l)
            {
                M[i][j] = v;
                ++j;
            }
            j = 0;
            ++i;
        }
    }

    T** get_M(){
        return M;
    };

    Matrix(Matrix&& Ma) noexcept{
        m = Ma.get_m();
        n = Ma.get_n();
        M = Ma.get_M();
        Ma.n = 0;
        Ma.m = 0;
        Ma.M = nullptr;

    }
    Matrix& operator= (Matrix&& Ma)
    {
        m =Ma.get_m();
        n = Ma.get_n();
        M = Ma.get_M();
        Ma.n = 0;
        Ma.m = 0;
        Ma.M = nullptr;
        return *this;
    }

    template<typename T1>
    Matrix (initializer_list<T1> lst)
    {
        //cout << "used" << endl;
        int m1 = lst.size();

        n = 1, m = m1;
        M = (T **) new T *[m]; // количество строк, количество указателей
        for (int i = 0; i < m; i++)
            M[i] = (T *) new T[n];
        int i = 0, j = 0;
        for (const auto &l: lst) {
            M[i][j] = (T)l;
            ++i;
        }

    }

    friend ostream &operator<< (ostream &, const Matrix<T> &M);

    template<typename T1>
    Matrix( Matrix<T1> &_M)
    {
        //  *this <= _M
        m = _M.get_m();
        n = _M.get_n();
        M = (T**) new T*[m];
        for (int i = 0; i < m; i++)
            M[i] = (T*) new T[n];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = (T)_M(i, j);
    }
    //template<typename T1>
    Matrix( Matrix<T>  & _M)
    {
        //  *this <= _M
        m = _M.get_m();
        n = _M.get_n();
        M = (T**) new T*[m];
        for (int i = 0; i < m; i++)
            M[i] = (T*) new T[n];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = (T)_M(i, j);
    }

    T get_elem(int i, int j) noexcept
    {
        if ((m > 0) && (n > 0))
            return M[i][j];
        else
            return 0;
    }

    void SetMij(int i, int j, T value) noexcept
    {
        if ((i < 0) || (i >= m))
            return;
        if ((j < 0) || (j >= n))
            return;
        M[i][j] = value;
    }



    template <typename T1>
    Matrix& operator+=(Matrix<T1> & M);
    template <typename T1>
    Matrix& operator-=(Matrix<T1> & M);


    friend Matrix<T> operator*(double k, Matrix<T> m1){
        cout << m1;
        int nn = m1.get_n();
        int mm = m1.get_m();
        auto tmp = Matrix<T>(mm, nn);

        for (int i = 0; i<mm; i++) {
            for (int j = 0; j < nn; j++) {
                tmp(i, j) = m1(i, j) * k;
            }
        }
        return tmp;

    }

    template <typename T1>
    Matrix& operator*=(Matrix<T1> & M);// Умножение с присваиванием на матрицу

    Matrix& operator*=(double num);// Умножение с присваиванием на число

    template <typename T1>
    Matrix& operator+(Matrix<T1> & M);//Сумма матриц

    template <typename T1>
    Matrix& operator-(Matrix<T1> & M);

    template<typename T1>
    Matrix operator*(Matrix<T1>  M);

    Matrix operator*(double d);

    Matrix operator= (Matrix<T> & M);

    template<typename T1>
    Matrix<T>(std::initializer_list<std::initializer_list<T1>> init_list);

    template<typename T1>
    Matrix& operator= (Matrix<T1> const& M);


    T& operator()(int row, int col)
    {
        return (M[row][col]);
    }
    const T&  operator()(int row, int col) const
    {
        return (static_cast<const T&>(M[row][col]));
    }


    ~Matrix()
    {
        if (n > 0)
        {
            for (int i = 0; i < m; i++)
                delete[] M[i];
        }
        if (m > 0)
            delete[] M;

    }
};

template<typename T>
ostream &operator<< (ostream &output, Matrix<T> &obj)
{
    int n = obj.get_n();
    int  m = obj.get_m();
    for (int i = 0; i < m; i++)
    {
        cout << "|" << "\t";
        for (int j = 0; j < n; j++)
            cout << obj(i, j) << "\t";
        cout<< "|" << "\t" << endl;
    }
    cout << "---------------------" << endl << endl;
    output << std::endl; // перенос маркера на новую строку
    return output; // позволяет множественный вывод, типа cout << x << y << z << ...
}


template<typename T>
template<typename T1>
Matrix<T>& Matrix<T>::operator*=(Matrix<T1> &Ma) {
    if (m != Ma.get_n() || n != Ma.get_m()) throw SizeEr();
    else {
        m = Ma.get_m();
        auto *tmp = new Matrix<T>(n, Ma.get_n());
        double tmp_res;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                tmp_res = 0;
                for (int k = 0; k < m; k++) {
                    tmp_res += M[i][ k] * Ma(k ,  j);
                }
                tmp->M[i][j] = static_cast<T>(tmp_res);
            }
        }
        //delete[] reinterpret_cast<void*>(M);
        M = tmp->M;
        m = tmp->m;
        n = tmp->n;
        return *this;
    }
}

template<typename T>
Matrix<T> &Matrix<T>::operator*=(double num) {
    for(int i = 0; i<m ;i++){
        for(int j = 0; j < n;j++)
            M[i][j] *= num;
    }
    return *this;
}


template<typename T>
template<typename T1>
Matrix<T>& Matrix<T>::operator=(Matrix<T1> const & Ma) {

    m = Ma.get_m();
    n =  Ma.get_n();
    for (int i = 0; i < m ; i++) {
        for(int j= 0; j < n;j++)
            M[i][j] = static_cast<T>(Ma(i, j));

    }
    return *this;
}

template<typename T>
template<typename T1>
Matrix<T> &Matrix<T>::operator+(Matrix<T1> & Ma) {
    if(m!=Ma.get_m() or n!=Ma.get_n()) throw SizeEr();
    // cout << "in";
    for(int i=0; i<m;i++){
        for(int j=0; j < n; j++)
        {
            M[i][j] = M[i][j]+Ma(i, j);
        }
    }
    return *this;
}


template<typename T>
template<typename T1>
Matrix<T> &Matrix<T>::operator+=( Matrix<T1>  &Matr) {
    if(m!=Matr.get_m() or n!=Matr.get_n()) throw SizeEr();
    for(int i=0; i<m;i++){
        for(int j=0; j < n; j++)
        {
            M[i][j] = M[i][j]+Matr(i, j);
        }
    }

    return *this;
}

template<typename T>
template<typename T1>
Matrix<T> &Matrix<T>::operator-=(  Matrix<T1> &Matr) {
    if(m!=Matr.get_m() or n!=Matr.get_n()) throw SizeEr();


    for(int i=0; i<m;i++){
        for(int j=0; j < n; j++)
        {
            M[i][j] = M[i][j]-Matr(i, j);

        }
    }
    return *this;
}


template<typename T>
template<typename T1>
Matrix<T> &Matrix<T>::operator-(Matrix<T1> & Ma) {
    if(m!=Ma.get_m() or n!=Ma.get_n()) throw SizeEr();
    //cout << "in";
    for(int i=0; i<m;i++){
        for(int j=0; j < n; j++)
        {
            M[i][j] = M[i][j]-Ma(i, j);
        }
    }
    return *this;
}

template<typename T>
template<typename T1>
Matrix<T> Matrix<T>::operator*( Matrix<T1> Ma)   {
    int n1  = Ma.get_n();
    if (m != Ma.get_n()) throw SizeEr();
    else {
        Matrix<T> tmp(m, n1);
        T **M1 = M;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n1; j++) {
                tmp(i, j) = 0;
                for (int k = 0; k < n; k++) {
                    // cout << "f[i][k]: " << M1[i][k] << "   sec[k][i]: " << Ma(k, j)<< endl;
                    tmp(i, j) += M1[i][k] * Ma(k, j);
                }
            }
        return tmp;
    }
}


template<typename T>
template<typename T1>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T1>> init_list) {

    int m1 = init_list.size();
    int n1;
    n1 = init_list.begin()->size();

    // cout << "m: " << m1 << "  n: " << n1 << endl;
    n = n1, m = m1;
   // cout << "m: " << m << "  n: " << n << endl;
    M = (T**) new T*[m]; // количество строк, количество указателей
    // Выделить память для каждого указателя
    for (int i = 0; i < m; i++)
        M[i] = (T*)new T[n];
    int i = 0, j = 0;
    for ( auto& l : init_list)
    {
        for ( auto& v : l)
        {
            M[i][j] = T(static_cast<T>(v));
            ++j;
        }
        j = 0;
        ++i;


    }
}



template<typename T>
Matrix<T> Matrix<T>::operator*(double d) {
    Matrix<T> tmp(m, n);
    T** M1 = M;
    for (int i = 0; i<m; i++)
        for (int j = 0; j< n; j++)
            tmp(i,j) =  d* M1[i][j];
    return tmp;
}

template <typename T>
Matrix<T> Matrix<T>::operator= (Matrix<T>&  Ma){ // x= y
    if (n > 0)
    {
        for (int i = 0; i < m; i++)
            delete[] M[i];
    }

    if (m > 0)
        delete[] M;
    n =Ma.get_n();

    m = Ma.get_m();
    M = (T**) new T*[m]; // количество строк, количество указателей
    //cout << "stad" << endl;
    for (int i = 0; i < m; i++)
        M[i] = (T*) new T[n];
    //cout << "started" << endl;
    for (int i = 0; i<m; i++)
        for (int j = 0; j< n; j++) {
            //  cout << i <<" " << j << endl;
            T val = (T)Ma(i, j);
            SetMij(i, j, val);
        }
    // cout << "here " << endl;
    return *this;

}

#endif //LABMATRIX_MATRIX_H
