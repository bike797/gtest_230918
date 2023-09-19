// 11_파라미터화테스트.cpp
#include <string>
#include <regex>

bool IsValidEmail(const std::string& email)
{
    const std::regex pattern(R"((\w+)(\.|\_)?(\w*)@(\w+)(\.(\w+))+)");
    return std::regex_match(email, pattern);
}
