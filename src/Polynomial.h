//
// Created by Роман Алексеев on 16.12.2023.
//


#pragma once

#include <vector>
#include "Double.h"
#include "Matrix.h"
#include "Rational.h"

template<typename T>
class Polynomial {
public:
    Polynomial() : polynomial(std::vector<T>()) {}

    explicit Polynomial(int i) : polynomial(std::vector<T>(1, {i})) {}

    Polynomial(std::initializer_list<T> list) : polynomial(list.begin(), list.end()) {}

    Polynomial(const std::vector<T> &polynomial) : polynomial(polynomial) {}

    Polynomial(const Polynomial &polynomial) = default;

    Polynomial(Polynomial &&polynomial) = default;

    virtual ~Polynomial() = default;

    Polynomial &operator+=(const Polynomial &polynomial1) {
        size_t n = std::max(this->polynomial.size(), polynomial1.polynomial.size());
        if (this->polynomial.size() < n) {
            this->polynomial.resize(n);
        }
        for (int i = 0; i < n; ++i) {
            this->polynomial[i] += polynomial1.polynomial[i];
        }
        return *this;
    }

    Polynomial &operator=(const Polynomial &polynomial1) {
        if (this == &polynomial1) {
            return *this;
        }
        this->polynomial = polynomial1.polynomial;
        return *this;
    }

    Polynomial operator+(const Polynomial &polynomial1) const {
        Polynomial result = *this;
        size_t n = std::max(result.polynomial.size(), polynomial1.polynomial.size());
        if (result.polynomial.size() < n) {
            result.polynomial.resize(n);
        }
        for (int i = 0; i < n; ++i) {
            result.polynomial[i] += polynomial1.polynomial[i];
        }
        return result;
    }

    Polynomial operator-(const Polynomial &polynomial1) const {
        Polynomial result = *this;
        size_t n = std::max(result.polynomial.size(), polynomial1.polynomial.size());
        if (result.polynomial.size() < n) {
            result.polynomial.resize(n);
        }
        for (int i = 0; i < n; ++i) {
            result.polynomial[i] -= polynomial1.polynomial[i];
        }
        return result;
    }

    Polynomial operator*(const Polynomial &polynomial1) const {
        size_t m = polynomial1.polynomial.size();
        size_t k = this->polynomial.size();
        size_t n = m + k - 1;
        Polynomial result((std::vector<Double>(n)));
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < m; ++j) {
                result.polynomial[i + j] += this->polynomial[i] * polynomial1.polynomial[j];
            }
        }
        return result;
    }

    friend bool operator==(const Polynomial<T> &polynomial1, const Polynomial<T> &polynomial2) {
        return polynomial1.polynomial == polynomial2.polynomial;
    }

    [[nodiscard]] const std::vector<T> &getPolynomial() const {
        return polynomial;
    };

    T solve(const T &x) {
        T result = 0;
        T a = 1;
        for (const auto &i: this->polynomial) {
            result += a * i;
            a *= x;
        }
        return result;
    };

    friend std::ostream &operator<<(std::ostream &os, const Polynomial<T> &polynomial1) {
        for (int i = polynomial1.polynomial.size() - 1; i > -1; --i) {
            os << polynomial1.polynomial[i] << "x^" << i << " ";
        }
        return os;
    };

    using value_type = T;
private:
    std::vector<T> polynomial;
};