 #include "RuneTargetMachine.h"
#include "Rune.h"
 #include "TargetInfo/RuneTargetInfo.h"
 #include "llvm/MC/TargetRegistry.h"
 #include <optional>

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRuneTarget() {
  // Register the target.
  TICK_CYAN()
  RegisterTargetMachine<RuneTargetMachine> A(getTheRuneTarget());
}

RuneTargetMachine::RuneTargetMachine(const Target &T, const Triple &TT,
                                     StringRef CPU, StringRef FS,
                                     const TargetOptions &Options,
                                     std::optional<Reloc::Model> RM,
                                     std::optional<CodeModel::Model> CM,
                                     CodeGenOptLevel OL, bool JIT)
    : CodeGenTargetMachineImpl(
          T, "e-m:e-p:64:64-i8:8:32-i16:16:32-i64:64-n64", TT, CPU, FS, Options,
          Reloc::Static, getEffectiveCodeModel(CM, CodeModel::Small), OL) {
  TICK_CYAN()
}