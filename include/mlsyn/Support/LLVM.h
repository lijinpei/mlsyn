#pragma once

#include "llvm/Support/Allocator.h"

namespace llvm {
// llvm/ADT/DenseMapInfo.h
template <typename, typename> class DenseMapInfo;

// llvm/ADT/DenseMap.h
template <typename, typename, typename, typename> class DenseMap;

// llvm/ADT/StringRef.h
class StringRef;
} // namespace llvm

namespace mlsyn {
// llvm/ADT/DenseMapInfo.h
using llvm::DenseMapInfo;

// llvm/ADT/DenseMap.h
using llvm::DenseMap;

// llvm/ADT/StringRef.h
using llvm::StringRef;

// llvm/Support/Allocator.h
using llvm::BumpPtrAllocator;
} // namespace mlsyn
