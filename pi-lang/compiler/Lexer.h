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

    Tag tag;

    virtual string toString() const;
};

struct Num : public Token {
    Num(int value);

    int value;

    string toString() const override;
};

struct Word : public Token {
    Word(string lexeme, Tag tag);

    string lexeme;
    static Word *AND, *OR, *EQ, *NE, *LE, *GE, *MINUS, *TRUE, *FALSE, *TEMP;

    bool operator==(Word &rhs) const;

    string toString() const override;
};

struct Type : public Word {
    Type(string s, Tag tag, int width);

    static bool numeric(Type *p);

    static Type *max(Type *p1, Type *p2);

    int width;
    static Type *Int, *Float, *Char, *Bool;
};

struct Array : public Type {
    Array(int size, Type *type);

    Type *of;
    int size;
};

struct Real : public Token {
    Real(float value);

    float value;
};

class Word_hash {
public:
    size_t operator()(Word &word) {
        return hash<string>()(word.lexeme) ^ hash<Tag>()(word.tag);
    }

};

class Lexer {
public:
    Lexer();
    Lexer(string sourceCode);
    void reserve(Word *w);

    Token *scan();

    static int line;
    static int column;
    char peek = ' ';
    unordered_map<string, Word *> words;
private:
    void readch();

    bool readch(char ch);

    int offset;
    string sourceCode;
};


#endif //PI_LANG_LEXER_H
