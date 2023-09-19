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
#if 0
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
#endif
// 2) 사용자 정의 타입
// > Google Test에서 사용자 정의 타입이 표현될 때,
//   원하는 형태로 표현되도록 연산자 재정의를 제공해야 합니다.

#if 1
struct InputType {
    std::string name;
    int age;
};

std::ostream& operator<<(std::ostream& os, const InputType& data)
{
    return os << "(" << data.name << ", " << data.age << ")";
}

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
    EXPECT_TRUE(Process(data.name, data.age));
}
#endif
