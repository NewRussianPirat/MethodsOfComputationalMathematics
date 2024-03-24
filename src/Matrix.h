//
// Created by Роман Алексеев on 01.10.2023.
//

#pragma once

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <type_traits>
#include <vector>
#include "Double.h"
#include "Polynomial.h"
#include "Rational.h"

template<typename T, typename = void>
struct is_Rational : std::false_type {
};

template<typename T>
struct is_Rational<T, std::enable_if_t<std::is_same<T, Rational>::value>> : std::true_type {
};

template<typename T, typename = void>
struct is_Double : std::false_type {
};

template<typename T>
struct is_Double<T, std::enable_if_t<std::is_same<T, Double>::value>> : std::true_type {
};

template<typename T>
class Polynomial;

template<typename T, typename = void>
struct is_Polynomial : std::false_type {
};

template<typename T>
struct is_Polynomial<T, std::enable_if_t<std::is_same<T, Polynomial<typename T::value_type>>::value>> : std::true_type {
};

template<typename T>
class SolveSystem;

template<typename T, typename = std::enable_if_t<
        is_Rational<T>::value || is_Double<T>::value || is_Polynomial<T>::value>>
class Matrix {
public:
    Matrix() : n(0), m(0), matrix(std::vector<std::vector<T>>()) {}

    explicit Matrix(const std::vector<std::vector<T>> &matrix) : n(matrix.size()), m(matrix[0].size()),
                                                                 matrix(matrix) {}

    Matrix(std::initializer_list<std::initializer_list<T>> list) : n(list.size()), m(list.begin()->size()),
                                                                   matrix(list.begin(), list.end()) {}

    Matrix(int n, int m) : n(n), m(m), matrix(std::vector<std::vector<T>>(n, std::vector<T>(m, 0))) {}

    Matrix(const Matrix<T> &matrix1) : n(matrix1.n), m(matrix1.m), matrix(matrix1.matrix) {}

    Matrix(Matrix<T> &&matrix1) noexcept: n(matrix1.n), m(matrix1.m), matrix(matrix1.matrix) {}

    ~Matrix() = default;

    std::vector<T> &operator[](int i) {
        if (i >= this->matrix.size()) {
            throw std::invalid_argument("index is more than matrix size");
        }
        return this->matrix[i];
    }

    Matrix<T> &operator=(const Matrix<T> &matrix1) {
        if (this == &matrix1) {
            return *this;
        }
        this->n = matrix1.n;
        this->m = matrix1.m;
        this->matrix = matrix1.matrix;
        return *this;
    }

    bool operator==(const Matrix<T> &matrix1) const {
        return (std::equal(this->matrix.begin(), this->matrix.end(), matrix1.matrix.begin(), matrix1.matrix.end()));
    }

    Matrix<T> operator+(const Matrix<T> &matrix1) const {
        if (this->n != matrix1.n || this->m != matrix1.m) {
            throw std::invalid_argument("Matrices must to have equal size");
        }
        Matrix<T> result(this->n, this->m);
        for (int i = 0; i < this->n; ++i) {
            for (int j = 0; j < this->m; ++j) {
                result.matrix[i][j] = this->matrix[i][j] + matrix1.matrix[i][j];
            }
        }
        return result;
    }

    Matrix<T> operator-(const Matrix<T> &matrix1) const {
        if (this->n != matrix1.n || this->m != matrix1.m) {
            throw std::invalid_argument("Matrices must to have equal size");
        }
        Matrix<T> result(this->n, this->m);
        for (int i = 0; i < this->n; ++i) {
            for (int j = 0; j < this->m; ++j) {
                result.matrix[i][j] = this->matrix[i][j] - matrix1.matrix[i][j];
            }
        }
        return result;
    }

    Matrix<T> operator*(Matrix<T> matrix1) const {
        if (this->m != matrix1.n) {
            throw std::invalid_argument("Wrong sizes of matrices");
        }
        Matrix<T> result(this->n, matrix1.m);
        for (int i = 0; i < this->n; ++i) {
            for (int j = 0; j < matrix1.m; ++j) {
                for (int k = 0; k < this->m; ++k) {
                    result.matrix[i][j] += this->matrix[i][k] * matrix1.matrix[k][j];
                }
            }
        }
        return result;
    }

    Matrix<T> operator*(const T &a) const {
        Matrix<T> result(this->n, this->m);
        for (int i = 0; i < this->n; ++i) {
            for (int j = 0; j < this->m; ++j) {
                result.matrix[i][j] = this->matrix[i][j] * a;
            }
        }
        return result;
    }

    friend Matrix<T> operator*(const T &a, Matrix<T> &matrix1) {
        Matrix<T> result(matrix1.n, matrix1.m);
        for (int i = 0; i < matrix1.n; ++i) {
            for (int j = 0; j < matrix1.m; ++j) {
                result.matrix[i][j] = matrix1.matrix[i][j] * a;
            }
        }
        return result;
    }

