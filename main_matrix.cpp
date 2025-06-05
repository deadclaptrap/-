#include <iostream>
#include <exception>
#include "matrix.h"

using namespace std;

int main()
{
    Matrix<int> Mq;
    Mq = Matrix<int>{ 1, 2, 3, 4, 5, 6 };
    cout << Mq;
    Matrix<int> m1(-4);
    Matrix<int> m2(4, 6);
    Matrix<int> m3(m1);
    Matrix<int> m4(std::move(m2));
     Matrix<int> m5 = {{1, 2, 3},
                          {4, 5, 6}};
     Matrix<int> m55 = {{1, 1, 1},
                           {1, 1, 1}};
    Matrix<int> m6 = {{1, 2, 3, 4, 5, 6}};
    Matrix<int> m7 = {1, 2, 3, 4, 5, 6};
    Matrix<int> m8 = {{1},{2},{3},{4},{5},{6}};
    cout << "m8: "<< endl << m8 ;
    cout << "m1: "<< endl << m1 ;
    cout << "m2: "<< endl << m2 ;
    cout << "m3: "<< endl << m3 ;
    cout << "m4: "<< endl << m4 ;
    cout << "m5: "<< endl << m5 ;
    cout << "m6: "<< endl << m6 ;
    cout << "m7: "<< endl << m7 ;
   // cout << m7.get_m() << " " << m7.get_n() << endl;


    Matrix<int> M1, M2, m11, M_sum;
    Matrix<int> M3 (2, 2);
    M3(0, 0) =1;
    M3(0, 1) = 1;
    M3(1, 0) =2;
    M3(1, 1) = 2;
    const Matrix<int> a{1, 1, 1};
    int val= a(0,0);
   cout << "VAL:" << val << endl;


    M1 = m5; // Копирующее присваивание

    cout <<"m5: " << endl<< m5 << "m55: " << endl<<m55;
    cout <<"m5:-m55 " << endl;
    cout << (m5-m55);
    m5-=m55;

   // cout << "m = m5-m55" << endl << m5;
    Matrix<double> m_d = { {1.1, 2}, {3.1, 4}, {5.1, 6} };
// double список инициализации в int матрицу
    Matrix<int> m_i = { {1.1, 2.2, 3.3}, {4.4, 5.5, 6.6} };
    Matrix<int> m_i1 = { {1.1, 2.2}, {3.3, 4.4}, {5.5, 6.6} };
    Matrix<int> m_i2 = { {1.1, 2.2}, {3.3, 4.4}, {5.5, 6.6} };
    Matrix<int> m_i3 = { {1.1, 2.2, 3.3}, {4.4, 5.5, 6.6} };
    Matrix<int> m_i4 = { {1.1, 2.2, 3.3}, {4.4, 5.5, 6.6} };
    Matrix<int> m_i5 = { {1.1, 2.2, 3.3}, {4.4, 5.5, 6.6} };
   // cout << "m_d" << endl << m_d << "m_i" << endl << m_i<< "m_i1" << endl << m_i1;
    m_i1 += m_d;
    cout <<"m_d" << endl <<  m_d << endl;
   //cout << "m_i1 += m_d" << endl <<m_i1  ;
   // cout << m_i1;
    cout << "m_i1 -= m_d" << endl <<(m_d -= m_i2) ;
    m_i3 *= 3.14;
    cout << "m_i  *= 3.14" << endl <<m_i3  ;
    //m_d * m_i;

    Matrix<double> m_sq = { {1.1, 2}, {3.1, 4}};
    Matrix<double> m_sq_i = { {1, 2}, {3, 4}};
    Matrix<double> mlt  = m_sq * m_sq_i;
    cout << mlt;
    try {
        m_sq *= m_i;
        cout << "m_sq*=m_sq;" << endl << m_sq;
    }
    catch ( ...) {
        cout << "Mistake" << endl;
    }

    Matrix<int> M={{1,2,3}, {5, 6, 7}};


    return 0;
}

