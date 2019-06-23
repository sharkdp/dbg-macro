#include <dbg_macro/dbg.h>

int main() {
  [](int x) {
    dbg("called from within a lambda!");
    return x;
  }(42);
}