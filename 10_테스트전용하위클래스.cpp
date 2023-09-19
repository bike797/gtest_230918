// 10_테스트전용하위클래스.cpp
#include "User.h"

#include <gtest/gtest.h>

// 문제점: 테스트 코드에서 접근하고자 하는 상태가
//       protected로 지정되어 있습니다.
// 해결방법
//  > 테스트 전용 하위 클래스 패턴(Test Specific Subclass Pattern)
//  방법: 테스트 코드 안에서 SUT를 상속하는 하위 클래스를 만들어서
//       테스트 되지 않은 요구사항을 검증할 수 있습니다.
//  장점: 제품 코드를 변경하지 않고, 테스트를 수행할 수 있습니다.

class TestUser : public User {
public:
    int GetAge() const { return User::GetAge(); }
};

TEST(UserTest, foo)
{
    // User user;
    TestUser user;

    user.foo();

    EXPECT_EQ(user.GetAge(), 100);
}
