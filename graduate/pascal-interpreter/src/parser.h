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
    binary_operator, number,
    identifier, assignment, variable_node,
    block_node,
    unknown
};
class abstract_node_visitor;
struct ast {
    ast_node_type type = ast_node_type::unknown;
    friend ostream &operator<<(ostream &os, const ast &ast) {
        os << "ast";
        return os;
    }
    virtual void accept(abstract_node_visitor* visitor) = 0;
};
struct identifier_node: public ast {
    string value;

    identifier_node(token token) : value(token.raw) { type = ast_node_type::identifier; }
    void accept(abstract_node_visitor *visitor) override;
};
struct type_node: public ast {
    string value;

    type_node(token token) : value(token.raw) {}
    void accept(abstract_node_visitor *visitor) override;
};
struct program_node: public ast {
    string name;
    ast* child;

    program_node(string name, ast *child) : name(name), child(child) {}

    void accept(abstract_node_visitor *visitor) override;
};
struct variable_declaration_node;
struct procedure_node: public ast {
    string name;
    vector<variable_declaration_node*> params;
    ast* child;

    procedure_node(string name, vector<variable_declaration_node*> params, ast *child) : name(name), params(std::move(params)), child(child) {}

    void accept(abstract_node_visitor *visitor) override;
};
struct function_node: public ast {
    string name;
    vector<variable_declaration_node*> params;
    type_node* ret_type;
    ast* child;

    function_node(string name, vector<variable_declaration_node*> params, type_node* ret_type, ast *child)
    : name(name), params(std::move(params)), ret_type(ret_type), child(child) {}

    void accept(abstract_node_visitor *visitor) override;
};
struct procedure_or_function_call_node: public ast {
    string name;
    vector<ast*> params;

    procedure_or_function_call_node(string name, vector<ast*> params) : name(std::move(name)), params(std::move(params)) {}

    void accept(abstract_node_visitor *visitor) override;
};
struct block_node: public ast {
    vector<ast*> children;

    block_node(vector<ast*>  children)
    : children(std::move(children)) {
        type = ast_node_type::block_node;
    }

    void accept(abstract_node_visitor *visitor) override;
};
struct binary_operator: public ast {
    ast* left;
    token op;
    ast* right;

    binary_operator(ast *left, token op, ast *right)
        : left(left), op(std::move(op)), right(right) {
        type = ast_node_type::binary_operator;
    }

    void accept(abstract_node_visitor *visitor) override;

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

    void accept(abstract_node_visitor *visitor) override;
};
struct compound: public ast {
    vector<ast*> children;

    compound(vector<ast*> children) : children(std::move(children)) {}

    void accept(abstract_node_visitor *visitor) override;

};
struct noop: public ast {
    void accept(abstract_node_visitor *visitor) override;
};
struct variable_node;
struct assignment: public ast {
    variable_node* left;
    ast* right;

    assignment(variable_node *left, ast *right) : left(left), right(right) {
        type = ast_node_type::assignment;
    }

    void accept(abstract_node_visitor *visitor) override;
};
struct if_node: public ast {
    ast* condition;
    ast* if_block;
    ast* else_block;

    if_node(ast *condition, ast *ifBlock, ast *elseBlock) : condition(condition), if_block(ifBlock),
                                                            else_block(elseBlock) {}

    void accept(abstract_node_visitor *visitor) override;

};
struct for_node: public ast {
    ast* init;
    ast* end;
    ast* block;

    for_node(ast *init, ast* end, ast *block) : init(init), end(end), block(block) {}

    void accept(abstract_node_visitor *visitor) override;
};
struct bool_expr_node: public ast {
    ast* left;
    token op;
    ast* right;

    bool_expr_node(ast *left, token op, ast *right) : left(left), op(std::move(op)), right(right) {}
    void accept(abstract_node_visitor *visitor) override;
};
struct variable_node: public ast {
    token id;

    variable_node(token id) : id(std::move(id)) {
        type = ast_node_type::variable_node;
    }

