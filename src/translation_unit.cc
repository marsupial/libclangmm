#include "translation_unit.h"
#include "source_location.h"
#include "tokens.h"
#include "utility.h"
#include <fstream>
#include <sstream>

#include <iostream>  //TODO: remove
using namespace std; //TODO: remove

clangmm::TranslationUnit::TranslationUnit(Index &index, const std::string &file_path,
                                          const std::vector<std::string> &command_line_args,
                                          const std::string &buffer, int flags) {
  std::vector<const char *> args;
  for(auto &a : command_line_args) {
    args.push_back(a.c_str());
  }

  CXUnsavedFile files[1];
  files[0].Filename = file_path.c_str();
  files[0].Contents = buffer.c_str();
  files[0].Length = buffer.size();

  cx_tu = clang_parseTranslationUnit(index.cx_index, file_path.c_str(), args.data(),
                                     args.size(), files, 1, flags);
}

clangmm::TranslationUnit::TranslationUnit(Index &index, const std::string &file_path,
                                          const std::vector<std::string> &command_line_args,
                                          int flags) {
  std::vector<const char *> args;
  for(auto &a : command_line_args) {
    args.push_back(a.c_str());
  }

  cx_tu = clang_parseTranslationUnit(index.cx_index, file_path.c_str(), args.data(),
                                     args.size(), NULL, 0, flags);
}

clangmm::TranslationUnit::~TranslationUnit() {
  clang_disposeTranslationUnit(cx_tu);
}

void clangmm::TranslationUnit::parse(Index &index, const std::string &file_path,
                                     const std::vector<std::string> &command_line_args,
                                     const std::map<std::string, std::string> &buffers, int flags) {
  std::vector<CXUnsavedFile> files;
  for(auto &buffer : buffers) {
    CXUnsavedFile file;
    file.Filename = buffer.first.c_str();
    file.Contents = buffer.second.c_str();
    file.Length = buffer.second.size();
    files.push_back(file);
  }
  std::vector<const char *> args;
  for(auto &a : command_line_args) {
    args.push_back(a.c_str());
  }
  cx_tu = clang_parseTranslationUnit(index.cx_index, file_path.c_str(), args.data(),
                                     args.size(), files.data(), files.size(), flags);
}

int clangmm::TranslationUnit::reparse(const std::string &buffer, int flags) {
  CXUnsavedFile files[1];

  auto file_path = to_string(clang_getTranslationUnitSpelling(cx_tu));

  files[0].Filename = file_path.c_str();
  files[0].Contents = buffer.c_str();
  files[0].Length = buffer.size();

  return clang_reparseTranslationUnit(cx_tu, 1, files, flags);
}

int clangmm::TranslationUnit::DefaultFlags() {
  int flags = CXTranslationUnit_CacheCompletionResults | CXTranslationUnit_PrecompiledPreamble | CXTranslationUnit_Incomplete | CXTranslationUnit_IncludeBriefCommentsInCodeCompletion;
#if CINDEX_VERSION_MAJOR > 0 || (CINDEX_VERSION_MAJOR == 0 && CINDEX_VERSION_MINOR >= 35)
  flags |= CXTranslationUnit_KeepGoing;
#endif
  return flags;
}

clangmm::CodeCompleteResults clangmm::TranslationUnit::get_code_completions(const std::string &buffer,
                                                                            unsigned line_number, unsigned column) {
  CodeCompleteResults results(cx_tu, buffer, line_number, column);
  return results;
}

std::vector<clangmm::Diagnostic> clangmm::TranslationUnit::get_diagnostics() {
  std::vector<Diagnostic> diagnostics;
  for(unsigned c = 0; c < clang_getNumDiagnostics(cx_tu); c++) {
    CXDiagnostic clang_diagnostic = clang_getDiagnostic(cx_tu, c);
    diagnostics.emplace_back(Diagnostic(cx_tu, clang_diagnostic));
    clang_disposeDiagnostic(clang_diagnostic);
  }
  return diagnostics;
}

std::unique_ptr<clangmm::Tokens> clangmm::TranslationUnit::get_tokens() {
  SourceRange range(clang_getCursorExtent(clang_getTranslationUnitCursor(cx_tu)));
  return std::unique_ptr<Tokens>(new Tokens(cx_tu, range));
}

std::unique_ptr<clangmm::Tokens> clangmm::TranslationUnit::get_tokens(const std::string &path, unsigned start_offset, unsigned end_offset) {
  SourceLocation start_location(cx_tu, path, start_offset);
  SourceLocation end_location(cx_tu, path, end_offset);
  SourceRange range(start_location, end_location);
  return std::unique_ptr<Tokens>(new Tokens(cx_tu, range));
}

std::unique_ptr<clangmm::Tokens> clangmm::TranslationUnit::get_tokens(unsigned start_offset, unsigned end_offset) {
  auto path = clangmm::to_string(clang_getTranslationUnitSpelling(cx_tu));
  SourceLocation start_location(cx_tu, path, start_offset);
  SourceLocation end_location(cx_tu, path, end_offset);
  SourceRange range(start_location, end_location);
  return std::unique_ptr<Tokens>(new Tokens(cx_tu, range));
}

std::unique_ptr<clangmm::Tokens> clangmm::TranslationUnit::get_tokens(unsigned start_line, unsigned start_column,
                                                                      unsigned end_line, unsigned end_column) {
  auto path = to_string(clang_getTranslationUnitSpelling(cx_tu));
  SourceLocation start_location(cx_tu, path, start_line, start_column);
  SourceLocation end_location(cx_tu, path, end_line, end_column);
  SourceRange range(start_location, end_location);
  return std::unique_ptr<Tokens>(new Tokens(cx_tu, range));
}

clangmm::Cursor clangmm::TranslationUnit::get_cursor(const std::string &path, unsigned offset) {
  SourceLocation location(cx_tu, path, offset);
  return Cursor(clang_getCursor(cx_tu, location.cx_location));
}

clangmm::Cursor clangmm::TranslationUnit::get_cursor(const std::string &path, unsigned line, unsigned column) {
  SourceLocation location(cx_tu, path, line, column);
  return Cursor(clang_getCursor(cx_tu, location.cx_location));
}

clangmm::Cursor clangmm::TranslationUnit::get_cursor(const SourceLocation &location) {
  return Cursor(clang_getCursor(cx_tu, location.cx_location));
}
