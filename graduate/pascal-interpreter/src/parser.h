//
// Created by pikachu on 2020/4/10.
//

#ifndef PASCAL_INTERPRETER_PARSER_H
#define PASCAL_INTERPRETER_PARSER_H
#include "token.h"
#include "lexer.h"
#include <string>
#include <iostream>
#include <any>
#include <unordered_set>
#include <utility>
enum class ast_node_type {
    binary_operator, number, unknown
};
class abstract_node_visitor;
struct ast {
    ast_node_type type = ast_node_type::unknown;
    friend ostream &operator<<(ostream &os, const ast &ast) {
        os << "ast";
        return os;
    }
    virtual int accept(abstract_node_visitor* visitor) = 0;
};
struct binary_operator: public ast {
    ast* left;
    token op;
    ast* right;

    binary_operator(ast *left, token op, ast *right)
        : left(left), op(std::move(op)), right(right) {
        type = ast_node_type::binary_operator;
    }

    int accept(abstract_node_visitor *visitor) override;

    friend ostream &operator<<(ostream &os, const binary_operator &ast) {
        os << "binary_operator";
        os << "(";
        os << *ast.left << ", " << ast.op << ", " << *ast.right;
        os << ")";
        return os;
    }

};

struct number: public ast {
    int value;

    explicit number(const token &token) {
        value = token.get_value<int>();
        type = ast_node_type::number;
    }

    int accept(abstract_node_visitor *visitor) override;

    friend ostream &operator<<(ostream &os, const number &ast) {
        os << "number";
        os << "(";
        os << ast.value;
        os << ")";
        return os;
    }
};
class parser {
public:
    explicit parser(lexer lexer);
    ast* parse() { expr(); }
private:
    void eat(token_type type);
    void error(string msg, token_type type) {
        std::cout << "Error: " << msg << std::endl;
        std::cout << _lexer.get_text() << std::endl;
        for(int i=0;i<cur_token.pos;i++) {
            std::cout << " ";
        }
        std::cout << "^" << std::endl;
        std::cout << "Expect " << type << std::endl;
        throw msg;
    }
    ast* expr();
    ast* factor();
    ast* term();
private:
    lexer _lexer;
    token cur_token;
    bool first = true;
};
struct abstract_node_visitor {
    virtual int visit(number* node) = 0;

    virtual int visit(binary_operator* node) = 0;
};
struct node_visitor: public abstract_node_visitor {
    int visit(number* node) override {
        return node->value;
    }
    int visit(binary_operator* node) override {
        auto a = node->left->accept(this);
        auto b = node->right->accept(this);
        switch (node->op.type) {
            case token_type::plus:
                return a + b;
            case token_type::minus:
                return a - b;
            case token_type::multiplication:
                return a * b;
            case token_type::division:
                return a / b;
            default:
                break;
        }
        std::cout << "Error" << std::endl;
        exit(1);
    }
};

#endif //PASCAL_INTERPRETER_PARSER_H
