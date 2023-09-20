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

class MockCar : public Car {
public:
    MOCK_METHOD(void, Go, (), (override));
    MOCK_METHOD(std::string, GetName, (), (const, override));
};

TEST(CarTest, Process)
{
    MockCar mock;

    EXPECT_CALL(mock, Go);

    Process(&mock);
}
