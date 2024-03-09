//
// Created by ????? ???????? on 12.11.2023.
//


#pragma once

#include "Matrix.h"

template<typename T>
class SolveSystem {
public:
    static Matrix<T> singleDivisionScheme(Matrix<T> A, Matrix<T> B, T *determinant = nullptr) {
        if (A.getN() != A.getM()) {
            throw std::invalid_argument("Matrix A is not square");
        }
        if (determinant != nullptr) {
            *determinant = 1;
        }
        int n = A.getN();
        Matrix<T> X(n, 1);
        for (int k = 0; k < n; ++k) {
            T a = A[k][k];
            for (int j = k; j < n; ++j) {
                A[k][j] /= a;
            }
            B[k][0] /= a;
            for (int i = k + 1; i < n; ++i) {
                for (int j = k + 1; j < n; ++j) {
                    A[i][j] -= A[i][k] * A[k][j];
                }
                B[i][0] -= A[i][k] * B[k][0];
                A[i][k] = 0;
            }
            if (determinant != nullptr) {
                *determinant *= a;
            }
        }
        X[n - 1][0] = B[n - 1][0];
        for (int i = n - 2; i > -1; --i) {
            X[i][0] = B[i][0];
            for (int j = i + 1; j < n; ++j) {
                X[i][0] -= A[i][j] * X[j][0];
            }
        }
        return X;
    }

    static Matrix<T> squareRootMethod(Matrix<T> A, Matrix<T> B) {
        if (A.getN() != A.getM()) {
            throw std::invalid_argument("Matrix A is not square");
        }
        int n = A.getN();
        Matrix<T> S(n, n);
        S[0][0] = T::sqrt(A[0][0]);
        for (int j = 1; j < n; ++j) {
            S[0][j] = A[0][j] / S[0][0];
        }
        for (int i = 1; i < n; ++i) {
            T sum = 0;
            for (int k = 0; k < i; ++k) {
                sum += S[k][i] * S[k][i];
            }
            S[i][i] = T::sqrt(A[i][i] - sum);
            for (int j = i + 1; j < n; ++j) {
                sum = 0;
                for (int k = 0; k < i; ++k) {
                    sum += S[k][i] * S[k][j];
                }
                S[i][j] = (A[i][j] - sum) / S[i][i];
            }
        }
        Matrix<T> Y(n, 1);
        Y[0][0] = B[0][0] / S[0][0];
        for (int i = 1; i < n; ++i) {
            T sum = 0;
            for (int k = 0; k < i; ++k) {
                sum += S[k][i] * Y[k][0];
            }
            Y[i][0] = (B[i][0] - sum) / S[i][i];
        }
        Matrix<T> Y1 = SolveSystem<T>::singleDivisionScheme(S.transpose(), B);
        Matrix<T> X(n, 1);
        X[n - 1][0] = Y[n - 1][0] / S[n - 1][n - 1];
        for (int i = n - 2; i > -1; --i) {
            T sum = 0;
            for (int k = i + 1; k < n; ++k) {
                sum += S[i][k] * X[k][0];
            }
            X[i][0] = (Y[i][0] - sum) / S[i][i];
        }
        return X;
    }

    static Matrix<T> rotationMethod(Matrix<T> A, Matrix<T> B) {
        if (A.getN() != A.getM()) {
            throw std::invalid_argument("Matrix A is not square");
        }
        int n = A.getN();
        Matrix<T> X(n, 1);
        T cos;
        T sin;
        T a1;
        T a2;
        T b1;
        T b2;
        T sqrt;
        for (int i = 0; i < n - 1; ++i) {
            for (int k = i + 1; k < n; ++k) {
                a1 = A[i][i];
                a2 = A[k][i];
                sqrt = T::sqrt(a1 * a1 + a2 * a2);
                cos = a1 / sqrt;
                sin = -a2 / sqrt;
                for (int j = i; j < n; ++j) {
                    a1 = A[i][j] * cos - A[k][j] * sin;
                    a2 = A[i][j] * sin + A[k][j] * cos;
                    A[i][j] = a1;
                    A[k][j] = a2;
                }
                b1 = B[i][0] * cos - B[k][0] * sin;
                b2 = B[i][0] * sin + B[k][0] * cos;
                B[i][0] = b1;
                B[k][0] = b2;
            }
        }
        B[n - 1][0] /= A[n - 1][n - 1];
        X[n - 1][0] = B[n - 1][0];
        for (int i = n - 2; i > -1; --i) {
            X[i][0] = B[i][0];
            for (int j = i + 1; j < n; ++j) {
                X[i][0] -= A[i][j] * X[j][0];
            }
            X[i][0] /= A[i][i];
        }
        return X;
    }

    //TODO: ¬ коммах осталс€ метод якоби, что с ним сделать?
    static Matrix<T> methodOfSimpleIteration(Matrix<T> A, Matrix<T> B, const Double accuracy) {
        if (A.getN() != A.getM()) {
            throw std::invalid_argument("Matrix A is not square");
        }
        int n = A.getN();
        Matrix<T> E(n, n);
        for (int i = 0; i < n; ++i) {
            E[i][i] = 1;
        }
        T c = 1. / A.norm();
        A = E - c * A;
        B = c * B;
        Matrix<T> X = Matrix<T>::generate(n, 1, 0, 1);
        Matrix<T> X0(n, 1);
//        Matrix<T> X(n, 1);
//        Matrix<T> X0 = Matrix<T>::generate(n, 1, 0, 1);
//        Matrix<T> X_old = Matrix<T>(n, 1);
        do {
            X0 = X;
            X = A * X0 + B;
        } while ((X - X0).norm() > accuracy);
//        for (int i = 0; i < n; ++i) {
//            for (int j = 0; j < n; ++j) {
//                if (i != j) {
//                    A[i][j] /= -A[i][i];
//                }
//            }
//            B[i][0] /= A[i][i];
//            A[i][i] = 0;
//        }
//        do {
//            for (int i = 0; i < n; ++i) {
//                X[i][0] = 0;
//                for (int j = 0; j < n; ++j) {
//                    if (i != j) {
//                        X[i][0] += A[i][j] * X0[j][0];
//                    }
//                }
//                X[i][0] += B[i][0];
//            }
//            X_old = X0;
//            X0 = X;
//        } while ((X_old - X0).norm() > accuracy);
        return X;
    }

    static Matrix<T> relaxationMethod(Matrix<T> A, Matrix<T> B, const Double accuracy) {
        if (A.getN() != A.getM()) {
            throw std::invalid_argument("Matrix A is not square");
        }
        int n = A.getN();
        Matrix<T> X = Matrix<T>::generate(n, 1, 0, 1);
        Matrix<T> X0;
        Matrix<T> AT = A.transpose();
        A = AT * A;
        B = AT * B;
        Double sum1;
        Double sum2;
        int i = 0;
        //generator for w
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0.0, 2.0);
        //generator_end
        Double w(dis(gen));
        do {
            X0 = X;
            sum1 = 0;
            sum2 = 0;
            for (int j = 0; j < i; ++j) {
                sum1 += A[i][j] * X[j][0];
            }
            for (int j = i + 1; j < n; ++j) {
                sum2 += A[i][j] * X0[j][0];
            }
            X[i][0] = -(w - 1) * X0[i][0] + (w * (B[i][0] - sum1 - sum2)) / A[i][i];
            if (i != n - 1) {
                ++i;
            } else {
                i = 0;
            }
        } while ((X - X0).norm() > accuracy);
        return X;
    }
};