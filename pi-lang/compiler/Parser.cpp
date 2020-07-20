//
// Created by pikachu on 2020/7/20.
//

#include "Parser.h"
#include <iostream>
Parser::Parser(const Lexer &lexer)
: lexer(lexer) {

}

void Parser::program() {
    // TODO: implement
    std::cout << "pi-lang compiler is under the development" << std::endl;
}

Node::Node() {
    lexline = Lexer::line;
}
int Node::labels = 0;
void Node::error(string s) const {
    std::cout << "ERROR: near line " << lexline << ": " << s << std::endl;
    exit(-1);
}

int Node::newlabel() {
    return ++labels;
}

void Node::emitlabel(int i) const {
    std::cout << "L" << i << ":";
}

void Node::emit(string s) const {
    std::cout << "\t" << s << std::endl;
}

Expr::Expr(const Token *token, const Type *type): op(token), type(type) {

}

void Expr::emitjumps(string test, int t, int f) const{
    if (t!=0 && f!=0) {
        emit("if " + test + " goto L" + to_string(t));
        emit("goto L" + to_string(f));
    } else if (t!=0) emit("if " + test + " goto L" + to_string(t));
    else if (f!=0) emit("iffalse " + test + " goto L" + to_string(t));
    else ; // nothing since both t and f fall through
}

void Expr::jumping(int t, int f) const {
    emitjumps(toString(), t, f);
}

string Expr::toString() const {
    return op->toString();
}

bool Expr::operator==(const Expr &rhs) const {
    return op == rhs.op &&
           type == rhs.type;
}

bool Expr::operator!=(const Expr &rhs) const {
    return !(rhs == *this);
}

const Expr *Op::reduce() {
    auto x = gen();
    auto t = new Temp(type);
    emit(t->toString() + " = " + x->toString());
    return t;
}

Temp::Temp(const Type *type): Expr(&Word::TEMP, type) {
    number = ++count;
}

string Temp::toString() const {
    return "t"+to_string(number);
}

Arith::Arith(const Token *token, const Expr *expr1, const Expr *expr2)
: Op(token, Type::max(expr1->type, expr2->type)), expr1(expr1), expr2(expr2) {
    if (type == nullptr) error("type error");
}

const Expr *Arith::gen() {
    return new Arith(op, expr1->reduce(), expr2->reduce());
}

string Arith::toString() const {
    return expr1->toString() + " " + op->toString() + " " + expr2->toString();
}

Unary::Unary(const Token *token, const Expr *expr)
: Op(token, Type::max(&Type::Int, expr->type)), expr(expr) {
    if (type == nullptr) error("type error");
}

const Expr *Unary::gen() {
    return new Unary(op, expr->reduce());
}

string Unary::toString() const {
    return op->toString() + " " + expr->toString();
}

Constant::Constant(const Token *token, const Type *type) : Expr(token, type) {

}
const Constant Constant::True = Constant(&Word::TRUE, &Type::Bool);
const Constant Constant::False = Constant(&Word::FALSE, &Type::Bool);
void Constant::jumping(int t, int f) const {
    if (*this == True && t != 0) emit("goto L" + to_string(t));
    else if (*this == False && f != 0) emit("goto L" + to_string(f));
}

Logical::Logical(const Token *token, const Expr *expr1, const Expr *expr2)
: Expr(token, check(expr1->type, expr2->type)), expr1(expr1), expr2(expr2) {
    if (type == nullptr) error("type error");
}

const Type *Logical::check(const Type* p1, const Type* p2) {
    if (*p1 == Type::Bool && *p2 == Type::Bool) return &Type::Bool;
    return nullptr;
}

const Expr *Logical::gen() {
    int f = newlabel();
    int a = newlabel();
    auto temp = new Temp(type);
    jumping(0,f);
    emit(temp->toString() + " = true");
    emit("goto L" + to_string(a));
    emitlabel(f);
    emit(temp->toString() + " = false");
    emitlabel(a);

    return temp;
}

string Logical::toString() const {
    return expr1->toString() + " " + op->toString() + " " + expr2->toString();
}
