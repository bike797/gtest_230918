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
//  2) Delegate Setup(위임 설치)
//   > 픽스쳐 설치에 관한 코드를 별도의 "테스트 유틸리티 함수"를 통해 캡슐화 합니다.
//   테스트 유틸리티 함수: 같은 테스트 스위트 안에서만 사용할 수 있어야 합니다.
//   => 명시적인 테스트 스위트 클래스를 제공해야 합니다.
#if 1
// 1) 테스트스위트 클래스를 testing::Test 자식 클래스로 만듭니다.
class CalcTest : public testing::Test {
protected:
    // * 테스트케이스는 자식 클래스로 만들어지기 때문에, private은 접근이 불가능합니다.
    Calc* CreateCalc() { return new Calc { 0 }; }
    // => 테스트 유틸리티 메소드 / 생성 메소드
};

// 2) TEST_F를 통해 테스트 케이스를 정의합니다.
TEST_F(CalcTest, PressPlus)
{
    SPEC("10 더하기 10을 하였을 때, 20의 결과가 디스플레이 되는지 검증한다.");
    // Arrange
    Calc* calc = CreateCalc();

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
    Calc* calc = CreateCalc();

    calc->Enter(10);
    calc->PressMinus();
    calc->Enter(10);
    calc->PressEquals();

    ASSERT_EQ(calc->Display(), 0) << "10 빼기 10 하였을 때";
}
#endif

// * 암묵적인 테스트 스위트 클래스
//             testing::Test
//                    |
//       -----------------------------
//       |                           |
// CalcTest_PressPlus_Test  CalcTest_PressMinus_Test

#if 0
// class CalcTest_PressPlus_Test : public ::testing::Test
TEST(CalcTest, PressPlus) { }

// class CalcTest_PressMinus_Test : public ::testing::Test
TEST(CalcTest, PressMinus) { }
#endif

// * 명시적인 테스트 스위트 클래스

//             testing::Test
//                    |
//                CalcTest : 명시적인 테스트 스위트 클래스
//                    |
//       -----------------------------
//       |                           |
// CalcTest_PressPlus_Test  CalcTest_PressMinus_Test
#if 0
class CalcTest : public testing::Test { };

// class CalcTest_PressPlus_Test : public CalcTest
TEST_F(CalcTest, PressPlus) { }

// class CalcTest_PressMinus_Test : public CalcTest
TEST_F(CalcTest, PressMinus) { }
#endif
