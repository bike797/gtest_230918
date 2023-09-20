// 19_Mock종류.cpp
#include <string>

class Car {
public:
    virtual ~Car() { }

    virtual void Go() { }
    virtual std::string GetName() const { return "Sonata"; }
};

void Process(Car* p)
{
    // ...
    std::string name = p->GetName();
    p->Go();
    // ...
}

#include <gmock/gmock.h>
/*
GMOCK WARNING:
Uninteresting mock function call - returning default value.
    Function call: GetName()
          Returns: ""
*/
// 원인: MOCK_METHOD 메소드가 EXPECT_CALL을 하지 않았는데,
//      호출이 수행된 경우, 위의 경고가 발생합니다.

// GoogleMock은 3가지 종류의 Mock이 있습니다.
// 위의 경우를 다른 정책으로 처리합니다.

// 1) Naggy Mock(기본)
// => 경고를 발생시키지만, 테스트의 결과는 성공입니다.

// 2) Nice Mock
// => 경고도 발생하지 않습니다.

// 3) Strict Mock
// => 테스트가 실패합니다.
// => 테스트의 통과 기준이 높아지고, 테스트 비용의 증가가 발생할 수 있습니다.

class MockCar : public Car {
public:
    MOCK_METHOD(void, Go, (), (override));
    MOCK_METHOD(std::string, GetName, (), (const, override));
};

using testing::NiceMock;
using testing::StrictMock;

TEST(CarTest, Process)
{
    // MockCar mock;
    // NiceMock<MockCar> mock;
    StrictMock<MockCar> mock;

    EXPECT_CALL(mock, Go);
    // EXPECT_CALL(mock, GetName);

    Process(&mock);
}
