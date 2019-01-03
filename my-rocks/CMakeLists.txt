## Download dependencies with Hunter ##
hunter_add_package(Boost COMPONENTS regex system filesystem)
hunter_add_package(GTest)

## Find Dependencies ##
find_package(Boost CONFIG REQUIRED regex system filesystem)
find_package(GTest CONFIG REQUIRED)

## Targets ##
add_executable(MyRocks MyRocksMain.cpp)
add_executable(MyRocksTest MyRocksTest.cpp)

target_link_libraries(MyRocks PUBLIC Boost::regex Boost::system Boost::filesystem)
target_link_libraries(MyRocksTest PUBLIC GTest::main)

## For reference
message("-- CMAKE_SOURCE_DIR - ${CMAKE_SOURCE_DIR} -- ")
message("-- CMAKE_BINARY_DIR - ${CMAKE_BINARY_DIR} -- ")

## Create OBJECT_DIR variable - the directory we will provide to `gcov` command
## gcov will use the directory to search for object files
set(OBJECT_DIR ${CMAKE_BINARY_DIR}/my-rocks/CMakeFiles/MyRocksTest.dir)
message("-- Object files will be output to: ${OBJECT_DIR}")

## Create the gcov target
# Creates a directory to hold the coverage results. Runs `make test` in the cmake_binary_dir
add_custom_target(gcov
        COMMAND mkdir -p coverage
        COMMAND ${CMAKE_MAKE_PROGRAM} test
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )

## Creates a custom gcov Command with target gcov
# Run coverage tests with 'make gcov'
add_custom_command(TARGET gcov
        COMMAND echo "=================== GCOV ===================="
        COMMAND gcov -b ${CMAKE_SOURCE_DIR}/my-rocks/MyRocksTest.cpp -o ${OBJECT_DIR}
        #| grep -B 5 "MyRocksTest.cpp.gcov" > CoverageSummary.tmp
        #COMMAND cat CoverageSummary.tmp
        COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/coverage"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
        )
add_dependencies(gcov MyRocks MyRocksTest)

add_test(MyRocksTest MyRocksTest)
