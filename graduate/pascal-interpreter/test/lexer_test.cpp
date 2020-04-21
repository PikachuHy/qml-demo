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
std::string blank(int n) {
    std::string ret;
    for(int i=0;i<n;i++) ret += ' ';
    return ret;
}
TEST(lexer, pascal) {
    std::string source_code = R"(
program factorial;

function factorial(n: integer): longint;
begin
    if n = 0 then
        factorial := 1
    else
        factorial := n * factorial(n - 1);
end;

var
    n: integer;

begin
    for n := 0 to 16 do
        writeln(n, '! = ', factorial(n));
end.
    )";
    lexer my_lexer(source_code);
    vector<token> tokens = {
            // line 1 program factorial;
            token_constant::program, token(token_type::identifier, "factorial"), token_constant::semicolon,
            // line 2 function factorial(n: integer): longint;
            token_constant::function, token(token_type::identifier, "factorial"),
            token_constant::left_parenthesis, token(token_type::identifier, "n"), token_constant::colon,
            token_constant::integer, token_constant::right_parenthesis,
            token_constant::colon, token_constant::longint,
            token_constant::semicolon,
            // line 3 begin
            token_constant::begin,
            // line 4 if n = 0 then
            token_constant::if_token, token(token_type::identifier, "n"), token_constant::equality,
            token(token_type::integer_const, "0"), token_constant::then_token,
            // line 5 factorial := 1
            token(token_type::identifier, "factorial"), token_constant::assignment,
            token(token_type::integer_const, "1"),
            // line 6 else
            token_constant::else_token,
            // line 7 factorial := n * factorial(n - 1);
            token(token_type::identifier, "factorial"), token_constant::assignment,
            token(token_type::identifier, "n"), token_constant::multiplication,
            token(token_type::identifier, "factorial"), token_constant::left_parenthesis,
            token(token_type::identifier, "n"), token_constant::minus, token(token_type::integer_const, "1"),
            token_constant::right_parenthesis, token_constant::semicolon,
            // line 8 end;
            token_constant::end, token_constant::semicolon,
            // line 9 var
            token_constant::variable,
            // line 10 n: integer;
            token(token_type::identifier, "n"), token_constant::colon,
            token_constant::integer, token_constant::semicolon,
            // line 11 begin
            token_constant::begin,
            // line 12 for n := 0 to 16 do
            token_constant::for_token, token(token_type::identifier, "n"),
            token_constant::assignment, token(token_type::integer_const, "0"),
            token_constant::to_token, token(token_type::integer_const, "16"), token_constant::do_token,
            // line 13 writeln(n, '! = ', factorial(n));
            token(token_type::identifier, "writeln"), token_constant::left_parenthesis,
            token(token_type::identifier, "n"), token_constant::comma,
            token(token_type::string_const, "! = "), token_constant::comma,
            token(token_type::identifier, "factorial"), token_constant::left_parenthesis,
            token(token_type::identifier, "n"), token_constant::right_parenthesis,
            token_constant::right_parenthesis, token_constant::semicolon,
            //line 14 end.
            token_constant::end, token_constant::dot,
    };
    for(auto it: tokens) {
        auto cur_token = my_lexer.get_next_token();
        ASSERT_EQ(it, cur_token)
        << "=======================================" << "\n"
        << cur_token.source_code << "\n"
        << blank(cur_token.col) << "^" << "\n"
        << "where "
        << cur_token.row<<":"<<cur_token.col;
    }
}