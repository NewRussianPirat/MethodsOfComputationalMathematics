//
// Created by Роман Алексеев on 23.12.2021.
//

//TODO:Надо бы адаптировать Rational, чтобы работал с методами

#pragma once

#include <iostream>

using namespace std;

class Rational {
public:
    Rational() : Chisl(0), Znam(1) {}

    Rational(int a) : Chisl(a), Znam(1) {}

    explicit Rational(int a, int b) : Chisl(a), Znam(b) {
        if (Znam == 0) {
            cout << "Знаменатель равен 0. Он будет замменён на 1";
            Znam = 1;
        }
        Normalize();
    }

    Rational(double a) {
        Znam = 1;
        while (a - (int) a != 0) {
            a *= 10;
            Znam *= 10;
        }
        Chisl = (int) a;
        Normalize();
    }

    inline Rational &operator=(Rational const &R1);

    inline Rational &operator=(int a);

    Rational &operator=(double a);

    Rational &operator+=(Rational const &R1);

    Rational &operator+=(int &a);

    Rational &operator-=(Rational const &R1);

    Rational &operator-=(int &a);

    Rational &operator*=(Rational const &R1);

    Rational &operator*=(int &a);

    Rational &operator/=(Rational const &R1);

    Rational &operator/=(int &a);

    inline Rational &operator++();

    inline Rational const operator++(int);

    inline Rational &operator--();

    inline Rational const operator--(int);

    inline Rational const operator+(Rational const &R1) const;

    inline Rational const operator+(int a) const;

    friend inline Rational const operator+(int a, Rational const &R2);

    inline Rational const operator-(Rational const &R1) const;

    inline Rational const operator-(int a) const;

    friend inline Rational const operator-(int a, Rational const &R2);

    inline Rational const operator*(Rational const &R1) const;

    inline Rational const operator*(int a) const;

    friend inline Rational const operator*(int a, Rational const &R2);

    inline Rational const operator/(Rational const &R1) const;

    inline Rational const operator/(int a) const;

    friend inline Rational const operator/(int a, Rational const &R2);

    friend inline bool const operator<(Rational const &R1, Rational const &R2);

    friend inline bool const operator>(Rational const &R1, Rational const &R2);

    friend inline bool const operator<=(Rational const &R1, Rational const &R2);

    friend inline bool const operator>=(Rational const &R1, Rational const &R2);

    friend inline bool const operator==(Rational const &R1, Rational const &R2);

    friend inline bool const operator!=(Rational const &R1, Rational const &R2);

    friend inline bool const operator<(Rational const &R1, int a);

    friend inline bool const operator>(Rational const &R1, int a);

    friend inline bool const operator<=(Rational const &R1, int a);

    friend inline bool const operator>=(Rational const &R1, int a);

    friend inline bool const operator==(Rational const &R1, int a);

    friend inline bool const operator!=(Rational const &R1, int a);

    friend inline bool const operator<(int a, Rational const &R1);

    friend inline bool const operator>(int a, Rational const &R1);

    friend inline bool const operator<=(int a, Rational const &R1);

    friend inline bool const operator>=(int a, Rational const &R1);

    friend inline bool const operator==(int a, Rational const &R1);

    friend inline bool const operator!=(int a, Rational const &R1);

    friend inline bool const operator<(Rational const &R1, double a);

    friend inline bool const operator>(Rational const &R1, double a);

    friend inline bool const operator<=(Rational const &R1, double a);

    friend inline bool const operator>=(Rational const &R1, double a);

    friend inline bool const operator==(Rational const &R1, double a);

    friend inline bool const operator!=(Rational const &R1, double a);

    friend inline bool const operator<(double a, Rational const &R1);

    friend inline bool const operator>(double a, Rational const &R1);

    friend inline bool const operator<=(double a, Rational const &R1);

    friend inline bool const operator>=(double a, Rational const &R1);

    friend inline bool const operator==(double a, Rational const &R1);

    friend inline bool const operator!=(double a, Rational const &R1);

    friend istream &operator>>(istream &is, Rational &R);

    friend inline ostream &operator<<(ostream &os, Rational const &R);

    inline explicit operator int() const { return Chisl / Znam; };

    inline explicit operator double() const { return (double) Chisl / Znam; };
protected:
    void Normalize();

    static int NOD(int, int);

    int Chisl;
    int Znam;
};

inline Rational &Rational::operator=(Rational const &R1) = default;

inline Rational &Rational::operator=(int a) {
    Chisl = a;
    Znam = 1;
    return *this;
};

inline Rational &Rational::operator++() {
    Chisl += Znam;
    return *this;
}

inline Rational const Rational::operator++(int) {
    Rational r = *this;
    ++*this;
    return r;
}

inline Rational &Rational::operator--() {
    Chisl -= Znam;
    return *this;
}

inline Rational const Rational::operator--(int) {
    Rational r = *this;
    --*this;
    return r;
}

inline Rational const Rational::operator+(Rational const &R1) const {
    return Rational(Chisl * R1.Znam + R1.Chisl * Znam, Znam * R1.Znam);
}

