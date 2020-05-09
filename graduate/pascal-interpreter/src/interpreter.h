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
    program, procedure
};
using eval_ret = std::variant<int, float, string>;
class activation_record {
public:
    activation_record(string name, activation_record_type type,
            int nestingLevel, bool trace_memory = false);

    virtual ~activation_record();

    void set(const string & key, variant<int, float, string> value) {
        memory[key] = value;
    }
    variant<int, float, string> get(const string& key) {
        return memory[key];
    }
    void print();

    int nesting_level() { return _nesting_level; }
private:
    string get_type_string();
private:
    string name;
    activation_record_type type;
    string type_string;
    int _nesting_level;
    nlohmann::fifo_map<string, eval_ret> memory;
    bool _trace_memory;

    friend class call_stack;
};
class call_stack {
public:
    call_stack(bool trace_memory = false) : _trace_memory(trace_memory) {}

    void push(activation_record* ar, bool print_flag = true);
    void pop();
    activation_record* top() {
        return records.back();
    }
    void print();
private:
    vector<activation_record*> records;
    bool _trace_memory;
};

class interpreter: public node_visitor_adaptor {
public:
    explicit interpreter(const string& text, bool trace_symbol = false, bool trace_memory = false);
    int interpret();

    void visit(program_node *node) override;

    void visit(variable_declaration_node *node) override;

    void visit(variable_node *node) override;

    void visit(assignment *node) override;

    void visit(procedure_or_function_call_node *node) override;

    void visit(procedure_node *node) override;

    void visit(function_node *node) override;

    void trace_symbol(bool flag = true) {
        _trace_symbol = flag;
    }
    void trace_memory(bool flag = true) {
        _trace_memory = flag;
    }
private:
    eval_ret eval_node(ast* node);
    eval_ret eval_number(ast* node);
    eval_ret eval_binary_operator(ast* node);
    eval_ret eval_variable_node(ast* node);
    void procedure_call(procedure_or_function_call_node* node, procedure_symbol* symbol);
private:
    parser _parser;
    call_stack _call_stack;
    unordered_map<ast_node_type, std::function<eval_ret(ast*)>> eval_table;
    scoped_symbol_table* cur_table;
    vector<scoped_symbol_table*> tables;
    bool _trace_symbol;
    bool _trace_memory;
};



#endif //PASCAL_INTERPRETER_INTERPRETER_H
