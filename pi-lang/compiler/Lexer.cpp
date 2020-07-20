//
// Created by pikachu on 2020/7/20.
//

#include "Lexer.h"

#include <utility>

Token::Token(Tag tag) : tag(tag) {

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

void Lexer::reserve(Word w) {
    words.insert(w);
}

Lexer::Lexer() {
    reserve(Word("if", Tag::IF));
    reserve(Word("else", Tag::ELSE));
    reserve(Word("while", Tag::WHILE));
    reserve(Word("do", Tag::DO));
    reserve(Word("break", Tag::BREAK));
    reserve(Word::TRUE);
    reserve(Word::FALSE);
    // TODO: type int char bool float
}
