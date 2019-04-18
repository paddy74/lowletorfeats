add_executable(lowletorfeats.test_main src/main.cpp)

target_link_libraries(lowletorfeats.test_main lowletorfeats)

enable_testing()
add_test(test_main lowletorfeats.test_main)
