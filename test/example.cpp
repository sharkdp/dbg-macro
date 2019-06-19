#include <dbg.h>

int main() {
  std::string message = "hello";
  dbg(message);  // [DEBUG example.cpp:5 (main)] message = "hello"

  std::vector<int> numbers{1, 17, 42};
  dbg(numbers);  // [DEBUG example.cpp:8 (main)] numbers = {1, 17, 42} (size=3)

  dbg("this line is executed");  // [DEBUG example.cpp:10 (main)] this line is executed

  dbg(sizeof(int));  // [DEBUG example.cpp:12 (main)] sizeof(int) = 4

  return 0;
}
