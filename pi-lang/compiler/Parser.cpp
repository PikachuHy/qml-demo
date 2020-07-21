//
// Created by pikachu on 2020/7/20.
//

#include "Parser.h"
#include <iostream>
#define MY_ERROR(msg) {std::cout << __FILE__ << ":" << __LINE__ << " "; error(msg);}
Parser::Parser(Lexer *lex)
        : lex(lex) {
    move();
}

void Parser::program() { // program -> block
    // TODO: implement
    std::cout << "pi-lang compiler is under the development" << std::endl;
    auto s = block();
    int begin = s->newlabel();
    int after = s->newlabel();
    s->emitlabel(begin);
    s->gen(begin, after);
    s->emitlabel(after);
}

void Parser::move() {
    look = lex->scan();
}

void Parser::error(string s) {
    std::cout << "near line " << Lexer::line << ": " << s << std::endl;
    exit(-1);
}

void Parser::match(int t) {
    if (static_cast<int>(look->tag) == t) move();
    else error("syntax error");
}

void Parser::match(Tag tag) {
    if (look->tag == tag) move();
    else error("syntax error");
}
Stmt *Parser::block() { // block -> { decls stmts }
    match('{');
    Env* saveEnv = top;
    top = new Env(top);
    decls();
    auto s = stmts();
    match('}');
    top = saveEnv;
    return s;
}

void Parser::decls() {
    while (look->tag == Tag::BASIC) { // D->type ID;
        auto p = type();
        auto token = look;
        match(Tag::ID);
        match(';');
        auto id = new Id((Word*)token, p, used);
        top->put(token, id);
        used = used + p->width;
    }
}

Type *Parser::type() {
    Type *p = (Type*)look; // expect look->tag == Tag::BASIC
    match(Tag::BASIC);
    if ((int)look->tag != '[') return p;
    return dims(p);
}

Stmt *Parser::stmts() {
    if ((int)look->tag == '}') return Stmt::Null;
    return new Seq(stmt(), stmts());
}

Type *Parser::dims(Type* p) {
    match('[');
    auto token = look;
    match(Tag::NUM);
    match(']');
    if ((int)look->tag == '[') {
        p = dims(p);
    }
    auto v = ((Num*)token)->value;
    return new Array(v, p);
}

Stmt *Parser::stmt() {
    Expr* x;
    Stmt *s, *s1, *s2;
    Stmt *savedStmt;
    switch (look->tag) {
        case (Tag)':': {
            move();
            return Stmt::Null;
        }
        case Tag::IF: {
            match(Tag::IF);
            match('(');
            x = boolean();
            match(')');
            s1 = stmt();
            if (look->tag != Tag::ELSE) return new If(x, s1);
            match(Tag::ELSE);
            s2 = stmt();
            return new Else(x, s1, s2);
        }
        case Tag::WHILE: {
            auto whilenode = new While();
            savedStmt = Stmt::Enclosing;
            Stmt::Enclosing = whilenode;
            match(Tag::WHILE);
            match('(');
            x =  boolean();
            match(')');
            s1 = stmt();
            whilenode->init(x, s1);
            Stmt::Enclosing = savedStmt;
            return whilenode;
        }
        case Tag::DO: {
            auto donode = new Do();
            savedStmt = Stmt::Enclosing;
            Stmt::Enclosing = donode;
            match(Tag::DO);
            s1 = stmt();
            match(Tag::WHILE);
            match('(');
            x =  boolean();
            match(')');
            match(';');
            donode->init(x, s1);
            Stmt::Enclosing = savedStmt;
            return donode;
        }
        case Tag::BREAK: {
            match(Tag::BREAK);
            match(';');
            return new Break();
        }
        case (Tag)'{':{
            return block();
        }
        default: {
            return assign();
        }
    }
    std::cout << "warning: nullptr stmt" << std::endl;
    return nullptr;
}

Stmt *Parser::assign() {
    Stmt* s;
    auto token = look;
    match(Tag::ID);
    auto id = top->get(token);
    if (id == nullptr) error(token->toString() + " undeclared");
    if ((int)look->tag == '=') { // S -> id = E;
        move();
        s = new Set(id, boolean());
    } else { // S->L = E;
        auto x = offset(id);
        match('=');
        s = new SetElem(x, boolean());
    }
    match(';');
    return s;
}

Expr *Parser::boolean() {
    auto x = join();
    while (look->tag == Tag::OR) {
        auto token = look;
        move();
        x = new Or(token, x, join());
    }
    return x;
}

Expr *Parser::join() {
    auto x = equality();
    while (look->tag == Tag::AND) {
        auto token = look;
        move();
        x = new And(token, x, equality());
    }
    return x;
}

