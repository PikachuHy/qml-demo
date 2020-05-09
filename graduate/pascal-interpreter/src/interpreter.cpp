//
// Created by pikachu on 2020/4/9.
//

#include "common.h"
#include "interpreter.h"
#include <Neargye/magic_enum.hpp>
#include <utility>
#include <functional>
#define ERROR_LOG(msg) std::cerr << __FILE__ << ":" << __LINE__ << " " << msg << std::endl; \
exit(1);


int interpreter::interpret() {
    auto ast = _parser.parse();
    ast->accept(this);
    return 0;
}

void interpreter::visit(program_node *node) {
    auto table = new scoped_symbol_table(node->name, cur_table);
    tables.push_back(table);
    cur_table = table;
    auto ar = new activation_record(node->name, activation_record_type::program, 1, _trace_memory);

    _call_stack.push(ar);
    node->child->accept(this);
    _call_stack.pop();

    tables.pop_back();
    if (_trace_symbol)
        cur_table->print();
    delete cur_table;
    cur_table = tables.back();

}

void interpreter::visit(procedure_or_function_call_node *node) {
    auto node_symbol = cur_table->lookup(node->name);
    if (node_symbol->symbol_type == symbol_type_enum::procedure_symbol) {
        procedure_call(node, (procedure_symbol*)node_symbol);
    } else if (node_symbol->symbol_type == symbol_type_enum::function_symbol) {

    } else if (node_symbol->symbol_type == symbol_type_enum::builtin_procedure_symbol) {
        if (node_symbol->name == "writeln") {
            auto print_val = [](const auto & val) {
                std::cout << val;
            };
            for(auto it: node->params) {
                auto val = eval_node(it);
                std::visit(print_val, val);
            }
            std::cout << std::endl;
        } else {
            ERROR_LOG(fmt::format("unimplement builtin procedure: {} ", node_symbol->name));
        }
    } else {
        ERROR_LOG(fmt::format("unknown symbol type: {}", magic_enum::enum_name(node_symbol->symbol_type)));
    }
}

void interpreter::visit(variable_declaration_node *node) {
    auto type = cur_table->lookup(node->get_type());
    cur_table->insert(new variable_symbol(node->get_name(), type));
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
        case token_type::equality: {
            return a == b;
        }
        default:
            auto msg = "unknown op"s;
            SPDLOG_ERROR(msg);
            std::cerr << msg << std::endl;
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
            auto msg = "unknown op"s;
            SPDLOG_ERROR(msg);
            std::cerr << msg << std::endl;
            exit(1);
    }
}


eval_ret interpreter::eval_binary_operator(ast *node) {
    auto op = (binary_operator*)node;
    auto left = eval_node(op->left);
    auto right = eval_node(op->right);
    return cal(left, right, op->op.type);
}

interpreter::interpreter(const string &text, bool trace_symbol, bool trace_memory)
:_parser(lexer(text)), _trace_symbol(trace_symbol), _trace_memory(trace_memory),
_call_stack(trace_memory){
    eval_table[ast_node_type::number] = [this](ast* node){ return this->eval_number(node);};
    eval_table[ast_node_type::string_node] = [this](ast* node){ return this->eval_string_node(node);};
    eval_table[ast_node_type::bool_expr_node] = [this](ast* node){ return this->eval_bool(node);};
    eval_table[ast_node_type::binary_operator] = [this](ast* node){ return this->eval_binary_operator(node);};
    eval_table[ast_node_type::variable_node] = [this](ast* node){ return this->eval_variable_node(node); };
    eval_table[ast_node_type::procedure_or_function_call_node] = [this](ast* node){ return this->eval_function_call(node); };
    cur_table = new builtin_symbol_table();
    tables.push_back(cur_table);
}

eval_ret interpreter::eval_node(ast *node) {
    if (eval_table.find(node->type) == eval_table.end()) {
        string msg = fmt::format("unknown ast node type: {}", magic_enum::enum_name(node->type));
        SPDLOG_ERROR(msg);
        std::cerr << __FILE__ << ":" << __LINE__ << " " << msg << std::endl;
        exit(1);
    }
    return eval_table[node->type](node);
}

eval_ret interpreter::eval_variable_node(ast *node) {
    auto _node = (variable_node*)node;
    return _call_stack.top()->get(_node->id.raw);
}

void interpreter::visit(variable_node *node) {
    auto name = node->id.get_value<string>();
    auto type = cur_table->lookup(name);
}

void interpreter::visit(procedure_node *node) {
    auto proc = new procedure_symbol(node->name);
    cur_table->insert(proc);
    for(auto param : node->params) {
        auto type = cur_table->lookup(param->get_type());
        auto var_symbol = new variable_symbol(param->get_name(), type);
        proc->params.push_back(var_symbol);
    }
    proc->body = node->child;
}

void interpreter::visit(function_node *node) {
    auto func = new function_symbol(node->name);
    cur_table->insert(func);
    for(auto param : node->params) {
        auto type = cur_table->lookup(param->get_type());
        auto var_symbol = new variable_symbol(param->get_name(), type);
        func->params.push_back(var_symbol);
    }
    auto ret_symbol_type = cur_table->lookup(node->ret_type->value);
    auto ret_symbol = new variable_symbol(node->name, ret_symbol_type);
    func->ret_value = ret_symbol;
    func->body = node->child;
}

