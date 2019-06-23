#include <dbg_macro/dbg.h>

int main() {
  const double fahrenheit = 100;
  const double celsius = dbg((fahrenheit - 32) * 5/9);
  const double kelvin = dbg(celsius + 273.15);

  return 0;
}
