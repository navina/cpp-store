#include <iostream>

int sum(int a, int b) {
    return a + b;
}

int main(int argc, char **argv) {
    std::cout << "Hello!" << std::endl;
    int result = sum(2, 3);
    std::cout << "Sum of 2 and 3 is " << result << std::endl;
    return 0;
}