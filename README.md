# `dbg(…)`

[![Build Status](https://travis-ci.org/sharkdp/dbg-macro.svg?branch=master)](https://travis-ci.org/sharkdp/dbg-macro) [![Build status](https://ci.appveyor.com/api/projects/status/vmo9rw4te2wifkul?svg=true)](https://ci.appveyor.com/project/sharkdp/dbg-macro) [![Try it online](https://img.shields.io/badge/try-online-f34b7d.svg)](https://repl.it/@sharkdp/dbg-macro-demo) [![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](dbg.h)

*A macro for `printf`-style debugging fans.*

Debuggers are great. But sometimes you just don't have the time and nerve to set
up everything correctly and just want a quick way to inspect some values at runtime.

This projects provides a [single header file](dbg.h) with a `dbg(…)`
macro that can be used in all circumstances where you would typically write
`printf("…", …)` or `std::cout << …`, but with a few extras.

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
  dbg(message);  // [example.cpp:15 (main)] message = "hello" (std::string)

  const int a = 2;
  const int b = dbg(3 * a) + 1;  // [example.cpp:18 (main)] 3 * a = 6 (int)

  std::vector<int> numbers{b, 13, 42};
  dbg(numbers);  // [example.cpp:21 (main)] numbers = {7, 13, 42} (size: 3) (std::vector<int>)

  dbg("this line is executed");  // [example.cpp:23 (main)] this line is executed

  factorial(4);

  return 0;
}
```

The code above produces this output ([try it yourself](https://repl.it/@sharkdp/dbg-macro-demo)):

![dbg(…) macro output](https://i.imgur.com/NHEYk9A.png)

## Features

 * Easy to read, colorized output (colors auto-disable when the output is not an interactive terminal)
 * Prints file name, line number, function name and the original expression
 * Adds type information for the printed-out value
 * Specialized pretty-printers for containers, pointers, string literals, enums, `std::optional`, etc.
 * Can be used inside expressions
 * The `dbg.h` header issues a compiler warning when included (so you don't forget to remove).
 * C++11 compatible

## Installation

To make this actually usable, the `dbg.h` header should to be available from all kinds of different
places and in all kinds of environments. The quick & dirty way is to actually copy the header file
to `/usr/include` or to clone the repository and symlink `dbg.h` to `/usr/include/dbg.h`.
``` bash
git clone https://github.com/sharkdp/dbg-macro
sudo ln -s $(readlink -f dbg-macro/dbg.h) /usr/include/dbg.h
```
Ideally, if this turns out to be a good idea, we would ship packages for various distributions so
you don't have to make untracked changes to your filesystem.

## Configuration

* Set the `DBG_MACRO_DISABLE` flag to disable the `dbg(…)` macro (i.e. to make it a no-op).
* Set the `DBG_MACRO_NO_WARNING` flag to disable the *"'dbg.h' header is included in your code base"* warnings.

## Customization

If you want `dbg(…)` to work for your custom datatype, you can simply overload `operator<<` for
`std::ostream&`:
```c++
std::ostream& operator<<(std::ostream& out, const user_defined_type& v) {
  out << "…";
  return out;
}
```

If you want to modify the type name that is printed by `dbg(…)`, you can add a custom
`get_type_name` overload:
```c++
// Customization point for type information
namespace dbg {
    std::string get_type_name(type_tag<bool>) {
        return "truth value";
    }
}
```

## Acknowledgement

This project is inspired by Rusts [`dbg!(…)` macro](https://doc.rust-lang.org/std/macro.dbg.html).
