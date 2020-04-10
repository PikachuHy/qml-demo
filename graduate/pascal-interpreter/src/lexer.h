//
// Created by pikachu on 2020/4/9.
//

#ifndef PASCAL_INTERPRETER_LEXER_H
#define PASCAL_INTERPRETER_LEXER_H

#include "token.h"

class lexer {
public:
    explicit lexer(string text);

    token get_next_token();
    inline const std::string & get_text() const { return text;}
    void reset() { pos = 0;}
private:
    inline void advance() { pos++; }
private:
    string text;
    int pos;
};


#endif //PASCAL_INTERPRETER_LEXER_H
