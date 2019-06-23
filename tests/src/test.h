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

template <typename T>
std::string pretty_print(T&& value) {
  std::stringstream stream;
  dbg_macro::pretty_print(stream, std::forward<T>(value));
  return stream.str();
}