//
// Created by julianlohuis on 23/11/2020.
//

#include "Parser.h"
#include "Lox.h"

#include <array>
#include <ranges>
#include <algorithm>

Parser::Parser(std::vector<Token> _tokens)
	: tokens(std::move(_tokens))
	, current(0)
{
}

Expr<std::string>* Parser::expression()
{
	return equality();
}
Expr<std::string>* Parser::equality()
{
	auto* expr = comparison();

	while (match(TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL))
	{
		Token op = previous();
		auto* right = comparison();
		expr = new Binary<std::string>(expr, op, right);
	}
	return expr;
}
template<typename... Args>
bool Parser::match(Args... args)
{
	std::array<TokenType, sizeof...(Args)> types { args... };

	for (auto type : types)
	{
		if (check(type))
		{
			advance();
			return true;
		}
	}

	return false;
}
bool Parser::check(TokenType type)
{
	if (isAtEnd()) { return false; }
	return peek().type == type;
}
Token Parser::advance()
{
	if (!isAtEnd()) { current++; }
	return previous();
}
bool Parser::isAtEnd()
{
	return peek().type == TokenType::END_OF_FILE;
}
Token Parser::peek()
{
	return tokens.at(current);
}
Token Parser::previous()
{
	return tokens.at(current - 1);
}
Expr<std::string>* Parser::comparison()
{
	auto* expr = term();

	while (match(TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL))
	{
		Token op = previous();
		auto* right = term();
		expr = new Binary<std::string>(expr, op, right);
	}
	return expr;
}
Expr<std::string>* Parser::term()
{
	auto* expr = factor();

	while (match(TokenType::MINUS, TokenType::PLUS))
	{
		Token op = previous();
		auto* right = factor();
		expr = new Binary<std::string>(expr, op, right);
	}
	return expr;
}
Expr<std::string>* Parser::factor()
{
	auto* expr = unary();

	while (match(TokenType::SLASH, TokenType::STAR))
	{
		Token op = previous();
		auto* right = unary();
		expr = new Binary<std::string>(expr, op, right);
	}
	return expr;
}
Expr<std::string>* Parser::unary()
{
	if (match(TokenType::BANG, TokenType::MINUS))
	{
		Token op = previous();
		auto* right = unary();
		return new Unary<std::string>(op, right);
	}

	return primary();
}
Expr<std::string>* Parser::primary()
{
	if (match(TokenType::FALSE)) { return new Literal<std::string>(false); }
	if (match(TokenType::TRUE)) { return new Literal<std::string>(true); }
	if (match(TokenType::NIL)) { return new Literal<std::string>(std::monostate()); }

	if (match(TokenType::NUMBER, TokenType::STRING)) { return new Literal<std::string>(previous().literal); }

	if (match(TokenType::LEFT_PAREN))
	{
		auto* expr = expression();
		consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
		return new Grouping<std::string>(expr);
	}

	throw error(peek(), "Expected expression.");
}
Token Parser::consume(TokenType type, const std::string& message)
{
	if (check(type)) { return advance(); }
	throw error(peek(), message);
}
ParseError Parser::error(Token token, const std::string& message)
{
	Lox::error(token, message);
	return {};
}
void Parser::synchronize()
{
	advance();

	while (!isAtEnd())
	{
		if (previous().type == TokenType::SEMICOLON) return;

		switch (peek().type)
		{
			case TokenType::CLASS:
			case TokenType::FUN:
			case TokenType::VAR:
			case TokenType::FOR:
			case TokenType::IF:
			case TokenType::WHILE:
			case TokenType::PRINT:
			case TokenType::RETURN: return;
		}

		advance();
	}
}
Expr<std::string>* Parser::parse()
{
	try
	{
		return expression();
	}
	catch (ParseError error)
	{
		return nullptr;
	}
}
