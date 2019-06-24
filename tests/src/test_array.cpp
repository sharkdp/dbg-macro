#include <array>
#include "test.h"

int main(int argc, char const* argv[]) {
  std::array<int,3> array1{};
  std::array<int,3> array2{1, 2, 3};

  const std::array<int,3> array3{};
  const std::array<int,3> array4{1, 2, 3};

  dbg(array1);
  dbg(array2);

  dbg(array3);
  dbg(array4);

  dbg(std::array<int, 3>{});
  dbg(std::array<int, 3>{1, 2, 3});

  assert_eq(pretty_print(std::array<int, 3>{}), "{0, 0, 0}");
  assert_eq(pretty_print(std::array<int, 3>{1, 2, 3}), "{1, 2, 3}");

  assert_eq(dbg_macro::type_name<std::array<int, 3>>(), "std::array<int, 3>");

  assert_eq(dbg_macro::type_name<const std::array<int, 3>>(), "const std::array<int, 3>");

  return 0;
}
