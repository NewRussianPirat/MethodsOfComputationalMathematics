//
// Created by Роман Алексеев on 25.02.2024.
//


#pragma once

#include <utility>
#include "Double.h"
#include "Rational.h"

template<typename T>
class SolveNonlinearEquation {
public:
    static void dichotomyMethod(std::pair<T, T> &segment, const T &accuracy) { //Метод дихотомии
        while (T::abs(segment.first - segment.second) > 2 * accuracy) {     //Выполнять, пока не будет достигнута точность
            T x = (segment.first + segment.second) / 2;     //Находим половину отрезка
            if (f(x) * f(segment.first) < 0) {           //Если произведение значений функции на начале и середине < 0
                segment.second = x;                         //Отрезок уменьшается справа
            } else {
                segment.first = x;                          //Иначе слева
            }
        }
    }

    static T methodOfSimpleIteration(const std::pair<T, T> &segment, const T &accuracy) { //Метод простой итерации
        T x0;                      //Начальное приближение, оно же x^k
        T x1 = findX0(segment);    //Следующее приближение, оно же x^k+1, которому сразу же присваивается середина отрезка
        do {
            x0 = x1;               //Обозначение в качестве x^k последнего вычисленного приближения
            x1 = phi(x0);       //Нахождение следующего приближения
        } while (T::abs(x1 - x0) > accuracy);   //Проверка на соблюдение точности, если не выполняется, ищем следующее приближение
        return x1;                 //Возвращаем последнее полученное приближение
    }

    static T newtonMethod(const std::pair<T, T> &segment, const T &accuracy) { //Метод Ньютона
        T x0;                      //Начальное приближение, оно же x^k
        T x1 = findX0(segment);    //Следующее приближение, оно же x^k+1, которому сразу же присваивается середина отрезка
        do {
            x0 = x1;                              //Обозначение в качестве x^k последнего вычисленного приближения
            x1 = x0 - f(x0) / f1(x0);       //Нахождение следующего приближения
        } while (T::abs(x1 - x0) > accuracy);     //Проверка на соблюдение точности, если не выполняется, ищем следующее приближение
        return x1;                 //Возвращаем последнее полученное приближение
    }

    static T stephensenMethod(const std::pair<T, T> &segment, const T &accuracy) { //Метод Стеффенсена
        T x0;                      //Начальное приближение, оно же x^k
        T x1 = findX0(segment);    //Следующее приближение, оно же x^k+1, которому сразу же присваивается середина отрезка
        T v;                       //Переменная, в которой будем хранить значение ?(x^k)
        T vv;                      //Переменная, в которой будем хранить значение ?(?(x^k))
        do {
            x0 = x1;               //Обозначение в качестве x^k последнего вычисленного приближения
            v = phi(x0);        //Вычисление ?(x^k)
            vv = phi(v);        //Вычисление ?(?(x^k))
//            x1 = (x0 * vv - v * v) / (vv - 2 * v + x0);    //Нахождение следующего приближения
            x1 = x0 - ((x0 - v) * (x0 - v)) / (vv - 2 * v + x0); //Эта формула гораздо лучше, погрешность сильно понижается
        } while (T::abs(x1 - x0) > accuracy);              //Проверка на соблюдение точности, если не выполняется, ищем следующее приближение
        return x1;                 //Возвращаем последнее полученное приближение
    }

    static T f(const T &x) {
        return T::pow(2, x) - x * x - 0.5; //Вычисление значения функции f(x)
    }

    static T f1(const T &x) {
        return T::pow(2, x) * T::log(2) - 2 * x; //Вычисление значения функции f'(x)
    }

    static T phi(const T &x) {
        return x - 0.72082 * (T::pow(2, x) - x * x - 0.5); //Вычисление значения функции ?(x)
    }

private:
    static T findX0(const std::pair<T, T> &segment) {
        return (segment.first + segment.second) / 2;
    }
};
