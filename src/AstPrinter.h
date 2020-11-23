//
// Created by julianlohuis on 23/11/2020.
//

#ifndef CPPLOX_ASTPRINTER_H
#define CPPLOX_ASTPRINTER_H

#include "Expr.h"

class AstPrinter : public Visitor<std::string>
{
public:
	std::string print(Expr<std::string>* expr);
	std::string visitBinaryExpr(Binary<std::string>* expr) final;
	std::string visitGroupingExpr(Grouping<std::string>* expr) final;
	std::string visitLiteralExpr(Literal<std::string>* expr) final;
	std::string visitUnaryExpr(Unary<std::string>* expr) final;

private:
	template<typename ...Ts>
	std::string parenthesize(std::string name, Ts ... ts);
};

#endif	//CPPLOX_ASTPRINTER_H
