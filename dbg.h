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

#if __cplusplus >= 201703L
#include <optional>
#endif

namespace dbg_macro {

// Implementation of 'type_name<T>()'

template <typename T>
const char* type_name_impl() {
#if defined(__clang__)
  return __PRETTY_FUNCTION__;
#elif defined(__GNUC__) && !defined(__clang__)
  return __PRETTY_FUNCTION__;
#elif defined(_MSC_VER)
  return __FUNCSIG__;
#else
#error "No support for this compiler."
#endif
}

template <typename T>
std::string type_name() {
#if defined(__clang__)
  size_t prefixlen =
      sizeof("const char *dbg_macro::type_name_impl() [T = ") - 1;
  size_t suffixlen = sizeof("]") - 1;
#elif defined(__GNUC__) && !defined(__clang__)
  size_t prefixlen =
      sizeof("const char* dbg_macro::type_name_impl() [with T = ") - 1;
  size_t suffixlen = sizeof("]") - 1;
#elif defined(_MSC_VER)
  size_t prefixlen =
      sizeof("const char *__cdecl dbg_macro::type_name_impl<") - 1;
  size_t suffixlen = sizeof(">(void)") - 1;
#else
#error "No support for this compiler."
#endif
  std::string type = type_name_impl<T>();
  return type.substr(prefixlen, type.size() - prefixlen - suffixlen);
}

// Implementation of 'is_detected' to specialize for container-like types

namespace detail_detector {

struct nonesuch {
  nonesuch() = delete;
  ~nonesuch() = delete;
  nonesuch(nonesuch const&) = delete;
  void operator=(nonesuch const&) = delete;
};

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

}  // namespace detail_detector

template <template <class...> class Op, class... Args>
using is_detected = typename detail_detector::
    detector<detail_detector::nonesuch, void, Op, Args...>::value_t;

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

// Specializations of "prettyPrint"

template <typename T>
typename std::enable_if<!has_begin_end_size<T>::value, bool>::type prettyPrint(
    std::ostream& stream,
    const T& value) {
  stream << value;
  return true;
}

template <>
bool prettyPrint(std::ostream& stream, const bool& value) {
  stream << std::boolalpha << value;
  return true;
}

template <>
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

template <>
bool prettyPrint(std::ostream& stream, const char* const& value) {
  stream << '"' << value << '"';
  return true;
}

#if __cplusplus >= 201703L

template <typename T>
bool prettyPrint(std::ostream& stream, const std::optional<T>& value) {
  if (value) {
    stream << '{' << *value << '}';
  } else {
    stream << "nullopt";
  }

  return true;
}

#endif  // __cplusplus >= 201703L

template <typename Container>
typename std::enable_if<has_begin_end_size<Container>::value, bool>::type
prettyPrint(std::ostream& stream, Container const& value) {
  stream << "{";
  const size_t size = value.size();
  const size_t n = std::min(size_t{5}, size);
  size_t i = 0;
  for (auto it = begin(value); it != end(value) && i < n; ++it, ++i) {
    prettyPrint(stream, *it);
    if (i != n - 1) {
      stream << ", ";
    }
  }

  if (size > n) {
    stream << ", ...";
    stream << " size:" << size;
  }

  stream << "}";
  return true;
}

template <>
bool prettyPrint(std::ostream& stream, const std::string& value) {
  stream << '"' << value << '"';
  return true;
}

class DebugOutput {
 public:
  DebugOutput(const char* filepath,
              int line,
              const char* function_name,
              const char* expression)
      : m_stderr_is_a_tty(isatty(fileno(stderr))),
        m_filepath(filepath),
        m_line(line),
        m_function_name(function_name),
        m_expression(expression) {
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
    const bool print_expr_and_type = prettyPrint(stream_value, ref);

    std::cerr << ansi(ANSI_DEBUG) << "[" << m_filepath << ":" << m_line << " ("
              << m_function_name << ")] " << ansi(ANSI_RESET);
    if (print_expr_and_type) {
      std::cerr << ansi(ANSI_EXPRESSION) << m_expression << ansi(ANSI_RESET)
                << " = ";
    }
    std::cerr << ansi(ANSI_VALUE) << stream_value.str() << ansi(ANSI_RESET);
    if (print_expr_and_type) {
      using ValueType = typename std::remove_cv<
          typename std::remove_reference<T>::type>::type;
      std::cerr << " (" << ansi(ANSI_TYPE) << type_name<ValueType>()
                << ansi(ANSI_RESET) << ")";
    }
    std::cerr << std::endl;

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
  const std::string m_expression;

  static constexpr int MAX_PATH_LENGTH = 20;

  static constexpr const char* const ANSI_EMPTY = "";
  static constexpr const char* const ANSI_DEBUG = "\x1b[02m";
  static constexpr const char* const ANSI_EXPRESSION = "\x1b[36m";
  static constexpr const char* const ANSI_VALUE = "\x1b[01m";
  static constexpr const char* const ANSI_TYPE = "\x1b[32m";
  static constexpr const char* const ANSI_RESET = "\x1b[0m";
};

}  // namespace dbg_macro

// We use a variadic macro to support commas inside expressions (e.g.
// initializer lists):
#define dbg(...)                                                     \
  dbg_macro::DebugOutput(__FILE__, __LINE__, __func__, #__VA_ARGS__) \
      .print((__VA_ARGS__))

#endif  // DBG_MACRO_DBG_H
