
#include <iostream>
#include "Lox.h"
#include "AstPrinter.h"

int main(int argc, const char** argv)
{
	using S = std::string;
	Expr<S>* expression = new Binary<S>(new Unary<S>(Token(TokenType::MINUS, "-", std::monostate(), 1), new Literal<S>(123.0)),
								   Token(TokenType::STAR, "*", std::monostate(), 1), new Grouping<S>(new Literal<S>(45.67)));

	AstPrinter astp;
	std::cout << astp.print(expression);

	return 0;

#if 0
	if (argc > 2)
	{
		std::cout << "Usage: cpplox [script]\n";
	}
	else if (argc == 2)
	{
		Lox::runFile(argv[1]);
	}
	else
	{
		Lox::runPrompt();
	}
#endif
}