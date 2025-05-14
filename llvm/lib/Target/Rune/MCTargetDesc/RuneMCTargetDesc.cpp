#include "MCTargetDesc/RuneInfo.h"
#include "Rune.h"
#include "RuneInstPrinter.h"
#include "RuneMCAsmInfo.h"
#include "TargetInfo/RuneTargetInfo.h"
#include "llvm/MC/MCDwarf.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define GET_REGINFO_MC_DESC
#include "RuneGenRegisterInfo.inc"

#define GET_INSTRINFO_MC_DESC
#include "RuneGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "RuneGenSubtargetInfo.inc"

static MCRegisterInfo *createRuneMCRegisterInfo(const Triple &TT) {
  TICK_MAGENTA()
  MCRegisterInfo *X = new MCRegisterInfo();
  InitRuneMCRegisterInfo(X, Rune::R0);
  return X;
}

static MCInstrInfo *createRuneMCInstrInfo() {
  TICK_MAGENTA()
  MCInstrInfo *X = new MCInstrInfo();
  InitRuneMCInstrInfo(X);
  return X;
}

static MCSubtargetInfo *createRuneMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU, StringRef FS) {
  TICK_MAGENTA()
  return createRuneMCSubtargetInfoImpl(TT, CPU, /*TuneCPU*/ CPU, FS);
}

static MCAsmInfo *createRuneMCAsmInfo(const MCRegisterInfo &MRI,
                                     const Triple &TT,
                                     const MCTargetOptions &Options) {
  TICK_MAGENTA()
  MCAsmInfo *MAI = new RuneELFMCAsmInfo(TT);
  unsigned SP = MRI.getDwarfRegNum(Rune::R1, true);
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, SP, 0);
  MAI->addInitialFrameState(Inst);
  return MAI;
}

static MCInstPrinter *createRuneMCInstPrinter(const Triple &T,
                                             unsigned SyntaxVariant,
                                             const MCAsmInfo &MAI,
                                             const MCInstrInfo &MII,
                                             const MCRegisterInfo &MRI) {
  TICK_MAGENTA()
  return new RuneInstPrinter(MAI, MII, MRI);
}

// We need to define this function for linking succeed
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRuneTargetMC() {
  TICK_MAGENTA()
  Target &TheRuneTarget = getTheRuneTarget();
  RegisterMCAsmInfoFn X(TheRuneTarget, createRuneMCAsmInfo);
  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheRuneTarget, createRuneMCRegisterInfo);
  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheRuneTarget, createRuneMCInstrInfo);
  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheRuneTarget,
                                          createRuneMCSubtargetInfo);

  // Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(TheRuneTarget, createRuneMCInstPrinter);
  // Register the MC Code Emitter.
  TargetRegistry::RegisterMCCodeEmitter(TheRuneTarget, createRuneMCCodeEmitter);
  // Register the asm backend.
  TargetRegistry::RegisterMCAsmBackend(TheRuneTarget, createRuneAsmBackend);
}
