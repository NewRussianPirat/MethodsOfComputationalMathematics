//
// Created by Роман Алексеев on 01.10.2023.
//

#include <iostream>
#include "Double.h"
#include "Eigenvalues.h"
#include "FunctionApproximation.h"
#include "Matrix.h"
#include "Polynomial.h"
#include "Rational.h"
#include "SolveNonlinearEquation.h"
#include "SolveSystem.h"

int main(int argc, char **argv) {
    Double::setDecimal(16);
    std::cout.precision(5);
    Double a = -3;      //Установление левой границы отрезка
    std::vector<Double> x;  //Вектор x
    std::vector<Double> y;  //Вектор значений функции в точках x
    while (a <= 3) {
        x.push_back(a);
        y.push_back(FunctionApproximation<Double>::f(a));
        a += 0.1;
    }
    Polynomial<Double> result1 = FunctionApproximation<Double>::leastSquareApproximation(2, x, y);
    Double d1 = FunctionApproximation<Double>::standardDeviation(result1, x, y);
    Polynomial<Double> result2 = FunctionApproximation<Double>::leastSquareApproximation(4, x, y);
    Double d2 = FunctionApproximation<Double>::standardDeviation(result2, x, y);
    Polynomial<Double> result3 = FunctionApproximation<Double>::leastSquareApproximation(6, x, y);
    Double d3 = FunctionApproximation<Double>::standardDeviation(result3, x, y);
    std::cout << "Q1 = " << result1 << '\n' << "D1 = " << d1 << '\n' << "Q2 = " << result2 << '\n' << "D2 = " << d2
              << '\n' << "Q3 = " << result3 << '\n' << "D3 = " << d3;
    return 0;
}
