//
// Created by Роман Алексеев on 09.03.2024.
//


#pragma once

#include "Double.h"
#include "Matrix.h"
#include "Polynomial.h"
#include "Rational.h"
#include "SolveSystem.h"

template<typename T>
class FunctionApproximation {
public:
    static Polynomial<T>    //Метод наименьших квадратов
    leastSquareApproximation(unsigned int degree, const std::vector<T> &x, const std::vector<T> &y,
                             const std::vector<T> *p = nullptr) {
        ++degree;   //Увеличиваю степень на 1 для удобства вычислений
        Matrix<T> A(degree, degree);    //Создаю будущую матрицу системы А
        Matrix<T> B(degree, 1);         //Создаю будущий вектор неоднородности B
        for (int i = 0; i < degree; ++i) {
            for (int j = i; j < degree; ++j) {
                T sum = 0;
                for (int k = 0; k < x.size(); ++k) {    //Подсчёт скалярных произведений
                    T a = T::pow(x[k], i + j);          //для матрицы A
                    if (p != nullptr) {
                        a *= (*p)[k];      //Учет веса, если таковой имеется
                    }
                    sum += a;
                }
                A[i][j] = sum;
                if (i != j) {
                    A[j][i] = sum;  //Учёт того, что матрица А симметрическая
                }
            }
        }
        for (int i = 0; i < degree; ++i) {
            T sum = 0;
            for (int k = 0; k < x.size(); ++k) {    //Подсчёт скалярных произведений
                T b = y[k] * T::pow(x[k], i);       //для вектора B
                if (p != nullptr) {
                    b *= (*p)[k];       //Учёт веса, если таковой имеется
                }
                sum += b;
            }
            B[i][0] = sum;
        }
        Matrix<T> X = SolveSystem<T>::squareRootMethod(A, B);   //Решение системы методом
        std::vector<T> v(degree);                               //методом квадратного корня
        for (int i = 0; i < degree; ++i) {
            v[i] = X[i][0];
        }
        return Polynomial(v);
    }

    //Поиск среднеквадратичного отклонения
    static T standardDeviation(const Polynomial<T> &approximation, const std::vector<T> &x, const std::vector<T> &y) {
        T result = 0;
        for (int i = 0; i < x.size(); ++i) {
            T a = y[i] - approximation.solve(x[i]);
            result += a * a;
        }
        return T::sqrt(result);
    }

    static T f(T x) {
        return T::exp(T::cos(x)); //Вычисление f(x)
    }

private:
};
