//
// Created by pikachu on 2020/4/10.
//

#ifndef PASCAL_INTERPRETER_PARSER_H
#define PASCAL_INTERPRETER_PARSER_H
#include "token.h"
#include "symbol.h"
#include "lexer.h"
#include <string>
#include <iostream>
#include <any>
#include <unordered_set>
#include <utility>
#include <vector>
#define ERROR(msg, type) \
SPDLOG_ERROR(msg); \
error(msg, type);

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
struct identifier_node: public ast {
    string value;

    identifier_node(token token) : value(token.raw) {}
    int accept(abstract_node_visitor *visitor) override;
};
struct type_node: public ast {
    string value;

    type_node(token token) : value(token.raw) {}
    int accept(abstract_node_visitor *visitor) override;
};
struct program_node: public ast {
    string name;
    ast* child;

    program_node(string name, ast *child) : name(name), child(child) {}

    int accept(abstract_node_visitor *visitor) override;
};
struct variable_declaration_node;
struct procedure_node: public ast {
    string name;
    vector<variable_declaration_node*> params;
    ast* child;

    procedure_node(string name, vector<variable_declaration_node*> params, ast *child) : name(name), params(std::move(params)), child(child) {}

    int accept(abstract_node_visitor *visitor) override;
};
struct function_node: public ast {
    string name;
    vector<variable_declaration_node*> params;
    type_node* ret_type;
    ast* child;

    function_node(string name, vector<variable_declaration_node*> params, type_node* ret_type, ast *child)
    : name(name), params(std::move(params)), ret_type(ret_type), child(child) {}

    int accept(abstract_node_visitor *visitor) override;
};
struct procedure_call_node: public ast {
    string name;
    vector<ast*> params;

    procedure_call_node(const string &name, const vector<ast*> & params) : name(name), params(params) {}

    int accept(abstract_node_visitor *visitor) override;
};
struct function_call_node: public ast {
    string name;
    vector<ast*> params;

    function_call_node(const string &name, const vector<ast*> & params) : name(name), params(params) {}

    int accept(abstract_node_visitor *visitor) override;
};
struct block_node: public ast {
    vector<ast*> children;

    block_node(vector<ast*>  children) : children(std::move(children)) {}

    int accept(abstract_node_visitor *visitor) override;
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
struct unary_operator: public ast {
    token op;
    ast* value;

    unary_operator(token op, ast *value) : op(std::move(op)), value(value) {}

    friend ostream &operator<<(ostream &os, const unary_operator &ast) {
        os << "unary_operator";
        os << "(";
        os << ast.op << ", " << *ast.value;
        os << ")";
        return os;
    }

    int accept(abstract_node_visitor *visitor) override;
};
struct compound: public ast {
    vector<ast*> children;

    compound(vector<ast*> children) : children(std::move(children)) {}

    int accept(abstract_node_visitor *visitor) override;

};
struct noop: public ast {
    int accept(abstract_node_visitor *visitor) override;
};
struct assignment: public ast {
    ast* left;
    ast* right;

    assignment(ast *left, ast *right) : left(left), right(right) {}

    int accept(abstract_node_visitor *visitor) override;
};
struct if_node: public ast {
    ast* condition;
    ast* if_block;
    ast* else_block;

    if_node(ast *condition, ast *ifBlock, ast *elseBlock) : condition(condition), if_block(ifBlock),
                                                            else_block(elseBlock) {}

    int accept(abstract_node_visitor *visitor) override;

};
struct for_node: public ast {
    ast* init;
    ast* end;
    ast* block;

    for_node(ast *init, ast* end, ast *block) : init(init), end(end), block(block) {}

    int accept(abstract_node_visitor *visitor) override;
};
struct bool_expr_node: public ast {
    ast* left;
    token op;
    ast* right;

    bool_expr_node(ast *left, token op, ast *right) : left(left), op(std::move(op)), right(right) {}
    int accept(abstract_node_visitor *visitor) override;
};
struct variable_node: public ast {
    token id;

    variable_node(token id) : id(std::move(id)) {}

