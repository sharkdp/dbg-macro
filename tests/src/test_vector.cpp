#include <vector>
#include "test.h"

int main(int argc, char const* argv[]) {
  const std::vector<int> dummy_vec_int{3, 2, 3};
  dbg(dummy_vec_int);

  std::vector<int> dummy_vec_int_nonconst{1, 2, 3};
  dbg(dummy_vec_int_nonconst);

  const std::vector<int> dummy_vec_empty{};
  dbg(dummy_vec_empty);

  std::vector<char> vec_chars{'h', 'e', 'l', 'l', 'o'};
  dbg(vec_chars);

  std::vector<bool> vec_bools{true, true, false, false, false, true, false};
  dbg(vec_bools);

  dbg(std::vector<int>{0, 1, 0, 1});

  std::vector<std::vector<int>> vec_of_vec_of_ints{{1, 2}, {3, 4, 5}};
  dbg(vec_of_vec_of_ints);

  std::vector<std::vector<std::vector<int>>> vec_of_vec_of_vec_of_ints{
      {{1, 2}, {3, 4, 5}}, {{3}}};
  dbg(vec_of_vec_of_vec_of_ints);

  assert_eq(pretty_print(std::vector<int>{}), "{}");
  assert_eq(pretty_print(std::vector<int>{1, 2, 3}), "{1, 2, 3}");
  assert_eq(pretty_print(std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}),
            "{1, 2, 3, 4, 5, ... size:9}");
  assert_eq(pretty_print(vec_of_vec_of_ints), "{{1, 2}, {3, 4, 5}}");

  assert_eq(dbg_macro::type_name<std::vector<int>>(), "std::vector<int>");
  assert_eq(dbg_macro::type_name<std::vector<const int*>>(),
            "std::vector<const int*>");
  assert_eq(dbg_macro::type_name<std::vector<std::vector<int>>>(),
            "std::vector<std::vector<int>>");

  return 0;
}
