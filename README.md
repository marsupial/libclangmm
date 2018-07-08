# libclangmm

###### an easy-to-use C++ wrapper for libclang

## About ##
Provides C++ bindings and class structure to the [libclang](http://www.llvm.org) C library.

Developed for [juCi++](https://gitlab.com/cppit/jucipp), a lightweight, platform-independent C++ IDE.

## Dependencies ##
* libclang

## Installation ##
See [installation guide](https://gitlab.com/cppit/libclangmm/blob/master/docs/install.md)

## Tests ##
To run the unit tests:
```sh
mkdir build && cd build
cmake -DBUILD_TESTING=1 ..
make
make test
```

## Coding style
Due to poor lambda support in clang-format, a custom clang-format is used with the following patch applied:
```diff
diff --git a/lib/Format/ContinuationIndenter.cpp b/lib/Format/ContinuationIndenter.cpp
index bb8efd61a3..e80a487055 100644
--- a/lib/Format/ContinuationIndenter.cpp
+++ b/lib/Format/ContinuationIndenter.cpp
@@ -276,6 +276,8 @@ LineState ContinuationIndenter::getInitialState(unsigned FirstIndent,
 }
 
 bool ContinuationIndenter::canBreak(const LineState &State) {
+  if(Style.ColumnLimit==0)
+    return true;
   const FormatToken &Current = *State.NextToken;
   const FormatToken &Previous = *Current.Previous;
   assert(&Previous == Current.Previous);
@@ -325,6 +327,8 @@ bool ContinuationIndenter::canBreak(const LineState &State) {
 }
 
 bool ContinuationIndenter::mustBreak(const LineState &State) {
+  if(Style.ColumnLimit==0)
+    return false;
   const FormatToken &Current = *State.NextToken;
   const FormatToken &Previous = *Current.Previous;
   if (Current.MustBreakBefore || Current.is(TT_InlineASMColon))
```

