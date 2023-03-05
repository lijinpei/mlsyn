#pragma once

#include "mlsyn/Support/MLIR.h"
#include "llvm/Support/Allocator.h"

namespace mlsyn {
class MLSynContext {
  BumpPtrAllocator Allocator;

public:
  BumpPtrAllocator &getAllocator();
};
} // namespace mlsyn
