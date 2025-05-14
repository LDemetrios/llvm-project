#ifndef LLVM_LIB_TARGET_RUNE_MCTARGETDESC_RUNEMCTARGETDESC_H
#define LLVM_LIB_TARGET_RUNE_MCTARGETDESC_RUNEMCTARGETDESC_H

#include <memory>
namespace llvm {
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCAsmBackend;
class MCObjectTargetWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class MCTargetOptions;
class Target;

MCCodeEmitter *createRuneMCCodeEmitter(const MCInstrInfo &MCII, MCContext &Ctx);
MCAsmBackend *createRuneAsmBackend(const Target &T, const MCSubtargetInfo &STI,
                                  const MCRegisterInfo &MRI,
                                  const MCTargetOptions &Options);
std::unique_ptr<MCObjectTargetWriter> createRuneELFObjectWriter(bool Is64Bit,
                                                               uint8_t OSABI);
} // namespace llvm

// Defines symbolic names for Rune registers.  This defines a mapping from
// register name to register number.
//
#define GET_REGINFO_ENUM
#include "RuneGenRegisterInfo.inc"

// Defines symbolic names for the Rune instructions.
#define GET_INSTRINFO_ENUM
#include "RuneGenInstrInfo.inc"

#endif // LLVM_LIB_TARGET_RUNE_MCTARGETDESC_RUNEMCTARGETDESC_H
