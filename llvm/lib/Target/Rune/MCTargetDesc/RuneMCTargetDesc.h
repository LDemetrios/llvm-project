#ifndef LLVM_LIB_TARGET_RUNE_MCTARGETDESC_RUNEMCTARGETDESC_H
#define LLVM_LIB_TARGET_RUNE_MCTARGETDESC_RUNEMCTARGETDESC_H

// Defines symbolic names for Rune registers.  This defines a mapping from
// register name to register number.
//
#define GET_REGINFO_ENUM
#include "RuneGenRegisterInfo.inc"

// Defines symbolic names for the Rune instructions.
#define GET_INSTRINFO_ENUM
#include "RuneGenInstrInfo.inc"

#endif // LLVM_LIB_TARGET_RUNE_MCTARGETDESC_RUNEMCTARGETDESC_H
