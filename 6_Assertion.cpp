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
    ASSERT_EQ(foo(), 42);
    ASSERT_EQ(goo(), 100);
}

// 2. EXPECT_XXX
//   EQ/NE/LT/GT/LE/GE/TRUE/FALSE ...
// => EXPECT_XXX: 단언문이 실패할 경우, 테스트의 결과는 실패로 변경되지만,
//        이후의 코드를 계속 수행합니다.
//   "죽은 단언문 문제"가 발생하지 않습니다.
TEST(SampleTest, Sample2)
{
    // ...
    EXPECT_EQ(foo(), 42);
    EXPECT_EQ(goo(), 100);
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

// 3. C 문자열 비교 단언문
//   C 문자열: 널 문자('\0')로 종료하는 char 배열
//   EXPECT_STREQ / NE
//   EXPECT_STRCASEEQ / STRCASENE => 대소문자 무시
TEST(SampleTest2, Sample1)
{
    std::string s1 = "hello";
    std::string s2 = "hello";
    EXPECT_EQ(s1, s2);

    const char* s3 = "HELLO";
    const char* s4 = s1.c_str();
    // EXPECT_EQ(s3, s4); // !!!
    // EXPECT_STREQ(s3, s4);
    EXPECT_STRCASEEQ(s3, s4);
}

// 4. 부동소수점 비교 단언문
//  EXPECT_FLOAT_EQ / NE
//  EXPECT_DOUBLE_EQ / NE

//  * 오차 범위를 직접 지정하고 싶다면
//  EXPECT_NEAR(a, b, 오차범위)
TEST(SampleTest3, Sample1)
{
    double a = 0.7;
    double b = 0.1 * 7;

    // EXPECT_EQ(a, b);
    EXPECT_DOUBLE_EQ(a, b);
    EXPECT_NEAR(a, b, 0.00000000001);
}

// 테스트 커버리지
//  => 테스트 코드에 의해서 실행되는 제품 코드의 비율
//   80% - 100%

void OpenFile(const std::string& filename)
{
    if (filename.empty()) {
        // throw 1;
        throw std::invalid_argument("Invalid filename");
    }

    // ...
}

// 4. 예외 검증 단언문을 제공합니다.
// =>     EXPECT_THROW: 기대한 예외가 발생하는지 여부를 검증합니다.
//    EXPECT_ANY_THROW: 예외가 발생하는지 여부를 검증합니다.
//     EXPECT_NO_THROW: 예외가 발생하지 않음을 검증합니다.
TEST(SampleTest4, Sample2)
{
    std::string emptyFileName = "";

    EXPECT_THROW(OpenFile(emptyFileName), std::invalid_argument);
}

// 잘못된 파일을 전달하였을 때, std::invalid_argument 예외가 발생하는지 여부를
// 검증하고 싶습니다.
TEST(SampleTest4, Sample1)
{
    std::string emptyFileName = "";

    try {
        OpenFile(emptyFileName);
        FAIL() << "기대한 예외가 발생하지 않음.";
    } catch (std::invalid_argument& e) {
        SUCCEED();
    } catch (...) {
        FAIL() << "기대한 예외와 다릅니다.";
    }
}
