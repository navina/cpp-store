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

## Enable Testing ##
enable_testing()

add_test(MyRocksTest MyRocksTest.cpp)

