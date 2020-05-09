//
// Created by pikachu on 2020/4/11.
//

#include <iostream>
#include <string>
#include <utility>
#include <exception>
#include <vector>
#include <climits>
#include <numeric>
#include <algorithm>
// https://github.com/gabime/spdlog
using namespace std;
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <execinfo.h>
#include <fmt/format.h>
#include "parser.h"
#include "ast_visualizer.h"
#include <variant>
auto get_val = [](const auto & val) {
    std::cout << val << std::endl;
    return val;
};
int main() {
    variant<int, float> a = 5.5f;
    variant<int, float> b = 3;
//    auto c = visit(get_val, a) ;//- visit(get_val, b);
//    auto c = get(a);
    auto c = get<float>(a);
    std::cout << c << std::endl;
    auto d = std::visit(get_val, a);
    std::cout << d << std::endl;
    return 0;
}