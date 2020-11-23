//
// Created by julianlohuis on 23/11/2020.
//

#ifndef CPPLOX_TOKENTYPE_H
#define CPPLOX_TOKENTYPE_H

#include <ostream>

enum class TokenType
{
	// Single-character tokens.
	LEFT_PAREN,
	RIGHT_PAREN,
	LEFT_BRACE,
	RIGHT_BRACE,
	COMMA,
	DOT,
	MINUS,
	PLUS,
	SEMICOLON,
	SLASH,
	STAR,

	// One or two character tokens.
	BANG,
	BANG_EQUAL,
	EQUAL,
	EQUAL_EQUAL,
	GREATER,
	GREATER_EQUAL,
	LESS,
	LESS_EQUAL,

	// Literals.
	IDENTIFIER,
	STRING,
	NUMBER,

	// Keywords.
	AND,
	CLASS,
	ELSE,
	FALSE,
	FUN,
	FOR,
	IF,
	NIL,
	OR,
	PRINT,
	RETURN,
	SUPER,
	THIS,
	TRUE,
	VAR,
	WHILE,

	_EOF
};

std::ostream& operator<<(std::ostream& os, const TokenType& token);

#endif	//CPPLOX_TOKENTYPE_H
