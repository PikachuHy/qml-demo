#include <string>
#include <iostream>
#include <any>

using namespace std;
#include "interpreter.h"
int main() {
    while (true) {
        try {
        std::cout << "cal> ";
        string s;
        getline(cin, s);
        if (s.empty()) continue;
        interpreter inter(s);
        std::cout << inter.interpret() << std::endl;
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}