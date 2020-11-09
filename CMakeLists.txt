cmake_minimum_required(VERSION 3.14)
project(Bitfield)

# ---- Options ---- #

# Option ENABLE_CODE_COVERAGE will build the code with --coverage.
# e.g. make sisl_coverage can be used to run all tests. (lcov required)
option(ENABLE_CODE_COVERAGE "Build with code coverage" OFF)

# Option ENABLE_TESTS will add the tests directories to the build
# e.g. make tests
option(ENABLE_TESTS "Build the tests" OFF)

# Option ENABLE_LTO will build the project link linker optimisation
option(ENABLE_LTO "Build with linker optimisation" OFF)

# Option ENABLE_DOXYGEN will generate documentation
# e.g. make sisl_doc will generate sisl libraries documentation
option(ENABLE_DOXYGEN "Generate Doxygen optimisation" OFF)

# Option ENABLE_BENCHMARKS to enable the benchmarks. Benchmarks are reccomended in release mode only
option(ENABLE_BENCHMARKS "Build including the benchmarks" OFF)

# ---- Options End ---- #

# ---- Version Generation ---- #
set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)
set(PATCH_VERSION 0)
# set (RELEASE_CANDIDATE 0) # Set this for rc

if (DEFINED RELEASE_CANDIDATE)
    set (RELEASE_CANDIDATE "-rc${RELEASE_CANDIDATE}")
endif()

# configure a header file to pass some of the CMake settings
# to the source code
#configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/version.h.in"
#        "${CMAKE_CURRENT_BINARY_DIR}/version.h")

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# ---- Version Generation End ---- #

# ---- General Settings ---- #

# Required packages
find_package(Threads REQUIRED)

# Enable verbose makefile output
set(CMAKE_VERBOSE_MAKEFILE ON)

# Include our custom cmake functions
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# ---- Compiler Settings ---- #
# Configure the compiler options
include(CompilerOptions)

# ---- Enable Testing ---- #
if(ENABLE_TESTS)
    enable_testing()
endif()

# ---- Default Output Build Location ---- #
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)

add_subdirectory(test)