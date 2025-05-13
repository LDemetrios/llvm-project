add_llvm_component_library(LLVMRuneDesc
        RuneMCTargetDesc.cpp

        LINK_COMPONENTS
        MC
        Support
        RuneInfo

        ADD_TO_COMPONENT
        Rune
)