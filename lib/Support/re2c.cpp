#include "llvm/Support/MemoryBuffer.h"

using namespace mlsyn;

void Re2CLexerBase::YYSKIP() {
  assert(CurPos < MemBuf.getBufferEnd());
  if (CurPos == MaxOffset) {
    char C = *MaxOffset;
    if (C == '\n') {
      if (MaxOffset < MemoryBuffer.getBufferEnd() && *(MaxOffset + 1) == '\r') {
        LineEndings.push_back(MaxOffset + 1);
        MaxOffset += 2;
      } else {
        LineEndings.push_back(MaxOffset);
        MaxOffset += 1;
      }
    } else {
      MaxOffset += 1;
    }
  }
  if (CurLine < LineEndings.size() && LineEndings[CurLine] == Offset) {
    CurLine += 1;
  }
  Offset += 1;
}
