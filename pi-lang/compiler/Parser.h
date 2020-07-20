//
// Created by pikachu on 2020/7/20.
//

#ifndef PI_LANG_PARSER_H
#define PI_LANG_PARSER_H
#include "Lexer.h"
class Node {
public:
    Node();
    void error(string s) const ;
    int newlabel();
    void emitlabel(int i) const ;
    void emit(string s) const ;
    static int labels;
    virtual string toString() const = 0;
private:
    int lexline;
};
struct Expr: public Node {
    Expr(const Token *token, const Type *type);
    const Token * op;
    const Type* type;
    virtual const Expr* gen() {return this;}
    virtual const Expr* reduce() {return this;}
    virtual void jumping(int t, int f) const;
    void emitjumps(string test, int t, int f) const;

    bool operator==(const Expr &rhs) const;

    bool operator!=(const Expr &rhs) const;

    string toString() const override;
};
struct Id : public Expr {
    Id(const Word* id, const Type* type, int b): Expr(id, type), offset(b) {}
    int offset;
};
struct Temp: public Expr {
    Temp(const Type* type);

    string toString() const override;

    static int count;
    int number;
};
struct Constant: public Expr {
    Constant(const Token *token, const Type *type);
    Constant(int i): Expr(new Num(i), &Type::Int) {}

    void jumping(int t, int f) const override;
    static const Constant True, False;
};
struct Logical : public Expr {
    const Expr* expr1;
    const Expr* expr2;

    Logical(const Token *token, const Expr *expr1, const Expr *expr2);

    const Expr *gen() override;

    string toString() const override;

private:
    const Type* check(const Type* p1, const Type* p2);
};
struct Op : public Expr {
    Op(const Token *token, const Type* type): Expr(token, type) {}

    const Expr *reduce() override;
};
struct Arith : public Op {
    const Expr* expr1;
    const Expr* expr2;
    Arith(const Token *token, const Expr* expr1, const Expr* expr2);

    const Expr *gen() override;

    string toString() const override;
};

struct Unary : public Op {
    const Expr* expr;
    Unary(const Token* token, const Expr* expr);

    const Expr *gen() override;

    string toString() const override;
};
class Parser {
public:
    Parser(const Lexer &lexer);
    void program();
private:
    Lexer lexer;
};


#endif //PI_LANG_PARSER_H
