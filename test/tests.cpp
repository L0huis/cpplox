#include <catch2/catch.hpp>

#include "vm.h"

TEST_CASE("bool__equality", "[bool]")
{
    initVM();

    auto source = R"???(
print true == true;    // expect: true
print true == false;   // expect: false
print false == true;   // expect: false
print false == false;  // expect: true

// Not equal to other types.
print true == 1;        // expect: false
print false == 0;       // expect: false
print true == "true";   // expect: false
print false == "false"; // expect: false
print false == "";      // expect: false

print true != true;    // expect: false
print true != false;   // expect: true
print false != true;   // expect: true
print false != false;  // expect: false

// Not equal to other types.
print true != 1;        // expect: true
print false != 0;       // expect: true
print true != "true";   // expect: true
print false != "false"; // expect: true
print false != "";      // expect: true

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("bool__not", "[bool]")
{
    initVM();

    auto source = R"???(
print !true;    // expect: false
print !false;   // expect: true
print !!true;   // expect: true

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("constructor__default_arguments", "[constructor]")
{
    initVM();

    auto source = R"???(
class Foo {}

var foo = Foo(1, 2, 3); // expect runtime error: Expected 0 arguments but got 3.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("constructor__extra_arguments", "[constructor]")
{
    initVM();

    auto source = R"???(
class Foo {
  init(a, b) {
    this.a = a;
    this.b = b;
  }
}

var foo = Foo(1, 2, 3, 4); // expect runtime error: Expected 2 arguments but got 4.
)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("constructor__call_init_explicitly", "[constructor]")
{
    initVM();

    auto source = R"???(
class Foo {
  init(arg) {
    print "Foo.init(" + arg + ")";
    this.field = "init";
  }
}

var foo = Foo("one"); // expect: Foo.init(one)
foo.field = "field";

var foo2 = foo.init("two"); // expect: Foo.init(two)
print foo2; // expect: Foo instance

// Make sure init() doesn't create a fresh instance.
print foo.field; // expect: init

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("constructor__return_in_nested_function", "[constructor]")
{
    initVM();

    auto source = R"???(
class Foo {
  init() {
    fun init() {
      return "bar";
    }
    print init(); // expect: bar
  }
}

print Foo(); // expect: Foo instance

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("constructor__early_return", "[constructor]")
{
    initVM();

    auto source = R"???(
class Foo {
  init() {
    print "init";
    return;
    print "nope";
  }
}

var foo = Foo(); // expect: init
print foo; // expect: Foo instance

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("constructor__call_init_early_return", "[constructor]")
{
    initVM();

    auto source = R"???(
class Foo {
  init() {
    print "init";
    return;
    print "nope";
  }
}

var foo = Foo(); // expect: init
print foo.init(); // expect: init
// expect: Foo instance

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("constructor__arguments", "[constructor]")
{
    initVM();

    auto source = R"???(
class Foo {
  init(a, b) {
    print "init"; // expect: init
    this.a = a;
    this.b = b;
  }
}

var foo = Foo(1, 2);
print foo.a; // expect: 1
print foo.b; // expect: 2

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("constructor__missing_arguments", "[constructor]")
{
    initVM();

    auto source = R"???(
class Foo {
  init(a, b) {}
}

var foo = Foo(1); // expect runtime error: Expected 2 arguments but got 1.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("constructor__return_value", "[constructor]")
{
    initVM();

    auto source = R"???(
class Foo {
  init() {
    return "result"; // Error at 'return': Can't return a value from an initializer.
  }
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("constructor__init_not_method", "[constructor]")
{
    initVM();

    auto source = R"???(
class Foo {
  init(arg) {
    print "Foo.init(" + arg + ")";
    this.field = "init";
  }
}

fun init() {
  print "not initializer";
}

init(); // expect: not initializer

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("constructor__default", "[constructor]")
{
    initVM();

    auto source = R"???(
class Foo {}

var foo = Foo();
print foo; // expect: Foo instance

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("call__object", "[call]")
{
    initVM();

    auto source = R"???(
class Foo {}

var foo = Foo();
foo(); // expect runtime error: Can only call functions and classes.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("call__string", "[call]")
{
    initVM();

    auto source = R"???(
"str"(); // expect runtime error: Can only call functions and classes.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("call__nil", "[call]")
{
    initVM();

    auto source = R"???(
nil(); // expect runtime error: Can only call functions and classes.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("call__bool", "[call]")
{
    initVM();

    auto source = R"???(
true(); // expect runtime error: Can only call functions and classes.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("call__num", "[call]")
{
    initVM();

    auto source = R"???(
123(); // expect runtime error: Can only call functions and classes.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("string__error_after_multiline", "[string]")
{
    initVM();

    auto source = R"???(
// Tests that we correctly track the line info across multiline strings.
var a = "1
2
3
";

err; // // expect runtime error: Undefined variable 'err'.
)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("string__multiline", "[string]")
{
    initVM();

    auto source = R"???(
var a = "1
2
3";
print a;
// expect: 1
// expect: 2
// expect: 3

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("string__literals", "[string]")
{
    initVM();

    auto source = R"???(
print "(" + "" + ")";   // expect: ()
print "a string"; // expect: a string

// Non-ASCII.
print "A~¶Þॐஃ"; // expect: A~¶Þॐஃ

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("string__unterminated", "[string]")
{
    initVM();

    auto source = R"???(
// [line 2] Error: Unterminated string.
"this string has no close quote
)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("operator__less_num_nonnum", "[operator]")
{
    initVM();

    auto source = R"???(
1 < "1"; // expect runtime error: Operands must be numbers.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__greater_num_nonnum", "[operator]")
{
    initVM();

    auto source = R"???(
1 > "1"; // expect runtime error: Operands must be numbers.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__not_class", "[operator]")
{
    initVM();

    auto source = R"???(
class Bar {}
print !Bar;      // expect: false
print !Bar();    // expect: false

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("operator__less_or_equal_num_nonnum", "[operator]")
{
    initVM();

    auto source = R"???(
1 <= "1"; // expect runtime error: Operands must be numbers.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__add_num_nil", "[operator]")
{
    initVM();

    auto source = R"???(
1 + nil; // expect runtime error: Operands must be two numbers or two strings.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__divide", "[operator]")
{
    initVM();

    auto source = R"???(
print 8 / 2;         // expect: 4
print 12.34 / 12.34;  // expect: 1

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("operator__greater_or_equal_num_nonnum", "[operator]")
{
    initVM();

    auto source = R"???(
1 >= "1"; // expect runtime error: Operands must be numbers.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__equals", "[operator]")
{
    initVM();

    auto source = R"???(
print nil == nil; // expect: true

print true == true; // expect: true
print true == false; // expect: false

print 1 == 1; // expect: true
print 1 == 2; // expect: false

print "str" == "str"; // expect: true
print "str" == "ing"; // expect: false

print nil == false; // expect: false
print false == 0; // expect: false
print 0 == "0"; // expect: false

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("operator__less_nonnum_num", "[operator]")
{
    initVM();

    auto source = R"???(
"1" < 1; // expect runtime error: Operands must be numbers.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__add_bool_string", "[operator]")
{
    initVM();

    auto source = R"???(
true + "s"; // expect runtime error: Operands must be two numbers or two strings.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__less_or_equal_nonnum_num", "[operator]")
{
    initVM();

    auto source = R"???(
"1" <= 1; // expect runtime error: Operands must be numbers.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__not_equals", "[operator]")
{
    initVM();

    auto source = R"???(
print nil != nil; // expect: false

print true != true; // expect: false
print true != false; // expect: true

print 1 != 1; // expect: false
print 1 != 2; // expect: true

print "str" != "str"; // expect: false
print "str" != "ing"; // expect: true

print nil != false; // expect: true
print false != 0; // expect: true
print 0 != "0"; // expect: true

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("operator__multiply_num_nonnum", "[operator]")
{
    initVM();

    auto source = R"???(
1 * "1"; // expect runtime error: Operands must be numbers.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__add_nil_nil", "[operator]")
{
    initVM();

    auto source = R"???(
nil + nil; // expect runtime error: Operands must be two numbers or two strings.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__greater_or_equal_nonnum_num", "[operator]")
{
    initVM();

    auto source = R"???(
"1" >= 1; // expect runtime error: Operands must be numbers.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__subtract", "[operator]")
{
    initVM();

    auto source = R"???(
print 4 - 3; // expect: 1
print 1.2 - 1.2; // expect: 0

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("operator__subtract_num_nonnum", "[operator]")
{
    initVM();

    auto source = R"???(
1 - "1"; // expect runtime error: Operands must be numbers.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__comparison", "[operator]")
{
    initVM();

    auto source = R"???(
print 1 < 2;    // expect: true
print 2 < 2;    // expect: false
print 2 < 1;    // expect: false

print 1 <= 2;    // expect: true
print 2 <= 2;    // expect: true
print 2 <= 1;    // expect: false

print 1 > 2;    // expect: false
print 2 > 2;    // expect: false
print 2 > 1;    // expect: true

print 1 >= 2;    // expect: false
print 2 >= 2;    // expect: true
print 2 >= 1;    // expect: true

// Zero and negative zero compare the same.
print 0 < -0; // expect: false
print -0 < 0; // expect: false
print 0 > -0; // expect: false
print -0 > 0; // expect: false
print 0 <= -0; // expect: true
print -0 <= 0; // expect: true
print 0 >= -0; // expect: true
print -0 >= 0; // expect: true

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("operator__divide_nonnum_num", "[operator]")
{
    initVM();

    auto source = R"???(
"1" / 1; // expect runtime error: Operands must be numbers.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__divide_num_nonnum", "[operator]")
{
    initVM();

    auto source = R"???(
1 / "1"; // expect runtime error: Operands must be numbers.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__add_bool_num", "[operator]")
{
    initVM();

    auto source = R"???(
true + 123; // expect runtime error: Operands must be two numbers or two strings.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__not", "[operator]")
{
    initVM();

    auto source = R"???(
print !true;     // expect: false
print !false;    // expect: true
print !!true;    // expect: true

print !123;      // expect: false
print !0;        // expect: false

print !nil;     // expect: true

print !"";       // expect: false

fun foo() {}
print !foo;      // expect: false

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("operator__subtract_nonnum_num", "[operator]")
{
    initVM();

    auto source = R"???(
"1" - 1; // expect runtime error: Operands must be numbers.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__negate_nonnum", "[operator]")
{
    initVM();

    auto source = R"???(
-"s"; // expect runtime error: Operand must be a number.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__equals_method", "[operator]")
{
    initVM();

    auto source = R"???(
// Bound methods have identity equality.
class Foo {
  method() {}
}

var foo = Foo();
var fooMethod = foo.method;

// Same bound method.
print fooMethod == fooMethod; // expect: true

// Different closurizations.
print foo.method == foo.method; // expect: false

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("operator__multiply_nonnum_num", "[operator]")
{
    initVM();

    auto source = R"???(
"1" * 1; // expect runtime error: Operands must be numbers.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__multiply", "[operator]")
{
    initVM();

    auto source = R"???(
print 5 * 3; // expect: 15
print 12.34 * 0.3; // expect: 3.702

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("operator__greater_nonnum_num", "[operator]")
{
    initVM();

    auto source = R"???(
"1" > 1; // expect runtime error: Operands must be numbers.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__equals_class", "[operator]")
{
    initVM();

    auto source = R"???(
// Bound methods have identity equality.
class Foo {}
class Bar {}

print Foo == Foo; // expect: true
print Foo == Bar; // expect: false
print Bar == Foo; // expect: false
print Bar == Bar; // expect: true

print Foo == "Foo"; // expect: false
print Foo == nil;   // expect: false
print Foo == 123;   // expect: false
print Foo == true;  // expect: false

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("operator__add_string_nil", "[operator]")
{
    initVM();

    auto source = R"???(
"s" + nil; // expect runtime error: Operands must be two numbers or two strings.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__negate", "[operator]")
{
    initVM();

    auto source = R"???(
print -(3); // expect: -3
print --(3); // expect: 3
print ---(3); // expect: -3

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("operator__add_bool_nil", "[operator]")
{
    initVM();

    auto source = R"???(
true + nil; // expect runtime error: Operands must be two numbers or two strings.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("operator__add", "[operator]")
{
    initVM();

    auto source = R"???(
print 123 + 456; // expect: 579
print "str" + "ing"; // expect: string

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("while__closure_in_body", "[while]")
{
    initVM();

    auto source = R"???(
var f1;
var f2;
var f3;

var i = 1;
while (i < 4) {
  var j = i;
  fun f() { print j; }

  if (j == 1) f1 = f;
  else if (j == 2) f2 = f;
  else f3 = f;

  i = i + 1;
}

f1(); // expect: 1
f2(); // expect: 2
f3(); // expect: 3

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("while__syntax", "[while]")
{
    initVM();

    auto source = R"???(
// Single-expression body.
var c = 0;
while (c < 3) print c = c + 1;
// expect: 1
// expect: 2
// expect: 3

// Block body.
var a = 0;
while (a < 3) {
  print a;
  a = a + 1;
}
// expect: 0
// expect: 1
// expect: 2

// Statement bodies.
while (false) if (true) 1; else 2;
while (false) while (true) 1;
while (false) for (;;) 1;

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("while__return_inside", "[while]")
{
    initVM();

    auto source = R"???(
fun f() {
  while (true) {
    var i = "i";
    return i;
  }
}

print f();
// expect: i

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("while__fun_in_body", "[while]")
{
    initVM();

    auto source = R"???(
// [line 2] Error at 'fun': Expect expression.
while (true) fun foo() {}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("while__var_in_body", "[while]")
{
    initVM();

    auto source = R"???(
// [line 2] Error at 'var': Expect expression.
while (true) var foo;

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("while__class_in_body", "[while]")
{
    initVM();

    auto source = R"???(
// [line 2] Error at 'class': Expect expression.
while (true) class Foo {}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("while__return_closure", "[while]")
{
    initVM();

    auto source = R"???(
fun f() {
  while (true) {
    var i = "i";
    fun g() { print i; }
    return g;
  }
}

var h = f();
h(); // expect: i

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("return__after_while", "[return]")
{
    initVM();

    auto source = R"???(
fun f() {
  while (true) return "ok";
}

print f(); // expect: ok

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("return__after_if", "[return]")
{
    initVM();

    auto source = R"???(
fun f() {
  if (true) return "ok";
}

print f(); // expect: ok

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("return__in_method", "[return]")
{
    initVM();

    auto source = R"???(
class Foo {
  method() {
    return "ok";
    print "bad";
  }
}

print Foo().method(); // expect: ok

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("return__in_function", "[return]")
{
    initVM();

    auto source = R"???(
fun f() {
  return "ok";
  print "bad";
}

print f(); // expect: ok

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("return__at_top_level", "[return]")
{
    initVM();

    auto source = R"???(
return "wat"; // Error at 'return': Can't return from top-level code.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("return__after_else", "[return]")
{
    initVM();

    auto source = R"???(
fun f() {
  if (false) "no"; else return "ok";
}

print f(); // expect: ok

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("return__return_nil_if_no_value", "[return]")
{
    initVM();

    auto source = R"???(
fun f() {
  return;
  print "bad";
}

print f(); // expect: nil

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("number__nan_equality", "[number]")
{
    initVM();

    auto source = R"???(
var nan = 0/0;

print nan == 0; // expect: false
print nan != 1; // expect: true

// NaN is not equal to self.
print nan == nan; // expect: false
print nan != nan; // expect: true

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("number__leading_dot", "[number]")
{
    initVM();

    auto source = R"???(
// [line 2] Error at '.': Expect expression.
.123;

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("number__decimal_point_at_eof", "[number]")
{
    initVM();

    auto source = R"???(
// [line 2] Error at end: Expect property name after '.'.
123.
)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("number__literals", "[number]")
{
    initVM();

    auto source = R"???(
print 123;     // expect: 123
print 987654;  // expect: 987654
print 0;       // expect: 0
print -0;      // expect: -0

print 123.456; // expect: 123.456
print -0.001;  // expect: -0.001

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("number__trailing_dot", "[number]")
{
    initVM();

    auto source = R"???(
// [line 2] Error at ';': Expect property name after '.'.
123.;

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("super__extra_arguments", "[super]")
{
    initVM();

    auto source = R"???(
class Base {
  foo(a, b) {
    print "Base.foo(" + a + ", " + b + ")";
  }
}

class Derived < Base {
  foo() {
    print "Derived.foo()"; // expect: Derived.foo()
    super.foo("a", "b", "c", "d"); // expect runtime error: Expected 2 arguments but got 4.
  }
}

Derived().foo();

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("super__no_superclass_method", "[super]")
{
    initVM();

    auto source = R"???(
class Base {}

class Derived < Base {
  foo() {
    super.doesNotExist(1); // expect runtime error: Undefined property 'doesNotExist'.
  }
}

Derived().foo();

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("super__no_superclass_call", "[super]")
{
    initVM();

    auto source = R"???(
class Base {
  foo() {
    super.doesNotExist(1); // Error at 'super': Can't use 'super' in a class with no superclass.
  }
}

Base().foo();

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("super__super_in_closure_in_inherited_method", "[super]")
{
    initVM();

    auto source = R"???(
class A {
  say() {
    print "A";
  }
}

class B < A {
  getClosure() {
    fun closure() {
      super.say();
    }
    return closure;
  }

  say() {
    print "B";
  }
}

class C < B {
  say() {
    print "C";
  }
}

C().getClosure()(); // expect: A

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("super__no_superclass_bind", "[super]")
{
    initVM();

    auto source = R"???(
class Base {
  foo() {
    super.doesNotExist; // Error at 'super': Can't use 'super' in a class with no superclass.
  }
}

Base().foo();

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("super__call_same_method", "[super]")
{
    initVM();

    auto source = R"???(
class Base {
  foo() {
    print "Base.foo()";
  }
}

class Derived < Base {
  foo() {
    print "Derived.foo()";
    super.foo();
  }
}

Derived().foo();
// expect: Derived.foo()
// expect: Base.foo()

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("super__this_in_superclass_method", "[super]")
{
    initVM();

    auto source = R"???(
class Base {
  init(a) {
    this.a = a;
  }
}

class Derived < Base {
  init(a, b) {
    super.init(a);
    this.b = b;
  }
}

var derived = Derived("a", "b");
print derived.a; // expect: a
print derived.b; // expect: b

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("super__closure", "[super]")
{
    initVM();

    auto source = R"???(
class Base {
  toString() { return "Base"; }
}

class Derived < Base {
  getClosure() {
    fun closure() {
      return super.toString();
    }
    return closure;
  }

  toString() { return "Derived"; }
}

var closure = Derived().getClosure();
print closure(); // expect: Base

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("super__call_other_method", "[super]")
{
    initVM();

    auto source = R"???(
class Base {
  foo() {
    print "Base.foo()";
  }
}

class Derived < Base {
  bar() {
    print "Derived.bar()";
    super.foo();
  }
}

Derived().bar();
// expect: Derived.bar()
// expect: Base.foo()

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("super__super_without_name", "[super]")
{
    initVM();

    auto source = R"???(
class A {}

class B < A {
  method() {
    super.; // Error at ';': Expect superclass method name.
  }
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("super__missing_arguments", "[super]")
{
    initVM();

    auto source = R"???(
class Base {
  foo(a, b) {
    print "Base.foo(" + a + ", " + b + ")";
  }
}

class Derived < Base {
  foo() {
    super.foo(1); // expect runtime error: Expected 2 arguments but got 1.
  }
}

Derived().foo();

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("super__indirectly_inherited", "[super]")
{
    initVM();

    auto source = R"???(
class A {
  foo() {
    print "A.foo()";
  }
}

class B < A {}

class C < B {
  foo() {
    print "C.foo()";
    super.foo();
  }
}

C().foo();
// expect: C.foo()
// expect: A.foo()

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("super__super_in_top_level_function", "[super]")
{
    initVM();

    auto source = R"???(
  super.bar(); // Error at 'super': Can't use 'super' outside of a class.
fun foo() {
}
)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("super__super_without_dot", "[super]")
{
    initVM();

    auto source = R"???(
class A {}

class B < A {
  method() {
    // [line 6] Error at ';': Expect '.' after 'super'.
    super;
  }
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("super__super_at_top_level", "[super]")
{
    initVM();

    auto source = R"???(
super.foo("bar"); // Error at 'super': Can't use 'super' outside of a class.
super.foo; // Error at 'super': Can't use 'super' outside of a class.
)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("super__parenthesized", "[super]")
{
    initVM();

    auto source = R"???(
class A {
  method() {}
}

class B < A {
  method() {
    // [line 8] Error at ')': Expect '.' after 'super'.
    (super).method();
  }
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("super__constructor", "[super]")
{
    initVM();

    auto source = R"???(
class Base {
  init(a, b) {
    print "Base.init(" + a + ", " + b + ")";
  }
}

class Derived < Base {
  init() {
    print "Derived.init()";
    super.init("a", "b");
  }
}

Derived();
// expect: Derived.init()
// expect: Base.init(a, b)

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("super__super_in_inherited_method", "[super]")
{
    initVM();

    auto source = R"???(
class A {
  say() {
    print "A";
  }
}

class B < A {
  test() {
    super.say();
  }

  say() {
    print "B";
  }
}

class C < B {
  say() {
    print "C";
  }
}

C().test(); // expect: A

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("super__reassign_superclass", "[super]")
{
    initVM();

    auto source = R"???(
class Base {
  method() {
    print "Base.method()";
  }
}

class Derived < Base {
  method() {
    super.method();
  }
}

class OtherBase {
  method() {
    print "OtherBase.method()";
  }
}

var derived = Derived();
derived.method(); // expect: Base.method()
Base = OtherBase;
derived.method(); // expect: Base.method()

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("super__bound_method", "[super]")
{
    initVM();

    auto source = R"???(
class A {
  method(arg) {
    print "A.method(" + arg + ")";
  }
}

class B < A {
  getClosure() {
    return super.method;
  }

  method(arg) {
    print "B.method(" + arg + ")";
  }
}


var closure = B().getClosure();
closure("arg"); // expect: A.method(arg)

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("if__var_in_then", "[if]")
{
    initVM();

    auto source = R"???(
// [line 2] Error at 'var': Expect expression.
if (true) var foo;

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("if__truth", "[if]")
{
    initVM();

    auto source = R"???(
// False and nil are false.
if (false) print "bad"; else print "false"; // expect: false
if (nil) print "bad"; else print "nil"; // expect: nil

// Everything else is true.
if (true) print true; // expect: true
if (0) print 0; // expect: 0
if ("") print "empty"; // expect: empty

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("if__else", "[if]")
{
    initVM();

    auto source = R"???(
// Evaluate the 'else' expression if the condition is false.
if (true) print "good"; else print "bad"; // expect: good
if (false) print "bad"; else print "good"; // expect: good

// Allow block body.
if (false) nil; else { print "block"; } // expect: block

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("if__dangling_else", "[if]")
{
    initVM();

    auto source = R"???(
// A dangling else binds to the right-most if.
if (true) if (false) print "bad"; else print "good"; // expect: good
if (false) if (true) print "bad"; else print "bad";

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("if__var_in_else", "[if]")
{
    initVM();

    auto source = R"???(
// [line 2] Error at 'var': Expect expression.
if (true) "ok"; else var foo;

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("if__class_in_else", "[if]")
{
    initVM();

    auto source = R"???(
// [line 2] Error at 'class': Expect expression.
if (true) "ok"; else class Foo {}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("if__if", "[if]")
{
    initVM();

    auto source = R"???(
// Evaluate the 'then' expression if the condition is true.
if (true) print "good"; // expect: good
if (false) print "bad";

// Allow block body.
if (true) { print "block"; } // expect: block

// Assignment in if condition.
var a = false;
if (a = true) print a; // expect: true

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("if__class_in_then", "[if]")
{
    initVM();

    auto source = R"???(
// [line 2] Error at 'class': Expect expression.
if (true) class Foo {}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("if__fun_in_else", "[if]")
{
    initVM();

    auto source = R"???(
// [line 2] Error at 'fun': Expect expression.
if (true) "ok"; else fun foo() {}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("if__fun_in_then", "[if]")
{
    initVM();

    auto source = R"???(
// [line 2] Error at 'fun': Expect expression.
if (true) fun foo() {}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("variable__undefined_global", "[variable]")
{
    initVM();

    auto source = R"???(
print notDefined;  // expect runtime error: Undefined variable 'notDefined'.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("variable__in_middle_of_block", "[variable]")
{
    initVM();

    auto source = R"???(
{
  var a = "a";
  print a; // expect: a
  var b = a + " b";
  print b; // expect: a b
  var c = a + " c";
  print c; // expect: a c
  var d = b + " d";
  print d; // expect: a b d
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__unreached_undefined", "[variable]")
{
    initVM();

    auto source = R"???(
if (false) {
  print notDefined;
}

print "ok"; // expect: ok

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__collide_with_parameter", "[variable]")
{
    initVM();

    auto source = R"???(
fun foo(a) {
  var a; // Error at 'a': Already variable with this name in this scope.
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("variable__undefined_local", "[variable]")
{
    initVM();

    auto source = R"???(
{
  print notDefined;  // expect runtime error: Undefined variable 'notDefined'.
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("variable__duplicate_local", "[variable]")
{
    initVM();

    auto source = R"???(
{
  var a = "value";
  var a = "other"; // Error at 'a': Already variable with this name in this scope.
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("variable__use_this_as_var", "[variable]")
{
    initVM();

    auto source = R"???(
// [line 2] Error at 'this': Expect variable name.
var this = "value";

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("variable__scope_reuse_in_different_blocks", "[variable]")
{
    initVM();

    auto source = R"???(
{
  var a = "first";
  print a; // expect: first
}

{
  var a = "second";
  print a; // expect: second
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__redeclare_global", "[variable]")
{
    initVM();

    auto source = R"???(
var a = "1";
var a;
print a; // expect: nil

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__redefine_global", "[variable]")
{
    initVM();

    auto source = R"???(
var a = "1";
var a = "2";
print a; // expect: 2

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__use_false_as_var", "[variable]")
{
    initVM();

    auto source = R"???(
// [line 2] Error at 'false': Expect variable name.
var false = "value";

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("variable__in_nested_block", "[variable]")
{
    initVM();

    auto source = R"???(
{
  var a = "outer";
  {
    print a; // expect: outer
  }
}
)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__local_from_method", "[variable]")
{
    initVM();

    auto source = R"???(
var foo = "variable";

class Foo {
  method() {
    print foo;
  }
}

Foo().method(); // expect: variable

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__use_local_in_initializer", "[variable]")
{
    initVM();

    auto source = R"???(
var a = "outer";
{
  var a = a; // Error at 'a': Can't read local variable in its own initializer.
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("variable__shadow_and_local", "[variable]")
{
    initVM();

    auto source = R"???(
{
  var a = "outer";
  {
    print a; // expect: outer
    var a = "inner";
    print a; // expect: inner
  }
}
)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__shadow_local", "[variable]")
{
    initVM();

    auto source = R"???(
{
  var a = "local";
  {
    var a = "shadow";
    print a; // expect: shadow
  }
  print a; // expect: local
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__use_nil_as_var", "[variable]")
{
    initVM();

    auto source = R"???(
// [line 2] Error at 'nil': Expect variable name.
var nil = "value";

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("variable__shadow_global", "[variable]")
{
    initVM();

    auto source = R"???(
var a = "global";
{
  var a = "shadow";
  print a; // expect: shadow
}
print a; // expect: global

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__uninitialized", "[variable]")
{
    initVM();

    auto source = R"???(
var a;
print a; // expect: nil

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__use_global_in_initializer", "[variable]")
{
    initVM();

    auto source = R"???(
var a = "value";
var a = a;
print a; // expect: value

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__early_bound", "[variable]")
{
    initVM();

    auto source = R"???(
var a = "outer";
{
  fun foo() {
    print a;
  }

  foo(); // expect: outer
  var a = "inner";
  foo(); // expect: outer
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("variable__duplicate_parameter", "[variable]")
{
    initVM();

    auto source = R"???(
fun foo(arg,
        arg) { // Error at 'arg': Already variable with this name in this scope.
  "body";
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("inheritance__inherit_from_function", "[inheritance]")
{
    initVM();

    auto source = R"???(
fun foo() {}

class Subclass < foo {} // expect runtime error: Superclass must be a class.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("inheritance__set_fields_from_base_class", "[inheritance]")
{
    initVM();

    auto source = R"???(
class Foo {
  foo(a, b) {
    this.field1 = a;
    this.field2 = b;
  }

  fooPrint() {
    print this.field1;
    print this.field2;
  }
}

class Bar < Foo {
  bar(a, b) {
    this.field1 = a;
    this.field2 = b;
  }

  barPrint() {
    print this.field1;
    print this.field2;
  }
}

var bar = Bar();
bar.foo("foo 1", "foo 2");
bar.fooPrint();
// expect: foo 1
// expect: foo 2

bar.bar("bar 1", "bar 2");
bar.barPrint();
// expect: bar 1
// expect: bar 2

bar.fooPrint();
// expect: bar 1
// expect: bar 2

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("inheritance__constructor", "[inheritance]")
{
    initVM();

    auto source = R"???(
class A {
  init(param) {
    this.field = param;
  }

  test() {
    print this.field;
  }
}

class B < A {}

var b = B("value");
b.test(); // expect: value

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("inheritance__inherit_from_nil", "[inheritance]")
{
    initVM();

    auto source = R"???(
var Nil = nil;
class Foo < Nil {} // expect runtime error: Superclass must be a class.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("inheritance__inherit_from_number", "[inheritance]")
{
    initVM();

    auto source = R"???(
var Number = 123;
class Foo < Number {} // expect runtime error: Superclass must be a class.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("inheritance__inherit_methods", "[inheritance]")
{
    initVM();

    auto source = R"???(
class Foo {
  methodOnFoo() { print "foo"; }
  override() { print "foo"; }
}

class Bar < Foo {
  methodOnBar() { print "bar"; }
  override() { print "bar"; }
}

var bar = Bar();
bar.methodOnFoo(); // expect: foo
bar.methodOnBar(); // expect: bar
bar.override(); // expect: bar

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("inheritance__parenthesized_superclass", "[inheritance]")
{
    initVM();

    auto source = R"???(
class Foo {}

// [line 4] Error at '(': Expect superclass name.
class Bar < (Foo) {}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("field__set_on_nil", "[field]")
{
    initVM();

    auto source = R"???(
nil.foo = "value"; // expect runtime error: Only instances have fields.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__get_on_string", "[field]")
{
    initVM();

    auto source = R"???(
"str".foo; // expect runtime error: Only instances have properties.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__get_on_class", "[field]")
{
    initVM();

    auto source = R"???(
class Foo {}
Foo.bar; // expect runtime error: Only instances have properties.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__call_nonfunction_field", "[field]")
{
    initVM();

    auto source = R"???(
class Foo {}

var foo = Foo();
foo.bar = "not fn";

foo.bar(); // expect runtime error: Can only call functions and classes.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__method_binds_this", "[field]")
{
    initVM();

    auto source = R"???(
class Foo {
  sayName(a) {
    print this.name;
    print a;
  }
}

var foo1 = Foo();
foo1.name = "foo1";

var foo2 = Foo();
foo2.name = "foo2";

// Store the method reference on another object.
foo2.fn = foo1.sayName;
// Still retains original receiver.
foo2.fn(1);
// expect: foo1
// expect: 1

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("field__set_on_num", "[field]")
{
    initVM();

    auto source = R"???(
123.foo = "value"; // expect runtime error: Only instances have fields.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__on_instance", "[field]")
{
    initVM();

    auto source = R"???(
class Foo {}

var foo = Foo();

print foo.bar = "bar value"; // expect: bar value
print foo.baz = "baz value"; // expect: baz value

print foo.bar; // expect: bar value
print foo.baz; // expect: baz value

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("field__set_on_function", "[field]")
{
    initVM();

    auto source = R"???(
fun foo() {}

foo.bar = "value"; // expect runtime error: Only instances have fields.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__get_on_nil", "[field]")
{
    initVM();

    auto source = R"???(
nil.foo; // expect runtime error: Only instances have properties.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__undefined", "[field]")
{
    initVM();

    auto source = R"???(
class Foo {}
var foo = Foo();

foo.bar; // expect runtime error: Undefined property 'bar'.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__call_function_field", "[field]")
{
    initVM();

    auto source = R"???(
class Foo {}

fun bar(a, b) {
  print "bar";
  print a;
  print b;
}

var foo = Foo();
foo.bar = bar;

foo.bar(1, 2);
// expect: bar
// expect: 1
// expect: 2

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("field__get_and_set_method", "[field]")
{
    initVM();

    auto source = R"???(
// Bound methods have identity equality.
class Foo {
  method(a) {
    print "method";
    print a;
  }
  other(a) {
    print "other";
    print a;
  }
}

var foo = Foo();
var method = foo.method;

// Setting a property shadows the instance method.
foo.method = foo.other;
foo.method(1);
// expect: other
// expect: 1

// The old method handle still points to the original method.
method(2);
// expect: method
// expect: 2

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("field__get_on_function", "[field]")
{
    initVM();

    auto source = R"???(
fun foo() {}

foo.bar; // expect runtime error: Only instances have properties.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__get_on_bool", "[field]")
{
    initVM();

    auto source = R"???(
true.foo; // expect runtime error: Only instances have properties.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__method", "[field]")
{
    initVM();

    auto source = R"???(
class Foo {
  bar(arg) {
    print arg;
  }
}

var bar = Foo().bar;
print "got method"; // expect: got method
bar("arg");          // expect: arg

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("field__set_on_class", "[field]")
{
    initVM();

    auto source = R"???(
class Foo {}
Foo.bar = "value"; // expect runtime error: Only instances have fields.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__get_on_num", "[field]")
{
    initVM();

    auto source = R"???(
123.foo; // expect runtime error: Only instances have properties.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__many", "[field]")
{
    initVM();

    auto source = R"???(
class Foo {}

var foo = Foo();
fun setFields() {
  foo.bilberry = "bilberry";
  foo.lime = "lime";
  foo.elderberry = "elderberry";
  foo.raspberry = "raspberry";
  foo.gooseberry = "gooseberry";
  foo.longan = "longan";
  foo.mandarine = "mandarine";
  foo.kiwifruit = "kiwifruit";
  foo.orange = "orange";
  foo.pomegranate = "pomegranate";
  foo.tomato = "tomato";
  foo.banana = "banana";
  foo.juniper = "juniper";
  foo.damson = "damson";
  foo.blackcurrant = "blackcurrant";
  foo.peach = "peach";
  foo.grape = "grape";
  foo.mango = "mango";
  foo.redcurrant = "redcurrant";
  foo.watermelon = "watermelon";
  foo.plumcot = "plumcot";
  foo.papaya = "papaya";
  foo.cloudberry = "cloudberry";
  foo.rambutan = "rambutan";
  foo.salak = "salak";
  foo.physalis = "physalis";
  foo.huckleberry = "huckleberry";
  foo.coconut = "coconut";
  foo.date = "date";
  foo.tamarind = "tamarind";
  foo.lychee = "lychee";
  foo.raisin = "raisin";
  foo.apple = "apple";
  foo.avocado = "avocado";
  foo.nectarine = "nectarine";
  foo.pomelo = "pomelo";
  foo.melon = "melon";
  foo.currant = "currant";
  foo.plum = "plum";
  foo.persimmon = "persimmon";
  foo.olive = "olive";
  foo.cranberry = "cranberry";
  foo.boysenberry = "boysenberry";
  foo.blackberry = "blackberry";
  foo.passionfruit = "passionfruit";
  foo.mulberry = "mulberry";
  foo.marionberry = "marionberry";
  foo.plantain = "plantain";
  foo.lemon = "lemon";
  foo.yuzu = "yuzu";
  foo.loquat = "loquat";
  foo.kumquat = "kumquat";
  foo.salmonberry = "salmonberry";
  foo.tangerine = "tangerine";
  foo.durian = "durian";
  foo.pear = "pear";
  foo.cantaloupe = "cantaloupe";
  foo.quince = "quince";
  foo.guava = "guava";
  foo.strawberry = "strawberry";
  foo.nance = "nance";
  foo.apricot = "apricot";
  foo.jambul = "jambul";
  foo.grapefruit = "grapefruit";
  foo.clementine = "clementine";
  foo.jujube = "jujube";
  foo.cherry = "cherry";
  foo.feijoa = "feijoa";
  foo.jackfruit = "jackfruit";
  foo.fig = "fig";
  foo.cherimoya = "cherimoya";
  foo.pineapple = "pineapple";
  foo.blueberry = "blueberry";
  foo.jabuticaba = "jabuticaba";
  foo.miracle = "miracle";
  foo.dragonfruit = "dragonfruit";
  foo.satsuma = "satsuma";
  foo.tamarillo = "tamarillo";
  foo.honeydew = "honeydew";
}

setFields();

fun printFields() {
  print foo.apple; // expect: apple
  print foo.apricot; // expect: apricot
  print foo.avocado; // expect: avocado
  print foo.banana; // expect: banana
  print foo.bilberry; // expect: bilberry
  print foo.blackberry; // expect: blackberry
  print foo.blackcurrant; // expect: blackcurrant
  print foo.blueberry; // expect: blueberry
  print foo.boysenberry; // expect: boysenberry
  print foo.cantaloupe; // expect: cantaloupe
  print foo.cherimoya; // expect: cherimoya
  print foo.cherry; // expect: cherry
  print foo.clementine; // expect: clementine
  print foo.cloudberry; // expect: cloudberry
  print foo.coconut; // expect: coconut
  print foo.cranberry; // expect: cranberry
  print foo.currant; // expect: currant
  print foo.damson; // expect: damson
  print foo.date; // expect: date
  print foo.dragonfruit; // expect: dragonfruit
  print foo.durian; // expect: durian
  print foo.elderberry; // expect: elderberry
  print foo.feijoa; // expect: feijoa
  print foo.fig; // expect: fig
  print foo.gooseberry; // expect: gooseberry
  print foo.grape; // expect: grape
  print foo.grapefruit; // expect: grapefruit
  print foo.guava; // expect: guava
  print foo.honeydew; // expect: honeydew
  print foo.huckleberry; // expect: huckleberry
  print foo.jabuticaba; // expect: jabuticaba
  print foo.jackfruit; // expect: jackfruit
  print foo.jambul; // expect: jambul
  print foo.jujube; // expect: jujube
  print foo.juniper; // expect: juniper
  print foo.kiwifruit; // expect: kiwifruit
  print foo.kumquat; // expect: kumquat
  print foo.lemon; // expect: lemon
  print foo.lime; // expect: lime
  print foo.longan; // expect: longan
  print foo.loquat; // expect: loquat
  print foo.lychee; // expect: lychee
  print foo.mandarine; // expect: mandarine
  print foo.mango; // expect: mango
  print foo.marionberry; // expect: marionberry
  print foo.melon; // expect: melon
  print foo.miracle; // expect: miracle
  print foo.mulberry; // expect: mulberry
  print foo.nance; // expect: nance
  print foo.nectarine; // expect: nectarine
  print foo.olive; // expect: olive
  print foo.orange; // expect: orange
  print foo.papaya; // expect: papaya
  print foo.passionfruit; // expect: passionfruit
  print foo.peach; // expect: peach
  print foo.pear; // expect: pear
  print foo.persimmon; // expect: persimmon
  print foo.physalis; // expect: physalis
  print foo.pineapple; // expect: pineapple
  print foo.plantain; // expect: plantain
  print foo.plum; // expect: plum
  print foo.plumcot; // expect: plumcot
  print foo.pomegranate; // expect: pomegranate
  print foo.pomelo; // expect: pomelo
  print foo.quince; // expect: quince
  print foo.raisin; // expect: raisin
  print foo.rambutan; // expect: rambutan
  print foo.raspberry; // expect: raspberry
  print foo.redcurrant; // expect: redcurrant
  print foo.salak; // expect: salak
  print foo.salmonberry; // expect: salmonberry
  print foo.satsuma; // expect: satsuma
  print foo.strawberry; // expect: strawberry
  print foo.tamarillo; // expect: tamarillo
  print foo.tamarind; // expect: tamarind
  print foo.tangerine; // expect: tangerine
  print foo.tomato; // expect: tomato
  print foo.watermelon; // expect: watermelon
  print foo.yuzu; // expect: yuzu
}

printFields();

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("field__set_on_string", "[field]")
{
    initVM();

    auto source = R"???(
"str".foo = "value"; // expect runtime error: Only instances have fields.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__set_on_bool", "[field]")
{
    initVM();

    auto source = R"???(
true.foo = "value"; // expect runtime error: Only instances have fields.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("field__set_evaluation_order", "[field]")
{
    initVM();

    auto source = R"???(
undefined1.bar // expect runtime error: Undefined variable 'undefined1'.
  = undefined2;
)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("method__extra_arguments", "[method]")
{
    initVM();

    auto source = R"???(
class Foo {
  method(a, b) {
    print a;
    print b;
  }
}

Foo().method(1, 2, 3, 4); // expect runtime error: Expected 2 arguments but got 4.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("method__arity", "[method]")
{
    initVM();

    auto source = R"???(
class Foo {
  method0() { return "no args"; }
  method1(a) { return a; }
  method2(a, b) { return a + b; }
  method3(a, b, c) { return a + b + c; }
  method4(a, b, c, d) { return a + b + c + d; }
  method5(a, b, c, d, e) { return a + b + c + d + e; }
  method6(a, b, c, d, e, f) { return a + b + c + d + e + f; }
  method7(a, b, c, d, e, f, g) { return a + b + c + d + e + f + g; }
  method8(a, b, c, d, e, f, g, h) { return a + b + c + d + e + f + g + h; }
}

var foo = Foo();
print foo.method0(); // expect: no args
print foo.method1(1); // expect: 1
print foo.method2(1, 2); // expect: 3
print foo.method3(1, 2, 3); // expect: 6
print foo.method4(1, 2, 3, 4); // expect: 10
print foo.method5(1, 2, 3, 4, 5); // expect: 15
print foo.method6(1, 2, 3, 4, 5, 6); // expect: 21
print foo.method7(1, 2, 3, 4, 5, 6, 7); // expect: 28
print foo.method8(1, 2, 3, 4, 5, 6, 7, 8); // expect: 36

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("method__too_many_parameters", "[method]")
{
    initVM();

    auto source = R"???(
class Foo {
  // 256 parameters.
  method(
    a1,
    a2,
    a3,
    a4,
    a5,
    a6,
    a7,
    a8,
    a9,
    a10,
    a11,
    a12,
    a13,
    a14,
    a15,
    a16,
    a17,
    a18,
    a19,
    a20,
    a21,
    a22,
    a23,
    a24,
    a25,
    a26,
    a27,
    a28,
    a29,
    a30,
    a31,
    a32,
    a33,
    a34,
    a35,
    a36,
    a37,
    a38,
    a39,
    a40,
    a41,
    a42,
    a43,
    a44,
    a45,
    a46,
    a47,
    a48,
    a49,
    a50,
    a51,
    a52,
    a53,
    a54,
    a55,
    a56,
    a57,
    a58,
    a59,
    a60,
    a61,
    a62,
    a63,
    a64,
    a65,
    a66,
    a67,
    a68,
    a69,
    a70,
    a71,
    a72,
    a73,
    a74,
    a75,
    a76,
    a77,
    a78,
    a79,
    a80,
    a81,
    a82,
    a83,
    a84,
    a85,
    a86,
    a87,
    a88,
    a89,
    a90,
    a91,
    a92,
    a93,
    a94,
    a95,
    a96,
    a97,
    a98,
    a99,
    a100,
    a101,
    a102,
    a103,
    a104,
    a105,
    a106,
    a107,
    a108,
    a109,
    a110,
    a111,
    a112,
    a113,
    a114,
    a115,
    a116,
    a117,
    a118,
    a119,
    a120,
    a121,
    a122,
    a123,
    a124,
    a125,
    a126,
    a127,
    a128,
    a129,
    a130,
    a131,
    a132,
    a133,
    a134,
    a135,
    a136,
    a137,
    a138,
    a139,
    a140,
    a141,
    a142,
    a143,
    a144,
    a145,
    a146,
    a147,
    a148,
    a149,
    a150,
    a151,
    a152,
    a153,
    a154,
    a155,
    a156,
    a157,
    a158,
    a159,
    a160,
    a161,
    a162,
    a163,
    a164,
    a165,
    a166,
    a167,
    a168,
    a169,
    a170,
    a171,
    a172,
    a173,
    a174,
    a175,
    a176,
    a177,
    a178,
    a179,
    a180,
    a181,
    a182,
    a183,
    a184,
    a185,
    a186,
    a187,
    a188,
    a189,
    a190,
    a191,
    a192,
    a193,
    a194,
    a195,
    a196,
    a197,
    a198,
    a199,
    a200,
    a201,
    a202,
    a203,
    a204,
    a205,
    a206,
    a207,
    a208,
    a209,
    a210,
    a211,
    a212,
    a213,
    a214,
    a215,
    a216,
    a217,
    a218,
    a219,
    a220,
    a221,
    a222,
    a223,
    a224,
    a225,
    a226,
    a227,
    a228,
    a229,
    a230,
    a231,
    a232,
    a233,
    a234,
    a235,
    a236,
    a237,
    a238,
    a239,
    a240,
    a241,
    a242,
    a243,
    a244,
    a245,
    a246,
    a247,
    a248,
    a249,
    a250,
    a251,
    a252,
    a253,
    a254,
    a255, a) {} // Error at 'a': Can't have more than 255 parameters.
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("method__missing_arguments", "[method]")
{
    initVM();

    auto source = R"???(
class Foo {
  method(a, b) {}
}

Foo().method(1); // expect runtime error: Expected 2 arguments but got 1.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("method__not_found", "[method]")
{
    initVM();

    auto source = R"???(
class Foo {}

Foo().unknown(); // expect runtime error: Undefined property 'unknown'.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("method__too_many_arguments", "[method]")
{
    initVM();

    auto source = R"???(
{
  var a = 1;
  true.method(
     a, // 1
     a, // 2
     a, // 3
     a, // 4
     a, // 5
     a, // 6
     a, // 7
     a, // 8
     a, // 9
     a, // 10
     a, // 11
     a, // 12
     a, // 13
     a, // 14
     a, // 15
     a, // 16
     a, // 17
     a, // 18
     a, // 19
     a, // 20
     a, // 21
     a, // 22
     a, // 23
     a, // 24
     a, // 25
     a, // 26
     a, // 27
     a, // 28
     a, // 29
     a, // 30
     a, // 31
     a, // 32
     a, // 33
     a, // 34
     a, // 35
     a, // 36
     a, // 37
     a, // 38
     a, // 39
     a, // 40
     a, // 41
     a, // 42
     a, // 43
     a, // 44
     a, // 45
     a, // 46
     a, // 47
     a, // 48
     a, // 49
     a, // 50
     a, // 51
     a, // 52
     a, // 53
     a, // 54
     a, // 55
     a, // 56
     a, // 57
     a, // 58
     a, // 59
     a, // 60
     a, // 61
     a, // 62
     a, // 63
     a, // 64
     a, // 65
     a, // 66
     a, // 67
     a, // 68
     a, // 69
     a, // 70
     a, // 71
     a, // 72
     a, // 73
     a, // 74
     a, // 75
     a, // 76
     a, // 77
     a, // 78
     a, // 79
     a, // 80
     a, // 81
     a, // 82
     a, // 83
     a, // 84
     a, // 85
     a, // 86
     a, // 87
     a, // 88
     a, // 89
     a, // 90
     a, // 91
     a, // 92
     a, // 93
     a, // 94
     a, // 95
     a, // 96
     a, // 97
     a, // 98
     a, // 99
     a, // 100
     a, // 101
     a, // 102
     a, // 103
     a, // 104
     a, // 105
     a, // 106
     a, // 107
     a, // 108
     a, // 109
     a, // 110
     a, // 111
     a, // 112
     a, // 113
     a, // 114
     a, // 115
     a, // 116
     a, // 117
     a, // 118
     a, // 119
     a, // 120
     a, // 121
     a, // 122
     a, // 123
     a, // 124
     a, // 125
     a, // 126
     a, // 127
     a, // 128
     a, // 129
     a, // 130
     a, // 131
     a, // 132
     a, // 133
     a, // 134
     a, // 135
     a, // 136
     a, // 137
     a, // 138
     a, // 139
     a, // 140
     a, // 141
     a, // 142
     a, // 143
     a, // 144
     a, // 145
     a, // 146
     a, // 147
     a, // 148
     a, // 149
     a, // 150
     a, // 151
     a, // 152
     a, // 153
     a, // 154
     a, // 155
     a, // 156
     a, // 157
     a, // 158
     a, // 159
     a, // 160
     a, // 161
     a, // 162
     a, // 163
     a, // 164
     a, // 165
     a, // 166
     a, // 167
     a, // 168
     a, // 169
     a, // 170
     a, // 171
     a, // 172
     a, // 173
     a, // 174
     a, // 175
     a, // 176
     a, // 177
     a, // 178
     a, // 179
     a, // 180
     a, // 181
     a, // 182
     a, // 183
     a, // 184
     a, // 185
     a, // 186
     a, // 187
     a, // 188
     a, // 189
     a, // 190
     a, // 191
     a, // 192
     a, // 193
     a, // 194
     a, // 195
     a, // 196
     a, // 197
     a, // 198
     a, // 199
     a, // 200
     a, // 201
     a, // 202
     a, // 203
     a, // 204
     a, // 205
     a, // 206
     a, // 207
     a, // 208
     a, // 209
     a, // 210
     a, // 211
     a, // 212
     a, // 213
     a, // 214
     a, // 215
     a, // 216
     a, // 217
     a, // 218
     a, // 219
     a, // 220
     a, // 221
     a, // 222
     a, // 223
     a, // 224
     a, // 225
     a, // 226
     a, // 227
     a, // 228
     a, // 229
     a, // 230
     a, // 231
     a, // 232
     a, // 233
     a, // 234
     a, // 235
     a, // 236
     a, // 237
     a, // 238
     a, // 239
     a, // 240
     a, // 241
     a, // 242
     a, // 243
     a, // 244
     a, // 245
     a, // 246
     a, // 247
     a, // 248
     a, // 249
     a, // 250
     a, // 251
     a, // 252
     a, // 253
     a, // 254
     a, // 255
     a); // Error at 'a': Can't have more than 255 arguments.
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("method__print_bound_method", "[method]")
{
    initVM();

    auto source = R"???(
class Foo {
  method() { }
}
var foo = Foo();
print foo.method; // expect: <fn method>

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("method__empty_block", "[method]")
{
    initVM();

    auto source = R"???(
class Foo {
  bar() {}
}

print Foo().bar(); // expect: nil

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("method__refer_to_name", "[method]")
{
    initVM();

    auto source = R"???(
class Foo {
  method() {
    print method; // expect runtime error: Undefined variable 'method'.
  }
}

Foo().method();

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("regression__394", "[regression]")
{
    initVM();

    auto source = R"???(
{
  class A {}
  class B < A {}
  print B; // expect: B
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("regression__40", "[regression]")
{
    initVM();

    auto source = R"???(
fun caller(g) {
  g();
  // g should be a function, not nil.
  print g == nil; // expect: false
}

fun callCaller() {
  var capturedVar = "before";
  var a = "a";

  fun f() {
    // Commenting the next line out prevents the bug!
    capturedVar = "after";

    // Returning anything also fixes it, even nil:
    //return nil;
  }

  caller(f);
}

callCaller();

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("assignment__grouping", "[assignment]")
{
    initVM();

    auto source = R"???(
var a = "a";
(a) = "value"; // Error at '=': Invalid assignment target.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("assignment__syntax", "[assignment]")
{
    initVM();

    auto source = R"???(
// Assignment on RHS of variable.
var a = "before";
var c = a = "var";
print a; // expect: var
print c; // expect: var

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("assignment__infix_operator", "[assignment]")
{
    initVM();

    auto source = R"???(
var a = "a";
var b = "b";
a + b = "value"; // Error at '=': Invalid assignment target.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("assignment__undefined", "[assignment]")
{
    initVM();

    auto source = R"???(
unknown = "what"; // expect runtime error: Undefined variable 'unknown'.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("assignment__prefix_operator", "[assignment]")
{
    initVM();

    auto source = R"???(
var a = "a";
!a = "value"; // Error at '=': Invalid assignment target.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("assignment__associativity", "[assignment]")
{
    initVM();

    auto source = R"???(
var a = "a";
var b = "b";
var c = "c";

// Assignment is right-associative.
a = b = c;
print a; // expect: c
print b; // expect: c
print c; // expect: c

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("assignment__local", "[assignment]")
{
    initVM();

    auto source = R"???(
{
  var a = "before";
  print a; // expect: before

  a = "after";
  print a; // expect: after

  print a = "arg"; // expect: arg
  print a; // expect: arg
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("assignment__to_this", "[assignment]")
{
    initVM();

    auto source = R"???(
class Foo {
  Foo() {
    this = "value"; // Error at '=': Invalid assignment target.
  }
}

Foo();

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("assignment__global", "[assignment]")
{
    initVM();

    auto source = R"???(
var a = "before";
print a; // expect: before

a = "after";
print a; // expect: after

print a = "arg"; // expect: arg
print a; // expect: arg

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("scanning__punctuators", "[scanning]")
{
    initVM();

    auto source = R"???(
(){};,+-*!===<=>=!=<>/.

// expect: LEFT_PAREN ( null
// expect: RIGHT_PAREN ) null
// expect: LEFT_BRACE { null
// expect: RIGHT_BRACE } null
// expect: SEMICOLON ; null
// expect: COMMA , null
// expect: PLUS + null
// expect: MINUS - null
// expect: STAR * null
// expect: BANG_EQUAL != null
// expect: EQUAL_EQUAL == null
// expect: LESS_EQUAL <= null
// expect: GREATER_EQUAL >= null
// expect: BANG_EQUAL != null
// expect: LESS < null
// expect: GREATER > null
// expect: SLASH / null
// expect: DOT . null
// expect: EOF  null

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("scanning__whitespace", "[scanning]")
{
    initVM();

    auto source = R"???(
space    tabs				newlines




end

// expect: IDENTIFIER space null
// expect: IDENTIFIER tabs null
// expect: IDENTIFIER newlines null
// expect: IDENTIFIER end null
// expect: EOF  null

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("scanning__numbers", "[scanning]")
{
    initVM();

    auto source = R"???(
123
123.456
.456
123.

// expect: NUMBER 123 123.0
// expect: NUMBER 123.456 123.456
// expect: DOT . null
// expect: NUMBER 456 456.0
// expect: NUMBER 123 123.0
// expect: DOT . null
// expect: EOF  null

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("scanning__strings", "[scanning]")
{
    initVM();

    auto source = R"???(
""
"string"

// expect: STRING ""
// expect: STRING "string" string
// expect: EOF  null
)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("scanning__identifiers", "[scanning]")
{
    initVM();

    auto source = R"???(
andy formless fo _ _123 _abc ab123
abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_

// expect: IDENTIFIER andy null
// expect: IDENTIFIER formless null
// expect: IDENTIFIER fo null
// expect: IDENTIFIER _ null
// expect: IDENTIFIER _123 null
// expect: IDENTIFIER _abc null
// expect: IDENTIFIER ab123 null
// expect: IDENTIFIER abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_ null
// expect: EOF  null

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("scanning__keywords", "[scanning]")
{
    initVM();

    auto source = R"???(
and class else false for fun if nil or return super this true var while

// expect: AND and null
// expect: CLASS class null
// expect: ELSE else null
// expect: FALSE false null
// expect: FOR for null
// expect: FUN fun null
// expect: IF if null
// expect: NIL nil null
// expect: OR or null
// expect: RETURN return null
// expect: SUPER super null
// expect: THIS this null
// expect: TRUE true null
// expect: VAR var null
// expect: WHILE while null
// expect: EOF  null

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("nil__literal", "[nil]")
{
    initVM();

    auto source = R"???(
print nil; // expect: nil

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("for__statement_initializer", "[for]")
{
    initVM();

    auto source = R"???(
// [line 3] Error at '{': Expect expression.
// [line 3] Error at ')': Expect ';' after expression.
for ({}; a < 2; a = a + 1) {}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("for__closure_in_body", "[for]")
{
    initVM();

    auto source = R"???(
var f1;
var f2;
var f3;

for (var i = 1; i < 4; i = i + 1) {
  var j = i;
  fun f() {
    print i;
    print j;
  }

  if (j == 1) f1 = f;
  else if (j == 2) f2 = f;
  else f3 = f;
}

f1(); // expect: 4
      // expect: 1
f2(); // expect: 4
      // expect: 2
f3(); // expect: 4
      // expect: 3

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("for__syntax", "[for]")
{
    initVM();

    auto source = R"???(
// Single-expression body.
for (var c = 0; c < 3;) print c = c + 1;
// expect: 1
// expect: 2
// expect: 3

// Block body.
for (var a = 0; a < 3; a = a + 1) {
  print a;
}
// expect: 0
// expect: 1
// expect: 2

// No clauses.
fun foo() {
  for (;;) return "done";
}
print foo(); // expect: done

// No variable.
var i = 0;
for (; i < 2; i = i + 1) print i;
// expect: 0
// expect: 1

// No condition.
fun bar() {
  for (var i = 0;; i = i + 1) {
    print i;
    if (i >= 2) return;
  }
}
bar();
// expect: 0
// expect: 1
// expect: 2

// No increment.
for (var i = 0; i < 2;) {
  print i;
  i = i + 1;
}
// expect: 0
// expect: 1

// Statement bodies.
for (; false;) if (true) 1; else 2;
for (; false;) while (true) 1;
for (; false;) for (;;) 1;

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("for__return_inside", "[for]")
{
    initVM();

    auto source = R"???(
fun f() {
  for (;;) {
    var i = "i";
    return i;
  }
}

print f();
// expect: i

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("for__statement_increment", "[for]")
{
    initVM();

    auto source = R"???(
// [line 2] Error at '{': Expect expression.
for (var a = 1; a < 2; {}) {}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("for__fun_in_body", "[for]")
{
    initVM();

    auto source = R"???(
// [line 2] Error at 'fun': Expect expression.
for (;;) fun foo() {}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("for__var_in_body", "[for]")
{
    initVM();

    auto source = R"???(
// [line 2] Error at 'var': Expect expression.
for (;;) var foo;

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("for__class_in_body", "[for]")
{
    initVM();

    auto source = R"???(
// [line 2] Error at 'class': Expect expression.
for (;;) class Foo {}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("for__scope", "[for]")
{
    initVM();

    auto source = R"???(
{
  var i = "before";

  // New variable is in inner scope.
  for (var i = 0; i < 1; i = i + 1) {
    print i; // expect: 0

    // Loop body is in second inner scope.
    var i = -1;
    print i; // expect: -1
  }
}

{
  // New variable shadows outer variable.
  for (var i = 0; i > 0; i = i + 1) {}

  // Goes out of scope after loop.
  var i = "after";
  print i; // expect: after

  // Can reuse an existing variable.
  for (i = 0; i < 1; i = i + 1) {
    print i; // expect: 0
  }
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("for__return_closure", "[for]")
{
    initVM();

    auto source = R"???(
fun f() {
  for (;;) {
    var i = "i";
    fun g() { print i; }
    return g;
  }
}

var h = f();
h(); // expect: i

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("for__statement_condition", "[for]")
{
    initVM();

    auto source = R"???(
// [line 3] Error at '{': Expect expression.
// [line 3] Error at ')': Expect ';' after expression.
for (var a = 1; {}; a = a + 1) {}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("comments__line_at_eof", "[comments]")
{
    initVM();

    auto source = R"???(
print "ok"; // expect: ok
// comment
)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("comments__only_line_comment_and_line", "[comments]")
{
    initVM();

    auto source = R"???(
// comment

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("comments__only_line_comment", "[comments]")
{
    initVM();

    auto source = R"???(
// comment
)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("comments__unicode", "[comments]")
{
    initVM();

    auto source = R"???(
// Unicode characters are allowed in comments.
//
// Latin 1 Supplement: £§¶ÜÞ
// Latin Extended-A: ĐĦŋœ
// Latin Extended-B: ƂƢƩǁ
// Other stuff: ឃᢆ᯽₪ℜ↩⊗┺░
// Emoji: ☃☺♣

print "ok"; // expect: ok

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("expressions__parse", "[expressions]")
{
    initVM();

    auto source = R"???(
// Note: This is just for the expression parsing chapter which prints the AST.
(5 - (3 - 1)) + -1
// expect: (+ (group (- 5.0 (group (- 3.0 1.0)))) (- 1.0))

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("expressions__evaluate", "[expressions]")
{
    initVM();

    auto source = R"???(
// Note: This is just for the expression evaluating chapter which evaluates an
// expression directly.
(5 - (3 - 1)) + -1
// expect: 2

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("logical_operator__or_truth", "[logical_operator]")
{
    initVM();

    auto source = R"???(
// False and nil are false.
print false or "ok"; // expect: ok
print nil or "ok"; // expect: ok

// Everything else is true.
print true or "ok"; // expect: true
print 0 or "ok"; // expect: 0
print "s" or "ok"; // expect: s

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("logical_operator__and_truth", "[logical_operator]")
{
    initVM();

    auto source = R"???(
// False and nil are false.
print false and "bad"; // expect: false
print nil and "bad"; // expect: nil

// Everything else is true.
print true and "ok"; // expect: ok
print 0 and "ok"; // expect: ok
print "" and "ok"; // expect: ok

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("logical_operator__or", "[logical_operator]")
{
    initVM();

    auto source = R"???(
// Note: These tests implicitly depend on ints being truthy.

// Return the first true argument.
print 1 or true; // expect: 1
print false or 1; // expect: 1
print false or false or true; // expect: true

// Return the last argument if all are false.
print false or false; // expect: false
print false or false or false; // expect: false

// Short-circuit at the first true argument.
var a = "before";
var b = "before";
(a = false) or
    (b = true) or
    (a = "bad");
print a; // expect: false
print b; // expect: true

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("logical_operator__and", "[logical_operator]")
{
    initVM();

    auto source = R"???(
// Note: These tests implicitly depend on ints being truthy.

// Return the first non-true argument.
print false and 1; // expect: false
print true and 1; // expect: 1
print 1 and 2 and false; // expect: false

// Return the last argument if all are true.
print 1 and true; // expect: true
print 1 and 2 and 3; // expect: 3

// Short-circuit at the first false argument.
var a = "before";
var b = "before";
(a = true) and
    (b = false) and
    (a = "bad");
print a; // expect: true
print b; // expect: false

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("limit__too_many_upvalues", "[limit]")
{
    initVM();

    auto source = R"???(
fun f() {
  var v00; var v01; var v02; var v03; var v04; var v05; var v06; var v07;
  var v08; var v09; var v0a; var v0b; var v0c; var v0d; var v0e; var v0f;

  var v10; var v11; var v12; var v13; var v14; var v15; var v16; var v17;
  var v18; var v19; var v1a; var v1b; var v1c; var v1d; var v1e; var v1f;

  var v20; var v21; var v22; var v23; var v24; var v25; var v26; var v27;
  var v28; var v29; var v2a; var v2b; var v2c; var v2d; var v2e; var v2f;

  var v30; var v31; var v32; var v33; var v34; var v35; var v36; var v37;
  var v38; var v39; var v3a; var v3b; var v3c; var v3d; var v3e; var v3f;

  var v40; var v41; var v42; var v43; var v44; var v45; var v46; var v47;
  var v48; var v49; var v4a; var v4b; var v4c; var v4d; var v4e; var v4f;

  var v50; var v51; var v52; var v53; var v54; var v55; var v56; var v57;
  var v58; var v59; var v5a; var v5b; var v5c; var v5d; var v5e; var v5f;

  var v60; var v61; var v62; var v63; var v64; var v65; var v66; var v67;
  var v68; var v69; var v6a; var v6b; var v6c; var v6d; var v6e; var v6f;

  var v70; var v71; var v72; var v73; var v74; var v75; var v76; var v77;
  var v78; var v79; var v7a; var v7b; var v7c; var v7d; var v7e; var v7f;

  fun g() {
    var v80; var v81; var v82; var v83; var v84; var v85; var v86; var v87;
    var v88; var v89; var v8a; var v8b; var v8c; var v8d; var v8e; var v8f;

    var v90; var v91; var v92; var v93; var v94; var v95; var v96; var v97;
    var v98; var v99; var v9a; var v9b; var v9c; var v9d; var v9e; var v9f;

    var va0; var va1; var va2; var va3; var va4; var va5; var va6; var va7;
    var va8; var va9; var vaa; var vab; var vac; var vad; var vae; var vaf;

    var vb0; var vb1; var vb2; var vb3; var vb4; var vb5; var vb6; var vb7;
    var vb8; var vb9; var vba; var vbb; var vbc; var vbd; var vbe; var vbf;

    var vc0; var vc1; var vc2; var vc3; var vc4; var vc5; var vc6; var vc7;
    var vc8; var vc9; var vca; var vcb; var vcc; var vcd; var vce; var vcf;

    var vd0; var vd1; var vd2; var vd3; var vd4; var vd5; var vd6; var vd7;
    var vd8; var vd9; var vda; var vdb; var vdc; var vdd; var vde; var vdf;

    var ve0; var ve1; var ve2; var ve3; var ve4; var ve5; var ve6; var ve7;
    var ve8; var ve9; var vea; var veb; var vec; var ved; var vee; var vef;

    var vf0; var vf1; var vf2; var vf3; var vf4; var vf5; var vf6; var vf7;
    var vf8; var vf9; var vfa; var vfb; var vfc; var vfd; var vfe; var vff;

    var oops;

    fun h() {
      v00; v01; v02; v03; v04; v05; v06; v07;
      v08; v09; v0a; v0b; v0c; v0d; v0e; v0f;

      v10; v11; v12; v13; v14; v15; v16; v17;
      v18; v19; v1a; v1b; v1c; v1d; v1e; v1f;

      v20; v21; v22; v23; v24; v25; v26; v27;
      v28; v29; v2a; v2b; v2c; v2d; v2e; v2f;

      v30; v31; v32; v33; v34; v35; v36; v37;
      v38; v39; v3a; v3b; v3c; v3d; v3e; v3f;

      v40; v41; v42; v43; v44; v45; v46; v47;
      v48; v49; v4a; v4b; v4c; v4d; v4e; v4f;

      v50; v51; v52; v53; v54; v55; v56; v57;
      v58; v59; v5a; v5b; v5c; v5d; v5e; v5f;

      v60; v61; v62; v63; v64; v65; v66; v67;
      v68; v69; v6a; v6b; v6c; v6d; v6e; v6f;

      v70; v71; v72; v73; v74; v75; v76; v77;
      v78; v79; v7a; v7b; v7c; v7d; v7e; v7f;

      v80; v81; v82; v83; v84; v85; v86; v87;
      v88; v89; v8a; v8b; v8c; v8d; v8e; v8f;

      v90; v91; v92; v93; v94; v95; v96; v97;
      v98; v99; v9a; v9b; v9c; v9d; v9e; v9f;

      va0; va1; va2; va3; va4; va5; va6; va7;
      va8; va9; vaa; vab; vac; vad; vae; vaf;

      vb0; vb1; vb2; vb3; vb4; vb5; vb6; vb7;
      vb8; vb9; vba; vbb; vbc; vbd; vbe; vbf;

      vc0; vc1; vc2; vc3; vc4; vc5; vc6; vc7;
      vc8; vc9; vca; vcb; vcc; vcd; vce; vcf;

      vd0; vd1; vd2; vd3; vd4; vd5; vd6; vd7;
      vd8; vd9; vda; vdb; vdc; vdd; vde; vdf;

      ve0; ve1; ve2; ve3; ve4; ve5; ve6; ve7;
      ve8; ve9; vea; veb; vec; ved; vee; vef;

      vf0; vf1; vf2; vf3; vf4; vf5; vf6; vf7;
      vf8; vf9; vfa; vfb; vfc; vfd; vfe; vff;

      oops; // Error at 'oops': Too many closure variables in function.
    }
  }
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("limit__too_many_locals", "[limit]")
{
    initVM();

    auto source = R"???(
fun f() {
  // var v00; First slot already taken.

  var v01; var v02; var v03; var v04; var v05; var v06; var v07;
  var v08; var v09; var v0a; var v0b; var v0c; var v0d; var v0e; var v0f;

  var v10; var v11; var v12; var v13; var v14; var v15; var v16; var v17;
  var v18; var v19; var v1a; var v1b; var v1c; var v1d; var v1e; var v1f;

  var v20; var v21; var v22; var v23; var v24; var v25; var v26; var v27;
  var v28; var v29; var v2a; var v2b; var v2c; var v2d; var v2e; var v2f;

  var v30; var v31; var v32; var v33; var v34; var v35; var v36; var v37;
  var v38; var v39; var v3a; var v3b; var v3c; var v3d; var v3e; var v3f;

  var v40; var v41; var v42; var v43; var v44; var v45; var v46; var v47;
  var v48; var v49; var v4a; var v4b; var v4c; var v4d; var v4e; var v4f;

  var v50; var v51; var v52; var v53; var v54; var v55; var v56; var v57;
  var v58; var v59; var v5a; var v5b; var v5c; var v5d; var v5e; var v5f;

  var v60; var v61; var v62; var v63; var v64; var v65; var v66; var v67;
  var v68; var v69; var v6a; var v6b; var v6c; var v6d; var v6e; var v6f;

  var v70; var v71; var v72; var v73; var v74; var v75; var v76; var v77;
  var v78; var v79; var v7a; var v7b; var v7c; var v7d; var v7e; var v7f;

  var v80; var v81; var v82; var v83; var v84; var v85; var v86; var v87;
  var v88; var v89; var v8a; var v8b; var v8c; var v8d; var v8e; var v8f;

  var v90; var v91; var v92; var v93; var v94; var v95; var v96; var v97;
  var v98; var v99; var v9a; var v9b; var v9c; var v9d; var v9e; var v9f;

  var va0; var va1; var va2; var va3; var va4; var va5; var va6; var va7;
  var va8; var va9; var vaa; var vab; var vac; var vad; var vae; var vaf;

  var vb0; var vb1; var vb2; var vb3; var vb4; var vb5; var vb6; var vb7;
  var vb8; var vb9; var vba; var vbb; var vbc; var vbd; var vbe; var vbf;

  var vc0; var vc1; var vc2; var vc3; var vc4; var vc5; var vc6; var vc7;
  var vc8; var vc9; var vca; var vcb; var vcc; var vcd; var vce; var vcf;

  var vd0; var vd1; var vd2; var vd3; var vd4; var vd5; var vd6; var vd7;
  var vd8; var vd9; var vda; var vdb; var vdc; var vdd; var vde; var vdf;

  var ve0; var ve1; var ve2; var ve3; var ve4; var ve5; var ve6; var ve7;
  var ve8; var ve9; var vea; var veb; var vec; var ved; var vee; var vef;

  var vf0; var vf1; var vf2; var vf3; var vf4; var vf5; var vf6; var vf7;
  var vf8; var vf9; var vfa; var vfb; var vfc; var vfd; var vfe; var vff;

  var oops; // Error at 'oops': Too many local variables in function.
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("limit__no_reuse_constants", "[limit]")
{
    initVM();

    auto source = R"???(
fun f() {
  0; 1; 2; 3; 4; 5; 6; 7;
  8; 9; 10; 11; 12; 13; 14; 15;
  16; 17; 18; 19; 20; 21; 22; 23;
  24; 25; 26; 27; 28; 29; 30; 31;
  32; 33; 34; 35; 36; 37; 38; 39;
  40; 41; 42; 43; 44; 45; 46; 47;
  48; 49; 50; 51; 52; 53; 54; 55;
  56; 57; 58; 59; 60; 61; 62; 63;
  64; 65; 66; 67; 68; 69; 70; 71;
  72; 73; 74; 75; 76; 77; 78; 79;
  80; 81; 82; 83; 84; 85; 86; 87;
  88; 89; 90; 91; 92; 93; 94; 95;
  96; 97; 98; 99; 100; 101; 102; 103;
  104; 105; 106; 107; 108; 109; 110; 111;
  112; 113; 114; 115; 116; 117; 118; 119;
  120; 121; 122; 123; 124; 125; 126; 127;
  128; 129; 130; 131; 132; 133; 134; 135;
  136; 137; 138; 139; 140; 141; 142; 143;
  144; 145; 146; 147; 148; 149; 150; 151;
  152; 153; 154; 155; 156; 157; 158; 159;
  160; 161; 162; 163; 164; 165; 166; 167;
  168; 169; 170; 171; 172; 173; 174; 175;
  176; 177; 178; 179; 180; 181; 182; 183;
  184; 185; 186; 187; 188; 189; 190; 191;
  192; 193; 194; 195; 196; 197; 198; 199;
  200; 201; 202; 203; 204; 205; 206; 207;
  208; 209; 210; 211; 212; 213; 214; 215;
  216; 217; 218; 219; 220; 221; 222; 223;
  224; 225; 226; 227; 228; 229; 230; 231;
  232; 233; 234; 235; 236; 237; 238; 239;
  240; 241; 242; 243; 244; 245; 246; 247;
  248; 249; 250; 251; 252; 253; 254; 255;

  1; // Error at '1': Too many constants in one chunk.
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("limit__stack_overflow", "[limit]")
{
    initVM();

    auto source = R"???(
fun foo() {
  var a1;
  var a2;
  var a3;
  var a4;
  var a5;
  var a6;
  var a7;
  var a8;
  var a9;
  var a10;
  var a11;
  var a12;
  var a13;
  var a14;
  var a15;
  var a16;
  foo(); // expect runtime error: Stack overflow.
}

foo();

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("limit__too_many_constants", "[limit]")
{
    initVM();

    auto source = R"???(
fun f() {
  0; 1; 2; 3; 4; 5; 6; 7;
  8; 9; 10; 11; 12; 13; 14; 15;
  16; 17; 18; 19; 20; 21; 22; 23;
  24; 25; 26; 27; 28; 29; 30; 31;
  32; 33; 34; 35; 36; 37; 38; 39;
  40; 41; 42; 43; 44; 45; 46; 47;
  48; 49; 50; 51; 52; 53; 54; 55;
  56; 57; 58; 59; 60; 61; 62; 63;
  64; 65; 66; 67; 68; 69; 70; 71;
  72; 73; 74; 75; 76; 77; 78; 79;
  80; 81; 82; 83; 84; 85; 86; 87;
  88; 89; 90; 91; 92; 93; 94; 95;
  96; 97; 98; 99; 100; 101; 102; 103;
  104; 105; 106; 107; 108; 109; 110; 111;
  112; 113; 114; 115; 116; 117; 118; 119;
  120; 121; 122; 123; 124; 125; 126; 127;
  128; 129; 130; 131; 132; 133; 134; 135;
  136; 137; 138; 139; 140; 141; 142; 143;
  144; 145; 146; 147; 148; 149; 150; 151;
  152; 153; 154; 155; 156; 157; 158; 159;
  160; 161; 162; 163; 164; 165; 166; 167;
  168; 169; 170; 171; 172; 173; 174; 175;
  176; 177; 178; 179; 180; 181; 182; 183;
  184; 185; 186; 187; 188; 189; 190; 191;
  192; 193; 194; 195; 196; 197; 198; 199;
  200; 201; 202; 203; 204; 205; 206; 207;
  208; 209; 210; 211; 212; 213; 214; 215;
  216; 217; 218; 219; 220; 221; 222; 223;
  224; 225; 226; 227; 228; 229; 230; 231;
  232; 233; 234; 235; 236; 237; 238; 239;
  240; 241; 242; 243; 244; 245; 246; 247;
  248; 249; 250; 251; 252; 253; 254; 255;

  "oops"; // Error at '"oops"': Too many constants in one chunk.
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("class__empty", "[class]")
{
    initVM();

    auto source = R"???(
class Foo {}

print Foo; // expect: Foo

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("class__inherit_self", "[class]")
{
    initVM();

    auto source = R"???(
class Foo < Foo {} // Error at 'Foo': A class can't inherit from itself.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("class__reference_self", "[class]")
{
    initVM();

    auto source = R"???(
class Foo {
  returnSelf() {
    return Foo;
  }
}

print Foo().returnSelf(); // expect: Foo

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("class__local_inherit_other", "[class]")
{
    initVM();

    auto source = R"???(
class A {}

fun f() {
  class B < A {}
  return B;
}

print f(); // expect: B

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("class__inherited_method", "[class]")
{
    initVM();

    auto source = R"???(
class Foo {
  inFoo() {
    print "in foo";
  }
}

class Bar < Foo {
  inBar() {
    print "in bar";
  }
}

class Baz < Bar {
  inBaz() {
    print "in baz";
  }
}

var baz = Baz();
baz.inFoo(); // expect: in foo
baz.inBar(); // expect: in bar
baz.inBaz(); // expect: in baz

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("class__local_reference_self", "[class]")
{
    initVM();

    auto source = R"???(
{
  class Foo {
    returnSelf() {
      return Foo;
    }
  }

  print Foo().returnSelf(); // expect: Foo
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("class__local_inherit_self", "[class]")
{
    initVM();

    auto source = R"???(
{
  class Foo < Foo {} // Error at 'Foo': A class can't inherit from itself.
}
// [c line 5] Error at end: Expect '}' after block.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("closure__close_over_function_parameter", "[closure]")
{
    initVM();

    auto source = R"???(
var f;

fun foo(param) {
  fun f_() {
    print param;
  }
  f = f_;
}
foo("param");

f(); // expect: param

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__reuse_closure_slot", "[closure]")
{
    initVM();

    auto source = R"???(
{
  var f;

  {
    var a = "a";
    fun f_() { print a; }
    f = f_;
  }

  {
    // Since a is out of scope, the local slot will be reused by b. Make sure
    // that f still closes over a.
    var b = "b";
    f(); // expect: a
  }
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__close_over_later_variable", "[closure]")
{
    initVM();

    auto source = R"???(
// This is a regression test. There was a bug where if an upvalue for an
// earlier local (here "a") was captured *after* a later one ("b"), then it
// would crash because it walked to the end of the upvalue list (correct), but
// then didn't handle not finding the variable.

fun f() {
  var a = "a";
  var b = "b";
  fun g() {
    print b; // expect: b
    print a; // expect: a
  }
  g();
}
f();

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__nested_closure", "[closure]")
{
    initVM();

    auto source = R"???(
var f;

fun f1() {
  var a = "a";
  fun f2() {
    var b = "b";
    fun f3() {
      var c = "c";
      fun f4() {
        print a;
        print b;
        print c;
      }
      f = f4;
    }
    f3();
  }
  f2();
}
f1();

f();
// expect: a
// expect: b
// expect: c

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__assign_to_shadowed_later", "[closure]")
{
    initVM();

    auto source = R"???(
var a = "global";

{
  fun assign() {
    a = "assigned";
  }

  var a = "inner";
  assign();
  print a; // expect: inner
}

print a; // expect: assigned

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__shadow_closure_with_local", "[closure]")
{
    initVM();

    auto source = R"???(
{
  var foo = "closure";
  fun f() {
    {
      print foo; // expect: closure
      var foo = "shadow";
      print foo; // expect: shadow
    }
    print foo; // expect: closure
  }
  f();
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__unused_later_closure", "[closure]")
{
    initVM();

    auto source = R"???(
// This is a regression test. When closing upvalues for discarded locals, it
// wouldn't make sure it discarded the upvalue for the correct stack slot.
//
// Here we create two locals that can be closed over, but only the first one
// actually is. When "b" goes out of scope, we need to make sure we don't
// prematurely close "a".
var closure;

{
  var a = "a";

  {
    var b = "b";
    fun returnA() {
      return a;
    }

    closure = returnA;

    if (false) {
      fun returnB() {
        return b;
      }
    }
  }

  print closure(); // expect: a
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__closed_closure_in_function", "[closure]")
{
    initVM();

    auto source = R"???(
var f;

{
  var local = "local";
  fun f_() {
    print local;
  }
  f = f_;
}

f(); // expect: local

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__unused_closure", "[closure]")
{
    initVM();

    auto source = R"???(
// This is a regression test. There was a bug where the VM would try to close
// an upvalue even if the upvalue was never created because the codepath for
// the closure was not executed.

{
  var a = "a";
  if (false) {
    fun foo() { a; }
  }
}

// If we get here, we didn't segfault when a went out of scope.
print "ok"; // expect: ok

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__assign_to_closure", "[closure]")
{
    initVM();

    auto source = R"???(
var f;
var g;

{
  var local = "local";
  fun f_() {
    print local;
    local = "after f";
    print local;
  }
  f = f_;

  fun g_() {
    print local;
    local = "after g";
    print local;
  }
  g = g_;
}

f();
// expect: local
// expect: after f

g();
// expect: after f
// expect: after g

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__reference_closure_multiple_times", "[closure]")
{
    initVM();

    auto source = R"???(
var f;

{
  var a = "a";
  fun f_() {
    print a;
    print a;
  }
  f = f_;
}

f();
// expect: a
// expect: a

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__open_closure_in_function", "[closure]")
{
    initVM();

    auto source = R"???(
{
  var local = "local";
  fun f() {
    print local; // expect: local
  }
  f();
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("closure__close_over_method_parameter", "[closure]")
{
    initVM();

    auto source = R"???(
var f;

class Foo {
  method(param) {
    fun f_() {
      print param;
    }
    f = f_;
  }
}

Foo().method("param");
f(); // expect: param

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("block__empty", "[block]")
{
    initVM();

    auto source = R"???(
{} // By itself.

// In a statement.
if (true) {}
if (false) {} else {}

print "ok"; // expect: ok

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("block__scope", "[block]")
{
    initVM();

    auto source = R"???(
var a = "outer";

{
  var a = "inner";
  print a; // expect: inner
}

print a; // expect: outer

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("print__missing_argument", "[print]")
{
    initVM();

    auto source = R"???(
// [line 2] Error at ';': Expect expression.
print;

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("this__this_at_top_level", "[this]")
{
    initVM();

    auto source = R"???(
this; // Error at 'this': Can't use 'this' outside of a class.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("this__nested_closure", "[this]")
{
    initVM();

    auto source = R"???(
class Foo {
  getClosure() {
    fun f() {
      fun g() {
        fun h() {
          return this.toString();
        }
        return h;
      }
      return g;
    }
    return f;
  }

  toString() { return "Foo"; }
}

var closure = Foo().getClosure();
print closure()()(); // expect: Foo

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("this__nested_class", "[this]")
{
    initVM();

    auto source = R"???(
class Outer {
  method() {
    print this; // expect: Outer instance

    fun f() {
      print this; // expect: Outer instance

      class Inner {
        method() {
          print this; // expect: Inner instance
        }
      }

      Inner().method();
    }
    f();
  }
}

Outer().method();

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("this__closure", "[this]")
{
    initVM();

    auto source = R"???(
class Foo {
  getClosure() {
    fun closure() {
      return this.toString();
    }
    return closure;
  }

  toString() { return "Foo"; }
}

var closure = Foo().getClosure();
print closure(); // expect: Foo

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("this__this_in_method", "[this]")
{
    initVM();

    auto source = R"???(
class Foo {
  bar() { return this; }
  baz() { return "baz"; }
}

print Foo().bar().baz(); // expect: baz

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("this__this_in_top_level_function", "[this]")
{
    initVM();

    auto source = R"???(
fun foo() {
  this; // Error at 'this': Can't use 'this' outside of a class.
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("function__extra_arguments", "[function]")
{
    initVM();

    auto source = R"???(
fun f(a, b) {
  print a;
  print b;
}

f(1, 2, 3, 4); // expect runtime error: Expected 2 arguments but got 4.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("function__too_many_parameters", "[function]")
{
    initVM();

    auto source = R"???(
// 256 parameters.
fun f(
    a1,
    a2,
    a3,
    a4,
    a5,
    a6,
    a7,
    a8,
    a9,
    a10,
    a11,
    a12,
    a13,
    a14,
    a15,
    a16,
    a17,
    a18,
    a19,
    a20,
    a21,
    a22,
    a23,
    a24,
    a25,
    a26,
    a27,
    a28,
    a29,
    a30,
    a31,
    a32,
    a33,
    a34,
    a35,
    a36,
    a37,
    a38,
    a39,
    a40,
    a41,
    a42,
    a43,
    a44,
    a45,
    a46,
    a47,
    a48,
    a49,
    a50,
    a51,
    a52,
    a53,
    a54,
    a55,
    a56,
    a57,
    a58,
    a59,
    a60,
    a61,
    a62,
    a63,
    a64,
    a65,
    a66,
    a67,
    a68,
    a69,
    a70,
    a71,
    a72,
    a73,
    a74,
    a75,
    a76,
    a77,
    a78,
    a79,
    a80,
    a81,
    a82,
    a83,
    a84,
    a85,
    a86,
    a87,
    a88,
    a89,
    a90,
    a91,
    a92,
    a93,
    a94,
    a95,
    a96,
    a97,
    a98,
    a99,
    a100,
    a101,
    a102,
    a103,
    a104,
    a105,
    a106,
    a107,
    a108,
    a109,
    a110,
    a111,
    a112,
    a113,
    a114,
    a115,
    a116,
    a117,
    a118,
    a119,
    a120,
    a121,
    a122,
    a123,
    a124,
    a125,
    a126,
    a127,
    a128,
    a129,
    a130,
    a131,
    a132,
    a133,
    a134,
    a135,
    a136,
    a137,
    a138,
    a139,
    a140,
    a141,
    a142,
    a143,
    a144,
    a145,
    a146,
    a147,
    a148,
    a149,
    a150,
    a151,
    a152,
    a153,
    a154,
    a155,
    a156,
    a157,
    a158,
    a159,
    a160,
    a161,
    a162,
    a163,
    a164,
    a165,
    a166,
    a167,
    a168,
    a169,
    a170,
    a171,
    a172,
    a173,
    a174,
    a175,
    a176,
    a177,
    a178,
    a179,
    a180,
    a181,
    a182,
    a183,
    a184,
    a185,
    a186,
    a187,
    a188,
    a189,
    a190,
    a191,
    a192,
    a193,
    a194,
    a195,
    a196,
    a197,
    a198,
    a199,
    a200,
    a201,
    a202,
    a203,
    a204,
    a205,
    a206,
    a207,
    a208,
    a209,
    a210,
    a211,
    a212,
    a213,
    a214,
    a215,
    a216,
    a217,
    a218,
    a219,
    a220,
    a221,
    a222,
    a223,
    a224,
    a225,
    a226,
    a227,
    a228,
    a229,
    a230,
    a231,
    a232,
    a233,
    a234,
    a235,
    a236,
    a237,
    a238,
    a239,
    a240,
    a241,
    a242,
    a243,
    a244,
    a245,
    a246,
    a247,
    a248,
    a249,
    a250,
    a251,
    a252,
    a253,
    a254,
    a255, a) {} // Error at 'a': Can't have more than 255 parameters.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("function__local_recursion", "[function]")
{
    initVM();

    auto source = R"???(
{
  fun fib(n) {
    if (n < 2) return n;
    return fib(n - 1) + fib(n - 2);
  }

  print fib(8); // expect: 21
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("function__missing_comma_in_parameters", "[function]")
{
    initVM();

    auto source = R"???(
// [line 3] Error at 'c': Expect ')' after parameters.
// [c line 4] Error at end: Expect '}' after block.
fun foo(a, b c, d, e, f) {}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("function__missing_arguments", "[function]")
{
    initVM();

    auto source = R"???(
fun f(a, b) {}

f(1); // expect runtime error: Expected 2 arguments but got 1.

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("function__empty_body", "[function]")
{
    initVM();

    auto source = R"???(
fun f() {}
print f(); // expect: nil

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("function__body_must_be_block", "[function]")
{
    initVM();

    auto source = R"???(
// [line 3] Error at '123': Expect '{' before function body.
// [c line 4] Error at end: Expect '}' after block.
fun f() 123;

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("function__recursion", "[function]")
{
    initVM();

    auto source = R"???(
fun fib(n) {
  if (n < 2) return n;
  return fib(n - 1) + fib(n - 2);
}

print fib(8); // expect: 21

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("function__local_mutual_recursion", "[function]")
{
    initVM();

    auto source = R"???(
{
  fun isEven(n) {
    if (n == 0) return true;
    return isOdd(n - 1); // expect runtime error: Undefined variable 'isOdd'.
  }

  fun isOdd(n) {
    if (n == 0) return false;
    return isEven(n - 1);
  }

  isEven(4);
}
)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_RUNTIME_ERROR);
}

TEST_CASE("function__print", "[function]")
{
    initVM();

    auto source = R"???(
fun foo() {}
print foo; // expect: <fn foo>

print clock; // expect: <native fn>

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("function__too_many_arguments", "[function]")
{
    initVM();

    auto source = R"???(
fun foo() {}
{
  var a = 1;
  foo(
     a, // 1
     a, // 2
     a, // 3
     a, // 4
     a, // 5
     a, // 6
     a, // 7
     a, // 8
     a, // 9
     a, // 10
     a, // 11
     a, // 12
     a, // 13
     a, // 14
     a, // 15
     a, // 16
     a, // 17
     a, // 18
     a, // 19
     a, // 20
     a, // 21
     a, // 22
     a, // 23
     a, // 24
     a, // 25
     a, // 26
     a, // 27
     a, // 28
     a, // 29
     a, // 30
     a, // 31
     a, // 32
     a, // 33
     a, // 34
     a, // 35
     a, // 36
     a, // 37
     a, // 38
     a, // 39
     a, // 40
     a, // 41
     a, // 42
     a, // 43
     a, // 44
     a, // 45
     a, // 46
     a, // 47
     a, // 48
     a, // 49
     a, // 50
     a, // 51
     a, // 52
     a, // 53
     a, // 54
     a, // 55
     a, // 56
     a, // 57
     a, // 58
     a, // 59
     a, // 60
     a, // 61
     a, // 62
     a, // 63
     a, // 64
     a, // 65
     a, // 66
     a, // 67
     a, // 68
     a, // 69
     a, // 70
     a, // 71
     a, // 72
     a, // 73
     a, // 74
     a, // 75
     a, // 76
     a, // 77
     a, // 78
     a, // 79
     a, // 80
     a, // 81
     a, // 82
     a, // 83
     a, // 84
     a, // 85
     a, // 86
     a, // 87
     a, // 88
     a, // 89
     a, // 90
     a, // 91
     a, // 92
     a, // 93
     a, // 94
     a, // 95
     a, // 96
     a, // 97
     a, // 98
     a, // 99
     a, // 100
     a, // 101
     a, // 102
     a, // 103
     a, // 104
     a, // 105
     a, // 106
     a, // 107
     a, // 108
     a, // 109
     a, // 110
     a, // 111
     a, // 112
     a, // 113
     a, // 114
     a, // 115
     a, // 116
     a, // 117
     a, // 118
     a, // 119
     a, // 120
     a, // 121
     a, // 122
     a, // 123
     a, // 124
     a, // 125
     a, // 126
     a, // 127
     a, // 128
     a, // 129
     a, // 130
     a, // 131
     a, // 132
     a, // 133
     a, // 134
     a, // 135
     a, // 136
     a, // 137
     a, // 138
     a, // 139
     a, // 140
     a, // 141
     a, // 142
     a, // 143
     a, // 144
     a, // 145
     a, // 146
     a, // 147
     a, // 148
     a, // 149
     a, // 150
     a, // 151
     a, // 152
     a, // 153
     a, // 154
     a, // 155
     a, // 156
     a, // 157
     a, // 158
     a, // 159
     a, // 160
     a, // 161
     a, // 162
     a, // 163
     a, // 164
     a, // 165
     a, // 166
     a, // 167
     a, // 168
     a, // 169
     a, // 170
     a, // 171
     a, // 172
     a, // 173
     a, // 174
     a, // 175
     a, // 176
     a, // 177
     a, // 178
     a, // 179
     a, // 180
     a, // 181
     a, // 182
     a, // 183
     a, // 184
     a, // 185
     a, // 186
     a, // 187
     a, // 188
     a, // 189
     a, // 190
     a, // 191
     a, // 192
     a, // 193
     a, // 194
     a, // 195
     a, // 196
     a, // 197
     a, // 198
     a, // 199
     a, // 200
     a, // 201
     a, // 202
     a, // 203
     a, // 204
     a, // 205
     a, // 206
     a, // 207
     a, // 208
     a, // 209
     a, // 210
     a, // 211
     a, // 212
     a, // 213
     a, // 214
     a, // 215
     a, // 216
     a, // 217
     a, // 218
     a, // 219
     a, // 220
     a, // 221
     a, // 222
     a, // 223
     a, // 224
     a, // 225
     a, // 226
     a, // 227
     a, // 228
     a, // 229
     a, // 230
     a, // 231
     a, // 232
     a, // 233
     a, // 234
     a, // 235
     a, // 236
     a, // 237
     a, // 238
     a, // 239
     a, // 240
     a, // 241
     a, // 242
     a, // 243
     a, // 244
     a, // 245
     a, // 246
     a, // 247
     a, // 248
     a, // 249
     a, // 250
     a, // 251
     a, // 252
     a, // 253
     a, // 254
     a, // 255
     a); // Error at 'a': Can't have more than 255 arguments.
}

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_COMPILE_ERROR);
}

TEST_CASE("function__mutual_recursion", "[function]")
{
    initVM();

    auto source = R"???(
fun isEven(n) {
  if (n == 0) return true;
  return isOdd(n - 1);
}

fun isOdd(n) {
  if (n == 0) return false;
  return isEven(n - 1);
}

print isEven(4); // expect: true
print isOdd(3); // expect: true

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}

TEST_CASE("function__parameters", "[function]")
{
    initVM();

    auto source = R"???(
fun f0() { return 0; }
print f0(); // expect: 0

fun f1(a) { return a; }
print f1(1); // expect: 1

fun f2(a, b) { return a + b; }
print f2(1, 2); // expect: 3

fun f3(a, b, c) { return a + b + c; }
print f3(1, 2, 3); // expect: 6

fun f4(a, b, c, d) { return a + b + c + d; }
print f4(1, 2, 3, 4); // expect: 10

fun f5(a, b, c, d, e) { return a + b + c + d + e; }
print f5(1, 2, 3, 4, 5); // expect: 15

fun f6(a, b, c, d, e, f) { return a + b + c + d + e + f; }
print f6(1, 2, 3, 4, 5, 6); // expect: 21

fun f7(a, b, c, d, e, f, g) { return a + b + c + d + e + f + g; }
print f7(1, 2, 3, 4, 5, 6, 7); // expect: 28

fun f8(a, b, c, d, e, f, g, h) { return a + b + c + d + e + f + g + h; }
print f8(1, 2, 3, 4, 5, 6, 7, 8); // expect: 36

)???";

    auto result = interpret(source);
    REQUIRE(result == INTERPRET_OK);
}
