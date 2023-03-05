#pragma once

#include "mlir/Support/LogicalResult.h"
#include "mlsyn/Support/MLIR.h"

namespace mlsyn {
class Symbol;
class SyntaxContext;
class SyntaxExpander {
  bool canLookAhead = false;

public:
  virtual ~SyntaxExpander() = 0;
  virtual FailureOr<std::size_t>
  parse(Symbol symbol, const MemoryBuffer &MemBuf, SyntaxContext &Context) = 0;
};
class LookAheadSyntaxExpander : public SyntaxExpander {
public:
  using LookAheadTokenTy = void *;
  struct LookAheadInfo {
    std::size_t Size;
    LookAheadTokenTy Token;
  };

protected:
  struct LookAheadStorageBase {
    Symbol symbol;
    const MemoryBuffer &MemBuf;
    SyntaxContext &Context;
  };
  virtual FailureOr<LookAheadInfo> lookAhead(Symbol symbol,
                                             const MemoryBuffer &MemBuf,
                                             SyntaxContext &Context) = 0;
  virtual void discardLookAhead(LookAheadTokenTy) = 0;
  virtual FailureOr<std::size_t> parseLookAhead(LookAheadTokenTy) = 0;
};
class SyntaxExpanderResolver {
  SyntaxContext &Context;

public:
  SyntaxExpanderResolver(SyntaxContext &Context) : Context(Context);
  virtual SyntaxExpander *resolveSyntaxExpander(Symbol) = 0;
};
class MapSyntaxExpanderResolver : public SyntaxExpanderResolver {
public:
  SyntaxExpander *resolveSyntaxExpander(Symbol) override;
};
} // namespace mlsyn
