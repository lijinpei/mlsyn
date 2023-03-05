#include "mlsyn/Core/Symbol.h"
#include "mlir/Support/LogicalResult.h"
#include "mlsyn/Support/re2c.h"
#include "llvm/Support/MemoryBuffer.h"

namespace {
using namespace mlsyn;
class SymbolLexer : Re2CLexerBase {
public:
  SymbolLexer(const llvm::MemoryBuffer &MemBuf) : Re2CLexerBase(MemBuf) {}
  FailureOr<StringRef> lex() {
    /*!re2c
        re2c:api = custom;
        re2c:api:style = functions;
        re2c:yyfill:enable = 0;
        re2c:define:YYCTYPE = char;

        symbol = [A-Za-z_][A-Za-z_0-9]*;
        symbol { return getCurrentSpelling(); }
        * { return LogicalResult::failure(); }
      */
  }
};
} // namespace

namespace mlsyn {
FailureOr<StringRef> lexSymbol(const llvm::MemoryBuffer &Buffer) {
  return SymbolLexer(Buffer).lex();
}
} // namespace mlsyn
