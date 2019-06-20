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

template <typename ...>
using void_t = void;

template <class Default, class AlwaysVoid,
          template<class...> class Op, class... Args>
struct detector {
  using value_t = std::false_type;
  using type = Default;
};

template <class Default, template<class...> class Op, class... Args>
struct detector<Default, void_t<Op<Args...>>, Op, Args...> {
  using value_t = std::true_type;
  using type = Op<Args...>;
};

} // namespace detail

template <template<class...> class Op, class... Args>
using is_detected = typename detail::detector<nonesuch, void, Op, Args...>::value_t;

template <template<class...> class Op, class... Args>
using detected_t = typename detail::detector<nonesuch, void, Op, Args...>::type;

template <class Default, template<class...> class Op, class... Args>
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
    static constexpr bool value = is_detected<detect_begin_t, T>::value
                                  && is_detected<detect_end_t, T>::value
                                  && is_detected<detect_size_t, T>::value;
};

template <typename T>
typename std::enable_if<!has_begin_end_size<T>::value, bool>::type
prettyPrint(std::ostream& stream, const T& value) {
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
prettyPrint(std::ostream &stream, Container const &value) {
  stream << "{";
  size_t const size = value.size();
  size_t const n = std::min(size_t{5}, size);
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

template <typename ...Args>
class DebugOutput_impl {
 public:
  DebugOutput_impl(const char* filename, int line, const char* function_name, Args && ... args)
      : m_stderr_is_a_tty(isatty(fileno(stderr))),
        m_filename(filename),
        m_line(line),
        m_function_name(function_name),
        m_arguments{args...} {}

  template <typename... Brgs>
  void print(Brgs&&... brgs) {
    size_t i = 0;
    // expander trick to emulate C++17 fold expression
    using expander = int[];
    (void)expander{0, (void(printValue(std::forward<Brgs>(brgs), i++)), 0)...};
  }

  template <typename T>
  void printValue(T&& value, size_t i) const {
    const T& ref = value;
    std::stringstream stream_value;
    const bool print_expression = prettyPrint(stream_value, ref);

    std::cerr << ansi(ANSI_WARNING_COLOR) << "[DEBUG " << m_filename << ":"
              << m_line << " (" << m_function_name << ")] ";
    if (print_expression) {
      std::cerr << ansi(ANSI_RESET) <<  m_arguments[i] << ansi(ANSI_BOLD) << " = ";
    }
    std::cerr << ansi(ANSI_RESET)
              << ansi(ANSI_VALUE_COLOR) << stream_value.str() << ansi(ANSI_RESET) << std::endl;
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

  const std::string m_filename;
  const int m_line;
  const std::string m_function_name;
  const char * m_arguments[sizeof...(Args)];

  static constexpr const char* const ANSI_EMPTY = "";
  static constexpr const char* const ANSI_WARNING_COLOR = "\x1b[33;01m";
  static constexpr const char* const ANSI_VALUE_COLOR = "\x1b[36m";
  static constexpr const char* const ANSI_BOLD = "\x1b[01m";
  static constexpr const char* const ANSI_RESET = "\x1b[0m";
};

template <typename... Args>
DebugOutput_impl<Args...> DebugOutput(const char* filename,
                                      int line,
                                      const char* function_name,
                                      Args&&... args) {
  return DebugOutput_impl<Args...>{filename, line, function_name,
                                   std::forward<Args>(args)...};
}

}  // namespace dbg_macro

#define STRINGIFY(s) _STRINGIFY(s)
#define _STRINGIFY(s) #s

#define FOREACH_1(fn, x) fn(x)
#define FOREACH_2(fn, x, ...) fn(x), FOREACH_1(fn, __VA_ARGS__)
#define FOREACH_3(fn, x, ...) fn(x), FOREACH_2(fn, __VA_ARGS__)
#define FOREACH_4(fn, x, ...) fn(x), FOREACH_3(fn, __VA_ARGS__)
#define FOREACH_5(fn, x, ...) fn(x), FOREACH_4(fn, __VA_ARGS__)
#define FOREACH_6(fn, x, ...) fn(x), FOREACH_5(fn, __VA_ARGS__)
#define FOREACH_7(fn, x, ...) fn(x), FOREACH_6(fn, __VA_ARGS__)

#define FOREACH_N(_1, _2, _3, _4, _5, _6, _7, N, ...) N

// clang-format off
#define FOREACH(fn, ...) \
  FOREACH_N(__VA_ARGS__, \
          FOREACH_7,     \
          FOREACH_6,     \
          FOREACH_5,     \
          FOREACH_4,     \
          FOREACH_3,     \
          FOREACH_2,     \
          FOREACH_1)     \
  (fn, __VA_ARGS__)
// clang-format on

#define dbg(...)                                          \
  dbg_macro::DebugOutput(__FILE__, __LINE__, __func__,    \
                         FOREACH(STRINGIFY, __VA_ARGS__)) \
      .print(__VA_ARGS__)

#endif  // DBG_MACRO_DBG_H
