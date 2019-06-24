#include "test.h"

int main(int argc, char const* argv[]) {
  const std::string test_string = "hello";

  dbg(test_string);

  assert_eq(dbg_macro::type_name<std::string>(), "std::string");

  return 0;
}