    void accept(abstract_node_visitor *visitor) override;
};
struct number: public ast {
    int value;
    token num;
    explicit number(const token &token) {
        num = token;
        type = ast_node_type::number;
    }

    void accept(abstract_node_visitor *visitor) override;

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
    void accept(abstract_node_visitor *visitor) override;
};
struct variable_declaration_node: public ast {
    identifier_node* name;
    type_node* type;

    variable_declaration_node(identifier_node *name, type_node *type) : name(name), type(type) {}

    void accept(abstract_node_visitor *visitor) override;

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
    ast* procedure_or_function_call_statement(token id);

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
    virtual void visit(program_node* node) = 0;
    virtual void visit(identifier_node* node) = 0;
    virtual void visit(type_node* node) = 0;
    virtual void visit(procedure_node* node) = 0;
    virtual void visit(function_node* node) = 0;
    virtual void visit(procedure_or_function_call_node* node) = 0;
    virtual void visit(block_node* node) = 0;
    virtual void visit(variable_declaration_node* node) = 0;

    virtual void visit(number* node) = 0;
    virtual void visit(string_node* node) = 0;

    virtual void visit(binary_operator* node) = 0;

    virtual void visit(unary_operator* node) = 0;

    virtual void visit(noop* node) = 0;

    virtual void visit(compound* node) = 0;
    virtual void visit(assignment* node) = 0;
    virtual void visit(if_node* node) = 0;
    virtual void visit(bool_expr_node* node) = 0;
    virtual void visit(variable_node* node) = 0;
    virtual void visit(for_node* node) = 0;

};
struct node_visitor_adaptor: public abstract_node_visitor {
    void visit(program_node *node) override {
        node->child->accept(this);
    }

    void visit(procedure_node *node) override {
        for(auto it: node->params) it->accept(this);
        node->child->accept(this);
    }

    void visit(block_node *node) override {
        for(auto it: node->children) {
            it->accept(this);
        }
    }

    void visit(variable_declaration_node *node) override {
        node->name->accept(this);
        node->type->accept(this);
    }

    void visit(number *node) override {
    }
    void visit(string_node *node) override {
    }

    void visit(binary_operator *node) override {
        node->left->accept(this);
        node->right->accept(this);
    }

    void visit(unary_operator *node) override {
        node->value->accept(this);
    }

    void visit(noop *node) override {
    }

    void visit(compound *node) override {
        for(auto it: node->children) {
            it->accept(this);
        }
    }

    void visit(assignment *node) override {
        node->left->accept(this);
        node->right->accept(this);
    }

    void visit(variable_node *node) override {
    }

    void visit(procedure_or_function_call_node *node) override {
        for(auto it: node->params) it->accept(this);
    }

    void visit(function_node *node) override {
        for(auto it: node->params) it->accept(this);
        node->ret_type->accept(this);
        node->child->accept(this);
    }

    void visit(if_node *node) override {
        node->condition->accept(this);
        node->if_block->accept(this);
        node->else_block->accept(this);
    }

    void visit(bool_expr_node *node) override {
        node->left->accept(this);
        node->right->accept(this);
    }

    void visit(for_node *node) override {
        node->init->accept(this);
        node->end->accept(this);
        node->block->accept(this);
    }

    void visit(identifier_node *node) override {
    }

    void visit(type_node *node) override {
    }
};

struct symbol_node_visitor: public node_visitor_adaptor {
    explicit symbol_node_visitor(scoped_symbol_table * table);

    void visit(variable_declaration_node *node) override;

    void visit(variable_node *node) override;

    void visit(procedure_node *node) override;

    void visit(function_node *node) override;

    void visit(procedure_or_function_call_node *node) override;

    void visit(program_node *node) override;

private:
    scoped_symbol_table* cur_table;
    vector<scoped_symbol_table*> tables;
};
#endif //PASCAL_INTERPRETER_PARSER_H
