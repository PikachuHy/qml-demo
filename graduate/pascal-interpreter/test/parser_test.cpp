//
// Created by pikachu on 2020/4/10.
//

#include <gtest/gtest.h>
#include "parser.h"
#include <vector>
string string_join(const vector<string>& vec, string seg) {
    string ret;
    for(const auto& it: vec) {
        ret += it;
        ret += seg;
    }
    return ret;
}
class post_node_visitor: public node_visitor_adaptor {
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
        std::cout << node->op.raw << std::endl;
        return 0;
    }

    int visit(number *node) override {
        std::cout << node->num.raw << std::endl;
        return 0;
    }

    int visit(unary_operator *node) override {
        node->value->accept(this);
        std::cout << node->op.raw << std::endl;
        return 0;
    }

    int visit(noop *node) override {
        std::cout << "noop" << std::endl;
        return 0;
    }

    int visit(compound *node) override {
        for(auto it: node->children) {
            it->accept(this);
        }
        std::cout << "compound" << std::endl;
        return 0;
    }

    int visit(assignment *node) override {
        node->left->accept(this);
        node->right->accept(this);
        std::cout << ":=" << std::endl;
        return 0;
    }

    int visit(variable_node *node) override {
        std::cout << node->id.raw << std::endl;
        return 0;
    }

    int visit(program_node *node) override {
        node->child->accept(this);
        std::cout << "program" << std::endl;
        return 0;
    }

    int visit(block_node *node) override {
        for(auto it: node->children) {
            it->accept(this);
        }
        std::cout << "block" << std::endl;
        return 0;
    }

    int visit(variable_declaration_node *node) override {
        std::cout << node->get_name() << std::endl;
        std::cout << node->get_type() << std::endl;
        std::cout << "var dec" << std::endl;
        return 0;
    }

    std::vector<string> ret;

    int visit(procedure_node *node) override {
        node->child->accept(this);
        std::cout << "proc dec" << std::endl;
        return 0;
    }

    int visit(string_node *node) override {
        std::cout << "string const: " << node->value.raw << std::endl;
        return 0;
    }

    int visit(procedure_call_node *node) override {
        for(auto it: node->params) {
            it->accept(this);
        }
        std::cout << "proc call: " << node->name << std::endl;
        return 0;
    }

    int visit(function_node *node) override {
        for(auto it: node->params) {
            it->accept(this);
        }
        node->ret_type->accept(this);
        node->child->accept(this);
        std::cout << "func dec: " << node->name <<  std::endl;
        return 0;
    }

    int visit(if_node *node) override {
        node->condition->accept(this);
        node->if_block->accept(this);
        node->else_block->accept(this);
        std::cout << "if" << std::endl;
        return 0;
    }

    int visit(bool_expr_node *node) override {
        node->left->accept(this);
        node->right->accept(this);
        std::cout << node->op.raw << std::endl;
        return 0;
    }

    int visit(for_node *node) override {
        node->init->accept(this);
        node->end->accept(this);
        node->block->accept(this);
        std::cout << "for" << std::endl;
        return 0;
    }

    int visit(function_call_node *node) override {

        for(auto it: node->params) {
            it->accept(this);
        }
        std::cout << "func call: " << node->name << std::endl;
        return 0;
    }

    int visit(identifier_node *node) override {
        std::cout << node->value << std::endl;
        return 0;
    }

    int visit(type_node *node) override {
        std::cout << node->value << std::endl;
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
    testing::internal::CaptureStdout();
    post_node_visitor visitor;
    node->accept(&visitor);
    std::string output = testing::internal::GetCapturedStdout();
    auto expect_string = string_join(expect, "\n"s);
    ASSERT_EQ(expect_string, output);
}
TEST(parser, post_2) {
    auto node = parser(lexer("(5 + 3) * 12 / 3")).expr();
    vector<string> expect = {
            "5", "3", "+", "12", "*", "3", "/"
    };
    testing::internal::CaptureStdout();
    post_node_visitor visitor;
    node->accept(&visitor);
    std::string output = testing::internal::GetCapturedStdout();
    auto expect_string = string_join(expect, "\n"s);
    ASSERT_EQ(expect_string, output);
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

    testing::internal::CaptureStdout();
    post_node_visitor visitor;
    node->accept(&visitor);
    std::string output = testing::internal::GetCapturedStdout();
    auto expect_string = string_join(expect, "\n"s);
    ASSERT_EQ(expect_string, output);

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

    testing::internal::CaptureStdout();
    post_node_visitor visitor;
    node->accept(&visitor);
    std::string output = testing::internal::GetCapturedStdout();
    auto expect_string = string_join(expect, "\n"s);
    ASSERT_EQ(expect_string, output);

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

    testing::internal::CaptureStdout();
    post_node_visitor visitor;
    node->accept(&visitor);
    std::string output = testing::internal::GetCapturedStdout();
    auto expect_string = string_join(expect, "\n"s);
    ASSERT_EQ(expect_string, output);

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

    testing::internal::CaptureStdout();
    post_node_visitor visitor;
    node->accept(&visitor);
    std::string output = testing::internal::GetCapturedStdout();
    auto expect_string = string_join(expect, "\n"s);
    ASSERT_EQ(expect_string, output);

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

    testing::internal::CaptureStdout();
    post_node_visitor visitor;
    node->accept(&visitor);
    std::string output = testing::internal::GetCapturedStdout();
    auto expect_string = string_join(expect, "\n"s);
    ASSERT_EQ(expect_string, output);

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

    testing::internal::CaptureStdout();
    post_node_visitor visitor;
    node->accept(&visitor);
    std::string output = testing::internal::GetCapturedStdout();
    auto expect_string = string_join(expect, "\n"s);
    ASSERT_EQ(expect_string, output);

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
            "number", "INTEGER", "var dec",
            "a", "INTEGER", "var dec",
            "b", "INTEGER", "var dec",
            "c", "INTEGER", "var dec",
            "x", "INTEGER", "var dec",
            "y", "REAL", "var dec",


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

    testing::internal::CaptureStdout();
    post_node_visitor visitor;
    node->accept(&visitor);
    std::string output = testing::internal::GetCapturedStdout();
    auto expect_string = string_join(expect, "\n"s);
    ASSERT_EQ(expect_string, output);

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
            "a", "INTEGER", "var dec",
            "b", "INTEGER", "var dec",
            "y", "REAL", "var dec",

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

    testing::internal::CaptureStdout();
    post_node_visitor visitor;
    node->accept(&visitor);
    std::string output = testing::internal::GetCapturedStdout();
    auto expect_string = string_join(expect, "\n"s);
    ASSERT_EQ(expect_string, output);

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
            "a", "INTEGER", "var dec",
            "b", "INTEGER", "var dec",
            "y", "REAL", "var dec",

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

    testing::internal::CaptureStdout();
    post_node_visitor visitor;
    node->accept(&visitor);
    std::string output = testing::internal::GetCapturedStdout();
    auto expect_string = string_join(expect, "\n"s);
    ASSERT_EQ(expect_string, output);

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
            "a", "INTEGER", "var dec",

            "a", "REAL", "var dec",
            "k", "INTEGER", "var dec",

            "a", "INTEGER", "var dec",
            "z", "INTEGER", "var dec",

            "z", "777", ":=",
            "noop",
            "compound",
            "block",

            "proc dec",

            "noop",
            "compound",

            "block",

            "proc dec",

            "a", "10", ":=",
            "noop",
            "compound",
            "block",
            "program"
    };

    testing::internal::CaptureStdout();
    post_node_visitor visitor;
    node->accept(&visitor);
    std::string output = testing::internal::GetCapturedStdout();
    auto expect_string = string_join(expect, "\n"s);
    ASSERT_EQ(expect_string, output);

}


TEST(parser, sample) {

    auto code = R"(
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
    testing::internal::CaptureStdout();
    auto node = parser(lexer(code)).parse();
    vector<string> list = {
            "n", "INTEGER", "var dec",
            "LONGINT", "noop",
            "n", "0", "=",
            "factorial", "1", ":=",
            "block",
            "factorial", "n",
            "n", "1", "-",
            "proc call: factorial",
            "*", ":=", "block", "if",
            "compound", "block", "func dec: factorial",
            "n", "INTEGER", "var dec",
            "n", "0", ":=", "16",
            "n", "string const: ! = ",
            "n", "proc call: factorial",
            "proc call: writeln",
            "for", "compound", "block", "program"
    };
    post_node_visitor visitor;
    node->accept(&visitor);
    std::string output = testing::internal::GetCapturedStdout();
    std::string expect = string_join(list, "\n"s);
    ASSERT_EQ(expect, output);

}

