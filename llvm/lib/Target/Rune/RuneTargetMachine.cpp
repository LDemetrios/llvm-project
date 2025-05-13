#include "RuneTargetMachine.h"
#include "Rune.h"
#include "TargetInfo/RuneTargetInfo.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
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
    : CodeGenTargetMachineImpl(T, "e-m:e-p:32:32-i8:8:32-i16:16:32-i64:64-n32",
                               TT, CPU, FS, Options, Reloc::Static,
                               getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()),
      Subtarget(TT, std::string(CPU), std::string(FS), *this) {
  TICK_CYAN()
  initAsmInfo();
}

namespace {

/// Rune Code Generator Pass Configuration Options.
class RunePassConfig : public TargetPassConfig {
public:
  RunePassConfig(RuneTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  RuneTargetMachine &getRuneTargetMachine() const {
    return getTM<RuneTargetMachine>();
  }

  bool addInstSelector() override {
    TICK_CYAN()
    addPass(createRuneISelDag(getRuneTargetMachine(), getOptLevel()));
    return false;
  }
};

} // end anonymous namespace

TargetPassConfig *RuneTargetMachine::createPassConfig(PassManagerBase &PM) {
  TICK_CYAN()
  return new RunePassConfig(*this, PM);
}

TargetLoweringObjectFile *RuneTargetMachine::getObjFileLowering() const {
  TICK_CYAN()
  return TLOF.get();
}
