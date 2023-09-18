// 5_전역픽스쳐.cpp
// => Test Fixture / Test Suite Fixture
//  : xUnit Test Framework이 공통적으로 제공하는 기능입니다.
// => Global Fixture
//  : Google Test Framework이 제공하는 기능입니다.
//    프로그램 시작/끝에 픽스쳐를 설치하고 해체하는 기능을 제공합니다.

#include <gtest/gtest.h>

TEST(SampleTest, foo) { }
TEST(ImageProcessorTest, goo) { }

// 전역 픽스쳐를 사용하는 방법
// 1) testing::Environment 자식 클래스를 정의합니다.
class MyEnvironment : public testing::Environment {
public:
    void SetUp() override
    {
        std::cout << "MyEnvironment.SetUp()" << std::endl;
    }

    void TearDown() override
    {
        std::cout << "MyEnvironment.TearDown()" << std::endl;
    }
};

// 2) 설치하는 방법 2가지
//  - main을 통해 설치합니다.
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    testing::AddGlobalTestEnvironment(new MyEnvironment);

    return RUN_ALL_TESTS();
}
