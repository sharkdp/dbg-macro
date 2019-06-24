#include <string>
#include "test.h"

int main(int argc, char const* argv[]) {
  int int1 = 1337;
  int &ref1 = int1;
  int *ptr1 = &int1;

  const int int2 = 1337;
  const int &ref2 = int2;
  const int *ptr2 = &int2;

  int * ptr3 = nullptr;

  const char* c_string = "hello";

  dbg(int1);
  dbg(ptr1);
  dbg(ref1);

  dbg(int2);
  dbg(ptr2);
  dbg(ref2);

  dbg(ptr3);

  dbg(c_string);

  assert_eq(dbg_macro::type_name<int>(), "int");
  assert_eq(dbg_macro::type_name<int*>(), "int*");
  assert_eq(dbg_macro::type_name<int&>(), "int&");

  assert_eq(dbg_macro::type_name<const int>(), "const int");
  assert_eq(dbg_macro::type_name<const int*>(), "const int*");
  assert_eq(dbg_macro::type_name<const int&>(), "const int&");

  assert_eq(pretty_print(static_cast<void*>(nullptr)), "nullptr");

  assert_eq(pretty_print(c_string), "\"hello\"");

  return 0;
}
