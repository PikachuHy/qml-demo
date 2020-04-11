#include <string>
#include <iostream>
#include <any>
#include <stack>
#include <utility>
#include <vector>
#include <unordered_set>
#include "token.h"
using namespace std;
class calculator {
public:
    explicit calculator(string text) : text(std::move(text)) {}
    int eval() {
        std::stack<int> operands;
        std::stack<token_type> operators;
        unordered_set<token_type> operators_set = {
                token_type::plus, token_type::minus,
                token_type::multiplication, token_type::integer_division
        };
        unordered_set<token_type> valid_token_set = operators_set;
        valid_token_set.insert(token_type::integer_const);
        std::vector<std::vector<int>> op_priority_table(4, std::vector<int>(4, 1));
        op_priority_table[3][0] = -1;
        op_priority_table[3][1] = -1;
        op_priority_table[2][0] = -1;
        op_priority_table[2][1] = -1;
        std::unordered_map<token_type, int> token_type_index = {
                {token_type::plus,             0},
                {token_type::minus,            1},
                {token_type::multiplication,   2},
                {token_type::integer_division, 3},
        };

        cur_token = get_next_token();
        while (cur_token != token_constant::eof) {
            operands.push(cur_token.get_value<int>());
            eat(token_type::integer_const);
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
                error("Invalid syntax", token_type::integer_const);
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

private:
    inline void advance() { pos++; }
    token get_next_token() {
        if (pos >= text.size()) return token_constant::eof;
        while (text[pos] == ' ') {
            advance();
        }
        if (isdigit(text[pos])) {
            auto start = pos;
            while (isdigit(text[pos])) {
                advance();
            }
            return {token_type::integer_const, text.substr(start, pos - start), start};
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
    void eat(token_type type) {
        if (cur_token.type == type) {
            cur_token = get_next_token();
            return;
        }
        error("Invalid syntax", type);
    }
    int cal(int a, int b, token_type type) {
        switch (type) {
            case token_type::plus:
                return a + b;
            case token_type::minus:
                return a - b;
            case token_type::multiplication:
                return a * b;
            case token_type::integer_division:
                return a / b;
            default:
                break;
        }
        return -1;
    }
    void error(string msg, token_type type) {
        std::cout << "Error: " << msg << std::endl;
        std::cout << text << std::endl;
        for(int i=0;i<cur_token.pos;i++) {
            std::cout << " ";
        }
        std::cout << "^" << std::endl;
        std::cout << "Expect " << type << std::endl;
        throw msg;
    }
    void error(const std::unordered_set<token_type> &set) const {
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
private:
    token cur_token;
    string text;
    int pos = 0;
};

#ifndef TEST
int main() {
    while (true) {
        try {
        std::cout << "cal> ";
        string s;
        getline(cin, s);
        if (s.empty()) continue;
        calculator cal(s);
        std::cout << cal.eval() << std::endl;
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}
#endif