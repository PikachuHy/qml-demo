//
// Created by pikachu on 2020/4/11.
//
#include "common.h"
#include "symbol.h"
#include "token.h"


string function_symbol::to_string() const {
    std::string param_string;
    if (params.empty()) {
        param_string += "[]";
    } else {
        param_string += "[";
        for(int i=0;i<params.size()-1;i++) {
            param_string += fmt::format("{}, ", params[i]->to_string());
        }
        param_string += params.back()->to_string();
        param_string += "]";
    }
    assert(ret_value != nullptr);
    assert(ret_value->type != nullptr);
    return fmt::format("<FunctionSymbol(name={}, parameters={}, return_type={})>", name, param_string, ret_value->type->name);
}


string procedure_symbol::to_string() const {
    std::string param_string;
    if (params.empty()) {
        param_string += "[]";
    } else {
        param_string += "[";
        for(int i=0;i<params.size()-1;i++) {
            param_string += fmt::format("{}, ", params[i]->to_string());
        }
        param_string += params.back()->to_string();
        param_string += "]";
    }
    return fmt::format("<ProcedureSymbol(name={}, parameters={})>", name, param_string);
}

scoped_symbol_table::scoped_symbol_table(string name, scoped_symbol_table *scope, bool trace_symbol)
        : _scope_name(std::move(name)), _enclosing_scope(scope), _trace_symbol(trace_symbol) {
    if (_trace_symbol)
        spdlog::info("ENTER scope: {}", _scope_name);
    if (scope) {
        _scope_level = scope->_scope_level + 1;
    }
}

void scoped_symbol_table::define(symbol *symbol) {
    if (_trace_symbol)
        spdlog::info("Define: {}", symbol->to_string());
    _symbols[symbol->name] = symbol;
}

void scoped_symbol_table::insert(symbol *symbol) {
    if (_trace_symbol)
        spdlog::info("Insert: {}", symbol->name);
    if (_symbols.find(symbol->name) != _symbols.end()) {
        auto msg = fmt::format("Error: Duplicate identifier '{}' found", symbol->name);
        SPDLOG_ERROR(msg);
        std::cerr << msg << std::endl;
        throw invalid_semantic_exception(msg);
    }
    _symbols[symbol->name] = symbol;
}

symbol *scoped_symbol_table::lookup(const string &name) {
    if (_trace_symbol)
        spdlog::info("Lookup: {}. (Scope name: {})", name, _scope_name);
    if (_symbols.find(name) == _symbols.end()) {
        if (_enclosing_scope) return _enclosing_scope->lookup(name);

        SPDLOG_ERROR("Unknown type {}", name);
        std::cerr << __BASE_FILE__ << ":" << __LINE__ << " " << "Unknown type " << name << std::endl;
        exit(1);
    }
    return _symbols[name];
}

std::string scoped_symbol_table::to_string() {
    std::string ret;
    ret += "Symbols: "s;
    ret += "["s;
    for(auto [k, v] : _symbols) {
        ret += v->to_string();
        ret += ", ";
    }
    ret += "]"s;
    return ret;
}

std::string scoped_symbol_table::to_table_string() {
    std::string ret;
    std::string header = "SCOPE (SCOPED SYMBOL TABLE)"s;
    ret += header;
    ret += "\n"s;
    ret += string(header.size(), '=');
    ret += "\n"s;
    ret += fmt::format("Scope name     : {}\n", _scope_name);
    ret += fmt::format("Scope level    : {}\n", _scope_level);
    ret += fmt::format("Enclosing scope: {}\n", _enclosing_scope ? _enclosing_scope->_scope_name : "None"s);
    std::string content_header = "Scope (Scoped symbol table) contents";
    ret += content_header;
    ret += "\n"s;
    ret += string(content_header.size(), '-');
    ret += "\n"s;
    for(auto [k, v]: _symbols) {
        ret += fmt::format("{:>7}: {}\n", k, v->to_string());
    }
    return ret;
}

scoped_symbol_table::~scoped_symbol_table() {
    if (_trace_symbol) {
        print();
        spdlog::info("LEAVE scope: {}", _scope_name);
    }
}

void scoped_symbol_table::print() {
    std::cout << std::endl << std::endl;
    std::cout << to_table_string();
    std::cout << std::endl << std::endl;
}

string builtin_type_symbol::to_string() const {
    return fmt::format("<BuiltinTypeSymbol(name='{}')>", name);
}

string variable_symbol::to_string() const {
    return fmt::format("<VarSymbol(name='{}', type='{}')>", name, type->name);
}

string builtin_procedure_symbol::to_string() const {
    return fmt::format("<BuiltinProcedureSymbol(name='{}')>", name);
}

builtin_symbol_table::builtin_symbol_table() {
    auto int_type = new builtin_type_symbol("INTEGER");
    insert(int_type);
    auto real_type = new builtin_type_symbol("REAL");
    insert(real_type);
    insert(new builtin_type_symbol("LONGINT"));
    auto writeln_proc = new builtin_procedure_symbol("writeln");
    insert(writeln_proc);
}
