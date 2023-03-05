#pragma once

#include <memory>

namespace mlsyn {
class SyntaxExpander;
class SyntaxContext;
namespace builtin {
std::unique_ptr<SyntaxExpander> createLoadLanguageExpander();
void loadBuiltinLanguage(SyntaxContext &Context);
} // namespace builtin
} // namespace mlsyn
