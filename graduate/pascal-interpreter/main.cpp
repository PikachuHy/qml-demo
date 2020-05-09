//
// Created by pikachu on 2020/4/11.
//

#include "interpreter.h"
#include <spdlog/spdlog.h>
#include <fstream>
#include <filesystem>
int main(int argc, char *argv[]) {
    if (argc == 2) {
        filesystem::path path(argv[1]);
        if (!filesystem::exists(path)) {
            SPDLOG_ERROR("file: {} is not exist", path.u8string());
            return 0;
        }
        ifstream fin(argv[1]);
        stringstream buffer;
        buffer << fin.rdbuf();
        string code(buffer.str());
        interpreter(code).interpret();
    } else {
        std::cout << "unimplement" << std::endl;
    }
    return 0;
}
