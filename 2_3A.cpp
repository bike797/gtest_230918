// 2_3A.cpp
//  SUT(System Under Test, 테스트 대상 시스템)
//   - CUT(Class Under Test / Code Under Test)
class Calc {
public:
    double Display() { return 0.0; }

    void Enter(double n) {}
    void PressPlus() {}
    void PressMinus() {}
    void PressEquals() {}
};

#include <gtest/gtest.h>

// 1. TestCase 만드는 방법
//  TEST 매크로를 통해서 테스트케이스를 만들 수 있습니다.
// : TEST(테스트 스위트 이름, 테스트 케이스 이름)
// => 테스트 스위트는 태스트 대상 클래스(모듈)의 이름의 마지막에
//    Test 또는 Spec 접미를 붙이는 형태로 많이 사용합니다.
TEST(CalcTest, PressPlus)
{
    // 아래 매크로 함수를 통해 테스트를 명시적으로 실패할 수 있습니다.
    //  > 실패의 이유를 함께 작성해야 합니다.
    FAIL() << "작성 중입니다.";
}

// 2. TestCase 구성하는 방법 - 3A
// 1) Arrange: 테스트 대상 코드를 초기화하고, 필요한 경우 설정하고 준비합니다.
// 2) Act: 테스트 대상 코드에 작용을 가합니다.
// 3) Assert: 기대하는 바를 단언합니다.

TEST(CalcTest, PressPlus2)
{
    // Arrange
    Calc* calc = new Calc;

    // Act
    calc->Enter(10);
    calc->PressPlus();
    calc->Enter(10);
    calc->PressEquals();

    // Assert
    if (calc->Display() != 20) {
        FAIL() << "10 더하기 10을 하였을 때";
    } else {
        SUCCEED();
    }
}
