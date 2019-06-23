#include <dbg_macro/dbg.h>
#include <list>

int main(int argc, char const* argv[]) {
  const std::list<int> list{-4, -3, -2, -1, 1, 2, 3, 4};
  dbg(list);
  return 0;
}
