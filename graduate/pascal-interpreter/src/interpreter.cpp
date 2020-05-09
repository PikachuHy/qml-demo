//
// Created by pikachu on 2020/4/9.
//

#include "common.h"
#include "interpreter.h"
#include <Neargye/magic_enum.hpp>
#include <utility>
#include <functional>

int interpreter::interpret() {
    auto ast = _parser.parse();
    ast->accept(this);
    return 0;
}

void interpreter::visit(program_node *node) {
    std::cout << std::endl;
    spdlog::info("ENTER: PROGRAM {}", node->name);
    auto ar = new activation_record(node->name, activation_record_type::program, 1);
    ar->print();
    std::cout << std::endl << std::endl;
    _call_stack.push(ar);
    node->child->accept(this);
    spdlog::info("LEAVE: PROGRAM {}", node->name);
    _call_stack.pop()->print();

}

void interpreter::visit(variable_declaration_node *node) {

}

void interpreter::visit(assignment *node) {
    if (node->left->type == ast_node_type::variable_node) {
        auto key = node->left->id.raw;
        auto value = eval_node(node->right);
        _call_stack.top()->set(key, value);
    } else {
        node->accept(this);
    }
}

eval_ret interpreter::eval_number(ast *node) {
    auto num = (number*)node;
    if (num->num.type == token_type::real_const) {
        return num->num.get_value<float>();
    } else {
        return num->num.get_value<int>();
    }
}
template <typename T>
eval_ret cal(T a, T b, token_type op) {

    switch (op) {
        case token_type::plus:
            return a + b;
        case token_type::minus:
            return a - b;
        case token_type::multiplication:
            return a * b;
        case token_type::integer_division: {
            int a_int = (int)a;
            int b_int = (int)b;
            return a_int / b_int;
        }
        case token_type::float_division: {
            auto a_f = (float)a;
            auto b_f = (float)b;
            return a_f / b_f;
        }
        default:
            SPDLOG_ERROR("unknown op");
            exit(1);
    }
}
eval_ret cal(eval_ret a, eval_ret b, token_type op) {
    if (a.index() == b.index() && a.index() == 0) {
        return cal(get<0>(a), get<0>(b), op);
    }
    float a_val;
    float b_val;
    if (a.index() == 0) a_val = get<0>(a);
    if (a.index() == 1) a_val = get<1>(a);
    if (b.index() == 0) b_val = get<0>(b);
    if (b.index() == 1) b_val = get<1>(b);
    switch (op) {
        case token_type::plus:
            return a_val + b_val;
        case token_type::minus:
            return a_val - b_val;
        case token_type::multiplication:
            return a_val * b_val;
        case token_type::integer_division: {
            int a_int = (int)a_val;
            int b_int = (int)b_val;
            return a_int / b_int;
        }
        case token_type::float_division: {
            auto a_f = (float)a_val;
            auto b_f = (float)b_val;
            return a_f / b_f;
        }
        default:
            SPDLOG_ERROR("unknown op");
            exit(1);
    }
}


eval_ret interpreter::eval_binary_operator(ast *node) {
    auto op = (binary_operator*)node;
    auto left = eval_node(op->left);
    auto right = eval_node(op->right);
    return cal(left, right, op->op.type);
}

interpreter::interpreter(const string &text):_parser(lexer(text)) {
    eval_table[ast_node_type::number] = [this](ast* node){ return this->eval_number(node);};
    eval_table[ast_node_type::binary_operator] = [this](ast* node){ return this->eval_binary_operator(node);};
    eval_table[ast_node_type::variable_node] = [this](ast* node){ return this->eval_variable_node(node); };
}

eval_ret interpreter::eval_node(ast *node) {
    if (eval_table.find(node->type) == eval_table.end()) {
        std::cerr << "unknown ast node type: " << magic_enum::enum_name(node->type) << std::endl;
        exit(1);
    }
    return eval_table[node->type](node);
}

eval_ret interpreter::eval_variable_node(ast *node) {
    auto _node = (variable_node*)node;
    return _call_stack.top()->get(_node->id.raw);
}

activation_record::activation_record(string name, activation_record_type type, int nestingLevel)
        : name(std::move(name)), type(type), nesting_level(nestingLevel) {}



void activation_record::print() {
    spdlog::info("CALL STACK");
    spdlog::info("{}: PROGRAM {}", nesting_level, name);
    auto get_string = [](const auto& val) {
        std::cout << val << std::endl;
    };
    for(const auto& [k, v]: memory) {
        std::cout << fmt::format("   {:<20}: ", k);
        std::visit(get_string, v);
    }
}
