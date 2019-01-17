#include <gtest/gtest.h>
#include <iostream>
#include <include/Tuple.hpp>


TEST (MyRocksTest, myrockstest) {
    std::cout << "Inside the tests!" << std::endl;
    ASSERT_EQ(1 + 1, 2);
}

TEST (MyRocksTest_Sum, myrockstest_1) {
    Tuple t = Tuple(2, 3);
    ASSERT_EQ(t.sum(), 2+3);
}
