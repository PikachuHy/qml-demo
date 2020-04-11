//
// Created by pikachu on 2020/4/10.
//


#include <gtest/gtest.h>
#include "lexer.h"
TEST(lexer, add_1) {
    lexer my_lexer("3+5");
    ASSERT_EQ(token(token_type::integer_const, "3"), my_lexer.get_next_token());
    ASSERT_EQ(token_constant::plus, my_lexer.get_next_token());
    ASSERT_EQ(token(token_type::integer_const, "5"), my_lexer.get_next_token());
}
TEST(lexer, add_2) {
    lexer my_lexer("12+3");
    ASSERT_EQ(token(token_type::integer_const, "12"), my_lexer.get_next_token());
    ASSERT_EQ(token_constant::plus, my_lexer.get_next_token());
    ASSERT_EQ(token(token_type::integer_const, "3"), my_lexer.get_next_token());
}
TEST(lexer, add_3) {
    lexer my_lexer("   12+3");
    ASSERT_EQ(token(token_type::integer_const, "12"), my_lexer.get_next_token());
    ASSERT_EQ(token_constant::plus, my_lexer.get_next_token());
    ASSERT_EQ(token(token_type::integer_const, "3"), my_lexer.get_next_token());
}
TEST(lexer, minus_1) {
    lexer my_lexer("3-5");
    ASSERT_EQ(token(token_type::integer_const, "3"), my_lexer.get_next_token());
    ASSERT_EQ(token_constant::minus, my_lexer.get_next_token());
    ASSERT_EQ(token(token_type::integer_const, "5"), my_lexer.get_next_token());
}
TEST(lexer, minus_2) {
    lexer my_lexer("3-15");
    ASSERT_EQ(token(token_type::integer_const, "3"), my_lexer.get_next_token());
    ASSERT_EQ(token_constant::minus, my_lexer.get_next_token());
    ASSERT_EQ(token(token_type::integer_const, "15"), my_lexer.get_next_token());
}
TEST(lexer, multiplication_1) {
    lexer my_lexer("3*5");
    ASSERT_EQ(token(token_type::integer_const, "3"), my_lexer.get_next_token());
    ASSERT_EQ(token_constant::multiplication, my_lexer.get_next_token());
    ASSERT_EQ(token(token_type::integer_const, "5"), my_lexer.get_next_token());
}
TEST(lexer, multiplication_2) {
    lexer my_lexer("3*15");
    ASSERT_EQ(token(token_type::integer_const, "3"), my_lexer.get_next_token());
    ASSERT_EQ(token_constant::multiplication, my_lexer.get_next_token());
    ASSERT_EQ(token(token_type::integer_const, "15"), my_lexer.get_next_token());
}
TEST(lexer, division_1) {
    lexer my_lexer("15/3");
    ASSERT_EQ(token(token_type::integer_const, "15"), my_lexer.get_next_token());
    ASSERT_EQ(token_constant::integer_division, my_lexer.get_next_token());
    ASSERT_EQ(token(token_type::integer_const, "3"), my_lexer.get_next_token());
}

TEST(lexer, arbitrary_1) {
    lexer my_lexer("9 - 5 + 3 + 11");
    ASSERT_EQ(token(token_type::integer_const, "9"), my_lexer.get_next_token());
    ASSERT_EQ(token_constant::minus, my_lexer.get_next_token());
    ASSERT_EQ(token(token_type::integer_const, "5"), my_lexer.get_next_token());
    ASSERT_EQ(token_constant::plus, my_lexer.get_next_token());
    ASSERT_EQ(token(token_type::integer_const, "3"), my_lexer.get_next_token());
    ASSERT_EQ(token_constant::plus, my_lexer.get_next_token());
    ASSERT_EQ(token(token_type::integer_const, "11"), my_lexer.get_next_token());
}