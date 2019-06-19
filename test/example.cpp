#include <dbg.h>

int main() {
  std::string message = "hello";
  dbg(message);  // [DEBUG example.cpp:5 (main)] message = "hello"

  std::vector<int> numbers{1, 17, 42};
  dbg(numbers);  // [DEBUG example.cpp:8 (main)] numbers = {1, 17, 42} (size=3)

  return 0;
}
