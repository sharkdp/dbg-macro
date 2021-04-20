#include <dbg.h>
#include <vector>

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
  dbg(message);  // [example.cpp:15 (main)] message = "hello" (std::string)

  const int a = 2;
  const int b = dbg(3 * a) + 1;  // [example.cpp:18 (main)] 3 * a = 6 (int)

  std::vector<int> numbers{b, 13, 42};
  dbg(numbers);  // [example.cpp:21 (main)] numbers = {7, 13, 42} (std::vector<int>)

  dbg("this line is executed");  // [example.cpp:23 (main)] this line is executed

  factorial(4);

  return 0;
}
