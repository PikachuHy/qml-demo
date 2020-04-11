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
void split_string(const string_view s, std::vector<string_view>& v, const string_view c)
{
    string::size_type pos1, pos2;
    pos2 = s.find(c);
     pos1 = 0;
     while(string::npos != pos2)
     {
         v.push_back(s.substr(pos1, pos2-pos1));

         pos1 = pos2 + c.size();
         pos2 = s.find(c, pos1);
     }
     if(pos1 != s.length())
         v.push_back(s.substr(pos1));
 }
lexer::lexer(string text) : text(std::move(text)) {
    pos = 0;
    row = 0;
    col = 0;
    split_string(this->text, this->source_code, "\n"sv);
}
token lexer::get_next_token() {
    if (pos >= text.size()) return token_constant::eof;
    token ret = create_token(token_type::unknown, text.substr(pos, 1));
    while (text[pos] == ' ' || text[pos] == '\n') {
        advance();
    }
    if (text[pos] == '_' || isalpha(text[pos])) {
        auto cur_col = col;
        auto start = pos;
        while (text[pos] == '_' || isalnum(text[pos])) {
            advance();
        }
        auto str = text.substr(start, pos - start);
        auto upper_str = to_upper(str);
        auto iter = token_constant::keyword_token_map.find(upper_str);
        if (iter != token_constant::keyword_token_map.end()) {
            ret = create_token(iter->second);
        } else {
            ret = create_token(token_type::identifier, str);
        }
        ret.col = cur_col;
    } else if (text[pos] == ':' && peek() == '=') {
        ret = create_token(token_type::assignment, text.substr(pos, 2));
        advance();
        advance();
    } else if (isdigit(text[pos])) {
        auto cur_col = col;
        auto start = pos;
        while (isdigit(text[pos])) {
            advance();
        }
        ret = create_token(token_type::integer, text.substr(start, pos - start));
        ret.col = cur_col;
    } else if ((token_constant::arithmetic_operator_token_type_set.count(last_token.type) == 1
    || last_token.type == token_type::unknown || last_token.type == token_type::left_parenthesis)
        && (text[pos] == '+' || text[pos] == '-')
    ) {
        ret = {token_type::unary, text.substr(pos, 1), pos};
        advance();
    } else {
        auto iter = token_constant::single_char_token_map.find(text[pos]);
        if (iter != token_constant::single_char_token_map.end()) {
            ret = create_token(iter->second);
            advance();
        }
    }
    last_token = ret;
    return ret;
}

token lexer::create_token(token_type type, const string& value) {
    return token(type, value, row, col, source_code[row]);
}

token lexer::create_token(token token) {
    token.row = row;
    token.col = col;
    token.source_code = source_code[row];
    return token;
}

