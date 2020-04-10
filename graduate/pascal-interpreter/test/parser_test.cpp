//
// Created by pikachu on 2020/4/10.
//

#include <gtest/gtest.h>
#include "parser.h"

TEST(parser, 1) {
    auto node = parser(lexer("3 + 5")).parse();
    auto expect = new binary_operator {
            new number{token{token_type::integer, "3"}},
            token_constant::plus,
            new number{token{token_type::integer, "5"}},
    };
    ASSERT_EQ(*expect, node);
}