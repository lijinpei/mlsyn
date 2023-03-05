#include "mlsyn/Core/SyntaxContext.h"

using namespace mlsyn;

SyntaxExpander *
SyntaxContext::getSyntaxExpanderRecursive(const SyntaxContext *From,
                                          Symbol Sym) {
  while (From) {
    auto Itor = From->Expanders.find(Sym);
    if (Itor != From->Expanders.end()) {
      return Itor->second;
    }
    From = From->ParentSynCtx;
  }
  return nullptr;
}
