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
    inline const std::string & get_text() const { return text;}
    void reset() { pos = 0;}
    void enter_new_expr() { new_expr = true; }
private:
    inline void advance() {
        if (text[pos] == '\n') {
            row++;
            col = 0;
        } else {
            col++;
        }
        pos++;
    }
    inline char peek() { return text[pos+1];}
    token create_token(token t);
    token create_token(token_type type, const string& value);
private:
    string text;
    int pos;
    int row;
    int col;
    bool new_expr = true;
    std::vector<string_view> source_code;
    token last_token;
};


#endif //PASCAL_INTERPRETER_LEXER_H
