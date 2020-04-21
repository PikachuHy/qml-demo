//
// Created by pikachu on 2020/4/11.
//

#include <iostream>
#include <string>
#include <utility>
#include <exception>
#include <vector>
#include <climits>
#include <numeric>
#include <algorithm>
// https://github.com/gabime/spdlog
using namespace std;
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <execinfo.h>
#include <fmt/format.h>
#include "parser.h"
class ast_visualizer: public node_visitor_adaptor {
public:
    ast_visualizer() {
        dot_header.emplace_back(R"(
digraph astgraph {
  node [shape=circle, fontsize=12, fontname="Courier", height=.1];
  ranksep=.3;
  edge [arrowsize=.5]

)");
        dot_footer.emplace_back("}");
    }
    string gendot() {
        string ret;
        for(const auto& it: dot_header) {
            ret += it;
        }
        for(const auto& it: dot_body) {
            ret += it;
        }
        for(const auto& it: dot_footer) {
            ret += it;
        }
        return ret;
    }
    int visit(program_node *node) override {
        add_node(node, "program"s);
        node->child->accept(this);
        add_edge(node, node->child);
    }

    int visit(procedure_node *node) override {
        add_node(node, fmt::format("proc_dec:{}", node->name));
        for(auto it: node->params) {
            it->accept(this);
            add_edge(node, it);
        }
        node->child->accept(this);
        add_edge(node, node->child);
    }

    int visit(block_node *node) override {
        add_node(node, "block"s);
        for (auto it: node->children) {
            it->accept(this);
        }
        for (auto it: node->children) {
            add_edge(node, it);
        }
    }

    int visit(variable_declaration_node *node) override {
        add_node(node, "var dec"s);
        node->name->accept(this);
        node->type->accept(this);
        add_edge(node, node->name);
        add_edge(node, node->type);
    }

    int visit(number *node) override {
        add_node(node, node->num.raw);
    }

    int visit(string_node *node) override {
        add_node(node, fmt::format("string const: {}", node->value.raw));
    }

    int visit(binary_operator *node) override {
        add_node(node, node->op.raw);
        node->left->accept(this);
        node->right->accept(this);
        add_edge(node, node->left);
        add_edge(node, node->right);
    }

    int visit(unary_operator *node) override {
        add_node(node, fmt::format("unary {}", node->op.raw));
        node->value->accept(this);
        add_edge(node, node->value);
    }

    int visit(noop *node) override {
        add_node(node, "noop"s);
    }

    int visit(compound *node) override {
        add_node(node, "compound");
        for(auto it: node->children) {
            it->accept(this);
            add_edge(node, it);
        }
    }

    int visit(assignment *node) override {
        add_node(node, ":="s);
        node->left->accept(this);
        node->right->accept(this);
        add_edge(node, node->left);
        add_edge(node, node->right);
    }

    int visit(variable_node *node) override {
        add_node(node, node->id.raw);
    }

    int visit(procedure_call_node *node) override {
        add_node(node, fmt::format("proc call:{}", node->name));
        for(auto it: node->params) {
            it->accept(this);
            add_edge(node, it);
        }

    }

    int visit(function_node *node) override {
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

    int visit(if_node *node) override {
        add_node(node, "if"s);
        node->condition->accept(this);
        node->if_block->accept(this);
        node->else_block->accept(this);
        add_edge(node, node->condition);
        add_edge(node, node->if_block);
        add_edge(node, node->else_block);
    }

    int visit(bool_expr_node *node) override {
        add_node(node, node->op.raw);
        node->left->accept(this);
        node->right->accept(this);
        add_edge(node, node->left);
        add_edge(node, node->right);
    }

    int visit(for_node *node) override {
        add_node(node, "for"s);
        node->init->accept(this);
        node->end->accept(this);
        node->block->accept(this);
        add_edge(node, node->init);
        add_edge(node, node->end);
        add_edge(node, node->block);
    }

    int visit(function_call_node *node) override {
        add_node(node, fmt::format("func call: {}", node->name));
        for(auto it: node->params) {
            it->accept(this);
            add_edge(node, it);
        }
    }

    int visit(identifier_node *node) override {
        add_node(node, node->value);
    }

    int visit(type_node *node) override {
        add_node(node, node->value);
    }

private:
    void add_node(ast* node, const string& label) {
        ast2count[node]=count;
        auto s = fmt::format(R"(    node{} [label="{}"]{})", count++, label, "\n");
        dot_body.emplace_back(s);
    }
    void add_edge(ast* from, ast* to) {
        auto s = fmt::format("    node{}->node{}\n", ast2count[from], ast2count[to]);
        dot_body.emplace_back(s);
    }
private:
    int count = 1;
    vector<string> dot_header;
    vector<string> dot_body;
    vector<string> dot_footer;
    unordered_map<ast*, int> ast2count;
};
int main() {
    string code = R"(
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
    auto ast = parser(lexer(code)).parse();
    ast_visualizer vis;
    ast->accept(&vis);
    std::cout << vis.gendot() << std::endl;
    return 0;
}