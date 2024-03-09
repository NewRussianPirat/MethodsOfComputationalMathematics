//
// Created by Роман Алексеев on 05.11.2023.
//

#include "Double.h"

double Double::getValue() const {
    return value;
}

Double &Double::operator=(const Double &aDouble) {
    if (this == &aDouble) {
        return *this;
    }
    value = aDouble.value;
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

Double operator+(double d, const Double &aDouble) {
    return {aDouble.value + d};
}

Double Double::operator-(const Double &d) const {
    return {this->value - d.value};
}

Double Double::operator-(double d) const {
    return {this->value - d};
}

Double operator-(double d, const Double &aDouble) {
    return {aDouble.value - d};
}

Double Double::operator*(const Double &d) const {
    return {this->value * d.value};
}

Double Double::operator*(double d) const {
    return {this->value * d};
}

Double operator*(double d, const Double &aDouble) {
    return {aDouble.value * d};
}

Double Double::operator/(const Double &d) const {
    return {this->value / d.value};
}

Double Double::operator/(double d) const {
    return {this->value / d};
}

Double operator/(double d, const Double &aDouble) {
    return {d / aDouble.value};
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

bool operator==(double d, const Double &aDouble) {
    return d == aDouble.value;
}

bool operator==(const Double &aDouble, double d) {
    return aDouble.value == d;
}

bool operator!=(const Double &d1, const Double &d2) {
    return d1.value != d2.value;
}

bool operator!=(double d, const Double &aDouble) {
    return d != aDouble.value;
}

bool operator!=(const Double &aDouble, double d) {
    return aDouble.value != d;
}

bool operator>(const Double &d1, const Double &d2) {
    return d1.value > d2.value;
}

bool operator>(double d, const Double &aDouble) {
    return d > aDouble.value;
}

bool operator>(const Double &aDouble, double d) {
    return aDouble.value > d;
}

bool operator<(const Double &d1, const Double &d2) {
    return d1.value < d2.value;
}

bool operator<(double d, const Double &aDouble) {
    return d < aDouble.value;
}

bool operator<(const Double &aDouble, double d) {
    return aDouble.value < d;
}

bool operator>=(const Double &d1, const Double &d2) {
    return d1.value >= d2.value;
}

bool operator>=(double d, const Double &aDouble) {
    return d >= aDouble.value;
}

bool operator>=(const Double &aDouble, double d) {
    return aDouble.value >= d;
}

bool operator<=(const Double &d1, const Double &d2) {
    return d1.value <= d2.value;
}

bool operator<=(double d, const Double &aDouble) {
    return d <= aDouble.value;
}

bool operator<=(const Double &aDouble, double d) {
    return aDouble.value <= d;
}

Double Double::sqrt(const Double &aDouble) {
    return {std::sqrt(aDouble.value)};
}

Double Double::pow(const Double &aDouble, const Double &x) {
    return {std::pow(aDouble.value, x.value)};
}

Double Double::exp(const Double &aDouble) {
    return {std::exp(aDouble.value)};
}

Double Double::log(const Double &aDouble) {
    return {std::log(aDouble.value)};
}

Double Double::cos(const Double &aDouble) {
    return {std::cos(aDouble.value)};
}

Double Double::sin(const Double &aDouble) {
    return {std::sin(aDouble.value)};
}

Double Double::abs(const Double &aDouble) {
    return {std::abs(aDouble.value)};
}

Double Double::max(const Double &aDouble, const Double &aDouble1) {
    if (aDouble.value > aDouble1.value) {
        return {aDouble.value};
    } else {
        return {aDouble1.value};
    }
}

template<typename... Args>
Double Double::max(const Double &aDouble, const Args &... args) {
    return max(aDouble, max(args...));
}

std::ostream &operator<<(std::ostream &os, const Double &aDouble) {
    return os << aDouble.getValue();
}

void Double::setDecimal(unsigned int i) {
    Double::decimal = i;
    Double::round = std::pow(10, i);
}

unsigned int Double::getDecimal() {
    return decimal;
}
