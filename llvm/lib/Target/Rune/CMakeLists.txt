add_llvm_component_group(Rune)

set(LLVM_TARGET_DEFINITIONS Rune.td)

tablegen(LLVM RuneGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM RuneGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM RuneGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM RuneGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM RuneGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM RuneGenCallingConv.inc -gen-callingconv)
tablegen(LLVM RuneGenAsmWriter.inc -gen-asm-writer)

add_public_tablegen_target(RuneCommonTableGen)

add_llvm_target(RuneCodeGen
  RuneTargetMachine.cpp
  RuneRegisterInfo.cpp
  RuneInstrInfo.cpp
  RuneSubtarget.cpp
  RuneAsmPrinter.cpp
  RuneISelDagToDag.cpp
  RuneISelLowering.cpp
  RuneMCInstLower.cpp

  LINK_COMPONENTS
  CodeGen
  Core
  Support
  Target
  RuneInfo
  AsmPrinter
  SelectionDAG

  ADD_TO_COMPONENT
  Rune
  )

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
