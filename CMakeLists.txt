cmake_minimum_required(VERSION 3.9)

## Clang Installation Directory
set(CLANG_INSTALL_BASE "/home/nramesh/cpp-projects/build")

## Set CMake compiler to Clang
set(CMAKE_C_COMPILER "${CLANG_INSTALL_BASE}/bin/clang")
set(CMAKE_CXX_COMPILER "${CLANG_INSTALL_BASE}/bin/clang++")
set(CMAKE_LINKER "${CLANG_INSTALL_BASE}/bin/clang++")
set(ENV{PATH} "${CLANG_INSTALL_BASE}:$ENV{PATH}")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)
set(CMAKE_CXX_FLAGS "-g -O2 -Wall -fprofile-instr-generate -fcoverage-mapping")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.33.tar.gz"
    SHA1 "acbf4b9b77b5a0160adc1da1cdda35f64b14196a"
)

project(CppStore)
## Enable Testing - before adding any sub-directories ##
enable_testing()

add_subdirectory(my-rocks)
