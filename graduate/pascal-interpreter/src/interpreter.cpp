//
// Created by pikachu on 2020/4/9.
//

#include "interpreter.h"

int interpreter::interpret() {
    auto ast = _parser.parse();
    return ast->accept(&visitor);
}

