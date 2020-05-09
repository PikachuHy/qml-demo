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
    auto table = new scoped_symbol_table("global", nullptr, true);
    auto int_type = builtin_type_symbol("INTEGER");
    table->define(&int_type);

    auto var_x_symbol = variable_symbol("x", &int_type);
    table->define(&var_x_symbol);

    auto real_type = builtin_type_symbol("REAL");
    table->define(&real_type);

    auto var_y_symbol = variable_symbol("y", &real_type);
    table->define(&var_y_symbol);

    std::cout << table->to_string() << std::endl;

    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(expect, output);
}


TEST(symbol, pascal_part11_1) {

    auto table = new builtin_symbol_table();
    spdlog::set_pattern("%v");
    testing::internal::CaptureStdout();
    auto expect = R"(
ENTER scope: Part11
Lookup: INTEGER. (Scope name: Part11)
Lookup: INTEGER. (Scope name: global)
Insert: x
Lookup: REAL. (Scope name: Part11)
Lookup: REAL. (Scope name: global)
Insert: y


SCOPE (SCOPED SYMBOL TABLE)
===========================
Scope name     : Part11
Scope level    : 1
Enclosing scope: global
Scope (Scoped symbol table) contents
------------------------------------
      x: <VarSymbol(name='x', type='INTEGER')>
      y: <VarSymbol(name='y', type='REAL')>


LEAVE scope: Part11
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
    auto visitor = symbol_node_visitor(table);
    node->accept(&visitor);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(expect, output);

}


TEST(symbol, pascal_part11_2) {
    auto table = new builtin_symbol_table();
    spdlog::set_pattern("%v");
    testing::internal::CaptureStdout();
    auto expect = R"(
ENTER scope: Part11
Lookup: INTEGER. (Scope name: Part11)
Lookup: INTEGER. (Scope name: global)
Insert: number
Lookup: INTEGER. (Scope name: Part11)
Lookup: INTEGER. (Scope name: global)
Insert: a
Lookup: INTEGER. (Scope name: Part11)
Lookup: INTEGER. (Scope name: global)
Insert: b
Lookup: REAL. (Scope name: Part11)
Lookup: REAL. (Scope name: global)
Insert: y
Lookup: number. (Scope name: Part11)
Lookup: a. (Scope name: Part11)
Lookup: number. (Scope name: Part11)
Lookup: b. (Scope name: Part11)
Lookup: a. (Scope name: Part11)
Lookup: number. (Scope name: Part11)
Lookup: y. (Scope name: Part11)


SCOPE (SCOPED SYMBOL TABLE)
===========================
Scope name     : Part11
Scope level    : 1
Enclosing scope: global
Scope (Scoped symbol table) contents
------------------------------------
 number: <VarSymbol(name='number', type='INTEGER')>
      a: <VarSymbol(name='a', type='INTEGER')>
      b: <VarSymbol(name='b', type='INTEGER')>
      y: <VarSymbol(name='y', type='REAL')>


LEAVE scope: Part11
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
    auto visitor = symbol_node_visitor(table);
    node->accept(&visitor);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(expect, output);
}

