//
// Created by pikachu on 2020/4/11.
//

#include "symbol.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(symbol, to_string) {
    std::stringstream ss;
    std::string ret;
    auto int_type = builtin_type_symbol("INTEGER");
    ss << &int_type;
    ss >> ret;
    ASSERT_EQ(ret, "INTEGER");
    auto real_type = builtin_type_symbol("REAL");
    ret = "";
    ss.clear();
    ss << &real_type;
    ss >> ret;
    ASSERT_EQ(ret, "REAL");
    auto var_x_symbol = variable_symbol("x", &int_type);
    ret = "";
    ss.clear();
    ss << &var_x_symbol;
    ss >> ret;
    ASSERT_EQ(ret, "<x:INTEGER>");
    auto var_y_symbol = variable_symbol("y", &real_type);
    ret = "";
    ss.clear();
    ss << &var_y_symbol;
    ss >> ret;
    ASSERT_EQ(ret, "<y:REAL>");
}

TEST(symbol, symbol_table) {
    auto table = symbol_table();
    auto int_type = builtin_type_symbol("INTEGER");
    table.define(&int_type);
    ASSERT_EQ(table.to_string(), "Symbols: [INTEGER, ]");

    auto var_x_symbol = variable_symbol("x", &int_type);
    table.define(&var_x_symbol);
    ASSERT_EQ(table.to_string(), "Symbols: [INTEGER, <x:INTEGER>, ]");

    auto real_type = builtin_type_symbol("REAL");
    table.define(&real_type);
    ASSERT_EQ(table.to_string(), "Symbols: [INTEGER, <x:INTEGER>, REAL, ]");
    auto var_y_symbol = variable_symbol("y", &real_type);
    table.define(&var_y_symbol);
    ASSERT_EQ(table.to_string(), "Symbols: [INTEGER, <x:INTEGER>, REAL, <y:REAL>, ]");

    vector<string> log = {
            "Define: INTEGER",
            "Define: <x:INTEGER>",
            "Define: REAL",
            "Define: <y:REAL>"
    };
    ASSERT_EQ(log, table.get_log());
}