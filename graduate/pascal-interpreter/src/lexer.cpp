//
// Created by pikachu on 2020/4/9.
//

#include "common.h"
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
lexer::lexer(string text) : _text(std::move(text)) {
    _pos = 0;
    _row = 0;
    _col = 0;
    split_string(this->_text, this->_source_code, "\n"sv);
}
token lexer::get_next_token() {
    if (_pos >= _text.size()) return token_constant::eof;
    token ret = create_token(token_type::unknown, _text.substr(_pos, 1));
    while (_text[_pos] == ' ' || _text[_pos] == '\n') { // 跳过 空格 回车
        advance();
    }
    if (_text[_pos] == '{') { // 跳过 注释
        advance();
        while (_text[_pos] != '}') {
            advance();
        }
        advance();
        return get_next_token();
    }
    if (_text[_pos] == '\'') { // 字符串
        auto cur_col = _col;
        advance();
        auto start = _pos;
        while (_text[_pos] != '\'') {
            advance();
        }
        auto str = _text.substr(start, _pos - start);
        advance();
        ret = create_token(token_type::string_const, str);
        ret.col = cur_col;
    } else if (_text[_pos] == '_' || isalpha(_text[_pos])) { // 标识符
        auto cur_col = _col;
        auto start = _pos;
        while (_text[_pos] == '_' || isalnum(_text[_pos])) {
            advance();
        }
        auto str = _text.substr(start, _pos - start);
        auto upper_str = to_upper(str);
        auto iter = token_constant::keyword_token_map.find(upper_str);
        if (iter != token_constant::keyword_token_map.end()) {
            ret = create_token(iter->second);
        } else {
            ret = create_token(token_type::identifier, str);
        }
        ret.col = cur_col;
    } else if (_text[_pos] == ':' && peek() == '=') { // 赋值
        ret = create_token(token_type::assignment, _text.substr(_pos, 2));
        advance();
        advance();
    } else if (isdigit(_text[_pos])) { // 数值
        bool is_real = false;
        auto cur_col = _col;
        auto start = _pos;
        while (isdigit(_text[_pos])) {
            advance();
        }
        if (_text[_pos] == '.') {
            is_real = true;
            advance();
        }
        while (isdigit(_text[_pos])) {
            advance();
        }
        auto value = _text.substr(start, _pos - start);
        if (is_real) {

            ret = create_token(token_type::real_const, value);  // 实数
        } else {
            ret = create_token(token_type::integer_const, value); // 整数
        }
        ret.col = cur_col;
    } else if ((token_constant::arithmetic_operator_token_type_set.count(_last_token.type) == 1
                || _last_token.type == token_type::unknown || _last_token.type == token_type::left_parenthesis)
        && (_text[_pos] == '+' || _text[_pos] == '-')
    ) {
        ret = {token_type::unary, _text.substr(_pos, 1), _pos};
        advance();
    } else {
        auto iter = token_constant::single_char_token_map.find(_text[_pos]);
        if (iter != token_constant::single_char_token_map.end()) {
            ret = create_token(iter->second);
            advance();
        } else if (_text[_pos] == '\0') ret = token_type::eof;
        else {
            ret = create_token(token_type::unknown, _text.substr(_pos, 1));
        }
    }

    _last_token = ret;
    return ret;
}

token lexer::create_token(token_type type, const string& value) {
    return token(type, value, _row, _col, _source_code[_row]);
}

token lexer::create_token(token token) {
    token.row = _row;
    token.col = _col;
    token.source_code = _source_code[_row];
    return token;
}

