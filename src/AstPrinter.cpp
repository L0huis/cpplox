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
    return parenthesize(expr->op.lexeme, expr->left.get(), expr->right.get());
}

std::string AstPrinter::visitGroupingExpr(Grouping<std::string>* expr)
{
    return parenthesize("group", expr->expression.get());
}

// Helper vor the visitor stuff
template<class... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;
using namespace std::string_literals;

std::string AstPrinter::visitLiteralExpr(Literal<std::string>* expr)
{
    return std::visit(overloaded{ [](auto arg) { return ""s; },
                                  [](std::monostate arg) { return "nil"s; },
                                  [](bool arg) { return arg ? "true"s : "false"s; },
                                  [](std::string arg) { return arg; },
                                  [](double arg) {
                                      return std::to_string(arg);
                                  } },
                      expr->value);
}

std::string AstPrinter::visitUnaryExpr(Unary<std::string>* expr)
{
    return parenthesize(expr->op.lexeme, expr->right.get());
}

template<typename... Args>
std::string AstPrinter::parenthesize(std::string name, Args... args)
{
    std::stringstream ss;

    ss << '(' << name;
    (void)std::initializer_list<int>{ [&](auto& arg) {
        ss << ' ' << arg->accept(this);
        return 0;
    }(args)... };
    ss << ')';

    return ss.str();
}