    [[nodiscard]] int getN() const {
        return n;
    }

    [[nodiscard]] int getM() const {
        return m;
    };

    [[nodiscard]] const vector<std::vector<T>> &getMatrix() const {
        return matrix;
    }

    static Matrix<T> generate(int n, int m, double min, double max, bool haveDiagonalDominance = false) {
        if (haveDiagonalDominance && n != m) {
            throw std::invalid_argument("Matrix with diagonal dominance must be square");
        }
        Matrix<T> result(n, m);
        //generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0, 1);
        //generator_end
        double t = dis(gen);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                T a = dis(gen);
                result.matrix[i][j] += T(a);
                if (haveDiagonalDominance) {
                    result.matrix[i][i] += a;
                }
            }
        }
        return result;
    }

    [[nodiscard]] Matrix<T> transpose() const {
        Matrix<T> result(this->m, this->n);
        for (int i = 0; i < this->n; ++i) {
            for (int j = 0; j < this->m; ++j) {
                result.matrix[j][i] = this->matrix[i][j];
            }
        }
        return result;
    }

    Matrix<T> &joinMatrix(Matrix<T> &&matrix1) {
        if (this->n != matrix1.n) {
            throw std::invalid_argument("Number of columns in both matrices must be equal");
        }
        this->m += matrix1.m;
        for (int j = 0; j < matrix1.m; ++j) {
            for (int i = 0; i < matrix1.n; ++i) {
                this->matrix[i].push_back(matrix1.matrix[i][j]);
            }
        }
        return *this;
    }

    [[nodiscard]] Matrix<T> reverse() const {
        Matrix<T> result(n, 0);
        Matrix<T> E(n, 1);
        for (int i = 0; i < this->m; ++i) {
            if (i != 0) {
                E.matrix[i - 1][0] = 0;
            }
            E.matrix[i][0] = 1;
            result.joinMatrix(SolveSystem<T>::singleDivisionScheme(*this, E));
        }
        return result;
    }

    //TODO: Есть сомнения в использовнии...
    [[nodiscard]] T determinant() const {
        if (this->n != this->m) {
            throw std::invalid_argument("Cannot find determinant of non-square matrix");
        }
        if (this->n == 0) {
            return T(0);
        }
        if (this->n == 1) {
            return this->matrix[0][0];
        }
        if (this->n == 2) {
            return this->matrix[0][0] * this->matrix[1][1] - this->matrix[0][1] * this->matrix[1][0];
        }
        T result(0);
        for (int k = 0; k < this->n; ++k) {
            std::vector<std::vector<T>> sub;
            for (int i = 1; i < this->n; ++i) {
                std::vector<T> a;
                for (int j = 0; j < this->n; ++j) {
                    if (j != k) {
                        a.push_back(this->matrix[i][j]);
                    }
                }
                sub.push_back(a);
            }
            Matrix<T> subMatrix(sub);
            T b1 = subMatrix.determinant();
            T b2 = this->matrix[0][k];
            T b3(k % 2 == 0 ? 1 : -1);
            result += b1 * b2 * b3;
        }
        return result;
    }

    //TODO: Оно не работает адекватно, и, возможно, не заработает
    Polynomial<T> characteristicPolynomial() {
        std::vector<std::vector<Polynomial<T>>> sub(this->n, std::vector<Polynomial<T>>(this->n));
        for (int i = 0; i < this->n; ++i) {
            for (int j = 0; j < this->n; ++j) {
                if (i != j) {
                    sub[i][j] = {this->matrix[i][j]};
                } else {
                    sub[i][j] = {this->matrix[i][j], -1};
                }
            }
        }
        Matrix<Polynomial<T>> subMatrix(sub);
        return subMatrix.determinant();
    }

    T norm() {
        T result = 0;
        if (this->m == 1) {
            for (int i = 0; i < this->n; ++i) {
                result += T::abs(this->matrix[i][0]);
            }
        } else {
            T a;
            for (int i = 0; i < this->n; ++i) {
                a = 0;
                for (int j = 0; j < this->m; ++j) {
                    a += T::abs(this->matrix[i][j]);
                }
                result = T::max(result, a);
            }
        }
        return result;
    }

    T condition() {
        T a = this->norm();
        T b = this->reverse().norm();
        return {a + b};
    }

    //TODO: Надо переработать будет мб
    friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix1) {
        std::vector<std::vector<T>> v = matrix1.getMatrix();
        int n = (Double::getDecimal() < 6) ? Double::getDecimal() + 3 : 9;
        for (int i = 0; i < matrix1.getN(); ++i) {
            for (int j = 0; j < matrix1.getM(); ++j) {
                os << std::setw(n) << v[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }

private:
    int n;
    int m;
    std::vector<std::vector<T>> matrix;
};
