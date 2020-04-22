//
// Created by pikachu on 2020/4/10.
//

#include "common.h"
#include "parser.h"
#include "symbol.h"
#include <utility>

parser::parser(lexer lexer) : _lexer(std::move(lexer)) {
    cur_token = _lexer.get_next_token();
}

void parser::eat(token_type type) {
    if (cur_token.type == token_type::unknown) {
        string msg = "Unknown char: ";
        msg += cur_token.raw;
        ERROR(msg, type);
    }
    if (cur_token.type == type) {
        cur_token = _lexer.get_next_token();
        return;
    }
    ERROR("Invalid syntax", type);
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
    if (token.type == token_type::string_const) {
        eat(token_type::string_const);
        return new string_node(token);
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
    auto id = cur_token;
    eat(token_type::identifier);
    if (cur_token.type == token_type::left_parenthesis) {
        return procedure_call_statement(id);
    } else {
        return new variable_node(id);
    }
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
        auto name = cur_token.get_value<string>();
        eat(token_type::identifier);
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
#ifdef TEST
    auto ret = program();
    if (cur_token.type != token_type::eof) {
        error("code not end", token_type::eof);
    }
    return ret;
#else
    switch (cur_token.type) {

        case token_type::integer_const:
        case token_type::real_const:
        case token_type::left_parenthesis:
        case token_type::right_parenthesis:
        case token_type::unary:
            return expr();
        case token_type::program:
            return program();
        case token_type::begin:
            return compound_statement();
        default:
            return nullptr;
    }
#endif
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
        SPDLOG_ERROR("Invalid syntax");
        throw invalid_syntax_exception();
    }
    return ret;
}

ast *parser::statement() {
    if (cur_token.type == token_type::begin) {
        return compound_statement();
    }
    if (cur_token.type == token_type::identifier) {
        auto id = cur_token;
        eat(token_type::identifier);
        if (cur_token.type == token_type::left_parenthesis) {
            return procedure_call_statement(id);
        } else {
            return assignment_statement(id);
        }
    } else if (cur_token.type == token_type::if_token) {
        return if_statement();
    } else if (cur_token.type == token_type::for_token) {
        return for_statement();
    }
    return empty();
}

ast *parser::empty() {
    return new noop();
}

ast *parser::assignment_statement(token id) {
    eat(token_type::assignment);

    return new assignment(new variable_node(id), expr());
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
    bool noop = true;
    // TODO: 这里的语法有问题
    while (cur_token.type == token_type::variable
        || cur_token.type == token_type::procedure
        || cur_token.type == token_type::function
    ) {

        if (cur_token.type == token_type::variable) {
            eat(token_type::variable);
            while (cur_token.type == token_type::identifier) {
                auto var_dec = variable_declaration();
                ret.insert(ret.end(), var_dec.begin(), var_dec.end());
                eat(token_type::semicolon);
            }
            noop = false;
        } else if (cur_token.type == token_type::procedure) {
            auto p = procedure();
            ret.insert(ret.end(), p.begin(), p.end());
            noop = false;
        } else if (cur_token.type == token_type::function) {
            auto p = function();
            ret.insert(ret.end(), p.begin(), p.end());
            noop = false;
        }
    }
    if (noop) ret.emplace_back(empty());
    return ret;
}

vector<ast *> parser::variable_declaration() {
    vector<identifier_node*> variables;
    auto name = new identifier_node(cur_token);
    variables.emplace_back(name);
    eat(token_type::identifier);
    while (cur_token.type == token_type::comma) {
        eat(token_type::comma);
        name = new identifier_node(cur_token);
        variables.emplace_back(name);
        eat(token_type::identifier);
    }
    eat(token_type::colon);
    auto type = new type_node(cur_token);
    eat(token_type::type_specification);
    vector<ast*> ret;
    for(const auto& it: variables) {
        ret.push_back(new variable_declaration_node(it, type));
    }
    return ret;
}

vector<ast *> parser::procedure() {
    vector<ast *> ret;
    while (cur_token.type == token_type::procedure) {
        eat(token_type::procedure);
        auto name = cur_token.get_value<string>();
        eat(token_type::identifier);
        vector<variable_declaration_node*> param_nodes;
        if (cur_token.type == token_type::left_parenthesis) {
            eat(token_type::left_parenthesis);
            while (true) {
                vector<token> params;
                params.push_back(cur_token);
                eat(token_type::identifier);
                while (cur_token.type == token_type::comma) {
                    eat(token_type::comma);
                    params.push_back(cur_token);
                    eat(token_type::identifier);
                }
                eat(token_type::colon);
                for (const auto& param : params) {
                    param_nodes.emplace_back(new variable_declaration_node{
                        new identifier_node(param), new type_node(cur_token)});
                }
                eat(token_type::type_specification);
                if (cur_token.type != token_type::semicolon) break;
                eat(token_type::semicolon);
            }
            eat(token_type::right_parenthesis);
        }
        eat(token_type::semicolon);
        auto p = new procedure_node(name, param_nodes, block());
        eat(token_type::semicolon);
        ret.push_back(p);
    }

    return ret;
}

