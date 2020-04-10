//
// Created by pikachu on 2020/4/10.
//

#include "parser.h"

#include <utility>

parser::parser(lexer lexer) : _lexer(std::move(lexer)) {}

void parser::eat(token_type type) {
    if (cur_token.type == type) {
        cur_token = _lexer.get_next_token();
        return;
    }
    error("Invalid syntax", type);
}

ast* parser::factor() {
    auto token = this->cur_token;
    if (token.type == token_type::integer) {
        eat(token_type::integer);
        return new number{token};
    }
    eat(token_type::left_parenthesis);
    auto ret = expr();
    eat(token_type::right_parenthesis);
    return ret;
}

ast *parser::term() {
    auto ret = factor();
    while (cur_token.type == token_type::multiplication
           || cur_token.type == token_type::division) {
        auto token = cur_token;
        eat(token.type);
        ret = new binary_operator(ret, token, factor());
    }
    return ret;
}
ast *parser::expr() {
    if (first) {
        first = false;
        cur_token = _lexer.get_next_token();
    }
    auto ret = term();
    while (cur_token.type == token_type::plus
           || cur_token.type == token_type::minus) {
        auto token = cur_token;
        eat(token.type);
        ret = new binary_operator(ret, token, term());
    }
    return ret;
}

int binary_operator::accept(node_visitor *visitor) {
    return visitor->visit(this);
}

int number::accept(node_visitor *visitor) {
    return visitor->visit(this);
}
