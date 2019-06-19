# `dbg(…)`

*A macro for `printf`-style debugging fans.*

Debuggers are great. But sometimes you just don't have the time and nerve to set
up everything correctly and just want a quick way to inspect some values at runtime.

This projects provides a single header file ([`dbg.h`](dbg.h)) that defines a `dbg(…)`
macro which can be used in all circumstances where you would typically write
`printf("…", …)` or `std::cout << … << std::endl;` for the nth-time.
