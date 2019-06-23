#include <cstdint>
#include <string>
#include "test.h"

int main(int argc, char const* argv[]) {
  int test_int = 42;
  const float test_float = 3.14f;
  const bool test_bool = false;
  const char test_char = 'X';
  const uint64_t test_uint64_t = 12345678987654321;
  int* test_pointer = &test_int;
  const int* test_pointer_to_const = &test_int;
  int* test_pointer_null = nullptr;
  const int& test_ref_to_int = test_int;
  const char* test_c_string = "hello";
  const std::string test_string = "hello";

  dbg(test_int);
  dbg(test_float);
  dbg(test_bool);
  dbg(test_char);
  dbg(test_uint64_t);
  dbg(test_pointer);
  dbg(test_pointer_to_const);
  dbg(test_pointer_null);
  dbg(test_ref_to_int);
  dbg(test_c_string);
  dbg(test_string);

  assert_eq(pretty_print(3), "3");
  assert_eq(pretty_print(3.14), "3.14");
  assert_eq(pretty_print(true), "true");
  assert_eq(pretty_print(static_cast<void*>(nullptr)), "nullptr");
  assert_eq(pretty_print("string literal"), "string literal");
  assert_eq(pretty_print('X'), "'X'");
  assert_eq(pretty_print(test_c_string), "\"hello\"");

  assert_eq(dbg_macro::type_name<void>(), "void");
  assert_eq(dbg_macro::type_name<int>(), "int");
  assert_eq(dbg_macro::type_name<char>(), "char");
  assert_eq(dbg_macro::type_name<short>(), "short");
  assert_eq(dbg_macro::type_name<long>(), "long");
  assert_eq(dbg_macro::type_name<unsigned short>(), "unsigned short");
  assert_eq(dbg_macro::type_name<unsigned long>(), "unsigned long");
  assert_eq(dbg_macro::type_name<float>(), "float");

  assert_eq(dbg_macro::type_name<const int>(), "const int");
  assert_eq(dbg_macro::type_name<volatile int>(), "volatile int");

  assert_eq(dbg_macro::type_name<int&>(), "int&");
  assert_eq(dbg_macro::type_name<const int&>(), "const int&");

  assert_eq(dbg_macro::type_name<int*>(), "int*");
  assert_eq(dbg_macro::type_name<int** const*>(), "int** const*");
  assert_eq(dbg_macro::type_name<const int*>(), "const int*");
  assert_eq(dbg_macro::type_name<int* const>(), "int* const");
  assert_eq(dbg_macro::type_name<const int* const>(), "const int* const");

  assert_eq(dbg_macro::type_name<std::string>(), "std::string");

  return 0;
}
