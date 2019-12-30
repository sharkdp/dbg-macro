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
#include <variant>
#endif

#include <dbg.h>

#include <catch2/catch.hpp>

template <typename T>
std::string pretty_print(T&& value) {
  std::stringstream stream;
  dbg::pretty_print(stream, std::forward<T>(value));
  return stream.str();
}

TEST_CASE("using dbg(..) inside expressions") {
  const int test_int = 42;
  const auto new_int = dbg(test_int) + dbg(2);
  CHECK(new_int == 44);

  const auto my_string = dbg("my string");
  CHECK(my_string == std::string("my string"));
}

TEST_CASE("side effects") {
  int x = 1;
  dbg(++x);
  CHECK(x == 2);
}

TEST_CASE("pretty_print") {
  SECTION("primitive types") {
    CHECK(pretty_print(3) == "3");
    CHECK(pretty_print(3.14) == "3.14");
    CHECK(pretty_print(true) == "true");
    CHECK(pretty_print(static_cast<void*>(nullptr)) == "nullptr");
    CHECK(pretty_print('X') == "'X'");
    CHECK(pretty_print('\x7F') == "'\\x7F'");
    const char* test_c_string = "hello";
    CHECK(pretty_print(test_c_string) == "\"hello\"");
  }

  SECTION("string literals") {
    CHECK(pretty_print("string literal") == "string literal");
  }

  SECTION("containers") {
    CHECK(pretty_print(std::vector<int>{}) == "{}");
    CHECK(pretty_print(std::vector<int>{1, 2, 3}) == "{1, 2, 3}");
    CHECK(pretty_print(std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
                                        13, 14}) ==
          "{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, ... size:14}");
  }

  SECTION("std::string") {
    std::string x = "foo";
    std::string y = "bar";
    CHECK(pretty_print(x) == "\"foo\"");
    CHECK(pretty_print(std::make_pair(x, y)) == "{\"foo\", \"bar\"}");
  }

  SECTION("nested containers") {
    std::vector<std::vector<int>> vec_of_vec_of_ints{{1, 2}, {3, 4, 5}};

    CHECK(pretty_print(vec_of_vec_of_ints) == "{{1, 2}, {3, 4, 5}}");
  }

  SECTION("std::tuple") {
    CHECK(pretty_print(std::tuple<>{}) == "{}");
    CHECK(pretty_print(std::tuple<int, bool>{42, false}) == "{42, false}");
  }

  SECTION("std::pair") {
    CHECK(pretty_print(std::pair<int, bool>{13, true})  == "{13, true}");

    std::pair<std::pair<bool, int>, bool> pair_of_pairs{{false, 17}, true};
    CHECK(pretty_print(pair_of_pairs)  == "{{false, 17}, true}");
  }

  SECTION("std::unique_ptr") {
    auto dummy_unique_ptr = std::unique_ptr<int>{new int{42}};
    const void* unique_ptr_address = static_cast<void*>(dummy_unique_ptr.get());
    std::stringstream s_unique_ptr_expected;
    s_unique_ptr_expected << unique_ptr_address;
    CHECK(s_unique_ptr_expected.str() == pretty_print(dummy_unique_ptr));
  }

  SECTION("std::shared_ptr") {
    auto dummy_shared_ptr = std::shared_ptr<int>{new int{42}};
    auto dummy_shared_ptr2 = dummy_shared_ptr;
    const void* shared_ptr_address = static_cast<void*>(dummy_shared_ptr.get());
    std::stringstream s_shared_ptr_expected;
    s_shared_ptr_expected << shared_ptr_address << " (use_count = 2)";
    CHECK(s_shared_ptr_expected.str() == pretty_print(dummy_shared_ptr));
  }

#if DBG_MACRO_CXX_STANDARD >= 17
  SECTION("std::optional") {
    CHECK(pretty_print(std::make_optional<bool>(false)) == "{false}");
    std::optional<int> empty_optional;
    CHECK(pretty_print(empty_optional) == "nullopt");
  }

  SECTION("std::variant") {
    std::variant<int, std::string> dummy_variant = "test";
    CHECK(pretty_print(dummy_variant) == "{\"test\"}");
    dummy_variant = 42;
    CHECK(pretty_print(dummy_variant) == "{42}");
  }
