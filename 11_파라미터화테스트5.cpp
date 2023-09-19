// 11_파라미터화테스트5.cpp
#include <gtest/gtest.h>

// 파라미터화 테스트에서 데이터셋을 정의하는 함수
// 1. testing::Values(1, 2, 3, 4, 5);
// 2. testing::ValuesIn(data)
// 3. testing::Range(start, end, step)
// 4. testing::Combine(
//        testing::ValuesIn(cars), testing::ValuesIn(colors));
class SampleTest : public testing::TestWithParam<int> {
public:
    void SetUp() override { std::cout << "SetUp()" << std::endl; }
    void TearDown() override { std::cout << "TearDown()" << std::endl; }

    static void SetUpTestSuite() { std::cout << "SetUpTestSuite()" << std::endl; }
    static void TearDownTestSuite() { std::cout << "TearDownTestSuite()" << std::endl; }
};

INSTANTIATE_TEST_SUITE_P(SampleValues, SampleTest,
    // testing::Values(1, 3, 5, 7, 9, 11, 13, 15)
    testing::Range(1, 100, 2));

TEST_P(SampleTest, Sample)
{
    std::cout << GetParam() << std::endl;
}

// * 구글 테스트가 제공하는 테스트케이스를 만드는 3가지 방법
// 1) TEST(SampleTest, Sample) {}
//  => 테스트 스위트 클래스를 명시적으로 제공하지 않습니다.

// 2) TEST_F
//    class SampleTest : public testing::Test {};
//    TEST_F(SampleTest, Sample) {}

// 3) TEST_P
//    class SampleTest : public testing::TestWithParam<int> {};
///   INSTANTIATE_TEST_SUITE_P(SampleValues, SampleTest, Values(1, 2, 3));
//    TEST_P(SampleTest, Sample) { GetParam(); }
