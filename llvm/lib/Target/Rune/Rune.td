include "llvm/Target/Target.td"
include "RuneRegisterInfo.td"
include "RuneInstrInfo.td"
include "RuneCallingConv.td"

class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"generic", []>;

def RuneInstrInfo : InstrInfo;
def Rune : Target {
  let InstructionSet = RuneInstrInfo;
}
