//
// Created by Роман Алексеев on 05.11.2023.
//

#pragma once

#include <cmath>
#include <iostream>

class Double {
public:
    Double() : value(0.) {}

    Double(double d) {
        value = Double::Round(d);
    }

    Double(int i) {
        value = Double::Round(i);
    }

    virtual ~Double() = default;

    Double(const Double &x) = default;

    Double(Double &&x) = default;

    Double &operator=(const Double &x);

    Double &operator=(double d);

    Double operator+(const Double &d) const;

    Double operator+(double d) const;

    friend Double operator+(double d, const Double &x);

    Double operator-(const Double &d) const;

    Double operator-(double d) const;

    friend Double operator-(double d, const Double &x);

    Double operator*(const Double &d) const;

    Double operator*(double d) const;

    friend Double operator*(double d, const Double &x);

    Double operator/(const Double &d) const;

    Double operator/(double d) const;

    friend Double operator/(double d, const Double &x);

    Double &operator+=(const Double &d);

    Double &operator+=(double d);

    Double &operator-=(const Double &d);

    Double &operator-=(double d);

    Double &operator*=(const Double &d);

    Double &operator*=(double d);

    Double &operator/=(const Double &d);

    Double &operator/=(double d);

    Double operator-() const;

    friend bool operator==(const Double &d1, const Double &d2);

    friend bool operator==(double d, const Double &x);

    friend bool operator==(const Double &x, double d);

    friend bool operator!=(const Double &d1, const Double &d2);

    friend bool operator!=(double d, const Double &x);

    friend bool operator!=(const Double &x, double d);

    friend bool operator>(const Double &d1, const Double &d2);

    friend bool operator>(double d, const Double &x);

    friend bool operator>(const Double &x, double d);

    friend bool operator<(const Double &d1, const Double &d2);

    friend bool operator<(double d, const Double &x);

    friend bool operator<(const Double &x, double d);

    friend bool operator>=(const Double &d1, const Double &d2);

    friend bool operator>=(double d, const Double &x);

    friend bool operator>=(const Double &x, double d);

    friend bool operator<=(const Double &d1, const Double &d2);

    friend bool operator<=(double d, const Double &x);

    friend bool operator<=(const Double &x, double d);

    [[nodiscard]] double getValue() const;

    static Double sqrt(const Double &x);

    static Double pow(const Double &x, const Double &y);

    static Double exp(const Double &x);

    static Double log(const Double &x);

    static Double cos(const Double &x);

    static Double sin(const Double &x);

    static Double abs(const Double &x);

    static Double max(const Double &x, const Double &x1);

    template<typename... Args>
    static Double max(const Double &x, const Args &... args);

    friend std::ostream &operator<<(std::ostream &os, const Double &x);

    static void setDecimal(unsigned int i);

    static unsigned int getDecimal();


private:
    double value;
    static inline unsigned int decimal = 16;
    static inline double round = std::pow(10, 16);

    [[nodiscard]] static double Round(double d) {
        d = std::round(d * round);
        d /= round;
        return std::round(d * round) / round;
    }
};
