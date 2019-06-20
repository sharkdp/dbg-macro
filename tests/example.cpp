#include <vector>
#include <dbg.h>

// Customization point for type information
namespace dbg_macro {
    std::string type_name(type_tag<bool>) {
        return "truth value";
    }
}

// You can use "dbg(..)" in expressions:
int factorial(int n) {
  if (dbg(n <= 1)) {
    return dbg(1);
  } else {
    return dbg(n * factorial(n - 1));
  }
}

int main() {
  std::string message = "hello";
  dbg(message);  // [example.cpp:15 (main)] message = "hello" (std::__cxx11::basic_string<char>)

  const int a = 2;
  const int b = dbg(3 * a) + 1;  // [example.cpp:18 (main)] 3 * a = 6 (int)

  std::vector<int> numbers{b, 13, 42};
  dbg(numbers);  // [example.cpp:21 (main)] numbers = {7, 13, 42} (size: 3) (std::vector<int>)

  dbg("this line is executed");  // [example.cpp:23 (main)] this line is executed

  factorial(4);

  return 0;
}
