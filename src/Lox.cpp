//
// Created by julianlohuis on 22/11/2020.
//

#include "Lox.h"

#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>
#include <iterator>
#include <string>
#include <iostream>
#include <fmt/format.h>

namespace Lox
{
void runFile(const char* filename)
{
	std::string bytes = [filename]() {
		std::string bytes;
		std::ifstream file(filename, std::ios::binary);
		std::copy(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(),
				  std::back_insert_iterator(bytes));
		return bytes;
	}();

	run(bytes);

	// Indicate an error in the exit code
	if (hadError) std::exit(65);
}

void runPrompt()
{
	std::string line;
	do {
		std::cout << "> ";
		run(line);
		hadError = false;
	} while (std::getline(std::cin, line));
}

void run(const std::string& source)
{
	Scanner scanner(source);
	std::vector<Token> tokens = scanner.scanTokens();
	Parser parser(tokens);
	auto* expression = parser.parse();

	if (hadError) return;

	AstPrinter astp;
	std::cout << astp.print(expression);
}

void error(int line, const std::string& message)
{
	report(line, "", message);
}

void Lox::error(const Token& token, const std::string& message)
{
	if (token.type == TokenType::END_OF_FILE) { report(token.line, " at end", message); }
	else
	{
		report(token.line, " at '" + token.lexeme + "'", message);
	}
}

void report(int line, std::string where, std::string message)
{
	fmt::print("[line {}] Error {}: {}\n", line, where, message);
}
}  // namespace Lox
