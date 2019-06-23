#include "test.h"

class user_defined_class {
 public:
  void some_method(int x) { dbg(x); }
};

int main(int argc, char const* argv[]) {
  user_defined_class{}.some_method(42);
  return 0;
}
