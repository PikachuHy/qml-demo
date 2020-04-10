//
// Created by pikachu on 2020/4/9.
//

#include "interpreter.h"

token interpreter::get_next_token() {
    return _lexer.get_next_token();
}

int interpreter::interpret() {
    return _parser.parse()->accept(&visitor);
}

