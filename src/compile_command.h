#ifndef COMPILECOMMAND_H_
#define COMPILECOMMAND_H_
#include <clang-c/CXCompilationDatabase.h>
#include <string>
#include <vector>

namespace clangmm {
  class CompileCommand {
  public:
    CompileCommand(const CXCompileCommand &cx_command) : cx_command(cx_command){};
    std::vector<std::string> get_arguments();

    CXCompileCommand cx_command;
  };
} // namespace clangmm
#endif // COMPILECOMMAND_H_
