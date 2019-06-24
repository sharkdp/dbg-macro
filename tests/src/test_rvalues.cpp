#include "test.h"

int main(int argc, char const* argv[]) {
  std::string message = "hello world";
  dbg(std::move(message));

  return 0;
}
