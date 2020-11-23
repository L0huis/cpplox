//
// Created by julianlohuis on 23/11/2020.
//

#ifndef CPPLOX_SCANNER_H
#define CPPLOX_SCANNER_H

#include "TokenType.h"
#include "Token.h"
#include "Lox.h"

#include <vector>
#include <string>
#include <map>

using namespace std::string_view_literals;

class Scanner
{
	const std::string source;
	std::vector<Token> tokens;
	const std::map<std::string_view, TokenType> keywords {
		{ "and"sv, TokenType::AND },	 { "class"sv, TokenType::CLASS },	{ "else"sv, TokenType::ELSE },
		{ "false"sv, TokenType::FALSE }, { "for"sv, TokenType::FOR },		{ "fun"sv, TokenType::FUN },
		{ "if"sv, TokenType::IF },		 { "nil"sv, TokenType::NIL },		{ "or"sv, TokenType::OR },
		{ "print"sv, TokenType::PRINT }, { "return"sv, TokenType::RETURN }, { "super"sv, TokenType::SUPER },
		{ "this"sv, TokenType::THIS },	 { "true"sv, TokenType::TRUE },		{ "var"sv, TokenType::VAR },
		{ "while"sv, TokenType::WHILE },
	};

	int start = 0;
	int current = 0;
	int line = 1;

	bool isAtEnd();
	void scanToken();
	char advance();
	void addToken(TokenType type);
	void addToken(TokenType type, Token::literal_t literal);
	bool match(char expected);
	char peek();
	void string();
	bool isDigit(char c);
	void number();
	char peekNext();
	void identifier();
	bool isAlpha(char c);
	bool isAlphaNumeric(char c);

public:
	Scanner(std::string _source);
	std::vector<Token> scanTokens();
};

#endif	//CPPLOX_SCANNER_H
