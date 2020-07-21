//
// Created by pikachu on 2020/7/20.
//
#include "Parser.h"
#include <iostream>
#include <fstream>
#include <cstring>

void read_file(const string& filename, string & filedata) {
    ifstream infile;
    char *fileBuffer = NULL;
    infile.open(filename,ios::binary);
    if(infile.is_open())
    {
        infile.seekg(0,ios::end);
        auto len = infile.tellg(); //获取文件长度
        infile.seekg(0, ios::beg); //设置读取位置为起始位置

        fileBuffer = new char[(size_t)len + 1];
        memset(fileBuffer,0,(size_t)len + 1);
        infile.read(fileBuffer,len);
        filedata = fileBuffer;
        delete [] fileBuffer;
        }

    infile.close();
}
int main(int argc, char *argv[]) {
    std::cout << "hello, pi-lang compiler" << std::endl;
    if (argc == 1) {
        std::cout << "Usage: pic <filename>" << std::endl;
        return 0;
    }
    string filename = argv[1];
    std::cout << "parse " << filename << std::endl;
    string filedata;
    read_file(filename, filedata);
    Lexer lexer(filedata);
    Parser parser(&lexer);
    parser.program();
    std::cout << "Done!" << std::endl;
    return 0;
}