
#include <iostream>
#include "Lox.h"
#include "AstPrinter.h"

int main(int argc, const char** argv)
{
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
}