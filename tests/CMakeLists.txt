message(STATUS "Generating tests")

# Create and link the test executables
add_executable(lowletorfeats.test_FeatureKey src/test_FeatureKey.cpp)
add_executable(lowletorfeats.test_Document src/test_Document.cpp)
add_executable(lowletorfeats.test_FC src/test_FC.cpp)

target_link_libraries(lowletorfeats.test_FeatureKey lowletorfeats)
target_link_libraries(lowletorfeats.test_Document lowletorfeats)
target_link_libraries(lowletorfeats.test_FC lowletorfeats)

# Test definitions
macro(create_test target)
    add_test(NAME ${target} COMMAND $<TARGET_FILE:${target}>)
endmacro(create_test)

create_test(lowletorfeats.test_FeatureKey)
create_test(lowletorfeats.test_Document)
create_test(lowletorfeats.test_FC)

message(STATUS "Generating tests - done")

# -----------------------------------------------------------------------------
# Code Coverage report
# -----------------------------------------------------------------------------
# cmake .. -DENABLE_CODECOV=ON
# cmake --build .
# cmake --target target
if (ENABLE_COVERAGE)
    include(CodeCoverage)
    set(COVERAGE_LCOV_EXCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/../libs/*")

    APPEND_COVERAGE_COMPILER_FLAGS()

    include(ProcessorCount)
    ProcessorCount(N_CORES)

    SETUP_TARGET_FOR_COVERAGE_LCOV(
        NAME lowletorfeats.coverage
        EXECUTABLE cd tests/ && ctest -j ${N_CORES}
        DEPENDENCIES
            lowletorfeats.test_FeatureKey
            lowletorfeats.test_Document
            lowletorfeats.test_FC
    )
endif()