void interpreter::procedure_call(procedure_or_function_call_node *node, procedure_symbol *symbol) {

    auto ar = new activation_record(node->name, activation_record_type::procedure, _call_stack.top()->nesting_level()+1, _trace_memory);
    if (node->params.size() != symbol->params.size()) {
        auto msg = fmt::format("procedure params error, expect {} params, actual {} params",
                         symbol->params.size(), node->params.size());
        SPDLOG_ERROR(msg);
        std::cerr << msg << std::endl;
        exit(1);
    }
    auto table = new scoped_symbol_table(node->name, cur_table);
    auto params_size = node->params.size();
    for(int i=0;i<params_size;i++) {
        table->insert(symbol->params[i]);
        auto var = symbol->params[i]->name;
        auto val = eval_node(node->params[i]);
        ar->set(var, val);
    }
    tables.push_back(table);
    cur_table = table;
    _call_stack.push(ar);
    assert(symbol->body != nullptr);
    symbol->body->accept(this);
    _call_stack.pop();
    tables.pop_back();
    cur_table = tables.back();
}

eval_ret interpreter::eval_function_call(ast *node) {
    assert(node->type == ast_node_type::procedure_or_function_call_node);
    auto func_node = (procedure_or_function_call_node*)node;
    auto symbol = cur_table->lookup(func_node->name);
    assert(symbol->symbol_type == symbol_type_enum::function_symbol);
    auto func_symbol = (function_symbol*)symbol;
    return function_call(func_node, func_symbol);
}

eval_ret interpreter::function_call(procedure_or_function_call_node *node, function_symbol *symbol) {

    auto ar = new activation_record(node->name, activation_record_type::procedure, _call_stack.top()->nesting_level()+1, _trace_memory);
    if (node->params.size() != symbol->params.size()) {
        auto msg = fmt::format("procedure params error, expect {} params, actual {} params",
                               symbol->params.size(), node->params.size());
        SPDLOG_ERROR(msg);
        std::cerr << msg << std::endl;
        exit(1);
    }
    auto table = new scoped_symbol_table(node->name, cur_table);
    auto params_size = node->params.size();
    for(int i=0;i<params_size;i++) {
        table->insert(symbol->params[i]);
        auto var = symbol->params[i]->name;
        auto val = eval_node(node->params[i]);
        ar->set(var, val);
    }
    tables.push_back(table);
    cur_table = table;
    _call_stack.push(ar);
    assert(symbol->body != nullptr);
    symbol->body->accept(this);
    auto ret = _call_stack.top()->get(node->name);
    _call_stack.pop();
    tables.pop_back();
    cur_table = tables.back();
    return ret;
}

void interpreter::visit(for_node *node) {
    assert(node->init->type == ast_node_type::assignment);
    auto init = (assignment*)node->init;
    init->left->accept(this);
    auto loop = init->left->id.raw;
    int begin = get<0>(eval_node(init->right));
    int end = get<0>(eval_node(node->end));
    for (int i = begin; i <= end; ++i) {
        node->block->accept(this);
        _call_stack.top()->set(loop, i+1);
    }
}

eval_ret interpreter::eval_string_node(ast *node) {
    assert(node->type == ast_node_type::string_node);
    auto str_node = (string_node*)node;
    return str_node->value.raw;
}

void interpreter::visit(if_node *node) {
    if (eval_bool(node->condition)) {
        node->if_block->accept(this);
    } else {
        node->else_block->accept(this);
    }
}

bool interpreter::eval_bool(ast *node) {
    auto ret = eval_binary_operator(node);
    return get<bool>(ret);
}

activation_record::activation_record(string name, activation_record_type type,
        int nestingLevel, bool trace_memory)
        : name(std::move(name)), type(type),
          _nesting_level(nestingLevel), _trace_memory(trace_memory) {
    type_string = get_type_string();
}



void activation_record::print() {
    spdlog::info("{}: {} {}", _nesting_level, get_type_string(), name);
    auto get_string = [](const auto& val) {
        std::cout << val << std::endl;
    };
    for(const auto& [k, v]: memory) {
        std::cout << fmt::format("   {:<20}: ", k);
        std::visit(get_string, v);
    }
}

string activation_record::get_type_string() {
    auto str_view = magic_enum::enum_name(type);
    string str(str_view);
    transform(str.begin(),str.end(),str.begin(),::toupper);
    return str;
}

activation_record::~activation_record() {
}

void call_stack::print() {
    spdlog::info("CALL STACK");
    auto iter = records.rbegin();
    while (iter != records.rend()) {
        (*iter)->print();
        iter++;
    }
}

void call_stack::push(activation_record *ar, bool print_flag) {
    records.push_back(ar);
    if (_trace_memory) {
        std::cout << std::endl << std::endl;
        spdlog::info("ENTER: {} {}", ar->type_string, ar->name);
        print();
    }
}

void call_stack::pop() {
    auto ar = records.back();
    if (_trace_memory) {
        std::cout << std::endl << std::endl;
        spdlog::info("LEAVE: {} {}", ar->type_string, ar->name);
        print();
    }
    records.pop_back();
    delete ar;
}
