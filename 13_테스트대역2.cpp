// 13_테스트대역2.cpp
#include <string>

// Test Double(테스트 대역)
// 목적: 테스트 환경을 통제하기 위해서 사용합니다.
// 적용: 제품 코드에 테스트 대역을 적용하기 위해서는,
//      제품 코드가 테스트 대역을 적용할 수 있는 설계가 미리 반영되어 있어야 합니다.
//  => 약한 결합 / 느슨한 결합

// 강한 결합: 협력 객체를 이용할 때, 구체적인 타입에 의존하는 것
// 약한 결합: 협력 객체를 이용할 때, 추상 타입(추상 클래스/인터페이스)에 의존하는 것

// 1) 협력 객체 인터페이스 도입
class IFileSystem {
public:
    virtual ~IFileSystem() { }

    virtual bool IsValidFilename(const std::string& name) = 0;
};

// 2) 협력 객체의 인터페이스를 구현하는 형태로 변경합니다.
class FileSystem : public IFileSystem {
public:
    bool IsValidFilename(const std::string& name) override
    {
        // 현재의 파일 시스템에서 적합한 이름인지 확인합니다.
        // return true;
        return false;
    }
};

// 3) 외부에서 생성해서, 전달해야 합니다.
//    협력 객체를 직접 생성하는 것은, 강한 결합이 형성될 수 있습니다.
//   => 의존성 주입(Dependency Injection)
//    1) 생성자 주입
//     : 협력 객체가 필수적일 때
//    2) 메소드 주입
//     : 협력 객체가 필수적이지 않을 때

// Logger -------<> << IFileSystem >>
//                         |
//                      --------------
//                      |            |
//                 FileSystem    TestDouble
class Logger {
    IFileSystem* fs;

public:
    Logger(IFileSystem* p = nullptr)
        : fs { p }
    {
        // 기존 제품 코드의 동작과 동일하게 만들기 위해 제공합니다.
        if (fs == nullptr) {
            fs = new FileSystem;
        }
    }

    // 확장자를 제외한 파일명이 5글자 이상이어야 합니다.
    // ex)
    //  file.log  -> file   -> X
    // hello.log  -> hello  -> O
    bool IsValidLogFilename(const std::string& filename)
    {
        //------- 테스트 대상 코드
        size_t index = filename.find_last_of(".");
        std::string name = filename.substr(0, index);
        if (name.size() < 5) {
            return false;
        }
        //------- 테스트 대상 코드

        // IFileSystem* fs = new FileSystem;
        return fs->IsValidFilename(filename);
    }
};

//----
#include <gtest/gtest.h>

// 테스트 대역을 만드는 방법
// => 협력 객체의 인터페이스를 구현해서 만듭니다.

// Test Stub Pattern
class TestDoubleFileSystem : public IFileSystem {
public:
    bool IsValidFilename(const std::string& filename) override
    {
        return true; // 테스트 하는데 필요한 결과
    }
};

TEST(LoggerTest, IsValidLogFilename_NameLonggerThan5Chars_ReturnsTrue)
{
    TestDoubleFileSystem fs;
    Logger logger { &fs };
    std::string validFilename = "valid.log";

    EXPECT_TRUE(logger.IsValidLogFilename(validFilename)) << "확장자를 제외한 파일명이 다섯글자 이상일 때";
}

TEST(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse)
{
    TestDoubleFileSystem fs;
    Logger logger { &fs };
    std::string invalidFilename = "bad.log";

    EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename)) << "확장자를 제외한 파일명이 다섯글자 미만일 때";
}

//----
#include <gmock/gmock.h>

class MockFileSystem : public IFileSystem {
public:
    // bool IsValidFilename(const std::string& filename) override
    MOCK_METHOD(bool, IsValidFilename, (const std::string& filename), (override));
};

using testing::NiceMock;
using testing::Return;

TEST(LoggerTest2, IsValidLogFilename_NameLonggerThan5Chars_ReturnsTrue)
{
    NiceMock<MockFileSystem> fs;
    ON_CALL(fs, IsValidFilename).WillByDefault(Return(true));
    Logger logger { &fs };
    std::string validFilename = "valid.log";

    EXPECT_TRUE(logger.IsValidLogFilename(validFilename)) << "확장자를 제외한 파일명이 다섯글자 이상일 때";
}

TEST(LoggerTest2, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse)
{
    NiceMock<MockFileSystem> fs;
    ON_CALL(fs, IsValidFilename).WillByDefault(Return(true));
    Logger logger { &fs };
    std::string invalidFilename = "bad.log";

    EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename)) << "확장자를 제외한 파일명이 다섯글자 미만일 때";
}

// : xUnit Test Pattern
// 테스트 대역 4가지 종류
// 1) Test Stub
// 2) Fake Object
// 3) Test Spy
// 4) Mock Object
