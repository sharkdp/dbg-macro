#include "test.h"
#include <list>

int main(int argc, char const* argv[]) {
  std::list<int> list1{};
  std::list<int> list2{1, 2, 3};

  const std::list<int> list3{};
  const std::list<int> list4{1, 2, 3};

  dbg(list1);
  dbg(list2);

  dbg(list3);
  dbg(list4);

  dbg(std::list<int>{});
  dbg(std::list<int>{1, 2, 3});

  assert_eq(pretty_print(std::list<int>{}), "{}");
  assert_eq(pretty_print(std::list<int>{1, 2, 3}), "{1, 2, 3}");

  assert_eq(dbg_macro::type_name<std::list<int>>(), "std::list<int>");

  assert_eq(dbg_macro::type_name<const std::list<int>>(), "const std::list<int>");

  return 0;
}
