//
// Created by Роман Алексеев on 23.12.2021.
//

#include "Rational.h"

void Rational::Normalize() {
    int a = NOD(Chisl, Znam);
    Chisl /= a;
    Znam /= a;
    if (Znam < 0) {
        Chisl = 0 - Chisl;
        Znam = 0 - Znam;
    }
}

int Rational::NOD(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (a && b)
        a > b ? a %= b : b %= a;
    return (a + b);
}

Rational &Rational::operator=(double a) {
    Znam = 1;
    while (a - (int) a != 0) {
        a *= 10;
        Znam *= 10;
    }
    Chisl = (int) a;
    Normalize();
    return *this;
}

Rational &Rational::operator+=(Rational const &R1) {
    Chisl = Chisl * R1.Znam + R1.Chisl * Znam;
    Znam *= R1.Znam;
    Normalize();
    return *this;
}

Rational &Rational::operator+=(int &a) {
    Chisl += a * Znam;
    Normalize();
    return *this;
}

Rational &Rational::operator-=(Rational const &R1) {
    Chisl = Chisl * R1.Znam - R1.Chisl * Znam;
    Znam *= R1.Znam;
    Normalize();
    return *this;
}

Rational &Rational::operator-=(int &a) {
    Chisl -= a * Znam;
    Normalize();
    return *this;
}

Rational &Rational::operator*=(Rational const &R1) {
    Chisl *= R1.Chisl;
    Znam *= R1.Znam;
    Normalize();
    return *this;
}

Rational &Rational::operator*=(int &a) {
    Chisl *= a;
    Normalize();
    return *this;
}

Rational &Rational::operator/=(Rational const &R1) {
    Chisl *= R1.Znam;
    Znam *= R1.Chisl;
    Normalize();
    return *this;
}

Rational &Rational::operator/=(int &a) {
    Znam *= a;
    Normalize();
    return *this;
}

istream &operator>>(istream &is, Rational &R) {
    is >> R.Chisl;
    char ch;
    is >> ch;
    if (ch != '/') {
        is.putback(ch);
        R.Znam = 1;
    } else is >> R.Znam;
    if (R.Znam == 0) throw runtime_error("Знаменатель не может быть равен нулю");
    return is;
}