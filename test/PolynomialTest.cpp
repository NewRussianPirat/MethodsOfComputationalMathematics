//
// Created by Роман Алексеев on 17.12.2023.
//

#include <gtest/gtest.h>
#include "../src/Double.h"
#include "../src/Polynomial.h"

TEST(PolynomialSum, Test1) {
    Double::setDecimal(16);
    Polynomial<Double> polynomial1 = {0, 1};
    Polynomial<Double> polynomial2 = {2, 3, 4};
    Polynomial<Double> polynomial3 = polynomial1 + polynomial2;
    ASSERT_EQ(polynomial3.getPolynomial(), std::vector<Double>({2, 4, 4}));
}

TEST(PolynomialDiff, Test1) {
    Double::setDecimal(16);
    Polynomial<Double> polynomial1 = {0, 1};
    Polynomial<Double> polynomial2 = {2, 3, 4};
    Polynomial<Double> polynomial3 = polynomial1 - polynomial2;
    ASSERT_EQ(polynomial3.getPolynomial(), std::vector<Double>({-2, -2, -4}));
}

TEST(PolynomialMult, Test1) {
    Double::setDecimal(16);
    Polynomial<Double> polynomial1 = {0, 1};
    Polynomial<Double> polynomial2 = {2, 3, 4};
    Polynomial<Double> polynomial3 = polynomial1 * polynomial2;
    ASSERT_EQ(polynomial3.getPolynomial(), std::vector<Double>({0, 2, 3, 4}));
}