#include "TargetInfo/RuneTargetInfo.h"
#include "Rune.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheRuneTarget() {
  TICK_YELLOW()
  static Target TheRuneTarget;
  return TheRuneTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRuneTargetInfo() {
  TICK_YELLOW()
  RegisterTarget<Triple::rune> X(getTheRuneTarget(), "rune",
                                "Simulator target for LLVM course", "RUNE");
}