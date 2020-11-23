//
// Created by julianlohuis on 23/11/2020.
//

#ifndef CPPLOX_TOKEN_H
#define CPPLOX_TOKEN_H

#include "TokenType.h"

#include <string>
#include <ostream>
#include <variant>

struct Token
{
	using literal_t = std::variant<std::monostate, std::string, double>;

	TokenType type;
	std::string lexeme;
	literal_t literal;
	int line;

	Token(TokenType _type, const std::string& _lexeme, literal_t _literal, int _line);

	friend std::ostream& operator<<(std::ostream& os, const Token& token);
};

#endif	//CPPLOX_TOKEN_H
