//
// Created by pikachu on 2020/4/10.
//

#include "parser.h"

#include <utility>

parser::parser(lexer lexer) : _lexer(std::move(lexer)) {
    cur_token = _lexer.get_next_token();
}

void parser::eat(token_type type) {
    if (cur_token.type == type) {
        cur_token = _lexer.get_next_token();
        return;
    }
    error("Invalid syntax", type);
}

ast *parser::factor() {
    auto token = this->cur_token;
    if (token.type == token_type::integer_const) {
        eat(token_type::integer_const);
        return new number{token};
    }
    if (token.type == token_type::real_const) {
        eat(token_type::real_const);
        return new number{token};
    }
    if (token.type == token_type::unary) {
        eat(token_type::unary);
        auto ret = new unary_operator{token, factor()};
        return ret;
    }
    if (token.type == token_type::left_parenthesis) {
        _lexer.enter_new_expr();
        eat(token_type::left_parenthesis);
        auto ret = expr();
        eat(token_type::right_parenthesis);
        return ret;
    }
    return variable();
}

ast *parser::term() {
    auto ret = factor();
    while (cur_token.type == token_type::multiplication
           || cur_token.type == token_type::integer_division
           || cur_token.type == token_type::float_division) {
        auto token = cur_token;
        eat(token.type);
        ret = new binary_operator(ret, token, factor());
    }
    return ret;
}

ast *parser::expr() {
    auto ret = term();
    while (cur_token.type == token_type::plus
           || cur_token.type == token_type::minus) {
        auto token = cur_token;
        eat(token.type);
        ret = new binary_operator(ret, token, term());
    }
    return ret;
}

ast *parser::program() {
    ast* ret;
    if (cur_token.type == token_type::program) {
        eat(token_type::program);
        auto name = variable()->id.get_value<string>();
        eat(token_type::semicolon);
        ret = new program_node(name, block());
    } else {
        ast* ret = compound_statement();
    }
    eat(token_type::dot);
    return ret;
}

ast *parser::compound_statement() {
    eat(token_type::begin);
    auto nodes = statement_list();
    eat(token_type::end);
    return new compound{nodes};
}

ast *parser::parse() {
    auto ret = program();
    if (cur_token.type != token_type::eof) {
        error("code not end", token_type::eof);
    }
    return ret;
}

variable_node *parser::variable() {
    auto ret = new variable_node(cur_token);
    eat(token_type::identifier);
    return ret;
}

vector<ast *> parser::statement_list() {
    vector<ast *> ret;
    ret.emplace_back(statement());
    while (cur_token.type == token_type::semicolon) {
        eat(token_type::semicolon);
        auto nodes = statement_list();
        ret.insert(ret.end(), nodes.begin(), nodes.end());
    }
    if (cur_token.type == token_type::identifier) {
        error();
    }
    return ret;
}

ast *parser::statement() {
    if (cur_token.type == token_type::begin) {
        return compound_statement();
    }
    if (cur_token.type == token_type::identifier) {
        return assignment_statement();
    }
    return empty();
}

ast *parser::empty() {
    return new noop();
}

ast *parser::assignment_statement() {
    auto var = variable();
    eat(token_type::assignment);

    return new assignment{var, expr()};
}

ast *parser::block() {
    vector<ast*> children;
    auto dec = declarations();
    children.insert(children.end(), dec.begin(), dec.end());
    children.emplace_back(compound_statement());
    return new block_node{children};
}

vector<ast *> parser::declarations() {
    vector<ast*> ret;
    if (cur_token.type == token_type::variable) {
        eat(token_type::variable);
        while (cur_token.type == token_type::identifier) {
            auto var_dec = variable_declaration();
            ret.insert(ret.end(), var_dec.begin(), var_dec.end());
            eat(token_type::semicolon);
        }
    } else {
        ret.emplace_back(empty());
    }
    return ret;
}

vector<ast *> parser::variable_declaration() {
    vector<string> variables;
    auto name = cur_token.get_value<string>();
    variables.emplace_back(name);
    eat(token_type::identifier);
    while (cur_token.type == token_type::comma) {
        eat(token_type::comma);
        name = cur_token.get_value<string>();
        variables.emplace_back(name);
        eat(token_type::identifier);
    }
    eat(token_type::colon);
    auto type = cur_token.get_value<string>();
    eat(token_type::type_specification);
    vector<ast*> ret;
    for(const auto& it: variables) {
        ret.push_back(new variable_declaration_node{it, type});
    }
    return ret;
}

int binary_operator::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

int number::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

int unary_operator::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

int compound::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

int noop::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

int assignment::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

int variable_node::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

int program_node::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

int block_node::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

int variable_declaration_node::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}
