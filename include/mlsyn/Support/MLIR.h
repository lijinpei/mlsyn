#pragma once

#include "mlsyn/Support/LLVM.h"

namespace mlir {
// mlir/IR/MLIRContext.h
class MLIRContext;

// mlir/Support/LogicalResult.h
class LogicalResult;
template <typename T> class FailureOr;
class ParseResult;

// mlir/Support/TypeID.h
class TypeID;
} // namespace mlir

namespace mlsyn {
// mlir/IR/MLIRContext.h
using mlir::MLIRContext;

// mlir/Support/LogicalResult.h
using mlir::FailureOr;
using mlir::LogicalResult;
using mlir::ParseResult;

// mlir/Support/TypeID.h
using mlir::TypeID;
} // namespace mlsyn
