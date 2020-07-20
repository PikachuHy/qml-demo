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

Real::Real(float value): Token(Tag::REAL), value(value) {

}
