#include <cstdint>
#include <string>
#include <vector>
#include <cassert>

#include <dbg.h>

int factorial(int n) {
  if (dbg(n <= 1)) {
    return dbg(1);
  } else {
    return dbg(n * factorial(n - 1));
  }
}

class Test {
  public:
    Test(int m) : member(dbg(m)) {
    }

  private:
    int member;
};

int main() {
  dbg("====== primitive types");

  const int test_int = 42;
  const float test_float = 3.14;
  const bool test_bool = false;
  const uint64_t test_uint64_t = 12345678987654321;
  const int* test_pointer = &test_int;
  const int& test_ref_to_int = test_int;
  const char* test_c_string = "hello";
  const std::string test_string = "hello";

  dbg(test_int);
  dbg(test_float);
  dbg(test_bool);
  dbg(test_uint64_t);
  dbg(test_pointer);
  dbg(test_ref_to_int);
  dbg(test_c_string);
  dbg(test_string);

  dbg("====== r-values");

  dbg(42);
  dbg(3.14);
  dbg(false);
  dbg(12345678987654321);
  dbg((void*)nullptr);
  dbg("string literal");

  std::string message = "hello world";
  dbg(std::move(message));

  dbg("====== expressions inside macros");

  dbg(9 + 33);
  dbg(test_string + " world");

  dbg("====== using dbg(..) inside expressions");

  const auto new_int = dbg(test_int) + dbg(2);
  assert(new_int == 44);

  const auto my_string = dbg("my string");
  assert(my_string == std::string("my string"));

  dbg("====== containers");

  const std::vector<int> dummy_vec_int{1, 2, 3};
  dbg(dummy_vec_int);

  dbg("====== class example");

  Test test(42);

  dbg("====== 'factorial' example");

  factorial(4);
}
