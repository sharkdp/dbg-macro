#include <list>
#include "test.h"

int main(int argc, char const* argv[]) {
  std::list<int> list1{};
  std::list<int> list2{1, 2, 3};

  std::list<std::list<int>> list3{};
  std::list<std::list<int>> list4{{}};
  std::list<std::list<int>> list5{{}, {}};
  std::list<std::list<int>> list6{{1, 0}, {0, 1}};

  const std::list<int> list7{};
  const std::list<int> list8{1, 2, 3};

  const std::list<std::list<int>> list9{};
  const std::list<std::list<int>> list10{{}};
  const std::list<std::list<int>> list11{{}, {}};
  const std::list<std::list<int>> list12{{1, 0}, {0, 1}};

  dbg(list1);
  dbg(list2);

  dbg(list3);
  dbg(list4);
  dbg(list5);
  dbg(list6);

  dbg(list7);
  dbg(list8);

  dbg(list9);
  dbg(list10);
  dbg(list11);
  dbg(list12);

  dbg(std::list<int>{});
  dbg(std::list<int>{1, 2, 3});

  dbg(std::list<std::list<int>>{});
  dbg(std::list<std::list<int>>{{}});
  dbg(std::list<std::list<int>>{{}, {}});
  dbg(std::list<std::list<int>>{{1, 0}, {0, 1}});

  assert_eq(pretty_print(std::list<int>{}), "{}");
  assert_eq(pretty_print(std::list<int>{1, 2, 3}), "{1, 2, 3}");

  assert_eq(pretty_print(std::list<std::list<int>>{}), "{}");
  assert_eq(pretty_print(std::list<std::list<int>>{{}}), "{{}}");
  assert_eq(pretty_print(std::list<std::list<int>>{{}, {}}), "{{}, {}}");
  assert_eq(pretty_print(std::list<std::list<int>>{{1, 0}, {0, 1}}), "{{1, 0}, {0, 1}}");

  assert_eq(dbg_macro::type_name<std::list<int>>(), "std::list<int>");
  assert_eq(dbg_macro::type_name<std::list<std::list<int>>>(), "std::list<std::list<int>>");

  assert_eq(dbg_macro::type_name<const std::list<int>>(), "const std::list<int>");
  assert_eq(dbg_macro::type_name<const std::list<std::list<int>>>(), "const std::list<std::list<int>>");

  return 0;
}
