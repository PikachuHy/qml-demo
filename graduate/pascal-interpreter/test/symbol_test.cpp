//
// Created by pikachu on 2020/4/11.
//

#include "symbol.h"
#include "parser.h"
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


TEST(symbol, pascal_part11_1) {

    auto code = R"(
PROGRAM Part11;
VAR
   x : INTEGER;
   y : REAL;

BEGIN

END.
)";
    auto node = parser(lexer(code)).parse();
    symbol_table table;
    auto visitor = symbol_node_visitor(table);
    node->accept(&visitor);
    vector<string> log = {
            "Define: INTEGER",
            "Define: REAL",
            "Lookup: INTEGER",
            "Define: <x:INTEGER>",
            "Lookup: REAL",
            "Define: <y:REAL>",
    };
    ASSERT_EQ(log, table.get_log());
    auto expect = "Symbols: [INTEGER, REAL, <x:INTEGER>, <y:REAL>, ]";
    ASSERT_EQ(expect, table.to_string());

}


TEST(symbol, pascal_part11_2) {

    auto code = R"(
PROGRAM Part11;
VAR
   number : INTEGER;
   a, b   : INTEGER;
   y      : REAL;

BEGIN {Part11}
   number := 2;
   a := number ;
   b := 10 * a + 10 * number DIV 4;
   y := 20 / 7 + 3.14
END.  {Part11}
)";
    auto node = parser(lexer(code)).parse();
    symbol_table table;
    auto visitor = symbol_node_visitor(table);
    node->accept(&visitor);
    vector<string> log = {
            "Define: INTEGER",
            "Define: REAL",
            "Lookup: INTEGER",
            "Define: <number:INTEGER>",
            "Lookup: INTEGER",
            "Define: <a:INTEGER>",
            "Lookup: INTEGER",
            "Define: <b:INTEGER>",
            "Lookup: REAL",
            "Define: <y:REAL>",
            "Lookup: number",
            "Lookup: a",
            "Lookup: number",
            "Lookup: b",
            "Lookup: a",
            "Lookup: number",
            "Lookup: y"
    };
    ASSERT_EQ(log, table.get_log());
    auto expect = "Symbols: [INTEGER, REAL, <number:INTEGER>, <a:INTEGER>, <b:INTEGER>, <y:REAL>, ]";
    ASSERT_EQ(expect, table.to_string());
}

