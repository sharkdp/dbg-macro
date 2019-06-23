#include <dbg_macro/dbg.h>

int factorial(int n) {
  if (dbg(n == 0)) {
    return dbg(1);
  } else {
    return dbg(n * factorial(n - 1));
  }
}

int main() {
  int result = dbg(factorial(4));
  return 0;
}
