add_llvm_component_group(Rune)

add_llvm_target(RuneCodeGen
        RuneTargetMachine.cpp

        LINK_COMPONENTS
        CodeGen
        Core
        Support
        Target
        RuneInfo

        ADD_TO_COMPONENT
        Rune
)

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)