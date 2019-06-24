#include <vector>
#include "test.h"

int main(int argc, char const* argv[]) {
  std::vector<int> vector1{};
  std::vector<int> vector2{1, 2, 3};

  std::vector<std::vector<int>> vector3{};
  std::vector<std::vector<int>> vector4{{}};
  std::vector<std::vector<int>> vector5{{}, {}};
  std::vector<std::vector<int>> vector6{{1, 0}, {0, 1}};

  const std::vector<int> vector7{};
  const std::vector<int> vector8{1, 2, 3};

  const std::vector<std::vector<int>> vector9{};
  const std::vector<std::vector<int>> vector10{{}};
  const std::vector<std::vector<int>> vector11{{}, {}};
  const std::vector<std::vector<int>> vector12{{1, 0}, {0, 1}};

  dbg(vector1);
  dbg(vector2);

  dbg(vector3);
  dbg(vector4);
  dbg(vector5);
  dbg(vector6);

  dbg(vector7);
  dbg(vector8);

  dbg(vector9);
  dbg(vector10);
  dbg(vector11);
  dbg(vector12);

  dbg(std::vector<int>{});
  dbg(std::vector<int>{1, 2, 3});

  dbg(std::vector<std::vector<int>>{});
  dbg(std::vector<std::vector<int>>{{}});
  dbg(std::vector<std::vector<int>>{{}, {}});
  dbg(std::vector<std::vector<int>>{{1, 0}, {0, 1}});

  assert_eq(pretty_print(std::vector<int>{}), "{}");
  assert_eq(pretty_print(std::vector<int>{1, 2, 3}), "{1, 2, 3}");

  assert_eq(pretty_print(std::vector<std::vector<int>>{}), "{}");
  assert_eq(pretty_print(std::vector<std::vector<int>>{{}}), "{{}}");
  assert_eq(pretty_print(std::vector<std::vector<int>>{{}, {}}), "{{}, {}}");
  assert_eq(pretty_print(std::vector<std::vector<int>>{{1, 0}, {0, 1}}), "{{1, 0}, {0, 1}}");

  assert_eq(dbg_macro::type_name<std::vector<int>>(), "std::vector<int>");
  assert_eq(dbg_macro::type_name<std::vector<std::vector<int>>>(), "std::vector<std::vector<int>>");

  assert_eq(dbg_macro::type_name<const std::vector<int>>(), "const std::vector<int>");
  assert_eq(dbg_macro::type_name<const std::vector<std::vector<int>>>(), "const std::vector<std::vector<int>>");

  return 0;
}
