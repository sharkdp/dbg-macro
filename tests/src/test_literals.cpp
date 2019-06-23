#include <dbg_macro/dbg.h>

int main(int argc, char const* argv[]) {
  dbg(42);
  dbg(3.14);
  dbg(false);
  dbg(12345678987654321);
  dbg(static_cast<void*>(nullptr));
  dbg("string literal");

  return 0;
}
