#include "test.h"

int main(int argc, char const* argv[]) {
  dbg(1337);
  dbg("string literal");

  assert_eq(pretty_print(1337), "1337");
  assert_eq(pretty_print("string literal"), "string literal");

  return 0;
}
