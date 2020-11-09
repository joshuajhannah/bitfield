set(TEST_NAME "test_bitfield")

set(SOURCE_FILES
        test_bitfield.cpp
        )

# Create a test executable
add_executable(${TEST_NAME} "")

# Add sources
target_sources(${TEST_NAME} PRIVATE ${SOURCE_FILES})

# Include directories
target_include_directories(${TEST_NAME} PRIVATE ${CATCH_INCLUDE_DIRS})

# Add compiler options for this library
target_compile_options(${TEST_NAME} PRIVATE ${TEST_COPTS} ${EXCEPTIONS_FLAG})

# Link dependencies
target_link_libraries(${TEST_NAME} gtest gtest_main)

# Do not decay cxx standard if not specified
set_property(TARGET ${TEST_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

message( STATUS "RUNTIME_OUTPUT_DIRECTORY: " ${CMAKE_BINARY_DIR}/build/test )

# Set output test directory
set_target_properties(
        ${TEST_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/test)

# Add this target to the post build unit tests
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})