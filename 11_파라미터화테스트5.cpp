// 11_파라미터화테스트5.cpp
#include <gtest/gtest.h>

// 파라미터화 테스트에서 데이터셋을 정의하는 함수
// 1. testing::Values(1, 2, 3, 4, 5);
// 2. testing::ValuesIn(data)
// 3. testing::Range(start, end, step)
// 4. testing::Combine(
//        testing::ValuesIn(cars), testing::ValuesIn(colors));
class SampleTest : public testing::TestWithParam<int> {
};

INSTANTIATE_TEST_SUITE_P(SampleValues, SampleTest,
    // testing::Values(1, 3, 5, 7, 9, 11, 13, 15)
    testing::Range(1, 100, 2));

TEST_P(SampleTest, Sample)
{
    std::cout << GetParam() << std::endl;
}
