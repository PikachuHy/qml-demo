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

    int visit(unary_operator *node) override {
        node->value->accept(this);
        ret.push_back(node->op.get_value<string>());
        return 0;
    }

    int visit(noop *node) override {
        ret.emplace_back("noop");
        return 0;
    }

    int visit(compound *node) override {
        for(auto it: node->children) {
            it->accept(this);
        }
        ret.emplace_back("compound");
        return 0;
    }

    int visit(assignment *node) override {
        node->left->accept(this);
        node->right->accept(this);
        ret.emplace_back(":=");
        return 0;
    }

    int visit(variable_node *node) override {
        ret.push_back(node->id.get_value<string>());
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

    int visit(unary_operator *node) override {
        ret.push_back(node->op.get_value<string>());
        node->value->accept(this);
        return 0;
    }
    int visit(number *node) override {
        ret.push_back(to_string(node->value));
        return 0;
    }

    int visit(noop *node) override {
        return 0;
    }

    int visit(compound *node) override {
        return 0;
    }

    int visit(assignment *node) override {
        return 0;
    }

    int visit(variable_node *node) override {
        return 0;
    }

    std::vector<string> ret;

};

TEST(parser, 1) {
    auto node = parser(lexer("3 + 5")).expr();
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
    auto node = parser(lexer("3 + 5")).expr();
    vector<string> expect = {
            "3", "5", "+"
    };
    ASSERT_EQ(expect, post_node_visitor().expr(node));
}
TEST(parser, post_2) {
    auto node = parser(lexer("(5 + 3) * 12 / 3")).expr();
    vector<string> expect = {
            "5", "3", "+", "12", "*", "3", "/"
    };
    ASSERT_EQ(expect, post_node_visitor().expr(node));
}
TEST(parser, pre_1) {
    auto node = parser(lexer("2 + 3")).expr();
    vector<string> expect = {
            "+", "2", "3"
    };
    ASSERT_EQ(expect, pre_node_visitor().expr(node));
}
TEST(parser, pre_2) {
    auto node = parser(lexer("(2 + 3 * 5) ")).expr();
    vector<string> expect = {
            "+", "2", "*", "3", "5"
    };
    ASSERT_EQ(expect, pre_node_visitor().expr(node));
}

TEST(parser, pascal_1) {

    auto code = R"(BEGIN  END.)";
    auto node = parser(lexer(code)).parse();
    vector<string> expect = {
            "noop",
            "compound"
    };

    ASSERT_EQ(expect, post_node_visitor().expr(node));

}

TEST(parser, pascal_2) {

    auto code = R"(
    BEGIN
        number := 2;
        a := number;
        b := 10 * a + 10 * number / 4;
        c := a - - b
    END.)";
    auto node = parser(lexer(code)).parse();
    vector<string> expect = {
            "number", "2", ":=",
            "a", "number", ":=",
            "b",
            "10", "a", "*",
            "10", "number", "*", "4", "/",
            "+", ":=",
            "c", "a", "b", "-", "-", ":=",
            "compound"
    };

    ASSERT_EQ(expect, post_node_visitor().expr(node));

}
TEST(parser, pascal_3) {

    auto code = R"(BEGIN
    BEGIN
        number := 2;
        a := number;
        b := 10 * a + 10 * number / 4;
        c := a - - b
    END;
    x := 11;
END.)";
    auto node = parser(lexer(code)).parse();
    vector<string> expect = {
            "number", "2", ":=",
            "a", "number", ":=",
            "b",
            "10", "a", "*",
            "10", "number", "*", "4", "/",
            "+", ":=",
            "c", "a", "b", "-", "-", ":=",
            "compound",
            "x", "11", ":=", "noop",
            "compound"
    };

    ASSERT_EQ(expect, post_node_visitor().expr(node));

}
TEST(parser, pascal_4) {

    auto code = R"(BEGIN
    BEGIN
        number := 2;
        a := number;
        b := 10 * a + 10 * number DIV 4;
        c := a - - b
    end;
    x := 11;
END.)";
    auto node = parser(lexer(code)).parse();
    vector<string> expect = {
            "number", "2", ":=",
            "a", "number", ":=",
            "b",
            "10", "a", "*",
            "10", "number", "*", "4", "/",
            "+", ":=",
            "c", "a", "b", "-", "-", ":=",
            "compound",
            "x", "11", ":=", "noop",
            "compound"
    };

    ASSERT_EQ(expect, post_node_visitor().expr(node));

}
TEST(parser, pascal_5) {

    auto code = R"(BEGIN
    BEGIN
        number := 2;
        a := number;
        b := 10 * a + 10 * number DIV 4;
        c := a - - b
    END;
    x := 11;
END.)";
    auto node = parser(lexer(code)).parse();
    vector<string> expect = {
            "number", "2", ":=",
            "a", "number", ":=",
            "b",
            "10", "a", "*",
            "10", "number", "*", "4", "/",
            "+", ":=",
            "c", "a", "b", "-", "-", ":=",
            "compound",
            "x", "11", ":=", "noop",
            "compound"
    };

    ASSERT_EQ(expect, post_node_visitor().expr(node));

}
TEST(parser, pascal_6) {

    auto code = R"(BEGIN
    BEGIN
        _number := 2;
        a := number;
        b := 10 * a + 10 * number DIV 4;
        c := a - - b
    END;
    x := 11;
END.)";
    auto node = parser(lexer(code)).parse();
    vector<string> expect = {
            "_number", "2", ":=",
            "a", "number", ":=",
            "b",
            "10", "a", "*",
            "10", "number", "*", "4", "/",
            "+", ":=",
            "c", "a", "b", "-", "-", ":=",
            "compound",
            "x", "11", ":=", "noop",
            "compound"
    };

    ASSERT_EQ(expect, post_node_visitor().expr(node));

}