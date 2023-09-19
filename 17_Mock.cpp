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

#include <gtest/gtest.h>

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
