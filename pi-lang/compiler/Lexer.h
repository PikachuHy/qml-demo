//
// Created by pikachu on 2020/7/20.
//

#ifndef PI_LANG_LEXER_H
#define PI_LANG_LEXER_H
#include <string>
#include <unordered_set>
using namespace std;
enum class Tag {
    AND = 256, BASIC, BREAK, DO, ELSE,
    EQ, FALSE, GE, ID, IF,
    INDEX, LE, MINUS, NE, NUM,
    OR, REAL, TEMP, TRUE, WHILE
};

struct Token {
    Token(Tag tag);
    const Tag tag;
};
struct Num : public Token{
    Num(int value);
    const int value;
};
struct Word: public Token {
    Word(string lexeme, Tag tag);

    const string lexeme;
    const static Word AND, OR, EQ, NE, LE, GE, MINUS, TRUE, FALSE, TEMP;

    bool operator==(const Word &rhs) const;

    bool operator!=(const Word &rhs) const;
};
struct Real: public Token {
    Real(float value);
    const float value;
};
class Lexer {
public:
    Lexer();
    void reserve(Word w);
    static int line;
    char peak;
    unordered_set<Word> words;

};


#endif //PI_LANG_LEXER_H
