//
// Created by pikachu on 2020/4/21.
//

#include <gtest/gtest.h>
#include "ast_visualizer.h"

TEST(ast_visualizer, sample) {
    string code = R"(
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
    auto ast = parser(lexer(code)).parse();
    ast_visualizer vis;
    ast->accept(&vis);
    string expect = R"(
digraph astgraph {
  node [shape=circle, fontsize=12, fontname="Courier", height=.1];
  ranksep=.3;
  edge [arrowsize=.5]

    node1 [label="program"]
    node2 [label="block"]
    node3 [label="func dec: factorial"]
    node4 [label="var dec"]
    node5 [label="n"]
    node6 [label="INTEGER"]
    node4->node5
    node4->node6
    node3->node4
    node7 [label="LONGINT"]
    node3->node7
    node8 [label="block"]
    node9 [label="noop"]
    node10 [label="compound"]
    node11 [label="if"]
    node12 [label="="]
    node13 [label="n"]
    node14 [label="0"]
    node12->node13
    node12->node14
    node15 [label="block"]
    node16 [label=":="]
    node17 [label="factorial"]
    node18 [label="1"]
    node16->node17
    node16->node18
    node15->node16
    node19 [label="block"]
    node20 [label=":="]
    node21 [label="factorial"]
    node22 [label="*"]
    node23 [label="n"]
    node24 [label="proc call: factorial"]
    node25 [label="-"]
    node26 [label="n"]
    node27 [label="1"]
    node25->node26
    node25->node27
    node24->node25
    node22->node23
    node22->node24
    node20->node21
    node20->node22
    node19->node20
    node11->node12
    node11->node15
    node11->node19
    node10->node11
    node8->node9
    node8->node10
    node3->node8
    node28 [label="var dec"]
    node29 [label="n"]
    node30 [label="INTEGER"]
    node28->node29
    node28->node30
    node31 [label="compound"]
    node32 [label="for"]
    node33 [label=":="]
    node34 [label="n"]
    node35 [label="0"]
    node33->node34
    node33->node35
    node36 [label="16"]
    node37 [label="proc call: writeln"]
    node38 [label="n"]
    node37->node38
    node39 [label="string const: ! = "]
    node37->node39
    node40 [label="proc call: factorial"]
    node41 [label="n"]
    node40->node41
    node37->node40
    node32->node33
    node32->node36
    node32->node37
    node31->node32
    node2->node3
    node2->node28
    node2->node31
    node1->node2
})";
    ASSERT_EQ(expect, vis.gen_dot());
}