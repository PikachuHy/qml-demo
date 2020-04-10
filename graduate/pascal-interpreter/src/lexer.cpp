//
// Created by pikachu on 2020/4/9.
//

#include "lexer.h"

#include <utility>
string to_upper(const string& s) {
    string ret;
    for(char ch: s) {
        ret += toupper(ch);
    }
    return ret;
}
lexer::lexer(string text) : text(std::move(text)) {
    pos = 0;
}
token lexer::get_next_token() {
    if (pos >= text.size()) return token_constant::eof;
    token ret{token_type::unknown, text.substr(pos, 1), pos};
    while (text[pos] == ' ' || text[pos] == '\n') {
        advance();
    }
    if (text[pos] == '_' || isalpha(text[pos])) {
        auto start = pos;
        while (text[pos] == '_' || isalnum(text[pos])) {
            advance();
        }
        auto str = text.substr(start, pos - start);
        auto upper_str = to_upper(str);
        auto iter = token_constant::keyword_token_map.find(upper_str);
        if (iter != token_constant::keyword_token_map.end()) {
            ret = iter->second;
            ret.set_pos(start);
        } else {
            ret = {token_type::identifier, str, start};
        }
    } else if (text[pos] == ':' && peek() == '=') {
        ret = { token_type::assignment, text.substr(pos, 2), pos};
        advance();
        advance();
    } else if (isdigit(text[pos])) {
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

