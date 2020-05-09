//
// Created by pikachu on 2020/4/9.
//
#include <gtest/gtest.h>
#include "interpreter.h"
#include <spdlog/spdlog.h>
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
TEST(interpreter, unary_1) {
    ASSERT_EQ(5, interpreter("+ 5").interpret());
    ASSERT_EQ(-5, interpreter("- 5").interpret());
}
TEST(interpreter, unary_2) {
    ASSERT_EQ(2, interpreter("+ 5 + (-3)").interpret());
    ASSERT_EQ(-8, interpreter("- 5 + (-3)").interpret());
}
TEST(interpreter, unary_3) {
    int a =  5 - - - + - 3;
    ASSERT_EQ(8, a);
    ASSERT_EQ(8, interpreter(" 5 - - - + - 3").interpret());
    ASSERT_EQ(10, interpreter("5 - - - + - (3 + 4) - +2").interpret());
}

TEST(interpreter, memory) {
    spdlog::set_pattern("%v");
    string code = R"(
program Main;
var x, y : integer;
begin { Main }
   y := 7;
   x := (y + 3) * 3;
end.  { Main }
)";
    string expect = R"(
ENTER: PROGRAM Main
CALL STACK
1: PROGRAM Main


LEAVE: PROGRAM Main
CALL STACK
1: PROGRAM Main
   y                   : 7
   x                   : 30
)";
    testing::internal::CaptureStdout();
    interpreter(code).interpret();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(expect, output);
}

TEST(interpreter, procedure_execution) {
    spdlog::set_pattern("%v");
    string code = R"(
program Main;

procedure Alpha(a : integer; b : integer);
var x : integer;
begin
   x := (a + b ) * 2;
end;

begin { Main }

   Alpha(3 + 5, 7);  { procedure call }

end.  { Main }
)";
    string expect = R"(

ENTER: PROGRAM Main
CALL STACK
1: PROGRAM Main


ENTER: PROCEDURE Alpha
CALL STACK
2: PROCEDURE Alpha
   a                   : 8
   b                   : 7
1: PROGRAM Main


LEAVE: PROCEDURE Alpha
CALL STACK
2: PROCEDURE Alpha
   a                   : 8
   b                   : 7
   x                   : 30
1: PROGRAM Main


LEAVE: PROGRAM Main
CALL STACK
1: PROGRAM Main
)";
    testing::internal::CaptureStdout();
    interpreter(code, false, true).interpret();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(expect, output);
}
TEST(interpreter, nested_procedure_calls) {
    spdlog::set_pattern("%v");
    string code = R"(
program Main;

procedure Alpha(a : integer; b : integer);
var x : integer;

   procedure Beta(a : integer; b : integer);
   var x : integer;
   begin
      x := a * 10 + b * 2;
   end;

begin
   x := (a + b ) * 2;

   Beta(5, 10);      { procedure call }
end;

begin { Main }

   Alpha(3 + 5, 7);  { procedure call }

end.  { Main }
)";
    string expect = R"(

ENTER: PROGRAM Main
CALL STACK
1: PROGRAM Main


ENTER: PROCEDURE Alpha
CALL STACK
2: PROCEDURE Alpha
   a                   : 8
   b                   : 7
1: PROGRAM Main


ENTER: PROCEDURE Beta
CALL STACK
3: PROCEDURE Beta
   a                   : 5
   b                   : 10
2: PROCEDURE Alpha
   a                   : 8
   b                   : 7
   x                   : 30
1: PROGRAM Main


LEAVE: PROCEDURE Beta
CALL STACK
3: PROCEDURE Beta
   a                   : 5
   b                   : 10
   x                   : 70
2: PROCEDURE Alpha
   a                   : 8
   b                   : 7
   x                   : 30
1: PROGRAM Main


LEAVE: PROCEDURE Alpha
CALL STACK
2: PROCEDURE Alpha
   a                   : 8
   b                   : 7
   x                   : 30
1: PROGRAM Main


LEAVE: PROGRAM Main
CALL STACK
1: PROGRAM Main
)";
    testing::internal::CaptureStdout();
    interpreter(code, false, true).interpret();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(expect, output);
}