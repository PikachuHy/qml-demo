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
    interpreter(const string& text) : _lexer(lexer(text)), _parser(_lexer) {
        this->text = text;
    };

    int interpret();

    token get_next_token();

    void reset() { _lexer.reset(); }
private:
    void eat(token_type type);
    void error(const std::unordered_set<token_type> & set) const;
    void error(string msg, token_type type) {
        std::cout << "Error: " << msg << std::endl;
        std::cout << text << std::endl;
        for(int i=0;i<cur_token.pos;i++) {
            std::cout << " ";
        }
        std::cout << "^" << std::endl;
        std::cout << "Expect " << type << std::endl;
        throw msg;
    }
    int cal(int a, int b, token_type type);
    int factor();
    int term();
    int cal_with_table();
    int expr();
    int expr_internal();
private:
    lexer _lexer;
    parser _parser;
    token cur_token;
    string text;
    node_visitor visitor;
};



#endif //PASCAL_INTERPRETER_INTERPRETER_H
