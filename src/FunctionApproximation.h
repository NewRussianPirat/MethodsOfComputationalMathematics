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
    static Polynomial<T>
    rootMeanSquareApproximation(unsigned int degree, const std::vector<T> &x, const std::vector<T> &y,
                                const std::vector<T> *p = nullptr) {
        ++degree;
        Matrix<T> A(degree, degree);
        Matrix<T> B(degree, 1);
        for (int i = 0; i < degree; ++i) {
            for (int j = i; j < degree; ++j) {
                T sum = 0;
                for (int k = 0; k < x.size(); ++k) {
                    T a = T::pow(x[k], i + j);
                    if (p != nullptr) {
                        a *= (*p)[k];
                    }
                    sum += a;
                }
                A[i][j] = sum;
                if (i != j) {
                    A[j][i] = sum;
                }
            }
        }
        for (int i = 0; i < degree; ++i) {
            T sum = 0;
            for (int k = 0; k < x.size(); ++k) {
                T b = y[k] * T::pow(x[k], i);
                if (p != nullptr) {
                    b *= (*p)[k];
                }
                sum += b;
            }
            B[i][0] = sum;
        }
        Matrix<T> X = SolveSystem<T>::squareRootMethod(A, B);
        std::vector<T> v(degree);
        for (int i = 0; i < degree; ++i) {
            v[i] = X[i][0];
        }
        return Polynomial(v);
    }

    static T f(T x) {
        return T::exp(T::cos(x));
    }

private:
};
