#include "test.h"

int main(int argc, char const* argv[]) {
  int x = 1;
  dbg(++x);
  assert_eq(x, 2);
  return 0;
}
