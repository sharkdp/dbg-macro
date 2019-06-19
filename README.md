# `dbg(…)`

*A macro for `printf`-style debugging fans.*

Debuggers are great. But sometimes you just don't have the time and nerve to set
up everything correctly and just want a quick way to inspect some values at runtime.

This projects provides a single header file ([`dbg.h`](dbg.h)) that defines a `dbg(…)`
macro which can be used in all circumstances where you would typically write
`printf("…", …)` or `std::cout << … << std::endl;` for yet another time.

## Examples

``` c++
#include <dbg.h>

int main() {
  std::string message = "hello";
  dbg(message);  // [DEBUG example.cpp:5 (main)] message = "hello"

  std::vector<int> numbers{1, 17, 42};
  dbg(numbers);  // [DEBUG example.cpp:8 (main)] numbers = {1, 17, 42} (size=3)

  return 0;
}
```

```c++
// Use it inside expressions:
int factorial(int n) {
   if (dbg(n <= 1)) {
       return dbg(1);
   } else {
       return dbg(n * factorial(n - 1));
   }
}
```

## Features

 * Prints file name, line number, function name and the original expression
 * Easy to read, colorized output
 * Can be used inside normal expressions
 * The `dbg.h` header issues a compiler warning when included
 * Works for containers

## Acknowledgement

This project is inspired by Rusts [`dbg!(…)` macro](https://doc.rust-lang.org/std/macro.dbg.html).
