cmake_minimum_required(VERSION 3.10..3.31)
project(lg2_demo C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(_XOPEN_SOURCE ON)
# set(CMAKE_C_STANDARD 17)

set(BUILD_EXAMPLES OFF)
set(BUILD_TESTS OFF)
set(BUILD_SHARED_LIBS OFF)
set(USE_SSH ON)
set(USE_THREADS ON)
# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/debug)

add_subdirectory(${CMAKE_SOURCE_DIR}/libgit2)

add_compile_options(-std=gnu11)
add_executable(diff src/diff.c)
add_executable(threaded src/threaded.c)
add_executable(untracked src/untracked.c)

target_include_directories(diff PUBLIC libgit2)
target_include_directories(threaded PUBLIC libgit2)
target_include_directories(untracked PUBLIC libgit2)

target_link_libraries(
        diff PUBLIC libgit2 libgit2package
)

target_link_libraries(
        threaded PUBLIC libgit2 libgit2package
)

target_link_libraries(
        untracked PUBLIC libgit2 libgit2package
)
