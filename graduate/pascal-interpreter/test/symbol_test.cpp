//
// Created by pikachu on 2020/4/11.
//

#include "common.h"
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
    auto table = scoped_symbol_table();
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
    auto table = new scoped_symbol_table();
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
    auto expect = "Symbols: [INTEGER, REAL, <x:INTEGER>, <y:REAL>, ]";
    ASSERT_EQ(expect, table->to_string());

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
    auto table = new scoped_symbol_table();
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
    auto expect = "Symbols: [INTEGER, REAL, <number:INTEGER>, <a:INTEGER>, <b:INTEGER>, <y:REAL>, ]";
    ASSERT_EQ(expect, table->to_string());
}

TEST(symbol, pascal_part14_1) {
    spdlog::set_pattern("%v");
    testing::internal::CaptureStdout();
    auto code = R"(
program Main;
   var x, y: real;

   procedure Alpha(a : integer);
      var y : integer;
   begin
      x := a + x + y;
   end;

begin { Main }

end.  { Main }
)";
    auto output = R"(ENTER scope: global
Insert: INTEGER
Insert: REAL
Lookup: REAL. (Scope name: global)
Insert: x
Lookup: REAL. (Scope name: global)
Insert: y
Insert: Alpha
ENTER scope: Alpha
Lookup: INTEGER. (Scope name: Alpha)
Lookup: INTEGER. (Scope name: global)
Insert: a
Lookup: INTEGER. (Scope name: Alpha)
Lookup: INTEGER. (Scope name: global)
Insert: y
Lookup: x. (Scope name: Alpha)
Lookup: x. (Scope name: global)
Lookup: a. (Scope name: Alpha)
Lookup: x. (Scope name: Alpha)
Lookup: x. (Scope name: global)
Lookup: y. (Scope name: Alpha)


SCOPE (SCOPED SYMBOL TABLE)
===========================
Scope name     : Alpha
Scope level    : 2
Enclosing scope: global
Scope (Scoped symbol table) contents
------------------------------------
      a: <VarSymbol(name='a', type='INTEGER')>
      y: <VarSymbol(name='y', type='INTEGER')>


LEAVE scope: Alpha


SCOPE (SCOPED SYMBOL TABLE)
===========================
Scope name     : global
Scope level    : 1
Enclosing scope: None
Scope (Scoped symbol table) contents
------------------------------------
INTEGER: <BuiltinTypeSymbol(name='INTEGER')>
   REAL: <BuiltinTypeSymbol(name='REAL')>
      x: <VarSymbol(name='x', type='REAL')>
      y: <VarSymbol(name='y', type='REAL')>
  Alpha: <ProcedureSymbol(name=Alpha, parameters=[<VarSymbol(name='a', type='INTEGER')>])>


LEAVE scope: global
)";
    auto node = parser(lexer(code)).parse();
    auto table = new scoped_symbol_table();
    auto visitor = symbol_node_visitor(table);
    node->accept(&visitor);

    auto table_string = table->to_table_string();
    std::cout << std::endl << std::endl;
    std::cout << table_string << std::endl << std::endl;
    delete table;
    std::string my_output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, my_output);
}

