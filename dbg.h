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

#pragma message("WARNING: the 'dbg.h' header is included in your code base")

#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

#include <unistd.h>

namespace dbg_macro {

// -- begin is_detected

struct nonesuch {
  nonesuch() = delete;
  ~nonesuch() = delete;
  nonesuch(nonesuch const&) = delete;
  void operator=(nonesuch const&) = delete;
};

namespace detail {

template <typename...>
using void_t = void;

template <class Default,
          class AlwaysVoid,
          template <class...>
          class Op,
          class... Args>
struct detector {
  using value_t = std::false_type;
  using type = Default;
};

template <class Default, template <class...> class Op, class... Args>
struct detector<Default, void_t<Op<Args...>>, Op, Args...> {
  using value_t = std::true_type;
  using type = Op<Args...>;
};

}  // namespace detail

template <template <class...> class Op, class... Args>
using is_detected =
    typename detail::detector<nonesuch, void, Op, Args...>::value_t;

template <template <class...> class Op, class... Args>
using detected_t = typename detail::detector<nonesuch, void, Op, Args...>::type;

template <class Default, template <class...> class Op, class... Args>
using detected_or = detail::detector<Default, void, Op, Args...>;

// -- end is_detected

template <typename T>
using detect_begin_t = decltype(begin(std::declval<T>()));

template <typename T>
using detect_end_t = decltype(end(std::declval<T>()));

template <typename T>
using detect_size_t = decltype(std::declval<T>().size());

template <typename T>
struct has_begin_end_size {
  static constexpr bool value = is_detected<detect_begin_t, T>::value &&
                                is_detected<detect_end_t, T>::value &&
                                is_detected<detect_size_t, T>::value;
};

template <typename T>
typename std::enable_if<!has_begin_end_size<T>::value, bool>::type prettyPrint(
    std::ostream& stream,
    const T& value) {
  stream << value;
  return true;
}

bool prettyPrint(std::ostream& stream, const bool& value) {
  stream << std::boolalpha << value;
  return true;
}

bool prettyPrint(std::ostream& stream, const char& value) {
  stream << "'" << value << "'";
  return true;
}

template <typename P>
bool prettyPrint(std::ostream& stream, P* const& value) {
  if (value == nullptr) {
    stream << "nullptr";
  } else {
    stream << value;
  }
  return true;
}

template <int N>
bool prettyPrint(std::ostream& stream, const char (&value)[N]) {
  stream << value;
  return false;
}

bool prettyPrint(std::ostream& stream, const char* const& value) {
  stream << '"' << value << '"';
  return true;
}

bool prettyPrint(std::ostream& stream, const std::string& value) {
  stream << '"' << value << '"';
  return true;
}

template <typename Container>
typename std::enable_if<has_begin_end_size<Container>::value, bool>::type
prettyPrint(std::ostream& stream, Container const& value) {
  stream << "{";
  const size_t size = value.size();
  const size_t n = std::min(size_t{5}, size);
  size_t i = 0;
  for (auto it = begin(value); it != end(value) && i < n; ++it, ++i) {
    stream << *it;
    if (i != n - 1) {
      stream << ", ";
    }
  }

  if (size > n) {
    stream << ", ...";
  }

  stream << "}";
  stream << " (size: " << size << ")";
  return true;
}

class DebugOutput {
 public:
  DebugOutput(const char* filepath,
              int line,
              const char* function_name,
              const char* argument)
      : m_stderr_is_a_tty(isatty(fileno(stderr))),
        m_filepath(filepath),
        m_line(line),
        m_function_name(function_name),
        m_argument(argument) {
    const int path_length = m_filepath.length();
    if (path_length > MAX_PATH_LENGTH) {
      m_filepath = ".." + m_filepath.substr(path_length - MAX_PATH_LENGTH,
                                            MAX_PATH_LENGTH);
    }
  }

  template <typename T>
  T&& print(T&& value) const {
    const T& ref = value;
    std::stringstream stream_value;
    const bool print_expression = prettyPrint(stream_value, ref);

    std::cerr << ansi(ANSI_WARNING_COLOR) << "[DEBUG " << m_filepath << ":"
              << m_line << " (" << m_function_name << ")] ";
    if (print_expression) {
      std::cerr << ansi(ANSI_RESET) << m_argument << ansi(ANSI_BOLD) << " = ";
    }
    std::cerr << ansi(ANSI_RESET) << ansi(ANSI_VALUE_COLOR)
              << stream_value.str() << ansi(ANSI_RESET) << std::endl;

    return std::forward<T>(value);
  }

 private:
  const char* ansi(const char* code) const {
    if (m_stderr_is_a_tty) {
      return code;
    } else {
      return ANSI_EMPTY;
    }
  }

  const bool m_stderr_is_a_tty;

  std::string m_filepath;
  const int m_line;
  const std::string m_function_name;
  const std::string m_argument;

  static constexpr int MAX_PATH_LENGTH = 20;

  static constexpr const char* const ANSI_EMPTY = "";
  static constexpr const char* const ANSI_WARNING_COLOR = "\x1b[33;01m";
  static constexpr const char* const ANSI_VALUE_COLOR = "\x1b[36m";
  static constexpr const char* const ANSI_BOLD = "\x1b[01m";
  static constexpr const char* const ANSI_RESET = "\x1b[0m";
};

}  // namespace dbg_macro

// We use a variadic macro to support commas inside expressions (e.g.
// initializer lists):
#define dbg(...)                                                     \
  dbg_macro::DebugOutput(__FILE__, __LINE__, __func__, #__VA_ARGS__) \
      .print((__VA_ARGS__))

#endif  // DBG_MACRO_DBG_H
