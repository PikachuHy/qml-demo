//
// Created by pikachu on 2020/4/10.
//

#include <gtest/gtest.h>
#include "parser.h"
#include <vector>
class post_node_visitor: node_visitor_adaptor {
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
        ret.push_back(node->num.raw);
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

    int visit(program_node *node) override {
        node->child->accept(this);
        ret.emplace_back("program");
        return 0;
    }

    int visit(block_node *node) override {
        for(auto it: node->children) {
            it->accept(this);
        }
        ret.emplace_back("block");
        return 0;
    }

    int visit(variable_declaration_node *node) override {
        ret.push_back(node->name);
        ret.push_back(node->type);
        ret.emplace_back("var_dec");
        return 0;
    }

    std::vector<string> ret;

    int visit(procedure_node *node) override {
        node->child->accept(this);
        ret.emplace_back("proc_dec");
        return 0;
    }
};
class pre_node_visitor: node_visitor_adaptor {
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
        ret.push_back(node->num.raw);
        return 0;
    }
    std::vector<string> ret;

};

TEST(parser, 1) {
    auto node = parser(lexer("3 + 5")).expr();
    auto expect = new binary_operator {
            new number{token{token_type::integer_const, "3"}},
            token_constant::plus,
            new number{token{token_type::integer_const, "5"}},
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

TEST(parser, pascal_part9_1) {

    auto code = R"(BEGIN  END.)";
    auto node = parser(lexer(code)).parse();
    vector<string> expect = {
            "noop",
            "compound"
    };

    ASSERT_EQ(expect, post_node_visitor().expr(node));

}

TEST(parser, pascal_part9_2) {

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
TEST(parser, pascal_part9_3) {

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
TEST(parser, pascal_part9_4) {

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
            "10", "number", "*", "4", "DIV",
            "+", ":=",
            "c", "a", "b", "-", "-", ":=",
            "compound",
            "x", "11", ":=", "noop",
            "compound"
    };

    ASSERT_EQ(expect, post_node_visitor().expr(node));

}
TEST(parser, pascal_part9_5) {

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
            "10", "number", "*", "4", "DIV",
            "+", ":=",
            "c", "a", "b", "-", "-", ":=",
            "compound",
            "x", "11", ":=", "noop",
            "compound"
    };

    ASSERT_EQ(expect, post_node_visitor().expr(node));

}
TEST(parser, pascal_part9_6) {

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
            "10", "number", "*", "4", "DIV",
            "+", ":=",
            "c", "a", "b", "-", "-", ":=",
            "compound",
            "x", "11", ":=", "noop",
            "compound"
    };

    ASSERT_EQ(expect, post_node_visitor().expr(node));

}


TEST(parser, pascal_part10_1) {

    auto code = R"(
PROGRAM Part10;
VAR
   number     : INTEGER;
   a, b, c, x : INTEGER;
   y          : REAL;

BEGIN {Part10}
   BEGIN
      number := 2;
      a := number;
      b := 10 * a + 10 * number DIV 4;
      c := a - - b
   END;
   x := 11;
   y := 20 / 7 + 3.14;
   { writeln('a = ', a); }
   { writeln('b = ', b); }
   { writeln('c = ', c); }
   { writeln('number = ', number); }
   { writeln('x = ', x); }
   { writeln('y = ', y); }
END.  {Part10}
)";
    auto node = parser(lexer(code)).parse();
    vector<string> expect = {
            "number", "INTEGER", "var_dec",
            "a", "INTEGER", "var_dec",
            "b", "INTEGER", "var_dec",
            "c", "INTEGER", "var_dec",
            "x", "INTEGER", "var_dec",
            "y", "REAL", "var_dec",


            "number", "2", ":=",
            "a", "number", ":=",
            "b",
            "10", "a", "*",
            "10", "number", "*", "4", "DIV",
            "+", ":=",
            "c", "a", "b", "-", "-", ":=",
            "compound",
            "x", "11", ":=",
            "y", "20", "7", "/", "3.14", "+", ":=",
            "noop",
            "compound",
            "block",
            "program"
    };

    ASSERT_EQ(expect, post_node_visitor().expr(node));
    // debug
    int offset = 40;
    vector<string> a;
    auto b = post_node_visitor().expr(node);
    vector<string> c;
    a.insert(a.end(), expect.begin()+offset, expect.end());
    c.insert(c.end(), b.begin()+offset, b.end());
    ASSERT_EQ(a, c);

}

TEST(parser, pascal_part10_2) {

    auto code = R"(
PROGRAM Part10AST;
VAR
   a, b : INTEGER;
   y    : REAL;

BEGIN {Part10AST}
   a := 2;
   b := 10 * a + 10 * a DIV 4;
   y := 20 / 7 + 3.14;
END.  {Part10AST}
)";
    auto node = parser(lexer(code)).parse();
    vector<string> expect = {
            "a", "INTEGER", "var_dec",
            "b", "INTEGER", "var_dec",
            "y", "REAL", "var_dec",

            "a", "2", ":=",
            "b",
            "10", "a", "*",
            "10", "a", "*", "4", "DIV",
            "+", ":=",
            "y", "20", "7", "/", "3.14", "+", ":=",
            "noop",
            "compound",
            "block",
            "program"
    };

    ASSERT_EQ(expect, post_node_visitor().expr(node));

}
TEST(parser, pascal_part10_3) {

    auto code = R"(
PROGRAM Part10AST;
VAR
   a, b : INTEGER;
   y    : REAL;

BEGIN
   a := 2;
   b := 10 * a + 10 * a DIV 4;
   y := 20 / 7 + 3.14;
END.
)";
    auto node = parser(lexer(code)).parse();
    vector<string> expect = {
            "a", "INTEGER", "var_dec",
            "b", "INTEGER", "var_dec",
            "y", "REAL", "var_dec",

            "a", "2", ":=",
            "b",
            "10", "a", "*",
            "10", "a", "*", "4", "DIV",
            "+", ":=",
            "y", "20", "7", "/", "3.14", "+", ":=",
            "noop",
            "compound",
            "block",
            "program"
    };

    ASSERT_EQ(expect, post_node_visitor().expr(node));

}


TEST(parser, pascal_part12_1) {

    auto code = R"(
PROGRAM Part12;
VAR
   a : INTEGER;

PROCEDURE P1;
VAR
   a : REAL;
   k : INTEGER;

   PROCEDURE P2;
   VAR
      a, z : INTEGER;
   BEGIN {P2}
      z := 777;
   END;  {P2}

BEGIN {P1}

END;  {P1}

BEGIN {Part12}
   a := 10;
END.  {Part12}
)";
    auto node = parser(lexer(code)).parse();
    vector<string> expect = {
            "a", "INTEGER", "var_dec",

            "a", "REAL", "var_dec",
            "k", "INTEGER", "var_dec",

            "a", "INTEGER", "var_dec",
            "z", "INTEGER", "var_dec",

            "z", "777", ":=",
            "noop",
            "compound",
            "block",

            "proc_dec",

            "noop",
            "compound",

            "block",

            "proc_dec",

            "a", "10", ":=",
            "noop",
            "compound",
            "block",
            "program"
    };

    ASSERT_EQ(expect, post_node_visitor().expr(node));

}

