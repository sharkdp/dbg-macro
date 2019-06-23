#include <dbg_macro/dbg.h>
#include <array>

int main(int argc, char const* argv[]) {
  const std::array<int, 2> array{{-1, 1}};
  dbg(array);
  return 0;
}
