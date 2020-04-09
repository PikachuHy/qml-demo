//
// Created by pikachu on 2020/4/9.
//

#ifndef PASCAL_INTERPRETER_INTERPRETER_H
#define PASCAL_INTERPRETER_INTERPRETER_H
#include "token.h"
#include "lexer.h"
#include <string>
#include <iostream>
#include <any>
#include <unordered_set>

using namespace std;


class interpreter {
public:
    interpreter(const lexer &_lexer);
    interpreter(const string& text) : interpreter(lexer(text)) {
        this->text = text;
    };

    int expr();

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
private:
    lexer _lexer;
    token cur_token;
    string text;

    int expr_internal();
};



#endif //PASCAL_INTERPRETER_INTERPRETER_H
