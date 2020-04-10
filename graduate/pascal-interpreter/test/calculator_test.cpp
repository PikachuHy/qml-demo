//
// Created by pikachu on 2020/4/10.
//

#include <gtest/gtest.h>
#include "cal1.cpp"

TEST(calculator, add_1) {
    calculator inter("3+5");
    ASSERT_EQ(8, inter.eval());
}
TEST(calculator, add_2) {
    calculator inter("12+3");
    ASSERT_EQ(15, inter.eval());
}
TEST(calculator, add_3) {
    calculator inter("   12+3");
    ASSERT_EQ(15, inter.eval());
}
TEST(calculator, minus_1) {
    calculator inter("3-5");
    ASSERT_EQ(-2, inter.eval());
}
TEST(calculator, minus_2) {
    calculator inter("3-15");
    ASSERT_EQ(-12, inter.eval());
}
TEST(calculator, multiplication_1) {
    calculator inter("3*5");
    ASSERT_EQ(15, inter.eval());
}
TEST(calculator, multiplication_2) {
    calculator inter("3*15");
    ASSERT_EQ(45, inter.eval());
}
TEST(calculator, division_1) {
    calculator inter("15/3");
    ASSERT_EQ(5, inter.eval());
}

TEST(calculator, arbitrary_1) {
    calculator inter("9 - 5 + 3 + 11");
    ASSERT_EQ(18, inter.eval());
}

TEST(calculator, arbitrary_2) {
    calculator inter("9 - 5 * 3 + 11");
    ASSERT_EQ(5, inter.eval());
}
TEST(calculator, arbitrary_3) {
    calculator inter("9 - 5 * 3 + 11 + 15 / 3");
    ASSERT_EQ(10, inter.eval());
}
TEST(calculator, arbitrary_4) {
    calculator inter("9 - 5 * 3 + 11 * 15 / 3");
    ASSERT_EQ(49, inter.eval());
}
TEST(calculator, arbitrary_5) {
    ASSERT_EQ(3, calculator("3").eval());
    ASSERT_EQ(7, calculator("3 + 4").eval());
    ASSERT_EQ(5, calculator("7 - 3 + 2 - 1").eval());
    ASSERT_EQ(42, calculator("7 * 4 / 2 * 3").eval());
}
/*
 * 暂未实现
TEST(calculator, parentheses_1) {
    ASSERT_EQ(4, calculator("(3 + 1)").eval());
    ASSERT_EQ(3, calculator("12 / (3 + 1)").eval());
    ASSERT_EQ(2, calculator("(12 / (3 + 1) - 1)").eval());
    ASSERT_EQ(22, calculator("7 + 3 * (10 / (12 / (3 + 1) - 1))").eval());
}
TEST(calculator, parentheses_2) {
    ASSERT_EQ(22, calculator("7 + 3 * (10 / (12 / (3 + 1) - 1))").eval());
    ASSERT_EQ(10, calculator("7 + 3 * (10 / (12 / (3 + 1) - 1)) / (2 + 3) - 5 - 3 + (8)").eval());
    ASSERT_EQ(12, calculator("7 + (((3 + 2)))").eval());
}
*/