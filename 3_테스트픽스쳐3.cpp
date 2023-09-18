// 3_테스트픽스쳐2.cpp
class Calc {
public:
    // 요구사항 변경
    Calc(int n) { }

    double Display() { return 0.0; }

    void Enter(double n) { }
    void PressPlus() { }
    void PressMinus() { }
    void PressEquals() { }
};

#include <gtest/gtest.h>

#define SPEC(msg) printf("[SPEC] %s\n", msg)

// 2. Text Fixture 설치하는 방법
//  3) Implicit Set Up(암묵적 설치)
//  => xUnit Test Framework가 제공하는 기능입니다.
//  방법: 여러 테스트케이스에서 같은 테스트 픽스쳐 설치의 코드를 암묵적으로 호출되는
//      함수를 통해서 처리합니다.
//   : 명시적인 테스트 스위트 클래스가 필요합니다.

// 1) 테스트스위트 클래스를 testing::Test 자식 클래스로 만듭니다.
class CalcTest : public testing::Test {
protected:
    Calc* calc;

    void SetUp() override
    {
        std::cout << "SetUp()" << std::endl;
        calc = new Calc { 0 };
    }
};

// 2) TEST_F를 통해 테스트 케이스를 정의합니다.
TEST_F(CalcTest, PressPlus)
{
    SPEC("10 더하기 10을 하였을 때, 20의 결과가 디스플레이 되는지 검증한다.");

    // Act
    calc->Enter(10);
    calc->PressPlus();
    calc->Enter(10);
    calc->PressEquals();

    // Assert
    ASSERT_EQ(calc->Display(), 20) << "10 더하기 10 하였을 때";
}

TEST_F(CalcTest, PressMinus)
{
    calc->Enter(10);
    calc->PressMinus();
    calc->Enter(10);
    calc->PressEquals();

    ASSERT_EQ(calc->Display(), 0) << "10 빼기 10 하였을 때";
}
