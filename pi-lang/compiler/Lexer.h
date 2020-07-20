//
// Created by pikachu on 2020/7/20.
//

#ifndef PI_LANG_LEXER_H
#define PI_LANG_LEXER_H
#include <string>
#include <unordered_map>
using namespace std;
enum class Tag {
    AND = 256, BASIC, BREAK, DO, ELSE,
    EQ, FALSE, GE, ID, IF,
    INDEX, LE, MINUS, NE, NUM,
    OR, REAL, TEMP, TRUE, WHILE
};

struct Token {
    Token(Tag tag);
    Token(char ch);
    const Tag tag;
    virtual string toString() const;
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
struct Type: public Word {
    Type(string s, Tag tag, int width);
    static bool numeric(const Type* p);
    static const Type* max(const Type* p1, const Type* p2);
    const int width;
    const static Type Int, Float, Char, Bool;
};
struct Array : public Type {
    Array(int size, Type* type);
    Type* of;
    int size;
};
struct Real: public Token {
    Real(float value);
    const float value;
};

class Word_hash
{
public:
    size_t operator()(const Word& word) const {
        return hash<string>()(word.lexeme) ^ hash<Tag>()(word.tag);
    }

};

class Lexer {
public:
    Lexer();
    void reserve(const Word* w);
    const Token* scan();
    static int line;
    char peek;
    unordered_map<string, const Word*> words;
private:
    void readch();
    bool readch(char ch);
    int offset;
    string sourceCode;
};


#endif //PI_LANG_LEXER_H
