//
// Created by julianlohuis on 23/11/2020.
//

#ifndef CPPLOX_PARSER_H
#define CPPLOX_PARSER_H

#include "Token.h"
#include "Expr.h"

#include <vector>
#include <memory>
#include <exception>

struct ParseError : public std::exception {};

class Parser
{
private:
	std::vector<Token> tokens;
	size_t current;

public:
	explicit Parser(std::vector<Token> _tokens);

	Expr<std::string>* expression();
	Expr<std::string>* equality();
	template<typename... Ts>
	bool match(Ts... args);
	bool check(TokenType type);
	Token advance();
	bool isAtEnd();
	Token peek();
	Token previous();
	Expr<std::string>* comparison();
	Expr<std::string>* term();
	Expr<std::string>* factor();
	Expr<std::string>* unary();
	Expr<std::string>* primary();
	Token consume(TokenType type, const std::string& message);
	ParseError error(Token token, const std::string& message);
	void synchronize();
	Expr<std::string>* parse();
};

#endif	//CPPLOX_PARSER_H
