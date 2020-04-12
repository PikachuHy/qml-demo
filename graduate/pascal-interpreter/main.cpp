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
int main() {
    fmt::format("The answer is {}.", 43);
    fmt::print("The answer is {}. print", 43);
    return 0;
}