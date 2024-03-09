//
// Created by ����� �������� on 12.11.2023.
//

#include <gtest/gtest.h>
#include "../src/SolveSystem.h"

TEST(SolveSystemSingleDivisionScheme, Test1) {
    Double::setDecimal(2);
    Matrix<Double> A = {{1, 2, 3},
                        {4, 5, 6},
                        {7, 8, 10}};
    Matrix<Double> B = {{1},
                        {1},
                        {1}};
    Matrix<Double> X = {{-1},
                        {1},
                        {0}};
    Matrix<Double> X1 = SolveSystem<Double>::singleDivisionScheme(A, B);
    EXPECT_EQ(X1, X);
}

TEST(SolveSystemSingleDivisionScheme, Test2) {
//    Matrix<Double> A = {{Double(1.50, 2), Double(2.50, 2), Double(3.50, 2)},
//                        {Double(4.50, 2), Double(5.50, 2), Double(6.50, 2)},
//                        {Double(7.50, 2), Double(8.50, 2), Double(10.50, 2)}};
//    Matrix<Double> B = {{Double(1., 2)},
//                        {Double(1., 2)},
//                        {Double(1., 2)}};
//    Matrix<Double> X = {{Double(-1., 2)},
//                        {Double(1., 2)},
//                        {Double(0., 2)}};
//    Matrix<Double> X1(singleDivisionScheme(A, B));
//    /*EXPECT_EQ(X1, X);*/
}

TEST(SolveSystemSingleDivisionScheme, Test3) {
    Matrix<Rational> A = {{1.50, 2.50, 3.50},
                          {4.50, 5.50, 6.50},
                          {7.50, 8.50, 10.50}};
    Matrix<Rational> B = {{1},
                          {1},
                          {1}};
    Matrix<Rational> X = {{-1},
                          {1},
                          {0}};
    Matrix<Rational> X1 = SolveSystem<Rational>::singleDivisionScheme(A, B);
    EXPECT_EQ(X1, X);
}