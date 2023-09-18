// 6_Assertion.cpp
#include <gtest/gtest.h>

int foo() { return 42; }
int goo() { return 100; }

// 1. ASSERT_XXX
//   EQ/NE/LT/GT/LE/GE/TRUE/FALSE ...
//  => Google Test는 단언문을 매크로의 형태로 제공합니다.
//  => ASSERT_XXX: 하나의 단언문이 실패할 경우, 이후의 코드를 수행하지 않습니다.
//  => 하나의 테스트 케이스 안에서 여러개의 단언문을 사용할 경우,
//     단언문이 실패할 때, 이후의 단언문을 수행하지 않음으로
//     "죽은 단언문" 문제가 발생합니다.
//   : xUnit Test Pattern에서는 하나의 테스트케이스 안에 여러개의 단언문을 작성하지 말자.
//  => GoogleTest는 새로운 단언문을 제공합니다.
TEST(SampleTest, Sample1)
{
    // ...
    ASSERT_EQ(foo(), 4);
    ASSERT_EQ(goo(), 10);
}

// 2. EXPECT_XXX
//   EQ/NE/LT/GT/LE/GE/TRUE/FALSE ...
// => EXPECT_XXX: 단언문이 실패할 경우, 테스트의 결과는 실패로 변경되지만,
//        이후의 코드를 계속 수행합니다.
//   "죽은 단언문 문제"가 발생하지 않습니다.
TEST(SampleTest, Sample2)
{
    // ...
    EXPECT_EQ(foo(), 4);
    EXPECT_EQ(goo(), 10);
}

class User {
    std::string name = "Tom";

public:
    std::string GetName() const { return name; }
};

// User* GetUser() { return new User; }
User* GetUser() { return nullptr; }

TEST(SampleTest, Sample3)
{
    User* user = GetUser();

    ASSERT_NE(user, nullptr); // 왜 ASSERT로 작성되어야 하는지를 이해해야 합니다.
    EXPECT_EQ(user->GetName(), "Tom");
    // 널 참조로 인해, 테스트 프로그램이 비정상 종료할 수 있습니다.
}
