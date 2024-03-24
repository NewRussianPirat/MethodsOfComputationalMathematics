//
// Created by Роман Алексеев on 05.11.2023.
//

#include "Double.h"

double Double::getValue() const {
    return value;
}

Double &Double::operator=(const Double &x) {
    if (this == &x) {
        return *this;
    }
    value = x.value;
    return *this;
}

Double &Double::operator=(double d) {
    this->value = Double::Round(d);
    return *this;
}

Double Double::operator+(const Double &d) const {
    return {this->value + d.value};
}

Double Double::operator+(double d) const {
    return {this->value + d};
}

Double operator+(double d, const Double &x) {
    return {x.value + d};
}

Double Double::operator-(const Double &d) const {
    return {this->value - d.value};
}

Double Double::operator-(double d) const {
    return {this->value - d};
}

Double operator-(double d, const Double &x) {
    return {x.value - d};
}

Double Double::operator*(const Double &d) const {
    return {this->value * d.value};
}

Double Double::operator*(double d) const {
    return {this->value * d};
}

Double operator*(double d, const Double &x) {
    return {x.value * d};
}

Double Double::operator/(const Double &d) const {
    return {this->value / d.value};
}

Double Double::operator/(double d) const {
    return {this->value / d};
}

Double operator/(double d, const Double &x) {
    return {d / x.value};
}

Double &Double::operator+=(const Double &d) {
    *this = Double(this->value += d.value);
    return *this;
}

Double &Double::operator+=(double d) {
    *this = Double(this->value += d);
    return *this;
}

Double &Double::operator-=(const Double &d) {
    *this = Double(this->value -= d.value);
    return *this;
}

Double &Double::operator-=(double d) {
    *this = Double(this->value -= d);
    return *this;
}

Double &Double::operator*=(const Double &d) {
    *this = Double(this->value *= d.value);
    return *this;
}

Double &Double::operator*=(double d) {
    *this = Double(this->value *= d);
    return *this;
}

Double &Double::operator/=(const Double &d) {
    *this = Double(this->value /= d.value);
    return *this;
}

Double &Double::operator/=(double d) {
    *this = Double(this->value /= d);
    return *this;
}

Double Double::operator-() const {
    return {-this->value};
}

bool operator==(const Double &d1, const Double &d2) {
    return d1.value == d2.value;
}

bool operator==(double d, const Double &x) {
    return d == x.value;
}

bool operator==(const Double &x, double d) {
    return x.value == d;
}

bool operator!=(const Double &d1, const Double &d2) {
    return d1.value != d2.value;
}

bool operator!=(double d, const Double &x) {
    return d != x.value;
}

bool operator!=(const Double &x, double d) {
    return x.value != d;
}

bool operator>(const Double &d1, const Double &d2) {
    return d1.value > d2.value;
}

bool operator>(double d, const Double &x) {
    return d > x.value;
}

bool operator>(const Double &x, double d) {
    return x.value > d;
}

bool operator<(const Double &d1, const Double &d2) {
    return d1.value < d2.value;
}

bool operator<(double d, const Double &x) {
    return d < x.value;
}

bool operator<(const Double &x, double d) {
    return x.value < d;
}

bool operator>=(const Double &d1, const Double &d2) {
    return d1.value >= d2.value;
}

bool operator>=(double d, const Double &x) {
    return d >= x.value;
}

bool operator>=(const Double &x, double d) {
    return x.value >= d;
}

bool operator<=(const Double &d1, const Double &d2) {
    return d1.value <= d2.value;
}

bool operator<=(double d, const Double &x) {
    return d <= x.value;
}

bool operator<=(const Double &x, double d) {
    return x.value <= d;
}

Double Double::sqrt(const Double &x) {
    return {std::sqrt(x.value)};
}

Double Double::pow(const Double &x, const Double &y) {
    return {std::pow(x.value, y.value)};
}

Double Double::exp(const Double &x) {
    return {std::exp(x.value)};
}

Double Double::log(const Double &x) {
    return {std::log(x.value)};
}

Double Double::cos(const Double &x) {
    return {std::cos(x.value)};
}

Double Double::sin(const Double &x) {
    return {std::sin(x.value)};
}

Double Double::abs(const Double &x) {
    return {std::abs(x.value)};
}

Double Double::max(const Double &x, const Double &x1) {
    if (x.value > x1.value) {
        return {x.value};
    } else {
        return {x1.value};
    }
}

template<typename... Args>
Double Double::max(const Double &x, const Args &... args) {
    return max(x, max(args...));
}

std::ostream &operator<<(std::ostream &os, const Double &x) {
    return os << x.getValue();
}

void Double::setDecimal(unsigned int i) {
    Double::decimal = i;
    Double::round = std::pow(10, i);
}

unsigned int Double::getDecimal() {
    return decimal;
}
