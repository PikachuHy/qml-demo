//
// Created by pikachu on 2020/7/20.
//

#include "Lexer.h"

#include <utility>

Token::Token(Tag tag) : tag(tag) {

}

Token::Token(char ch) : tag(static_cast<const Tag>(ch)){
    // TODO: find a better way to receive char
}

Num::Num(int value) : Token(Tag::NUM), value(value) {

}

Word::Word(string lexeme, Tag tag) : Token(tag), lexeme(std::move(lexeme)) {

}
const Word Word::AND = Word("&&"s, Tag::AND);
const Word Word::OR = Word("||"s, Tag::OR);
const Word Word::EQ = Word("=="s, Tag::EQ);
const Word Word::NE = Word("!="s, Tag::NE);
const Word Word::LE = Word("<="s, Tag::LE);
const Word Word::GE = Word(">="s, Tag::GE);
const Word Word::MINUS = Word("-"s, Tag::MINUS);
const Word Word::TRUE = Word("true"s, Tag::TRUE);
const Word Word::FALSE = Word("false"s, Tag::FALSE);
const Word Word::TEMP = Word("t"s, Tag::TEMP);

bool Word::operator==(const Word &rhs) const {
    return tag == rhs.tag &&
           lexeme == rhs.lexeme;
}

bool Word::operator!=(const Word &rhs) const {
    return !(rhs == *this);
}

Real::Real(float value): Token(Tag::REAL), value(value) {

}
int Lexer::line = 1;

void Lexer::reserve(const Word* w) {
    words[w->lexeme] = w;
}

Lexer::Lexer() {
    reserve(new Word("if", Tag::IF));
    reserve(new Word("else", Tag::ELSE));
    reserve(new Word("while", Tag::WHILE));
    reserve(new Word("do", Tag::DO));
    reserve(new Word("break", Tag::BREAK));
    reserve(&Word::TRUE);
    reserve(&Word::FALSE);
    // TODO: type int char bool float
    offset = 0;
    peek = ' ';
}

void Lexer::readch() {
    peek = sourceCode[offset++];
}

bool Lexer::readch(char ch) {
    readch();
    if (peek != ch) return false;
    peek = ' ';
    return false;
}

const Token* Lexer::scan() {
    for(;;readch()) {
        if (peek == ' ' || peek == '\t') continue;
        else if (peek == '\n') line++;
        else break;
    }
    // parse && || == != <= >=
    switch (peek) {
        case '&': {
            if (readch('&')) return &Word::AND;
            else return new Token('&');
        }
        case '|': {
            if (readch('|')) return &Word::OR;
            else return new Token('|');
        }
        case '=': {
            if (readch('=')) return &Word::EQ;
            else return new Token('=');
        }
        case '!': {
            if (readch('=')) return &Word::NE;
            else return new Token('!');
        }
        case '<': {
            if (readch('=')) return &Word::LE;
            else return new Token('<');
        }
        case '>': {
            if (readch('=')) return &Word::GE;
            else return new Token('>');
        }
    }
    // int or float
    if (isdigit(peek)) {
        int v = 0;
        do {
            v = v * 10 + (peek - '0');
            readch();
        } while (isdigit(peek));
        if (peek != '.') return new Num(v);
        float x = v;
        float d = 10;
        for(;;) {
            readch();
            if (!isdigit(peek)) break;
            x+= (peek - '0') / d;
            d *= 10;
        }
        return new Real(x);
    }
    if (isalpha(peek)) {
        string s;
        do {
            s += peek;
            readch();
        } while (isalnum(peek));

        if (words.find(s) != words.end()) {
            return words[s];
        }
        auto w = new Word(s, Tag::ID);
        words[w->lexeme] = w;
        return w;
    }
    auto token = new Token(peek);
    peek = ' ';
    return token;
}
