//
// Created by Роман Алексеев on 09.03.2024.
//


#pragma once

#include <functional>
#include "Double.h"
#include "Matrix.h"
#include "Polynomial.h"
#include "Rational.h"
#include "SolveSystem.h"

//template<typename T>
class FunctionApproximation {
public:
    template<typename T>
    static Polynomial<T>    //Метод наименьших квадратов
    leastSquareApproximation(unsigned int degree, const std::vector<T> &x, const std::vector<T> &y,
                             const std::vector<T> *p = nullptr) {
        ++degree;   //Увеличиваю степень на 1 для удобства вычислений
        Matrix<T> A(degree, degree);    //Создаю будущую матрицу системы А
        Matrix<T> B(degree, 1);         //Создаю будущий вектор неоднородности B
        for (int i = 0; i < degree; ++i) {
            for (int j = i; j < degree; ++j) {
                T sum = 0;
                for (int k = 0; k < x.size(); ++k) {    //Подсчёт скалярных произведений
                    T a = T::pow(x[k], i + j);          //для матрицы A
                    if (p != nullptr) {
                        a *= (*p)[k];      //Учет веса, если таковой имеется
                    }
                    sum += a;
                }
                A[i][j] = sum;
                if (i != j) {
                    A[j][i] = sum;  //Учёт того, что матрица А симметрическая
                }
            }
        }
        for (int i = 0; i < degree; ++i) {
            T sum = 0;
            for (int k = 0; k < x.size(); ++k) {    //Подсчёт скалярных произведений
                T b = y[k] * T::pow(x[k], i);       //для вектора B
                if (p != nullptr) {
                    b *= (*p)[k];       //Учёт веса, если таковой имеется
                }
                sum += b;
            }
            B[i][0] = sum;
        }
        Matrix<T> X = SolveSystem<T>::squareRootMethod(A, B);   //Решение системы методом
        std::vector<T> v(degree);                               //методом квадратного корня
        for (int i = 0; i < degree; ++i) {
            v[i] = X[i][0];
        }
        return Polynomial(v);
    }

    // Интерполирование многочленом Ньютона на чебышёвских узлах
    template<typename T>
    static Polynomial<T> newtonApproximation(int degree, double a, double b, const std::function<T(T)> &f) {
        int n = degree + 1;
        std::vector<T> chebyshevNodes(n);
        std::vector<std::vector<T>> dividedDifferences(n);
        dividedDifferences[0] = std::vector<T>(n);
        for (int i = 0; i < n; ++i) {   // Вычисление чебышёвских узлов и значений функции в них
            chebyshevNodes[i] = (a + b) / 2 + ((b - a) / 2) * T::cos((M_PI * (2 * i + 1)) / (2 * n));
            dividedDifferences[0][i] = f(chebyshevNodes[i]);
        }
        for (int i = 1; i < n; ++i) {   // Заполнение таблицы разделённых разностей
            dividedDifferences[i] = std::vector<T>(n - i);
            for (int j = 0; j < n - i; ++j) {
                dividedDifferences[i][j] = (dividedDifferences[i - 1][j] - dividedDifferences[i - 1][j + 1]) /
                                           (chebyshevNodes[j] - chebyshevNodes[j + i]);
            }
        }
        Polynomial<T> result;
        Polynomial<T> factor = {1}; // Множитель (x-x_0)...(x-x_(n-1))
        for (int i = 0; i < n; ++i) {   // Составление итогового многочлена
            result += factor * dividedDifferences[i][0];
            factor = factor * Polynomial<T>({-chebyshevNodes[i], 1});
        }
        return result;
    }

    // Интерполирование многочленом Ньютона на равноотстающих узлах
    template<typename T>
    static Polynomial<T>
    equidistantNewtonApproximation(int degree, double a, double b, const std::function<T(T)> &f, int method = 0) {
        int n = degree + 1;
        double h = (b - a) / degree;
        std::vector<T> equidistantNodes(n);
        std::vector<std::vector<T>> differences(n);
        differences[0] = std::vector<T>(n);
        Polynomial<T> result;
        Polynomial<T> factor = {1};
        for (int i = 0; i < n; ++i) {   // Вычисление равноотстающих узлов и значений функции в них
            equidistantNodes[i] = a + h * i;
            differences[0][i] = f(equidistantNodes[i]);
        }
        if (method == 0) {  // Стандартное интерполирование
            for (int i = 1; i < n; ++i) {
                differences[i] = std::vector<T>(n - i);
                for (int j = 0; j < n - i; ++j) {   // Заполнение таблицы разделённых разностей
                    differences[i][j] = (differences[i - 1][j] - differences[i - 1][j + 1]) /
                                        (equidistantNodes[j] - equidistantNodes[j + i]);
                }
            }
            for (int i = 0; i < n; ++i) {   // Составление итогового многочлена
                result += factor * differences[i][0];
                factor = factor * Polynomial<T>({-equidistantNodes[i], 1}); // Множитель (x-x_0)...(x-x_(n-1))
            }
        } else {  // Интерполирование в таблице
            for (int i = 1; i < n; ++i) {
                differences[i] = std::vector<T>(n - i);
                for (int j = 0; j < n - i; ++j) {   // Заполнение таблицы конечных разностей
                    differences[i][j] = differences[i - 1][j + 1] - differences[i - 1][j];
                }
            }
            Double factorial = 1;   // Факториал
            if (method == 1) {  // Интерполирование в начале таблицы
                for (int i = 0; i < n; ++i) {   // Составление итогового многочлена
                    result += (factor * differences[i][0]) / factorial;
                    factor = (factor * Polynomial<T>({-i, 1})); // Множитель x(x-1)...(x-k+1))
                    factorial *= (i + 1);
                }
            } else if (method == 2) {  // Интерполирование в начале таблицы
                for (int i = 0; i < n; ++i) {   // Составление итогового многочлена
                    result += (factor * differences[i][n - i - 1]) / factorial;
                    factor = (factor * Polynomial<T>({i, 1})); // Множитель x(x+1)...(x+k-1)
                    factorial *= (i + 1);
                }
            }
        }
        return result;
    }

    //Поиск среднеквадратичного отклонения
    template<typename T>
    static T standardDeviation(const Polynomial<T> &approximation, const std::vector<T> &x, const std::vector<T> &y) {
        T result = 0;
        for (int i = 0; i < x.size(); ++i) {
            T a = y[i] - approximation.solve(x[i]);
            result += a * a;
        }
        return T::sqrt(result);
    }

private:

};
