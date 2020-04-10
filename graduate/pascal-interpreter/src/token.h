//
// Created by pikachu on 2020/4/9.
//

#ifndef PASCAL_INTERPRETER_TOKEN_H
#define PASCAL_INTERPRETER_TOKEN_H

#include <string>
#include <iostream>
#include <any>
#include <unordered_map>
#include <unordered_set>
using namespace std;

enum class token_type {
    integer, left_parenthesis, right_parenthesis,
    plus, minus, multiplication, division,
    unary,
    eof, unknown
};
ostream &operator<<(ostream &os, const token_type &type);
struct token {
    token_type type = token_type::unknown;
    any value;
    int pos;
    token(token_type type = token_type::unknown, string value = ""s, int pos = 0);


    template<typename T>
    T get_value() const {
        return std::any_cast<T>(value);
    }
    token set_pos(int pos) {
        this->pos = pos;
        return *this;
    }
    friend ostream &operator<<(ostream &os, const token &token) {
        os << "type: " << token.type << " value: " << token.get_value<string>();
        return os;
    }

    bool operator==(const token &rhs) const;

    bool operator!=(const token &rhs) const;
};

namespace token_constant {
    extern const token plus;
    extern const token minus;
    extern const token multiplication;
    extern const token division;
    extern const token left_parenthesis;
    extern const token right_parenthesis;
    extern const token eof;
    extern const token unknown;
    extern const unordered_map<char, token> arithmetic_operator_token_map;
    extern const unordered_set<token_type> arithmetic_operator_token_type_set;
    extern const unordered_map<char, token> single_char_token_map;
}


#endif //PASCAL_INTERPRETER_TOKEN_H
