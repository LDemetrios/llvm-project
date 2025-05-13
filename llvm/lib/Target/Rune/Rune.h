#ifndef LLVM_LIB_TARGET_Rune_Rune_H
#define LLVM_LIB_TARGET_Rune_Rune_H

#include "MCTargetDesc/RuneMCTargetDesc.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include <ostream>

// Performed by Lisp magicians, don't try at home

#define PARENS ()

#define UNPACK( ... ) __VA_ARGS__

#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

#define FOR_EACH(sep, macro, ...)                            \
__VA_OPT__(EXPAND(FOR_EACH_HELPER(sep, macro, __VA_ARGS__)))
#define FOR_EACH_HELPER(sep, macro, a1, ...)                 \
    macro(a1)                                                \
    __VA_OPT__( UNPACK sep FOR_EACH_AGAIN PARENS (sep, macro, __VA_ARGS__))
#define FOR_EACH_AGAIN() FOR_EACH_HELPER

#define PRINT_ARGUMENT(x) #x << ": " << x
#define PRINT_ARGUMENTS(...) FOR_EACH((<< ", " <<), PRINT_ARGUMENT, __VA_ARGS__)

#define TICK(Color, ...)                                                   \
  {                                                                             \
    llvm::errs().changeColor(Color)                                             \
       << __func__ << "::" << __LINE__  << ": " << PRINT_ARGUMENTS(__VA_ARGS__) \
       __VA_OPT__(<<) "\n" << "\t\t(" << __FILE__ << ")"                        \
       << "\n";                                                                 \
    llvm::errs().changeColor(llvm::raw_ostream::WHITE);                         \
  }
// #define TICK(Color) {}

#define TICK_RED(...) TICK(llvm::raw_ostream::RED __VA_OPT__(,) __VA_ARGS__)
#define TICK_GREEN(...) TICK(llvm::raw_ostream::GREEN __VA_OPT__(,) __VA_ARGS__)
#define TICK_YELLOW(...) TICK(llvm::raw_ostream::YELLOW __VA_OPT__(,) __VA_ARGS__)
#define TICK_CYAN(...) TICK(llvm::raw_ostream::CYAN __VA_OPT__(,) __VA_ARGS__)
#define TICK_MAGENTA(...) TICK(llvm::raw_ostream::MAGENTA __VA_OPT__(,) __VA_ARGS__)
#define TICK_WHITE(...) TICK(llvm::raw_ostream::WHITE __VA_OPT__(,) __VA_ARGS__)


namespace llvm {
class RuneTargetMachine;
class FunctionPass;
class RuneSubtarget;
class AsmPrinter;
class InstructionSelector;
class MCInst;
class MCOperand;
class MachineInstr;
class MachineOperand;
class PassRegistry;

bool lowerRuneMachineInstrToMCInst(const MachineInstr *MI, MCInst &OutMI,
                                  AsmPrinter &AP);
bool LowerRuneMachineOperandToMCOperand(const MachineOperand &MO,
                                       MCOperand &MCOp, const AsmPrinter &AP);
FunctionPass *createRuneISelDag(RuneTargetMachine &TM, CodeGenOptLevel OptLevel);

} // namespace llvm

#endif // LLVM_LIB_TARGET_Rune_Rune_H