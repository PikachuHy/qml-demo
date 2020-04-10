//
// Created by pikachu on 2020/4/9.
//
#include <gtest/gtest.h>
#include "interpreter.h"
TEST(interpreter, add_1) {
    interpreter inter("3+5");
    ASSERT_EQ(8, inter.interpret());
}
TEST(interpreter, add_2) {
    interpreter inter("12+3");
    ASSERT_EQ(15, inter.interpret());
}
TEST(interpreter, add_3) {
    interpreter inter("   12+3");
    ASSERT_EQ(15, inter.interpret());
}
TEST(interpreter, minus_1) {
    interpreter inter("3-5");
    ASSERT_EQ(-2, inter.interpret());
}
TEST(interpreter, minus_2) {
    interpreter inter("3-15");
    ASSERT_EQ(-12, inter.interpret());
}
TEST(interpreter, multiplication_1) {
    interpreter inter("3*5");
    ASSERT_EQ(15, inter.interpret());
}
TEST(interpreter, multiplication_2) {
    interpreter inter("3*15");
    ASSERT_EQ(45, inter.interpret());
}
TEST(interpreter, division_1) {
    interpreter inter("15/3");
    ASSERT_EQ(5, inter.interpret());
}

TEST(interpreter, arbitrary_1) {
    interpreter inter("9 - 5 + 3 + 11");
    ASSERT_EQ(18, inter.interpret());
}

TEST(interpreter, arbitrary_2) {
    interpreter inter("9 - 5 * 3 + 11");
    ASSERT_EQ(5, inter.interpret());
}
TEST(interpreter, arbitrary_3) {
    interpreter inter("9 - 5 * 3 + 11 + 15 / 3");
    ASSERT_EQ(10, inter.interpret());
}
TEST(interpreter, arbitrary_4) {
    interpreter inter("9 - 5 * 3 + 11 * 15 / 3");
    ASSERT_EQ(49, inter.interpret());
}
TEST(interpreter, arbitrary_5) {
    ASSERT_EQ(3, interpreter("3").interpret());
    ASSERT_EQ(7, interpreter("3 + 4").interpret());
    ASSERT_EQ(5, interpreter("7 - 3 + 2 - 1").interpret());
    ASSERT_EQ(42, interpreter("7 * 4 / 2 * 3").interpret());
}
TEST(interpreter, parentheses_1) {
    ASSERT_EQ(4, interpreter("(3 + 1)").interpret());
    ASSERT_EQ(3, interpreter("12 / (3 + 1)").interpret());
    ASSERT_EQ(2, interpreter("(12 / (3 + 1) - 1)").interpret());
    ASSERT_EQ(22, interpreter("7 + 3 * (10 / (12 / (3 + 1) - 1))").interpret());
}
TEST(interpreter, parentheses_2) {
    ASSERT_EQ(22, interpreter("7 + 3 * (10 / (12 / (3 + 1) - 1))").interpret());
    ASSERT_EQ(10, interpreter("7 + 3 * (10 / (12 / (3 + 1) - 1)) / (2 + 3) - 5 - 3 + (8)").interpret());
    ASSERT_EQ(12, interpreter("7 + (((3 + 2)))").interpret());
}