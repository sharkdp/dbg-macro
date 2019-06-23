#include "test.h"

struct user_defined_type {
  int x;
};

std::ostream& operator<<(std::ostream& out, const user_defined_type& v) {
  out << "user_defined_type{" << v.x << "}";
  return out;
}

namespace dbg_macro {
    std::string get_type_name(type_tag<user_defined_type>) {
        return "user_defined_type";
    }
}

int main(int argc, char const* argv[]) {
  user_defined_type udt{42};
  dbg(udt);

  assert_eq(pretty_print(udt), "user_defined_type{42}");

  assert_eq(dbg_macro::type_name<user_defined_type>(), "user_defined_type");

  return 0;
}
