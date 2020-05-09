//
// Created by pikachu on 2020/4/21.
//

#include "ast_visualizer.h"
#include <fmt/format.h>
ast_visualizer::ast_visualizer() {
    _dot_header.emplace_back(R"(
digraph astgraph {
  node [shape=circle, fontsize=12, fontname="Courier", height=.1];
  ranksep=.3;
  edge [arrowsize=.5]

)");
    _dot_footer.emplace_back("}");
}

string ast_visualizer::gen_dot() {
    string ret;
    for(const auto& it: _dot_header) {
        ret += it;
    }
    for(const auto& it: _dot_body) {
        ret += it;
    }
    for(const auto& it: _dot_footer) {
        ret += it;
    }
    return ret;
}

void ast_visualizer::visit(procedure_node *node) {
    add_node(node, fmt::format("proc_dec:{}", node->name));
    for(auto it: node->params) {
        it->accept(this);
        add_edge(node, it);
    }
    node->child->accept(this);
    add_edge(node, node->child);
}

void ast_visualizer::visit(program_node *node) {
    add_node(node, "program"s);
    node->child->accept(this);
    add_edge(node, node->child);
}

void ast_visualizer::visit(block_node *node) {
    add_node(node, "block"s);
    for (auto it: node->children) {
        it->accept(this);
    }
    for (auto it: node->children) {
        add_edge(node, it);
    }
}

void ast_visualizer::visit(variable_declaration_node *node) {
    add_node(node, "var dec"s);
    node->name->accept(this);
    node->type->accept(this);
    add_edge(node, node->name);
    add_edge(node, node->type);
}

void ast_visualizer::visit(number *node) {
    add_node(node, node->num.raw);
}

void ast_visualizer::visit(string_node *node) {
    add_node(node, fmt::format("string const: {}", node->value.raw));
}

void ast_visualizer::visit(binary_operator *node) {
    add_node(node, node->op.raw);
    node->left->accept(this);
    node->right->accept(this);
    add_edge(node, node->left);
    add_edge(node, node->right);
}

void ast_visualizer::visit(unary_operator *node) {
    add_node(node, fmt::format("unary {}", node->op.raw));
    node->value->accept(this);
    add_edge(node, node->value);
}

void ast_visualizer::visit(noop *node) {
    add_node(node, "noop"s);
}

void ast_visualizer::visit(compound *node) {
    add_node(node, "compound");
    for(auto it: node->children) {
        it->accept(this);
        add_edge(node, it);
    }
}

void ast_visualizer::visit(assignment *node) {
    add_node(node, ":="s);
    node->left->accept(this);
    node->right->accept(this);
    add_edge(node, node->left);
    add_edge(node, node->right);
}

void ast_visualizer::visit(variable_node *node) {
    add_node(node, node->id.raw);
}

void ast_visualizer::visit(procedure_or_function_call_node *node) {
    add_node(node, fmt::format("proc call: {}", node->name));
    for(auto it: node->params) {
        it->accept(this);
        add_edge(node, it);
    }

}

void ast_visualizer::visit(function_node *node) {
    add_node(node, fmt::format("func dec: {}", node->name));
    for(auto it: node->params) {
        it->accept(this);
        add_edge(node, it);
    }
    node->ret_type->accept(this);
    add_edge(node, node->ret_type);
    node->child->accept(this);
    add_edge(node, node->child);
}

void ast_visualizer::visit(if_node *node) {
    add_node(node, "if"s);
    node->condition->accept(this);
    node->if_block->accept(this);
    node->else_block->accept(this);
    add_edge(node, node->condition);
    add_edge(node, node->if_block);
    add_edge(node, node->else_block);
}

void ast_visualizer::visit(bool_expr_node *node) {
    add_node(node, node->op.raw);
    node->left->accept(this);
    node->right->accept(this);
    add_edge(node, node->left);
    add_edge(node, node->right);
}

void ast_visualizer::visit(for_node *node) {
    add_node(node, "for"s);
    node->init->accept(this);
    node->end->accept(this);
    node->block->accept(this);
    add_edge(node, node->init);
    add_edge(node, node->end);
    add_edge(node, node->block);
}


void ast_visualizer::visit(identifier_node *node) {
    add_node(node, node->value);
}

void ast_visualizer::visit(type_node *node) {
    add_node(node, node->value);
}

void ast_visualizer::add_node(ast *node, const string &label) {
    _ast2count[node]=_count;
    auto s = fmt::format(R"(    node{} [label="{}"]{})", _count++, label, "\n");
    _dot_body.emplace_back(s);
}

void ast_visualizer::add_edge(ast *from, ast *to) {
    auto s = fmt::format("    node{}->node{}\n", _ast2count[from], _ast2count[to]);
    _dot_body.emplace_back(s);
}
