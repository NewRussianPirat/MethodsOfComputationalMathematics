//
// Created by Роман Алексеев on 16.12.2023.
//

#include "Double.h"
#include "Matrix.h"
#include "Polynomial.h"
#include "Rational.h"
#include "SolveSystem.h"

#pragma once

template<typename T>
class Eigenvalues {
public:
    static Polynomial<T> danilevskyMethod(Matrix<T> A) {
        int n = A.getN();
        Polynomial<T> result = {1};
        for (int k = n - 2; k > -1; --k) {
            T a1 = A[k + 1][k];
            if (a1 == 0) {
                for (int j = 0; j < k; ++j) {
                    if (A[k + 1][j] != 0) {
                        a1 = A[k + 1][j];
                        std::swap(A[j], A[k]);
                        for (int i = 0; i < n; ++i) {
                            std::swap(A[i][j], A[i][k]);
                        }
                        break;
                    }
                }
                if (a1 == 0) {
                    std::vector<T> v(n - k);
                    for (int i = 0; i < n - k - 1; ++i) {
                        v[i] = ((n - k) % 2 == 0 ? 1 : -1) * A[k + 1][n - 1 - i];
                    }
                    v[n - k - 1] = (n - k - 1) % 2 == 0 ? 1 : -1;
                    n = k + 1;
                    k = n - 1;
                    result = result * Polynomial(v);
                    continue;
                }
            }
            std::vector<T> v = A[k + 1];
            for (int i = 0; i < n; ++i) {
                A[i][k] /= a1;
            }
            for (int j = 0; j < n; ++j) {
                if (j == k) {
                    continue;
                }
                T a2 = A[k + 1][j];
                for (int i = 0; i < n; ++i) {
                    A[i][j] -= A[i][k] * a2;
                }
            }
            for (int j = 0; j < n; ++j) {
                T a3 = 0;
                for (int i = 0; i < n; ++i) {
                    a3 += v[i] * A[i][j];
                }
                A[k][j] = a3;
            }
        }
        std::vector<T> v(n + 1);
        for (int i = 0; i < n; ++i) {
            v[i] = ((n + 1) % 2 == 0 ? 1 : -1) * A[0][n - 1 - i];
        }
        v[n] = n % 2 == 0 ? 1 : -1;
        result = result * Polynomial(v);
        return result;
    }

    static Polynomial<T> krylovMethod(const Matrix<T> &A) {
        int n = A.getN();
        Matrix<T> A1(n, n);
        Matrix<T> c = Matrix<T>::generate(n, 1, -5, 5);
        for (int i = 0; i < n; ++i) {
            A1[i][n - 1] = c[i][0];
        }
        for (int j = n - 2; j > -1; --j) {
            c = A * c;
            for (int i = 0; i < n; ++i) {
                A1[i][j] = c[i][0];
            }
        }
        Matrix<T> B = A * c;
        Matrix<T> X = SolveSystem<T>::singleDivisionScheme(A1, B);
        std::vector<T> result(n + 1);
        for (int i = 0; i < n; ++i) {
            result[i] = ((n + 1) % 2 == 0 ? 1 : -1) * X[n - 1 - i][0];
        }
        result[n] = n % 2 == 0 ? 1 : -1;
        return Polynomial(result);
    }

    static T powerMethod(const Matrix<T> &A, const Double accuracy, Matrix<T> *eigenvector = nullptr) {
        //TODO: Мб добавить что-то кроме поиска максимального значения...
        //TODO: Иногда цикл уходит на бесконечность?
        int n = A.getN();
        Matrix<T> z0 = Matrix<T>::generate(n, 1, -5, 5);
        Matrix<T> zk1 = z0;
        Matrix<T> zk = A * z0;
        std::vector<T> result(n);
        for (int i = 0; i < n; ++i) {
            result[i] = zk[i][0] / zk1[i][0];
        }
        bool stop;
        do {
            stop = true;
            T a = 1 / zk.norm();
            zk1 = a * zk;
            zk = A * zk1;
            for (int i = 0; i < n - 1; ++i) {
                if (T::abs(zk[i][0] / zk1[i][0] - result[i]) > accuracy) {
                    stop = false;
                }
                result[i] = zk[i][0] / zk1[i][0];
            }
        } while (!stop);
        if (eigenvector != nullptr) {
            *eigenvector = zk;
        }
        return zk[0][0] / zk1[0][0];
    }
};
