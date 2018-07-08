#ifndef UTILITY_H_
#define UTILITY_H_
#include <clang-c/Index.h>
#include <string>

namespace clangmm {
  std::string to_string(CXString cx_string);

  class String {
  public:
    String(const CXString &cx_string);
    ~String();
    CXString cx_string;
    const char *c_str;
  };

  void remove_include_guard(std::string &buffer);
} // namespace clangmm

#endif // UTILITY_H_
