// 3_테스트픽스쳐.cpp
class Calc {
public:
    double Display() { return 0.0; }

    void Enter(double n) { }
    void PressPlus() { }
    void PressMinus() { }
    void PressEquals() { }
};

#include <gtest/gtest.h>

#define SPEC(msg) printf("[SPEC] %s\n", msg)

TEST(CalcTest, PressPlus)
{
    SPEC("10 더하기 10을 하였을 때, 20의 결과가 디스플레이 되는지 검증한다.");
    // Arrange
    Calc* calc = new Calc;

    // Act
    calc->Enter(10);
    calc->PressPlus();
    calc->Enter(10);
    calc->PressEquals();

    // Assert
    ASSERT_EQ(calc->Display(), 20) << "10 더하기 10 하였을 때";
}

TEST(CalcTest, PressMinus)
{
    Calc* calc = new Calc;

    calc->Enter(10);
    calc->PressMinus();
    calc->Enter(10);
    calc->PressEquals();

    ASSERT_EQ(calc->Display(), 0) << "10 빼기 10 하였을 때";
}
