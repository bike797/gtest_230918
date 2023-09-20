// 18_Mocking2.cpp
#include <gmock/gmock.h>

struct Element { }; // Dummy

class Calc {
public:
    virtual ~Calc() { }

    // 주의: 순수 가상 함수가 아닙니다.
    virtual int Add(Element x) { return 0; } // 행위 기반 검증 대상 X
    virtual int Add(int times, Element x) { return 0; } // 행위 기반 검증 대상 O
};

class MockCalc : public Calc {
public:
    // 행위 기반 검증을 수행하고자 하는 메소드에 대해서만 Mocking을 수행하면 됩니다.
    // int Add(int times, Element x) override
    MOCK_METHOD(int, Add, (int times, Element x), (override));

    // 해결 방법: 명시적으로 동일한 이름의 using 선언이 필요합니다.
    using Calc::Add;
};

TEST(CalcTest, Sample)
{
    MockCalc mock;

    // 문제: 오버로딩 되어 있는 함수를 Mocking 하면, Mocking에 의해서
    //      이름이 가려지는 문제가 발생합니다.
    mock.Add(Element {});
    mock.Add(42, Element {});
}
