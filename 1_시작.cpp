// 1_시작.cpp
#include <gtest/gtest.h>


// Google Test에서는 main을 아래 형태로 제공해야 합니다.
// - Google Test는 다양한 환경에서 동작하는 main을 제공합니다.
//   gtest_main.cc
// - 라이브러리에 main을 포함시키면, 매번 main을 작성할 필요가 없습니다.
#if 0
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif

// $ g++ 1_시작.cpp -std=c++14 -I ./googletest/googletest/include -L. -lgtest -pthread
// $ ./a.out
