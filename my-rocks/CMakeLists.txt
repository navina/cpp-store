## Download dependencies with Hunter ##
hunter_add_package(Boost COMPONENTS regex system filesystem)
hunter_add_package(GTest)

## Find Dependencies ##
find_package(Boost CONFIG REQUIRED regex system filesystem)
find_package(GTest CONFIG REQUIRED)

## Targets ##
add_executable(MyRocks src/MyRocksMain.cpp include/Tuple.hpp)
add_executable(MyRocksTest tests/MyRocksTest.cpp src/MyTuple.cpp)

target_link_libraries(MyRocks PUBLIC Boost::regex Boost::system Boost::filesystem)
target_link_libraries(MyRocksTest PUBLIC GTest::main)

add_test(MyRocksTest MyRocksTest)
