message(STATUS "Generating samples")

add_executable(lowletorfeats.example src/example.cpp)
target_link_libraries(lowletorfeats.example lowletorfeats)

message(STATUS "Generating samples - done")