TEST(symbol, pascal_part14_1) {
    spdlog::set_pattern("%v");
    auto table = new builtin_symbol_table();
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
ENTER scope: Main
Lookup: REAL. (Scope name: Main)
Lookup: REAL. (Scope name: global)
Insert: x
Lookup: REAL. (Scope name: Main)
Lookup: REAL. (Scope name: global)
Insert: y
Insert: Alpha
ENTER scope: Alpha
Lookup: INTEGER. (Scope name: Alpha)
Lookup: INTEGER. (Scope name: Main)
Lookup: INTEGER. (Scope name: global)
Insert: a
Lookup: INTEGER. (Scope name: Alpha)
Lookup: INTEGER. (Scope name: Main)
Lookup: INTEGER. (Scope name: global)
Insert: y
Lookup: x. (Scope name: Alpha)
Lookup: x. (Scope name: Main)
Lookup: a. (Scope name: Alpha)
Lookup: x. (Scope name: Alpha)
Lookup: x. (Scope name: Main)
Lookup: y. (Scope name: Alpha)


SCOPE (SCOPED SYMBOL TABLE)
===========================
Scope name     : Alpha
Scope level    : 2
Enclosing scope: Main
Scope (Scoped symbol table) contents
------------------------------------
      a: <VarSymbol(name='a', type='INTEGER')>
      y: <VarSymbol(name='y', type='INTEGER')>


LEAVE scope: Alpha


SCOPE (SCOPED SYMBOL TABLE)
===========================
Scope name     : Main
Scope level    : 1
Enclosing scope: global
Scope (Scoped symbol table) contents
------------------------------------
      x: <VarSymbol(name='x', type='REAL')>
      y: <VarSymbol(name='y', type='REAL')>
  Alpha: <ProcedureSymbol(name=Alpha, parameters=[<VarSymbol(name='a', type='INTEGER')>])>


LEAVE scope: Main
)";
    std::cout << std::endl;
    auto node = parser(lexer(code)).parse();
    auto visitor = symbol_node_visitor(table);
    node->accept(&visitor);
    std::string my_output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, my_output);
}


TEST(symbol, pascal_part14_2) {
    auto table = new builtin_symbol_table();
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
        auto visitor = symbol_node_visitor(table);
        node->accept(&visitor);
        ASSERT_FALSE(true);
    } catch (std::exception& e) {
        string msg = e.what();
        ASSERT_EQ("Error: Duplicate identifier 'a' found", msg);
    }
}


TEST(symbol, pascal) {

    auto table = new builtin_symbol_table();
    spdlog::set_pattern("%v");
    testing::internal::CaptureStdout();
    auto expect = R"(
ENTER scope: factorial
Insert: factorial
ENTER scope: factorial
Lookup: INTEGER. (Scope name: factorial)
Lookup: INTEGER. (Scope name: factorial)
Lookup: INTEGER. (Scope name: global)
Insert: n
Lookup: LONGINT. (Scope name: factorial)
Lookup: LONGINT. (Scope name: factorial)
Lookup: LONGINT. (Scope name: global)
Insert: factorial
Lookup: n. (Scope name: factorial)
Lookup: factorial. (Scope name: factorial)
Lookup: factorial. (Scope name: factorial)
Lookup: n. (Scope name: factorial)
Lookup: factorial. (Scope name: factorial)
Lookup: n. (Scope name: factorial)


SCOPE (SCOPED SYMBOL TABLE)
===========================
Scope name     : factorial
Scope level    : 2
Enclosing scope: factorial
Scope (Scoped symbol table) contents
------------------------------------
      n: <VarSymbol(name='n', type='INTEGER')>
factorial: <VarSymbol(name='factorial', type='LONGINT')>


LEAVE scope: factorial
Lookup: INTEGER. (Scope name: factorial)
Lookup: INTEGER. (Scope name: global)
Insert: n
Lookup: n. (Scope name: factorial)
Lookup: writeln. (Scope name: factorial)
Lookup: writeln. (Scope name: global)
Lookup: n. (Scope name: factorial)
Lookup: factorial. (Scope name: factorial)
Lookup: n. (Scope name: factorial)


SCOPE (SCOPED SYMBOL TABLE)
===========================
Scope name     : factorial
Scope level    : 1
Enclosing scope: global
Scope (Scoped symbol table) contents
------------------------------------
factorial: <FunctionSymbol(name=factorial, parameters=[<VarSymbol(name='n', type='INTEGER')>], return_type=LONGINT)>
      n: <VarSymbol(name='n', type='INTEGER')>


LEAVE scope: factorial
)";
    std::string source_code = R"(
program factorial;

function factorial(n: integer): longint;
begin
    if n = 0 then
        factorial := 1
    else
        factorial := n * factorial(n - 1);
end;

var
    n: integer;

begin
    for n := 0 to 16 do
        writeln(n, '! = ', factorial(n));
end.
    )";
    std::cout << std::endl;
    auto node = parser(lexer(source_code)).parse();
    auto visitor = symbol_node_visitor(table);
    node->accept(&visitor);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(expect, output);
}