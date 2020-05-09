//
// Created by pikachu on 2020/4/9.
//

#ifndef PASCAL_INTERPRETER_INTERPRETER_H
#define PASCAL_INTERPRETER_INTERPRETER_H
#include "token.h"
#include "lexer.h"
#include "parser.h"
#include <string>
#include <iostream>
#include <any>
#include <unordered_set>
#include <stack>
#include <variant>
#include <nlohmann/fifo_map.hpp>
using namespace std;

enum class activation_record_type {
    program
};
using eval_ret = std::variant<int, float, string>;
class activation_record {
public:
    activation_record(string name, activation_record_type type, int nestingLevel);

    void set(const string & key, variant<int, float, string> value) {
        memory[key] = value;
    }
    variant<int, float, string> get(const string& key) {
        return memory[key];
    }
    void print();
private:
    string name;
    activation_record_type type;
    int nesting_level;
    nlohmann::fifo_map<string, eval_ret> memory;
};
class call_stack {
public:
    void push(activation_record* ar) {
        records.push(ar);
    }
    activation_record* pop() {
        auto ret = records.top();
        records.pop();
        return ret;
    }
    activation_record* top() {
        return records.top();
    }
private:
    stack<activation_record*> records;
};

class interpreter: public node_visitor_adaptor {
public:
    explicit interpreter(const string& text);
    int interpret();

    void visit(program_node *node) override;

    void visit(variable_declaration_node *node) override;

    void visit(assignment *node) override;

private:
    eval_ret eval_node(ast* node);
    eval_ret eval_number(ast* node);
    eval_ret eval_binary_operator(ast* node);
    eval_ret eval_variable_node(ast* node);
private:
    parser _parser;
    call_stack _call_stack;
    unordered_map<ast_node_type, std::function<eval_ret(ast*)>> eval_table;
};



#endif //PASCAL_INTERPRETER_INTERPRETER_H
