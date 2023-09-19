// 11_파라미터화테스트3.cpp
#include <string>
#include <iostream>

bool Process(const std::string& name, int age)
{
    std::cout << name << ", " << age << std::endl;
    // return true;
    return false;
}

#include <gtest/gtest.h>

// 입력이 두개 이상의 데이터를 가지는 경우
// 1) tuple
// 2) 사용자 정의 타입
using InputType = std::tuple<std::string, int>;

class ProcessTest : public testing::TestWithParam<InputType> {
};

INSTANTIATE_TEST_SUITE_P(ProcessValues, ProcessTest,
    testing::Values(
        InputType { "Tom", 42 },
        InputType { "Bob", 100 },
        InputType { "Alice", 32 }));

TEST_P(ProcessTest, Process)
{
    const InputType& data = GetParam();
    EXPECT_TRUE(Process(std::get<0>(data), std::get<1>(data)));
}
