#ifndef CURSOR_H_
#define CURSOR_H_
#include "source_location.h"
#include "source_range.h"
#include <clang-c/Index.h>
#include <string>
#include <unordered_set>
#include <vector>

namespace clangmm {
  class Cursor {
  public:
    enum class Kind {
      UnexposedDecl = 1,
      StructDecl = 2,
      UnionDecl = 3,
      ClassDecl = 4,
      EnumDecl = 5,
      FieldDecl = 6,
      EnumConstantDecl = 7,
      FunctionDecl = 8,
      VarDecl = 9,
      ParmDecl = 10,
      ObjCInterfaceDecl = 11,
      ObjCCategoryDecl = 12,
      ObjCProtocolDecl = 13,
      ObjCPropertyDecl = 14,
      ObjCIvarDecl = 15,
      ObjCInstanceMethodDecl = 16,
      ObjCClassMethodDecl = 17,
      ObjCImplementationDecl = 18,
      ObjCCategoryImplDecl = 19,
      TypedefDecl = 20,
      CXXMethod = 21,
      Namespace = 22,
      LinkageSpec = 23,
      Constructor = 24,
      Destructor = 25,
      ConversionFunction = 26,
      TemplateTypeParameter = 27,
      NonTypeTemplateParameter = 28,
      TemplateTemplateParameter = 29,
      FunctionTemplate = 30,
      ClassTemplate = 31,
      ClassTemplatePartialSpecialization = 32,
      NamespaceAlias = 33,
      UsingDirective = 34,
      UsingDeclaration = 35,
      TypeAliasDecl = 36,
      ObjCSynthesizeDecl = 37,
      ObjCDynamicDecl = 38,
      CXXAccessSpecifier = 39,
      FirstDecl = UnexposedDecl,
      LastDecl = CXXAccessSpecifier,
      FirstRef = 40,
      ObjCSuperClassRef = 40,
      ObjCProtocolRef = 41,
      ObjCClassRef = 42,
      TypeRef = 43,
      CXXBaseSpecifier = 44,
      TemplateRef = 45,
      NamespaceRef = 46,
      MemberRef = 47,
      LabelRef = 48,
      OverloadedDeclRef = 49,
      VariableRef = 50,
      LastRef = VariableRef,
      FirstInvalid = 70,
      InvalidFile = 70,
      NoDeclFound = 71,
      NotImplemented = 72,
      InvalidCode = 73,
      LastInvalid = InvalidCode,
      FirstExpr = 100,
      UnexposedExpr = 100,
      DeclRefExpr = 101,
      MemberRefExpr = 102,
      CallExpr = 103,
      ObjCMessageExpr = 104,
      BlockExpr = 105,
      IntegerLiteral = 106,
      FloatingLiteral = 107,
      ImaginaryLiteral = 108,
      StringLiteral = 109,
      CharacterLiteral = 110,
      ParenExpr = 111,
      UnaryOperator = 112,
      ArraySubscriptExpr = 113,
      BinaryOperator = 114,
      CompoundAssignOperator = 115,
      ConditionalOperator = 116,
      CStyleCastExpr = 117,
      CompoundLiteralExpr = 118,
      InitListExpr = 119,
      AddrLabelExpr = 120,
      StmtExpr = 121,
      GenericSelectionExpr = 122,
      GNUNullExpr = 123,
      CXXStaticCastExpr = 124,
      CXXDynamicCastExpr = 125,
      CXXReinterpretCastExpr = 126,
      CXXConstCastExpr = 127,
      CXXFunctionalCastExpr = 128,
      CXXTypeidExpr = 129,
      CXXBoolLiteralExpr = 130,
      CXXNullPtrLiteralExpr = 131,
      CXXThisExpr = 132,
      CXXThrowExpr = 133,
      CXXNewExpr = 134,
      CXXDeleteExpr = 135,
      UnaryExpr = 136,
      ObjCStringLiteral = 137,
      ObjCEncodeExpr = 138,
      ObjCSelectorExpr = 139,
      ObjCProtocolExpr = 140,
      ObjCBridgedCastExpr = 141,
      PackExpansionExpr = 142,
      SizeOfPackExpr = 143,
      LambdaExpr = 144,
      ObjCBoolLiteralExpr = 145,
      ObjCSelfExpr = 146,
      LastExpr = ObjCSelfExpr,
      FirstStmt = 200,
      UnexposedStmt = 200,
      LabelStmt = 201,
      CompoundStmt = 202,
      CaseStmt = 203,
      DefaultStmt = 204,
      IfStmt = 205,
      SwitchStmt = 206,
      WhileStmt = 207,
      DoStmt = 208,
      ForStmt = 209,
      GotoStmt = 210,
      IndirectGotoStmt = 211,
      ContinueStmt = 212,
      BreakStmt = 213,
      ReturnStmt = 214,
      GCCAsmStmt = 215,
      AsmStmt = GCCAsmStmt,
      ObjCAtTryStmt = 216,
      ObjCAtCatchStmt = 217,
      ObjCAtFinallyStmt = 218,
      ObjCAtThrowStmt = 219,
      ObjCAtSynchronizedStmt = 220,
      ObjCAutoreleasePoolStmt = 221,
      ObjCForCollectionStmt = 222,
      CXXCatchStmt = 223,
      CXXTryStmt = 224,
      CXXForRangeStmt = 225,
      SEHTryStmt = 226,
      SEHExceptStmt = 227,
      SEHFinallyStmt = 228,
      MSAsmStmt = 229,
      NullStmt = 230,
      DeclStmt = 231,
      LastStmt = DeclStmt,
      TranslationUnit = 300,
      FirstAttr = 400,
      UnexposedAttr = 400,
      IBActionAttr = 401,
      IBOutletAttr = 402,
      IBOutletCollectionAttr = 403,
      CXXFinalAttr = 404,
      CXXOverrideAttr = 405,
      AnnotateAttr = 406,
      AsmLabelAttr = 407,
      LastAttr = AsmLabelAttr,
      PreprocessingDirective = 500,
      MacroDefinition = 501,
      MacroExpansion = 502,
      MacroInstantiation = MacroExpansion,
      InclusionDirective = 503,
      FirstPreprocessing = PreprocessingDirective,
      LastPreprocessing = InclusionDirective,
      ModuleImportDecl = 600,
      FirstExtraDecl = ModuleImportDecl,
      LastExtraDecl = ModuleImportDecl,
    };
    class Type {
    public:
      Type(const CXType &cx_type) : cx_type(cx_type) {}
      std::string get_spelling() const;
      Type get_result() const;
      Cursor get_cursor() const;
      bool operator==(const Cursor::Type &rhs) const;

