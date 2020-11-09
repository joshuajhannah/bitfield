# GCC Compiler
list(APPEND GCC_EXCEPTIONS_FLAGS
        "-fexceptions"
        )

list(APPEND GCC_FLAGS
        "-Wall"
        "-Wextra"
        "-Wcast-qual"
        "-Wconversion-null"
        "-Wmissing-declarations"
        "-Woverlength-strings"
        "-Wpointer-arith"
        "-Wunused-local-typedefs"
        "-Wunused-result"
        "-Wvarargs"
        "-Wvla"
        "-Wwrite-strings"
        "-Wno-sign-compare"
        "-pipe"
        "-pthread"
        "-msse4"
        "-fconcepts"
        "-g" # always include debug information
        )

list(APPEND GCC_TEST_FLAGS
        "-Wno-conversion-null"
        "-Wno-missing-declarations"
        "-Wno-sign-compare"
        "-Wno-unused-function"
        "-Wno-unused-parameter"
        "-Wno-unused-private-field"
        )

list(APPEND GCC_DEBUG_FLAGS
        "-D_GLIBCXX_DEBUG"
        "-O0"
        "-g"
        )

list(APPEND GCC_RELEASE_FLAGS
        "-O3"
        "-fPIC"
        "-m64"
        "-march=native"
        )

list(APPEND COVERAGE_FLAGS
        "--coverage"
        "-fprofile-arcs"
        "-ftest-coverage"
        )

# LLVM
list(APPEND LLVM_EXCEPTIONS_FLAGS
        "-fexceptions"
        )

list(APPEND LLVM_FLAGS
        "-Wall"
        "-Wextra"
        )

list(APPEND LLVM_TEST_FLAGS
        "-Wno-c99-extensions"
        "-Wno-missing-noreturn"
        "-Wno-missing-prototypes"
        "-Wno-missing-variable-declarations"
        "-Wno-null-conversion"
        "-Wno-shadow"
        "-Wno-shift-sign-overflow"
        "-Wno-sign-compare"
        "-Wno-unused-function"
        "-Wno-unused-member-function"
        "-Wno-unused-parameter"
        "-Wno-unused-private-field"
        "-Wno-unused-template"
        "-Wno-used-but-marked-unused"
        "-Wno-zero-as-null-pointer-constant"
        "-Wno-gnu-zero-variadic-macro-arguments"
        )

# Configure Compiler options
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(DEFAULT_COPTS "${GCC_FLAGS}")
    set(TEST_COPTS "${GCC_FLAGS};${GCC_TEST_FLAGS}")
    set(EXCEPTIONS_FLAG "${GCC_EXCEPTIONS_FLAGS}")
elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    # MATCHES so we get both Clang and AppleClang
    set(DEFAULT_COPTS "${LLVM_FLAGS}")
    set(TEST_COPTS "${LLVM_FLAGS};${LLVM_TEST_FLAGS}")
    set(EXCEPTIONS_FLAG "${LLVM_EXCEPTIONS_FLAGS}")
else()
    message(FATAL_ERROR "Unknown compiler: ${CMAKE_CXX_COMPILER}.")
endif()

# Store the build type internally
if(CMAKE_BUILD_TYPE)
    string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_LOWER)
endif()

if(${CMAKE_BUILD_TYPE_LOWER} MATCHES "debug")
    set(DEFAULT_COPTS "${DEFAULT_COPTS};${GCC_DEBUG_FLAGS}")
    set(TEST_COPTS "${TEST_COPTS};${GCC_TEST_FLAGS};${GCC_DEBUG_FLAGS}")
elseif(${CMAKE_BUILD_TYPE_LOWER} MATCHES "release")
    set(DEFAULT_COPTS "${GCC_FLAGS};${GCC_RELEASE_FLAGS}")
    set(TEST_COPTS "${GCC_FLAGS};${GCC_TEST_FLAGS};${GCC_RELEASE_FLAGS}")
else()
    message(FATAL_ERROR "Unknown build type: ${CMAKE_BUILD_TYPE}.")
endif()

if(ENABLE_CODE_COVERAGE)
    # Check prereqs
    find_program( GCOV_PATH gcov )
    find_program( LCOV_PATH  NAMES lcov lcov.bat lcov.exe lcov.perl)
    find_program( GENHTML_PATH NAMES genhtml genhtml.perl genhtml.bat )
    find_program( GCOVR_PATH gcovr PATHS ${CMAKE_SOURCE_DIR}/scripts/test)
    find_program( SIMPLE_PYTHON_EXECUTABLE python )

    set(DEFAULT_COPTS "${DEFAULT_COPTS};${COVERAGE_FLAGS}")
    set(TEST_COPTS "${TEST_COPTS};${COVERAGE_FLAGS}")

    if(NOT ${CMAKE_BUILD_TYPE_LOWER} MATCHES "debug")
        message(WARNING "Code coverage results with an optimised (non-Debug) build may be misleading")
    endif() # NOT CMAKE_BUILD_TYPE STREQUAL "Debug"

    if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
        link_libraries(gcov)
    else()
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    endif()
endif()

# Set C++ standard to 17
if(NOT "${CMAKE_CXX_STANDARD}")
    set(CMAKE_CXX_STANDARD 20)
endif()