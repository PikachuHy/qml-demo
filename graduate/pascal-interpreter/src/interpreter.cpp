//
// Created by pikachu on 2020/4/9.
//

#include "interpreter.h"

int interpreter::interpret() {
    return _parser.parse()->accept(&visitor);
}

