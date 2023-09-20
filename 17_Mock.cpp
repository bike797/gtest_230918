// 17_Mock.cpp
#include <string>
#include <vector>

enum Level {
    INFO,
    WARN,
    ERROR
};

class DLoggerTarget {
public:
    virtual ~DLoggerTarget() { }

    virtual void Write(Level level, const std::string& message) = 0;
};

class FileTarget : public DLoggerTarget { };
class NetworkTarget : public DLoggerTarget { };

class DLogger {
    std::vector<DLoggerTarget*> targets;

public:
    void AddTarget(DLoggerTarget* p) { targets.push_back(p); }

    void Write(Level level, const std::string& message)
    {
        for (auto e : targets) {
            e->Write(level, message);
            // break;
        }
    }
};

// Mock Object Pattern(모의 객체)
// 의도: SUT의 함수를 호출하였을 때, 발생하는 부수 효과를 관찰할 수 없어서
//      테스트되지 않은 요구사항이 존재합니다.
// 방법: 행위 기반 검증을 수행합니다.

// 상태 검증
//  - 객체에 작용을 가한 후, 내부의 상태의 변화를 단언문을 통해서 확인합니다.
// 동작 검증
//  - 객체에 작용을 가한 후, 내부적으로 발생하는 함수의 호출 여부, 호출 횟수, 호출 인자, 호출 순서 정보를
//    통해 정상 동작 여부를 검증합니다.
//  => Mock Object(모의 객체)는 Mock Framework을 이용해서 생성할 수 있습니다.
//   C++: Google Mock 프로젝트는 원래는 별도의 프로젝트로 존재했지만,
//        1.8 버전 이후로 Google Test에 흡수 되었습니다.

// #include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mock Framework을 이용해서, 테스트 대역(모의 객체)을 만들어야 합니다.
class MockDLoggerTarget : public DLoggerTarget {
public:
    // - Mocking
    // MOCK_METHOD{인자개수}(메소드 이름, 메소드 타입)
    // MOCK_METHOD2(Write, void(Level level, const std::string& message));

    // 1.10 이후로 Google Mock의 Mocking의 방법이 변경되었습니다.
    // MOCK_METHOD(반환타입,메소드이름, (인자정보), (한정자 정보))

    // void Write(Level level, const std::string& message) override
    MOCK_METHOD(void, Write, (Level level, const std::string& message), (override));
};

// Google Mock은 Act 하기 전에 Assert를 먼저 작성해야 합니다.
TEST(DLoggerTest, Write)
{
    // Arrange
    DLogger logger;
    MockDLoggerTarget mock1, mock2;
    logger.AddTarget(&mock1);
    logger.AddTarget(&mock2);

    // Assert
    EXPECT_CALL(mock1, Write(INFO, "test_message"));
    EXPECT_CALL(mock2, Write(INFO, "test_message"));

    // Act
    logger.Write(INFO, "test_message");
}

// * 테스트 대역(Test Double)
// 1. Test Stub
//  => SUT가 테스트하는데 필요한 결과를 테스트 대역을 통해 제어합니다.
//   "특수한 상황을 시뮬레이션 하는 목적"

// 2. Fake Object
//  => 협력 객체가 준비되지 않았거나, 사용하기 어렵거나, 너무 느려서
//     같은 역활을 수행하는 가벼운 테스트 대역을 통해 SUT를 검증합니다.

// 3. Test Spy
//  => 관찰할 수 있는 SUT의 부수효과가 존재하지 않는 경우,
//     협력 객체를 이용해서 목격한 일을 기록해두었다가, 테스트에서 확인합니다.

// 4. Mock Object
// => 관찰할 수 있는 SUT의 부수효과가 존재하지 않는 경우,
//    협력 객체를 대상으로 호출되는 메소드의 호출 여부/인자/순서 등의 정보를 통해
//    "행위 기반 검증"을 수행합니다.
