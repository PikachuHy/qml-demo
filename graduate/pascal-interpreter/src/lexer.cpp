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
    while (text[pos] == ' ') {
        advance();
    }
    if (isdigit(text[pos])) {
        auto start = pos;
        while (isdigit(text[pos])) {
            advance();
        }
        return {token_type::integer, text.substr(start, pos - start), start};
    }
    auto iter = token_constant::single_char_token_map.find(text[pos]);
    if (iter != token_constant::single_char_token_map.end()) {
        auto ret = iter->second;
        ret.set_pos(pos);
        advance();
        return ret;
    }
    return {token_type::unknown, text.substr(pos, 1), pos};
}

