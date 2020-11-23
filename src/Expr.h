//
// Created by julianlohuis on 23/11/2020.
//

#ifndef CPPLOX_EXPR_H
#define CPPLOX_EXPR_H

#include "Token.h"

template<typename T>
struct Visitor;

template<typename T>
struct Expr
{
	virtual T accept(Visitor<T>* visitor) = 0;
	virtual ~Expr() = default;
};

template<typename T>
struct Binary : public Expr<T>
{
	Expr<T>* left;
	Token op;
	Expr<T>* right;
	Binary(Expr<T>* _left, Token _op, Expr<T>* _right)
		: left(_left)
		, op(_op)
		, right(_right)
	{
	}
	T accept(Visitor<T>* visitor)
	{
		return visitor->visitBinaryExpr(this);
	}
};

template<typename T>
struct Grouping : public Expr<T>
{
	Expr<T>* expression;
	Grouping(Expr<T>* _expression)
		: expression(_expression)
	{
	}
	T accept(Visitor<T>* visitor)
	{
		return visitor->visitGroupingExpr(this);
	}
};

template<typename T>
struct Literal : public Expr<T>
{
	Token::literal_t value;
	Literal(Token::literal_t _value)
		: value(_value)
	{
	}
	T accept(Visitor<T>* visitor)
	{
		return visitor->visitLiteralExpr(this);
	}
};

template<typename T>
struct Unary : public Expr<T>
{
	Token op;
	Expr<T>* right;
	Unary(Token _op, Expr<T>* _right)
		: op(_op)
		, right(_right)
	{
	}
	T accept(Visitor<T>* visitor)
	{
		return visitor->visitUnaryExpr(this);
	}
};

template<typename T>
struct Visitor
{
	virtual T visitBinaryExpr(Binary<T>* expr) = 0;
	virtual T visitGroupingExpr(Grouping<T>* expr) = 0;
	virtual T visitLiteralExpr(Literal<T>* expr) = 0;
	virtual T visitUnaryExpr(Unary<T>* expr) = 0;
};

#endif	//CPPLOX_EXPR_H
