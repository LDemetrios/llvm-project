#include "MCTargetDesc/RuneInstPrinter.h"
#include "Rune.h"
#include "RuneSubtarget.h"
#include "RuneTargetMachine.h"
#include "TargetInfo/RuneTargetInfo.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "asm-printer"

namespace {

class RuneAsmPrinter : public AsmPrinter {
  const MCSubtargetInfo *STI;

public:
  explicit RuneAsmPrinter(TargetMachine &TM,
                         std::unique_ptr<MCStreamer> Streamer)
      : AsmPrinter(TM, std::move(Streamer)), STI(TM.getMCSubtargetInfo()) {
    TICK_GREEN()
  }

  void emitInstruction(const MachineInstr *MI) override;

  StringRef getPassName() const override { return "Rune Assembly Printer"; }

  bool lowerPseudoInstExpansion(const MachineInstr *MI, MCInst &Inst);

  // Used in pseudo lowerings
  bool lowerOperand(const MachineOperand &MO, MCOperand &MCOp) const {
    return LowerRuneMachineOperandToMCOperand(MO, MCOp, *this);
  }
};

} // end anonymous namespace

// Runeple pseudo-instructions have their lowering (with expansion to real
// instructions) auto-generated.
#include "RuneGenMCPseudoLowering.inc"

void RuneAsmPrinter::emitInstruction(const MachineInstr *MI) {
  TICK_GREEN()
  // Do any auto-generated pseudo lowerings.
  if (MCInst OutInst; lowerPseudoInstExpansion(MI, OutInst)) {
    EmitToStreamer(*OutStreamer, OutInst);
    return;
  }

  MCInst TmpInst;
  if (!lowerRuneMachineInstrToMCInst(MI, TmpInst, *this))
    EmitToStreamer(*OutStreamer, TmpInst);
}

// Force static initialization.
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRuneAsmPrinter() {
  RegisterAsmPrinter<RuneAsmPrinter> X(getTheRuneTarget());
}
