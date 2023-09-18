// 7_GoogleTest.cpp
#include <gtest/gtest.h>

// * 작성중인 테스트는 명시적으로 실패해야 합니다.
// * 테스트를 주석처리하게 되면, 잊혀진 테스트가 됩니다.
// * 테스트를 비활성화해서, 테스트를 수행하지 않고, 결과에 포함되지 않습니다.
//   비활성화된 테스트의 존재 여부를 알립니다.
// => Google Test에서 테스트를 비활성화하는 방법은
//    테스트 스위트 이름 또는 테스트 케이스의 이름이 DISABLED_로 시작해야 합니다.
// => 비활성화된 테스트도 수행할 수 있는 기능을 제공합니다.
//   $ ./a.out --gtest_also_run_disabled_tests

TEST(ImageProcessorTest, DISABLED_ResizeImage)
{
    // 작성중입니다.
    FAIL() << "작성중입니다.";
}

class DISABLED_SampleTest : public testing::Test { };

TEST_F(DISABLED_SampleTest, foo) { }
TEST_F(DISABLED_SampleTest, goo) { }
TEST_F(DISABLED_SampleTest, hoo) { }
