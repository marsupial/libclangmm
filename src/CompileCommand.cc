#include "CompileCommand.h"
#include "CompileCommands.h"

std::string clang::CompileCommand::
get_command() {
  std::string res;
  unsigned N = clang_CompileCommand_getNumArgs(cx_command);
  for (unsigned i = 0; i < N; i++) {
    res += clang_getCString(clang_CompileCommand_getArg(cx_command, i));
  }
  return res;
}

std::vector<std::string> clang::CompileCommand::
get_command_as_args() {
  unsigned N = clang_CompileCommand_getNumArgs(cx_command);
  std::vector<std::string> res(N);
  for (unsigned i = 0; i < N; i++) {
    res[i] = clang_getCString(clang_CompileCommand_getArg(cx_command, i));
  }
  return res;
}
