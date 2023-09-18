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
// 1) Arrange/Given: 테스트 대상 코드를 초기화하고, 필요한 경우 설정하고 준비합니다.
// 2)      Act/When: 테스트 대상 코드에 작용을 가합니다.
// 3)   Assert/Then: 기대하는 바를 단언합니다.

// 3. 좋은 단위 테스트
//  1) 가독성
//     - 테스트 코드의 구성
//     - 테스트 케이스의 이름
//      : 어떤 시나리오로 테스트가 수행되는가
//     - 테스트 케이스의 실패
//      : 테스트가 실패하였을 때, 왜 실패하였는지?

//  2) 유지보수성
//    - 테스트 코드도 유지보수의 대상입니다.
//    => 테스트 코드의 유지보수의 비용을 최소화해야 합니다.
//       오류가 발생할 가능성이 있는 코드는 테스트케이스 안에서
//       지양해야 합니다.
//       제어 구문(조건문, 반복문, 예외 처리)의 코드의 발생을
//       최소화해야 합니다.

//  3) 신뢰성
//   - 테스트의 결과를 신뢰할 수 있는가?

// 3. BDD(Behavior Driven Development)
//   1) 가독성 => 용어을 사람이 사용하는 자연어와 유사하게 구성합니다.
//   2) 상태 검증 / 행위 검증

#define SPEC(msg) printf("[SPEC] %s\n", msg)

TEST(CalcTest, PressPlus2)
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
#if 0
    if (calc->Display() != 20) {
        FAIL() << "10 더하기 10을 하였을 때, 결과가 일치하지 않음.";
    } else {
        SUCCEED();
    }
#endif
    // xUnit Test Framework는 다양한 단언문을 제공하고 있습니다.
    //  : ASSERT_EQ/NE/LT/GT/LE/GE ...
    ASSERT_EQ(calc->Display(), 20) << "10 더하기 10 하였을 때";
}
