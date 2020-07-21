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

struct Stmt : public Node {
    Stmt() {}
    static Stmt * Null, *Enclosing; // used for break stmts
    virtual void gen(int b, int a) {} // called with labels begin and after
    int after = 0; // saves label after

    string toString() override;
};
struct Expr;
struct If : public Stmt {
    Expr* expr;
    Stmt* stmt;

    If(Expr *expr, Stmt *stmt);

    void gen(int b, int a) override;
};
struct Else : public Stmt {
    Expr* expr;
    Stmt* stmt1;
    Stmt* stmt2;

    Else(Expr *expr, Stmt *stmt1, Stmt *stmt2);

    void gen(int b, int a) override;
};
struct While : public Stmt {
    Expr* expr;
    Stmt* stmt;
    void init(Expr* expr, Stmt* stmt);

    void gen(int b, int a) override;
};
struct Do : public Stmt {
    Expr* expr;
    Stmt* stmt;
    void init(Expr* expr, Stmt* stmt);

    void gen(int b, int a) override;
};
struct Id;
struct Set : public Stmt {
    Id* id;
    Expr* expr;

    Set(Id *id, Expr *expr);
    Type* check(Type* p1, Type* p2);

    void gen(int b, int a) override;
};
struct Access;
struct SetElem : public Stmt {
    Id* array;
    Expr* index;
    Expr* expr;
    SetElem(Access* x, Expr* y);
    Type* check(Type* p1, Type* p2);

    void gen(int b, int a) override;
};
struct Seq : public Stmt {
    Stmt* stmt1;
    Stmt* stmt2;

    Seq(Stmt *stmt1, Stmt *stmt2);

    void gen(int b, int a) override;
};
struct Break: public Stmt {
    Stmt* stmt;

    Break();

    void gen(int b, int a) override;
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
    Logical(Token *token, Expr *expr1, Expr *expr2, Type* type);

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
    void init();
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

struct Access : public Op {
    Id* array;
    Expr* index;

    Access(Id *array, Expr *index, Type *type);

    Expr *gen() override;

    void jumping(int t, int f) override;

    string toString() override;
};
class Env {
public:
    Env(Env* prev):prev(prev) {
    }
    void put(Token* token, Id* id);
    Id* get(Token* v);
protected:
    Env* prev;
private:
    unordered_map<Token*,Id*> table;
};
class Parser {
public:
    Parser(Lexer* lex);
    void move();
    void error(string s);
    void match(int t);
    void match(Tag tag);
    void program();
    Stmt * block();
    void decls();
    Type* type();
    Type* dims(Type* p);
    Stmt* stmts();
    Stmt* stmt();
    Stmt* assign();
    Expr* boolean();
    Expr* join();
    Expr* equality();
    Expr* rel();
    Expr* expr();
    Expr* term();
    Expr* unary();
    Expr* factor();
    Access* offset(Id* a);
private:
    Lexer *lex;
    Token* look; // lookahead token
    Env* top;
    int used;
};


#endif //PI_LANG_PARSER_H
