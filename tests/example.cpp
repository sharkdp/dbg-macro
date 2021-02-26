#if DBG_WINDOWS_CLASSIC
#ifndef NOMINMAX
#define NOMINMAX
#endif  // !NOMAXMIN

#include <Windows.h>
#include <string>

struct ConsoleCode {
  ConsoleCode(const char* _code) {
    if (std::string(_code) == "") {
      attribute = Attribute::ANSI_EMPTY;
    } else if (std::string(_code) == "\x1b[02m") {
      attribute = Attribute::ANSI_DEBUG;
    } else if (std::string(_code) == "\x1b[33m") {
      attribute = Attribute::ANSI_WARN;
    } else if (std::string(_code) == "\x1b[36m") {
      attribute = Attribute::ANSI_EXPRESSION;
    } else if (std::string(_code) == "\x1b[01m") {
      attribute = Attribute::ANSI_VALUE;
    } else if (std::string(_code) == "\x1b[32m") {
      attribute = Attribute::ANSI_TYPE;
    } else if (std::string(_code) == "\x1b[0m") {
      attribute = Attribute::ANSI_RESET;
    }
  };

  operator WORD() { return static_cast<WORD>(attribute); };

 private:
  enum struct Attribute : WORD {
    ANSI_EMPTY = 0U,
    ANSI_DEBUG = FOREGROUND_INTENSITY,
    ANSI_WARN = FOREGROUND_RED | FOREGROUND_GREEN,
    ANSI_EXPRESSION = FOREGROUND_GREEN | FOREGROUND_BLUE,
    ANSI_VALUE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    ANSI_TYPE = FOREGROUND_GREEN,
    ANSI_RESET = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
  };

  Attribute attribute = Attribute::ANSI_EMPTY;
};

inline std::ostream& operator<<(std::ostream& stream, ConsoleCode code) {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                          static_cast<WORD>(code));
  return stream;
}

#ifndef DBG_ANSI_TYPE
#define DBG_ANSI_TYPE ConsoleCode
#endif  // !DBG_ANSI_TYPE
#endif  // DBG_WINDOWS_CLASSIC

#include <dbg.h>
#include <vector>

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
  dbg(numbers);  // [example.cpp:21 (main)] numbers = {7, 13, 42} (std::vector<int>)

  dbg("this line is executed");  // [example.cpp:23 (main)] this line is executed

  factorial(4);

  return 0;
}
