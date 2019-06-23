#include <dbg_macro/dbg.h>

int gcd(int a, int b) {
  if (dbg(b == 0)) {
    return dbg(a);
  }
  return dbg(gcd(b, a % b));
}

int main(int argc, char const* argv[]) {
  int result = dbg(gcd(16, 12));
  return 0;
}
