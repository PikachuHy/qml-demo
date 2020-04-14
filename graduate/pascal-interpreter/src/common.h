//
// Created by pikachu on 2020/4/12.
//

#ifndef PASCAL_INTERPRETER_COMMON_H
#define PASCAL_INTERPRETER_COMMON_H
#include <spdlog/spdlog.h>
#include <fmt/format.h>
#include <string>
#include "token.h"
class invalid_syntax_exception: public std::exception {
public:
    explicit invalid_syntax_exception(std::string msg = "Invalid syntax") : msg(std::move(msg)) {}

    const char *what() {
        return msg.c_str();
    }

private:
    std::string msg;
};
class invalid_semantic_exception: public std::exception {
public:
    explicit invalid_semantic_exception(std::string msg) : msg(std::move(msg)) {}

    const char *what() {
        return msg.c_str();
    }

private:
    std::string msg;
};
#endif //PASCAL_INTERPRETER_COMMON_H
