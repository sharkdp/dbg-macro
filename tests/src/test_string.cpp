#include "test.h"

int main(int argc, char const* argv[]) {
  const std::string string = "hello world";

  dbg(string);

  assert_eq(pretty_print(string), "\"hello world\"");

  assert_eq(dbg_macro::type_name<std::string>(), "std::string");

  return 0;
}
