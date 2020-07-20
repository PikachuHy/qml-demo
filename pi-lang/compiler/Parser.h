//
// Created by pikachu on 2020/7/20.
//

#ifndef PI_LANG_PARSER_H
#define PI_LANG_PARSER_H

#include "Lexer.h"

class Node {
public:
    Node();

    void error(string s);

    int newlabel();

    void emitlabel(int i);

    void emit(string s);

    static int labels;

    virtual string toString() = 0;

private:
    int lexline;
};

struct Expr : public Node {
    Expr(Token *token, Type *type);

    Token *op;
    Type *type;

    virtual Expr *gen() { return this; }

    virtual Expr *reduce() { return this; }

    virtual void jumping(int t, int f);

    void emitjumps(string test, int t, int f);

    bool operator==(Expr &rhs) const;

    string toString() override;
};

struct Id : public Expr {
    Id(Word *id, Type *type, int b) : Expr(id, type), offset(b) {}

    int offset;
};

struct Temp : public Expr {
    Temp(Type *type);

    string toString() override;

    static int count;
    int number;
};

struct Constant : public Expr {
    Constant(Token *token, Type *type);

    Constant(int i) : Expr(new Num(i), Type::Int) {}

    void jumping(int t, int f) override;

    static Constant *True, *False;
};

struct Logical : public Expr {
    Expr *expr1;
    Expr *expr2;

    Logical(Token *token, Expr *expr1, Expr *expr2);

    Expr *gen() override;

    string toString() override;

protected:
    virtual Type *check(Type *p1, Type *p2);
};
struct Or : public Logical {
    Or(Token *token, Expr *expr1, Expr *expr2);

    void jumping(int t, int f) override;
};
struct And : public Logical {
    And(Token *token, Expr *expr1, Expr *expr2);

    void jumping(int t, int f) override;
};
struct Not : public Logical {
    Not(Token *token, Expr *expr);

    void jumping(int t, int f) override;

    string toString() override;
};
struct Rel : public Logical {
public:
    Rel(Token *token, Expr *expr1, Expr *expr2);

    void jumping(int t, int f) override;
protected:
    Type *check(Type *p1, Type *p2) override;
};
struct Op : public Expr {
    Op(Token *token, Type *type) : Expr(token, type) {}

    Expr *reduce() override;
};

struct Arith : public Op {
    Expr *expr1;
    Expr *expr2;

    Arith(Token *token, Expr *expr1, Expr *expr2);

    Expr *gen() override;

    string toString() override;
};

struct Unary : public Op {
    Expr *expr;

    Unary(Token *token, Expr *expr);

    Expr *gen() override;

    string toString() override;
};

class Parser {
public:
    Parser(Lexer &lexer);

    void program();

private:
    Lexer lexer;
};


#endif //PI_LANG_PARSER_H