Expr *Parser::equality() {
    auto x = rel();
    while (look->tag == Tag::EQ || look->tag == Tag::NE) {
        auto token = look;
        move();
        x = new Rel(token, x, rel());
    }
    return x;
}

Expr *Parser::rel() {
    auto x = expr();
    switch (look->tag) {
        case (Tag)'<':
        case Tag::LE:
        case Tag::NE:
        case (Tag)'>': {
            auto token = look;
            move();
            return new Rel(token, x, expr());
        }
        default: {

        }
    }
    return x;
}

Expr *Parser::expr() {
    auto x = term();
    while ((int)look->tag == '+' || (int)look->tag == '-') {
        auto token = look;
        move();
        x = new Arith(token, x, term());
    }
    return x;
}

Expr *Parser::term() {
    auto x = unary();
    while ((int)look->tag == '*' || (int)look->tag == '/') {
        auto token = look;
        move();
        x = new Arith(token, x, unary());
    }
    return x;
}

Expr *Parser::unary() {
    if ((int)look->tag == '-') {
        move();
        return new Unary(Word::MINUS, unary());
    }
    if ((int)look->tag == '!') {
        auto token = look;
        move();
        return new Not(token, unary());
    }
    return factor();
}

Expr *Parser::factor() {
    Expr* x = nullptr;
    switch (look->tag) {
        case (Tag)'(': {
            move();
            x = boolean();
            match(')');
            return x;
        }
        case Tag::NUM: {
            x = new Constant(look, Type::Int);
            move();
            return x;
        }
        case Tag::REAL:{
            x = new Constant(look, Type::Float);
            move();
            return x;
        }
        case Tag::TRUE: {
            x = Constant::True;
            move();
            return x;
        }
        case Tag::FALSE: {
            x = Constant::False;
            move();
            return x;
        }
        case Tag::ID: {
            auto id = top->get(look);
            if (id == nullptr) {
                error(look->toString() + " undeclared");
            }
            move();
            if ((int)look->tag != '[') return id;
            return offset(id);
        }
        default: {
            error("syntax error");
        }
    }
    return x;
}

Access *Parser::offset(Id* a) { // I -> [E] | [E] I
    Expr* i;
    Expr* w;
    Expr* t1;
    Expr* t2;
    Expr* loc;
    auto p = a->type;
    // first index, I -> [E]
    match('[');
    i = boolean();
    match(']');
    w = new Constant(p->width);
    t1 = new Arith(new Token('*'), i, w);
    loc = t1;
    while ((int)look->tag == '[') { // multi-dimensional I -> [E] I
        match('[');
        i = boolean();
        match(']');
        w = new Constant(p->width);
        t1 = new Arith(new Token('*'), i, w);
        t2 = new Arith(new Token('+'), loc, t1);
        loc = t2;
    }

    return new Access(a, loc, p);
}


Node::Node() {
    lexline = Lexer::line;
    column = Lexer::column;
}

int Node::labels = 0;

