//
// Created by julianlohuis on 23/11/2020.
//

#include "Scanner.h"

#include <charconv>

Scanner::Scanner(std::string _source)
	: source(_source)
{
}

std::vector<Token> Scanner::scanTokens()
{
	while (!isAtEnd())
	{
		start = current;
		scanToken();
	}

	tokens.emplace_back(TokenType::_EOF, "", std::monostate(), line);

	return tokens;
}

bool Scanner::isAtEnd()
{
	return current >= source.size();
}

void Scanner::scanToken()
{
	char c = advance();
	switch (c)
	{
		case '(': addToken(TokenType::LEFT_PAREN); break;
		case ')': addToken(TokenType::RIGHT_PAREN); break;
		case '{': addToken(TokenType::LEFT_BRACE); break;
		case '}': addToken(TokenType::RIGHT_BRACE); break;
		case ',': addToken(TokenType::COMMA); break;
		case '.': addToken(TokenType::DOT); break;
		case '-': addToken(TokenType::MINUS); break;
		case '+': addToken(TokenType::PLUS); break;
		case ';': addToken(TokenType::SEMICOLON); break;
		case '*': addToken(TokenType::STAR); break;
		case '!': addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
		case '=': addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
		case '<': addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
		case '>': addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
		case '/':
			if (match('/'))
			{
				// A comment goes until the end of the line.
				while (peek() != '\n' && !isAtEnd()) advance();
			}
			else
			{
				addToken(TokenType::SLASH);
			}
			break;
		case ' ':
		case '\r':
		case '\t':
			// Ignore whitespace.
			break;

		case '\n': line++; break;
		case '"': string(); break;

		default:
			if (isDigit(c))
			{
				number();
			}
			else if (isAlpha(c))
			{
				identifier();
			}
			else
			{
				Lox::error(line, "Unexpected character.");
			}
	}
}

char Scanner::advance()
{
	current++;
	return source.at(current - 1);
}

void Scanner::addToken(TokenType type)
{
	addToken(type, std::monostate());
}

void Scanner::addToken(TokenType type, Token::literal_t literal)
{
	auto text = source.substr(start, current - start);
	tokens.emplace_back(type, text, literal, line);
}

bool Scanner::match(char expected)
{
	if (isAtEnd())
		return false;
	if (source.at(current) != expected)
		return false;

	current++;
	return true;
}

char Scanner::peek()
{
	if (isAtEnd())
		return '\0';
	return source.at(current);
}

void Scanner::string()
{
	while (peek() != '"' && !isAtEnd())
	{
		if (peek() == '\n')
			line++;
		advance();
	}

	if (isAtEnd())
	{
		Lox::error(line, "Unterminated string.");
		return;
	}

	// The closing ".
	advance();

	// Trim the surrounding quotes.
	addToken(TokenType::STRING, std::string(source.substr(start + 1, current - start - 1)));
}

bool Scanner::isDigit(char c)
{
	return c >= '0' && c <= '9';
}

void Scanner::number()
{
	while (isDigit(peek())) advance();

	// Look for a fractional part.
	if (peek() == '.' && isDigit(peekNext()))
	{
		// Consume the "."
		advance();

		while (isDigit(peek())) advance();
	}

	double result;
	if (auto [p, ec] = std::from_chars(source.data() + start, source.data() + current, result); ec == std::errc())
	{
		addToken(TokenType::NUMBER, result);
	}
	else
	{
		Lox::error(line, "Cannot parse number");
	}
}

char Scanner::peekNext()
{
	if (current + 1 >= source.length())
		return '\0';
	return source.at(current + 1);
}

void Scanner::identifier()
{
	while (isAlphaNumeric(peek())) advance();
	std::string text = source.substr(start, current - start);
	TokenType type;
	if (keywords.contains(text))
		type = keywords.at(text);
	else
		type = TokenType::IDENTIFIER;
	addToken(type);
}

bool Scanner::isAlpha(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::isAlphaNumeric(char c)
{
	return isAlpha(c) || isDigit(c);
}
