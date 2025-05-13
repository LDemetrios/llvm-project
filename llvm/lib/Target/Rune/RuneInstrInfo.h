#ifndef LLVM_LIB_TARGET_RUNE_RUNEINSTRINFO_H
#define LLVM_LIB_TARGET_RUNE_RUNEINSTRINFO_H

#include "RuneRegisterInfo.h"
#include "MCTargetDesc/RuneInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "RuneGenInstrInfo.inc"

namespace llvm {

class RuneSubtarget;

class RuneInstrInfo : public RuneGenInstrInfo {
public:
  RuneInstrInfo();

};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_RUNE_RUNEINSTRINFO_H
