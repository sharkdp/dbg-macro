#include "test.h"

int main(int argc, char const* argv[]) {
  int counter = 0;

  dbg(counter++);

  assert_eq(counter, 1);

  dbg(++counter);

  assert_eq(counter, 2);

  dbg(--counter);

  assert_eq(counter, 1);

  dbg(counter--);

  assert_eq(counter, 0);

  return 0;
}
