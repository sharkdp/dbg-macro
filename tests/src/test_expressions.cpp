#include <string>
#include "test.h"

int main(int argc, char const* argv[]) {
  int test_int = 42;

  const std::string hello = "hello";
  const std::string world = "world";

  dbg(9 + 33);
  dbg(hello + " " + world);

  const auto new_int = dbg(test_int) + dbg(2);
  assert_eq(new_int, 44);

  const auto my_string = dbg("my string");
  assert_eq(my_string, std::string("my string"));

  return 0;
}
