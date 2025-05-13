#ifndef LLVM_LIB_TARGET_RUNE_RUNETARGETMACHINE_H
#define LLVM_LIB_TARGET_RUNE_RUNETARGETMACHINE_H

#include "RuneSubtarget.h"
#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
#include <optional>

namespace llvm {
extern Target TheRuneTarget;

class RuneTargetMachine : public CodeGenTargetMachineImpl {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  RuneSubtarget Subtarget;

public:
  RuneTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                   StringRef FS, const TargetOptions &Options,
                   std::optional<Reloc::Model> RM,
                   std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                   bool JIT);

  const RuneSubtarget *getSubtargetImpl(const Function &) const override {
    TICK_CYAN()
    return &Subtarget;
  }
  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
  TargetLoweringObjectFile *getObjFileLowering() const override;
};
} // end namespace llvm

#endif // LLVM_LIB_TARGET_RUNE_RUNETARGETMACHINE_H
