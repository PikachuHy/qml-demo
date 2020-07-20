//
// Created by pikachu on 2020/7/20.
//
#include "Parser.h"
#include <iostream>
int main() {
    std::cout << "hello, pi-lang compiler" << std::endl;
    Lexer lexer;
    Parser parser(lexer);
    parser.program();
    std::cout << "Done!" << std::endl;
    return 0;
}