add_llvm_component_library(LLVMRuneDesc
  RuneMCTargetDesc.cpp
  RuneMCAsmInfo.cpp
  RuneInstPrinter.cpp

  LINK_COMPONENTS
  MC
  Support
  RuneInfo

  ADD_TO_COMPONENT
  Rune
 )
