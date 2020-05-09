//
// Created by pikachu on 2020/4/11.
//

#ifndef PASCAL_INTERPRETER_SYMBOL_H
#define PASCAL_INTERPRETER_SYMBOL_H
#include <string>
#include <any>
#include <ostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <nlohmann/fifo_map.hpp>
#include "token.h"
struct ast;
using namespace std;
enum class symbol_type_enum {
    procedure_symbol, function_symbol,
    builtin_procedure_symbol,
    unknown
};
struct symbol {
    std::string name;
    symbol* type;
    symbol_type_enum symbol_type = symbol_type_enum::unknown;

    symbol(std::string name, symbol *type = nullptr) : name(std::move(name)), type(type) {}
    friend std::ostream &operator<<(std::ostream &os, const symbol *symbol) {
        os << symbol->to_string();
        return os;
    }
    virtual std::string to_string() const  = 0;
};
struct builtin_type_symbol: public symbol {
    builtin_type_symbol(const std::string& name) : symbol(name) {}


    string to_string() const override;
};
struct builtin_procedure_symbol: public symbol {
    builtin_procedure_symbol(const std::string& name) : symbol(name) {
        symbol_type = symbol_type_enum::builtin_procedure_symbol;
    }


    string to_string() const override;
};
struct variable_symbol: public symbol {
    variable_symbol(const std::string& name, symbol *type): symbol(name, type) {}

    string to_string() const override;
};
struct procedure_symbol: public symbol {
    vector<variable_symbol*> params;
    ast* body;
    explicit procedure_symbol(const string &name, ast* body = nullptr) : symbol(name), body(body) {
        symbol_type = symbol_type_enum::procedure_symbol;
    }

    string to_string() const override;
};
struct function_symbol: public symbol {
    vector<variable_symbol*> params;
    ast* body;
    symbol* ret_value;
    explicit function_symbol(const string &name, ast* body = nullptr) : symbol(name), body(body) {
        symbol_type = symbol_type_enum::function_symbol;
    }

    string to_string() const override;
};
class scoped_symbol_table {
public:
    explicit scoped_symbol_table(string name = "global",
            scoped_symbol_table *scope = nullptr, bool trace_symbol = false);

    virtual ~scoped_symbol_table();

    void define(symbol* symbol);
    void insert(symbol* symbol);
    symbol* lookup(const std::string & name);
    std::string to_string();
    std::string to_table_string();
    void print();
    void trace_symbol(bool flag = true) { _trace_symbol = flag; }
private:
//    std::unordered_map<std::string, symbol*> symbols;
    nlohmann::fifo_map<std::string, symbol*> _symbols;
    std::string _scope_name;
    int _scope_level = 0;
    scoped_symbol_table* _enclosing_scope = nullptr;
    bool _trace_symbol;
};
class builtin_symbol_table: public scoped_symbol_table {
public:
    builtin_symbol_table();
};
#endif //PASCAL_INTERPRETER_SYMBOL_H
