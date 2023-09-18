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
    ~MyEnvironment() { std::cout << "~MyEnvironment()" << std::endl; }

    void SetUp() override
    {
        std::cout << "MyEnvironment.SetUp()" << std::endl;
    }

    void TearDown() override
    {
        std::cout << "MyEnvironment.TearDown()" << std::endl;
    }
};

class MyEnvironment2 : public testing::Environment {
public:
    ~MyEnvironment2() { std::cout << "~MyEnvironment()" << std::endl; }

    void SetUp() override
    {
        std::cout << "MyEnvironment2.SetUp()" << std::endl;
    }

    void TearDown() override
    {
        std::cout << "MyEnvironment2.TearDown()" << std::endl;
    }
};

// 2) 설치하는 방법 2가지
//  - main을 통해 설치합니다.
#if 1
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    testing::AddGlobalTestEnvironment(new MyEnvironment2);
    testing::AddGlobalTestEnvironment(new MyEnvironment);
    // 주의: 반드시 new를 통해 생성된 객체를 등록해야 합니다.

    return RUN_ALL_TESTS();
}
#endif
// - 전역 변수
// : 두 개이상의 글로벌 픽스쳐를 등록할 경우,
//   어떤 픽스쳐가 먼저 수행될지 보장할 수 없습니다.
//  => main을 직접 정의해서 등록해야 합니다.
#if 0
testing::Environment* my_env = testing::AddGlobalTestEnvironment(new MyEnvironment);

// 별도의 파일
testing::Environment* my_env2 = testing::AddGlobalTestEnvironment(new MyEnvironment2);
#endif
