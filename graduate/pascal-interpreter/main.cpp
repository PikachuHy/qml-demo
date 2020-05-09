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
int f(int n) {
    if (n == 0) return 1;
    return n * f(n-1);
}
int main() {
    for(int i=0;i<17;i++) {
        std::cout << i << "! =" << f(i) << std::endl;
    }
    return 0;
}