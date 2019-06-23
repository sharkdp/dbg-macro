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

class user_defined_class {
 public:
  void some_method(int x) { dbg(x); }
};

int main(int argc, char const* argv[]) {
  user_defined_class{}.some_method(42);
  return 0;
}
