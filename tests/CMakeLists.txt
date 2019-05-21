message(STATUS "Preparing tests")

# Enable construction of test target
enable_testing()

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

message(STATUS "Preparing tests - done")
