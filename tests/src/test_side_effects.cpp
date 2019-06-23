#include <dbg_macro/dbg.h>

template <typename L, typename R>
void assert_eq(const L& lhs, const R& rhs) {
  if (lhs != rhs) {
    std::cerr << "Assertion 'lhs == rhs' failed!\n";
    dbg(lhs);
    dbg(rhs);
    std::exit(1);
  }
}

int main(int argc, char const* argv[]) {
  int x = 1;
  dbg(++x);
  assert_eq(x, 2);
  return 0;
}
