//
// Created by pikachu on 2020/4/9.
//
#include "common.h"
#include "token.h"

// TODO 更好的方式写常量
const token token_constant::plus = token(token_type::plus, "+");
const token token_constant::minus = token(token_type::minus, "-");
const token token_constant::multiplication = token(token_type::multiplication, "*");
const token token_constant::integer_division = token(token_type::integer_division, "/");
const token token_constant::float_division = token(token_type::float_division, "DIV");
const token token_constant::left_parenthesis = token(token_type::left_parenthesis, "(");
const token token_constant::right_parenthesis = token(token_type::right_parenthesis, ")");
const token token_constant::dot = token(token_type::dot, ".");
const token token_constant::semicolon = token(token_type::semicolon, ";");
const token token_constant::colon = token(token_type::colon, ":");
const token token_constant::comma = token(token_type::comma, ",");
const token token_constant::begin = token(token_type::begin, "BEGIN");
const token token_constant::end = token(token_type::end, "END");
const token token_constant::variable = token(token_type::variable, "VAR");
const token token_constant::real = token(token_type::type_specification, "REAL");
const token token_constant::integer = token(token_type::type_specification, "INTEGER");
const token token_constant::eof = token(token_type::eof, "-1");
const token token_constant::unknown = token(token_type::unknown, "");
const token token_constant::program = token(token_type::program, "PROGRAM");
const token token_constant::procedure = token(token_type::procedure, "PROCEDURE");
const unordered_map<char, token> token_constant::arithmetic_operator_token_map = {
        {plus.get_value<string>()[0],             plus},
        {minus.get_value<string>()[0],            minus},
        {multiplication.get_value<string>()[0],   multiplication},
        {integer_division.get_value<string>()[0], integer_division},
};
const unordered_set<token_type> token_constant::arithmetic_operator_token_type_set = {
        token_type::plus,
        token_type::minus,
        token_type::multiplication,
        token_type::integer_division,
        token_type::unary
};
const std::unordered_map<char, token> token_constant::single_char_token_map = {
        {plus.get_value<string>()[0],              plus},
        {minus.get_value<string>()[0],             minus},
        {multiplication.get_value<string>()[0],    multiplication},
        {integer_division.get_value<string>()[0],  integer_division},
        {left_parenthesis.get_value<string>()[0],  left_parenthesis},
        {right_parenthesis.get_value<string>()[0], right_parenthesis},
        {dot.get_value<string>()[0],               dot},
        {semicolon.get_value<string>()[0],         semicolon},
        {colon.get_value<string>()[0],             colon},
        {comma.get_value<string>()[0],             comma},
};
const std::unordered_map<string, token> token_constant::keyword_token_map = {
        {begin.get_value<string>(),          begin},
        {end.get_value<string>(),            end},
        {float_division.get_value<string>(), float_division},
        {program.get_value<string>(),        program},
        {variable.get_value<string>(),       variable},
        {real.get_value<string>(),           real},
        {integer.get_value<string>(),        integer},
        {procedure.get_value<string>(),        procedure},

};

token::token(token_type type, string value, int row, int col, string_view source_code)
        : type(type), row(row), col(col), source_code(source_code), raw(value) {
    if (type == token_type::integer_const) {
        this->value = atoi(value.c_str());
    } else if (type == token_type::real_const) {
        this->value = atof(value.c_str());
    } else {
        this->value = value;
    }
}

bool token::operator==(const token &rhs) const {
    if (type != rhs.type) return false;
    if (type == token_type::integer_const) {
        return get_value<int>() == rhs.get_value<int>();
    }
    return get_value<string>() == rhs.get_value<string>();
}

bool token::operator!=(const token &rhs) const {
    return !(rhs == *this);
}

ostream &operator<<(ostream &os, const token_type &type) {
    switch (type) {
        case token_type::integer_const:
            os << "integer_const";
            break;
        case token_type::plus:
            os << "plus(+)";
            break;
        case token_type::minus:
            os << "minus(-)";
            break;
        case token_type::multiplication:
            os << "multiplication(*)";
            break;
        case token_type::integer_division:
            os << "integer_division(DIV)";
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
        case token_type::begin:
            os << "BEGIN";
            break;
        case token_type::end:
            os << "END";
            break;
        case token_type::dot:
            os << ".";
            break;
        case token_type::assignment:
            os << "assignment(:=)";
            break;
        case token_type::semicolon:
            os << "semicolon(;)";
            break;
        case token_type::real_const:
            os << "real_const";
            break;
        case token_type::float_division:
            os << "float_division(/)";
            break;
        case token_type::unary:
            os << "unary(+ -)";
            break;
        case token_type::program:
            os << "program";
            break;
        case token_type::variable:
            os << "variable";
            break;
        case token_type::type_specification:
            os << "type_specification";
            break;
        case token_type::comma:
            os << "comma(,)";
            break;
        case token_type::colon:
            os << "colon(:)";
            break;
        case token_type::identifier:
            os << "identifier";
            break;
        default:
            os << "token no implement to_string(). ";
            os << "token code: " << as_integer(type);
    }
    return os;
}
