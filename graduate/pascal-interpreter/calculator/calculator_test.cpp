//
// Created by pikachu on 2020/4/10.
//

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>
#include "calculator.cpp"
TEST_CASE("single number") {
    CHECK(calculator("3").eval() == 3);
}

TEST_CASE("single operator") {
    SECTION("add") {
        CHECK(calculator("3+5").eval() == 8);
        CHECK(calculator("3 + 4").eval() == 7);
        CHECK(calculator("12+3").eval() == 15);
        CHECK(calculator("   12+3").eval() == 15);
    }
    SECTION("minus") {
        CHECK(calculator("3-5").eval() == -2);
        CHECK(calculator("3-15").eval() == -12);
    }
    SECTION("multiplication") {
        CHECK(calculator("3*5").eval() == 15);
        CHECK(calculator("3*15").eval() == 45);

    }
    SECTION("division") {
        CHECK(calculator("15/3").eval() == 5);

    }
}

TEST_CASE("arbitrary") {
    CHECK(calculator("9 - 5 + 3 + 11").eval() == 18);
    CHECK(calculator("9 - 5 * 3 + 11").eval() == 5);
    CHECK(calculator("9 - 5 * 3 + 11 + 15 / 3").eval() == 10);
    CHECK(calculator("9 - 5 * 3 + 11 * 15 / 3").eval() == 49);
    CHECK(calculator("7 - 3 + 2 - 1").eval() == 5);
    CHECK(calculator("7 * 4 / 2 * 3").eval() == 42);
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