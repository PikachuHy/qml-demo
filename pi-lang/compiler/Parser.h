//
// Created by pikachu on 2020/7/20.
//

#ifndef PI_LANG_PARSER_H
#define PI_LANG_PARSER_H
#include "Lexer.h"

class Parser {
public:
    Parser(const Lexer &lexer);
    void program();
private:
    Lexer lexer;
};


#endif //PI_LANG_PARSER_H
