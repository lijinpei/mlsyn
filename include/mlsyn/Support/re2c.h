#pragma once

#include "mlsyn/Support/MLIR.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/MemoryBuffer.h"

namespace llvm {
class MemoryBuffer;
}

namespace mlsyn {
struct LineAndCol {
  std::size_t Line;
  std::size_t Column;
};
class Re2CLexerBase {
  const llvm::MemoryBuffer &MemBuf;
  using PositionTy = const char *;
  PositionTy CurPos = MemBuf.getBufferStart();
  PositionTy MaxOffset = CurPos;
  std::vector<PositionTy> LineEndings;
  std::size_t CurLine = 0;
  PositionTy BackupPos = nullptr;
  std::size_t BackupLine = std::size_t(-1);

public:
  Re2CLexerBase(const llvm::MemoryBuffer &MemBuf) : MemBuf(MemBuf) {}
  void YYSKIP();
  char YYPEEK() const { return *CurPos; }
  bool YYLESSTHAN(std::size_t Len) const {
    return CurPos + Len <= MemBuf.getBufferEnd();
  }
  void YYBACKUP() {
    assert(BackupPos == nullptr && BackupLine == std::size_t(-1) &&
           "Backup storage already used");
    BackupPos = CurPos;
    BackupLine = CurLine;
  }
  void YYRESTORE() {
    assert(BackupPos != nullptr && BackupLine != std::size_t(-1) &&
           "Backup storage empty");
    CurPos = BackupPos;
    CurLine = BackupLine;
  }
  LineAndCol getCurrentLineAndCol() const {
    std::ptrdiff_t CurCol = CurLine ? CurPos - LineEndings[CurLine - 1]
                                    : CurPos - MemBuf.getBufferStart();
    assert(CurCol > 0);
    return {CurLine + 1, (std::size_t)CurCol};
  }
  StringRef getCurrentSpelling() {
    const char *Start = MemBuf.getBufferStart();
    return StringRef(Start, CurPos - Start);
  }
  /* YYBACKUPCTX(); YYRESTORECTX(); YYFILL(); */
};
} // namespace mlsyn