void Node::error(string s) {
    std::cout << "ERROR: near line " << lexline << ":" << column << " " << s << std::endl;
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
Stmt* Stmt::Null = new Stmt();
Stmt* Stmt::Enclosing = Stmt::Null;

string Stmt::toString() {
    return "stmt";
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
int Temp::count = 0;
string Temp::toString() {
    return "t" + to_string(number);
}

Arith::Arith(Token *token, Expr *expr1, Expr *expr2)
        : Op(token, nullptr), expr1(expr1), expr2(expr2) {
    type = Type::max(expr1->type, expr2->type);
    if (type == nullptr) MY_ERROR("type error");
}

Expr *Arith::gen() {
    return new Arith(op, expr1->reduce(), expr2->reduce());
}

string Arith::toString() {
    return expr1->toString() + " " + op->toString() + " " + expr2->toString();
}

Unary::Unary(Token *token, Expr *expr)
        : Op(token, nullptr), expr(expr) {
    type = Type::max(Type::Int, expr->type);
    if (type == nullptr) MY_ERROR("type error");
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
        : Expr(token, nullptr), expr1(expr1), expr2(expr2) {
    type = check(expr1->type, expr2->type);
    if (type == nullptr) MY_ERROR("type error");
}

Logical::Logical(Token *token, Expr *expr1, Expr *expr2, Type *type)
:Expr(token, type), expr1(expr1), expr2(expr2) {

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

Rel::Rel(Token *token, Expr *expr1, Expr *expr2)
: Logical(token, expr1, expr2, nullptr) {
    type = check(expr1->type, expr2->type);
    if (type == nullptr) MY_ERROR("type error");
}

void Rel::jumping(int t, int f) {
    auto a = expr1->reduce();
    auto b = expr2->reduce();
    auto test = a->toString() + " " + op->toString() + " " + b->toString();
    emitjumps(test, t, f);
}

Type *Rel::check(Type *p1, Type *p2) {
    // TODO: must use typeid ???
//    if (typeid(p1) == typeid(Array) || typeid(p2) == typeid(Array)) return nullptr;
    if (typeid(*p1) == typeid(Array)) {
        p1 = ((Array*)p1)->of;
    }
    if (typeid(*p2) == typeid(Array)) {
        p2 = ((Array*)p2)->of;
    }
    if (*p1 == *p2) return Type::Bool;
    return nullptr;
}

void Rel::init() {

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

If::If(Expr *expr, Stmt *stmt) : expr(expr), stmt(stmt) {
    if (expr->type != Type::Bool) expr->error("boolean required in if");
}

void If::gen(int b, int a) {
    int label = newlabel();
    expr->jumping(0, a);
    emitlabel(label);
    stmt->gen(label, a);
}

Else::Else(Expr *expr, Stmt *stmt1, Stmt *stmt2) : expr(expr), stmt1(stmt1), stmt2(stmt2) {
    if (expr->type != Type::Bool) expr->error("boolean required in if");
}

void Else::gen(int b, int a) {
    int label1 = newlabel();
    int label2 = newlabel();
    expr->jumping(0, label2);
    emitlabel(label1);
    stmt1->gen(label1, a);
    emit("goto L" + to_string(a));
    emitlabel(label2);
    stmt2->gen(label2, a);
}

void While::gen(int b, int a) {
    after = a;
    expr->jumping(0, a);
    int label = newlabel();
    emitlabel(label);
    stmt->gen(label, b);
    emit("goto L" + to_string(b));
}

void While::init(Expr *expr, Stmt *stmt) {
    this->expr = expr;
    this->stmt = stmt;
    if (expr->type != Type::Bool) expr->error("boolean required in if");
}

void Do::init(Expr *expr, Stmt *stmt) {
    this->expr = expr;
    this->stmt = stmt;
    if (expr->type != Type::Bool) expr->error("boolean required in if");
}

void Do::gen(int b, int a) {
    after = a;
    int label = newlabel();
    stmt->gen(b, label);
    emitlabel(label);
    expr->jumping(b, 0);
}

Set::Set(Id *id, Expr *expr) : id(id), expr(expr) {
    if (check(id->type, expr->type) == nullptr) MY_ERROR("type error");
}

Type *Set::check(Type* p1, Type* p2) {
    if (typeid(*p1) == typeid(Array)) {
        p1 = ((Array*)p1)->of;
    }
    if (typeid(*p2) == typeid(Array)) {
        p2 = ((Array*)p2)->of;
    }
    if (Type::numeric(p1) && Type::numeric(p2)) return p2;
    if (p1 == Type::Bool && p2 == Type::Bool) return p2;
    return nullptr;
}

void Set::gen(int b, int a) {
    emit(id->toString() + " = " + expr->gen()->toString());
}

SetElem::SetElem(Access *x, Expr* y) : array(x->array), index(x->index), expr(y) {
    if (check(x->type, expr->type) == nullptr) MY_ERROR("type error")
}

Type *SetElem::check(Type* p1, Type* p2) {
    if (typeid(*p1) == typeid(Array)) {
        p1 = ((Array*)p1)->of;
    }
    if (typeid(*p2) == typeid(Array)) {
        p2 = ((Array*)p2)->of;
    }
//    if (typeid(p1) == typeid(Array) || typeid(p2) == typeid(Array)) return nullptr;
    if (p1 == p2) return p2;
    if (Type::numeric(p1) && Type::numeric(p2)) return p2;
    return nullptr;
}

void SetElem::gen(int b, int a) {
    auto s1 = index->reduce()->toString();
    auto s2 = expr->reduce()->toString();
    emit(array->toString() + " [ " + s1 + " ] = " + s2);
}

Seq::Seq(Stmt *stmt1, Stmt *stmt2) : stmt1(stmt1), stmt2(stmt2) {

}

void Seq::gen(int b, int a) {
    if (stmt1 == Stmt::Null) stmt2->gen(b, a);
    else if (stmt2 == Stmt::Null) stmt1->gen(b, a);
    else {
        int label = newlabel();
        stmt1->gen(b, label);
        emitlabel(label);
        stmt2->gen(label, a);
    }
}

Break::Break() {
    if (Stmt::Enclosing == Stmt::Null) MY_ERROR("unenclosed break");
    stmt = Stmt::Enclosing;
}

void Break::gen(int b, int a) {
    emit("goto L" + to_string(stmt->after));
}

void Env::put(Token *token, Id *id) {
    table[token] = id;
}

Id *Env::get(Token *v) {
    for(auto e = this; e != nullptr; e = e->prev) {
        auto found = e->table.find(v);
        if (found != e->table.end()) return e->table[v];
    }
    return nullptr;
}
