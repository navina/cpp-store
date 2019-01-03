# cpp-store
# How To
## Build 
Build the project with CMake and Make commands to generate executables
```shell
mkdir -p build
cd build
cmake ..
make
```
## Run Main
```shell
cd build
./my-rocks/MyRocks
```

## Run Test
```shell
cd build
./my-rocks/MyRocksTest
```

## Run Code Coverage with GCov
```shell
cd build
make gcov
```
You can find the the .GCNO files in build/coverage directory. You have to delete the .GCNO and .GCDA files before re-running the coverage tests.
