#include <string>
#include <iostream>
#include <any>
#include <stack>
#include <utility>
#include <vector>
#include <unordered_set>

using namespace std;


template<typename Enumeration>
auto as_integer(Enumeration const value)
-> typename std::underlying_type<Enumeration>::type {
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

enum class token_type {
    integer_const, real_const,
    left_parenthesis, right_parenthesis,
    plus, minus, multiplication, division,
    unary,
    eof, unknown
};

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
        case token_type::division:
            os << "division(/)";
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
        case token_type::real_const:
            os << "real_const";
            break;
        case token_type::unary:
            os << "unary(+ -)";
            break;
        default:
            os << "token no implement to_string(). ";
            os << "token code: " << as_integer(type);
    }
    return os;
}

struct token {
    token_type type = token_type::unknown;
    any value;
    string raw;
    int pos;

    token(token_type type = token_type::unknown, string value = ""s,
          int pos = 0) : type(type), raw(value), pos(pos) {
        if (type == token_type::integer_const) {
            this->value = atoi(value.c_str());
        } else if (type == token_type::real_const) {
            this->value = atof(value.c_str());
        } else {
            this->value = value;
        }
    }


    template<typename T>
    T get_value() const {
        return std::any_cast<T>(value);
    }

    friend ostream &operator<<(ostream &os, const token &token) {
        os << "type: " << token.type << " value: " << token.get_value<string>();
        return os;
    }

    bool operator==(const token &rhs) const {
        if (type != rhs.type) return false;
        return raw == rhs.raw;
    }

    bool operator!=(const token &rhs) const {
        return !(rhs == *this);
    }
};
namespace token_constant {
    const token eof = token(token_type::eof, "-1");
    const token plus = token(token_type::plus, "+");
    const token minus = token(token_type::minus, "-");
    const token multiplication = token(token_type::multiplication, "*");
    const token division = token(token_type::division, "/");
    const token left_parenthesis = token(token_type::left_parenthesis, "(");
    const token right_parenthesis = token(token_type::right_parenthesis, ")");

    const std::unordered_map<char, token> single_char_token_map = {
            {plus.get_value<string>()[0],              plus},
            {minus.get_value<string>()[0],             minus},
            {multiplication.get_value<string>()[0],    multiplication},
            {division.get_value<string>()[0],          division},
            {left_parenthesis.get_value<string>()[0],  left_parenthesis},
            {right_parenthesis.get_value<string>()[0], right_parenthesis},
    };
}
class calculator {
public:
    explicit calculator(string text) : _text(std::move(text)) {}

    int eval() {
        std::stack<int> operands;
        std::stack<token_type> operators;
        unordered_set<token_type> operators_set = {
                token_type::plus, token_type::minus,
                token_type::multiplication, token_type::division
        };
        unordered_set<token_type> valid_token_set = operators_set;
        valid_token_set.insert(token_type::integer_const);
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

        _cur_token = get_next_token();
        while (_cur_token != token_constant::eof) {
            operands.push(_cur_token.get_value<int>());
            eat(token_type::integer_const);
            if (_cur_token == token_constant::eof) break;
            if (operators_set.find(_cur_token.type) != operators_set.end()) {
                while (!operators.empty()) {
                    auto row_index = token_type_index[_cur_token.type];
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
                operators.push(_cur_token.type);
                eat(_cur_token.type);
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
    inline void advance() { _pos++; }

    token get_next_token() {
        if (_pos >= _text.size()) return token_constant::eof;
        while (_text[_pos] == ' ') {
            advance();
        }
        if (isdigit(_text[_pos])) {
            auto start = _pos;
            while (isdigit(_text[_pos])) {
                advance();
            }
            return token(token_type::integer_const, _text.substr(start, _pos - start), start);
        }
        auto iter = token_constant::single_char_token_map.find(_text[_pos]);
        if (iter != token_constant::single_char_token_map.end()) {
            auto ret = iter->second;
            advance();
            return ret;
        }
        return token(token_type::unknown, _text.substr(_pos, 1), _pos);
    }

    void eat(token_type type) {
        if (_cur_token.type == type) {
            _cur_token = get_next_token();
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
            case token_type::division:
                return a / b;
            default:
                break;
        }
        return -1;
    }

    void error(string msg, token_type type) {
        std::cout << "Error: " << msg << std::endl;
        std::cout << _text << std::endl;
        for (int i = 0; i < _cur_token.pos; i++) {
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
        std::cout << "current type: " << _cur_token.type << std::endl;
        std::cout << "current value: " << _cur_token.get_value<string>() << std::endl;
        exit(1);
    }

private:
    token _cur_token;
    string _text;
    int _pos = 0;
};

#ifndef CATCH_CONFIG_MAIN
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