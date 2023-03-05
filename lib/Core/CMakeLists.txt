file(GLOB SRC
     "*.re2c.cpp"
     "*.cpp"
)
add_mlsyn_library(MLSynCore
	Symbol.re2c.cpp
	SyntaxContext.cpp
)

target_link_libraries(MLSynCore
	MLIRSupport)
