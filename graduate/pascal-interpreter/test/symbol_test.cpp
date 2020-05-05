//
// Created by pikachu on 2020/4/11.
//

#include "common.h"
#include "symbol.h"
#include "parser.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(symbol, to_string) {
    spdlog::set_pattern("%v");
    testing::internal::CaptureStdout();
    auto expect = R"(
<BuiltinTypeSymbol(name='INTEGER')>
<BuiltinTypeSymbol(name='REAL')>
<VarSymbol(name='x', type='INTEGER')>
<VarSymbol(name='y', type='REAL')>
)";
    std::cout << std::endl;
    auto int_type = new builtin_type_symbol("INTEGER");
    std::cout << int_type << std::endl;
    auto real_type = new builtin_type_symbol("REAL");
    std::cout << real_type << std::endl;
    auto var_x_symbol = new variable_symbol("x", int_type);
    std::cout << var_x_symbol << std::endl;
    auto var_y_symbol = new variable_symbol("y", real_type);
    std::cout << var_y_symbol << std::endl;
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(expect, output);
}

TEST(symbol, symbol_table) {
    spdlog::set_pattern("%v");
    testing::internal::CaptureStdout();
    auto expect = R"(
ENTER scope: global
Define: <BuiltinTypeSymbol(name='INTEGER')>
Define: <VarSymbol(name='x', type='INTEGER')>
Define: <BuiltinTypeSymbol(name='REAL')>
Define: <VarSymbol(name='y', type='REAL')>
Symbols: [<BuiltinTypeSymbol(name='INTEGER')>, <VarSymbol(name='x', type='INTEGER')>, <BuiltinTypeSymbol(name='REAL')>, <VarSymbol(name='y', type='REAL')>, ]
)";
    std::cout << std::endl;
    auto table = scoped_symbol_table();
    auto int_type = builtin_type_symbol("INTEGER");
    table.define(&int_type);

    auto var_x_symbol = variable_symbol("x", &int_type);
    table.define(&var_x_symbol);

    auto real_type = builtin_type_symbol("REAL");
    table.define(&real_type);

    auto var_y_symbol = variable_symbol("y", &real_type);
    table.define(&var_y_symbol);

    std::cout << table.to_string() << std::endl;

    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(expect, output);
}


TEST(symbol, pascal_part11_1) {
    spdlog::set_pattern("%v");
    testing::internal::CaptureStdout();
    auto expect = R"(
ENTER scope: global
Insert: INTEGER
Insert: REAL
Lookup: INTEGER. (Scope name: global)
Insert: x
Lookup: REAL. (Scope name: global)
Insert: y
Symbols: [<BuiltinTypeSymbol(name='INTEGER')>, <BuiltinTypeSymbol(name='REAL')>, <VarSymbol(name='x', type='INTEGER')>, <VarSymbol(name='y', type='REAL')>, ]
)";

    auto code = R"(
PROGRAM Part11;
VAR
   x : INTEGER;
   y : REAL;

BEGIN

END.
)";
    std::cout << std::endl;
    auto node = parser(lexer(code)).parse();
    auto table = new scoped_symbol_table();
    auto visitor = symbol_node_visitor(table);
    node->accept(&visitor);
    std::cout << table->to_string() << std::endl;
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(expect, output);

}


TEST(symbol, pascal_part11_2) {
    spdlog::set_pattern("%v");
    testing::internal::CaptureStdout();
    auto expect = R"(
ENTER scope: global
Insert: INTEGER
Insert: REAL
Lookup: INTEGER. (Scope name: global)
Insert: number
Lookup: INTEGER. (Scope name: global)
Insert: a
Lookup: INTEGER. (Scope name: global)
Insert: b
Lookup: REAL. (Scope name: global)
Insert: y
Lookup: number. (Scope name: global)
Lookup: a. (Scope name: global)
Lookup: number. (Scope name: global)
Lookup: b. (Scope name: global)
Lookup: a. (Scope name: global)
Lookup: number. (Scope name: global)
Lookup: y. (Scope name: global)
Symbols: [<BuiltinTypeSymbol(name='INTEGER')>, <BuiltinTypeSymbol(name='REAL')>, <VarSymbol(name='number', type='INTEGER')>, <VarSymbol(name='a', type='INTEGER')>, <VarSymbol(name='b', type='INTEGER')>, <VarSymbol(name='y', type='REAL')>, ]
)";
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
    std::cout << std::endl;
    auto node = parser(lexer(code)).parse();
    auto table = new scoped_symbol_table();
    auto visitor = symbol_node_visitor(table);
    node->accept(&visitor);
    std::cout << table->to_string() << std::endl;
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(expect, output);
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
    auto output = R"(
ENTER scope: global
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
    std::cout << std::endl;
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


TEST(symbol, pascal_part14_2) {
    auto code = R"(
program Main;
   var x, y: real;

   procedure Alpha(a : integer);
      var y : integer;
      var a : real;  { ERROR here! }
   begin
      x := a + x + y;
   end;

begin { Main }

end.  { Main }
)";
    try {
        auto node = parser(lexer(code)).parse();
        auto table = new scoped_symbol_table();
        auto visitor = symbol_node_visitor(table);
        node->accept(&visitor);
        ASSERT_FALSE(true);
    } catch (std::exception& e) {
        string msg = e.what();
        ASSERT_EQ("Error: Duplicate identifier 'a' found", msg);
    }
}

