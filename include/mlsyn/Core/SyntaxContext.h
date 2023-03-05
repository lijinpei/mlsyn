#pragma once

#include "llvm/ADT/DenseMap.h"
#include "llvm/Support/SourceMgr.h"

#include "mlsyn/Core/MLSynContext.h"
#include "mlsyn/Core/Symbol.h"
#include "mlsyn/Support/MLIR.h"

namespace mlsyn {
class SyntaxExpander;
class SyntaxContext {
  MLSynContext &Context;
  SyntaxContext *ParentSynCtx = nullptr;
  DenseMap<Symbol, SyntaxExpander *> Expanders;
  SymbolTable SymTab;
  static SyntaxExpander *getSyntaxExpanderRecursive(const SyntaxContext *From,
                                                    Symbol Sym);

public:
  SyntaxExpander *registerExpander(Symbol Sym, SyntaxExpander *Expander) {
    return std::exchange(Expanders[Sym], Expander);
  }
  SyntaxExpander *deregisterEexpander(Symbol Sym) {
    auto Itor = Expanders.find(Sym);
    assert(Itor != Expanders.end());
    auto *Result = Itor->second;
    Expanders.erase(Itor);
    return Result;
  }
  SyntaxExpander *getSyntaxExpander(Symbol Sym) const {
    return getSyntaxExpanderRecursive(this, Sym);
  }
};
} // namespace mlsyn
