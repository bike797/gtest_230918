// 9_FriendTest.cpp
#if 0
class User {
    int age = 42;

    int GetAge() const { return age; }

public:
    void foo() { age = 100; }
};
#endif
#include "User.h"

#include <gtest/gtest.h>

// 문제점
// : 테스트 코드에서 확인해야 하는 메소드가
//   private 영역에 존재해서 외부에서 접근이 불가능합니다.
// 해결방법
// => Friend Test로 테스트케이스를 선언하면,
//    private 영역에 접근할 수 있습니다.
//  : SUT(제품코드)에 Google Test 의존성이 생깁니다.
//  오직 C++ 기반의 Google Test에서만 제공합니다.

// => 다른 플랫폼에서는 private 메소드를 검증할 수 없습니다.
//    테스트를 통해 검증이 필요하면, 공개되어야 합니다.
//   "테스트되지 않은 private 메소드보다 테스트된 public 메소드가 안전합니다."

// => private 메소드의 용도를 public 메소드의 가독성을 높이기 위해 사용해야 됩니다.
//   : public 메소드 검증을 통해 자연스럽게 private 메소드도 검증할 수 있습니다.
//  "Clean Code"

TEST(UserTest, foo)
{
    User user;

    user.foo();

    EXPECT_EQ(user.GetAge(), 100);
}
