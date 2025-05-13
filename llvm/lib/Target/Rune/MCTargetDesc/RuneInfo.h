#ifndef LLVM_LIB_TARGET_RUNE_MCTARGETDESC_RUNEINFO_H
#define LLVM_LIB_TARGET_RUNE_MCTARGETDESC_RUNEINFO_H

#include "llvm/MC/MCInstrDesc.h"

namespace llvm {

namespace RuneOp {
enum OperandType : unsigned {
  OPERAND_SIMM16 = MCOI::OPERAND_FIRST_TARGET,
};
} // namespace RuneOp

} // end namespace llvm

#endif