vector<ast *> parser::function() {
    vector<ast *> ret;
    while (cur_token.type == token_type::function) {
        eat(token_type::function);
        auto name = cur_token.get_value<string>();
        eat(token_type::identifier);
        vector<variable_declaration_node*> param_nodes;
        if (cur_token.type == token_type::left_parenthesis) {
            eat(token_type::left_parenthesis);
            while (true) {
                vector<token> params;
                params.push_back(cur_token);
                eat(token_type::identifier);
                while (cur_token.type == token_type::comma) {
                    eat(token_type::comma);
                    params.push_back(cur_token);
                    eat(token_type::identifier);
                }
                eat(token_type::colon);
                for (const auto& param : params) {
                    param_nodes.emplace_back(new variable_declaration_node{
                            new identifier_node(param), new type_node(cur_token)});
                }
                eat(token_type::type_specification);
                if (cur_token.type != token_type::semicolon) break;
                eat(token_type::semicolon);
            }
            eat(token_type::right_parenthesis);
        }
        eat(token_type::colon);
        auto ret_type = new type_node(cur_token);
        eat(token_type::type_specification);
        eat(token_type::semicolon);
        auto p = new function_node(name, param_nodes, ret_type, block());
        eat(token_type::semicolon);
        ret.push_back(p);
    }

    return ret;
}
void parser::error(string msg, token_type expect_type) {
    std::cout << "Error: " << msg << std::endl;
    std::cout << cur_token.source_code << std::endl;
    for(int i=0;i<cur_token.col;i++) {
        std::cout << " ";
    }
    std::cout << "^" << std::endl;
    std::cout << "Expect " << expect_type << std::endl;
    throw invalid_syntax_exception(msg);
}

ast *parser::procedure_call_statement(token id) {
    vector<ast*> params;
    eat(token_type::left_parenthesis);
    params.push_back(expr());
    while (cur_token.type == token_type::comma) {
        eat(token_type::comma);
        params.push_back(expr());
    }
    eat(token_type::right_parenthesis);
    return new procedure_call_node(id.get_value<string>(), params);
}

ast *parser::if_statement() {
    eat(token_type::if_token);
    auto left = expr();
    auto op = cur_token;
    eat(op.type);
    auto cond = new bool_expr_node(left, op, expr());
    eat(token_type::then_token);
    auto if_block = statement();
    eat(token_type::else_token);
    auto ret = new if_node(cond, new block_node({if_block}), new block_node({statement()}));
    eat(token_type::semicolon);
    return ret;
}

ast *parser::for_statement() {
    eat(token_type::for_token);
    auto id = cur_token;
    eat(token_type::identifier);
    auto init = assignment_statement(id);
    eat(token_type::to_token);
    auto end = new number(cur_token);
    eat(token_type::integer_const);
    eat(token_type::do_token);
    auto ret = new for_node(init, end, statement());
    eat(token_type::semicolon);
    return ret;
}

ast *parser::function_call_statement(token id) {
    vector<ast*> params;
    eat(token_type::left_parenthesis);
    params.push_back(expr());
    while (cur_token.type == token_type::comma) {
        eat(token_type::comma);
        params.push_back(expr());
    }
    eat(token_type::right_parenthesis);
    return new procedure_call_node(id.get_value<string>(), params);
}


void binary_operator::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

void number::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

void unary_operator::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

void compound::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

void noop::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

void assignment::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

void variable_node::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

void program_node::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}
void type_node::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}
void identifier_node::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

void procedure_node::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

void function_node::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

void block_node::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

void variable_declaration_node::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

symbol_node_visitor::symbol_node_visitor(scoped_symbol_table *table) {
    auto int_type = new builtin_type_symbol("INTEGER");
    table->insert(int_type);
    auto real_type = new builtin_type_symbol("REAL");
    table->insert(real_type);
    tables.push_back(table);
    cur_table = table;
}

void symbol_node_visitor::visit(variable_declaration_node *node) {
    auto type = cur_table->lookup(node->get_type());
    cur_table->insert(new variable_symbol(node->get_name(), type));
}

void symbol_node_visitor::visit(variable_node *node) {
    auto name = node->id.get_value<string>();
    auto type = cur_table->lookup(name);
}

void symbol_node_visitor::visit(procedure_node *node) {
    auto proc = new procedure_symbol(node->name);
    cur_table->insert(proc);
    auto table = new scoped_symbol_table(node->name, cur_table);
    for(auto param : node->params) {
        auto type = table->lookup(param->get_type());
        auto var_symbol = new variable_symbol(param->get_name(), type);
        table->insert(var_symbol);
        proc->params.push_back(var_symbol);
    }
    tables.push_back(table);
    cur_table = table;
    node->child->accept(this);
    tables.pop_back();
    std::cout << std::endl << std::endl;
    std::cout << cur_table->to_table_string();
    std::cout << std::endl << std::endl;
    delete cur_table;
    cur_table = tables.back();
}

void procedure_call_node::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

void function_call_node::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

void if_node::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}
void for_node::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

void bool_expr_node::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}

void string_node::accept(abstract_node_visitor *visitor) {
    return visitor->visit(this);
}
