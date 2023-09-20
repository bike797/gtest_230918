// 18_Mocking6.cpp
enum Level {
    INFO,
    WARN
};

class Logger {
public:
    virtual ~Logger() { }

    virtual void Send(Level level,
        const char* dir,
        const char* file,
        const char* message)
        = 0;
};

class Car {
public:
    void Start(Logger* logger)
    {
        // ...
        logger->Send(INFO, "/tmp2", "car.log", "car start...");
        // ...
    }
};

// Car 객체가 logger를 사용할 때, /tmp 디렉토리에 로깅을 기록하는지 검증하고 싶습니다.
//  : 모든 인자에 대한 검증이 필요한 것이 아니라, dir에 대한 인자만 검증하고 싶습니다.
#include <gmock/gmock.h>
class MockLogger : public Logger {
public:
    MOCK_METHOD(void, Send, (const char* dir));

    void Send(Level level, const char* dir, const char* file, const char* message) override
    {
        // MOCK_METHOD한 메소드를 직접 호출합니다.
        Send(dir);
    }
};

TEST(CarTet, Start)
{
    MockLogger logger;
    Car car;

    EXPECT_CALL(logger, Send("/tmp")); // 원하는 인자만 검증할 수 있습니다. => 목 간략화

    car.Start(&logger);
}
