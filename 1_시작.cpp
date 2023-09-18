// 1_시작.cpp
#include <gtest/gtest.h>


// Google Test에서는 main을 아래 형태로 제공해야 합니다.
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// $ g++ 1_시작.cpp -std=c++14 -I ./googletest/googletest/include -L. -lgtest -pthread
// $ ./a.out
