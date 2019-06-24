#include <array>
#include "test.h"

int main(int argc, char const* argv[]) {
  std::array<int,3> array1{};
  std::array<int,3> array2{1, 2, 3};

  std::array<std::array<int, 2>, 2> array3{};
  std::array<std::array<int, 2>, 2> array4{1, 0, 0, 1};

  const std::array<int,3> array5{};
  const std::array<int,3> array6{1, 2, 3};

  const std::array<std::array<int, 2>, 2> array7{};
  const std::array<std::array<int, 2>, 2> array8{1, 0, 0, 1};

  dbg(array1);
  dbg(array2);

  dbg(array3);
  dbg(array4);

  dbg(array5);
  dbg(array6);

  dbg(array7);
  dbg(array8);

  dbg(std::array<int, 3>{});
  dbg(std::array<int, 3>{1, 2, 3});

  dbg(std::array<std::array<int, 2>, 2>{});
  dbg(std::array<std::array<int, 2>, 2>{1, 0, 0, 1});

  assert_eq(pretty_print(std::array<int, 3>{}), "{0, 0, 0}");
  assert_eq(pretty_print(std::array<int, 3>{1, 2, 3}), "{1, 2, 3}");

  assert_eq(pretty_print(std::array<std::array<int, 2>, 2>{}), "{{0, 0}, {0, 0}}");
  assert_eq(pretty_print(std::array<std::array<int, 2>, 2>{1, 0, 0, 1}), "{{1, 0}, {0, 1}}");

  assert_eq(dbg_macro::type_name<std::array<int, 3>>(), "std::array<int, 3>");
  assert_eq(dbg_macro::type_name<std::array<std::array<int, 2>, 2>>(), "std::array<std::array<int, 2>, 2>");

  assert_eq(dbg_macro::type_name<const std::array<int, 3>>(), "const std::array<int, 3>");
  assert_eq(dbg_macro::type_name<const std::array<std::array<int, 2>, 2>>(), "const std::array<std::array<int, 2>, 2>");

  return 0;
}
