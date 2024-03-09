//
// Created by Роман Алексеев on 05.11.2023.
//

#include <gtest/gtest.h>
#include "../src/Double.h"

TEST(DoubleInit, Test1) {
    Double d;
    EXPECT_EQ(d.getValue(), 0.);
}

TEST(DoubleInit, Test2) {
    Double d(1);
    EXPECT_EQ(d.getValue(), 1.);
}

TEST(DoubleInit, Test3) {
    Double::setDecimal(2);
    Double d(3.45567);
    EXPECT_EQ(d.getValue(), 3.46);
}

TEST(DoubleInit, Test4) {
    Double::setDecimal(2);
    Double d(3.45467);
    EXPECT_EQ(d.getValue(), 3.45);
}

TEST(DoubleInit, Test5) {
    Double::setDecimal(16);
    Double d1(2.4354);
    Double d2 = d1;
    EXPECT_EQ(d1.getValue(), d2.getValue());
}

TEST(DoubleInit, Test6) {
    Double d1(2.4354);
    Double d2 = std::move(d1);
    EXPECT_EQ(d1.getValue(), d2.getValue());
}

TEST(DoubleAssignment, Test1) {
    Double d1(2.935824);
    Double d2;
    d2 = d1;
    EXPECT_EQ(d1.getValue(), d2.getValue());
}

TEST(DoubleAssignment, Test2) {
    Double d1(2.935824);
    d1 = 6.54346;
    EXPECT_EQ(d1.getValue(), 6.5434600);
}

TEST(DoubleSum, Test1) {
    Double::setDecimal(4);
    Double d1(2.4323);
    Double d2(14.3245);
    Double d3 = d1 + d2;
    EXPECT_EQ(d3.getValue(), 16.7568);
}

TEST(DoubleSum, Test2) {
    Double::setDecimal(4);
    Double d1(2.4323);
    Double d2(3.5234543);
    Double d3 = d1 + d2;
    EXPECT_EQ(d3.getValue(), 5.9558);
}

TEST(DoubleSum, Test3) {
    Double::setDecimal(4);
    Double d1(2.4323);
    Double d2(14.3245);
    d1 += d2;
    EXPECT_EQ(d1.getValue(), 16.7568);
}

TEST(DoubleSum, Test4) {
    Double::setDecimal(4);
    Double d1(2.4323);
    Double d2(3.5234543);
    d1 += d2;
    EXPECT_EQ(d1.getValue(), 5.9558);
}

TEST(DoubleDiff, Test1) {
    Double::setDecimal(4);
    Double d1(2.4323);
    Double d2(14.3245);
    Double d3 = d1 - d2;
    EXPECT_EQ(d3.getValue(), -11.8922);
}

TEST(DoubleDiff, Test2) {
    Double::setDecimal(4);
    Double d1(2.4323);
    Double d2(3.5234543);
    Double d3 = d1 - d2;
    EXPECT_EQ(d3.getValue(), -1.0912);
}

TEST(DoubleDiff, Test3) {
    Double::setDecimal(4);
    Double d1(2.4323);
    Double d2(14.3245);
    d1 -= d2;
    EXPECT_EQ(d1.getValue(), -11.8922);
}

TEST(DoubleDiff, Test4) {
    Double::setDecimal(4);
    Double d1(2.4323);
    Double d2(3.5234543);
    d1 -= d2;
    EXPECT_EQ(d1.getValue(), -1.0912);
}

TEST(DoubleMult, Test1) {
    Double::setDecimal(4);
    Double d1(2.4323);
    Double d2(14.3245);
    Double d3 = d1 * d2;
    EXPECT_EQ(d3.getValue(), 34.8415);
}

TEST(DoubleMult, Test2) {
    Double::setDecimal(4);
    Double d1(2.4323);
    Double d2(3.5234543);
    Double d3 = d1 * d2;
    EXPECT_EQ(d3.getValue(), 8.5702);
}

TEST(DoubleMult, Test3) {
    Double::setDecimal(4);
    Double d1(2.4323);
    Double d2(14.3245);
    d1 *= d2;
    EXPECT_EQ(d1.getValue(), 34.8415);
}

TEST(DoubleMult, Test4) {
    Double::setDecimal(4);
    Double d1(2.4323);
    Double d2(3.5234543);
    d1 *= d2;
    EXPECT_EQ(d1.getValue(), 8.5702);
}

TEST(DoubleDiv, Test1) {
    Double::setDecimal(4);
    Double d1(2.4323);
    Double d2(14.3245);
    Double d3 = d1 / d2;
    EXPECT_EQ(d3.getValue(), 0.1698);
}

TEST(DoubleDiv, Test2) {
    Double::setDecimal(4);
    Double d1(2.4323);
    Double d2(3.5234543);
    Double d3 = d1 / d2;
    EXPECT_EQ(d3.getValue(), 0.6903);
}

TEST(DoubleDiv, Test3) {
    Double::setDecimal(4);
    Double d1(2.4323);
    Double d2(14.3245);
    d1 /= d2;
    EXPECT_EQ(d1.getValue(), 0.1698);
}

TEST(DoubleDiv, Test4) {
    Double::setDecimal(4);
    Double d1(2.4323);
    Double d2(3.5234543);
    d1 /= d2;
    EXPECT_EQ(d1.getValue(), 0.6903);
}