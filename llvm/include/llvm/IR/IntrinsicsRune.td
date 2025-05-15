let TargetPrefix = "rune" in {

 def int_rune_putpixel: ClangBuiltin<"runePutPixel">,
   Intrinsic<[], [llvm_i32_ty, llvm_i32_ty, llvm_i32_ty], [IntrNoMem, IntrHasSideEffects]>;

 def int_rune_flush: ClangBuiltin<"runeFlush">,
   Intrinsic<[], [], [IntrNoMem, IntrHasSideEffects]>;

 } // TargetPrefix = "rune"