#include "RuneRegisterInfo.h"
#include "Rune.h"
#include "RuneFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

using namespace llvm;

#define GET_REGINFO_TARGET_DESC
#include "RuneGenRegisterInfo.inc"

RuneRegisterInfo::RuneRegisterInfo() : RuneGenRegisterInfo(Rune::R0) {
  TICK_GREEN()
}
const MCPhysReg *
RuneRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  TICK_GREEN()
  return CSR_Rune_SaveList;
}

BitVector RuneRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  TICK_GREEN()
  RuneFrameLowering const *TFI = getFrameLowering(MF);

  BitVector Reserved(getNumRegs());
  Reserved.set(Rune::R1);

  if (TFI->hasFP(MF)) {
    Reserved.set(Rune::R2);
  }
  return Reserved;
}

bool RuneRegisterInfo::requiresRegisterScavenging(
    const MachineFunction &MF) const {
  return false;
}

bool RuneRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                          int SPAdj, unsigned FIOperandNum,
                                          RegScavenger *RS) const {
  TICK_GREEN()
  assert(SPAdj == 0 && "Unexpected non-zero SPAdj value");

  MachineInstr &MI = *II;
  MachineFunction &MF = *MI.getParent()->getParent();
  DebugLoc DL = MI.getDebugLoc();

  int FrameIndex = MI.getOperand(FIOperandNum).getIndex();
  Register FrameReg;
  int Offset = getFrameLowering(MF)
                   ->getFrameIndexReference(MF, FrameIndex, FrameReg)
                   .getFixed();
  Offset += MI.getOperand(FIOperandNum + 1).getImm();

  if (!isInt<16>(Offset)) {
    llvm_unreachable("");
  }

  MI.getOperand(FIOperandNum).ChangeToRegister(FrameReg, false, false, false);
  MI.getOperand(FIOperandNum + 1).ChangeToImmediate(Offset);
  return false;
}

Register RuneRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  TICK_GREEN()
  const TargetFrameLowering *TFI = getFrameLowering(MF);
  return TFI->hasFP(MF) ? Rune::R2 : Rune::R1;
}

const uint32_t *
RuneRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                      CallingConv::ID CC) const {
  TICK_GREEN()
  return CSR_Rune_RegMask;
}
