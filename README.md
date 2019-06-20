# `dbg(…)`

[![Build Status](https://travis-ci.org/sharkdp/dbg-macro.svg?branch=master)](https://travis-ci.org/sharkdp/dbg-macro)

*A macro for `printf`-style debugging fans.*

Debuggers are great. But sometimes you just don't have the time and nerve to set
up everything correctly and just want a quick way to inspect some values at runtime.

This projects provides a single header file ([`dbg.h`](dbg.h)) that defines a `dbg(…)`
macro which can be used in all circumstances where you would typically write
`printf("…", …)` or `std::cout << … << std::endl;` yet another time.

## Examples

``` c++
#include <vector>
#include <dbg.h>

int main() {
  std::string message = "hello";
  dbg(message);  // [DEBUG example.cpp:6 (main)] message = "hello"

  const int a = 2;
  const int b = dbg(3 * a) + 1;  // [DEBUG example.cpp:9 (main)] 3 * a = 6

  std::vector<int> numbers{b, 13, 42};
  dbg(numbers);  // [DEBUG example.cpp:12 (main)] numbers = {7, 13, 42} (size: 3)

  dbg("this line is executed");  // [DEBUG example.cpp:14 (main)] this line is executed

  dbg(sizeof(int));  // [DEBUG example.cpp:16 (main)] sizeof(int) = 4

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

// A call to factorial(4) prints:
// [DEBUG factorial.cpp:9 (factorial)] n <= 1 = false
// [DEBUG factorial.cpp:9 (factorial)] n <= 1 = false
// [DEBUG factorial.cpp:9 (factorial)] n <= 1 = false
// [DEBUG factorial.cpp:9 (factorial)] n <= 1 = true
// [DEBUG factorial.cpp:10 (factorial)] 1 = 1
// [DEBUG factorial.cpp:12 (factorial)] n * factorial(n - 1) = 2
// [DEBUG factorial.cpp:12 (factorial)] n * factorial(n - 1) = 6
// [DEBUG factorial.cpp:12 (factorial)] n * factorial(n - 1) = 24
```

## Features

 * Prints file name, line number, function name and the original expression
 * Easy to read, colorized output
 * Can be used inside normal expressions
 * The `dbg.h` header issues a compiler warning when included
 * Works for containers

## Installation

To make this actually useful, the `dbg.h` header has to be available from all kinds of different
places and in all kinds of environments. The quick & dirty way is to actually copy the header file
to `/usr/include` or to clone the repository and symlink `dbg.h` to `/usr/include/dbg.h`.
``` bash
git clone https://github.com/sharkdp/dbg-macro
sudo ln -s $(readlink -f dbg-macro/dbg.h) /usr/include/dbg.h
```
Ideally, if this turns out to be a good idea, we would ship packages for various distributions so
you don't have to make untracked changes to your filesystem.

## Acknowledgement

This project is inspired by Rusts [`dbg!(…)` macro](https://doc.rust-lang.org/std/macro.dbg.html).
