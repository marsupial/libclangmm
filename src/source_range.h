#ifndef SOURCERANGE_H_
#define SOURCERANGE_H_
#include "source_location.h"
#include <clang-c/Index.h>
#include <string>
#include <utility>

namespace clangmm {
  class SourceRange {
  public:
    SourceRange(const CXSourceRange &cx_range) : cx_range(cx_range) {}
    SourceRange(const SourceLocation &start, const SourceLocation &end);
    SourceLocation get_start() const;
    SourceLocation get_end() const;
    std::pair<clangmm::Offset, clangmm::Offset> get_offsets() const;

    friend std::ostream &operator<<(std::ostream &os, const SourceRange &range) {
      os << range.get_start() << '-' << range.get_end();
      return os;
    }

    CXSourceRange cx_range;
  };
} // namespace clangmm
#endif // SOURCERANGE_H_
