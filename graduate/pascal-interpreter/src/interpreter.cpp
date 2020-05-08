//
// Created by pikachu on 2020/4/9.
//

#include "common.h"
#include "interpreter.h"

#include <utility>

int interpreter::interpret() {
    auto ast = _parser.parse();
    return 0;
}

void interpreter::visit(program_node *node) {
    activation_record ar(node->name, activation_record_type::program, 1);
    node_visitor_adaptor::visit(node);
}

activation_record::activation_record(string name, activation_record_type type, int nestingLevel)
        : name(std::move(name)), type(type), nesting_level(nestingLevel) {}
