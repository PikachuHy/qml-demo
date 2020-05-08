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

using namespace std;

enum class activation_record_type {
    program
};
class activation_record {
public:
    activation_record(string name, activation_record_type type, int nestingLevel);

private:
    string name;
    activation_record_type type;
    int nesting_level;
};
class call_stack {
public:
    void push(activation_record ar) {
        records.emplace(ar);
    }
    activation_record pop() {
        auto ret = records.top();
        records.pop();
        return ret;
    }
    activation_record top() {
        return records.top();
    }
private:
    stack<activation_record> records;
};
class interpreter: public node_visitor_adaptor {
public:
    explicit interpreter(const string& text) : _parser(lexer(text)) {
    };

    int interpret();

    void visit(program_node *node) override;

private:
    parser _parser;

};



#endif //PASCAL_INTERPRETER_INTERPRETER_H
