#include "Rune.h"
#include "clang/Basic/Builtins.h"
#include "clang/Basic/MacroBuilder.h"
#include "clang/Basic/TargetBuiltins.h"

using namespace clang;
using namespace clang::targets;

static constexpr Builtin::Info BuiltinInfo[] = {
#define BUILTIN(ID, TYPE, ATTRS)                                               \
  {#ID, TYPE, ATTRS, nullptr, HeaderDesc::NO_HEADER, ALL_LANGUAGES},
#include "clang/Basic/BuiltinsRune.def"
};

void RuneTargetInfo::getTargetDefines(const LangOptions &Opts,
                                     MacroBuilder &Builder) const {
  Builder.defineMacro("__rune__");
}

ArrayRef<Builtin::Info> RuneTargetInfo::getTargetBuiltins() const {
//  return std::nullopt;
  return llvm::ArrayRef(BuiltinInfo,
                        clang::Rune::LastTSBuiltin - Builtin::FirstTSBuiltin);
}