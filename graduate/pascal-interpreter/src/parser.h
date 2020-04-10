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
enum class ast_node_type {
    binary_operator, number, unknown
};
class node_visitor;
struct ast {
    ast_node_type type = ast_node_type::unknown;
    friend ostream &operator<<(ostream &os, const ast &ast) {
        os << "ast";
        return os;
    }
    virtual int accept(node_visitor* visitor) = 0;
};
struct binary_operator: public ast {
    ast* left;
    token op;
    ast* right;

    binary_operator(ast *left, const token &op, ast *right)
        : left(left), op(op), right(right) {
        type = ast_node_type::binary_operator;
    }

    int accept(node_visitor *visitor) override;

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

    number(const token &token) {
        value = token.get_value<int>();
        type = ast_node_type::number;
    }

    int accept(node_visitor *visitor) override;

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
    parser(const lexer &lexer);
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

struct node_visitor {
    int visit(ast* node) {
        switch (node->type) {
            case ast_node_type::binary_operator:
                return visit((binary_operator*)node);
            case ast_node_type::number:
                return visit((number*)node);
        }
        std::cout << "Error" << std::endl;
        exit(1);
    }
    int visit(number* node) {
        return node->value;
    }
    int visit(binary_operator* node) {
        auto a = visit(node->left);
        auto b = visit(node->right);
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