#endif
}

struct user_defined_type {
  int x;
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

TEST_CASE("pretty_print user defined types") {
  SECTION("classes") {
    user_defined_type x{42};
    CHECK(pretty_print(x) == "user_defined_type{42}");
  }

  SECTION("enums") {
    user_defined_enum x = UDE_VALUE42;
    CHECK(pretty_print(x) == "42");
  }

  SECTION("enum classes") {
    user_defined_enum_class x = user_defined_enum_class::VALUE42;
    CHECK(pretty_print(x) == "42");
  }

  SECTION("containers") {
    user_defined_container<int, 3> xs{{1, 2, 3}};
    CHECK(pretty_print(xs) == "{1, 2, 3}");
  }
}

TEST_CASE("type_name") {
  using namespace dbg;

  SECTION("primitive types") {
    CHECK(type_name<void>() == "void");
    CHECK(type_name<int>() == "int");
    CHECK(type_name<char>() == "char");
    CHECK(type_name<short>() == "short");
    CHECK(type_name<long>() == "long");
    CHECK(type_name<unsigned short>() == "unsigned short");
    CHECK(type_name<unsigned long>() == "unsigned long");
    CHECK(type_name<float>() == "float");
  }

  SECTION("const and volatile") {
    CHECK(type_name<const int>() == "const int");
    CHECK(type_name<volatile int>() == "volatile int");
  }

  SECTION("references") {
    CHECK(type_name<int&>() == "int&");
    CHECK(type_name<const int&>() == "const int&");
  }

  SECTION("pointers") {
    CHECK(type_name<int*>() == "int*");
    CHECK(type_name<int** const*>() == "int** const*");
    CHECK(type_name<const int*>() == "const int*");
    CHECK(type_name<int* const>() == "int* const");
    CHECK(type_name<const int* const>() == "const int* const");
  }

  SECTION("common STL types") {
    CHECK(type_name<std::string>() == "std::string");
    CHECK(type_name<std::vector<int>>() == "std::vector<int>");
    CHECK(type_name<std::vector<const int*>>() == "std::vector<const int*>");
    CHECK(type_name<std::vector<std::vector<int>>>() ==
          "std::vector<std::vector<int>>");
  }

#ifndef _MSC_VER
  SECTION("std::tuple") {
    CHECK(type_name<std::tuple<>>() == "std::tuple<>");
    CHECK(type_name<std::tuple<int, char>>() == "std::tuple<int, char>");
    CHECK(type_name<std::tuple<std::string, char>>() == "std::tuple<std::string, char>");
  }

  SECTION("user-defined types") {
    CHECK(type_name<user_defined_type>() == "user_defined_type");
    CHECK(type_name<user_defined_enum>() == "user_defined_enum");
    CHECK(type_name<user_defined_enum_class>() == "user_defined_enum_class");
  }
#endif
}

TEST_CASE("dbg::hex and dbg::oct") {
  uint8_t hex_1 = 0xA7;
  CHECK(pretty_print(dbg::hex(hex_1)) == "0xA7");

  uint16_t hex_2 = 0xAB12;
  CHECK(pretty_print(dbg::hex(hex_2)) == "0xAB12");

  uint64_t hex_3 = 0x1234567890ABCDEF;
  CHECK(pretty_print(dbg::hex(hex_3)) == "0x1234567890ABCDEF");

  int8_t hex_4 = -0x80;
  CHECK(pretty_print(dbg::hex(hex_4)) == "-0x80");

  int8_t hex_5 = 0x7F;
  CHECK(pretty_print(dbg::hex(hex_5)) == "0x7F");

  int64_t hex_6 = std::numeric_limits<int64_t>::lowest();
  CHECK(pretty_print(dbg::hex(hex_6)) == "-0x8000000000000000");

  uint32_t oct_1 = 01234567;
  CHECK(pretty_print(dbg::oct(oct_1)) == "0o1234567");

  CHECK(dbg(dbg::hex(hex_2)) == hex_2);
  CHECK(dbg(dbg::hex(hex_2)) + 1 == hex_2 + 1);
}
