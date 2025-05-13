add_llvm_component_library(LLVMRuneInfo
        RuneTargetInfo.cpp

        LINK_COMPONENTS
        MC
        Support

        ADD_TO_COMPONENT
        Rune
)