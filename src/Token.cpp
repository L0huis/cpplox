//
// Created by julianlohuis on 23/11/2020.
//

#include "Token.h"

Token::Token(TokenType _type, const std::string& _lexeme, literal_t _literal, int _line)
	: type(_type)
	, lexeme(_lexeme)
	, literal(_literal)
	, line(_line)
{
}

std::ostream& operator<<(std::ostream& os, const Token& token)
{
	os << "type: " << token.type << " lexeme: " << token.lexeme;
	if (token.type == TokenType::NUMBER)
		os << " value: " << std::get<double>(token.literal);
	else if (token.type == TokenType::STRING)
		os << " value: " << std::get<std::string>(token.literal);
	os << " line: " << token.line;

	return os;
}
