#include "gtest/gtest.h"
#include "gmock/gmock.h"

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    std::cout << "AEDA 220/2021 - Practical 6" << std::endl;
    return RUN_ALL_TESTS();
}