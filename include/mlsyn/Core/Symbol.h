#pragma once

#include "mlir/Support/LogicalResult.h"
#include "mlsyn/Support/MLIR.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/MemoryBuffer.h"

namespace llvm {
class MemoryBufer;
}

namespace mlsyn {
class SymbolTable;
class Symbol {
public:
  using ID = std::size_t;
  ID getID() const { return Id; }
  StringRef getSpelling(const SymbolTable &);

private:
  Symbol(ID Id) : Id(Id) {}
  ID Id;
  friend class DenseMapInfo<Symbol>;
};
} // namespace mlsyn

namespace llvm {
template <> struct DenseMapInfo<mlsyn::Symbol> {
  using BaseInfo = DenseMapInfo<mlsyn::Symbol::ID>;
  static mlsyn::Symbol getEmptyKey() {
    return mlsyn::Symbol(BaseInfo::getEmptyKey());
  }
  static mlsyn::Symbol getTombstoneKey() {
    return mlsyn::Symbol(BaseInfo::getTombstoneKey());
  }
  static unsigned getHashValue(mlsyn::Symbol Sym) {
    return BaseInfo::getHashValue(Sym.Id);
  }
  static bool isEqual(mlsyn::Symbol LHS, mlsyn::Symbol RHS) {
    return LHS.Id == RHS.Id;
  }
};
} // namespace llvm

namespace mlsyn {
class SymbolTable {
  struct SymbolInfo {
    StringRef Spelling;
  };
  mlsyn::Symbol::ID NextId = 0;
  std::vector<SymbolInfo> SymbolInfos;
  DenseMap<StringRef, Symbol> SymbolMap;

public:
  Symbol internalize(StringRef Spelling);
  StringRef getSpelling(Symbol Sym) const {
    return SymbolInfos[Sym.getID()].Spelling;
  }
};
FailureOr<StringRef> lexSymbolSpelling(const llvm::MemoryBuffer &);
} // namespace mlsyn
