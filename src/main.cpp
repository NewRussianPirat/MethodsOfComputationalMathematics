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
    Double a = -3;
    std::vector<Double> x;
    std::vector<Double> y;
    while (a <= 3) {
        x.push_back(a);
        y.push_back(FunctionApproximation<Double>::f(a));
        a += 0.1;
    }
    Polynomial<Double> result1 = FunctionApproximation<Double>::rootMeanSquareApproximation(2, x, y);
    Polynomial<Double> result2 = FunctionApproximation<Double>::rootMeanSquareApproximation(4, x, y);
    Polynomial<Double> result3 = FunctionApproximation<Double>::rootMeanSquareApproximation(6, x, y);
    std::cout << result1 << '\n' << result2 << '\n' << result3;
    return 0;
}
