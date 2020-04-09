//
// Created by pikachu on 2020/4/9.
//
#include <gtest/gtest.h>
#include "interpreter.h"
TEST(interpreter, add_1) {
    interpreter inter("3+5");
    ASSERT_EQ(token(token_type::integer, "3"), inter.get_next_token());
    ASSERT_EQ(token_constant::plus, inter.get_next_token());
    ASSERT_EQ(token(token_type::integer, "5"), inter.get_next_token());
    inter.reset();
    ASSERT_EQ(8, inter.expr());
}
TEST(interpreter, add_2) {
    interpreter inter("12+3");
    ASSERT_EQ(token(token_type::integer, "12"), inter.get_next_token());
    ASSERT_EQ(token_constant::plus, inter.get_next_token());
    ASSERT_EQ(token(token_type::integer, "3"), inter.get_next_token());
    inter.reset();
    ASSERT_EQ(15, inter.expr());
}
TEST(interpreter, add_3) {
    interpreter inter("   12+3");
    ASSERT_EQ(token(token_type::integer, "12"), inter.get_next_token());
    ASSERT_EQ(token_constant::plus, inter.get_next_token());
    ASSERT_EQ(token(token_type::integer, "3"), inter.get_next_token());
    inter.reset();
    ASSERT_EQ(15, inter.expr());
}
TEST(interpreter, minus_1) {
    interpreter inter("3-5");
    ASSERT_EQ(token(token_type::integer, "3"), inter.get_next_token());
    ASSERT_EQ(token_constant::minus, inter.get_next_token());
    ASSERT_EQ(token(token_type::integer, "5"), inter.get_next_token());
    inter.reset();
    ASSERT_EQ(-2, inter.expr());
}
TEST(interpreter, minus_2) {
    interpreter inter("3-15");
    ASSERT_EQ(token(token_type::integer, "3"), inter.get_next_token());
    ASSERT_EQ(token_constant::minus, inter.get_next_token());
    ASSERT_EQ(token(token_type::integer, "15"), inter.get_next_token());
    inter.reset();
    ASSERT_EQ(-12, inter.expr());
}
TEST(interpreter, multiplication_1) {
    interpreter inter("3*5");
    ASSERT_EQ(token(token_type::integer, "3"), inter.get_next_token());
    ASSERT_EQ(token_constant::multiplication, inter.get_next_token());
    ASSERT_EQ(token(token_type::integer, "5"), inter.get_next_token());
    inter.reset();
    ASSERT_EQ(15, inter.expr());
}
TEST(interpreter, multiplication_2) {
    interpreter inter("3*15");
    ASSERT_EQ(token(token_type::integer, "3"), inter.get_next_token());
    ASSERT_EQ(token_constant::multiplication, inter.get_next_token());
    ASSERT_EQ(token(token_type::integer, "15"), inter.get_next_token());
    inter.reset();
    ASSERT_EQ(45, inter.expr());
}
TEST(interpreter, division_1) {
    interpreter inter("15/3");
    ASSERT_EQ(token(token_type::integer, "15"), inter.get_next_token());
    ASSERT_EQ(token_constant::division, inter.get_next_token());
    ASSERT_EQ(token(token_type::integer, "3"), inter.get_next_token());
    inter.reset();
    ASSERT_EQ(5, inter.expr());
}

TEST(interpreter, arbitrary_1) {
    interpreter inter("9 - 5 + 3 + 11");
    ASSERT_EQ(token(token_type::integer, "9"), inter.get_next_token());
    ASSERT_EQ(token_constant::minus, inter.get_next_token());
    ASSERT_EQ(token(token_type::integer, "5"), inter.get_next_token());
    ASSERT_EQ(token_constant::plus, inter.get_next_token());
    ASSERT_EQ(token(token_type::integer, "3"), inter.get_next_token());
    ASSERT_EQ(token_constant::plus, inter.get_next_token());
    ASSERT_EQ(token(token_type::integer, "11"), inter.get_next_token());
    inter.reset();
    ASSERT_EQ(18, inter.expr());
}

TEST(interpreter, arbitrary_2) {
    interpreter inter("9 - 5 * 3 + 11");
    ASSERT_EQ(5, inter.expr());
}
TEST(interpreter, arbitrary_3) {
    interpreter inter("9 - 5 * 3 + 11 + 15 / 3");
    ASSERT_EQ(10, inter.expr());
}
TEST(interpreter, arbitrary_4) {
    interpreter inter("9 - 5 * 3 + 11 * 15 / 3");
    ASSERT_EQ(49, inter.expr());
}
TEST(interpreter, arbitrary_5) {
    ASSERT_EQ(3, interpreter("3").expr());
    ASSERT_EQ(7, interpreter("3 + 4").expr());
    ASSERT_EQ(5, interpreter("7 - 3 + 2 - 1").expr());
    ASSERT_EQ(42, interpreter("7 * 4 / 2 * 3").expr());
}
TEST(interpreter, parentheses_1) {
    ASSERT_EQ(4, interpreter("(3 + 1)").expr());
    ASSERT_EQ(3, interpreter("12 / (3 + 1)").expr());
    ASSERT_EQ(2, interpreter("(12 / (3 + 1) - 1)").expr());
    ASSERT_EQ(22, interpreter("7 + 3 * (10 / (12 / (3 + 1) - 1))").expr());
}