//
// Created by pikachu on 2020/4/9.
//

#include "lexer.h"

#include <utility>

lexer::lexer(string text) : text(std::move(text)) {
    pos = 0;
}
token lexer::get_next_token() {
    if (pos >= text.size()) return token_constant::eof;
    token ret{token_type::unknown, text.substr(pos, 1), pos};
    while (text[pos] == ' ') {
        advance();
    }
    if (isdigit(text[pos])) {
        auto start = pos;
        while (isdigit(text[pos])) {
            advance();
        }
        ret = {token_type::integer, text.substr(start, pos - start), start};
    } else if ((token_constant::arithmetic_operator_token_type_set.count(last_token.type) == 1
    || last_token.type == token_type::unknown || last_token.type == token_type::left_parenthesis)
        && (text[pos] == '+' || text[pos] == '-')
    ) {
        ret = {token_type::unary, text.substr(pos, 1), pos};
        advance();
    } else {
        auto iter = token_constant::single_char_token_map.find(text[pos]);
        if (iter != token_constant::single_char_token_map.end()) {
            ret = iter->second;
            ret.set_pos(pos);
            advance();
        }
    }
    last_token = ret;
    return ret;
}

