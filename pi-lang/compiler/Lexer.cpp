//
// Created by pikachu on 2020/7/20.
//

#include "Lexer.h"

#include <utility>

Token::Token(Tag tag) : tag(tag) {

}

Token::Token(char ch) : tag(static_cast<Tag>(ch)) {
    // TODO: find a better way to receive char
}

string Token::toString() const {
    return ""s + (char) tag;
}

Num::Num(int value) : Token(Tag::NUM), value(value) {

}

Word::Word(string lexeme, Tag tag) : Token(tag), lexeme(std::move(lexeme)) {

}

Word *Word::AND = new Word("&&"s, Tag::AND);
Word *Word::OR = new Word("||"s, Tag::OR);
Word *Word::EQ = new Word("=="s, Tag::EQ);
Word *Word::NE = new Word("!="s, Tag::NE);
Word *Word::LE = new Word("<="s, Tag::LE);
Word *Word::GE = new Word(">="s, Tag::GE);
Word *Word::MINUS = new Word("-"s, Tag::MINUS);
Word *Word::TRUE = new Word("true"s, Tag::TRUE);
Word *Word::FALSE = new Word("false"s, Tag::FALSE);
Word *Word::TEMP = new Word("t"s, Tag::TEMP);

bool Word::operator==(Word &rhs) const {
    return tag == rhs.tag &&
           lexeme == rhs.lexeme;
}


Real::Real(float value) : Token(Tag::REAL), value(value) {

}

int Lexer::line = 1;
int Lexer::column = 0;

void Lexer::reserve(Word *w) {
    words[w->lexeme] = w;
}

Lexer::Lexer() {
    reserve(new Word("if", Tag::IF));
    reserve(new Word("else", Tag::ELSE));
    reserve(new Word("while", Tag::WHILE));
    reserve(new Word("do", Tag::DO));
    reserve(new Word("break", Tag::BREAK));
    reserve(Word::TRUE);
    reserve(Word::FALSE);
    // TODO: type int char bool float
    offset = 0;
    peek = ' ';
}

Lexer::Lexer(string sourceCode): sourceCode(sourceCode), offset(0), peek(' ') {

    reserve(new Word("if", Tag::IF));
    reserve(new Word("else", Tag::ELSE));
    reserve(new Word("while", Tag::WHILE));
    reserve(new Word("do", Tag::DO));
    reserve(new Word("break", Tag::BREAK));
    reserve(Word::TRUE);
    reserve(Word::FALSE);
    reserve(Type::Int);
    reserve(Type::Char);
    reserve(Type::Bool);
    reserve(Type::Float);
}
void Lexer::readch() {
    peek = sourceCode[offset++];
    column++;
}

bool Lexer::readch(char ch) {
    readch();
    if (peek != ch) return false;
    peek = ' ';
    return false;
}

Token *Lexer::scan() {
    for (;; readch()) {
        if (peek == ' ' || peek == '\t' || peek == '\r') continue;
        else if (peek == '\n') {
            line++;
            column = 1;
        }
        else break;
    }
    // parse && || == != <= >=
    switch (peek) {
        case '&': {
            if (readch('&')) return Word::AND;
            else return new Token('&');
        }
        case '|': {
            if (readch('|')) return Word::OR;
            else return new Token('|');
        }
        case '=': {
            if (readch('=')) return Word::EQ;
            else return new Token('=');
        }
        case '!': {
            if (readch('=')) return Word::NE;
            else return new Token('!');
        }
        case '<': {
            if (readch('=')) return Word::LE;
            else return new Token('<');
        }
        case '>': {
            if (readch('=')) return Word::GE;
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
        for (;;) {
            readch();
            if (!isdigit(peek)) break;
            x += (peek - '0') / d;
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


Type::Type(string s, Tag tag, int width) : Word(std::move(s), tag), width(width) {

}

Type *Type::Int = new Type("int", Tag::BASIC, 4);
Type *Type::Float = new Type("float", Tag::BASIC, 8);
Type *Type::Char = new Type("char", Tag::BASIC, 1);
Type *Type::Bool = new Type("bool", Tag::BASIC, 1);

bool Type::numeric(Type *p) {
    return *p == *Type::Char || *p == *Type::Int || *p == *Type::Float;
}

Type *Type::max(Type *p1, Type *p2) {
    if (!numeric(p1) || !numeric(p2)) return nullptr;
    if (*p1 == *Type::Float || *p2 == *Type::Float) return Type::Float;
    if (*p1 == *Type::Int || *p2 == *Type::Int) return Type::Int;
    return Type::Char;
}

Array::Array(int size, Type *type)
        : Type("[]"s, Tag::INDEX, size * type->width),
          size(size), of(type) {

}
