//
// Created by julianlohuis on 23/11/2020.
//

#include "Token.h"

Token::Token(TokenType _type, const std::string& _lexem, literal_t _literal, int _line)
	: type(_type)
	, lexem(_lexem)
	, literal(_literal)
	, line(_line)
{
}

std::ostream& operator<<(std::ostream& os, const Token& token)
{
	os << "type: " << token.type << " lexem: " << token.lexem;
	if (token.type == TokenType::NUMBER)
		os << " literal: " << std::get<double>(token.literal);
	else if (token.type == TokenType::STRING)
		os << " literal: " << std::get<std::string>(token.literal);
	os << " line: " << token.line;

	return os;
}
