//
// Created by pikachu on 2020/4/9.
//

#ifndef PASCAL_INTERPRETER_LEXER_H
#define PASCAL_INTERPRETER_LEXER_H

#include "token.h"
#include <vector>

class lexer {
public:
    explicit lexer(string text);

    token get_next_token();
    inline const std::string & get_text() const { return _text;}
    void reset() { _pos = 0;}
    void enter_new_expr() {}
private:
    inline void advance() {
        if (_text[_pos] == '\n') {
            _row++;
            _col = 0;
        } else {
            _col++;
        }
        _pos++;
    }
    inline char peek() { return _text[_pos + 1];}
    token create_token(token t);
    token create_token(token_type type, const string& value);
private:
    string _text;
    int _pos;
    int _row;
    int _col;
    std::vector<string_view> _source_code;
    token _last_token;
};


#endif //PASCAL_INTERPRETER_LEXER_H
