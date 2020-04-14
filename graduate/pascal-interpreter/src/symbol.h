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
using namespace std;
struct symbol {
    std::string name;
    symbol* type;

    symbol(std::string name, symbol *type = nullptr) : name(std::move(name)), type(type) {}
    friend std::ostream &operator<<(std::ostream &os, const symbol *symbol) {
        os << symbol->to_string();
        return os;
    }
    virtual std::string to_string() const  = 0;
};
struct builtin_type_symbol: public symbol {
    builtin_type_symbol(const std::string name) : symbol(name) {}


    string to_string() const override;
};
struct variable_symbol: public symbol {
    variable_symbol(const std::string name, symbol *type): symbol(std::move(name), type) {}

    string to_string() const override;
};
struct procedure_symbol: public symbol {
    vector<variable_symbol*> params;

    explicit procedure_symbol(const string &name) : symbol(name) {}

    string to_string() const override;
};
class scoped_symbol_table {
public:
    explicit scoped_symbol_table(string name = "global", scoped_symbol_table *scope = nullptr);

    virtual ~scoped_symbol_table();

    void define(symbol* symbol);
    void insert(symbol* symbol);
    symbol* lookup(const std::string & name);
    std::string to_string();
    std::string to_table_string();
private:
//    std::unordered_map<std::string, symbol*> symbols;
    nlohmann::fifo_map<std::string, symbol*> symbols;
    std::string scope_name;
    int scope_level = 1;
    scoped_symbol_table* enclosing_scope = nullptr;
};
#endif //PASCAL_INTERPRETER_SYMBOL_H
