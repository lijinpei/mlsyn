#pragma once

#include "mlir/Support/LogicalResult.h"
#include "mlir/Support/TypeID.h"
#include "mlsyn/Support/MLIR.h"

namespace mlsyn {
class Language {
private:
  TypeID LangID;
  bool HasAdHocExpander = false;

public:
  virtual ~Language();
  TypeID getTypeID() { return LangID; }
  virtual LogicalResult registerLang(SyntaxContext &Ctx) = 0;
  virtual LanguageExpander *resolveAdHocExpander(Symbol);
};
} // namespace mlsyn
