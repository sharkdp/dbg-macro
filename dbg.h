/*****************************************************************************

                                dbg(...) macro

License (MIT):

  Copyright (c) 2019 David Peter <mail@david-peter.de>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to
  deal in the Software without restriction, including without limitation the
  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
  sell copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

*****************************************************************************/

#ifndef DBG_MACRO_DBG_H
#define DBG_MACRO_DBG_H

#include <ios>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
void PrettyPrint(std::ostream& stream, T&& value) {
  stream << value;
}

template <>
void PrettyPrint(std::ostream& stream, bool&& value) {
  stream << std::boolalpha << value;
}

template <>
void PrettyPrint(std::ostream& stream, const bool& value) {
  stream << std::boolalpha << value;
}

template <typename S>
void PrettyPrint(std::ostream& stream, const std::vector<S>& value) {
  const auto n = std::min(5, static_cast<int>(value.size()));
  for (int i = 0; i < n; ++i) {
    stream << value[i];
    if (i != n - 1) {
      stream << ", ";
    }
  }
}

class DebugOutput {
 public:
  DebugOutput(const char* filename, int line, const char* argument)
      : m_filename(filename), m_line(line), m_argument(argument) {}

  template <typename T>
  void print(T&& value) {
    std::cerr << ANSI_WARNING_COLOR << "[DEBUG " << m_filename << ":" << m_line
              << "] " << ANSI_RESET << m_argument << ANSI_BOLD << " = {"
              << ANSI_RESET << ANSI_VALUE_COLOR;
    PrettyPrint(std::cerr, std::forward<T>(value));
    std::cerr << ANSI_RESET << ANSI_BOLD << "}" << ANSI_RESET << std::endl;
  }

 private:
  const std::string m_filename;
  const int m_line;
  const char* m_argument;

  static constexpr const char* const ANSI_WARNING_COLOR = "\x1b[33;01m";
  static constexpr const char* const ANSI_VALUE_COLOR = "\x1b[36m";
  static constexpr const char* const ANSI_BOLD = "\x1b[01m";
  static constexpr const char* const ANSI_RESET = "\x1b[0m";
};

#define dbg(VALUE) DebugOutput(__FILE__, __LINE__, #VALUE).print((VALUE));

#endif  // DBG_MACRO_DBG_H
