#ifndef LLVM_LIB_TARGET_RUNE_MCTARGETDESC_RUNEMCASMINFO_H
#define LLVM_LIB_TARGET_RUNE_MCTARGETDESC_RUNEMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {

class Triple;

class RuneELFMCAsmInfo : public MCAsmInfoELF {
public:
  explicit RuneELFMCAsmInfo(const Triple &TheTriple);
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_RUNE_MCTARGETDESC_RUNEMCASMINFO_H