//
// Created by ����� �������� on 25.02.2024.
//


#pragma once

#include <utility>
#include "Double.h"
#include "Rational.h"

template<typename T>
class SolveNonlinearEquation {
public:
    static void dichotomyMethod(std::pair<T, T> &segment, const T &accuracy) { //����� ���������
        while (T::abs(segment.first - segment.second) > 2 * accuracy) {     //���������, ���� �� ����� ���������� ��������
            T x = (segment.first + segment.second) / 2;     //������� �������� �������
            if (f(x) * f(segment.first) < 0) {           //���� ������������ �������� ������� �� ������ � �������� < 0
                segment.second = x;                         //������� ����������� ������
            } else {
                segment.first = x;                          //����� �����
            }
        }
    }

    static T methodOfSimpleIteration(const std::pair<T, T> &segment, const T &accuracy) { //����� ������� ��������
        T x0;                      //��������� �����������, ��� �� x^k
        T x1 = findX0(segment);    //��������� �����������, ��� �� x^k+1, �������� ����� �� ������������� �������� �������
        do {
            x0 = x1;               //����������� � �������� x^k ���������� ������������ �����������
            x1 = phi(x0);       //���������� ���������� �����������
        } while (T::abs(x1 - x0) > accuracy);   //�������� �� ���������� ��������, ���� �� �����������, ���� ��������� �����������
        return x1;                 //���������� ��������� ���������� �����������
    }

    static T newtonMethod(const std::pair<T, T> &segment, const T &accuracy) { //����� �������
        T x0;                      //��������� �����������, ��� �� x^k
        T x1 = findX0(segment);    //��������� �����������, ��� �� x^k+1, �������� ����� �� ������������� �������� �������
        do {
            x0 = x1;                              //����������� � �������� x^k ���������� ������������ �����������
            x1 = x0 - f(x0) / f1(x0);       //���������� ���������� �����������
        } while (T::abs(x1 - x0) > accuracy);     //�������� �� ���������� ��������, ���� �� �����������, ���� ��������� �����������
        return x1;                 //���������� ��������� ���������� �����������
    }

    static T stephensenMethod(const std::pair<T, T> &segment, const T &accuracy) { //����� �����������
        T x0;                      //��������� �����������, ��� �� x^k
        T x1 = findX0(segment);    //��������� �����������, ��� �� x^k+1, �������� ����� �� ������������� �������� �������
        T v;                       //����������, � ������� ����� ������� �������� ?(x^k)
        T vv;                      //����������, � ������� ����� ������� �������� ?(?(x^k))
        do {
            x0 = x1;               //����������� � �������� x^k ���������� ������������ �����������
            v = phi(x0);        //���������� ?(x^k)
            vv = phi(v);        //���������� ?(?(x^k))
//            x1 = (x0 * vv - v * v) / (vv - 2 * v + x0);    //���������� ���������� �����������
            x1 = x0 - ((x0 - v) * (x0 - v)) / (vv - 2 * v + x0); //��� ������� ������� �����, ����������� ������ ����������
        } while (T::abs(x1 - x0) > accuracy);              //�������� �� ���������� ��������, ���� �� �����������, ���� ��������� �����������
        return x1;                 //���������� ��������� ���������� �����������
    }

    static T f(const T &x) {
        return T::pow(2, x) - x * x - 0.5; //���������� �������� ������� f(x)
    }

    static T f1(const T &x) {
        return T::pow(2, x) * T::log(2) - 2 * x; //���������� �������� ������� f'(x)
    }

    static T phi(const T &x) {
        return x - 0.72082 * (T::pow(2, x) - x * x - 0.5); //���������� �������� ������� ?(x)
    }

private:
    static T findX0(const std::pair<T, T> &segment) {
        return (segment.first + segment.second) / 2;
    }
};
