//
// Created by pikachu on 2020/4/9.
//

#ifndef PASCAL_INTERPRETER_LEXER_H
#define PASCAL_INTERPRETER_LEXER_H

#include "token.h"

class lexer {
public:
    lexer(const string &text);

    token get_next_token();
    void reset() { pos = 0;}
private:
    inline void advance() { pos++; }
private:
    string text;
    int pos;
};


#endif //PASCAL_INTERPRETER_LEXER_H
