#include <vector>
#include <dbg.h>

int main() {
  std::string message = "hello";
  dbg(message);  // [DEBUG example.cpp:5 (main)] message = "hello"

  const int a = 2;
  const int b = dbg(3 * a) + 1;  // [DEBUG example.cpp:8 (main)] 3 * a = 6

  std::vector<int> numbers{b, 13, 42};
  dbg(numbers);  // [DEBUG example.cpp:11 (main)] numbers = {7, 13, 42} (size: 3)

  dbg("this line is executed");  // [DEBUG example.cpp:13 (main)] this line is executed

  dbg(sizeof(int));  // [DEBUG example.cpp:15 (main)] sizeof(int) = 4

  return 0;
}
