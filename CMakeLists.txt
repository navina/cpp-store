cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.33.tar.gz"
    SHA1 "acbf4b9b77b5a0160adc1da1cdda35f64b14196a"
)

project(CppStore)

add_subdirectory(my-rocks)
