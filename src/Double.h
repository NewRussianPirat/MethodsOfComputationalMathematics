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
        if (decimal == 16) {
            value = d;
        } else {
            value = Double::Round(d);
        }
    }

    Double(int i) {
        if (decimal == 16) {
            value = i;
        } else {
            value = Double::Round(i);
        }
    }

    virtual ~Double() = default;

    Double(const Double &aDouble) = default;

    Double(Double &&aDouble) = default;

    Double &operator=(const Double &aDouble);

    Double &operator=(double d);

    Double operator+(const Double &d) const;

    Double operator+(double d) const;

    friend Double operator+(double d, const Double &aDouble);

    Double operator-(const Double &d) const;

    Double operator-(double d) const;

    friend Double operator-(double d, const Double &aDouble);

    Double operator*(const Double &d) const;

    Double operator*(double d) const;

    friend Double operator*(double d, const Double &aDouble);

    Double operator/(const Double &d) const;

    Double operator/(double d) const;

    friend Double operator/(double d, const Double &aDouble);

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

    friend bool operator==(double d, const Double &aDouble);

    friend bool operator==(const Double &aDouble, double d);

    friend bool operator!=(const Double &d1, const Double &d2);

    friend bool operator!=(double d, const Double &aDouble);

    friend bool operator!=(const Double &aDouble, double d);

    friend bool operator>(const Double &d1, const Double &d2);

    friend bool operator>(double d, const Double &aDouble);

    friend bool operator>(const Double &aDouble, double d);

    friend bool operator<(const Double &d1, const Double &d2);

    friend bool operator<(double d, const Double &aDouble);

    friend bool operator<(const Double &aDouble, double d);

    friend bool operator>=(const Double &d1, const Double &d2);

    friend bool operator>=(double d, const Double &aDouble);

    friend bool operator>=(const Double &aDouble, double d);

    friend bool operator<=(const Double &d1, const Double &d2);

    friend bool operator<=(double d, const Double &aDouble);

    friend bool operator<=(const Double &aDouble, double d);

    [[nodiscard]] double getValue() const;

    static Double sqrt(const Double &aDouble);

    static Double pow(const Double &aDouble, const Double &x);

    static Double exp(const Double &aDouble);

    static Double log(const Double &aDouble);

    static Double cos(const Double &aDouble);

    static Double sin(const Double &aDouble);

    static Double abs(const Double &aDouble);

    static Double max(const Double &aDouble, const Double &aDouble1);

    template<typename... Args>
    static Double max(const Double &aDouble, const Args &... args);

    friend std::ostream &operator<<(std::ostream &os, const Double &aDouble);

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
