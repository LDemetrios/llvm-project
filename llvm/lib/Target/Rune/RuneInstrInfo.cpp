#include "RuneInstrInfo.h"
#include "Rune.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineMemOperand.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "RuneGenInstrInfo.inc"

#define DEBUG_TYPE "Rune-inst-info"

RuneInstrInfo::RuneInstrInfo() : RuneGenInstrInfo() { TICK_GREEN() }
