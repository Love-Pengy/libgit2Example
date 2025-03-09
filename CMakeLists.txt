cmake_minimum_required(VERSION 3.23)
project(lg2_demo C)
set(CMAKE_C_STANDARD 99)

# set(CMAKE_PREFIX_PATH /opt/homebrew)
# set(CMAKE_PREFIX_PATH /opt/homebrew/opt/libssh2)
# set(CMAKE_PREFIX_PATH /opt/homebrew/opt/openssl@3)
set(BUILD_EXAMPLES OFF)
set(BUILD_TESTS OFF)
set(BUILD_SHARED_LIBS OFF)
set(USE_SSH ON)
set(USE_THREADS ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/debug)

#Use pkg-config to resolve brew installation dependencies
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(SSH2 REQUIRED IMPORTED_TARGET libssh2 openssl libssl libcrypto libpcre)

#The following dependencies can be used with the system's own
# find_library(CF CoreFoundation)
# find_library(SEC Security)
# find_library(ICONV iconv)
# find_library(SYS System)
# find_library(Z z)

add_subdirectory(${CMAKE_SOURCE_DIR}/libgit2)

add_executable(lg2_demo main.c)

target_include_directories(lg2_demo PUBLIC libgit2)

target_link_libraries(
        #It's very important here, I missed util, http-parser and libgit2package at the beginning, so I couldn't link it correctly at all
        lg2_demo PUBLIC libgit2 libgit2package
        # PkgConfig::SSH2
        # ${CF} ${SEC} ${ICONV} ${SYS} ${Z}
)
