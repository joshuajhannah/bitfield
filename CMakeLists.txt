cmake_minimum_required(VERSION 3.14)
project(Bitfield)

# Enable verbose makefile output
set(CMAKE_VERBOSE_MAKEFILE ON)

# Include our custom cmake functions
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# ---- Compiler Settings ---- #
# Configure the compiler options
include(CompilerOptions)

# ---- Default Output Build Location ---- #
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)

add_subdirectory(test)