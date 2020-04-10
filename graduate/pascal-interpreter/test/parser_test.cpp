//
// Created by pikachu on 2020/4/10.
//

#include <gtest/gtest.h>
#include "parser.h"
#include <vector>
class post_node_visitor: abstract_node_visitor {
public:
    vector<string> expr(ast* node) {
        ret.clear();
        node->accept(this);
        return ret;
    }
private:
    int visit(binary_operator* node) override {
        node->left->accept(this);
        node->right->accept(this);
        ret.push_back(node->op.get_value<string>());
        return 0;
    }

    int visit(number *node) override {
        ret.push_back(to_string(node->value));
        return 0;
    }

    std::vector<string> ret;

};
class pre_node_visitor: abstract_node_visitor {
public:
    vector<string> expr(ast* node) {
        ret.clear();
        node->accept(this);
        return ret;
    }
private:
    int visit(binary_operator* node) override {
        ret.push_back(node->op.get_value<string>());
        node->left->accept(this);
        node->right->accept(this);
        return 0;
    }

    int visit(number *node) override {
        ret.push_back(to_string(node->value));
        return 0;
    }

    std::vector<string> ret;

};

TEST(parser, 1) {
    auto node = parser(lexer("3 + 5")).parse();
    auto expect = new binary_operator {
            new number{token{token_type::integer, "3"}},
            token_constant::plus,
            new number{token{token_type::integer, "5"}},
    };
    ASSERT_TRUE(node);
    auto t = dynamic_cast<binary_operator *>(node);
    ASSERT_EQ(t->op, expect->op);
}
TEST(parser, post_1) {
    auto node = parser(lexer("3 + 5")).parse();
    vector<string> expect = {
            "3", "5", "+"
    };
    ASSERT_EQ(expect, post_node_visitor().expr(node));
}
TEST(parser, post_2) {
    auto node = parser(lexer("(5 + 3) * 12 / 3")).parse();
    vector<string> expect = {
            "5", "3", "+", "12", "*", "3", "/"
    };
    ASSERT_EQ(expect, post_node_visitor().expr(node));
}
TEST(parser, pre_1) {
    auto node = parser(lexer("2 + 3")).parse();
    vector<string> expect = {
            "+", "2", "3"
    };
    ASSERT_EQ(expect, pre_node_visitor().expr(node));
}
TEST(parser, pre_2) {
    auto node = parser(lexer("(2 + 3 * 5) ")).parse();
    vector<string> expect = {
            "+", "2", "*", "3", "5"
    };
    ASSERT_EQ(expect, pre_node_visitor().expr(node));
}