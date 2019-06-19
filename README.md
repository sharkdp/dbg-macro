# `dbg(…)`

*A macro for `printf`-style debugging fans.*

Debuggers are great. But sometimes you just don't have the time and nerve to set
up everything correctly and just want a quick way to inspect some values at runtime.

This projects provides a single header file ([`dbg.h`](dbg.h)) that defines a `dbg(…)`
macro which can be used in all circumstances where you would typically write
`printf("…", …)` or `std::cout << … << std::endl;` for the *n*th-time.

## Features:

 * Can be used inside expressions:
   ``` c++
   int factorial(int n) {
       if (dbg(n <= 1)) {
           return dbg(1);
       } else {
           return dbg(n * factorial(n - 1));
       }
   }
   ```
 * Prints file name, line number and the original expression
 * Easy to read, colorized output
 * The `dbg.h` header issues a compiler warning when included
 * Works for containers

## Acknowledgement

This project is inspired by Rusts [`dbg!(…)` macro](https://doc.rust-lang.org/std/macro.dbg.html).
