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

struct user_defined_type {
  int x;
};

std::ostream& operator<<(std::ostream& out, const user_defined_type& v) {
  out << "user_defined_type{" << v.x << "}";
  return out;
}

int main(int argc, char const* argv[]) {
  user_defined_type udt{42};
  dbg(udt);

  assert_eq(pretty_print(udt), "user_defined_type{42}");

  assert_eq(dbg_macro::type_name<user_defined_type>(), "user_defined_type");

  return 0;
}
