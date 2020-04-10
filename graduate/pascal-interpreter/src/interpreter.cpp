//
// Created by pikachu on 2020/4/9.
//

#include "interpreter.h"
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <stack>

/*
expr: term ((PLUS|MINUS) term)*
term: factor ((MUL|DIV) factor)*
factor: INTEGER
 */
int interpreter::expr() {
//    cur_token = get_next_token();
//    return expr_internal();
    return interpret();
}

int interpreter::expr_internal() {
    auto ret = term();
    while (cur_token.type == token_type::plus
           || cur_token.type == token_type::minus) {
        auto token = cur_token;
        if (token.type == token_type::plus) {
            eat(token.type);
            ret = ret + term();
        } else if (token.type == token_type::minus) {
            eat(token.type);
            ret = ret - term();
        }
    }
    return ret;
}

token interpreter::get_next_token() {
    return _lexer.get_next_token();
}

void interpreter::eat(token_type type) {
    if (cur_token.type == type) {
        cur_token = get_next_token();
        return;
    }
    error("Invalid syntax", type);
}

void interpreter::error(const std::unordered_set<token_type> &set) const {
    std::cout << "Error type." << std::endl;
    std::cout << "Expect: ";
    for (auto it: set) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    std::cout << "current type: " << cur_token.type << std::endl;
    std::cout << "current value: " << cur_token.get_value<string>() << std::endl;
    exit(1);
}

int interpreter::cal(int a, int b, token_type type) {
    switch (type) {
        case token_type::plus:
            return a + b;
        case token_type::minus:
            return a - b;
        case token_type::multiplication:
            return a * b;
        case token_type::division:
            return a / b;
        default:
            break;
    }
    return -1;
}

int interpreter::term() {
    auto ret = factor();
    while (cur_token.type == token_type::multiplication
           || cur_token.type == token_type::division) {
        auto token = cur_token;
        if (token.type == token_type::multiplication) {
            eat(token_type::multiplication);
            ret = ret * factor();
        } else if (token.type == token_type::division) {
            eat(token_type::division);
            ret = ret / factor();
        }
    }
    return ret;
}

int interpreter::factor() {
    auto token = this->cur_token;
    if (token.type == token_type::integer) {
        eat(token_type::integer);
        return token.get_value<int>();
    }
    eat(token_type::left_parenthesis);
    auto ret = expr_internal();
    eat(token_type::right_parenthesis);
    return ret;
}

int interpreter::cal_with_table() {
    std::stack<int> operands;
    std::stack<token_type> operators;
    unordered_set<token_type> operators_set = {
            token_type::plus, token_type::minus,
            token_type::multiplication, token_type::division
    };
    unordered_set<token_type> valid_token_set = operators_set;
    valid_token_set.insert(token_type::integer);
    std::vector<std::vector<int>> op_priority_table(4, std::vector<int>(4, 1));
    op_priority_table[3][0] = -1;
    op_priority_table[3][1] = -1;
    op_priority_table[2][0] = -1;
    op_priority_table[2][1] = -1;
    std::unordered_map<token_type, int> token_type_index = {
            {token_type::plus,           0},
            {token_type::minus,          1},
            {token_type::multiplication, 2},
            {token_type::division,       3},
    };

    cur_token = get_next_token();
    while (cur_token != token_constant::eof) {
        operands.push(factor());
        if (cur_token == token_constant::eof) break;
        if (operators_set.find(cur_token.type) != operators_set.end()) {
            while (!operators.empty()) {
                auto row_index = token_type_index[cur_token.type];
                auto col_index = token_type_index[operators.top()];
                if (op_priority_table[row_index][col_index] > 0) {
                    auto a = operands.top();
                    operands.pop();
                    auto b = operands.top();
                    operands.pop();
                    auto op = operators.top();
                    operators.pop();
                    auto c = cal(b, a, op);
                    operands.push(c);
                } else break;
            }
            operators.push(cur_token.type);
            eat(cur_token.type);
        } else {
            error(valid_token_set);
        }
    }
    while (!operators.empty()) {
        auto a = operands.top();
        operands.pop();
        if (operands.empty()) {
            error("Invalid syntax", token_type::integer);
        }
        auto b = operands.top();
        operands.pop();
        auto op = operators.top();
        operators.pop();
        auto c = cal(b, a, op);
        operands.push(c);
    }
    return operands.top();
}

int interpreter::interpret() {
    return _parser.parse()->accept(&visitor);
}

