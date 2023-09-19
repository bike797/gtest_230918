// 13_테스트대역.cpp
#include <string>

class FileSystem {
public:
    bool IsValidFilename(const std::string& name)
    {
        // 현재의 파일 시스템에서 적합한 이름인지 확인합니다.
        return true;
    }
};

class Logger {
public:
    // 확장자를 제외한 파일명이 5글자 이상이어야 합니다.
    // ex)
    //  file.log  -> file   -> X
    // hello.log  -> hello  -> O
    bool IsValidLogFilename(const std::string& filename)
    {
        size_t index = filename.find_last_of(".");
        std::string name = filename.substr(0, index);
        if (name.size() < 5) {
            return false;
        }

        FileSystem fs;
        return fs.IsValidFilename(filename);
    }
};

//----
#include <gtest/gtest.h>

TEST(LoggerTest, IsValidLogFilename_NameLonggerThan5Chars_ReturnsTrue)
{
}

TEST(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse)
{
}
