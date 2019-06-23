#include "test.h"

enum user_defined_enum { UDE_VALUE13 = 13, UDE_VALUE42 = 42 };

int main(int argc, char const* argv[]) {
  user_defined_enum ude = UDE_VALUE42;
  dbg(ude);

  assert_eq(pretty_print(ude), "42");

  return 0;
}
