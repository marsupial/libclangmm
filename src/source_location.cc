#include "source_location.h"
#include "utility.h"

// // // // // // // //
//  SourceLocation   //
// // // // // // // //
clangmm::SourceLocation::SourceLocation(CXTranslationUnit &tu, const std::string &filepath, unsigned offset) {
  CXFile file = clang_getFile(tu, filepath.c_str());
  cx_location = clang_getLocationForOffset(tu, file, offset);
}

clangmm::SourceLocation::SourceLocation(CXTranslationUnit &tu, const std::string &filepath, unsigned line, unsigned column) {
  CXFile file = clang_getFile(tu, filepath.c_str());
  cx_location = clang_getLocation(tu, file, line, column);
}

std::string clangmm::SourceLocation::get_path() const {
  std::string path;
  get_data(&path, nullptr, nullptr, nullptr);
  return path;
}
clangmm::Offset clangmm::SourceLocation::get_offset() const {
  unsigned line, index;
  get_data(nullptr, &line, &index, nullptr);
  return {line, index};
}

void clangmm::SourceLocation::get_data(std::string *path, unsigned *line, unsigned *column, unsigned *offset) const {
  if(path == nullptr)
    clang_getExpansionLocation(cx_location, NULL, line, column, offset);
  else {
    CXFile file;
    clang_getExpansionLocation(cx_location, &file, line, column, offset);
    if(file != NULL) {
      *path = to_string(clang_getFileName(file));
    }
  }
}
