#include <array>
#include <cstdint>
#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#if DBG_MACRO_CXX_STANDARD >= 17
#include <optional>
#include <string_view>
#include <variant>
#endif

#include <dbg.h>

int main() {
  dbg("====== primitive types");

  int test_int = 42;
  const float test_float = 3.14f;
  const bool test_bool = false;
  const char test_char = 'X';
  const uint64_t test_uint64_t = 12345678987654321;
  int* test_pointer = &test_int;
  const int* test_pointer_to_const = &test_int;
  int* test_pointer_null = nullptr;
  const int& test_ref_to_int = test_int;
  const char* test_c_string = "hello";
  const char test_c_chararray[] = "hello";
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
  dbg(test_c_chararray);
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

  dbg("====== multiple arguments");

  dbg(test_int, (std::vector<int>{2, 3, 4}), test_string);

  dbg("====== containers");

  const std::vector<int> dummy_vec_int{3, 2, 3};
  dbg(dummy_vec_int);

  std::vector<int> dummy_vec_int_nonconst{1, 2, 3};
  dbg(dummy_vec_int_nonconst);

  const std::vector<int> dummy_vec_empty{};
  dbg(dummy_vec_empty);

  std::vector<char> vec_chars{'h', 'e', 'l', 'l', 'o', '\x00', '\xFE'};
  dbg(vec_chars);

  std::vector<bool> vec_bools{true, true, false, false, false, true, false};
  dbg(vec_bools);

  dbg((std::vector<int>{0, 1, 0, 1}));

  const std::array<int, 2> dummy_array{{0, 4}};
  dbg(dummy_array);

  const std::list<int> dummy_list{1, 2, 3, 4, 5, 6, 7, 8, 9};
  dbg(dummy_list);

  std::vector<std::vector<int>> vec_of_vec_of_ints{{1, 2}, {3, 4, 5}};
  dbg(vec_of_vec_of_ints);

  std::vector<std::vector<std::vector<int>>> vec_of_vec_of_vec_of_ints{
      {{1, 2}, {3, 4, 5}}, {{3}}};
  dbg(vec_of_vec_of_vec_of_ints);

  int dummy_int_array[] = {11, 22, 33};
  dbg(dummy_int_array);

  dbg("====== integer formatting");
  dbg(dbg::hex(42));
  dbg(dbg::bin(0x00ff00ff));

  int8_t negative_five = -5;
  dbg(dbg::bin(negative_five));
  dbg(dbg::bin(static_cast<uint8_t>(negative_five)));

  dbg("====== std::tuple and std::pair");
  dbg((std::tuple<std::string, int, float>{"Hello", 7, 3.14f}));
  dbg((std::pair<std::string, int>{"Hello", 7}));

#if DBG_MACRO_CXX_STANDARD >= 17
  dbg("====== Sum types");
  dbg(std::make_optional<bool>(false));
  dbg((std::variant<int, std::string>{"test"}));

  dbg("======= std::string_view");
  dbg(std::string_view{"test"});
#endif

  dbg("====== function name tests");

  class user_defined_class {
   public:
    user_defined_class() {}
    void some_method(int x) { dbg(x); }
  };
  user_defined_class{}.some_method(42);

  [](int x) {
    dbg("called from within a lambda!");
    return x;
  }(42);

  dbg("====== type names without a value");
  using IsSame = std::is_same<uint8_t, char>::type;

  struct user_defined_trivial_type {
    int32_t a;
    bool b;
  };

  dbg(dbg::type<IsSame>());
  dbg(dbg::type<int32_t>());
  dbg(dbg::type<const int32_t>());
  dbg(dbg::type<int32_t*>());
  dbg(dbg::type<int32_t&>());
  dbg(dbg::type<user_defined_trivial_type>());
  dbg(dbg::type<user_defined_class>());

  dbg("====== timestamp");
  dbg(dbg::time());
}