inline const Rational Rational::operator+(int a) const {
    return Rational(Chisl + a * Znam, Znam);
}

inline Rational const operator+(int a, Rational const &R2) {
    return Rational(R2.Chisl + a * R2.Znam, R2.Znam);
}

inline Rational const Rational::operator-(Rational const &R1) const {
    return Rational(Chisl * R1.Znam - R1.Chisl * Znam, Znam * R1.Znam);
}

inline Rational const Rational::operator-(int a) const {
    return Rational(Chisl - a * Znam, Znam);
}

inline Rational const operator-(int a, Rational const &R2) {
    return Rational(a * R2.Znam - R2.Chisl, R2.Znam);
}

inline Rational const Rational::operator*(Rational const &R1) const {
    return Rational(Chisl * R1.Chisl, Znam * R1.Znam);
}

inline Rational const Rational::operator*(int a) const {
    return Rational(Chisl * a, Znam);
}

inline Rational const operator*(int a, Rational const &R2) {
    return Rational(R2.Chisl * a, R2.Znam);
}

inline Rational const Rational::operator/(Rational const &R1) const {
    if (R1 == 0) throw runtime_error("Знаменатель не может быть равен нулю");
    return Rational(Chisl * R1.Znam, Znam * R1.Chisl);
}

inline Rational const Rational::operator/(int a) const {
    if (a == 0) throw runtime_error("Знаменатель не может быть равен нулю");
    return Rational(Chisl, Znam * a);
}

inline Rational const operator/(int a, Rational const &R2) {
    if (R2 == 0) throw runtime_error("Знаменатель не может быть равен нулю");
    return Rational(R2.Znam * a, R2.Chisl);
}

inline bool const operator<(Rational const &R1, Rational const &R2) {
    return R1.Chisl * R2.Znam < R2.Chisl * R1.Znam;
}

inline bool const operator>(Rational const &R1, Rational const &R2) {
    return R1.Chisl * R2.Znam > R2.Chisl * R1.Znam;
}

inline bool const operator<=(Rational const &R1, Rational const &R2) {
    return R1.Chisl * R2.Znam <= R2.Chisl * R1.Znam;
}

inline bool const operator>=(Rational const &R1, Rational const &R2) {
    return R1.Chisl * R2.Znam >= R2.Chisl * R1.Znam;
}

inline bool const operator==(Rational const &R1, Rational const &R2) {
    return R1.Chisl * R2.Znam == R2.Chisl * R1.Znam;
}

inline bool const operator!=(Rational const &R1, Rational const &R2) {
    return R1.Chisl * R2.Znam != R2.Chisl * R1.Znam;
}

inline bool const operator<(Rational const &R1, int a) {
    return R1 < Rational(a);
}

inline bool const operator>(Rational const &R1, int a) {
    return R1 > Rational(a);
}

inline bool const operator<=(Rational const &R1, int a) {
    return R1 <= Rational(a);
}

inline bool const operator>=(Rational const &R1, int a) {
    return R1 >= Rational(a);
}

inline bool const operator==(Rational const &R1, int a) {
    return R1 == Rational(a);
}

inline bool const operator!=(Rational const &R1, int a) {
    return R1 != Rational(a);
}

inline bool const operator<(int a, Rational const &R1) {
    return Rational(a) < R1;
}

inline bool const operator>(int a, Rational const &R1) {
    return Rational(a) > R1;
}

inline bool const operator<=(int a, Rational const &R1) {
    return Rational(a) <= R1;
}

inline bool const operator>=(int a, Rational const &R1) {
    return Rational(a) >= R1;
}

inline bool const operator==(int a, Rational const &R1) {
    return Rational(a) == R1;
}

inline bool const operator!=(int a, Rational const &R1) {
    return Rational(a) != R1;
}

inline bool const operator<(Rational const &R1, double a) {
    return (double) R1 < a;
}

inline bool const operator>(Rational const &R1, double a) {
    return (double) R1 > a;
}

inline bool const operator<=(Rational const &R1, double a) {
    return (double) R1 <= a;
}

inline bool const operator>=(Rational const &R1, double a) {
    return (double) R1 >= a;
}

inline bool const operator==(Rational const &R1, double a) {
    return (double) R1 == a;
}

inline bool const operator!=(Rational const &R1, double a) {
    return (double) R1 != a;
}

inline bool const operator<(double a, Rational const &R1) {
    return a < (double) R1;
}

inline bool const operator>(double a, Rational const &R1) {
    return a > (double) R1;
}

inline bool const operator<=(double a, Rational const &R1) {
    return a <= (double) R1;
}

inline bool const operator>=(double a, Rational const &R1) {
    return a >= (double) R1;
}

inline bool const operator==(double a, Rational const &R1) {
    return a == (double) R1;
}

inline bool const operator!=(double a, Rational const &R1) {
    return a != (double) R1;
}

inline ostream &operator<<(ostream &os, Rational const &R) {
    os << R.Chisl;
    if (R.Znam != 1) os << '/' << R.Znam;
    return os;
}