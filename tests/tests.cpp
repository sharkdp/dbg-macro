#include <array>
#include <cstdint>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include <dbg.h>

void simple_assert_helper(const bool condition, const char* expr) {
  if (!condition) {
    std::cerr << "assertion '" << expr << "' failed!\n";
    std::exit(1);
  }
}

#define simple_assert(expr) simple_assert_helper((expr), #expr)

template <typename T>
std::string prettyPrint(T&& value) {
  std::stringstream stream;
  dbg_macro::prettyPrint(stream, std::forward<T>(value));
  return stream.str();
}

struct user_defined_type {
  int x;
};

class user_defined_class {
 public:
  void some_method(int x) { dbg(x); }
};

std::ostream& operator<<(std::ostream& out, const user_defined_type& v) {
  out << "user_defined_type{" << v.x << "}";
  return out;
}

int main() {
  dbg("====== primitive types");

  int test_int = 42;
  const float test_float = 3.14;
  const bool test_bool = false;
  const char test_char = 'X';
  const uint64_t test_uint64_t = 12345678987654321;
  int* test_pointer = &test_int;
  const int* test_pointer_to_const = &test_int;
  int* test_pointer_null = nullptr;
  const int& test_ref_to_int = test_int;
  const char* test_c_string = "hello";
  const std::string test_string = "hello";

  dbg(test_int);
  dbg(test_float);
  dbg(test_bool);
  dbg(test_char);
  dbg(test_uint64_t);
  dbg(test_pointer);
  dbg(test_pointer_to_const);
  dbg(test_pointer_null);
  dbg(test_ref_to_int);
  dbg(test_c_string);
  dbg(test_string);

  dbg("====== r-values, literals, constants, etc.");

  dbg(42);
  dbg(3.14);
  dbg(false);
  dbg(12345678987654321);
  dbg(static_cast<void*>(nullptr));
  dbg("string literal");

  std::string message = "hello world";
  dbg(std::move(message));

  dbg(sizeof(int));

  dbg("====== expressions inside macros");

  dbg(9 + 33);
  dbg(test_string + " world");

  dbg("====== using dbg(..) inside expressions");

  const auto new_int = dbg(test_int) + dbg(2);
  simple_assert(new_int == 44);

  const auto my_string = dbg("my string");
  simple_assert(my_string == std::string("my string"));

  dbg("====== containers");

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

  const std::array<int, 2> dummy_array{{0, 4}};
  dbg(dummy_array);

  const std::list<int> dummy_list{1, 2, 3, 4, 5, 6, 7, 8, 9};
  dbg(dummy_list);

  std::vector<std::vector<int>> vec_of_vec_of_ints{{1, 2}, {3, 4, 5}};
  dbg(vec_of_vec_of_ints);

  std::vector<std::vector<std::vector<int>>> vec_of_vec_of_vec_of_ints{
      {{1, 2}, {3, 4, 5}}, {{3}}};
  dbg(vec_of_vec_of_vec_of_ints);

  dbg("====== user-defined types");

  user_defined_type udt{42};
  dbg(udt);

  dbg("====== side effects");

  int x = 1;
  dbg(++x);
  simple_assert(x == 2);

  dbg("====== function name tests");

  user_defined_class{}.some_method(42);

  [](int x) {
    dbg("called from within a lambda!");
    return x;
  }(42);

  dbg("====== prettyPrint tests");

  simple_assert(prettyPrint(3) == "3");
  simple_assert(prettyPrint(3.14) == "3.14");
  simple_assert(prettyPrint(true) == "true");
  simple_assert(prettyPrint(static_cast<void*>(nullptr)) == "nullptr");
  simple_assert(prettyPrint("string literal") == "string literal");
  simple_assert(prettyPrint('X') == "'X'");
  simple_assert(prettyPrint(test_c_string) == "\"hello\"");

  simple_assert(prettyPrint(std::vector<int>{}) == "{}");
  simple_assert(prettyPrint(std::vector<int>{1, 2, 3}) == "{1, 2, 3}");
  simple_assert(prettyPrint(std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}) ==
                "{1, 2, 3, 4, 5, ... size:9}");
  simple_assert(prettyPrint(vec_of_vec_of_ints) == "{{1, 2}, {3, 4, 5}}");

  simple_assert(prettyPrint(udt) == "user_defined_type{42}");

  dbg("====== type_name<T>() tests");

  simple_assert(dbg_macro::type_name<int>() == "int");
  simple_assert(dbg_macro::type_name<char>() == "char");
  simple_assert(dbg_macro::type_name<std::string>() == "std::string");
  simple_assert(dbg_macro::type_name<user_defined_type>() ==
                "user_defined_type");
}
