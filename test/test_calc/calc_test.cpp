/**
 * tests/test_defaults.cpp
 */

#include "calc.h"
#include "gtest/gtest.h"

#define SPEC(msg) printf("[ SPEC     ] %s\n", msg)

namespace gtestbox {
    namespace tests {
        namespace test_hello {

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
                SPEC("10 더하기 10을 하였을 때, 20의 결과가 디스플레이 되는지 검증한다.");
                Calc* calc = new Calc;

                calc->Enter(10);
                calc->PressMinus();
                calc->Enter(10);
                calc->PressEquals();

                ASSERT_EQ(calc->Display(), 0) << "10 빼기 10 하였을 때";
            }

        }
    }
}
