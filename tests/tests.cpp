#include <array>
#include <cstdint>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include <dbg.h>

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

class user_defined_class {
 public:
  void some_method(int x) { dbg(x); }
};

std::ostream& operator<<(std::ostream& out, const user_defined_type& v) {
  out << "user_defined_type{" << v.x << "}";
  return out;
}

enum user_defined_enum { UDE_VALUE13 = 13, UDE_VALUE42 = 42 };
enum class user_defined_enum_class { VALUE13 = 13, VALUE42 = 42 };

template <typename T, std::size_t N>
struct user_defined_container {
  T data[N];
  const T* begin() const { return data; }
  const T* end() const { return data + N; }
  std::size_t size() const { return N; }
};

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

  dbg("====== using dbg(..) inside expressions");

  const auto new_int = dbg(test_int) + dbg(2);
  assert_eq(new_int, 44);

  const auto my_string = dbg("my string");
  assert_eq(my_string, std::string("my string"));

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

  int dummy_int_array[] = {11, 22, 33};
  dbg(dummy_int_array);

  user_defined_container<int, 3> dummy_udc = {{11, 22, 33}};
  dbg(dummy_udc);

  dbg("====== user-defined types");

  user_defined_type udt{42};
  dbg(udt);

  user_defined_enum ude = UDE_VALUE42;
  dbg(ude);
  user_defined_enum_class udec = user_defined_enum_class::VALUE42;
  dbg(udec);

  dbg("====== side effects");

  int x = 1;
  dbg(++x);
  assert_eq(x, 2);

  dbg("====== function name tests");

  user_defined_class{}.some_method(42);

  [](int x) {
    dbg("called from within a lambda!");
    return x;
  }(42);

  dbg("====== pretty_print tests");

  assert_eq(pretty_print(3), "3");
  assert_eq(pretty_print(3.14), "3.14");
  assert_eq(pretty_print(true), "true");
  assert_eq(pretty_print(static_cast<void*>(nullptr)), "nullptr");
  assert_eq(pretty_print("string literal"), "string literal");
  assert_eq(pretty_print('X'), "'X'");
  assert_eq(pretty_print(test_c_string), "\"hello\"");

  assert_eq(pretty_print(std::vector<int>{}), "{}");
  assert_eq(pretty_print(std::vector<int>{1, 2, 3}), "{1, 2, 3}");
  assert_eq(pretty_print(std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}),
            "{1, 2, 3, 4, 5, ... size:9}");
  assert_eq(pretty_print(vec_of_vec_of_ints), "{{1, 2}, {3, 4, 5}}");

  assert_eq(pretty_print(udt), "user_defined_type{42}");
  assert_eq(pretty_print(ude), "42");
  assert_eq(pretty_print(udec), "42");

  assert_eq(pretty_print(std::tuple<int, float>{42, 3.14f}), "{42, 3.14}");
  assert_eq(pretty_print(std::tuple<>{}), "{}");

#if __cplusplus >= 201703L
  assert_eq(pretty_print(std::make_optional<int>(42)), "{42}");
  std::optional<int> empty_optional;
  assert_eq(pretty_print(empty_optional), "nullopt");
#endif

  dbg("====== type_name<T>() tests");

  using namespace dbg_macro;

  assert_eq(type_name<void>(), "void");
  assert_eq(type_name<int>(), "int");
  assert_eq(type_name<char>(), "char");
  assert_eq(type_name<short>(), "short");
  assert_eq(type_name<long>(), "long");
  assert_eq(type_name<unsigned short>(), "unsigned short");
  assert_eq(type_name<unsigned long>(), "unsigned long");
  assert_eq(type_name<float>(), "float");

  assert_eq(type_name<const int>(), "const int");
  assert_eq(type_name<volatile int>(), "volatile int");

  assert_eq(type_name<int&>(), "int&");
  assert_eq(type_name<const int&>(), "const int&");

  assert_eq(type_name<int*>(), "int*");
  assert_eq(type_name<int** const*>(), "int** const*");
  assert_eq(type_name<const int*>(), "const int*");
  assert_eq(type_name<int* const>(), "int* const");
  assert_eq(type_name<const int* const>(), "const int* const");

  assert_eq(type_name<std::string>(), "std::string");
  assert_eq(type_name<std::vector<int>>(), "std::vector<int>");
  assert_eq(type_name<std::vector<const int*>>(), "std::vector<const int*>");
  assert_eq(type_name<std::vector<std::vector<int>>>(),
            "std::vector<std::vector<int>>");

#ifndef _MSC_VER
  assert_eq(type_name<std::tuple<int, char>>(), "std::tuple<int, char>");
  assert_eq(type_name<user_defined_type>(), "user_defined_type");
  assert_eq(type_name<user_defined_enum>(), "user_defined_enum");
  assert_eq(type_name<user_defined_enum_class>(), "user_defined_enum_class");
#endif
}
