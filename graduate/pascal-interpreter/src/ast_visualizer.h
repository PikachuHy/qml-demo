//
// Created by pikachu on 2020/4/21.
//

#ifndef PASCAL_INTERPRETER_AST_VISUALIZER_H
#define PASCAL_INTERPRETER_AST_VISUALIZER_H
#include "parser.h"
#include <unordered_map>
using std::unordered_map;

class ast_visualizer: public node_visitor_adaptor {
public:
    ast_visualizer();
    string gen_dot();
private:
    void visit(program_node *node) override;

    void visit(procedure_node *node) override;

    void visit(block_node *node) override;

    void visit(variable_declaration_node *node) override;

    void visit(number *node) override;

    void visit(string_node *node) override;

    void visit(binary_operator *node) override;

    void visit(unary_operator *node) override;

    void visit(noop *node) override;

    void visit(compound *node) override;

    void visit(assignment *node) override;

    void visit(variable_node *node) override;

    void visit(procedure_call_node *node) override;

    void visit(function_node *node) override;

    void visit(if_node *node) override;

    void visit(bool_expr_node *node) override;

    void visit(for_node *node) override;

    void visit(function_call_node *node) override;

    void visit(identifier_node *node) override;

    void visit(type_node *node) override;

    void add_node(ast* node, const string& label);
    void add_edge(ast* from, ast* to);
private:
    int count = 1;
    vector<string> dot_header;
    vector<string> dot_body;
    vector<string> dot_footer;
    unordered_map<ast*, int> ast2count;
};


#endif //PASCAL_INTERPRETER_AST_VISUALIZER_H
