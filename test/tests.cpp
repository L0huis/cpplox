#include <catch2/catch.hpp>
#include <fstream>
#include <string>
#include <cstdio>

#include "vm.h"

static std::string read_file(const char* path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(74);
    }

    file.seekg(0L, std::ios::end);
    auto size = file.tellg();
    file.seekg(0L, std::ios::beg);

    std::string buffer(size, '\0');

    std::copy(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), buffer.begin());

    return buffer;
}

TEST_CASE("bool__equality", "[bool]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\bool\equality.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("bool__not", "[bool]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\bool\not.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("constructor__default_arguments", "[constructor]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\constructor\default_arguments.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("constructor__extra_arguments", "[constructor]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\constructor\extra_arguments.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("constructor__call_init_explicitly", "[constructor]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\constructor\call_init_explicitly.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("constructor__return_in_nested_function", "[constructor]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\constructor\return_in_nested_function.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("constructor__early_return", "[constructor]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\constructor\early_return.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("constructor__call_init_early_return", "[constructor]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\constructor\call_init_early_return.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("constructor__arguments", "[constructor]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\constructor\arguments.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("constructor__missing_arguments", "[constructor]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\constructor\missing_arguments.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("constructor__return_value", "[constructor]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\constructor\return_value.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("constructor__init_not_method", "[constructor]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\constructor\init_not_method.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("constructor__default", "[constructor]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\constructor\default.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("call__object", "[call]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\call\object.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("call__string", "[call]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\call\string.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("call__nil", "[call]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\call\nil.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("call__bool", "[call]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\call\bool.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("call__num", "[call]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\call\num.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("string__error_after_multiline", "[string]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\string\error_after_multiline.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("string__multiline", "[string]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\string\multiline.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("string__literals", "[string]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\string\literals.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("string__unterminated", "[string]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\string\unterminated.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("operator__less_num_nonnum", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\less_num_nonnum.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__greater_num_nonnum", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\greater_num_nonnum.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__not_class", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\not_class.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("operator__less_or_equal_num_nonnum", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\less_or_equal_num_nonnum.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__add_num_nil", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\add_num_nil.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__divide", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\divide.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("operator__greater_or_equal_num_nonnum", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\greater_or_equal_num_nonnum.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__equals", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\equals.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("operator__less_nonnum_num", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\less_nonnum_num.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__add_bool_string", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\add_bool_string.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__less_or_equal_nonnum_num", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\less_or_equal_nonnum_num.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__not_equals", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\not_equals.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("operator__multiply_num_nonnum", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\multiply_num_nonnum.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__add_nil_nil", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\add_nil_nil.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__greater_or_equal_nonnum_num", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\greater_or_equal_nonnum_num.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__subtract", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\subtract.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("operator__subtract_num_nonnum", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\subtract_num_nonnum.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__comparison", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\comparison.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("operator__divide_nonnum_num", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\divide_nonnum_num.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__divide_num_nonnum", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\divide_num_nonnum.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__add_bool_num", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\add_bool_num.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__not", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\not.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("operator__subtract_nonnum_num", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\subtract_nonnum_num.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__negate_nonnum", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\negate_nonnum.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__equals_method", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\equals_method.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("operator__multiply_nonnum_num", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\multiply_nonnum_num.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__multiply", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\multiply.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("operator__greater_nonnum_num", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\greater_nonnum_num.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__equals_class", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\equals_class.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("operator__add_string_nil", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\add_string_nil.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__negate", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\negate.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("operator__add_bool_nil", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\add_bool_nil.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__add", "[operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\operator\add.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("while__closure_in_body", "[while]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\while\closure_in_body.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("while__syntax", "[while]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\while\syntax.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("while__return_inside", "[while]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\while\return_inside.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("while__fun_in_body", "[while]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\while\fun_in_body.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("while__var_in_body", "[while]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\while\var_in_body.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("while__class_in_body", "[while]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\while\class_in_body.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("while__return_closure", "[while]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\while\return_closure.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("return__after_while", "[return]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\return\after_while.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("return__after_if", "[return]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\return\after_if.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("return__in_method", "[return]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\return\in_method.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("return__in_function", "[return]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\return\in_function.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("return__at_top_level", "[return]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\return\at_top_level.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("return__after_else", "[return]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\return\after_else.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("return__return_nil_if_no_value", "[return]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\return\return_nil_if_no_value.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("number__nan_equality", "[number]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\number\nan_equality.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("number__leading_dot", "[number]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\number\leading_dot.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("number__decimal_point_at_eof", "[number]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\number\decimal_point_at_eof.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("number__literals", "[number]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\number\literals.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("number__trailing_dot", "[number]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\number\trailing_dot.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("super__extra_arguments", "[super]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\super\extra_arguments.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("super__no_superclass_method", "[super]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\super\no_superclass_method.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("super__no_superclass_call", "[super]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\super\no_superclass_call.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("super__super_in_closure_in_inherited_method", "[super]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\super\super_in_closure_in_inherited_method.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("super__no_superclass_bind", "[super]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\super\no_superclass_bind.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("super__call_same_method", "[super]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\super\call_same_method.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("super__this_in_superclass_method", "[super]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\super\this_in_superclass_method.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("super__closure", "[super]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\super\closure.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("super__call_other_method", "[super]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\super\call_other_method.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("super__super_without_name", "[super]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\super\super_without_name.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("super__missing_arguments", "[super]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\super\missing_arguments.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("super__indirectly_inherited", "[super]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\super\indirectly_inherited.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("super__super_in_top_level_function", "[super]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\super\super_in_top_level_function.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("super__super_without_dot", "[super]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\super\super_without_dot.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("super__super_at_top_level", "[super]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\super\super_at_top_level.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("super__parenthesized", "[super]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\super\parenthesized.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("super__constructor", "[super]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\super\constructor.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("super__super_in_inherited_method", "[super]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\super\super_in_inherited_method.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("super__reassign_superclass", "[super]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\super\reassign_superclass.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("super__bound_method", "[super]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\super\bound_method.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("if__var_in_then", "[if]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\if\var_in_then.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("if__truth", "[if]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\if\truth.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("if__else", "[if]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\if\else.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("if__dangling_else", "[if]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\if\dangling_else.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("if__var_in_else", "[if]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\if\var_in_else.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("if__class_in_else", "[if]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\if\class_in_else.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("if__if", "[if]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\if\if.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("if__class_in_then", "[if]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\if\class_in_then.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("if__fun_in_else", "[if]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\if\fun_in_else.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("if__fun_in_then", "[if]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\if\fun_in_then.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("variable__undefined_global", "[variable]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\variable\undefined_global.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("variable__in_middle_of_block", "[variable]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\variable\in_middle_of_block.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__unreached_undefined", "[variable]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\variable\unreached_undefined.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__collide_with_parameter", "[variable]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\variable\collide_with_parameter.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("variable__undefined_local", "[variable]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\variable\undefined_local.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("variable__duplicate_local", "[variable]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\variable\duplicate_local.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("variable__use_this_as_var", "[variable]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\variable\use_this_as_var.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("variable__scope_reuse_in_different_blocks", "[variable]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\variable\scope_reuse_in_different_blocks.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__redeclare_global", "[variable]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\variable\redeclare_global.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__redefine_global", "[variable]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\variable\redefine_global.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__use_false_as_var", "[variable]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\variable\use_false_as_var.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("variable__in_nested_block", "[variable]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\variable\in_nested_block.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__local_from_method", "[variable]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\variable\local_from_method.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__use_local_in_initializer", "[variable]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\variable\use_local_in_initializer.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("variable__shadow_and_local", "[variable]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\variable\shadow_and_local.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__shadow_local", "[variable]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\variable\shadow_local.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__use_nil_as_var", "[variable]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\variable\use_nil_as_var.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("variable__shadow_global", "[variable]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\variable\shadow_global.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__uninitialized", "[variable]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\variable\uninitialized.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__use_global_in_initializer", "[variable]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\variable\use_global_in_initializer.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__early_bound", "[variable]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\variable\early_bound.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__duplicate_parameter", "[variable]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\variable\duplicate_parameter.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("inheritance__inherit_from_function", "[inheritance]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\inheritance\inherit_from_function.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("inheritance__set_fields_from_base_class", "[inheritance]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\inheritance\set_fields_from_base_class.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("inheritance__constructor", "[inheritance]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\inheritance\constructor.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("inheritance__inherit_from_nil", "[inheritance]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\inheritance\inherit_from_nil.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("inheritance__inherit_from_number", "[inheritance]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\inheritance\inherit_from_number.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("inheritance__inherit_methods", "[inheritance]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\inheritance\inherit_methods.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("inheritance__parenthesized_superclass", "[inheritance]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\inheritance\parenthesized_superclass.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("field__set_on_nil", "[field]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\field\set_on_nil.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__get_on_string", "[field]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\field\get_on_string.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__get_on_class", "[field]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\field\get_on_class.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__call_nonfunction_field", "[field]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\field\call_nonfunction_field.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__method_binds_this", "[field]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\field\method_binds_this.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("field__set_on_num", "[field]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\field\set_on_num.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__on_instance", "[field]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\field\on_instance.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("field__set_on_function", "[field]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\field\set_on_function.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__get_on_nil", "[field]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\field\get_on_nil.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__undefined", "[field]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\field\undefined.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__call_function_field", "[field]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\field\call_function_field.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("field__get_and_set_method", "[field]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\field\get_and_set_method.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("field__get_on_function", "[field]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\field\get_on_function.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__get_on_bool", "[field]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\field\get_on_bool.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__method", "[field]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\field\method.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("field__set_on_class", "[field]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\field\set_on_class.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__get_on_num", "[field]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\field\get_on_num.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__many", "[field]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\field\many.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("field__set_on_string", "[field]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\field\set_on_string.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__set_on_bool", "[field]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\field\set_on_bool.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__set_evaluation_order", "[field]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\field\set_evaluation_order.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("method__extra_arguments", "[method]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\method\extra_arguments.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("method__arity", "[method]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\method\arity.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("method__too_many_parameters", "[method]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\method\too_many_parameters.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("method__missing_arguments", "[method]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\method\missing_arguments.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("method__not_found", "[method]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\method\not_found.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("method__too_many_arguments", "[method]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\method\too_many_arguments.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("method__print_bound_method", "[method]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\method\print_bound_method.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("method__empty_block", "[method]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\method\empty_block.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("method__refer_to_name", "[method]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\method\refer_to_name.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("regression__394", "[regression]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\regression\394.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("regression__40", "[regression]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\regression\40.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("assignment__grouping", "[assignment]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\assignment\grouping.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("assignment__syntax", "[assignment]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\assignment\syntax.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("assignment__infix_operator", "[assignment]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\assignment\infix_operator.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("assignment__undefined", "[assignment]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\assignment\undefined.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("assignment__prefix_operator", "[assignment]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\assignment\prefix_operator.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("assignment__associativity", "[assignment]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\assignment\associativity.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("assignment__local", "[assignment]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\assignment\local.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("assignment__to_this", "[assignment]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\assignment\to_this.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("assignment__global", "[assignment]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\assignment\global.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("scanning__punctuators", "[scanning]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\scanning\punctuators.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("scanning__whitespace", "[scanning]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\scanning\whitespace.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("scanning__numbers", "[scanning]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\scanning\numbers.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("scanning__strings", "[scanning]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\scanning\strings.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("scanning__identifiers", "[scanning]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\scanning\identifiers.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("scanning__keywords", "[scanning]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\scanning\keywords.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("nil__literal", "[nil]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\nil\literal.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("for__statement_initializer", "[for]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\for\statement_initializer.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("for__closure_in_body", "[for]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\for\closure_in_body.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("for__syntax", "[for]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\for\syntax.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("for__return_inside", "[for]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\for\return_inside.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("for__statement_increment", "[for]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\for\statement_increment.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("for__fun_in_body", "[for]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\for\fun_in_body.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("for__var_in_body", "[for]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\for\var_in_body.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("for__class_in_body", "[for]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\for\class_in_body.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("for__scope", "[for]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\for\scope.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("for__return_closure", "[for]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\for\return_closure.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("for__statement_condition", "[for]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\for\statement_condition.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("comments__line_at_eof", "[comments]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\comments\line_at_eof.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("comments__only_line_comment_and_line", "[comments]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\comments\only_line_comment_and_line.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("comments__only_line_comment", "[comments]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\comments\only_line_comment.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("comments__unicode", "[comments]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\comments\unicode.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("expressions__parse", "[expressions]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\expressions\parse.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("expressions__evaluate", "[expressions]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\expressions\evaluate.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("logical_operator__or_truth", "[logical_operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\logical_operator\or_truth.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("logical_operator__and_truth", "[logical_operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\logical_operator\and_truth.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("logical_operator__or", "[logical_operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\logical_operator\or.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("logical_operator__and", "[logical_operator]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\logical_operator\and.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("limit__too_many_upvalues", "[limit]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\limit\too_many_upvalues.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("limit__too_many_locals", "[limit]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\limit\too_many_locals.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("limit__no_reuse_constants", "[limit]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\limit\no_reuse_constants.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("limit__stack_overflow", "[limit]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\limit\stack_overflow.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("limit__too_many_constants", "[limit]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\limit\too_many_constants.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("class__empty", "[class]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\class\empty.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("class__inherit_self", "[class]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\class\inherit_self.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("class__reference_self", "[class]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\class\reference_self.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("class__local_inherit_other", "[class]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\class\local_inherit_other.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("class__inherited_method", "[class]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\class\inherited_method.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("class__local_reference_self", "[class]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\class\local_reference_self.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("class__local_inherit_self", "[class]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\class\local_inherit_self.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("closure__close_over_function_parameter", "[closure]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\closure\close_over_function_parameter.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__reuse_closure_slot", "[closure]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\closure\reuse_closure_slot.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__close_over_later_variable", "[closure]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\closure\close_over_later_variable.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__nested_closure", "[closure]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\closure\nested_closure.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__assign_to_shadowed_later", "[closure]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\closure\assign_to_shadowed_later.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__shadow_closure_with_local", "[closure]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\closure\shadow_closure_with_local.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__unused_later_closure", "[closure]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\closure\unused_later_closure.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__closed_closure_in_function", "[closure]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\closure\closed_closure_in_function.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__unused_closure", "[closure]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\closure\unused_closure.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__assign_to_closure", "[closure]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\closure\assign_to_closure.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__reference_closure_multiple_times", "[closure]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\closure\reference_closure_multiple_times.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__open_closure_in_function", "[closure]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\closure\open_closure_in_function.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__close_over_method_parameter", "[closure]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\closure\close_over_method_parameter.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("block__empty", "[block]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\block\empty.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("block__scope", "[block]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\block\scope.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("print__missing_argument", "[print]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\print\missing_argument.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("this__this_at_top_level", "[this]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\this\this_at_top_level.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("this__nested_closure", "[this]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\this\nested_closure.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("this__nested_class", "[this]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\this\nested_class.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("this__closure", "[this]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\this\closure.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("this__this_in_method", "[this]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\this\this_in_method.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("this__this_in_top_level_function", "[this]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\this\this_in_top_level_function.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("function__extra_arguments", "[function]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\function\extra_arguments.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("function__too_many_parameters", "[function]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\function\too_many_parameters.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("function__local_recursion", "[function]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\function\local_recursion.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("function__missing_comma_in_parameters", "[function]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\function\missing_comma_in_parameters.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("function__missing_arguments", "[function]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\function\missing_arguments.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("function__empty_body", "[function]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\function\empty_body.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("function__body_must_be_block", "[function]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\function\body_must_be_block.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("function__recursion", "[function]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\function\recursion.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("function__local_mutual_recursion", "[function]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\function\local_mutual_recursion.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("function__print", "[function]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\function\print.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("function__too_many_arguments", "[function]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\function\too_many_arguments.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("function__mutual_recursion", "[function]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\function\mutual_recursion.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("function__parameters", "[function]")
{
    initVM();
    auto source = read_file(R"(S:\C++\cpplox\test\loxsrc\function\parameters.lox)");
    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}
