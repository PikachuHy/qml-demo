//
// Created by pikachu on 2020/7/20.
//

#include "Parser.h"
#include <iostream>

Parser::Parser(Lexer &lexer)
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

void Node::error(string s) {
    std::cout << "ERROR: near line " << lexline << ": " << s << std::endl;
    exit(-1);
}

int Node::newlabel() {
    return ++labels;
}

void Node::emitlabel(int i) {
    std::cout << "L" << i << ":";
}

void Node::emit(string s) {
    std::cout << "\t" << s << std::endl;
}

Expr::Expr(Token *token, Type *type) : op(token), type(type) {

}

void Expr::emitjumps(string test, int t, int f) {
    if (t != 0 && f != 0) {
        emit("if " + test + " goto L" + to_string(t));
        emit("goto L" + to_string(f));
    } else if (t != 0) emit("if " + test + " goto L" + to_string(t));
    else if (f != 0) emit("iffalse " + test + " goto L" + to_string(t));
    else; // nothing since both t and f fall through
}

void Expr::jumping(int t, int f) {
    emitjumps(toString(), t, f);
}

string Expr::toString() {
    return op->toString();
}

bool Expr::operator==(Expr &rhs) const {
    return op == rhs.op &&
           type == rhs.type;
}


Expr *Op::reduce() {
    auto x = gen();
    auto t = new Temp(type);
    emit(t->toString() + " = " + x->toString());
    return t;
}

Temp::Temp(Type *type) : Expr(Word::TEMP, type) {
    number = ++count;
}

string Temp::toString() {
    return "t" + to_string(number);
}

Arith::Arith(Token *token, Expr *expr1, Expr *expr2)
        : Op(token, Type::max(expr1->type, expr2->type)), expr1(expr1), expr2(expr2) {
    if (type == nullptr) error("type error");
}

Expr *Arith::gen() {
    return new Arith(op, expr1->reduce(), expr2->reduce());
}

string Arith::toString() {
    return expr1->toString() + " " + op->toString() + " " + expr2->toString();
}

Unary::Unary(Token *token, Expr *expr)
        : Op(token, Type::max(Type::Int, expr->type)), expr(expr) {
    if (type == nullptr) error("type error");
}

Expr *Unary::gen() {
    return new Unary(op, expr->reduce());
}

string Unary::toString() {
    return op->toString() + " " + expr->toString();
}

Constant::Constant(Token *token, Type *type) : Expr(token, type) {

}

Constant *Constant::True = new Constant(Word::TRUE, Type::Bool);
Constant *Constant::False = new Constant(Word::FALSE, Type::Bool);

void Constant::jumping(int t, int f) {
    if (*this == *True && t != 0) emit("goto L" + to_string(t));
    else if (*this == *False && f != 0) emit("goto L" + to_string(f));
}

Logical::Logical(Token *token, Expr *expr1, Expr *expr2)
        : Expr(token, check(expr1->type, expr2->type)), expr1(expr1), expr2(expr2) {
    if (type == nullptr) error("type error");
}

Type *Logical::check(Type *p1, Type *p2) {
    if (*p1 == *Type::Bool && *p2 == *Type::Bool) return Type::Bool;
    return nullptr;
}

Expr *Logical::gen() {
    int f = newlabel();
    int a = newlabel();
    auto temp = new Temp(type);
    jumping(0, f);
    emit(temp->toString() + " = true");
    emit("goto L" + to_string(a));
    emitlabel(f);
    emit(temp->toString() + " = false");
    emitlabel(a);

    return temp;
}

string Logical::toString() {
    return expr1->toString() + " " + op->toString() + " " + expr2->toString();
}

Or::Or(Token *token, Expr *expr1, Expr *expr2) : Logical(token, expr1, expr2) {

}

void Or::jumping(int t, int f) {
    int label = t != 0 ? t : newlabel();
    expr1->jumping(label, 0);
    expr2->jumping(t,f);
    if (t == 0) emitlabel(label);
}

And::And(Token *token, Expr *expr1, Expr *expr2) : Logical(token, expr1, expr2) {

}

void And::jumping(int t, int f) {
    int label = f != 0 ? f : newlabel();
    expr1->jumping(0, label);
    expr2->jumping(t,f);
    if (f == 0) emitlabel(label);
}

Not::Not(Token *token, Expr *expr) : Logical(token, expr, expr) {

}

void Not::jumping(int t, int f) {
    expr2->jumping(f, t);
}

string Not::toString() {
    return op->toString() + " " + expr2->toString();
}

Rel::Rel(Token *token, Expr *expr1, Expr *expr2) : Logical(token, expr1, expr2) {

}

void Rel::jumping(int t, int f) {
    auto a = expr1->reduce();
    auto b = expr2->reduce();
    auto test = a->toString() + " " + op->toString() + " " + b->toString();
    emitjumps(test, t, f);
}

Type *Rel::check(Type *p1, Type *p2) {
    // TODO: must use typeid ???
    if (typeid(p1) == typeid(Array) || typeid(p2) == typeid(Array)) return nullptr;
    if (*p1 == *p2) return Type::Bool;
    return nullptr;
}

Access::Access(Id *array, Expr *index, Type *type)
: Op(new Word("[]", Tag::INDEX), type), array(array), index(index) {

}

Expr *Access::gen() {
    return new Access(array, index->reduce(), type);
}

void Access::jumping(int t, int f) {
    emitjumps(reduce()->toString(), t, f);
}

string Access::toString() {
    return array->toString() + "[ " + index->toString() + " ]";
}
