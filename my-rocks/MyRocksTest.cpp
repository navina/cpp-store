#include <gtest/gtest.h>
#include <iostream>

TEST (MyRocksTest, myrockstest) {
    std::cout << "Inside the test!" << std::endl;
    ASSERT_EQ(1 + 1, 2);
}