      CXType cx_type;
    };

    Cursor() { cx_cursor = clang_getNullCursor(); }
    Cursor(const CXCursor &cx_cursor) : cx_cursor(cx_cursor) {}
    Kind get_kind() const;
    std::string get_kind_spelling() const;
    static bool is_similar_kind(Kind kind, Kind other_kind);
    Type get_type() const;
    SourceLocation get_source_location() const;
    SourceRange get_source_range() const;
    std::string get_spelling() const;
    std::string get_display_name() const;
    std::string get_token_spelling() const;
    std::string get_usr() const;
    /// Improved usr that is also template and argument invariant
    std::string get_usr_extended() const;
    /// Also get overridden cursors
    std::unordered_set<std::string> get_all_usr_extended() const;
    Cursor get_referenced() const;
    Cursor get_canonical() const;
    Cursor get_definition() const;
    Cursor get_semantic_parent() const;
    std::vector<Cursor> get_children() const;
    std::vector<Cursor> get_arguments() const;
    std::vector<Cursor> get_all_overridden_cursors() const;
    operator bool() const;
    bool operator==(const Cursor &rhs) const;
    unsigned hash() const;

    bool is_valid_kind() const;
    std::string get_type_description() const;
    std::string get_brief_comments() const;

    friend std::ostream &operator<<(std::ostream &os, const Cursor &cursor) {
      os << cursor.get_source_range() << ' ' << cursor.get_spelling();
      return os;
    }

    CXCursor cx_cursor;
  };
} // namespace clangmm
#endif // CURSOR_H_
