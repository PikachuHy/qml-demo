//
// Created by pikachu on 2020/4/9.
//

#include "token.h"
// TODO 更好的方式写常量
const token token_constant::plus = token(token_type::plus, "+");
const token token_constant::minus = token(token_type::minus, "-");
const token token_constant::multiplication = token(token_type::multiplication, "*");
const token token_constant::division = token(token_type::division, "/");
const token token_constant::left_parenthesis = token(token_type::left_parenthesis, "(");
const token token_constant::right_parenthesis = token(token_type::right_parenthesis, ")");
const token token_constant::eof = token(token_type::eof, "-1");
const token token_constant::unknown = token(token_type::unknown, "");
const unordered_map<char, token> token_constant::arithmetic_operator_token_map = {
        {plus.get_value<string>()[0], plus},
        {minus.get_value<string>()[0], minus},
        {multiplication.get_value<string>()[0], multiplication},
        {division.get_value<string>()[0], division},
};
const unordered_set<token_type> token_constant::arithmetic_operator_token_type_set = {
        token_type::plus, token_type::minus, token_type::multiplication, token_type::division, token_type::unary
};
const std::unordered_map<char, token> token_constant::single_char_token_map = {
        {plus.get_value<string>()[0], plus},
        {minus.get_value<string>()[0], minus},
        {multiplication.get_value<string>()[0], multiplication},
        {division.get_value<string>()[0], division},
        {left_parenthesis.get_value<string>()[0], left_parenthesis},
        {right_parenthesis.get_value<string>()[0], right_parenthesis},
};
token::token(token_type type, string value, int pos) : type(type) {
    this->pos = pos;
    if (type == token_type::integer) {
        this->value = atoi(value.c_str());
    } else {
        this->value = value;
    }
}

bool token::operator==(const token &rhs) const {
    if (type != rhs.type) return false;
    if (type == token_type::integer) {
        return get_value<int>() == rhs.get_value<int>();
    }
    return get_value<string>() == rhs.get_value<string>();
}

bool token::operator!=(const token &rhs) const {
    return !(rhs == *this);
}

ostream &operator<<(ostream &os, const token_type &type) {
    switch (type) {
        case token_type::integer:
            os << "integer";
            break;
        case token_type::plus:
            os << "plus";
            break;
        case token_type::minus:
            os << "minus";
            break;
        case token_type::multiplication:
            os << "multiplication";
            break;
        case token_type::division:
            os << "division";
            break;
        case token_type::eof:
            os << "eof";
            break;
        case token_type::unknown:
            os << "unknown";
            break;
        case token_type::left_parenthesis:
            os << "(";
            break;
        case token_type::right_parenthesis:
            os << ")";
            break;
    }
    return os;
}
