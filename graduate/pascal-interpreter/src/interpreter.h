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

using namespace std;


class interpreter {
public:
    explicit interpreter(const string& text) : _parser(lexer(text)) {
    };

    int interpret();

private:
    parser _parser;
    node_visitor visitor;
};



#endif //PASCAL_INTERPRETER_INTERPRETER_H
