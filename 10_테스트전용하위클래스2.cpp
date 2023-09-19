// 10_테스트전용하위클래스2.cpp
#include <iostream>

class Engine {
public:
    virtual ~Engine() { }

    // 반드시 가상함수이어야 합니다.
    // => 가상 함수가 테스트를 할때 좀더 편리하게 테스트할 수 있습니다.
    virtual void Start()
    {
        // ...
        std::cout << "Engine Start" << std::endl;
        // ...
    }
};

class Car {
    Engine* engine;

public:
    Car(Engine* p)
        : engine { p }
    {
    }

    void Go() const
    {
        // ...
        engine->Start();
        // ...
    }
};

// Car의 Go가 호출되었을 때, Engine에 대해서 Start가 호출되었는지 여부를 검증하고 싶습니다.

#include <gtest/gtest.h>

class TestEngine : public Engine {
    bool isStart = false;

public:
    void Start() override
    {
        std::cout << "TestEngine::Start" << std::endl;
        Engine::Start(); // 부모 함수를 호출
        isStart = true;
    }

    // 테스트에서 확인할 수 있는 기능을 테스트 전용 하위 클래스를 통해서 제공합니다.
    bool IsStart() const { return isStart; }
};

TEST(CarTest, Go)
{
    TestEngine engine;
    Car car { &engine };

    car.Go();

    EXPECT_TRUE(engine.IsStart());
}

#if 0
TEST(CarTest, Go)
{
    Engine engine;
    Car car { &engine };

    car.Go();

    // 문제: Engine이 검증할 수 있는 기능을 제공하고 있지 않습니다.
}
#endif

// 테스트 가능 설계(Testability)
// => 제품 코드는 테스트 하기 쉬워야 합니다.
//  : 테스트 용이성
//  1) private 메소드는 public 메소드의 가독성을 높이기 위해 사용해야 합니다.
//  2) 일반 멤버 함수보다 가상 멤버 함수가 테스트 용이합니다.
//  : 테스트 작성 비용을 절감할 수 있습니다.
