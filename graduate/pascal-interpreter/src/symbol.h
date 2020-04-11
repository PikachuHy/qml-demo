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
#include "fifo_map.hpp"
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
    builtin_type_symbol(const std::string &name) : symbol(name) {}


    string to_string() const override {
        return name;
    }
};
struct variable_symbol: public symbol {
    variable_symbol(std::string name, symbol *type): symbol(std::move(name), type) {}

    string to_string() const override {
        std::string ret;
        ret += "<"s;
        ret += name;
        ret += ":"s;
        ret += type->to_string();
        ret += ">"s;
        return ret;
    }
};

class symbol_table {
public:
    void define(symbol* symbol) {
        std::string log;
        log += "Define: ";
        log += symbol->to_string();
        logger.push_back(log);
        symbols[symbol->name] = symbol;
    }
    symbol* lookup(const std::string & name) {
        std::string log;
        log += "Lookup: ";
        log += name;
        logger.push_back(log);
        return symbols[name];
    }
    std::string to_string() {
        std::string ret;
        ret += "Symbols: "s;
        ret += "["s;
        for(auto [k, v] : symbols) {
            ret += v->to_string();
            ret += ", ";
        }
        ret += "]"s;
        return ret;
    }
    const vector<string> & get_log() { return logger;}
private:
    std::vector<std::string> logger;
//    std::unordered_map<std::string, symbol*> symbols;
    nlohmann::fifo_map<std::string, symbol*> symbols;
};
#endif //PASCAL_INTERPRETER_SYMBOL_H
