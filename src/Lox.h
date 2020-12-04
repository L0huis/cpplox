//
// Created by julianlohuis on 22/11/2020.
//

#ifndef CPPLOX_LOX_H
#define CPPLOX_LOX_H

#include <string>
#include "Scanner.h"
#include "Parser.h"

#include "AstPrinter.h"

namespace Lox
{
static bool hadError = false;

void runFile(const char* filename);
void runPrompt();
void run(const std::string& source);

void error(int line, const std::string& message);
void error(const Token& token, const std::string& message);
void report(int line, std::string where, std::string message);
}  // namespace Lox

#endif	//CPPLOX_LOX_H
