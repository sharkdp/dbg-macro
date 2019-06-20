# `dbg(…)`

[![Build Status](https://travis-ci.org/sharkdp/dbg-macro.svg?branch=master)](https://travis-ci.org/sharkdp/dbg-macro)

*A macro for `printf`-style debugging fans.*

Debuggers are great. But sometimes you just don't have the time and nerve to set
up everything correctly and just want a quick way to inspect some values at runtime.

This projects provides a single header file ([`dbg.h`](dbg.h)) with a `dbg(…)`
macro that can be used in all circumstances where you would typically write
`printf("…", …)` or `std::cout << … << std::endl;`, but with a few extras.

## Examples

``` c++
#include <vector>
#include <dbg.h>

// You can use "dbg(..)" in expressions:
int factorial(int n) {
  if (dbg(n <= 1)) {
    return dbg(1);
  } else {
    return dbg(n * factorial(n - 1));
  }
}

int main() {
  std::string message = "hello";
  dbg(message);  // [example.cpp:15 (main)] message = "hello" (std::__cxx11::basic_string<char>)

  const int a = 2;
  const int b = dbg(3 * a) + 1;  // [example.cpp:18 (main)] 3 * a = 6 (int)

  std::vector<int> numbers{b, 13, 42};
  dbg(numbers);  // [example.cpp:21 (main)] numbers = {7, 13, 42} (size: 3) (std::vector<int>)

  dbg("this line is executed");  // [example.cpp:23 (main)] this line is executed

  factorial(4);

  return 0;
}

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
