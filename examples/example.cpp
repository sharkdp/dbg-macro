#include <vector>
#include <dbg.h>

int main() {
  std::string message = "hello";
  dbg(message);  // [DEBUG example.cpp:6 (main)] message = "hello"

  const int a = 2;
  const int b = dbg(3 * a) + 1;  // [DEBUG example.cpp:9 (main)] 3 * a = 6

  std::vector<int> numbers{b, 13, 42};
  dbg(numbers);  // [DEBUG example.cpp:12 (main)] numbers = {7, 13, 42} (size: 3)

  dbg("this line is executed");  // [DEBUG example.cpp:14 (main)] this line is executed

  dbg(sizeof(int));  // [DEBUG example.cpp:16 (main)] sizeof(int) = 4

  return 0;
}
