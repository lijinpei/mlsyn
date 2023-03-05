cmake_minimum_required(VERSION 3.20.0)
project(mlir-syntax)
find_package(LLVM REQUIRED)
find_package(MLIR REQUIRED)
list (INSERT CMAKE_MODULE_PATH 0
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
include (AddLLVM)
include (AddMLSyn)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${MLIR_INCLUDE_DIRS}")
add_subdirectory(lib)

