//
// Created by ����� �������� on 06.11.2023.
//

#include <gtest/gtest.h>
#include "../src/Matrix.h"

TEST(SquareMatrixInit, Test1) {
    Double::setDecimal(16);
    Matrix<Double> matrix;
    EXPECT_EQ(matrix.getN(), 0);
    EXPECT_EQ(matrix.getM(), 0);
    EXPECT_EQ(matrix.getMatrix(), std::vector<std::vector<Double>>());
}

TEST(SquareMatrixInit, Test2) {
    Double::setDecimal(16);
    std::vector<std::vector<Double>> v = {{1, 2, 3},
                                          {4, 5, 6},
                                          {7, 8, 9}};
    Matrix<Double> matrix(v);
    EXPECT_EQ(matrix.getN(), v.size());
    EXPECT_EQ(matrix.getM(), v[0].size());
    EXPECT_EQ(matrix.getMatrix(), v);
}

TEST(SquareMatrixInit, Test3) {
    Double::setDecimal(16);
    Matrix<Double> matrix = {{1, 2, 3},
                             {4, 5, 6},
                             {7, 8, 9}};
    EXPECT_EQ(matrix.getN(), 3);
    EXPECT_EQ(matrix.getM(), 3);
    EXPECT_EQ(matrix.getMatrix(), std::vector<std::vector<Double>>({{1, 2, 3},
                                                                    {4, 5, 6},
                                                                    {7, 8, 9}}));
}

TEST(SquareMatrixInit, Test4) {
    Double::setDecimal(16);
    Matrix<Double> matrix(2, 2);
    EXPECT_EQ(matrix.getN(), 2);
    EXPECT_EQ(matrix.getM(), 2);
    EXPECT_EQ(matrix.getMatrix(), std::vector<std::vector<Double>>({{0, 0},
                                                                    {0, 0}}));
}

TEST(SquareMatrixInit, Test5) {
    Double::setDecimal(16);
    Matrix<Double> matrix1 = {{1, 2, 3},
                              {4, 5, 6},
                              {7, 8, 9}};
    Matrix<Double> matrix2 = matrix1;
    EXPECT_EQ(matrix1.getN(), matrix2.getN());
    EXPECT_EQ(matrix1.getM(), matrix2.getM());
    EXPECT_EQ(matrix1.getMatrix(), matrix2.getMatrix());
}

TEST(SquareMatrixInit, Test6) {
    Double::setDecimal(16);
    Matrix<Double> matrix1 = {{1, 2, 3},
                              {4, 5, 6},
                              {7, 8, 9}};
    Matrix<Double> matrix2 = std::move(matrix1);
    EXPECT_EQ(matrix1.getN(), matrix2.getN());
    EXPECT_EQ(matrix1.getM(), matrix2.getM());
    EXPECT_EQ(matrix1.getMatrix(), matrix2.getMatrix());
}

TEST(SquareMatrixFunc, Test1) {
    Double::setDecimal(16);
    Matrix<Double> matrix1 = {{1, 2},
                              {3, 4},
                              {5, 6}};
    Matrix<Double> matrix2 = matrix1.transpose();
    EXPECT_EQ(matrix2.getN(), matrix1.getM());
    EXPECT_EQ(matrix2.getM(), matrix1.getN());
    EXPECT_EQ(matrix2.getMatrix(), std::vector<std::vector<Double>>({{1, 3, 5},
                                                                     {2, 4, 6}}));
}

TEST(SquareMatrixFunc, Test2) {
    Double::setDecimal(16);
    Matrix<Double> matrix1 = {{1, 2},
                              {3, 4},
                              {5, 6}};
    Matrix<Double> matrix2 = {{1, 2, 3},
                              {4, 5, 6}};
    Matrix<Double> matrix3 = matrix1 * matrix2;
    EXPECT_EQ(matrix3.getN(), matrix1.getN());
    EXPECT_EQ(matrix3.getM(), matrix2.getM());
    EXPECT_EQ(matrix3.getMatrix(), std::vector<std::vector<Double>>({{9,  12, 15},
                                                                     {19, 26, 33},
                                                                     {29, 40, 51}}));
}

TEST(SquareMatrixFunc, Test3) {
    Double::setDecimal(16);
    Matrix<Double> A = {{1, 2},
                        {3, 4}};
    Matrix<Double> B = {{1, 2},
                        {3, 4}};
    EXPECT_EQ(A, B);
}

TEST(SquareMatrixFunc, Test4) {
    Double::setDecimal(16);
    Matrix<Double> A = {{1, 2, 3, 4},
                        {5, 6, 7, 8},
                        {9, 10, 11, 12},
                        {13, 14, 15, 16}};
    Double determinant = A.determinant();
    EXPECT_EQ(determinant, 0);
}

//TODO: Надо будет починить
TEST(SquareMatrixFunc, Test5) {
//    Double::setDecimal(16);
//    Matrix<Polynomial<Double>> A = {{{3, -1}, {4}, {-3}},
//                            {{4}, {2, -1}, {-7}},
//                            {{1}, {5}, {8, -1}}};
//    Polynomial<Double> determinant = A.determinant();
//    EXPECT_EQ(determinant.getPolynomial(), std::vector<Double>({-57, -68, 13, -1}));
}

TEST(SquareMatrixFunc, Test6) {
//    Double::setDecimal(16);
//    Matrix<Double> A = {{3, 4, -3, 8},
//                        {4, 2, -7, 1},
//                        {1, 5, 8, 6},
//                        {-9, 6, -3, 2}};
//    Polynomial<Double> determinant = A.characteristicPolynomial();
//    EXPECT_EQ(determinant.getPolynomial(), std::vector<Double>({3552, -850, 178, -15, 1}));
}