    int accept(abstract_node_visitor *visitor) override;
};
struct number: public ast {
    int value;
    token num;
    explicit number(const token &token) {
        num = token;
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
struct string_node: public ast {
    token value;
    string_node(token value) : value(std::move(value)) {}
    int accept(abstract_node_visitor *visitor) override;
};
struct variable_declaration_node: public ast {
    identifier_node* name;
    type_node* type;

    variable_declaration_node(identifier_node *name, type_node *type) : name(name), type(type) {}

    int accept(abstract_node_visitor *visitor) override;

    string get_name() {return name->value;}
    string get_type() {return type->value;}
};
class parser {
public:
    explicit parser(lexer lexer);
    ast* parse();
    ast* expr();
private:
    void eat(token_type type);
    void error(string msg, token_type expect_type);
    ast* factor();
    ast* term();
    ast* program();
    vector<ast*> procedure();
    vector<ast*> function();
    ast* compound_statement();
    vector<ast*> statement_list();
    ast* statement();
    ast* procedure_call_statement(token id);
    ast* function_call_statement(token id);
    ast* assignment_statement(token id);
    ast* if_statement();
    ast* for_statement();
    variable_node* variable();
    ast* empty();
    ast* block();
    vector<ast*> declarations();
    vector<ast*> variable_declaration();
private:
    lexer _lexer;
    token cur_token;
    bool first = true;
};
struct abstract_node_visitor {
    virtual int visit(program_node* node) = 0;
    virtual int visit(identifier_node* node) = 0;
    virtual int visit(type_node* node) = 0;
    virtual int visit(procedure_node* node) = 0;
    virtual int visit(function_node* node) = 0;
    virtual int visit(procedure_call_node* node) = 0;
    virtual int visit(function_call_node* node) = 0;
    virtual int visit(block_node* node) = 0;
    virtual int visit(variable_declaration_node* node) = 0;

    virtual int visit(number* node) = 0;
    virtual int visit(string_node* node) = 0;

    virtual int visit(binary_operator* node) = 0;

    virtual int visit(unary_operator* node) = 0;

    virtual int visit(noop* node) = 0;

    virtual int visit(compound* node) = 0;
    virtual int visit(assignment* node) = 0;
    virtual int visit(if_node* node) = 0;
    virtual int visit(bool_expr_node* node) = 0;
    virtual int visit(variable_node* node) = 0;
    virtual int visit(for_node* node) = 0;

};
struct node_visitor_adaptor: public abstract_node_visitor {
    int visit(program_node *node) override {
        node->child->accept(this);
        return 0;
    }

    int visit(procedure_node *node) override {
        node->child->accept(this);
        return 0;
    }

    int visit(block_node *node) override {
        for(auto it: node->children) {
            it->accept(this);
        }
        return 0;
    }

    int visit(variable_declaration_node *node) override {
        return 0;
    }

    int visit(number *node) override {
        return 0;
    }
    int visit(string_node *node) override {
        return 0;
    }

    int visit(binary_operator *node) override {
        node->left->accept(this);
        node->right->accept(this);
        return 0;
    }

    int visit(unary_operator *node) override {
        node->value->accept(this);
        return 0;
    }

    int visit(noop *node) override {
        return 0;
    }

    int visit(compound *node) override {
        for(auto it: node->children) {
            it->accept(this);
        }
        return 0;
    }

    int visit(assignment *node) override {
        node->left->accept(this);
        node->right->accept(this);
        return 0;
    }

    int visit(variable_node *node) override {
        return 0;
    }

    int visit(procedure_call_node *node) override {
        return 0;
    }

    int visit(function_node *node) override {
        return 0;
    }

    int visit(if_node *node) override {
        return 0;
    }

    int visit(bool_expr_node *node) override {
        return 0;
    }

    int visit(for_node *node) override {
        return 0;
    }
    int visit(function_call_node *node) override {
        return 0;
    }

    int visit(identifier_node *node) override {
        return 0;
    }

    int visit(type_node *node) override {
        return 0;
    }
};
struct node_visitor: public node_visitor_adaptor {
    int visit(number* node) override {
        return node->value;
    }

    int visit(unary_operator *node) override {
        auto val = node->value->accept(this);
        if (node->op.get_value<string>() == "-") {
            val = -val;
        }
        return val;
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
            case token_type::integer_division:
                return a / b;
            default:
                break;
        }
        std::cout << "Error" << std::endl;
        exit(1);
    }
};
struct symbol_node_visitor: public node_visitor_adaptor {
    explicit symbol_node_visitor(scoped_symbol_table * table);

    int visit(variable_declaration_node *node) override;

    int visit(variable_node *node) override;

    int visit(procedure_node *node) override;

private:
    scoped_symbol_table* cur_table;
    vector<scoped_symbol_table*> tables;
};
#endif //PASCAL_INTERPRETER_PARSER_H
