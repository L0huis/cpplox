//
// Created by julianlohuis on 23/11/2020.
//

#include "AstPrinter.h"

#include <sstream>

std::string AstPrinter::print(Expr<std::string>* expr)
{
	return expr->accept(this);
}

std::string AstPrinter::visitBinaryExpr(Binary<std::string>* expr)
{
	return parenthesize(expr->op.lexeme, expr->left, expr->right);
}

std::string AstPrinter::visitGroupingExpr(Grouping<std::string>* expr)
{
	return parenthesize("group", expr->expression);
}

std::string AstPrinter::visitLiteralExpr(Literal<std::string>* expr)
{
	switch (expr->value.index())
	{
		case 0: return "nil";
		case 1: return std::get<std::string>(expr->value);
		case 2: return std::to_string(std::get<double>(expr->value));
	}
	return "";
}

std::string AstPrinter::visitUnaryExpr(Unary<std::string>* expr)
{
	return parenthesize(expr->op.lexeme, expr->right);
}

template<typename... Args>
std::string AstPrinter::parenthesize(std::string name, Args... args)
{
	std::stringstream ss;

	ss << '(' << name;
	(void)std::initializer_list<int> { [&, This = this](auto& arg) {
		ss << ' ' << arg->accept(This);
		return 0;
	}(args)... };
	ss << ')';

	return ss.str();
}
