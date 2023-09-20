// 20_Delegating.cpp
#include <iostream>

class Calc {
public:
    virtual ~Calc() { }

    virtual int Add(int a, int b) { return a + b; }
    virtual int Sub(int a, int b) { return a - b; }
};

void Process(Calc* p)
{
    if (p->Add(10, 20) == 30) {
        int result = p->Sub(100, 50);
        std::cout << "result: " << result << std::endl;
    }
}

#include <gmock/gmock.h>

// Mock Object(모의 객체)
// => 기능을 수행하지 않습니다.

// Google Mock은 MOCK_METHOD를 수행한 메소드에 대해서,
// 행위 기반 검증도 수행할 수 있지만, 결과를 제어하는 기능을 제공하고 있습니다.
// => Delegating(위임)
// : ON_CALL
//   - Stub, Fake를 Google Mock을 통해서 만들 수 있습니다.

class MockCalc : public Calc {
public:
    MOCK_METHOD(int, Add, (int a, int b), (override));
    MOCK_METHOD(int, Sub, (int a, int b), (override));
};

using testing::Return;

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }

struct Adder {
    int operator()(int a, int b) const { return a + b; }
};

TEST(CalcTest, Process)
{
    // Arrange
    MockCalc mock;
    // ON_CALL(mock, Add(10, 20)).WillByDefault(Return(30));
    // ON_CALL(mock, Sub(100, 50)).WillByDefault(Return(50));
    // ON_CALL(mock, Add).WillByDefault(&add); // 함수
    // ON_CALL(mock, Sub).WillByDefault(&sub); // 함수
    ON_CALL(mock, Add).WillByDefault(Adder {}); // 함수 객체
    ON_CALL(mock, Sub).WillByDefault([](int a, int b) { return a - b; }); // 람다 표현식

    // Assert
    EXPECT_CALL(mock, Add(10, 20));
    EXPECT_CALL(mock, Sub(100, 50));

    // Act
    // std::cout << mock.Add(10, 20) << std::endl;
    // std::cout << mock.Sub(100, 50) << std::endl;
    Process(&mock);
}
